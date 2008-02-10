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

#include "OSGScaleLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ScaleLayoutSpring
A UI Scale LayoutSpring. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScaleLayoutSpring::initMethod (void)
{
}

ScaleLayoutSpringPtr ScaleLayoutSpring::create(LayoutSpringPtr TheSpring, Real32 Factor)
{
    ScaleLayoutSpringPtr NewSpring = createEmpty();

    beginEditCP(NewSpring, SpringFieldMask | FactorFieldMask);
        NewSpring->setSpring(TheSpring);
        NewSpring->setFactor(Factor);
    endEditCP(NewSpring, SpringFieldMask | FactorFieldMask);

    return NewSpring;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 ScaleLayoutSpring::getMinimumValue(void) const
{
    if(getFactor() < 0.0f)
    {
        return getSpring()->getMinimumValue();
    }
    else
    {
        return static_cast<Real32>(osgfloor<Real32>(getFactor() * static_cast<Real32>(getSpring()->getMinimumValue())));
    }
}

Real32 ScaleLayoutSpring::getPreferredValue(void) const
{
    return static_cast<Real32>(osgfloor<Real32>(getFactor() * static_cast<Real32>(getSpring()->getPreferredValue())));
}

Real32 ScaleLayoutSpring::getMaximumValue(void) const
{
    if(getFactor() < 0.0f)
    {
        return getSpring()->getMaximumValue();
    }
    else
    {
        return static_cast<Real32>(osgfloor<Real32>(getFactor() * static_cast<Real32>(getSpring()->getMaximumValue())));
    }
}

Real32 ScaleLayoutSpring::getValue(void) const
{
    return static_cast<Real32>(osgfloor<Real32>(getFactor() * static_cast<Real32>(getSpring()->getValue())));
}

void ScaleLayoutSpring::setValue(const Real32& value)
{
    if(value == LayoutSpring::VALUE_NOT_SET)
    {
        getSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    else
    {
        getSpring()->setValue(osgfloor<Real32>(static_cast<Real32>(getSpring()->getValue()) / getFactor()));
    }
}

bool ScaleLayoutSpring::isCyclic(SpringLayoutPtr l) const
{
    return getSpring()->isCyclic(l);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScaleLayoutSpring::ScaleLayoutSpring(void) :
    Inherited()
{
}

ScaleLayoutSpring::ScaleLayoutSpring(const ScaleLayoutSpring &source) :
    Inherited(source)
{
}

ScaleLayoutSpring::~ScaleLayoutSpring(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScaleLayoutSpring::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ScaleLayoutSpring::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScaleLayoutSpring NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSCALELAYOUTSPRINGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCALELAYOUTSPRINGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCALELAYOUTSPRINGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

