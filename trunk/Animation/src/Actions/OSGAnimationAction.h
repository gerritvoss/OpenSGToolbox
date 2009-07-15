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

#ifndef _ANIMATIONACTION_H_
#define _ANIMATIONACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/Toolbox/OSGAction.h>

#include <OpenSG/Toolbox/OSGActionType.h>
#include <Animations/OSGAnimation.h>

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

/**
 * This class interface Aniamtion through Action. This single class is responsible for different action
 * for the animation which is set by the type. See getActionType() and setActionType() for more details
 */
class OSG_ANIMATIONLIB_DLLMAPPING AnimationAction : public Action 
{
/*=========================  PUBLIC  ===============================*/
  public:
  /**
   * Triggering this animation, behavior debpends on the action type and animation
   */
  virtual void triggerAction(void);
  
  /**
   *@return actionType discribing the current action
   *
   */
  virtual const ActionType &getType(void);
  
  /**
   *@param the animation associated with this action
   *
   */
  void setAnimation(AnimationPtr animation);
  
  /**
   *
   *@return animation associated with this action
   */
  AnimationPtr getAnimation(void);
  
  /**
   * Switch between different anmation action type, direct mapping from Animation
   */
  enum Type{
    PAUSE,
    UNPAUSE,
    PAUSETOGGLE,
    STOP
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
  AnimationAction(void);
  
  AnimationPtr animation;
  
  Type type;
};

typedef boost::shared_ptr<AnimationAction> AnimationActionPtr;

OSG_END_NAMESPACE

#endif /* _ANIMATIONACTION_H_ */


