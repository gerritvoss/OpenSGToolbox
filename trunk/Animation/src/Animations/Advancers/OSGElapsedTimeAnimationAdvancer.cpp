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

#include "OSGElapsedTimeAnimationAdvancer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ElapsedTimeAnimationAdvancer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ElapsedTimeAnimationAdvancer::initMethod (void)
{
}

osg::Real32 ElapsedTimeAnimationAdvancer::getValue(void) const
{
   return getElpsTime();
}

osg::Real32 ElapsedTimeAnimationAdvancer::getPrevValue(void) const
{
   return getPrevElpsTime();
}

void ElapsedTimeAnimationAdvancer::start(void)
{
    if(!_IsRunning)
    {
       setElpsTime( getStartTime() );
    }
    Inherited::start();
}

void ElapsedTimeAnimationAdvancer::reset(void)
{
    stop();

    start();
}

void ElapsedTimeAnimationAdvancer::stop(void)
{
    if(_IsRunning)
    {
        setElpsTime( getStartTime() );
    }
    Inherited::stop();
}

void ElapsedTimeAnimationAdvancer::update(const Real32& elps)
{
    if(_IsRunning && !_IsPaused)
    {
        setElpsTime(getElpsTime() + elps);
    }
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ElapsedTimeAnimationAdvancer::ElapsedTimeAnimationAdvancer(void) :
    Inherited()
{
}

ElapsedTimeAnimationAdvancer::ElapsedTimeAnimationAdvancer(const ElapsedTimeAnimationAdvancer &source) :
    Inherited(source)
{
}

ElapsedTimeAnimationAdvancer::~ElapsedTimeAnimationAdvancer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ElapsedTimeAnimationAdvancer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ElapsedTimeAnimationAdvancer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ElapsedTimeAnimationAdvancer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGELAPSEDTIMEANIMATIONADVANCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGELAPSEDTIMEANIMATIONADVANCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGELAPSEDTIMEANIMATIONADVANCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

