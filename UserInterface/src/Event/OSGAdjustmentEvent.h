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
#ifndef _OSGADJUSTMENTEVENT_H_
#define _OSGADJUSTMENTEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING AdjustmentEvent : public Event
{
/*=========================  PUBLIC  ===============================*/
public:
    enum EventEnum{ADJUSTMENT_VALUE_CHANGED=0, BLOCK_DECREMENT, BLOCK_INCREMENT, UNIT_DECREMENT, UNIT_INCREMENT, TRACK};

    EventEnum getEvent(void) const;
    UInt32 getValue(void) const;
    bool getValueIsAdjusting(void) const;

    AdjustmentEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, UInt32 Value, bool ValueIsAdjusting);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
protected:
    EventEnum _Event;
    UInt32 _Value;
    bool _ValueIsAdjusting;
  private:
     static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGAdjustmentEvent.inl"

#endif /* _OSGADJUSTMENTEVENT_H_ */
