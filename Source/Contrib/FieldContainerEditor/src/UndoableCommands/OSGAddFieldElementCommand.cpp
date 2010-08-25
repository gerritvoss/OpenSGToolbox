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

#include "OSGAddFieldElementCommand.h"
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

/*! \class OSG::AddFieldElementCommand
A AddFieldElementCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType AddFieldElementCommand::_Type("AddFieldElementCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

AddFieldElementCommandPtr AddFieldElementCommand::create(FieldContainer* FC, UInt32 FieldId, const std::string& Value)
{
	return RefPtr(new AddFieldElementCommand(FC, FieldId, Value));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AddFieldElementCommand::execute(void)
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
        
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        _AddedPtr = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
        //Check the pointer types match
        if(_AddedPtr != NULL && !isFieldContentDerivedFrom(TheFieldHandle->getType(),&_AddedPtr->getType()))
        {
            SWARNING << "Cannot add the value of field " << TheFieldHandle->getDescription()->getName() 
                     << ", on FieldContianer of type " << _FC->getType().getName()
                     << " because the value attemting to be set is not derived from the type the field stores." << std::endl;
            return;
        }

        TheHandle->add(_AddedPtr);
    }
    else
    {
        TheFieldHandle->pushValueFromCString(_Value.c_str());
    }

    Inherited::execute();
	_HasBeenDone = true;
}

std::string AddFieldElementCommand::getCommandDescription(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);

	std::string Description("");

    Description = Description + "Add " + _Value + " to " + TheFieldHandle->getDescription()->getName();
	
	return Description;
}

std::string AddFieldElementCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void AddFieldElementCommand::redo(void)
{
    Inherited::redo();

    //Set the value
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId); 
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        TheHandle->add(_AddedPtr);
    }
    else
    {
        TheFieldHandle->pushValueFromCString(_Value.c_str());
    }
}

void AddFieldElementCommand::undo(void)
{
    Inherited::undo();

    //Pop off the back element
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId); 
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        TheHandle->remove(TheHandle->size()-1);
    }
    else
    {
        TheFieldHandle->removeIndex(TheFieldHandle->size()-1);
    }
}

const CommandType &AddFieldElementCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AddFieldElementCommand::~AddFieldElementCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AddFieldElementCommand::operator =(const AddFieldElementCommand& source)
{
    assert("Should never reach operator=");
}

