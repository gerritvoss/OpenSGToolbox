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

#include "OSGProxyLayoutSpring.h"
#include "OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGProxyLayoutSpringBase.cpp file.
// To modify it, please change the .fcd file (OSGProxyLayoutSpring.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProxyLayoutSpring::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ProxyLayoutSpringTransitPtr ProxyLayoutSpring::create (const UInt32& Edge, 
                                                       Component* TheComponent,
                                                       SpringLayout* TheLayout)
{
    ProxyLayoutSpring* NewSpring = createEmpty();

        NewSpring->setEdge(Edge);
        NewSpring->setComponent(TheComponent);
        NewSpring->setLayout(TheLayout);

    return ProxyLayoutSpringTransitPtr(NewSpring);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 ProxyLayoutSpring::getMinimumValue(void) const
{
    return getConstraint()->getMinimumValue();
}

Real32 ProxyLayoutSpring::getPreferredValue(void) const
{
    return getConstraint()->getPreferredValue();
}

Real32 ProxyLayoutSpring::getMaximumValue(void) const
{
    return getConstraint()->getMaximumValue();
}

Real32 ProxyLayoutSpring::getValue(void) const
{
    return getConstraint()->getValue();
}

void ProxyLayoutSpring::setValue(const Real32& value)
{
    return getConstraint()->setValue(value);
}

bool ProxyLayoutSpring::isCyclic(const SpringLayout* l) const
{
    return l->isCyclic(getConstraint());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProxyLayoutSpring::ProxyLayoutSpring(void) :
    Inherited()
{
}

ProxyLayoutSpring::ProxyLayoutSpring(const ProxyLayoutSpring &source) :
    Inherited(source)
{
}

ProxyLayoutSpring::~ProxyLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ProxyLayoutSpring::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ProxyLayoutSpring::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ProxyLayoutSpring NI" << std::endl;
}

OSG_END_NAMESPACE
