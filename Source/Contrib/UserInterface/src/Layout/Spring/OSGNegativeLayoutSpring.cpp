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

#include "OSGNegativeLayoutSpring.h"
#include "OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNegativeLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGNegativeLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NegativeLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

NegativeLayoutSpringTransitPtr NegativeLayoutSpring::create(LayoutSpringRefPtr TheSpring)
{
    NegativeLayoutSpring* NewSpring = createEmpty();

    NewSpring->setSpring(TheSpring);

    return NegativeLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 NegativeLayoutSpring::getMinimumValue(void) const
{
    return -getSpring()->getMaximumValue();
}

Real32 NegativeLayoutSpring::getPreferredValue(void) const
{
    return -getSpring()->getPreferredValue();
}

Real32 NegativeLayoutSpring::getMaximumValue(void) const
{
    return -getSpring()->getMinimumValue();
}

Real32 NegativeLayoutSpring::getValue(void) const
{
    return -getSpring()->getValue();
}

void NegativeLayoutSpring::setValue(const Real32& value)
{
    if(value == LayoutSpring::VALUE_NOT_SET)
    {
        getSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    else
    {
        getSpring()->setValue(-value);
    }
}

bool NegativeLayoutSpring::isCyclic(const SpringLayout* l) const
{
    return getSpring()->isCyclic(l);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NegativeLayoutSpring::NegativeLayoutSpring(void) :
    Inherited()
{
}

NegativeLayoutSpring::NegativeLayoutSpring(const NegativeLayoutSpring &source) :
    Inherited(source)
{
}

NegativeLayoutSpring::~NegativeLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NegativeLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void NegativeLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump NegativeLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
