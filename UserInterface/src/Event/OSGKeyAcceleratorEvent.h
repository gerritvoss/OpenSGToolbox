/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
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
#ifndef _OSGKEYACCELERATOREVENT_H_
#define _OSGKEYACCELERATOREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include <OpenSG/Input/OSGKeyEvent.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING KeyAcceleratorEvent : public Event
{
/*=========================  PUBLIC  ===============================*/
public:
    enum EventType{KEYACCELERATOR_TRIGGERED=0};

    EventType getEvent(void) const;
	UInt32 getModifiers(void) const;
    KeyEvent::Key getKey(void) const;
    WindowPtr getWindow(void) const;

    KeyAcceleratorEvent(FieldContainerPtr Source, Time TimeStamp, KeyEvent::Key TheKey, UInt32 Modifiers, WindowPtr TheWindow, EventType TheEvent = KEYACCELERATOR_TRIGGERED);
private:
    EventType _Event;
    
    KeyEvent::Key _Key;
    UInt32 _Modifiers;
    WindowPtr _Window;
};

OSG_END_NAMESPACE

#include "OSGKeyAcceleratorEvent.inl"

#endif /* _OSGKEYACCELERATOREVENT_H_ */
