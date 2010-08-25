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

#include "OSGFModSoundManager.h"
#include "OSGFModSound.h"

#include "OSGBaseInitFunctions.h"

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFModSoundBase.cpp file.
// To modify it, please change the .fcd file (OSGFModSound.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FModSound::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::Static)
    {
        addPreFactoryInitFunction(boost::bind(&FModSoundManager::init));
        addPostFactoryExitFunction(boost::bind(&FModSoundManager::uninit));
    }
}

FMOD_RESULT F_CALLBACK FModSoundChannelCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, void *commanddata1, void *commanddata2)
{
    if(type == FMOD_CHANNEL_CALLBACKTYPE_END)
    {
        FMOD::Channel *cppchannel = (FMOD::Channel *)channel;

        void* userData;

        FMOD_RESULT result;
        result = cppchannel->getUserData(&userData);
        FMOD_ERRCHECK(result,"FModSoundChannelCallback()");

        static_cast<FModSound*>(userData)->soundEnded(cppchannel);
    }

    return FMOD_OK;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 FModSound::play(void)
{
    FMOD::Channel *channel;

    FMOD_RESULT result;
    result = FModSoundManager::the()->getSystem()->playSound(FMOD_CHANNEL_FREE, _FModSound, true, &channel);
    FMOD_ERRCHECK(result,"FModSound::play()");

    if(result == FMOD_OK && channel != NULL)
    {
        FMOD_MODE TheMode;
        result = channel->getMode(&TheMode);
        FMOD_ERRCHECK(result,"FModSound::play()");
        if(result == FMOD_OK && TheMode & FMOD_3D)
        {
            FMOD_VECTOR curPos;
            FMOD_VECTOR curVec;
            curPos.x = getPosition().x();
            curPos.y = getPosition().y();
            curPos.z = getPosition().z();
            curVec.x = getVelocity().x();
            curVec.y = getVelocity().y();
            curVec.z = getVelocity().z();

            result = channel->set3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::play()");
        }

        result = channel->setPaused(false);
        FMOD_ERRCHECK(result,"FModSound::play()");

        UInt32 ChannelID = addChannel(channel);

        produceSoundPlayed(ChannelID);
    
        return ChannelID;
    }

    return 0;
}

Real32 FModSound::getLength(void) const
{
    UInt32 ui_length(0);
    
    FMOD_RESULT result;
    result = _FModSound->getLength(&ui_length, FMOD_TIMEUNIT_MS);
    FMOD_ERRCHECK(result,"FModSound::getLength()");

    if(result == FMOD_OK)
    {
        return static_cast<Real32>(ui_length)/static_cast<Real32>(1000.0f);
    }
    else
    {
        return 0.0f;
    }
}

UInt32 FModSound::getNumChannels(void) const
{
    return _ChannelMap.size();
}

UInt32 FModSound::getNumPlayingChannels(void) const
{
    UInt32 Count(0);
    
    for(ChannelMap::const_iterator SearchItor = _ChannelMap.begin() ;
        SearchItor != _ChannelMap.end() ;
        ++SearchItor)
    {
        if(isPlaying(SearchItor->first))
        {
            ++Count;
        }
    }
    return Count;
}

bool FModSound::isPlaying(UInt32 ChannelID) const
{
    bool playing(false);
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;
        result = channel->isPlaying(&playing);
        FMOD_ERRCHECK(result,"FModSound::isPlaying()");
    }
    
    return playing;
    
}

bool FModSound::isValid(UInt32 ChannelID) const
{
    FMOD::Channel* channel(getChannel(ChannelID));
    return channel != NULL;
}

void FModSound::stop(UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL && isPlaying(ChannelID))
    {
        FMOD_RESULT result;
        result = channel->stop();
        FMOD_ERRCHECK(result,"FModSound::stop()");
        if(result == FMOD_OK)
        {
            produceSoundStopped(ChannelID);
        }
    }
}

void FModSound::pause(UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL && isPlaying(ChannelID) && !isPaused(ChannelID))
    {
        FMOD_RESULT result;
        result = channel->setPaused(true);
        FMOD_ERRCHECK(result,"FModSound::pause()");
        if(result == FMOD_OK)
        {
            produceSoundPaused(ChannelID);
        }
    }
}

void FModSound::unpause(UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL && isPaused(ChannelID))
    {
        FMOD_RESULT result;
        result = channel->setPaused(false);
        FMOD_ERRCHECK(result,"FModSound::unpause()");
        if(result == FMOD_OK)
        {
            produceSoundUnpaused(ChannelID);
        }
    }
}

void FModSound::pauseToggle(UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL && isPaused(ChannelID))
    {
        unpause(ChannelID);
    }
    else
    {
        pause(ChannelID);
    }
}

bool FModSound::isPaused(UInt32 ChannelID) const
{
    bool paused(false);
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;
        result = channel->getPaused(&paused);
        FMOD_ERRCHECK(result,"FModSound::isPause()");
    }
    
    return paused;
}



void FModSound::seek(Real32 pos, UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        unsigned int position(pos * 1000.0);

        FMOD_RESULT result;
        result = channel->setPosition(position, FMOD_TIMEUNIT_MS);
        FMOD_ERRCHECK(result,"FModSound::seek()");
    }
}

Real32 FModSound::getTime(UInt32 ChannelID) const
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        unsigned int position;
        FMOD_RESULT result;
        result = channel->getPosition(&position, FMOD_TIMEUNIT_MS);
        FMOD_ERRCHECK(result,"FModSound::getTime()");
        
        if(result == FMOD_OK)
        {
            return static_cast<Real32>(position)/static_cast<Real32>(1000.0f);
        }
    }
    return 0.0f;
}

void FModSound::setChannelPosition(const Pnt3f &pos, UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;

        FMOD_MODE TheMode;
        result = channel->getMode(&TheMode);
        FMOD_ERRCHECK(result,"FModSound::setChannelPosition()");
        if(result == FMOD_OK && TheMode & FMOD_3D)
        {
            FMOD_VECTOR curPos;
            FMOD_VECTOR curVec;

            result = channel->get3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::setChannelPosition()");

            curPos.x = pos.x();
            curPos.y = pos.y();
            curPos.z = pos.z();

            result = channel->set3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::setChannelPosition()");
        }
    }
}

Pnt3f FModSound::getChannelPosition(UInt32 ChannelID) const
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;

        FMOD_MODE TheMode;
        result = channel->getMode(&TheMode);
        FMOD_ERRCHECK(result,"FModSound::getChannelPosition()");
        if(result == FMOD_OK && TheMode & FMOD_3D)
        {
            FMOD_VECTOR curPos;
            FMOD_VECTOR curVec;

            result = channel->get3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::getChannelPosition()");

            return Vec3f(curPos.x, curPos.y, curPos.z);
        }
        else
        {
            SWARNING << "FModSound: This channel is not an FMOD_3D" << std::endl;
        }
    }
    return Vec3f(0.0f,0.0f,0.0f);
}

void FModSound::setChannelVelocity(const Vec3f &vec, UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;

        FMOD_MODE TheMode;
        result = channel->getMode(&TheMode);
        FMOD_ERRCHECK(result,"FModSound::setChannelVelocity()");
        if(result == FMOD_OK && TheMode & FMOD_3D)
        {
            FMOD_VECTOR curPos;
            FMOD_VECTOR curVec;

            result = channel->get3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::setChannelVelocity()");

            curVec.x = vec.x();
            curVec.y = vec.y();
            curVec.z = vec.z();

            result = channel->set3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::setChannelVelocity()");
        }
    }
}

Vec3f FModSound::getChannelVelocity(UInt32 ChannelID) const
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;

        FMOD_MODE TheMode;
        result = channel->getMode(&TheMode);
        FMOD_ERRCHECK(result,"FModSound::getChannelVelocity()");
        if(result == FMOD_OK && TheMode & FMOD_3D)
        {
            FMOD_VECTOR curPos;
            FMOD_VECTOR curVec;

            result = channel->get3DAttributes(&curPos, &curVec);
            FMOD_ERRCHECK(result,"FModSound::getChannelVelocity()");

            return Vec3f(curVec.x, curVec.y, curVec.z);
        }
        else
        {
            SWARNING << "FModSound: This channel is not an FMOD_3D" << std::endl;
        }
    }
    return Vec3f(0.0f,0.0f,0.0f);
}

void FModSound::setChannelVolume(Real32 volume, UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;
        result = channel->setVolume(volume);
        FMOD_ERRCHECK(result,"FModSound::setChannelVolume()");
    }
}

Real32 FModSound::getChannelVolume(UInt32 ChannelID) const
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        float  volume;

        FMOD_RESULT result;
        result = channel->getVolume(&volume);
        FMOD_ERRCHECK(result,"FModSound::getChannelVolume()");
        
        if(result == FMOD_OK)
        {
            return static_cast<Real32>(volume);
        }
    }
    return 0.0f;
}

bool FModSound::getMute(UInt32 ChannelID) const
{
    bool muteValue(false);
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;
        result = channel->getMute(&muteValue);
        FMOD_ERRCHECK(result,"FModSound::getMute()");
    }
    
    return muteValue;
}

void FModSound::mute(bool shouldMute, UInt32 ChannelID)
{
    FMOD::Channel* channel(getChannel(ChannelID));
    if(channel != NULL)
    {
        FMOD_RESULT result;
        result = channel->setMute(shouldMute);
        FMOD_ERRCHECK(result,"FModSound::mute()");
    }
}

void FModSound::soundEnded(FMOD::Channel *channel)
{
    UInt32 ChannelID(getChannelID(channel));

    if(ChannelID != 0)
    {
        removeChannel(ChannelID);
        produceSoundEnded(ChannelID);
    }
}

UInt32 FModSound::generateChannelID(void) const
{
    UInt32 NewID;//
    if(_ChannelMap.size() == 0)
    {
        NewID = 1;
    }
    else
    {
        NewID = (--_ChannelMap.end())->first+1;
    }
    while(_ChannelMap.find(NewID) != _ChannelMap.end())
    {
        if(NewID == TypeTraits<UInt32>::getMax())
        {
            NewID = 1;
        }
        else
        {
            ++NewID;
        }
    }
    return NewID;
}

FMOD::Channel* FModSound::getChannel(UInt32 ChannelID) const
{
    ChannelMap::const_iterator SearchItor = _ChannelMap.find(ChannelID);
    if(SearchItor != _ChannelMap.end())
    {
        return SearchItor->second;
    }
    else
    {
        return NULL;
    }
}

UInt32 FModSound::addChannel(FMOD::Channel* channel)
{
    
    FMOD_RESULT result;
    result = channel->setCallback(FModSoundChannelCallback);
    FMOD_ERRCHECK(result,"FModSound::addChannel()");
    result = channel->setUserData(this);
    FMOD_ERRCHECK(result,"FModSound::addChannel()");

    UInt32 NewID(generateChannelID());
    _ChannelMap[NewID] = channel;
    return NewID;
}

void FModSound::removeChannel(UInt32 ChannelID)
{
    _ChannelMap.erase(ChannelID);
}

UInt32 FModSound::getChannelID(FMOD::Channel* channel) const
{
    for(ChannelMap::const_iterator SearchItor = _ChannelMap.begin() ;
        SearchItor != _ChannelMap.end() ;
        ++SearchItor)
    {
        if(SearchItor->second == channel)
        {
            return SearchItor->first;
        }
    }
    return 0;
}


void FModSound::setAllChannelsVolume(Real32 volume)
{
    for(ChannelMap::iterator SearchItor = _ChannelMap.begin() ;
        SearchItor != _ChannelMap.end() ;
        ++SearchItor)
    {
        setChannelVolume(volume, SearchItor->first);
    }
}

void FModSound::stopAllChannels(void)
{
    ChannelMap TheChannelMap(_ChannelMap);
    for(ChannelMap::iterator SearchItor = TheChannelMap.begin() ;
        SearchItor != TheChannelMap.end() ;
        ++SearchItor)
    {
        stop(SearchItor->first);
    }
}

void FModSound::setAllChannelPaused(bool paused)
{
    for(ChannelMap::iterator SearchItor = _ChannelMap.begin() ;
        SearchItor != _ChannelMap.end() ;
        ++SearchItor)
    {
        if(paused)
        {
            pause(SearchItor->first);
        }
        else
        {
            unpause(SearchItor->first);
        }
    }
}

void FModSound::setAllChannelMute(bool shouldMute)
{
    for(ChannelMap::iterator SearchItor = _ChannelMap.begin() ;
        SearchItor != _ChannelMap.end() ;
        ++SearchItor)
    {
        mute(shouldMute, SearchItor->first);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FModSound::FModSound(void) :
    Inherited(),
    _FModSound(NULL)
{
}

FModSound::FModSound(const FModSound &source) :
    Inherited(source),
    _FModSound(NULL)
{
}

FModSound::~FModSound(void)
{
    if(!_FModSound)
    {
        FMOD_RESULT result;
        result = _FModSound->release();
        FMOD_ERRCHECK(result,"FModSound::~FModSound()");
    }
}

/*----------------------------- class specific ----------------------------*/

void FModSound::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & FileFieldMask)
    {
        if(!boost::filesystem::exists(getFile()))
		{
			SWARNING << "FModSound: error loading sound from file: " << getFile().string() << " This file does not exist." << std::endl;
		}
		else
        {
            FMOD_RESULT      result;
            FMOD_MODE soundMode(FMOD_DEFAULT);
            if(getEnable3D())
            {
                soundMode |= FMOD_3D;
            }
            //soundMode |= FMOD_NONBLOCKING;
            if(getLooping() != 0)
            {
                soundMode |= FMOD_LOOP_NORMAL | FMOD_SOFTWARE;
            }
            else
            {
                soundMode |= FMOD_HARDWARE;
            }

            if(getStreaming())
            {
                result = FModSoundManager::the()->getSystem()->createStream(getFile().string().c_str(), soundMode, 0, &_FModSound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
            }
            else
            {
                result = FModSoundManager::the()->getSystem()->createSound(getFile().string().c_str(), soundMode, 0, &_FModSound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
            }
            FMOD_ERRCHECK(result,"FModSound::changed()");

            if(result != FMOD_OK)
            {
                if(getStreaming())
                {
                    result = FModSoundManager::the()->getSystem()->createStream(getFile().string().c_str(), FMOD_SOFTWARE, 0, &_FModSound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
                }
                else
                {
                    result = FModSoundManager::the()->getSystem()->createSound(getFile().string().c_str(), FMOD_SOFTWARE, 0, &_FModSound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
                }
            }
            FMOD_ERRCHECK(result,"FModSound::changed()");
        }
    }
    if(whichField & VolumeFieldMask ||
        whichField & PanFieldMask ||
        whichField & FrequencyFieldMask)
    {
        FMOD_RESULT      result;
        result = _FModSound->setDefaults(getFrequency(), getVolume(),getPan(), 128);
        FMOD_ERRCHECK(result,"FModSound::changed()");
    }
    if(whichField & LoopingFieldMask)
    {
        FMOD_RESULT      result;
        result = _FModSound->setLoopCount(getLooping());
        FMOD_ERRCHECK(result,"FModSound::changed()");
    }
}

void FModSound::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FModSound NI" << std::endl;
}

OSG_END_NAMESPACE
