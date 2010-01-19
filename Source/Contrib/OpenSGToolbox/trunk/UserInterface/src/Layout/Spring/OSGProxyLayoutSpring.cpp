/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGProxyLayoutSpring.h"
#include "Layout/OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ProxyLayoutSpring
A UI Proxy LayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProxyLayoutSpring::initMethod (void)
{
}


ProxyLayoutSpringPtr ProxyLayoutSpring::create (const UInt32& Edge, ComponentPtr TheComponent, SpringLayoutPtr TheLayout)
{
    ProxyLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, EdgeFieldMask | ComponentFieldMask | LayoutFieldMask);
        NewSpring->setEdge(Edge);
        NewSpring->setComponent(TheComponent);
        NewSpring->setLayout(TheLayout);
    endEditCP(NewSpring, EdgeFieldMask | ComponentFieldMask | LayoutFieldMask);

    return NewSpring;
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

bool ProxyLayoutSpring::isCyclic(SpringLayoutPtr l) const
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

void ProxyLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ProxyLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ProxyLayoutSpring NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPROXYLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPROXYLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPROXYLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

