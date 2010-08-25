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
#include "OSGUpdateEventDetails.h"
#include "OSGAnimationGroup.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimationGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimationGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimationGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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
    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
    {
        getAnimations(i)->start(StartTime);
    }
    produceAnimationsStarted();
}

void AnimationGroup::seek(const Time& SeekTime)
{
    if(_IsPlaying)
    {
        for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
        {
            getAnimations(i)->seek(SeekTime);
        }
    }
}

void AnimationGroup::pause(bool ShouldPause)
{
    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
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
        for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
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

    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
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

void AnimationGroup::attachUpdateProducer(ReflexiveContainer* const producer)
{
    if(_UpdateEventConnection.connected())
    {
        _UpdateEventConnection.disconnect();
    }
    //Get the Id of the UpdateEvent
    const EventDescription* Desc(producer->getProducerType().findEventDescription("Update"));
    if(Desc == NULL)
    {
        SWARNING << "There is no Update event defined on " << producer->getType().getName() << " types." << std::endl;
    }
    else
    {
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&AnimationGroup::attachedUpdate, this, _1));
    }
}

Real32 AnimationGroup::getLength(void) const
{
    Real32 MaxLength(0.0f);
    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
    {
        MaxLength = osgMax(MaxLength,getAnimations(i)->getLength());
    }
    return MaxLength;
}

void AnimationGroup::attachedUpdate(EventDetails* const details)
{
    update(dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime());
}

void AnimationGroup::produceAnimationsStarted(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsStarted(Details);
}

void AnimationGroup::produceAnimationsStopped(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsStopped(Details);
}

void AnimationGroup::produceAnimationsPaused(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsPaused(Details);
}

void AnimationGroup::produceAnimationsUnpaused(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsUnpaused(Details);
}

void AnimationGroup::produceAnimationsEnded(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsEnded(Details);
}

void AnimationGroup::produceAnimationsCycled(void)
{
    AnimationEventDetailsUnrecPtr Details = AnimationEventDetails::create(this,getTimeStamp());
   
    Inherited::produceAnimationsCycled(Details);
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

void AnimationGroup::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & AnimationsFieldMask) || (whichField & OffsetFieldMask))
    {
        for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
        {
            getAnimations(i)->setOffset(getOffset());
            //commitChanges();
        }
    }
    if((whichField & AnimationsFieldMask) || (whichField & SpanFieldMask))
    {
        for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
        {
            getAnimations(i)->setSpan(getSpan());
            //commitChanges();
        }
    }
}

void AnimationGroup::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimationGroup NI" << std::endl;
}

OSG_END_NAMESPACE
