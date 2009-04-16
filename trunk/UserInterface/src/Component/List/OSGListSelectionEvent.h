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
#ifndef _OSG_UI_LIST_SELECTION_EVENT_H_
#define _OSG_UI_LIST_SELECTION_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ListSelectionEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
   //Returns the index of the first row whose selection may have changed.
   Int32 	getFirstIndex() const;
   //Returns the index of the last row whose selection may have changed.
   Int32 	getLastIndex() const;
   //Returns true if this is one of multiple change events
   bool 	getValueIsAdjusting() const;
    
    ListSelectionEvent(FieldContainerPtr Source, Time TimeStamp, Int32 FirstIndex, Int32 LastIndex, bool ValueIsAdjusting);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
     Int32 _FirstIndex;
     Int32 _LastIndex;
     bool _ValueIsAdjusting;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGListSelectionEvent.inl"

#endif /* _OSG_UI_LIST_SELECTION_EVENT_H_ */
