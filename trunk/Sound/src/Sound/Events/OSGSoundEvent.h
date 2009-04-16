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
#ifndef _OSGSOUNDEVENT_H_
#define _OSGSOUNDEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "Sound/OSGSound.h"

OSG_BEGIN_NAMESPACE

class OSG_SOUNDLIB_DLLMAPPING SoundEvent : public Event
{
  /*=========================  PUBLIC  ===============================*/
  public:

   SoundEvent(FieldContainerPtr Source, Time TimeStamp,
	   SoundPtr TheSound);

    virtual const EventType &getType(void) const;
    SoundPtr getSound(void) const;
    
    static const EventType &getClassType(void);
  private:
     static EventType _Type;

	 SoundPtr _Sound;
};

OSG_END_NAMESPACE

#include "OSGSoundEvent.inl"

#endif /* _OSGSOUNDEVENT_H_ */
