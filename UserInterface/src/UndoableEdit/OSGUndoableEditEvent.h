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
#ifndef _OSG_UI_UNDOABLE_EDIT_EVENT_H_
#define _OSG_UI_UNDOABLE_EDIT_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "OSGUndoableEdit.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING UndoableEditEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
    UndoableEditPtr getUndoableEdit(void) const;
    
    UndoableEditEvent(FieldContainerPtr Source, Time TimeStamp, UndoableEditPtr UndoableEdit);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
     UndoableEditPtr _UndoableEdit;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGUndoableEditEvent.inl"

#endif /* _OSG_UI_UNDOABLE_EDIT_EVENT_H_ */
