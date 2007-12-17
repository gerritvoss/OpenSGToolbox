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

#ifndef _OSGVARIABLEHEIGHTTREELAYOUTCACHE_H_
#define _OSGVARIABLEHEIGHTTREELAYOUTCACHE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractTreeLayoutCache.h"

OSG_BEGIN_NAMESPACE

/*! \brief VariableHeightTreeLayoutCache class. See \ref 
           PageUserInterfaceVariableHeightTreeLayoutCache for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING VariableHeightTreeLayoutCache : public AbstractTreeLayoutCache
{
    /*==========================  PUBLIC  =================================*/
  public:
	//Returns a rectangle giving the bounds needed to draw path.
	virtual void getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight, TreePath path, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn) const;

	//Returns true if the path is expanded, and visible.
	virtual bool getExpandedState(TreePath path) const const;

	//Returns the path to the node that is closest to x,y.
	virtual TreePath getPathClosestTo(const UInt32& x, const UInt32& y) const;

	//Returns the path for passed in row.
	virtual TreePath getPathForRow(const UInt32& row) const;

	//Returns the preferred height.
	virtual UInt32 getPreferredHeight(void) const;

	//Returns the preferred width for the passed in region.
	virtual UInt32 getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const;

	//Number of rows being displayed.
	virtual UInt32 getRowCount(void) const;

	//Returns the row that the last item identified in path is visible at.
	virtual UInt32 getRowForPath(TreePath path) const;

	//Returns the number of visible children for row.
	virtual UInt32 getVisibleChildCount(TreePath path) const;

	//Returns an Enumerator that increments over the visible paths starting at the passed in location.
	//virtual Enumeration getVisiblePathsFrom(TreePath path) const;

	//Instructs the LayoutCache that the bounds for path are invalid, and need to be updated.
	virtual void invalidatePathBounds(TreePath path);

	//Informs the TreeState that it needs to recalculate all the sizes it is referencing.
	virtual void invalidateSizes(void);

	//Returns true if the value identified by row is currently expanded.
	virtual bool isExpanded(TreePath path) const;

	//Marks the path path expanded state to isExpanded.
	virtual void setExpandedState(TreePath path, bool isExpanded);

	//Sets the TreeModel that will provide the data.
	virtual void setModel(TreeModelPtr newModel);
	
	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const UInt32& rowHeight);

	//Invoked after a node (or a set of siblings) has changed in some way.
	virtual void treeNodesChanged(TreeModelEvent e);

	//Invoked after nodes have been inserted into the tree.
	virtual void treeNodesInserted(TreeModelEvent e);

	//Invoked after nodes have been removed from the tree.
	virtual void treeNodesRemoved(TreeModelEvent e);

	//Invoked after the tree has drastically changed structure from a given node down.
	virtual void treeStructureChanged(TreeModelEvent e);


  protected:

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef VariableHeightTreeLayoutCache *VariableHeightTreeLayoutCachePtr;

OSG_END_NAMESPACE

#define OSGVARIABLEHEIGHTTREELAYOUTCACHE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGVARIABLEHEIGHTTREELAYOUTCACHE_H_ */
