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

#include "OSGLayoutSpring.h"
#include "OSGStaticLayoutSpring.h"
#include "OSGSumLayoutSpring.h"
#include "OSGMaxLayoutSpring.h"
#include "OSGNegativeLayoutSpring.h"
#include "OSGScaleLayoutSpring.h"
#include "OSGComponentWidthLayoutSpring.h"
#include "OSGComponentHeightLayoutSpring.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Real32 LayoutSpring::VALUE_NOT_SET = TypeTraits< Real32 >::getMin();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 LayoutSpring::getStrain(void) const
{
    Real32 delta = (getValue() - getPreferredValue());
    return delta/range(getValue() < getPreferredValue());
}

void LayoutSpring::setStrain(Real32 strain)
{
    setValue(getPreferredValue() + static_cast<Real32>(strain * range(strain < 0)));
}

bool LayoutSpring::isCyclic(const SpringLayout* l) const
{
    return false;
}

Real32 LayoutSpring::range(bool contract) const
{
    if(contract)
    {
        return getPreferredValue() - getMinimumValue();
    }
    else
    {
        return getMaximumValue() - getPreferredValue();
    }
}

LayoutSpringRefPtr LayoutSpring::constant(const Real32& pref)
{
    return StaticLayoutSpring::create(pref);
}

LayoutSpringRefPtr LayoutSpring::constant(const Real32& min, const Real32& pref, const Real32& max)
{
    return StaticLayoutSpring::create(min, pref, max);
}

LayoutSpringRefPtr LayoutSpring::minus(LayoutSpringRefPtr s)
{
    return NegativeLayoutSpring::create(s);
}

LayoutSpringRefPtr LayoutSpring::sum(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2)
{
    return SumLayoutSpring::create(s1, s2);
}

LayoutSpringRefPtr LayoutSpring::max(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2)
{
    return MaxLayoutSpring::create(s1, s2);
}

LayoutSpringRefPtr LayoutSpring::difference(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2)
{
    return SumLayoutSpring::create(s1, minus(s2));
}

LayoutSpringRefPtr LayoutSpring::scale(LayoutSpringRefPtr s, const Real32& factor)
{
    return ScaleLayoutSpring::create(s, factor);
}

LayoutSpringRefPtr LayoutSpring::width(Component* const c)
{
    return ComponentWidthLayoutSpring::create(c);
}

LayoutSpringRefPtr LayoutSpring::height(Component* const c)
{
    return ComponentHeightLayoutSpring::create(c);
}

LayoutSpringRefPtr LayoutSpring::requestedWidth(Component* const c)
{
    return ComponentWidthLayoutSpring::create(c, ComponentWidthLayoutSpring::REQUESTED_SIZE);
}

LayoutSpringRefPtr LayoutSpring::requestedHeight(Component* const c)
{
    return ComponentHeightLayoutSpring::create(c, ComponentWidthLayoutSpring::REQUESTED_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LayoutSpring::LayoutSpring(void) :
    Inherited()
{
}

LayoutSpring::LayoutSpring(const LayoutSpring &source) :
    Inherited(source)
{
}

LayoutSpring::~LayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
