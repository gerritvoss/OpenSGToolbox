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
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStarted(e);
    }
    produceEvent(AnimationStartedMethodId,e);
}

void Animation::produceAnimationStopped(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStopped(e);
    }
    produceEvent(AnimationStoppedMethodId,e);
}

void Animation::produceAnimationPaused(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationPaused(e);
    }
    produceEvent(AnimationPausedMethodId,e);
}

void Animation::produceAnimationUnpaused(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationUnpaused(e);
    }
    produceEvent(AnimationUnpausedMethodId,e);
}

void Animation::produceAnimationEnded(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationEnded(e);
    }
    produceEvent(AnimationEndedMethodId,e);
}

void Animation::produceAnimationCycled(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationPtr(this),getTimeStamp());
    AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
        (*SetItor)->animationCycled(e);
    }
    produceEvent(AnimationCycledMethodId,e);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Animation::Animation(void) :
    Inherited()
{
}

Animation::Animation(const Animation &source) :
    Inherited(source)
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

