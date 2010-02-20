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

#include "OSGScaleLayoutSpring.h"
#include "OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScaleLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGScaleLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScaleLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ScaleLayoutSpringTransitPtr ScaleLayoutSpring::create(LayoutSpringRefPtr TheSpring, Real32 Factor)
{
    ScaleLayoutSpring* NewSpring = createEmpty();

    NewSpring->setSpring(TheSpring);
    NewSpring->setFactor(Factor);

    return ScaleLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 ScaleLayoutSpring::getMinimumValue(void) const
{
    if(getFactor() < 0.0f)
    {
        return getSpring()->getMinimumValue();
    }
    else
    {
        return static_cast<Real32>(osgFloor(getFactor() * static_cast<Real32>(getSpring()->getMinimumValue())));
    }
}

Real32 ScaleLayoutSpring::getPreferredValue(void) const
{
    return static_cast<Real32>(osgFloor(getFactor() * static_cast<Real32>(getSpring()->getPreferredValue())));
}

Real32 ScaleLayoutSpring::getMaximumValue(void) const
{
    if(getFactor() < 0.0f)
    {
        return getSpring()->getMaximumValue();
    }
    else
    {
        return static_cast<Real32>(osgFloor(getFactor() * static_cast<Real32>(getSpring()->getMaximumValue())));
    }
}

Real32 ScaleLayoutSpring::getValue(void) const
{
    return static_cast<Real32>(osgFloor(getFactor() * static_cast<Real32>(getSpring()->getValue())));
}

void ScaleLayoutSpring::setValue(const Real32& value)
{
    if(value == LayoutSpring::VALUE_NOT_SET)
    {
        getSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    else
    {
        getSpring()->setValue(osgFloor(static_cast<Real32>(getSpring()->getValue()) / getFactor()));
    }
}

bool ScaleLayoutSpring::isCyclic(const SpringLayout* l) const
{
    return getSpring()->isCyclic(l);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScaleLayoutSpring::ScaleLayoutSpring(void) :
    Inherited()
{
}

ScaleLayoutSpring::ScaleLayoutSpring(const ScaleLayoutSpring &source) :
    Inherited(source)
{
}

ScaleLayoutSpring::~ScaleLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScaleLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ScaleLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScaleLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
