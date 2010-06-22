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

#include "OSGAnimationAdvancer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AnimationAdvancer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimationAdvancer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/



void AnimationAdvancer::start(void)
{   
    if(!_IsRunning)
    {
        _IsRunning = true;
        //produceAnimationStarted();
    }
}

void AnimationAdvancer::stop(void)
{
    if(!_IsRunning)
    {
        _IsRunning = false;
        //produceAnimationStopped();
    }
    //beginEditCP(AnimationPtr(this), CyclesFieldMask);
    //    setCycles( 0 );
    //endEditCP(AnimationPtr(this), CyclesFieldMask);
}

void AnimationAdvancer::pause(void)
{
    if(!_IsPaused)
    {
        _IsPaused = true;
        //produceAnimationPaused();
    }
}

void AnimationAdvancer::unpause(void)
{
    if(_IsPaused)
    {
        _IsPaused = false;
        //produceAnimationUnpaused();
    }
}

void AnimationAdvancer::pauseToggle(void)
{
    if(_IsPaused)
    {
        unpause();
    }
    else
    {
        pause();
    }
}

bool AnimationAdvancer::isPaused(void)
{
    return _IsPaused;
}

bool AnimationAdvancer::isRunning(void)
{
    return _IsRunning;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimationAdvancer::AnimationAdvancer(void) :
    Inherited(), _IsPaused(false),_IsRunning(false)
{
}

AnimationAdvancer::AnimationAdvancer(const AnimationAdvancer &source) :
    Inherited(source), _IsPaused(false),_IsRunning(false)
{
}

AnimationAdvancer::~AnimationAdvancer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimationAdvancer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AnimationAdvancer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AnimationAdvancer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGANIMATIONADVANCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGANIMATIONADVANCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGANIMATIONADVANCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

