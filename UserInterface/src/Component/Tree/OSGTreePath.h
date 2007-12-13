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

#ifndef _OSG_UI_TREE_PATH_H_
#define _OSG_UI_TREE_PATH_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

#include <vector>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING TreePath
{
private:
protected:
	//Primarily provided for subclasses that represent paths in a different manner.
	TreePath(void);

	//Constructs a new TreePath with the identified path components of length length.
	TreePath(std::vector<SharedFieldPtr> path, const UInt32& length);

	//Constructs a new TreePath, which is the path identified by parent ending in lastElement.
	TreePath(TreePath parent, SharedFieldPtr lastElement);

	std::vector<SharedFieldPtr> _Path;

public:
	//Tests two TreePaths for equality by checking each element of the paths for equality.
	bool operator==(const TreePath& Right) const;

	//Returns the last component of this path.
	SharedFieldPtr getLastPathComponent(void) const;

	//Returns a path containing all the elements of this object, except the last path component.
	TreePath getParentPath(void) const;

	//Returns an ordered array of Objects containing the components of this TreePath.
	std::vector<SharedFieldPtr> getPath(void) const;

	//Returns the path component at the specified index.
	SharedFieldPtr getPathComponent(const UInt32& Index) const;

	//Returns the number of elements in the path.
	UInt32 getPathCount(void) const;

	//Returns true if aTreePath is a descendant of this TreePath.
	bool isDescendant(TreePath aTreePath) const;

	//Returns a new path containing all the elements of this object plus child.
	TreePath pathByAddingChild(SharedFieldPtr child) const;

	//Constructs a TreePath containing only a single element.
	TreePath(SharedFieldPtr singlePath);

	//Constructs a path from an array of Objects, uniquely identifying the path from the root of the tree to a specific node, as returned by the tree's data model.
	TreePath(std::vector<SharedFieldPtr> path);

};

typedef TreePath* TreePathPtr;

OSG_END_NAMESPACE

#include "OSGTreePath.inl"

#endif /* _OSG_UI_TREE_PATH_H_ */

