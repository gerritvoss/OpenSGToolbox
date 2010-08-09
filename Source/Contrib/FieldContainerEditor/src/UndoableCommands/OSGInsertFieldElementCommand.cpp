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

#include "OSGInsertFieldElementCommand.h"
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

/*! \class OSG::InsertFieldElementCommand
A InsertFieldElementCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType InsertFieldElementCommand::_Type("InsertFieldElementCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

InsertFieldElementCommandPtr InsertFieldElementCommand::create(FieldContainer* FC, UInt32 FieldId, const std::string& Value, UInt32 Index)
{
	return RefPtr(new InsertFieldElementCommand(FC, FieldId, Value, Index));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void InsertFieldElementCommand::execute(void)
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
    if(TheFieldHandle->getCardinality() == FieldType::MultiField && _Index > TheFieldHandle->size())
    {
        SWARNING << "Cannot insert the value " << _Value << " at index " << _Index << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }
        
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        _InsertedPtr = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
        //Check the pointer types match
        if(_InsertedPtr != NULL && !isFieldContentDerivedFrom(TheFieldHandle->getType(),&_InsertedPtr->getType()))
        {
            SWARNING << "Cannot insert the value of field " << TheFieldHandle->getDescription()->getName() 
                     << ", on FieldContianer of type " << _FC->getType().getName()
                     << " because the value attemting to be set is not derived from the type the field stores." << std::endl;
            return;
        }

        TheHandle->insert(_Index, _InsertedPtr);
    }
    else
    {
        TheFieldHandle->insertIndexedValueFromCString(_Value.c_str(), _Index);
    }

    Inherited::execute();
	_HasBeenDone = true;
}

std::string InsertFieldElementCommand::getCommandDescription(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);

	std::string Description("");

    Description = Description + "Insert " + _Value + " to " + TheFieldHandle->getDescription()->getName() + " at index " + boost::lexical_cast<std::string>(_Index);
	
	return Description;
}

std::string InsertFieldElementCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void InsertFieldElementCommand::redo(void)
{
    Inherited::redo();

    //Set the value
    EditFieldHandlePtr TheFieldHandle = _FC->editField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

        TheHandle->insert(_Index, _InsertedPtr);
    }
    else
    {
        TheFieldHandle->insertIndexedValueFromCString(_Value.c_str(), _Index);
    }
}

void InsertFieldElementCommand::undo(void)
{
    Inherited::undo();

    //Remove the element that was inserted
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

const CommandType &InsertFieldElementCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InsertFieldElementCommand::~InsertFieldElementCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InsertFieldElementCommand::operator =(const InsertFieldElementCommand& source)
{
    assert("Should never reach operator=");
}

