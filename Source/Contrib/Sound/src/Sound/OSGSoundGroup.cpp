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

#include "OSGSoundGroup.h"
#include "OSGSound.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGSoundGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundGroup::stop(void)
{
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        getSounds(i)->stopAllChannels();
    }
}

void SoundGroup::pause(void)
{
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        getSounds(i)->setAllChannelPaused(true);
    }
}

void SoundGroup::unpause(void)
{
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        getSounds(i)->setAllChannelPaused(false);
    }
}

Real32 SoundGroup::getVolume(void) const
{
    Real32 Sum(0.0f);
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        Sum += getSounds(i)->getVolume();
    }

    return Sum/static_cast<Real32>(getMFSounds()->size());
}

void SoundGroup::mute(bool muted)
{
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        getSounds(i)->setAllChannelMute(muted);
    }
}

void SoundGroup::setVolume(Real32 volume)
{
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        getSounds(i)->setAllChannelsVolume(volume);
        getSounds(i)->setVolume(volume);
    }
}

UInt32 SoundGroup::getNumSounds(void) const
{
    return getMFSounds()->size();
}

UInt32 SoundGroup::getNumPlayingSounds(void) const
{
    UInt32 Count(0);
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        if(getSounds(i)->getNumPlayingChannels() > 0)
        {
            ++Count;
        }
    }
    return Count;
}

UInt32 SoundGroup::getNumPlayingChannels(void) const
{
    UInt32 Count(0);
    for(UInt32 i(0) ; i<getMFSounds()->size() ; ++i)
    {
        Count += getSounds(i)->getNumPlayingChannels();
    }
    return Count;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SoundGroup::SoundGroup(void) :
    Inherited()
{
}

SoundGroup::SoundGroup(const SoundGroup &source) :
    Inherited(source)
{
}

SoundGroup::~SoundGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundGroup::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SoundGroup::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SoundGroup NI" << std::endl;
}

OSG_END_NAMESPACE
