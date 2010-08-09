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

#include "OSGSetFieldValueCommand.h"
#include "OSGPointerSFieldBase.h"
#include "OSGFieldContainerSFieldHandle.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include "OSGFieldContainerFactory.h"
#include "OSGContainerUtils.h"
#include "OSGBaseFieldTraits.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SetFieldValueCommand
A SetFieldValueCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SetFieldValueCommand::_Type("SetFieldValueCommand", "FieldEditCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SetFieldValueCommandPtr SetFieldValueCommand::create(FieldContainer* FC, UInt32 FieldId, const std::string& Value, UInt32 Index)
{
	return RefPtr(new SetFieldValueCommand(FC, FieldId, Value, Index));
}

SetFieldValueCommandPtr SetFieldValueCommand::create(FieldContainer* FC, UInt32 FieldId, const std::string& Value,const std::string& PrevValue, UInt32 Index)
{
	return RefPtr(new SetFieldValueCommand(FC, FieldId, Value,PrevValue, Index));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SetFieldValueCommand::execute(void)
{
    //Check for a valid Field Container
    if(_FC == NULL)
    {
        SWARNING << "FieldContainer is NULL." << std::endl;
        return;
    }

    //Check for valid Field
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);
    if(!TheFieldHandle->isValid())
    {
        SWARNING << "No Field with Id: " << _FieldId << " in FieldContainers of type " << _FC->getType().getName() << std::endl;
        return;
    }

    //Check for valid indexing
    if(TheFieldHandle->getCardinality() == FieldType::SingleField && _Index != 0)
    {
        SWARNING << "Cannot reference index " << _Index << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field is a SingleField." << std::endl;
        return;
    }
    else if(TheFieldHandle->getCardinality() == FieldType::MultiField && _Index >= TheFieldHandle->size())
    {
        SWARNING << "Cannot set the value of index " << _Index << ", on field " << TheFieldHandle->getDescription()->getName() 
                 << ", on FieldContianer of type " << _FC->getType().getName()
                 << " because that field has size " << TheFieldHandle->size() << std::endl;
        return;
    }


    //Get the previous value
    if(_PrevValue.empty())
    {
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            if(TheFieldHandle->isPointerField())
            {
                _PrevPtrValue = dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get())->get();
                if(dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get())->get())
                {
                    _PrevValue = boost::lexical_cast<std::string>(dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get())->get()->getId());
                }
                else
                {
                    _PrevValue = "0";
                }
            }
            else
            {
                TheFieldHandle->pushValueToStream(TheOutStream);
                _PrevValue = StrStream.str();
            }
        }
        else
        {
            if(TheFieldHandle->isPointerField())
            {
                _PrevPtrValue = dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get())->get(_Index);
                if(_PrevPtrValue)
                {
                    _PrevValue = boost::lexical_cast<std::string>(dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get())->get(_Index)->getId());
                }
                else
                {
                    _PrevValue = "0";
                }
            }
            else
            {
                TheFieldHandle->pushIndexedValueToStream(TheOutStream, _Index);
                _PrevValue = StrStream.str();
            }
        }

        //Remove quotes from strings
        if(TheFieldHandle->getType().getContentType() == FieldTraits<std::string>::getType())
        {
            _PrevValue = _PrevValue.substr(1,StrStream.str().size()-2);
        }
    }

    //Set the value
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        if(TheFieldHandle->isPointerField())
        {
            _PtrValue = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
            
            //Check the pointer types match
            if(_PtrValue != NULL &&
                !isFieldContentDerivedFrom(TheFieldHandle->getType(),&_PtrValue->getType()))
            {
                SWARNING << "Cannot set the value of field " << TheFieldHandle->getDescription()->getName() 
                         << ", on FieldContianer of type " << _FC->getType().getName()
                         << " because the value attemting to be set is not derived from the type the field stores." << std::endl;
                return;
            }
            if(_PtrValue != _PrevPtrValue)
            {
                dynamic_cast<EditSFieldHandle<FieldContainerPtrSFieldBase>*>(_FC->editField(_FieldId).get())->set(_PtrValue);
            }
        }
        else
        {
            _FC->editField(_FieldId)->pushValueFromCString(_Value.c_str());
        }
    }
    else
    {
        if(TheFieldHandle->isPointerField())
        {
            _PtrValue = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
            
            //Check the pointer types match
            if(_PtrValue != NULL && !isFieldContentDerivedFrom(TheFieldHandle->getType(),&_PtrValue->getType()))
            {
                SWARNING << "Cannot set the value of field " << TheFieldHandle->getDescription()->getName() 
                         << ", on FieldContianer of type " << _FC->getType().getName()
                         << " because the value attemting to be set is not derived from the type the field stores." << std::endl;
                return;
            }
            if(_PtrValue != _PrevPtrValue)
            {
                dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(_FC->editField(_FieldId).get())->replace(_Index, _PtrValue);
            }
        }
        else
        {
            _FC->editField(_FieldId)->pushIndexedValueFromCString(_Value.c_str(), _Index);
        }
    }

    Inherited::execute();
	_HasBeenDone = true;
}

bool SetFieldValueCommand::isSignificant(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);
    if(TheFieldHandle->isPointerField())
    {
        return _PrevPtrValue != _PtrValue;
    }
    else
    {
        return _Value.compare(_PrevValue) != 0;
    }
}

bool SetFieldValueCommand::replaceEdit(const UndoableEditPtr anEdit) const
{
    dynamic_cast<const SetFieldValueCommand*>(anEdit.get());
    if(dynamic_cast<const SetFieldValueCommand*>(anEdit.get()))
    {
        const SetFieldValueCommand* otherEdit(dynamic_cast<const SetFieldValueCommand*>(anEdit.get()));
        const UndoableCommand* otherCommand(dynamic_cast<const UndoableCommand*>(anEdit.get()));
        return (otherEdit->_FC == _FC &&
                otherEdit->_FieldId == _FieldId &&
                otherEdit->_Index == _Index &&
                (::OSG::getSystemTime() - otherCommand->getTime() ) < getMaxReplaceTime());
    }

    return false;
}

bool SetFieldValueCommand::addEdit(const UndoableEditPtr anEdit)
{
    dynamic_cast<const SetFieldValueCommand*>(anEdit.get());
    if(dynamic_cast<const SetFieldValueCommand*>(anEdit.get()))
    {
        const SetFieldValueCommand* otherEdit(dynamic_cast<const SetFieldValueCommand*>(anEdit.get()));
        if(otherEdit->_FC == _FC &&
           otherEdit->_FieldId == _FieldId &&
           otherEdit->_Index == _Index &&
           (otherEdit->getTime() - getTime()) < getMaxReplaceTime())
        {
            _Value = otherEdit->_Value;
            _PtrValue = otherEdit->_PtrValue;
            _ExecuteTime = otherEdit->_ExecuteTime;
            return true;
        }
    }

    return false;
}

std::string SetFieldValueCommand::getCommandDescription(void) const
{
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);

	std::string Description("");

    Description = Description + "Set " + TheFieldHandle->getDescription()->getName() + " to " + _Value;
	
	return Description;
}

std::string SetFieldValueCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void SetFieldValueCommand::redo(void)
{
    Inherited::redo();

    //Set the value
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);
    //Set the value
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        if(TheFieldHandle->isPointerField())
        {
            FieldContainer* FC = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
            dynamic_cast<EditSFieldHandle<FieldContainerPtrSFieldBase>*>(_FC->editField(_FieldId).get())->set(FC);
        }
        else
        {
            _FC->editField(_FieldId)->pushValueFromCString(_Value.c_str());
        }
    }
    else
    {
        if(TheFieldHandle->isPointerField())
        {
            FieldContainer* FC = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_Value));
            dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(_FC->editField(_FieldId).get())->replace(_Index, FC);
        }
        else
        {
            _FC->editField(_FieldId)->pushIndexedValueFromCString(_Value.c_str(), _Index);
        }
    }
}

void SetFieldValueCommand::undo(void)
{
    Inherited::undo();

    //reset the value
    GetFieldHandlePtr TheFieldHandle = _FC->getField(_FieldId);
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        if(TheFieldHandle->isPointerField())
        {
            FieldContainer* FC = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_PrevValue));
            dynamic_cast<EditSFieldHandle<FieldContainerPtrSFieldBase>*>(_FC->editField(_FieldId).get())->set(FC);
        }
        else
        {
            _FC->editField(_FieldId)->pushValueFromCString(_PrevValue.c_str());
        }
    }
    else
    {
        if(TheFieldHandle->isPointerField())
        {
            FieldContainer* FC = FieldContainerFactory::the()->getContainer(boost::lexical_cast<UInt32>(_PrevValue));
            dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(_FC->editField(_FieldId).get())->replace(_Index, FC);
        }
        else
        {
            _FC->editField(_FieldId)->pushIndexedValueFromCString(_PrevValue.c_str(), _Index);
        }
    }
}

const CommandType &SetFieldValueCommand::getType(void) const
{
	return _Type;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SetFieldValueCommand::~SetFieldValueCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SetFieldValueCommand::operator =(const SetFieldValueCommand& source)
{
    assert("Should never reach operator=");
}

