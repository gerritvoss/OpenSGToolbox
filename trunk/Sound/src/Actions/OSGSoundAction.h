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

#ifndef _SOUNDACTION_H_
#define _SOUNDACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/Toolbox/OSGAction.h>

#include <OpenSG/Toolbox/OSGActionType.h>
#include <Sound/OSGSound.h>

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

/**
 * This class interface Aniamtion through Action. This single class is responsible for different action
 * for the sound which is set by the type. See getActionType() and setActionType() for more details
 */
class OSG_SOUNDLIB_DLLMAPPING SoundAction : public Action 
{
/*=========================  PUBLIC  ===============================*/
  public:

   /**
   *@param the Channel associated with this action
   *
   */
  void setChannel(UInt32 channel);
  
  /**
   *
   *@return Channel associated with this action
   */
  UInt32 getChannel(void);


  /**
   * Triggering this sound, behavior debpends on the action type and sound
   */
  virtual void triggerAction(void);
  
  /**
   *@return actionType discribing the current action
   *
   */
  virtual const ActionType &getType(void);
  
  /**
   *@param the sound associated with this action
   *
   */
  void setSound(SoundPtr sound);
  
  /**
   *
   *@return sound associated with this action
   */
  SoundPtr getSound(void);


  
  /**
   * Switch between different anmation action type, direct mapping from Sound
   */
  enum Type{
    PLAY,
    STOP,
    PAUSE,
    UNPAUSE,
    MUTE,
    UNMUTE,
  };
  
  /**
   *@param type behavior of the action
   */
  void setActionType(Type type);
  
  /**
   *@return type behavior of the action
   */
  Type getActionType(void);
  
 protected:
  SoundAction(void);
  
  SoundPtr sound;
  
  UInt32 channel;

  Type type;
};

typedef boost::shared_ptr<SoundAction> SoundActionPtr;

OSG_END_NAMESPACE

#endif /* _SOUNDACTION_H_ */
