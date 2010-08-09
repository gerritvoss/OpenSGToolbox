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

#include "OSGMoveFieldElementCommand.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MoveFieldElementCommand
A MoveFieldElementCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType MoveFieldElementCommand::_Type("MoveFieldElementCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

MoveFieldElementCommandPtr MoveFieldElementCommand::create(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex)
{
	return RefPtr(new MoveFieldElementCommand(FC, FieldId, FromIndex, ToIndex));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MoveFieldElementCommand::execute(void)
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
    if(TheFieldHandle->getCardinality() == FieldType::MultiField && _ToIndex > TheFieldHandle->size())
    {
        SWARNING << "Cannot move the value of to index " << _ToIndex << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }

    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        FieldContainerUnrecPtr ToFC = TheHandle->get(_FromIndex);
        TheHandle->remove(_FromIndex);
        TheHandle->insert(_ToIndex, ToFC);
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        //Get the from index value
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _FromIndex);
        std::string FromValue = StrStream.str();

        //Set the value
        TheFieldHandle->insertIndexedValueFromCString(FromValue.c_str(), _ToIndex);
        if(_ToIndex < _FromIndex)
        {
            TheFieldHandle->removeIndex(_FromIndex + 1);
        }
        else
        {
            TheFieldHandle->removeIndex(_FromIndex);
        }
    }

    Inherited::execute();
	_HasBeenDone = true;
}

std::string MoveFieldElementCommand::getCommandDescription(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);

	std::string Description("");

    Description = Description 
                + "Move " + TheFieldHandle->getDescription()->getName()
                + " index " + boost::lexical_cast<std::string>(_FromIndex) 
                + " to index " + boost::lexical_cast<std::string>(_ToIndex);
	
	return Description;
}

std::string MoveFieldElementCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void MoveFieldElementCommand::redo(void)
{
    Inherited::redo();

    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        FieldContainerUnrecPtr ToFC = TheHandle->get(_FromIndex);
        TheHandle->remove(_FromIndex);
        TheHandle->insert(_ToIndex, ToFC);
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        //Get the from index value
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _FromIndex);
        std::string FromValue = StrStream.str();

        //Set the value
        TheFieldHandle->insertIndexedValueFromCString(FromValue.c_str(), _ToIndex);
        if(_ToIndex < _FromIndex)
        {
            TheFieldHandle->removeIndex(_FromIndex + 1);
        }
        else
        {
            TheFieldHandle->removeIndex(_FromIndex);
        }
    }
}

void MoveFieldElementCommand::undo(void)
{
    Inherited::undo();

    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        FieldContainerUnrecPtr ToFC = TheHandle->get(_ToIndex);
        TheHandle->remove(_ToIndex);
        TheHandle->insert(_FromIndex, ToFC);
    }
    else
    {
        //Get the to index value
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);

        //Set the value
        if(_ToIndex < _FromIndex)
        {
            TheFieldHandle->pushIndexedValueToStream(TheOutStream, _ToIndex);
            TheFieldHandle->insertIndexedValueFromCString(StrStream.str().c_str(), _FromIndex+1);
        }
        else
        {
            TheFieldHandle->pushIndexedValueToStream(TheOutStream, _ToIndex-1);
            TheFieldHandle->insertIndexedValueFromCString(StrStream.str().c_str(), _FromIndex);
        }
        TheFieldHandle->removeIndex(_ToIndex);
    }

}

const CommandType &MoveFieldElementCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MoveFieldElementCommand::~MoveFieldElementCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MoveFieldElementCommand::operator =(const MoveFieldElementCommand& source)
{
    assert("Should never reach operator=");
}

