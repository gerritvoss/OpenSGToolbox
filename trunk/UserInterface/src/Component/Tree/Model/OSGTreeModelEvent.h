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
#ifndef _OSG_UI_TREE_MODEL_EVENT_H_
#define _OSG_UI_TREE_MODEL_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Toolbox/OSGEvent.h>
#include "OSGTreeModel.h"
#include "Component/Tree/OSGTreePath.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING TreeModelEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
	enum EventEnum {CONTENTS_CHANGED, INTERVAL_ADDED, INTERVAL_REMOVED};

	//Returns the values of the child indexes.
	const std::vector<UInt32>& getChildIndices(void) const;

	//Returns the objects that are children of the node identified by getPath at the locations specified by getChildIndices.
	const std::vector<boost::any>& getChildren(void) const;

	//For all events, except treeStructureChanged, returns the parent of the changed nodes.
	const TreePath& getPath(void) const;

	//Used to create an event when the node structure has changed in some way, identifying the path to the root of a modified subtree as an array of Objects.
	TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, const TreePath&);

	//Used to create an event when nodes have been changed, inserted, or removed, identifying the path to the parent of the modified items as an array of Objects.
	TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, const TreePath&, const std::vector<UInt32>& childIndices, const std::vector<boost::any>& children);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
  private:
     static EventType _Type;

     TreePath _Path;
     std::vector<boost::any> _Children;
     std::vector<UInt32> _ChildIndices;
    
};

OSG_END_NAMESPACE

#include "OSGTreeModelEvent.inl"

#endif /* _OSG_UI_TREE_MODEL_EVENT_H_ */
