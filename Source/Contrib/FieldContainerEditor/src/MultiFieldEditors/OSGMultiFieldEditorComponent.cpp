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

#include "OSGMultiFieldEditorComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiFieldEditorComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiFieldEditorComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiFieldEditorComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
//bool MultiFieldEditorComponent::attachField(FieldContainer* fc, UInt32 fieldId)
//{
    ////Cancel current editing
    //cancelEditing();

    ////Check that this is a valid FieldContainer
    //if(fc == NULL)
    //{
        //SWARNING << "Cannot attach to a Null FieldContainer." << std::endl;
        //return false;
    //}

    ////Check that this is a valid FieldId
    //const FieldDescriptionBase* Desc(fc->getFieldDescription(fieldId));
    //if(Desc == NULL)
    //{
        //SWARNING << "Cannot attach to field with id" << fieldId << ", on a FieldContainer with type " << fc->getType().getCName() << " because that is an invalid field id." << std::endl;
        //return false;
    //}
    ////Check that this is a type to edit for this editor
    //if(!isTypeEditable(Desc->getFieldType().getContentType()))
    //{
        //SWARNING << " Cannot attach to field " << Desc->getCName() 
                 //<< ", with content type " << Desc->getFieldType().getContentType().getCName()
                 //<< " because that content type is not supported by this editor type." << std::endl;
        //return false;
    //}

    ////Check that there is a getFieldHandle on this field
    //GetFieldHandlePtr TheFieldHandle = fc->getField(fieldId);
    //if(!TheFieldHandle.get())
    //{
        //SWARNING << "Cannot attach to field " << Desc->getCName() 
                 //<< ", on a FieldContainer with type " << fc->getType().getCName() << " because no GetFieldHandle is defined for that field type." << std::endl;
        //return false;
    //}

    ////Check that this is a MultiField
    //if(TheFieldHandle->getCardinality() != FieldType::MultiField)
    //{
        //SWARNING << "Cannot attach to field with id" << fieldId 
                 //<< ", on a FieldContainer with type " << fc->getType().getCName() << " because that is not a multi-field." << std::endl;
        //return false;
    //}

    //if(!internalAttachField(fc, fieldId))
    //{
        //return false;
    //}

    ////Attach to the field
    //setEditingFC(fc);
    //setEditingFieldId(fieldId);

    ////Tell the Editor that the field has changed
    //fieldChanged(fc, Desc->getFieldMask());

    ////Attach to the Changed function callback for the container
    //attachFieldCallback();

    //return true;
//}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiFieldEditorComponent::MultiFieldEditorComponent(void) :
    Inherited()
{
}

MultiFieldEditorComponent::MultiFieldEditorComponent(const MultiFieldEditorComponent &source) :
    Inherited(source)
{
}

MultiFieldEditorComponent::~MultiFieldEditorComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiFieldEditorComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MultiFieldEditorComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiFieldEditorComponent NI" << std::endl;
}

OSG_END_NAMESPACE
