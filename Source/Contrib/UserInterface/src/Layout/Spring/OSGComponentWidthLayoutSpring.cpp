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

#include "OSGComponentWidthLayoutSpring.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComponentWidthLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentWidthLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentWidthLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ComponentWidthLayoutSpringTransitPtr ComponentWidthLayoutSpring::create (Component* const TheComponent, UInt32 SizeField)
{
    ComponentWidthLayoutSpring* NewSpring = createEmpty();

    NewSpring->setComponent(TheComponent);
    NewSpring->setSizeField(SizeField);

    return ComponentWidthLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 ComponentWidthLayoutSpring::getMinimumValue(void) const
{
    return getComponent()->getMinSize().x();
}

Real32 ComponentWidthLayoutSpring::getPreferredValue(void) const
{
    switch(getSizeField())
    {
    case ComponentWidthLayoutSpring::MINIMUM_SIZE:
        return getComponent()->getMinSize().x();
        break;
    case ComponentWidthLayoutSpring::MAXIMUM_SIZE:
        return getComponent()->getMaxSize().x();
        break;
    case ComponentWidthLayoutSpring::REQUESTED_SIZE:
        return getComponent()->getRequestedSize().x();
        break;
    case ComponentWidthLayoutSpring::SIZE:
        return getComponent()->getSize().x();
        break;
    case ComponentWidthLayoutSpring::PREFERRED_SIZE:
    default:
        return getComponent()->getPreferredSize().x();
        break;
    }
}

Real32 ComponentWidthLayoutSpring::getMaximumValue(void) const
{
    return osgMin<Real32>(TypeTraits< Real32 >::getMax(), getComponent()->getMaxSize().x());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComponentWidthLayoutSpring::ComponentWidthLayoutSpring(void) :
    Inherited()
{
}

ComponentWidthLayoutSpring::ComponentWidthLayoutSpring(const ComponentWidthLayoutSpring &source) :
    Inherited(source)
{
}

ComponentWidthLayoutSpring::~ComponentWidthLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentWidthLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ComponentWidthLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComponentWidthLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
