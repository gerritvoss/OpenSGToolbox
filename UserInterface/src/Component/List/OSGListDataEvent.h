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
#ifndef _OSG_UI_LIST_DATA_EVENT_H_
#define _OSG_UI_LIST_DATA_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "OSGListModel.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ListDataEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
      enum EventEnum {CONTENTS_CHANGED, INTERVAL_ADDED, INTERVAL_REMOVED};

      //Returns the lower index of the range.
      UInt32 	getIndex0(void) const;
      //Returns the upper index of the range.
      UInt32 	getIndex1(void) const;
      //Returns the event type.
      EventEnum 	getEventEnum(void) const;
      //Returns the event type.
      ListModelPtr 	getModel(void) const;
    
    ListDataEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 Index0, UInt32 Index1, EventEnum Type, ListModelPtr Model);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
     UInt32 _Index0;
     UInt32 _Index1;
     EventEnum _EventEnum;
	 ListModelPtr _Model;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGListDataEvent.inl"

#endif /* _OSG_UI_LIST_DATA_EVENT_H_ */
