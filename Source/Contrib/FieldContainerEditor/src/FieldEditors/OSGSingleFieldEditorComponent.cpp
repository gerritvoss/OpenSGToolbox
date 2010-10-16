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

#include "OSGSingleFieldEditorComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSingleFieldEditorComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGSingleFieldEditorComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SingleFieldEditorComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool SingleFieldEditorComponent::internalAttachField(FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    GetFieldHandlePtr TheFieldHandle = fc->getField(fieldId);
    if(TheFieldHandle->getCardinality() != FieldType::MultiField &&
       index != 0)
    {
        SWARNING << "Cannot attach to index " << index 
                 <<", of field " << TheFieldHandle->getDescription()->getName() 
                 << ", on a FieldContainer with type " << fc->getType().getCName() << " because that is not a multi-field." << std::endl;
        return false;
    }
    if(TheFieldHandle->size() <= index)
    {
        SWARNING << "Cannot attach to index " << index 
                 <<", of field " << TheFieldHandle->getDescription()->getName() 
                 << ", on a FieldContainer with type " << fc->getType().getCName() << " because that index is out of bounds." << std::endl;
        return false;
    }

    setEditingFieldIndex(index);

    return true;
}

bool SingleFieldEditorComponent::internalDettachField(void)
{
    setEditingFieldIndex(0);

    return true;
}

UInt32 SingleFieldEditorComponent::getNumRequestedRows(void) const
{
    return 1;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SingleFieldEditorComponent::SingleFieldEditorComponent(void) :
    Inherited()
{
}

SingleFieldEditorComponent::SingleFieldEditorComponent(const SingleFieldEditorComponent &source) :
    Inherited(source)
{
}

SingleFieldEditorComponent::~SingleFieldEditorComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SingleFieldEditorComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SingleFieldEditorComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SingleFieldEditorComponent NI" << std::endl;
}

OSG_END_NAMESPACE
