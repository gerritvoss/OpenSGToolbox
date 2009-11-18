/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef OSG_COMPILEANIMATIONLIB
#define OSG_COMPILEANIMATIONLIB
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAnimationGroup.h"
#include "Animations/OSGAnimation.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AnimationGroup

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimationGroup::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AnimationGroup::start(const Time& StartTime)
{
    if(_IsPlaying)
    {
        stop(false);
    }

    _IsPlaying = true;
    for(UInt32 i = 0; i < getAnimations().size(); ++i)
    {
        getAnimations(i)->start(StartTime);
    }
    produceAnimationsStarted();
}

void AnimationGroup::seek(const Time& SeekTime)
{
    if(_IsPlaying)
    {
        for(UInt32 i = 0; i < getAnimations().size(); ++i)
        {
            getAnimations(i)->seek(SeekTime);
        }
    }
}

void AnimationGroup::pause(bool ShouldPause)
{
    for(UInt32 i = 0; i < getAnimations().size(); ++i)
    {
        getAnimations(i)->pause(ShouldPause);
    }

    if(_IsPaused && !ShouldPause)
    {
        _IsPaused = ShouldPause;
        produceAnimationsUnpaused();
    }
    if(!_IsPaused && ShouldPause)
    {
        _IsPaused = ShouldPause;
        produceAnimationsPaused();
    }
}

void AnimationGroup::stop(bool DisconnectFromEventProducer)
{
    if(_IsPlaying)
    {
        for(UInt32 i = 0; i < getAnimations().size(); ++i)
        {
            getAnimations(i)->stop(true);
        }

        _IsPlaying = false;
        if(DisconnectFromEventProducer)
        {
            _UpdateEventConnection.disconnect();
        }
        produceAnimationsStopped();
    }
}

bool AnimationGroup::update(const Time& ElapsedTime)
{
    if(!_IsPlaying || _IsPaused)
    {
        return false;
    }

    bool Result(true);

    for(UInt32 i = 0; i < getAnimations().size(); ++i)
    {
        Result = getAnimations(i)->update(ElapsedTime * getScale()) && Result;
    }

    if(Result)
    {
        _UpdateEventConnection.disconnect();
        _IsPlaying = false;
        produceAnimationsEnded();
    }

	return Result;
}

bool AnimationGroup::update(const AnimationAdvancerPtr& advancer)
{
    if(!_IsPlaying || _IsPaused)
    {
        return false;
    }

    bool Result(true);

    for(UInt32 i = 0; i < getAnimations().size(); ++i)
    {
        Result = Result && getAnimations(i)->update(advancer);
    }

	return Result;
}

Real32 AnimationGroup::getLength(void) const
{
    Real32 MaxLength(0.0f);
    for(UInt32 i = 0; i < getAnimations().size(); ++i)
    {
        MaxLength = osgMax(MaxLength,getAnimations(i)->getLength());
    }
    return MaxLength;
}

void AnimationGroup::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    update(UpdateEventPtr::dcast(EventDetails)->getElapsedTime());
}

void AnimationGroup::produceAnimationsStarted(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsStartedMethodId,e);
}

void AnimationGroup::produceAnimationsStopped(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsStoppedMethodId,e);
}

void AnimationGroup::produceAnimationsPaused(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsPausedMethodId,e);
}

void AnimationGroup::produceAnimationsUnpaused(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsUnpausedMethodId,e);
}

void AnimationGroup::produceAnimationsEnded(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsEndedMethodId,e);
}

void AnimationGroup::produceAnimationsCycled(void)
{
    const AnimationEventPtr e = AnimationEvent::create(AnimationGroupPtr(this),getTimeStamp());
    _Producer.produceEvent(AnimationsCycledMethodId,e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimationGroup::AnimationGroup(void) :
    Inherited(),
    _CurrentTime(0.0),
    _PrevTime(0.0),
    _IsPlaying(false),
    _IsPaused(false)

{
}

AnimationGroup::AnimationGroup(const AnimationGroup &source) :
    Inherited(source),
    _CurrentTime(0.0),
    _PrevTime(0.0),
    _IsPlaying(false),
    _IsPaused(false)

{
}

AnimationGroup::~AnimationGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimationGroup::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & AnimationsFieldMask) || (whichField & OffsetFieldMask))
    {
        for(UInt32 i = 0; i < getAnimations().size(); ++i)
        {
            beginEditCP(getAnimations(i), Animation::OffsetFieldMask);
                getAnimations(i)->setOffset(getOffset());
            endEditCP(getAnimations(i), Animation::OffsetFieldMask);
        }
    }
}

void AnimationGroup::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AnimationGroup NI" << std::endl;
}


OSG_END_NAMESPACE

