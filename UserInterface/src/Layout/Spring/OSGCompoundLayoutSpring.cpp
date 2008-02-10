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

#include "OSGCompoundLayoutSpring.h"
#include "Layout/OSGSpringLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CompoundLayoutSpring
A UI Compound LayoutSpring. Use the instance variables of the StaticSpring superclass to cache values that have already been calculated. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CompoundLayoutSpring::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 CompoundLayoutSpring::getMinimumValue(void) const
{
    if (getMinimum() == LayoutSpring::VALUE_NOT_SET)
    {
        beginEditCP(CompoundLayoutSpringPtr(this), MinimumFieldMask);
            const_cast<CompoundLayoutSpring*>(this)->setMinimum( operation(getSpring1()->getMinimumValue(), getSpring1()->getMinimumValue() ) );
        endEditCP(CompoundLayoutSpringPtr(this), MinimumFieldMask);
    }
    return getMinimum();
}

Real32 CompoundLayoutSpring::getPreferredValue(void) const
{
    if (getPreferred() == LayoutSpring::VALUE_NOT_SET)
    {
        beginEditCP(CompoundLayoutSpringPtr(this), PreferredFieldMask);
            const_cast<CompoundLayoutSpring*>(this)->setPreferred( operation(getSpring1()->getPreferredValue(), getSpring1()->getPreferredValue() ) );
        endEditCP(CompoundLayoutSpringPtr(this), PreferredFieldMask);
    }
    return getPreferred();
}

Real32 CompoundLayoutSpring::getMaximumValue(void) const
{
    if (getMaximum() == LayoutSpring::VALUE_NOT_SET)
    {
        beginEditCP(CompoundLayoutSpringPtr(this), MaximumFieldMask);
            const_cast<CompoundLayoutSpring*>(this)->setMaximum( operation(getSpring1()->getMaximumValue(), getSpring1()->getMaximumValue() ) );
        endEditCP(CompoundLayoutSpringPtr(this), MaximumFieldMask);
    }
    return getMaximum();
}

Real32 CompoundLayoutSpring::getValue(void) const
{
    beginEditCP(CompoundLayoutSpringPtr(this), SizeFieldMask);
        const_cast<CompoundLayoutSpring*>(this)->setSize( operation(getSpring1()->getValue(), getSpring2()->getValue() ) );
    endEditCP(CompoundLayoutSpringPtr(this), SizeFieldMask);

    return getSize();
}

bool CompoundLayoutSpring::isCyclic(SpringLayoutPtr l) const
{
    return l->isCyclic(getSpring1()) || l->isCyclic(getSpring2());
}

void CompoundLayoutSpring::clear(void)
{
    Inherited::clear();

    beginEditCP(CompoundLayoutSpringPtr(this), MinimumFieldMask | PreferredFieldMask | MaximumFieldMask);
        setMinimum(LayoutSpring::VALUE_NOT_SET);
        setPreferred(LayoutSpring::VALUE_NOT_SET);
        setMaximum(LayoutSpring::VALUE_NOT_SET);
    endEditCP(CompoundLayoutSpringPtr(this), MinimumFieldMask | PreferredFieldMask | MaximumFieldMask);
    
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

void CompoundLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CompoundLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CompoundLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOMPOUNDLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPOUNDLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPOUNDLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

