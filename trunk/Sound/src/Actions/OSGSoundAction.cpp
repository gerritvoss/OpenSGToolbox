/*---------------------------------------------------------------------------*\
 *                          OpenSG Animation                                 *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, freeman                                          *
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

#include "OSGSoundAction.h"


OSG_USING_NAMESPACE

void SoundAction::triggerAction(){
  if (sound == NULL) return;
  switch (type){
  case SoundAction::PLAY: sound->play(); break;
  case SoundAction::PAUSE: sound->pause(channel); break;
  case SoundAction::UNPAUSE: sound->unpause(channel); break;
  case SoundAction::STOP: sound->stop(channel); break;
  case SoundAction::MUTE: sound->mute(1, channel); break;
  case SoundAction::UNMUTE: sound->mute(0, channel); break;
  };
}

const ActionType& SoundAction::getType(){
  static ActionType type("Sound Action", "");
  return type;
}


void SoundAction::setSound(SoundPtr sound){
  this->sound = sound;
}
    
SoundPtr SoundAction::getSound(void){
  return sound;
}


void SoundAction::setActionType(SoundAction::Type type){
  this->type = type;
}
    
SoundAction::Type SoundAction::getActionType(void){
  return type;
}

void SoundAction::setChannel(UInt32 channel){
  this->channel = channel;
}
    
UInt32 SoundAction::getChannel(void){
  return channel;
}
