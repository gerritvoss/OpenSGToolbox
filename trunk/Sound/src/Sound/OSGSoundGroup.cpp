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

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGSoundGroup.h"
#include "OSGSound.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SoundGroup
A SoundGroup. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundGroup::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundGroup::stop(void)
{
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        getSounds(i)->stopAllChannels();
    }
}

void SoundGroup::pause(void)
{
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        getSounds(i)->setAllChannelPaused(true);
    }
}

void SoundGroup::unpause(void)
{
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        getSounds(i)->setAllChannelPaused(false);
    }
}

void SoundGroup::mute(bool muted)
{
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        getSounds(i)->setAllChannelMute(muted);
    }
}

void SoundGroup::setVolume(Real32 volume)
{
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        getSounds(i)->setAllChannelsVolume(volume);
        beginEditCP(getSounds(i), Sound::VolumeFieldMask);
            getSounds(i)->setVolume(volume);
        beginEditCP(getSounds(i), Sound::VolumeFieldMask);
    }
}

UInt32 SoundGroup::getNumSounds(void) const
{
    return getSounds().size();
}

UInt32 SoundGroup::getNumPlayingSounds(void) const
{
    UInt32 Count(0);
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        if(getSounds()[i]->getNumPlayingChannels() > 0)
        {
            ++Count;
        }
    }
    return Count;
}

UInt32 SoundGroup::getNumPlayingChannels(void) const
{
    UInt32 Count(0);
    for(UInt32 i(0) ; i<getSounds().size() ; ++i)
    {
        Count += getSounds()[i]->getNumPlayingChannels();
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

void SoundGroup::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SoundGroup::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SoundGroup NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSOUNDGROUPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSOUNDGROUPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSOUNDGROUPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

