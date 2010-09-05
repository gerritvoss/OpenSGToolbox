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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>
#include <boost/bind.hpp>

#include "OSGFieldEditorComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldEditorComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldEditorComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldEditorComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool FieldEditorComponent::attachField(FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    //Cancel current editing
    cancelEditing();

    //Check that this is a valid FieldContainer
    if(fc == NULL)
    {
        SWARNING << "Cannot attach to a Null FieldContainer." << std::endl;
        return false;
    }

    //Check that this is a valid FieldId
    const FieldDescriptionBase* Desc(fc->getFieldDescription(fieldId));
    if(Desc == NULL)
    {
        SWARNING << "Cannot attach to field with id " << fieldId
                 << ", on a FieldContainer with type " << fc->getType().getCName()
                 << " because that is an invalid field id." << std::endl;
        return false;
    }
    //Check that this is a type to edit for this editor
    if(!isTypeEditable(Desc->getFieldType().getContentType()))
    {
        SWARNING << " Cannot attach to field " << Desc->getCName() 
                 << ", with content type " << Desc->getFieldType().getContentType().getCName()
                 << " because that content type is not supported by this editor type." << std::endl;
        return false;
    }

    //Check that this is a valid index
    GetFieldHandlePtr TheFieldHandle = fc->getField(fieldId);
    if(!TheFieldHandle.get())
    {
        SWARNING << "Cannot attach to field " << Desc->getCName() 
                 << ", on a FieldContainer with type " << fc->getType().getCName()
                 << " because no GetFieldHandle is defined for that field type." << std::endl;
        return false;
    }

    if(!internalAttachField(fc, fieldId, index))
    {
        return false;
    }

    //Attach to the field
    setEditingFC(fc);
    setEditingFieldId(fieldId);

    //Tell the Editor that the field has changed
    fieldChanged(fc, Desc->getFieldMask());

    //Attach to the Changed function callback for the container
    attachFieldCallback();

    return true;
}

bool FieldEditorComponent::dettachField(void)
{
    //Cancel current editing
    cancelEditing();

    //Dettach from the field
    setEditingFC(NULL);
    setEditingFieldId(0);

    //Dettach from the Changed function callback for the container
    dettachFieldCallback();

    return internalDettachField();
}

bool FieldEditorComponent::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    return true;
}

bool FieldEditorComponent::internalDettachField(void)
{
    return true;
}

void FieldEditorComponent::fieldChanged(FieldContainer *fc, ConstFieldMaskArg whichField)
{
    if(fc == getEditingFC() &&
       (whichField & getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldMask()))
    {
        internalFieldChanged();
    }
}

void FieldEditorComponent::startEditing (void)
{
    if(!_isEditing)
    {
        _isEditing = true;
        dettachFieldCallback();
        internalStartEditing();
    }
}

void FieldEditorComponent::stopEditing  (void)
{
    if(_isEditing)
    {
        _isEditing = false;
        attachFieldCallback();
        internalStopEditing();
    }
}

void FieldEditorComponent::cancelEditing(void)
{
    if(_isEditing)
    {
        _isEditing = false;
        attachFieldCallback();
        internalCancelEditing();
    }
}

bool FieldEditorComponent::isEditing(void) const
{
    return _isEditing;
}

bool FieldEditorComponent::isTypeEditable(const DataType& type) const
{
    const std::vector<const DataType*>& TypeVec(getEditableTypes());
    for(UInt32 i(0) ; i<TypeVec.size() ; ++i)
    {
        if((*TypeVec[i]) == type)
        {
            return true;
        }
    }
    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void FieldEditorComponent::resolveLinks(void)
{
    dettachFieldCallback();

    Inherited::resolveLinks();
}

/*----------------------- constructors & destructors ----------------------*/

FieldEditorComponent::FieldEditorComponent(void) :
    Inherited()
{
}

FieldEditorComponent::FieldEditorComponent(const FieldEditorComponent &source) :
    Inherited(source),
    _CmdManager(source._CmdManager)
{
}

FieldEditorComponent::~FieldEditorComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldEditorComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FieldEditorComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FieldEditorComponent NI" << std::endl;
}

OSG_END_NAMESPACE
