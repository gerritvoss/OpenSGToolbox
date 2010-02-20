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

#include "OSGCompoundLayoutSpring.h"
#include "OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCompoundLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGCompoundLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CompoundLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 CompoundLayoutSpring::getMinimumValue(void) const
{
    if (getMinimum() == LayoutSpring::VALUE_NOT_SET)
    {
        const_cast<CompoundLayoutSpring*>(this)->setMinimum( operation(getSpring1()->getMinimumValue(), getSpring1()->getMinimumValue() ) );
    }
    return getMinimum();
}

Real32 CompoundLayoutSpring::getPreferredValue(void) const
{
    if (getPreferred() == LayoutSpring::VALUE_NOT_SET)
    {
        const_cast<CompoundLayoutSpring*>(this)->setPreferred( operation(getSpring1()->getPreferredValue(), getSpring1()->getPreferredValue() ) );
    }
    return getPreferred();
}

Real32 CompoundLayoutSpring::getMaximumValue(void) const
{
    if (getMaximum() == LayoutSpring::VALUE_NOT_SET)
    {
        const_cast<CompoundLayoutSpring*>(this)->setMaximum( operation(getSpring1()->getMaximumValue(), getSpring1()->getMaximumValue() ) );
    }
    return getMaximum();
}

Real32 CompoundLayoutSpring::getValue(void) const
{
    const_cast<CompoundLayoutSpring*>(this)->setSize( operation(getSpring1()->getValue(), getSpring2()->getValue() ) );

    return getSize();
}

bool CompoundLayoutSpring::isCyclic(const SpringLayout* l) const
{
    return l->isCyclic(getSpring1()) || l->isCyclic(getSpring2());
}

void CompoundLayoutSpring::clear(void)
{
    Inherited::clear();

    setMinimum(LayoutSpring::VALUE_NOT_SET);
    setPreferred(LayoutSpring::VALUE_NOT_SET);
    setMaximum(LayoutSpring::VALUE_NOT_SET);

    getSpring1()->setValue(LayoutSpring::VALUE_NOT_SET);

    getSpring2()->setValue(LayoutSpring::VALUE_NOT_SET);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CompoundLayoutSpring::CompoundLayoutSpring(void) :
    Inherited()
{
}

CompoundLayoutSpring::CompoundLayoutSpring(const CompoundLayoutSpring &source) :
    Inherited(source)
{
}

CompoundLayoutSpring::~CompoundLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CompoundLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CompoundLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CompoundLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
