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

#include "OSGSound.h"
#include "OSGSoundManager.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundBase.cpp file.
// To modify it, please change the .fcd file (OSGSound.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Sound::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

//! create a new instance of the class
SoundUnrecPtr Sound::create(void)
{
    return SoundManager::the()->createSound(); 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection Sound::addSoundListener(SoundListenerPtr Listener)
{
   _SoundListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Sound::isSoundListenerAttached, this, Listener),
       boost::bind(&Sound::removeSoundListener, this, Listener));
}

void Sound::removeSoundListener(SoundListenerPtr Listener)
{
   SoundListenerSetItor EraseIter(_SoundListeners.find(Listener));
   if(EraseIter != _SoundListeners.end())
   {
      _SoundListeners.erase(EraseIter);
   }
}

void Sound::produceSoundPlayed(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundPlayed(e);
    }
    _Producer.produceEvent(SoundPlayedMethodId,e);
}

void Sound::produceSoundStopped(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundStopped(e);
    }
    _Producer.produceEvent(SoundStoppedMethodId,e);
}

void Sound::produceSoundPaused(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundPaused(e);
    }
    _Producer.produceEvent(SoundPausedMethodId,e);
}

void Sound::produceSoundUnpaused(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundUnpaused(e);
    }
    _Producer.produceEvent(SoundUnpausedMethodId,e);
}

void Sound::produceSoundLooped(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundLooped(e);
    }
    _Producer.produceEvent(SoundLoopedMethodId,e);
}

void Sound::produceSoundEnded(UInt32 TheChannel)
{
    const SoundEventUnrecPtr e = SoundEvent::create(SoundUnrecPtr(this), getTimeStamp(), TheChannel);
    SoundListenerSet ListenerSet(_SoundListeners);
    for(SoundListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->soundEnded(e);
    }
    _Producer.produceEvent(SoundEndedMethodId,e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Sound::Sound(void) :
    Inherited()
{
}

Sound::Sound(const Sound &source) :
    Inherited(source)
{
}

Sound::~Sound(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Sound::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Sound::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Sound NI" << std::endl;
}

OSG_END_NAMESPACE
