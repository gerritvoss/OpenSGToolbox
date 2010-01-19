/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGAnimation.h"
#include "OSGUpdateEvent.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimationBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimation.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Animation::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 Animation::getLength(void) const
{
    if(getCycles() > 0)
    {
        return getCycleLength() * getCycles();
    }
    else
    {
        return -1.0f;
    }
}

EventConnection Animation::addAnimationListener(AnimationListenerPtr Listener)
{
   _AnimationListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Animation::isAnimationListenerAttached, this, Listener),
       boost::bind(&Animation::removeAnimationListener, this, Listener));
}

void Animation::start(const Time& StartTime)
{
    if(_IsPlaying)
    {
        stop(false);
    }

    _CurrentTime = _PrevTime = StartTime;
    setCycles(0);
    commitChanges();
    _IsPlaying = true;
    produceAnimationStarted();
}

void Animation::seek(const Time& SeekTime)
{
    if(_IsPlaying)
    {
        _CurrentTime = _PrevTime = SeekTime;
    }
}

void Animation::pause(bool ShouldPause)
{
    if(_IsPaused && !ShouldPause)
    {
        _IsPaused = ShouldPause;
        produceAnimationUnpaused();
    }
    if(!_IsPaused && ShouldPause)
    {
        _IsPaused = ShouldPause;
        produceAnimationPaused();
    }
}

void Animation::stop(bool DisconnectFromEventProducer)
{
    if(_IsPlaying)
    {
        _IsPlaying = false;
        if(DisconnectFromEventProducer)
        {
            _UpdateEventConnection.disconnect();
        }
        produceAnimationStopped();
    }
}

bool Animation::update(const Time& ElapsedTime)
{
    if(!_IsPlaying || _IsPaused)
    {
        return false;
    }

    _CurrentTime += getScale()*ElapsedTime;
    UInt32 PreUpdateCycleCount(getCycles());
	if(getCycling() < 0 || PreUpdateCycleCount < getCycling())
	{
		Real32 CycleLength(getCycleLength()),
			   t(_CurrentTime + getOffset());
        
		//Check if the Animation Time is past the end
		if(t >= CycleLength)
		{
			//Update the number of cycles completed
            setCycles( (CycleLength <= 0.0f) ? (0): (static_cast<UInt32>( osgFloor( t / CycleLength ) )) );
            commitChanges();
		}
		//Internal Update
		if(getCycling() > 0 && getCycles() >= getCycling())
		{
			internalUpdate(CycleLength-.0001, _PrevTime);
		}
		else
		{
			internalUpdate(t, _PrevTime);
		}


		//If the number of cycles has changed
		if(getCycles() != PreUpdateCycleCount)
		{
			if(getCycling() > 0 && getCycles() >= getCycling())
			{
                _UpdateEventConnection.disconnect();
                _IsPlaying = false;
				produceAnimationEnded();
			}
			else
			{
				produceAnimationCycled();
			}
		}
	}

    _PrevTime = _CurrentTime;
	//Return true if the animation has completed its number of cycles, false otherwise
	return (getCycling() > 0 && getCycles() >= getCycling());
}

//bool Animation::update(const AnimationAdvancerPtr& advancer)
//{
	//UInt32 PreUpdateCycleCount(getCycles());
	//if(getCycling() < 0 || PreUpdateCycleCount < getCycling())
	//{
		//Real32 CycleLength(getCycleLength()),
			   //t(advancer->getValue());
        
		////Check if the Animation Time is past the end
		//if(t >= CycleLength)
		//{
			////Update the number of cycles completed
            //setCycles( (CycleLength <= 0.0f) ? (0): (static_cast<UInt32>( osg::osgfloor( t / CycleLength ) )) );
            //commitChanges();
		//}
		////Internal Update
		//if(getCycling() > 0 && getCycles() >= getCycling())
		//{
			//internalUpdate(CycleLength-.0001, advancer->getPrevValue());
		//}
		//else
		//{
			//internalUpdate(t, advancer->getPrevValue());
		//}


		////If the number of cycles has changed
		//if(getCycles() != PreUpdateCycleCount)
		//{
			//if(getCycling() > 0 && getCycles() >= getCycling())
			//{
				//produceAnimationEnded();
			//}
			//else
			//{
				//produceAnimationCycled();
			//}
		//}
	//}

	////Return true if the animation has completed its number of cycles, false otherwise
	//return (getCycling() > 0 && getCycles() >= getCycling());

//}

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
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStarted(e);
    }
    _Producer.produceEvent(AnimationStartedMethodId,e);
}

void Animation::produceAnimationStopped(void)
{
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationStopped(e);
    }
    _Producer.produceEvent(AnimationStoppedMethodId,e);
}

void Animation::produceAnimationPaused(void)
{
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationPaused(e);
    }
    _Producer.produceEvent(AnimationPausedMethodId,e);
}

void Animation::produceAnimationUnpaused(void)
{
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationUnpaused(e);
    }
    _Producer.produceEvent(AnimationUnpausedMethodId,e);
}

void Animation::produceAnimationEnded(void)
{
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
	AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->animationEnded(e);
    }
    _Producer.produceEvent(AnimationEndedMethodId,e);
}

void Animation::produceAnimationCycled(void)
{
    const AnimationEventUnrecPtr e = AnimationEvent::create(AnimationRefPtr(this),getTimeStamp());
    AnimationListenerSet Listeners(_AnimationListeners);
    for(AnimationListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
        (*SetItor)->animationCycled(e);
    }
    _Producer.produceEvent(AnimationCycledMethodId,e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Animation::Animation(void) :
    Inherited(),
    _UpdateHandler(AnimationRefPtr(this)),
    _CurrentTime(0.0),
    _PrevTime(0.0),
    _IsPlaying(false),
    _IsPaused(false)
{
}

Animation::Animation(const Animation &source) :
    Inherited(source),
    _UpdateHandler(AnimationRefPtr(this)),
    _CurrentTime(0.0),
    _PrevTime(0.0),
    _IsPlaying(false),
    _IsPaused(false)

{
}

Animation::~Animation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Animation::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Animation::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Animation NI" << std::endl;
}

void Animation::UpdateHandler::eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId)
{
    _AttachedAnimation->update(dynamic_pointer_cast<UpdateEvent>(EventDetails)->getElapsedTime());
}

OSG_END_NAMESPACE
