/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#ifndef _OSGCOMPONENTEVENT_H_
#define _OSGCOMPONENTEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>

#include "Component/OSGComponentFields.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ComponentEvent : public Event
{
/*=========================  PUBLIC  ===============================*/
public:
    enum EventEnum{COMPONENT_HIDDEN=0, COMPONENT_VISIBLE, COMPONENT_MOVED, COMPONENT_RESIZED, COMPONENT_ENABLED, COMPONENT_DISABLED};

    EventEnum getEvent(void) const;
    ComponentPtr getOriginator(void) const;

    ComponentEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, ComponentPtr Originator);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
protected:
    EventEnum _Event;
    ComponentPtr _Originator;
  private:
     static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGComponentEvent.inl"

#endif /* _OSGCOMPONENTEVENT_H_ */
