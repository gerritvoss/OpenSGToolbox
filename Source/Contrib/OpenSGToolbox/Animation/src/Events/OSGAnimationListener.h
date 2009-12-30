/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Animation                               *
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
 * by the Free Software Foundation, version 3.                               *
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

#ifndef _OSGANIMATIONLISTENER_H_
#define _OSGANIMATIONLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include <OpenSG/Toolbox/OSGEventListener.h>
#include "OSGAnimationEvent.h"

OSG_BEGIN_NAMESPACE

class AnimationEvent;
class OSG_ANIMATIONLIB_DLLMAPPING AnimationListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void animationStarted(const AnimationEventPtr e) = 0;
   virtual void animationStopped(const AnimationEventPtr e) = 0;
   virtual void animationPaused(const AnimationEventPtr e) = 0;
   virtual void animationUnpaused(const AnimationEventPtr e) = 0;
   virtual void animationEnded(const AnimationEventPtr e) = 0;
   virtual void animationCycled(const AnimationEventPtr e) = 0;
};

typedef AnimationListener* AnimationListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGANIMATIONLISTENER_H_ */


