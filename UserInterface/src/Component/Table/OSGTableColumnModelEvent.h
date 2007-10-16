/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSG_UI_TABLE_COLUMN_MODEL_EVENT_H_
#define _OSG_UI_TABLE_COLUMN_MODEL_EVENT_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "OSGTableColumnModel.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING TableColumnModelEvent : public Event
{
private:
protected:
    UInt32 _FromIndex,
           _ToIndex;

    UInt32 _EventType;

    TableColumnModelPtr _Model;
    
public:
    enum EventType {COLUMN_MOVED, COLUMN_ADDED, COLUMN_REMOVED};

    //The index of the column from where it was moved or removed
    const UInt32& getFromIndex(void) const;
    
    //The index of the column to where it was moved or added from
    const UInt32& getToIndex(void) const;

    //Returns the type of event - one of: INSERT, UPDATE and DELETE.
    const UInt32& getEventType(void) const;
    
    //The Model that the Event originated from
    TableColumnModelPtr& getModel(void);

    //Constructor
    TableColumnModelEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FromIndex, UInt32 ToIndex, EventType Type, TableColumnModelPtr Model);
};

OSG_END_NAMESPACE

#include "OSGTableColumnModelEvent.inl"

#endif /* _OSG_UI_TABLE_COLUMN_MODEL_EVENT_H_ */

