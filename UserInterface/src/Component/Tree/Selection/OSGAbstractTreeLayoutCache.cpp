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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractTreeLayoutCache.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTreeLayoutCache
A AbstractTreeLayoutCache. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::vector<UInt32> AbstractTreeLayoutCache::getRowsForPaths(std::vector<TreePath> paths) const
{
	std::vector<UInt32> Result;
	for(UInt32 i(0) ; i<paths.size() ; ++i)
	{
		Result.push_back(this->getRowForPath(paths[i]));
	}
	return Result;
}

TreeModelPtr AbstractTreeLayoutCache::getModel(void) const
{
	return _TreeModel;
}

//AbstractLayoutCache.NodeDimensions AbstractTreeLayoutCache::getNodeDimensions(void) const;

UInt32 AbstractTreeLayoutCache::getPreferredHeight(void) const
{
	if(isFixedRowHeight())
	{
		return getRowHeight() * getRowCount();
	}
	else
	{
		//TODO: Implement
		return 0;
	}
}

UInt32 AbstractTreeLayoutCache::getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
	//TODO: Implement
	return 0;
}

UInt32 AbstractTreeLayoutCache::getRowHeight(void) const
{
	return _RowHeight;
}

TreeSelectionModelPtr AbstractTreeLayoutCache::getSelectionModel(void) const
{
	return _TreeSelectionModel;
}

bool AbstractTreeLayoutCache::isFixedRowHeight(void) const
{
	return _RowHeight > 0;
}

bool AbstractTreeLayoutCache::isRootVisible(void) const
{
	return _RootVisible;
}

void AbstractTreeLayoutCache::setModel(TreeModelPtr newModel)
{
    if(_TreeModel != NULL)
    {
        _TreeModel->removeTreeModelListener(&_ModelListener);
    }

    _TreeModel = newModel;
    
    if(_TreeModel != NULL)
    {
        _TreeModel->addTreeModelListener(&_ModelListener);
    }
    
    _ExpandedPathSet.clear();
    _ExpandedPathSet.comp = TreePathPreorderLessThan(_TreeModel);

    _VisiblePathSet.clear();
    _VisiblePathSet.comp = TreePathPreorderLessThan(_TreeModel);

    _VisiblePathSet.insert(TreePath(_TreeModel->getRoot()));
}

//void AbstractTreeLayoutCache::setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

void AbstractTreeLayoutCache::setRootVisible(bool rootVisible)
{
	_RootVisible = rootVisible;
}

void AbstractTreeLayoutCache::setRowHeight(const UInt32& rowHeight)
{
	_RowHeight = rowHeight;
}

void AbstractTreeLayoutCache::setSelectionModel(TreeSelectionModelPtr newLSM)
{
	_TreeSelectionModel = newLSM;
}

void AbstractTreeLayoutCache::getNodeDimensions(Pnt2s& TopLeft, Pnt2s& BottomRight, SharedFieldPtr value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn)
{
	//TODO: Implement
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTreeLayoutCache::AbstractTreeLayoutCache(void) : _TreeModel(NULL),
                                                        _TreeSelectionModel(NULL),
                                                        _ExpandedPathSet(TreePathPreorderLessThan(NULL)),
                                                        _VisiblePathSet(TreePathPreorderLessThan(NULL)),
                                                        _ModelListener(this)
{
}

/*----------------------------- class specific ----------------------------*/

bool AbstractTreeLayoutCache::TreePathPreorderLessThan::operator()(const TreePath& LeftPath,
                const TreePath& RightPath) const
{
    UInt32 LeftIndex(0), RightIndex(0);
    UInt32 LeftPathCount(LeftPath.getPathCount()), RightPathCount(RightPath.getPathCount());
    while(LeftIndex < LeftPathCount &&
          RightIndex < RightPathCount &&
          LeftPath.getPathComponent(LeftIndex) == RightPath.getPathComponent(RightIndex))
    {
        ++LeftIndex;
        ++RightIndex;
    }

    if(LeftIndex == LeftPathCount || RightIndex == RightPathCount)
    {
        return LeftPathCount < RightPathCount;
    }
    else if(LeftIndex == 0 || RightIndex == 0)
    {
        return false;
    }
    else
    {
        //Get the child indices of these nodes
        UInt32 LeftChildIndex(_TreeModel->getIndexOfChild(LeftPath.getPathComponent(LeftIndex-1), LeftPath.getPathComponent(LeftIndex))),
               RightChildIndex(_TreeModel->getIndexOfChild(RightPath.getPathComponent(RightIndex-1), RightPath.getPathComponent(RightIndex)));

        return LeftChildIndex < RightChildIndex;
    }
}

AbstractTreeLayoutCache::TreePathPreorderLessThan::TreePathPreorderLessThan(void) :
_TreeModel(NULL)
{
}

AbstractTreeLayoutCache::TreePathPreorderLessThan::TreePathPreorderLessThan(TreeModelPtr Model) :
_TreeModel(Model)
{
}

void AbstractTreeLayoutCache::ModelListener::treeNodesChanged(TreeModelEvent e)
{
    //This event inidicates changes that are not structural
    //So there are no changes to the Layout

    //Do nothing
}

void AbstractTreeLayoutCache::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    //If the Nodes are inserted into a node that is expanded then
    //they are visible.
    if(_AbstractTreeLayoutCache->isVisible(e.getPath()) && _AbstractTreeLayoutCache->isExpanded(e.getPath()))
    {
        //Add the newly inserted nodes into the visible set
        _AbstractTreeLayoutCache->setExpanded(e.getPath(), true);
    }
}

void AbstractTreeLayoutCache::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    //If the Nodes are remove into a node that is expanded then
    //they are no longer visible.
    if(_AbstractTreeLayoutCache->isVisible(e.getPath()) && _AbstractTreeLayoutCache->isExpanded(e.getPath()))
    {
        //Add the newly inserted nodes into the visible set
        _AbstractTreeLayoutCache->setExpanded(e.getPath(), false);
        _AbstractTreeLayoutCache->setExpanded(e.getPath(), true);
    }
}

void AbstractTreeLayoutCache::ModelListener::treeStructureChanged(TreeModelEvent e)
{
    //If the node that the changes are rooted at is expanded then
    //redo the visibility calculations on the parent node
    if(_AbstractTreeLayoutCache->isVisible(e.getPath()) && _AbstractTreeLayoutCache->isExpanded(e.getPath()))
    {
        //Add the newly inserted nodes into the visible set
        _AbstractTreeLayoutCache->setExpanded(e.getPath(), false);
        _AbstractTreeLayoutCache->setExpanded(e.getPath(), true);
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

