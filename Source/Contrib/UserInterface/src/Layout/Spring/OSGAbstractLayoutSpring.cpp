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

#include "OSGAbstractLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractLayoutSpring
A UI AbstractLayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractLayoutSpring::initMethod (void)
{
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
    beginEditCP(AbstractLayoutSpringPtr(this), SizeFieldMask);
        setSize(LayoutSpring::VALUE_NOT_SET);
    endEditCP(AbstractLayoutSpringPtr(this), SizeFieldMask);
}

void AbstractLayoutSpring::setNonClearValue(const Real32& value)
{
    beginEditCP(AbstractLayoutSpringPtr(this), SizeFieldMask);
        setSize(value);
    endEditCP(AbstractLayoutSpringPtr(this), SizeFieldMask);
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

void AbstractLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

