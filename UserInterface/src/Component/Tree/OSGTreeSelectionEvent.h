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
#ifndef _OSG_UI_TREE_SELECTION_EVENT_H_
#define _OSG_UI_TREE_SELECTION_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include "OSGTreePath.h"
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
	TreePath getNewLeadSelectionPath(void) const;

	//Returns the path that was previously the lead path.
	TreePath getOldLeadSelectionPath(void) const;

	//Returns the first path element.
	TreePath getPath(void) const;

	//Returns the paths that have been added or removed from the selection.
	std::vector<TreePath> getPaths(void) const;

	//Returns true if the first path element has been added to the selection, a return value of false means the first path has been removed from the selection.
	bool isAddedPath(void) const;

	//Returns true if the path identified by index was added to the selection.
	bool isAddedPath(const UInt32& index) const;

	//Returns true if the path identified by path was added to the selection.
	bool isAddedPath(const TreePath& path) const;
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGTreeSelectionEvent.inl"

#endif /* _OSG_UI_TREE_SELECTION_EVENT_H_ */
