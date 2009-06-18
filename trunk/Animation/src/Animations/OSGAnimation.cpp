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

#include "OSGAnimation.h"
#include <boost/bind.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Animation
Animation is the base class of all Animation 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Animation::initMethod (void)
{

}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
EventConnection Animation::addAnimationListener(AnimationListenerPtr Listener)
{
   _AnimationListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Animation::isAnimationListenerAttached, this, Listener),
       boost::bind(&Animation::removeAnimationListener, this, Listener));
}

void Animation::start(void)
{   
    if(!_IsRunning)
    {
        _IsRunning = true;
        produceAnimationStarted();
    }
}

void Animation::stop(void)
{
    if(!_IsRunning)
    {
        _IsRunning = false;
        produceAnimationStopped();
    }
    beginEditCP(AnimationPtr(this), CyclesFieldMask);
        setCycles( 0 );
    endEditCP(AnimationPtr(this), CyclesFieldMask);
}

bool Animation::update(const AnimationAdvancerPtr& advancer)
{
    UInt32 PreUpdateCycleCount(getCycles());
    if(getCycling() < 0 || PreUpdateCycleCount < getCycling())
    {
        Real32 Length(getLength()),
               t(advancer->getValue());
        
        //Check if the Animation Time is past the end
        if(t >= Length)
        {
            //Update the number of cycles completed
            beginEditCP(AnimationPtr(this), CyclesFieldMask);
                setCycles( (Length <= 0.0f) ? (0): (static_cast<UInt32>( osg::osgfloor( t / Length ) )) );
            endEditCP(AnimationPtr(this), CyclesFieldMask);
        }
        //Internal Update
        if(getCycling() > 0 && getCycles() >= getCycling())
        {
            internalUpdate(Length-.0001, advancer->getPrevValue());
        }
        else
        {
            internalUpdate(t, advancer->getPrevValue());
        }


        //If the number of cycles has changed
        if(getCycles() != PreUpdateCycleCount)
        {
            produceAnimationCycled();
        }
    }

    //Return true if the animation has completed its number of cycles, false otherwise
    return (getCycling() > 0 && getCycles() >= getCycling());
}

void Animation::pause(void)
{
    _IsPaused = true;
    produceAnimationPaused();
}

void Animation::unpause(void)
{
    _IsPaused = false;
    produceAnimationUnpaused();
}

void Animation::pauseToggle(void)
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

bool Animation::isPaused(void)
{
    return _IsPaused;
}

bool Animation::isRunning(void)
{
    return _IsRunning;
}

void Animation::removeAnimationListener(AnimationListenerPtr Listener)
{
   AnimationListenerSetItor EraseIter(_AnimationListeners.find(Listener));
   if(EraseIter != _AnimationListeners.end())
   {
      _AnimationListeners.erase(EraseIter);
   }
}

void Animation::produceAnimationStarted(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStarted(e);
    }
}

void Animation::produceAnimationStopped(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStopped(e);
    }
}

void Animation::produceAnimationPaused(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationPaused(e);
    }
}

void Animation::produceAnimationUnpaused(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationUnpaused(e);
    }
}

void Animation::produceAnimationEnded(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationEnded(e);
    }
}

void Animation::produceAnimationCycled(void)
{
    AnimationEvent e(AnimationPtr(this),getTimeStamp(),AnimationPtr(this));
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationCycled(e);
    }
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Animation::Animation(void) :
    Inherited(), _IsPaused(false),_IsRunning(false)
{
}

Animation::Animation(const Animation &source) :
    Inherited(source), _IsPaused(false),_IsRunning(false)
{
}

Animation::~Animation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Animation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Animation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Animation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

