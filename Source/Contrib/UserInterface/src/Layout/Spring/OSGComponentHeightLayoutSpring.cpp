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

#include "OSGComponentHeightLayoutSpring.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComponentHeightLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGComponentHeightLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentHeightLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ComponentHeightLayoutSpringTransitPtr ComponentHeightLayoutSpring::create (Component* const TheComponent, UInt32 SizeField)
{
    ComponentHeightLayoutSpring* NewSpring = createEmpty();

    NewSpring->setComponent(TheComponent);
    NewSpring->setSizeField(SizeField);

    return ComponentHeightLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 ComponentHeightLayoutSpring::getMinimumValue(void) const
{
    return getComponent()->getMinSize().y();
}

Real32 ComponentHeightLayoutSpring::getPreferredValue(void) const
{
    switch(getSizeField())
    {
    case ComponentHeightLayoutSpring::MINIMUM_SIZE:
        return getComponent()->getMinSize().y();
        break;
    case ComponentHeightLayoutSpring::MAXIMUM_SIZE:
        return getComponent()->getMaxSize().y();
        break;
    case ComponentHeightLayoutSpring::REQUESTED_SIZE:
        return getComponent()->getRequestedSize().y();
        break;
    case ComponentHeightLayoutSpring::SIZE:
        return getComponent()->getSize().y();
        break;
    case ComponentHeightLayoutSpring::PREFERRED_SIZE:
    default:
        return getComponent()->getPreferredSize().y();
        break;
    }
}

Real32 ComponentHeightLayoutSpring::getMaximumValue(void) const
{
    return osgMin<Real32>(TypeTraits< Real32 >::getMax(), getComponent()->getMaxSize().y());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComponentHeightLayoutSpring::ComponentHeightLayoutSpring(void) :
    Inherited()
{
}

ComponentHeightLayoutSpring::ComponentHeightLayoutSpring(const ComponentHeightLayoutSpring &source) :
    Inherited(source)
{
}

ComponentHeightLayoutSpring::~ComponentHeightLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentHeightLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ComponentHeightLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComponentHeightLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
