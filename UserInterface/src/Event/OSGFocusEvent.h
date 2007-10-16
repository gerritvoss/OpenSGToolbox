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
#ifndef _OSGFOCUSEVENT_H_
#define _OSGFOCUSEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>

#include "Component/OSGComponentFields.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING FocusEvent : public Event
{
/*=========================  PUBLIC  ===============================*/
public:
    enum EventEnum{FOCUS_GAINED=0, FOCUS_LOST=1};

    EventEnum getEvent(void) const;
    bool getTemporary(void) const;
    ComponentPtr getOpposite(void) const;

    FocusEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, bool Temporary, ComponentPtr Opposite);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
protected:
    EventEnum _Event;
    bool _Temporary;
    ComponentPtr _Opposite;
  private:
     static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGFocusEvent.inl"

#endif /* _OSGFOCUSEVENT_H_ */
