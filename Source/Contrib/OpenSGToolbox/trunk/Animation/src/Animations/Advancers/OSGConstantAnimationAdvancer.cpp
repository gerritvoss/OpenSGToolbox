/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>

#include "OSGConstantAnimationAdvancer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ConstantAnimationAdvancer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConstantAnimationAdvancer::initMethod (void)
{
}


osg::Real32 ConstantAnimationAdvancer::getValue(void) const
{
   return getConstant();
}

osg::Real32 ConstantAnimationAdvancer::getPrevValue(void) const
{
   return getPrevConstant();
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ConstantAnimationAdvancer::ConstantAnimationAdvancer(void) :
    Inherited()
{
}

ConstantAnimationAdvancer::ConstantAnimationAdvancer(const ConstantAnimationAdvancer &source) :
    Inherited(source)
{
}

ConstantAnimationAdvancer::~ConstantAnimationAdvancer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ConstantAnimationAdvancer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ConstantAnimationAdvancer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ConstantAnimationAdvancer NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGCONSTANTANIMATIONADVANCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCONSTANTANIMATIONADVANCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCONSTANTANIMATIONADVANCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

