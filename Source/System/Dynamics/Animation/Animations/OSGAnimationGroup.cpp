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


bool AnimationGroup::update(const Time& ElapsedTime)
{
    if(!_IsPlaying || _IsPaused)
    {
        return false;
    }
    _CurrentTime += getScale()*ElapsedTime;

    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
    {
        getAnimations(i)->update(ElapsedTime * getScale());
    }

 //   UInt32 PreUpdateCycleCount(getCycles());
	//if(getCycling() < 0 || PreUpdateCycleCount < getCycling())
	//{
	//	Real32 CycleLength(getCycleLength()),
	//		   t(_CurrentTime + getOffset());
 //       
	//	//Check if the Animation Time is past the end
	//	if(t >= CycleLength)
	//	{
	//		//Update the number of cycles completed
 //           setCycles( (CycleLength <= 0.0f) ? (0): (static_cast<UInt32>( osgFloor( t / CycleLength ) )) );
 //           commitChanges();
	//	}
	//	//Internal Update
	//	if(getCycling() > 0 && getCycles() >= getCycling())
	//	{
	//		internalUpdate(CycleLength-.0001, _PrevTime);
	//	}
	//	else
	//	{
	//		internalUpdate(t, _PrevTime);
	//	}


	//	//If the number of cycles has changed
	//	if(getCycles() != PreUpdateCycleCount)
	//	{
	//		if(getCycling() > 0 && getCycles() >= getCycling())
	//		{
 //               _UpdateEventConnection.disconnect();
 //               _IsPlaying = false;
	//			produceAnimationEnded();
	//		}
	//		else
	//		{
	//			produceAnimationCycled();
	//		}
	//	}
	//}

    _PrevTime = _CurrentTime;
	//Return true if the animation has completed its number of cycles, false otherwise
	return (getCycling() > 0 && getCycles() >= getCycling());
}

void AnimationGroup::start(const Time& StartTime)
{
    Inherited::start(StartTime);

    for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
    {
        getAnimations(i)->start(StartTime);
    }
}

void AnimationGroup::seek(const Time& SeekTime)
{
    Inherited::seek(SeekTime);

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

    Inherited::pause(ShouldPause);
}

void AnimationGroup::stop(bool DisconnectFromEventProducer)
{
    if(_IsPlaying)
    {
        for(UInt32 i = 0; i < getMFAnimations()->size(); ++i)
        {
            getAnimations(i)->stop(true);
        }
    }
    Inherited::stop();
}

void AnimationGroup::internalUpdate(Real32 t, const Real32 prev_t)
{
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

Real32 AnimationGroup::getCycleLength(void) const
{
    return getLength();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnimationGroup::AnimationGroup(void) :
    Inherited()
{
}

AnimationGroup::AnimationGroup(const AnimationGroup &source) :
    Inherited(source)
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
