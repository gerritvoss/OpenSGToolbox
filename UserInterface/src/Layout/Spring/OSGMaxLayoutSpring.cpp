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

#include "OSGMaxLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MaxLayoutSpring
A UI Max LayoutSpring. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaxLayoutSpring::initMethod (void)
{
}


MaxLayoutSpringPtr MaxLayoutSpring::create(LayoutSpringPtr TheSpring1, LayoutSpringPtr TheSpring2)
{
    MaxLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, Spring1FieldMask | Spring2FieldMask);
        NewSpring->setSpring1(TheSpring1);
        NewSpring->setSpring2(TheSpring2);
    endEditCP(NewSpring, Spring1FieldMask | Spring2FieldMask);

    return NewSpring;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Int32 MaxLayoutSpring::operation(const Int32& Left, const Int32& Right) const
{
    return osgMax(Left, Right);
}

void MaxLayoutSpring::setNonClearValue(const Int32& value)
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

void MaxLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MaxLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MaxLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMAXLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMAXLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMAXLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

