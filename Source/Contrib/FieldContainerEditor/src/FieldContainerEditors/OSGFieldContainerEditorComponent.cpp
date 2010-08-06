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

#include "OSGFieldContainerEditorComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFieldContainerEditorComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGFieldContainerEditorComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerEditorComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool FieldContainerEditorComponent::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(fc == NULL)
    {
        SWARNING << "Cannot attach to a Null FieldContainer." << std::endl;
        return false;
    }

    dettachFieldContainer();

    setEditingFC(fc);

    return true;
}

bool FieldContainerEditorComponent::dettachFieldContainer(void)
{
    return true;
}

bool FieldContainerEditorComponent::isTypeEditable(const FieldContainerType& type) const
{
    const std::vector<const FieldContainerType*>& TypeVec(getEditableTypes());
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

/*----------------------- constructors & destructors ----------------------*/

FieldContainerEditorComponent::FieldContainerEditorComponent(void) :
    Inherited()
{
}

FieldContainerEditorComponent::FieldContainerEditorComponent(const FieldContainerEditorComponent &source) :
    Inherited(source)
{
}

FieldContainerEditorComponent::~FieldContainerEditorComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldContainerEditorComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FieldContainerEditorComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerEditorComponent NI" << std::endl;
}

OSG_END_NAMESPACE
