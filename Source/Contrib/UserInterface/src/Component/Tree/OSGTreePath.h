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
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"
#include <boost/any.hpp>

#include "OSGBaseTypes.h"
#include <vector>
#include <deque>
#include "OSGTreeModelFields.h"


OSG_BEGIN_NAMESPACE
	 
class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreePath
{

public:
    struct BreadthFirstFunctional
    {
    public:
        bool operator()(const TreePath& LeftPath,
                        const TreePath& RightPath) const;
    };
    
    struct DepthFirstFunctional
    {
    public:
        bool operator()(const TreePath& LeftPath,
                        const TreePath& RightPath) const;
    };

    typedef std::vector<boost::any> PathVectorType;
    
    TreePath(const PathVectorType& path, TreeModel * const theModel);

    TreePath(boost::any value, TreeModel * const theModel);

    TreePath(const std::deque<boost::any>& path, TreeModel * const theModel);

    TreePath(const TreePath& p, UInt32 len);

    TreePath(const TreePath& p, boost::any child);

	//Tests two TreePaths for equality
	bool operator==(const TreePath& Right) const;

	bool operator!=(const TreePath& Right) const;
    
	bool operator<(const TreePath& Right) const;

	//Returns the last component of this path.
    boost::any getLastPathComponent(void) const;

	//Returns a path of the child node at index of this path
	TreePath getChildPath(UInt32 index) const;

	//Returns a path of the child of this path
	TreePath getChildPath(boost::any child) const;

	//Returns a path containing all the elements of this object, except the last path component.
	TreePath getParentPath(void) const;
    
	//Returns a path containing the highest depth ancestor of this path and the given path
	TreePath getHighestDepthAncestor(const TreePath& aTreePath) const;

	//Returns the path component at the specified index.
    boost::any getPathComponent(const UInt32& Index) const;

	//Returns the number of elements in the path.
	UInt32 getPathCount(void) const;

    //Returns the Depth of the Last Component in this Path
    UInt32 getDepth(void) const;

	//Returns true if aTreePath is a descendant of this TreePath.
	bool isDescendant(const TreePath& aTreePath) const;
    
	//Returns true if aTreePath is an ancestor of this TreePath.
	bool isAncestor(const TreePath& aTreePath) const;

	//Returns true if aTreePath is a sibling of this TreePath.
	bool isSibling(const TreePath& aTreePath) const;

    //Copy constructor
    TreePath(const TreePath& p);

    //Default Tree Path Constructor
    //creates an empty TreePath
    TreePath(void);

    //Returns true if this is an empty path
    bool empty(void) const;

    //A Breadth First Traversal comparator
    //Returns true if left would be visited before right in a BFT
    bool depthFirstLessThan(const TreePath& Right) const;

    //A Breadth First Traversal comparator
    //Returns true if this Path would be visited before Right in a BFT
    bool breadthFirstLessThan(const TreePath& Right) const;

private:
    friend class TreeModel;

protected:

	PathVectorType _Path;
    TreeModel* _Model;
};

typedef TreePath* TreePathPtr;

OSG_END_NAMESPACE

#include "OSGTreePath.inl"

#endif /* _OSG_UI_TREE_PATH_H_ */

