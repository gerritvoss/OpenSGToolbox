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

#define KE_COMPILEKABALAENGINELIB

#include "OSGConfig.h"

#include "OSGRemoveFieldElementCommand.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include "OSGFieldContainerFactory.h"
#include "OSGContainerUtils.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::RemoveFieldElementCommand
A RemoveFieldElementCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType RemoveFieldElementCommand::_Type("RemoveFieldElementCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

RemoveFieldElementCommandPtr RemoveFieldElementCommand::create(FieldContainer* FC, UInt32 FieldId, UInt32 Index)
{
	return RefPtr(new RemoveFieldElementCommand(FC, FieldId, Index));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RemoveFieldElementCommand::execute(void)
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
    if(TheFieldHandle->getCardinality() == FieldType::MultiField && _Index >= TheFieldHandle->size())
    {
        SWARNING << "Cannot remove at index " << _Index << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }
        
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        _RemovedPtr = TheHandle->get(_Index);
        
        //Get the previous value
        _RemovedValue = boost::lexical_cast<std::string>(TheHandle->get(_Index)->getId());

        TheHandle->remove(_Index);
    }
    else
    {
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);
        TheFieldHandle->pushIndexedValueToStream(TheOutStream, _Index);
        _RemovedValue = StrStream.str();

        TheFieldHandle->removeIndex(_Index);
    }

    Inherited::execute();
	_HasBeenDone = true;
}

std::string RemoveFieldElementCommand::getCommandDescription(void) const
{
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);

	std::string Description("");

    Description = Description + "Remove index " + boost::lexical_cast<std::string>(_Index) + " of " + TheFieldHandle->getDescription()->getName();
	
	return Description;
}

std::string RemoveFieldElementCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void RemoveFieldElementCommand::redo(void)
{
    Inherited::redo();

    //Remove the index
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId); 
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        TheHandle->remove(_Index);
    }
    else
    {
        TheFieldHandle->removeIndex(_Index);
    }
}

void RemoveFieldElementCommand::undo(void)
{
    Inherited::undo();

    //Insert the removed element
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId); 
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        TheHandle->insert(_Index, _RemovedPtr);
    }
    else
    {
        TheFieldHandle->insertIndexedValueFromCString(_RemovedValue.c_str(), _Index);
    }
}

const CommandType &RemoveFieldElementCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RemoveFieldElementCommand::~RemoveFieldElementCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RemoveFieldElementCommand::operator =(const RemoveFieldElementCommand& source)
{
    assert("Should never reach operator=");
}

