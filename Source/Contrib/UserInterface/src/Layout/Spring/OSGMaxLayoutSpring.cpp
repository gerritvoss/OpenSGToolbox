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

#include "OSGMaxLayoutSpring.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMaxLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGMaxLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaxLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

MaxLayoutSpringTransitPtr MaxLayoutSpring::create(LayoutSpringRefPtr TheSpring1, LayoutSpringRefPtr TheSpring2)
{
    MaxLayoutSpring* NewSpring = createEmpty();

    NewSpring->setSpring1(TheSpring1);
    NewSpring->setSpring2(TheSpring2);

    return MaxLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 MaxLayoutSpring::operation(const Real32& Left, const Real32& Right) const
{
    return osgMax(Left, Right);
}

void MaxLayoutSpring::setNonClearValue(const Real32& value)
{
    Inherited::setNonClearValue(value);
    
    getSpring1()->setValue(value);

    getSpring2()->setValue(value);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MaxLayoutSpring::MaxLayoutSpring(void) :
    Inherited()
{
}

MaxLayoutSpring::MaxLayoutSpring(const MaxLayoutSpring &source) :
    Inherited(source)
{
}

MaxLayoutSpring::~MaxLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaxLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MaxLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MaxLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
