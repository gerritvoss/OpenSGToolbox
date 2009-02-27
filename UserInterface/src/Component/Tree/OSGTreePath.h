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
#include <boost/any.hpp>

#include <OpenSG/OSGBaseTypes.h>
#include <vector>


OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING TreePath
{

public:
    struct NodePairType
    {
        boost::any _NodeValue;
        UInt32     _NodeIndex;

        NodePairType(const boost::any& Value, UInt32 Index);
        NodePairType(const NodePairType& Value);
        NodePairType(void);
    };

    typedef std::vector<NodePairType> PathVectorType;

	//Tests two TreePaths for equality by checking each element of the paths for equality.
	bool operator==(const TreePath& Right) const;

	bool operator!=(const TreePath& Right) const;

    bool operator<(const TreePath& RightPath) const;

    bool operator>(const TreePath& RightPath) const;

    bool operator<=(const TreePath& RightPath) const;

    bool operator>=(const TreePath& RightPath) const;

	//Returns the last component of this path.
	NodePairType getLastPathComponent(void) const;

	//Returns a path containing all the elements of this object, except the last path component.
	TreePath getParentPath(void) const;
    
	//Returns a path containing the highest depth ancestor of this path and the given path
	TreePath getHighestDepthAncestor(const TreePath& aTreePath) const;

	//Returns an ordered array of Objects containing the components of this TreePath.
	PathVectorType getPath(void) const;

	//Returns the path component at the specified index.
	NodePairType getPathComponent(const UInt32& Index) const;

	//Returns the number of elements in the path.
	UInt32 getPathCount(void) const;

    //Returns the Depth of the Last Component in this Path
    UInt32 getDepth(void) const;

	//Returns true if aTreePath is a descendant of this TreePath.
	bool isDescendant(TreePath aTreePath) const;

	//Returns a new path containing all the elements of this object plus child.
	TreePath pathByAddingChild(const boost::any& child, UInt32 childIndex) const;

    TreePath(void);

	//Constructs a TreePath containing only a single element.
	TreePath(const boost::any& singlePath, UInt32 childIndex = 0);

	//Constructs a path from an array of Objects, uniquely identifying the path from the root of the tree to a specific node, as returned by the tree's data model.
	TreePath(const PathVectorType& path);


	//Constructs a new TreePath with the identified path components of length length.
	TreePath(const PathVectorType& path, const UInt32& length);

private:
protected:

	PathVectorType _Path;
};

typedef TreePath* TreePathPtr;

OSG_END_NAMESPACE

#include "OSGTreePath.inl"

#endif /* _OSG_UI_TREE_PATH_H_ */

