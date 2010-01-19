/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
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

#include "OSGSoundActivity.h"
#include "Sound/OSGSound.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SoundActivity

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundActivity::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundActivity::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    if (getSound() == NullFC) return;
    switch (getActivityType()){
        case SOUND_PLAY:
            getSound()->play();
            break;
        case SOUND_STOP:
            getSound()->stopAllChannels();
            //getSound()->stopAllChannels(getChannel());
            break;
        case SOUND_PAUSE: 
            getSound()->setAllChannelPaused(true);
            //getSound()->setAllChannelPaused(getChannel());
            break;
        case SOUND_UNPAUSE:
            getSound()->setAllChannelPaused(false);
            //getSound()->unpause(getChannel());
            break;
        case SOUND_MUTE:
            getSound()->setAllChannelMute(true);
            //getSound()->mute(true,getChannel());
            break;
        case SOUND_UNMUTE:
            getSound()->setAllChannelMute(false);
            //getSound()->mute(false,getChannel());
            break;
        default:
            SWARNING << "SoundActivity::eventProduced(): Unknown Activity Type: " << getActivityType() << std::endl;
            break;
    };
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SoundActivity::SoundActivity(void) :
    Inherited()
{
}

SoundActivity::SoundActivity(const SoundActivity &source) :
    Inherited(source)
{
}

SoundActivity::~SoundActivity(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundActivity::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SoundActivity::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SoundActivity NI" << std::endl;
}


OSG_END_NAMESPACE

