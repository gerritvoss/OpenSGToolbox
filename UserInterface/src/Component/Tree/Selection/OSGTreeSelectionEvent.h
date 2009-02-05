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
#ifndef _OSG_UI_TREE_SELECTION_EVENT_H_
#define _OSG_UI_TREE_SELECTION_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "Util/OSGNumberRangeSet.h"
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING TreeSelectionEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
	enum EventEnum {CONTENTS_CHANGED, INTERVAL_ADDED, INTERVAL_REMOVED};

	//Returns a copy of the receiver, but with the source being newSource.
	//Object cloneWithSource(Object newSource) const;

	//Returns the current lead path.
	Int32 getNewLeadSelectionPath(void) const;

    //Returns the path that was previously the lead path.
	Int32 getOldLeadSelectionPath(void) const;

    //Returns a vector of the the elements changed
	const std::vector<NumberRange>& getElementsChanged(void) const;
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
    
	TreeSelectionEvent(FieldContainerPtr Source, Time TimeStamp, const std::vector<NumberRange>& ElementsChanged, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath);
  protected:
     Int32 _NewLeadSelectionPath;
     Int32 _OldLeadSelectionPath;
     std::vector<NumberRange> _ElementsChanged;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGTreeSelectionEvent.inl"

#endif /* _OSG_UI_TREE_SELECTION_EVENT_H_ */
