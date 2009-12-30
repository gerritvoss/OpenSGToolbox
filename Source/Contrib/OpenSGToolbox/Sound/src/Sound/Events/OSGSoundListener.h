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

#ifndef _OSGSOUNDLISTENER_H_
#define _OSGSOUNDLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#include <OpenSG/Toolbox/OSGEventListener.h>
#include "OSGSoundEvent.h"

OSG_BEGIN_NAMESPACE
//const SoundEvent& e
class SoundEvent;
class OSG_SOUNDLIB_DLLMAPPING SoundListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void soundPlayed(const SoundEventPtr e) = 0;
   virtual void soundStopped(const SoundEventPtr e) = 0;
   virtual void soundPaused(const SoundEventPtr e) = 0;
   virtual void soundUnpaused(const SoundEventPtr e) = 0;
   virtual void soundLooped(const SoundEventPtr e) = 0;
   virtual void soundEnded(const SoundEventPtr e) = 0;
};

typedef SoundListener* SoundListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGSOUNDLISTENER_H_ */
