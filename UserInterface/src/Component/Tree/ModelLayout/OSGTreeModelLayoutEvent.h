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
#ifndef _OSG_UI_TREE_MODEL_LAYOUT_EVENT_H_
#define _OSG_UI_TREE_MODEL_LAYOUT_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "Component/Tree/OSGTreePath.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING TreeModelLayoutEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
	enum EventEnum {TREE_EXPANDED, TREE_COLLAPSED, TREE_WILL_EXPAND, TREE_WILL_COLLAPSE};

	TreePath getPath(void) const;
    
    EventEnum getEvent(void) const;

	TreeModelLayoutEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, TreePath path);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
  private:
     static EventType _Type;

     EventEnum _Event;
     TreePath _Path;
};

OSG_END_NAMESPACE

#include "OSGTreeModelLayoutEvent.inl"

#endif /* _OSG_UI_TREE_MODEL_LAYOUT_EVENT_H_ */
