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

#include "OSGStaticLayoutSpring.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStaticLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGStaticLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StaticLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

StaticLayoutSpringTransitPtr StaticLayoutSpring::create (const Real32& Preferred)
{
    StaticLayoutSpring* NewSpring = createEmpty();

        NewSpring->setPreferred(Preferred);

    return StaticLayoutSpringTransitPtr(NewSpring);
}

StaticLayoutSpringTransitPtr StaticLayoutSpring::create (const Real32& Minimum, const Real32& Preferred, const Real32& Maximum)
{
    StaticLayoutSpring* NewSpring = createEmpty();

        NewSpring->setMinimum(Minimum);
        NewSpring->setPreferred(Preferred);
        NewSpring->setMaximum(Maximum);

    return StaticLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 StaticLayoutSpring::getMinimumValue(void) const
{
    return getMinimum();
}

Real32 StaticLayoutSpring::getPreferredValue(void) const
{
    return getPreferred();
}

Real32 StaticLayoutSpring::getMaximumValue(void) const
{
    return getMaximum();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StaticLayoutSpring::StaticLayoutSpring(void) :
    Inherited()
{
}

StaticLayoutSpring::StaticLayoutSpring(const StaticLayoutSpring &source) :
    Inherited(source)
{
}

StaticLayoutSpring::~StaticLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StaticLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void StaticLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StaticLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
