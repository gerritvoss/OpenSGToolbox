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

#include "OSGAbstractLayoutSpring.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 AbstractLayoutSpring::getValue(void) const
{
    if(getSize() == LayoutSpring::VALUE_NOT_SET)
    {
        return getPreferredValue();
    }
    else
    {
        return getSize();
    }
}

void AbstractLayoutSpring::setValue(const Real32& value)
{
    if (getValue() == value)
    {
        return;
    }
    if (value == LayoutSpring::VALUE_NOT_SET)
    {
        clear();
    }
    else
    {
        setNonClearValue(value);
    }
}

void AbstractLayoutSpring::clear(void)
{
    setSize(LayoutSpring::VALUE_NOT_SET);
}

void AbstractLayoutSpring::setNonClearValue(const Real32& value)
{
    setSize(value);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractLayoutSpring::AbstractLayoutSpring(void) :
    Inherited()
{
}

AbstractLayoutSpring::AbstractLayoutSpring(const AbstractLayoutSpring &source) :
    Inherited(source)
{
}

AbstractLayoutSpring::~AbstractLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
