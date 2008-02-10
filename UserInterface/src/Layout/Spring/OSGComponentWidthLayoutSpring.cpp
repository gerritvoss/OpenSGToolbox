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

#include "OSGComponentWidthLayoutSpring.h"
#include "Component/OSGComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComponentWidthLayoutSpring
A UI ComponentWidth LayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentWidthLayoutSpring::initMethod (void)
{
}

ComponentWidthLayoutSpringPtr ComponentWidthLayoutSpring::create (ComponentPtr TheComponent)
{
    ComponentWidthLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, ComponentFieldMask);
        NewSpring->setComponent(TheComponent);
    endEditCP(NewSpring, ComponentFieldMask);

    return NewSpring;
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
    return getComponent()->getPreferredSize().x();
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

void ComponentWidthLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ComponentWidthLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComponentWidthLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOMPONENTWIDTHLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPONENTWIDTHLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPONENTWIDTHLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

