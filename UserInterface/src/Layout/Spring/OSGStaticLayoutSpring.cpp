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

#include "OSGStaticLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StaticLayoutSpring
A UI Static LayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StaticLayoutSpring::initMethod (void)
{
}

StaticLayoutSpringPtr StaticLayoutSpring::create (const Real32& Preferred)
{
    StaticLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, PreferredFieldMask);
        NewSpring->setPreferred(Preferred);
    endEditCP(NewSpring, PreferredFieldMask);

    return NewSpring;
}

StaticLayoutSpringPtr StaticLayoutSpring::create (const Real32& Minimum, const Real32& Preferred, const Real32& Maximum)
{
    StaticLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, PreferredFieldMask | MinimumFieldMask | MaximumFieldMask);
        NewSpring->setMinimum(Minimum);
        NewSpring->setPreferred(Preferred);
        NewSpring->setMaximum(Maximum);
    endEditCP(NewSpring, PreferredFieldMask | MinimumFieldMask | MaximumFieldMask);

    return NewSpring;
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

void StaticLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StaticLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StaticLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSTATICLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTATICLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTATICLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

