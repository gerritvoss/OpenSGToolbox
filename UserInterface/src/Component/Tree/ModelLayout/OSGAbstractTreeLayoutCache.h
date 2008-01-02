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

#ifndef _OSGABSTRACTTREELAYOUTCACHE_H_
#define _OSGABSTRACTTREELAYOUTCACHE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "Component/Tree/OSGTreeRowMapper.h"
#include "Component/Tree/OSGTreePath.h"
#include "Component/Tree/Model/OSGTreeModel.h"
#include "Component/Tree/Model/OSGTreeModelListener.h"
#include "Component/Tree/Selection/OSGTreeSelectionModel.h"
#include <OpenSG/OSGVector.h>

#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeLayoutCache class. See \ref 
           PageUserInterfaceAbstractTreeLayoutCache for a description.
*/

class AbstractTreeLayoutCache;

typedef AbstractTreeLayoutCache *AbstractTreeLayoutCachePtr;

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTreeLayoutCache : public TreeRowMapper
{
    /*==========================  PUBLIC  =================================*/
  public:
    AbstractTreeLayoutCache(void);

	//Returns the rows that the TreePath instances in path are being displayed at.
	virtual std::vector<UInt32> getRowsForPaths(std::vector<TreePath> paths) const;

	//Returns a rectangle giving the bounds needed to draw path.
	virtual void getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight, TreePath path, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn) const = 0;

	//Returns true if every node in the path is expanded
	virtual bool isVisible(const TreePath& path) const = 0;

	//Returns the TreeModel that is providing the data.
	virtual TreeModelPtr getModel(void) const;

	//Returns the object that renders nodes in the tree, and which is responsible for calculating the dimensions of individual nodes.
	//virtual AbstractLayoutCache.NodeDimensions getNodeDimensions(void) const;

	//Returns the path to the node that is closest to x,y.
	virtual TreePath getPathClosestTo(const UInt32& x, const UInt32& y) const = 0;

	//Returns the path for passed in row.
	virtual TreePath getPathForRow(const UInt32& row) const = 0;

	//Returns the preferred height.
	virtual UInt32 getPreferredHeight(void) const;

	//Returns the preferred width for the passed in region.
	virtual UInt32 getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const;

	//Number of rows being displayed.
	virtual UInt32 getRowCount(void) const = 0;

	//Returns the row that the last item identified in path is visible at.
	virtual Int32 getRowForPath(const TreePath& path) const = 0;

	//Returns the height of each row.
	virtual UInt32 getRowHeight(void) const;

	//Returns the model used to maintain the selection.
	virtual TreeSelectionModelPtr getSelectionModel(void) const;

	//Returns the number of visible children for row.
	virtual UInt32 getVisibleChildCount(const TreePath& path) const = 0;
    
	//Returns the Visible Paths
    virtual std::vector<TreePath> getVisiblePaths(void) const;

	//Returns the Expanded Paths
    virtual std::vector<TreePath> getExpandedPaths(void) const;

	//Returns an Enumerator that increments over the visible paths starting at the passed in location.
	//virtual Enumeration getVisiblePathsFrom(const TreePath& path) const = 0;

	//Instructs the LayoutCache that the bounds for path are invalid, and need to be updated.
	virtual void invalidatePathBounds(const TreePath& path) = 0;

	//Informs the TreeState that it needs to recalculate all the sizes it is referencing.
	virtual void invalidateSizes(void) = 0;

	//Returns true if the last node in this path is expanded
	virtual bool isExpanded(const TreePath& path) const = 0;

	//Returns true if the root node of the tree is displayed.
	virtual bool isRootVisible(void) const;

	//Marks the path path expanded state to isExpanded.
	virtual void setExpanded(const TreePath& path, bool isExpanded) = 0;

	//Makes sure that all the nodes in path are expanded making the last node in the
    //path visible
	virtual void setVisible(const TreePath& path);

	//Sets the TreeModel that will provide the data.
	virtual void setModel(TreeModelPtr newModel);

	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const UInt32& rowHeight);

	//Sets the TreeSelectionModel used to manage the selection to new LSM.
	virtual void setSelectionModel(TreeSelectionModelPtr newLSM);

	//Returns true if the height of each row is a fixed size.
	virtual bool isFixedRowHeight(void) const;

  protected:
	//Returns, by reference in placeIn, the size needed to represent value.
	virtual void getNodeDimensions(Pnt2s& TopLeft, Pnt2s& BottomRight, SharedFieldPtr value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn);


    //Object responsible for getting the size of a node.
    //AbstractLayoutCache.NodeDimensions nodeDimensions;

    //True if the root node is displayed, false if its children are the highest visible nodes.
    bool _RootVisible;

    //Height to use for each row.
    Int32 _RowHeight;

    //Model providing information.
    TreeModelPtr _TreeModel;

    //Selection model.
    TreeSelectionModelPtr _TreeSelectionModel;


    struct TreePathPreorderLessThan
    {
    protected:
        TreeModelPtr _TreeModel;

        TreePathPreorderLessThan(void);
    public:
        TreePathPreorderLessThan(TreeModelPtr Model);

        bool operator()(const TreePath& LeftPath,
                        const TreePath& RightPath) const;
    };
    
    typedef std::set<TreePath, TreePathPreorderLessThan> TreePathSet;
    typedef TreePathSet::iterator TreePathSetItor;
    typedef TreePathSet::const_iterator TreePathSetConstItor;

    TreePathSet _ExpandedPathSet;
    TreePathSet _VisiblePathSet;
    
	class ModelListener : public TreeModelListener
	{
	public :
		ModelListener(AbstractTreeLayoutCachePtr TheAbstractTreeLayoutCache);
		
        virtual void treeNodesChanged(TreeModelEvent e);
        virtual void treeNodesInserted(TreeModelEvent e);
        virtual void treeNodesRemoved(TreeModelEvent e);
        virtual void treeStructureChanged(TreeModelEvent e);
	protected :
		AbstractTreeLayoutCachePtr _AbstractTreeLayoutCache;
	};

	friend class ModelListener;

	ModelListener _ModelListener;
    /*==========================  PRIVATE  ================================*/
  private:
};


OSG_END_NAMESPACE

#include "OSGAbstractTreeLayoutCache.inl"

#define OSGABSTRACTTREELAYOUTCACHE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTREELAYOUTCACHE_H_ */
