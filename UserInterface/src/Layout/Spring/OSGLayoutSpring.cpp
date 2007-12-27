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

#include "OSGLayoutSpring.h"
#include "OSGStaticLayoutSpring.h"
#include "OSGSumLayoutSpring.h"
#include "OSGMaxLayoutSpring.h"
#include "OSGNegativeLayoutSpring.h"
#include "OSGScaleLayoutSpring.h"
#include "OSGComponentWidthLayoutSpring.h"
#include "OSGComponentHeightLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LayoutSpring
A UI LayoutSpring. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Int32 LayoutSpring::VALUE_NOT_SET = TypeTraits< Int32 >::getMin();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LayoutSpring::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 LayoutSpring::getStrain(void) const
{
    Real32 delta = (getValue() - getPreferredValue());
    return delta/range(getValue() < getPreferredValue());
}

void LayoutSpring::setStrain(Real32 strain)
{
    setValue(getPreferredValue() + static_cast<Int32>(strain * range(strain < 0)));
}

bool LayoutSpring::isCyclic(SpringLayoutPtr l) const
{
    return false;
}

Real32 LayoutSpring::range(bool contract) const
{
    if(contract)
    {
        return getPreferredValue() - getMinimumValue();
    }
    else
    {
        return getMaximumValue() - getPreferredValue();
    }
}

LayoutSpringPtr LayoutSpring::constant(const Int32& pref)
{
    return StaticLayoutSpring::create(pref);
}

LayoutSpringPtr LayoutSpring::constant(const Int32& min, const Int32& pref, const Int32& max)
{
    return StaticLayoutSpring::create(min, pref, max);
}

LayoutSpringPtr LayoutSpring::minus(LayoutSpringPtr s)
{
    return NegativeLayoutSpring::create(s);
}

LayoutSpringPtr LayoutSpring::sum(LayoutSpringPtr s1, LayoutSpringPtr s2)
{
    return SumLayoutSpring::create(s1, s2);
}

LayoutSpringPtr LayoutSpring::max(LayoutSpringPtr s1, LayoutSpringPtr s2)
{
    return MaxLayoutSpring::create(s1, s2);
}

LayoutSpringPtr LayoutSpring::difference(LayoutSpringPtr s1, LayoutSpringPtr s2)
{
    return SumLayoutSpring::create(s1, minus(s2));
}

LayoutSpringPtr LayoutSpring::scale(LayoutSpringPtr s, const Real32& factor)
{
    return ScaleLayoutSpring::create(s, factor);
}

LayoutSpringPtr LayoutSpring::width(ComponentPtr c)
{
    return ComponentWidthLayoutSpring::create(c);
}

LayoutSpringPtr LayoutSpring::height(ComponentPtr c)
{
    return ComponentHeightLayoutSpring::create(c);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LayoutSpring::LayoutSpring(void) :
    Inherited()
{
}

LayoutSpring::LayoutSpring(const LayoutSpring &source) :
    Inherited(source)
{
}

LayoutSpring::~LayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

