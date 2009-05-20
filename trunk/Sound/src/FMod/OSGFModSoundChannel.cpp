/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFModSoundChannel.h"
#include "OSGFModSoundManager.h"

#ifdef _OSG_TOOLBOX_USE_FMOD_

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FModSoundChannel
A FMod SoundChannel Interface. 
*/

FMOD_RESULT F_CALLBACK FModSoundChannelCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2);

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool FModSoundChannel::isPlaying(void) const
{
    bool playing(false);
    FMOD_RESULT result;
    result = _FModChannel->isPlaying(&playing);
    FMOD_ERRCHECK(result);
    
    return playing;
    
}

bool FModSoundChannel::isValid(void) const
{
    bool valid(false);
        SWARNING << "FModSoundChannel: isValid Not Implemented" << std::endl;
    
    return valid;
}

void FModSoundChannel::stop(void)
{
    if(isPlaying())
    {
        FMOD_RESULT result;
        result = _FModChannel->stop();
        FMOD_ERRCHECK(result);
        if(result == FMOD_OK)
        {
            produceSoundStopped();
        }
    }
}

void FModSoundChannel::pause(void)
{
    if(isPlaying() && !isPaused())
    {
        FMOD_RESULT result;
        result = _FModChannel->setPaused(true);
        FMOD_ERRCHECK(result);
        if(result == FMOD_OK)
        {
            produceSoundPaused();
        }
    }
}

void FModSoundChannel::unpause(void)
{
    if(isPaused())
    {
        FMOD_RESULT result;
        result = _FModChannel->setPaused(false);
        FMOD_ERRCHECK(result);
        if(result == FMOD_OK)
        {
            produceSoundUnpaused();
        }
    }
}

void FModSoundChannel::pauseToggle(void)
{
    if(isPaused())
    {
        unpause();
    }
    else
    {
        pause();
    }
}

bool FModSoundChannel::isPaused(void) const
{
    bool paused(false);
    FMOD_RESULT result;
    result = _FModChannel->getPaused(&paused);
    FMOD_ERRCHECK(result);
    
    return paused;
}



void FModSoundChannel::seek(Real32 pos)
{
    unsigned int position(pos * 1000.0);

    FMOD_RESULT result;
    result = _FModChannel->setPosition(position, FMOD_TIMEUNIT_MS);
    FMOD_ERRCHECK(result);
}

Real32 FModSoundChannel::getTime(void) const
{
    unsigned int position;

    FMOD_RESULT result;
    result = _FModChannel->getPosition(&position, FMOD_TIMEUNIT_MS);
    FMOD_ERRCHECK(result);
    
    if(result == FMOD_OK)
    {
        return static_cast<Real32>(position)/static_cast<Real32>(1000.0f);
    }
    else
    {
        return 0.0f;
    }
}

Real32 FModSoundChannel::getLength(void) const
{
    UInt32 ui_length(0);
    
    FMOD_RESULT result;
    
    FMOD::Sound *sound;
    result = _FModChannel->getCurrentSound(&sound);
    FMOD_ERRCHECK(result);

    if(result == FMOD_OK)
    {
        result = sound->getLength(&ui_length, FMOD_TIMEUNIT_MS);
        FMOD_ERRCHECK(result);
    }

    if(result == FMOD_OK)
    {
        return static_cast<Real32>(ui_length)/static_cast<Real32>(1000.0f);
    }
    else
    {
        return 0.0;
    }
}


void FModSoundChannel::setPosition(const Pnt3f &pos)
{
    FMOD_RESULT result;

    FMOD_MODE TheMode;
    result = _FModChannel->getMode(&TheMode);
    FMOD_ERRCHECK(result);
    if(result == FMOD_OK && TheMode & FMOD_3D)
    {
        FMOD_VECTOR curPos;
        FMOD_VECTOR curVec;

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);

        curPos.x = pos.x();
        curPos.y = pos.y();
        curPos.z = pos.z();

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);
    }
}

Pnt3f FModSoundChannel::getPosition(void) const
{
    FMOD_RESULT result;

    FMOD_MODE TheMode;
    result = _FModChannel->getMode(&TheMode);
    FMOD_ERRCHECK(result);
    if(result == FMOD_OK && TheMode & FMOD_3D)
    {
        FMOD_VECTOR curPos;
        FMOD_VECTOR curVec;

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);

        return Vec3f(curPos.x, curPos.y, curPos.z);
    }
    else
    {
        SWARNING << "FModSoundChannel: This channel is not an FMOD_3D" << std::endl;
        return Vec3f(0.0f,0.0f,0.0f);
    }
}

void FModSoundChannel::setVelocity(const Vec3f &vec)
{
    FMOD_RESULT result;

    FMOD_MODE TheMode;
    result = _FModChannel->getMode(&TheMode);
    FMOD_ERRCHECK(result);
    if(result == FMOD_OK && TheMode & FMOD_3D)
    {
        FMOD_VECTOR curPos;
        FMOD_VECTOR curVec;

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);

        curVec.x = vec.x();
        curVec.y = vec.y();
        curVec.z = vec.z();

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);
    }
}

Vec3f FModSoundChannel::getVelocity(void) const
{
    FMOD_RESULT result;

    FMOD_MODE TheMode;
    result = _FModChannel->getMode(&TheMode);
    FMOD_ERRCHECK(result);
    if(result == FMOD_OK && TheMode & FMOD_3D)
    {
        FMOD_VECTOR curPos;
        FMOD_VECTOR curVec;

        result = _FModChannel->get3DAttributes(&curPos, &curVec);
        FMOD_ERRCHECK(result);

        return Vec3f(curVec.x, curVec.y, curVec.z);
    }
    else
    {
        SWARNING << "FModSoundChannel: This channel is not an FMOD_3D" << std::endl;
        return Vec3f(0.0f,0.0f,0.0f);
    }
}

void FModSoundChannel::setVolume(Real32 volume)
{
    FMOD_RESULT result;
    result = _FModChannel->setVolume(volume);
    FMOD_ERRCHECK(result);
}

Real32 FModSoundChannel::getVolume(void) const
{
    float  volume;

    FMOD_RESULT result;
    result = _FModChannel->getVolume(&volume);
    FMOD_ERRCHECK(result);
    
    if(result == FMOD_OK)
    {
        return static_cast<Real32>(volume);
    }
    else
    {
        return 0.0f;
    }
}

bool FModSoundChannel::getMute(void) const
{
    bool muteValue(false);
    FMOD_RESULT result;
    result = _FModChannel->getMute(&muteValue);
    FMOD_ERRCHECK(result);
    
    return muteValue;
}

void FModSoundChannel::mute(bool shouldMute)
{
    FMOD_RESULT result;
    result = _FModChannel->setMute(shouldMute);
    FMOD_ERRCHECK(result);
}

void FModSoundChannel::soundEnded(void)
{
    produceSoundEnded();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FModSoundChannel::FModSoundChannel(FMOD::Channel *channel) :
    Inherited(),
    _FModChannel(channel)
{
    FMOD_RESULT result;
    result = _FModChannel->setCallback(FModSoundChannelCallback);
    FMOD_ERRCHECK(result);
    result = _FModChannel->setUserData(this);
    FMOD_ERRCHECK(result);
}

FModSoundChannel::FModSoundChannel(const FModSoundChannel &source) :
    Inherited(source),
    _FModChannel(NULL)
{
}

FModSoundChannel::~FModSoundChannel(void)
{
}

FMOD_RESULT F_CALLBACK FModSoundChannelCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2)
{
    if(type == FMOD_CHANNEL_CALLBACKTYPE_END)
    {
        FMOD::Channel *cppchannel = (FMOD::Channel *)channel;

        void* userData;

        FMOD_RESULT result;
        result = cppchannel->getUserData(&userData);
        FMOD_ERRCHECK(result);

        static_cast<FModSoundChannel*>(userData)->soundEnded();
    }

    return FMOD_OK;
}



OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_USE_FMOD_ */
