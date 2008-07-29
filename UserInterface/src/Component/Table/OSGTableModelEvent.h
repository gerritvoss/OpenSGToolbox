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

#ifndef _OSG_UI_TABLE_MODEL_EVENT_H_
#define _OSG_UI_TABLE_MODEL_EVENT_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "Component/Table/Models/OSGTableModelFields.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING TableModelEvent : public Event
{
  private:
     static EventType _Type;
protected:
    UInt32 _FirstColumn,
           _LastColumn,
           _FirstRow,
           _LastRow;

    UInt32 _EventType;

    TableModelPtr _Model;
    
public:
    enum EventEnum {CONTENTS_CHANGED, INTERVAL_ADDED, INTERVAL_REMOVED, HEADER_ROW_CHANGED};

    //Returns the first column that changed
    const UInt32& getFirstColumn(void) const;
    
    //Returns the first column that changed
    const UInt32& getLastColumn(void) const;

    //Returns the first row that changed.
    const UInt32& getFirstRow(void) const;

    //Returns the last row that changed.
    const UInt32& getLastRow(void) const;

    //Returns the type of event - one of: INSERT, UPDATE and DELETE.
    const UInt32& getEventType(void) const;
    
    //The Model that the Event originated from
    TableModelPtr& getModel(void);

    //Constructor
    TableModelEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow, EventEnum Type, TableModelPtr Model);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
};

OSG_END_NAMESPACE

#include "OSGTableModelEvent.inl"

#endif /* _OSG_UI_TABLE_MODEL_EVENT_H_ */

