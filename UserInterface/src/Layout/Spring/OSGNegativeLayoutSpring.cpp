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

#include "OSGNegativeLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NegativeLayoutSpring
A UI Negative LayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NegativeLayoutSpring::initMethod (void)
{
}


NegativeLayoutSpringPtr NegativeLayoutSpring::create(LayoutSpringPtr TheSpring)
{
    NegativeLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, SpringFieldMask);
        NewSpring->setSpring(TheSpring);
    endEditCP(NewSpring, SpringFieldMask);

    return NewSpring;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Int32 NegativeLayoutSpring::getMinimumValue(void) const
{
    return -getSpring()->getMaximumValue();
}

Int32 NegativeLayoutSpring::getPreferredValue(void) const
{
    return -getSpring()->getPreferredValue();
}

Int32 NegativeLayoutSpring::getMaximumValue(void) const
{
    return -getSpring()->getMinimumValue();
}

Int32 NegativeLayoutSpring::getValue(void) const
{
    return -getSpring()->getValue();
}

void NegativeLayoutSpring::setValue(const Int32& value)
{
    if(value == LayoutSpring::VALUE_NOT_SET)
    {
        getSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    else
    {
        getSpring()->setValue(-value);
    }
}

bool NegativeLayoutSpring::isCyclic(SpringLayoutPtr l) const
{
    return getSpring()->isCyclic(l);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NegativeLayoutSpring::NegativeLayoutSpring(void) :
    Inherited()
{
}

NegativeLayoutSpring::NegativeLayoutSpring(const NegativeLayoutSpring &source) :
    Inherited(source)
{
}

NegativeLayoutSpring::~NegativeLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NegativeLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void NegativeLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump NegativeLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGNEGATIVELAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGNEGATIVELAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGNEGATIVELAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

