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

#include "OSGStubSound.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StubSound
A stub Sound Interface.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StubSound::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 StubSound::play(void)
{
    SWARNING << "StubSound played" << std::endl;
    return 0;
}

Real32 StubSound::getLength(void) const
{
    return 0.0;
}

UInt32 StubSound::getNumChannels(void) const
{
    return 0;
}

UInt32 StubSound::getNumPlayingChannels(void) const
{
    return 0;
}

bool StubSound::isPlaying(UInt32 ChannelID) const
{
    return false;
}

bool StubSound::isValid(UInt32 ChannelID) const
{
    return false;
}

void StubSound::stop(UInt32 ChannelID)
{
}


void StubSound::pause(UInt32 ChannelID)
{
}

void StubSound::unpause(UInt32 ChannelID)
{
}

void StubSound::pauseToggle(UInt32 ChannelID)
{
}

bool StubSound::isPaused(UInt32 ChannelID) const
{
    return false;
}



void StubSound::seek(Real32 pos, UInt32 ChannelID)
{
}

Real32 StubSound::getTime(UInt32 ChannelID) const
{
    return 0.0f;
}

void StubSound::setChannelPosition(const Pnt3f &pos, UInt32 ChannelID)
{
}

Pnt3f StubSound::getChannelPosition(UInt32 ChannelID) const
{
    return Pnt3f();
}

void StubSound::setChannelVelocity(const Vec3f &vec, UInt32 ChannelID)
{
}

Vec3f StubSound::getChannelVelocity(UInt32 ChannelID) const
{
    return Vec3f();
}


void StubSound::setChannelVolume(Real32 volume, UInt32 ChannelID)
{
}

Real32 StubSound::getChannelVolume(UInt32 ChannelID) const
{
    return 0.0f;
}

bool StubSound::getMute(UInt32 ChannelID) const
{
    return false;
}

void StubSound::mute(bool shouldMute, UInt32 ChannelID)
{
}

void StubSound::setAllChannelsVolume(Real32 volume)
{
}

void StubSound::stopAllChannels(void)
{
}

void StubSound::setAllChannelPaused(bool paused)
{
}

void StubSound::setAllChannelMute(bool shouldMute)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StubSound::StubSound(void) :
    Inherited()
{
}

StubSound::StubSound(const StubSound &source) :
    Inherited(source)
{
}

StubSound::~StubSound(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StubSound::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StubSound::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StubSound NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSTUBSOUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTUBSOUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTUBSOUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

