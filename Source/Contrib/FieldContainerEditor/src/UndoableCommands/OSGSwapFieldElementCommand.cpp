/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include "OSGSwapFieldElementCommand.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SwapFieldElementCommand
A SwapFieldElementCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SwapFieldElementCommand::_Type("SwapFieldElementCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SwapFieldElementCommandPtr SwapFieldElementCommand::create(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex)
{
	return RefPtr(new SwapFieldElementCommand(FC, FieldId, FromIndex, ToIndex));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SwapFieldElementCommand::execute(void)
{
    //Check for a valid Field Container
    if(_FC == NULL)
    {
        SWARNING << "FieldContainer is NULL." << std::endl;
        return;
    }

    //Check for valid Field
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(!TheFieldHandle->isValid())
    {
        SWARNING << "No Field with Id: " << _FieldId << " in FieldContainers of type " << _FC->getType().getName() << std::endl;
        return;
    }

    //Check for valid Field cardinality
    if(TheFieldHandle->getCardinality() != FieldType::MultiField)
    {
        SWARNING << "Field: " << _FC->getType().getName() << " is not a MultiField" << std::endl;
        return;
    }

    //Check for valid indexing
    if(TheFieldHandle->getCardinality() == FieldType::MultiField && _FromIndex >= TheFieldHandle->size())
    {
        SWARNING << "Cannot move the value of from index " << _FromIndex << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }
    if(TheFieldHandle->getCardinality() == FieldType::MultiField && _ToIndex >= TheFieldHandle->size())
    {
        SWARNING << "Cannot move the value of to index " << _ToIndex << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }

    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        UInt32 MinIndex(osgMin(_FromIndex,_ToIndex)), MaxIndex(osgMax(_FromIndex,_ToIndex));
        FieldContainerUnrecPtr MinIndexFC = TheHandle->get(MinIndex);
        FieldContainerUnrecPtr MaxIndexFC = TheHandle->get(MaxIndex);

        //Replace the MinIndex first
        UInt32 InitialSize(TheHandle->size());
        TheHandle->replace(MinIndex, MaxIndexFC);
        if(InitialSize != TheHandle->size())
        {
            TheHandle->insert(MaxIndex, MinIndexFC);
        }
        else
        {
            TheHandle->replace(MaxIndex, MinIndexFC);
        }
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _ToIndex);
        std::string ToValue = StrStream.str();

        //Get the from index value
        StrStream.clear();
        StrStream.str("");
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _FromIndex);
        std::string FromValue = StrStream.str();

        //Set the value
        TheFieldHandle->pushIndexedValueFromCString(ToValue.c_str(), _FromIndex);
        TheFieldHandle->pushIndexedValueFromCString(FromValue.c_str(), _ToIndex);
    }

    Inherited::execute();
	_HasBeenDone = true;
}

std::string SwapFieldElementCommand::getCommandDescription(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);

	std::string Description("");

    Description = Description 
                + "Move " + TheFieldHandle->getDescription()->getName()
                + " index " + boost::lexical_cast<std::string>(_FromIndex) 
                + " to index " + boost::lexical_cast<std::string>(_ToIndex);
	
	return Description;
}

std::string SwapFieldElementCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void SwapFieldElementCommand::redo(void)
{
    Inherited::redo();

    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        UInt32 MinIndex(osgMin(_FromIndex,_ToIndex)), MaxIndex(osgMax(_FromIndex,_ToIndex));
        FieldContainerUnrecPtr MinIndexFC = TheHandle->get(MinIndex);
        FieldContainerUnrecPtr MaxIndexFC = TheHandle->get(MaxIndex);

        //Replace the MinIndex first
        UInt32 InitialSize(TheHandle->size());
        TheHandle->replace(MinIndex, MaxIndexFC);
        if(InitialSize != TheHandle->size())
        {
            TheHandle->insert(MaxIndex, MinIndexFC);
        }
        else
        {
            TheHandle->replace(MaxIndex, MinIndexFC);
        }
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _ToIndex);
        std::string ToValue = StrStream.str();

        //Get the from index value
        StrStream.clear();
        StrStream.str("");
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _FromIndex);
        std::string FromValue = StrStream.str();

        //Set the value
        TheFieldHandle->pushIndexedValueFromCString(ToValue.c_str(), _FromIndex);
        TheFieldHandle->pushIndexedValueFromCString(FromValue.c_str(), _ToIndex);
    }
}

void SwapFieldElementCommand::undo(void)
{
    Inherited::undo();

    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        UInt32 MinIndex(osgMin(_FromIndex,_ToIndex)), MaxIndex(osgMax(_FromIndex,_ToIndex));
        FieldContainerUnrecPtr MinIndexFC = TheHandle->get(MinIndex);
        FieldContainerUnrecPtr MaxIndexFC = TheHandle->get(MaxIndex);

        //Replace the MinIndex first
        UInt32 InitialSize(TheHandle->size());
        TheHandle->replace(MinIndex, MaxIndexFC);
        if(InitialSize != TheHandle->size())
        {
            TheHandle->insert(MaxIndex, MinIndexFC);
        }
        else
        {
            TheHandle->replace(MaxIndex, MinIndexFC);
        }
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _ToIndex);
        std::string ToValue = StrStream.str();

        //Get the from index value
        StrStream.clear();
        StrStream.str("");
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _FromIndex);
        std::string FromValue = StrStream.str();

        //Set the value
        TheFieldHandle->pushIndexedValueFromCString(ToValue.c_str(), _FromIndex);
        TheFieldHandle->pushIndexedValueFromCString(FromValue.c_str(), _ToIndex);
    }

}

const CommandType &SwapFieldElementCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SwapFieldElementCommand::~SwapFieldElementCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SwapFieldElementCommand::operator =(const SwapFieldElementCommand& source)
{
    assert("Should never reach operator=");
}

