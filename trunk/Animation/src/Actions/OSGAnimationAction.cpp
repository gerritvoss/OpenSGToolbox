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

#include "OSGAnimationAction.h"


OSG_USING_NAMESPACE

void AnimationAction::triggerAction(){
  if (animation == NULL) return;
  //switch (type){
  //case AnimationAction::PAUSE: animation->pause(); break;
  //case AnimationAction::PAUSETOGGLE: animation->pauseToggle(); break;
  //case AnimationAction::UNPAUSE: animation->unpause(); break;
  //case AnimationAction::STOP: animation->stop(); break;
  //};
}

const ActionType& AnimationAction::getType(){
  static ActionType type("Animation Action", "");
  return type;
}


void AnimationAction::setAnimation(AnimationPtr animation){
  this->animation = animation;
}
    
AnimationPtr AnimationAction::getAnimation(void){
  return animation;
}


void AnimationAction::setActionType(AnimationAction::Type type){
  this->type = type;
}
    
AnimationAction::Type AnimationAction::getActionType(void){
  return type;
}
