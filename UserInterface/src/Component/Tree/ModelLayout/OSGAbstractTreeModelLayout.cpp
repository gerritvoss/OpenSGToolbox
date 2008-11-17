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

#include "OSGAbstractTreeModelLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTreeModelLayout
A UI Abstract Tree Model Layout. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTreeModelLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbstractTreeModelLayout::removeTreeModelLayoutListener(TreeModelLayoutListenerPtr Listener)
{
   TreeModelLayoutListenerSetItor EraseIter(_TreeModelLayoutListeners.find(Listener));
   if(EraseIter != _TreeModelLayoutListeners.end())
   {
      _TreeModelLayoutListeners.erase(EraseIter);
   }
}

std::vector<UInt32> AbstractTreeModelLayout::getRowsForPaths(std::vector<TreePath> paths) const
{
	std::vector<UInt32> Result;
	for(UInt32 i(0) ; i<paths.size() ; ++i)
	{
		Result.push_back(this->getRowForPath(paths[i]));
	}
	return Result;
}

TreeModelPtr AbstractTreeModelLayout::getModel(void) const
{
	return _TreeModel;
}

//AbstractLayoutCache.NodeDimensions AbstractTreeModelLayout::getNodeDimensions(void) const;

Real32 AbstractTreeModelLayout::getPreferredHeight(void) const
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

Real32 AbstractTreeModelLayout::getPreferredWidth(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	//TODO: Implement
	return 0;
}

Real32 AbstractTreeModelLayout::getRowHeight(void) const
{
	return getRowHeightInternal();
}

Real32 AbstractTreeModelLayout::getDepthOffset(void) const
{
	return getDepthOffsetInternal();
}

void AbstractTreeModelLayout::setDepthOffset(const Real32& depthOffset)
{
    beginEditCP(AbstractTreeModelLayoutPtr(this), DepthOffsetInternalFieldMask);
		setDepthOffsetInternal(depthOffset);
    endEditCP(AbstractTreeModelLayoutPtr(this), DepthOffsetInternalFieldMask);
}

TreeSelectionModelPtr AbstractTreeModelLayout::getSelectionModel(void) const
{
	return _TreeSelectionModel;
}

bool AbstractTreeModelLayout::isFixedRowHeight(void) const
{
	return getRowHeightInternal() > 0;
}

bool AbstractTreeModelLayout::isRootVisible(void) const
{
	return getRootVisibleInternal();
}

void AbstractTreeModelLayout::setModel(TreeModelPtr newModel)
{
    if(_TreeModel != NULL)
    {
        _TreeModel->removeTreeModelListener(&_ModelListener);
    }

    _TreeModel = newModel;
    
    _ExpandedPathSet = TreePathSet(TreePathPreorderLessThan(_TreeModel));
    //_ExpandedPathSet.clear();
    //_ExpandedPathSet.comp = TreePathPreorderLessThan(_TreeModel);

    _VisiblePathSet = TreePathSet(TreePathPreorderLessThan(_TreeModel));
    //_VisiblePathSet.clear();
    //_VisiblePathSet.comp = TreePathPreorderLessThan(_TreeModel);

    if(_TreeModel != NULL)
    {
        _TreeModel->addTreeModelListener(&_ModelListener);

        TreePath RootPath(_TreeModel->getRoot());
        setExpanded(RootPath, true);
        if(isRootVisible())
        {
            _VisiblePathSet.insert(RootPath);
        }
    }
    

}

//void AbstractTreeModelLayout::setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

void AbstractTreeModelLayout::setRootVisible(bool rootVisible)
{
    beginEditCP(AbstractTreeModelLayoutPtr(this), RootVisibleInternalFieldMask);
        setRootVisibleInternal(rootVisible);
    endEditCP(AbstractTreeModelLayoutPtr(this), RootVisibleInternalFieldMask);
}

void AbstractTreeModelLayout::setRowHeight(const Real32& rowHeight)
{
    beginEditCP(AbstractTreeModelLayoutPtr(this), RowHeightInternalFieldMask);
    setRowHeightInternal(rowHeight);
    endEditCP(AbstractTreeModelLayoutPtr(this), RowHeightInternalFieldMask);
}

void AbstractTreeModelLayout::setSelectionModel(TreeSelectionModelPtr newLSM)
{
	_TreeSelectionModel = newLSM;
}

void AbstractTreeModelLayout::setVisible(const TreePath& path)
{
    for(UInt32 i(1) ; i<=path.getPathCount() ; ++i)
    {
        setExpanded(TreePath(path.getPath(), i), true);
    }
}

std::vector<TreePath> AbstractTreeModelLayout::getVisiblePaths(void) const
{
    return std::vector<TreePath>(_VisiblePathSet.begin(), _VisiblePathSet.end());
}

std::vector<TreePath> AbstractTreeModelLayout::getExpandedPaths(void) const
{
    return std::vector<TreePath>(_ExpandedPathSet.begin(), _ExpandedPathSet.end());
}

void AbstractTreeModelLayout::vetoPathExpantion(const TreePath& Path)
{
	_VetoPathExpantion = true;
}

void AbstractTreeModelLayout::vetoPathCollapse(const TreePath& Path)
{
	_VetoPathCollapse = true;
}

void AbstractTreeModelLayout::getNodeDimensions(Pnt2f& TopLeft, Pnt2f& BottomRight, SharedFieldPtr value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn)
{
	//TODO: Implement
}

void AbstractTreeModelLayout::produceTreeCollapsed(const TreePath& Path)
{
	TreeModelLayoutEvent TheEvent(AbstractTreeModelLayoutPtr(this), getTimeStamp(), TreeModelLayoutEvent::TREE_COLLAPSED, Path);
	TreeModelLayoutListenerSet Listeners(_TreeModelLayoutListeners);
    for(TreeModelLayoutListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
		(*SetItor)->treeCollapsed(TheEvent);
    }
}

void AbstractTreeModelLayout::produceTreeExpanded(const TreePath& Path)
{
	TreeModelLayoutEvent TheEvent(AbstractTreeModelLayoutPtr(this), getTimeStamp(), TreeModelLayoutEvent::TREE_EXPANDED, Path);
	TreeModelLayoutListenerSet Listeners(_TreeModelLayoutListeners);
    for(TreeModelLayoutListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
		(*SetItor)->treeExpanded(TheEvent);
    }
}

void AbstractTreeModelLayout::produceTreeWillCollapse(const TreePath& Path)
{
	TreeModelLayoutEvent TheEvent(AbstractTreeModelLayoutPtr(this), getTimeStamp(), TreeModelLayoutEvent::TREE_WILL_COLLAPSE, Path);
	TreeModelLayoutListenerSet Listeners(_TreeModelLayoutListeners);
    for(TreeModelLayoutListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
		(*SetItor)->treeWillCollapse(TheEvent);
    }
}

void AbstractTreeModelLayout::produceTreeWillExpand(const TreePath& Path)
{
	TreeModelLayoutEvent TheEvent(AbstractTreeModelLayoutPtr(this), getTimeStamp(), TreeModelLayoutEvent::TREE_WILL_EXPAND, Path);
	TreeModelLayoutListenerSet Listeners(_TreeModelLayoutListeners);
    for(TreeModelLayoutListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
		(*SetItor)->treeWillExpand(TheEvent);
    }
}


bool AbstractTreeModelLayout::areChildrenVisible(const TreePath& path) const
{
    if(isRootVisible() ||
       (!isRootVisible() && path != TreePath(_TreeModel->getRoot())))
    {
        return isVisible(path) && isExpanded(path);
    }
    else
    {
        return isExpanded(path);
    }
}

void AbstractTreeModelLayout::insertVisiblePath(const TreePath& Path)
{
    _VisiblePathSet.insert(Path);
	//Insert all visible decendents of Path
	std::vector<TreePath> VisibleDecendants;
	getVisibleDecendants(Path, VisibleDecendants);
	for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
	{
		_VisiblePathSet.insert(VisibleDecendants[i]);
	}
}

void AbstractTreeModelLayout::removeVisiblePath(const TreePath& Path)
{
    std::string TempString;
    std::cout << "removeVisiblePath: Path: ";
    for(UInt32 i(0) ; i<Path.getPath().size() ; ++i)
    {
        Path.getPath()[i]->getValueByStr(TempString);
        std::cout << TempString << " - ";
    }
    std::cout << std::endl;

    std::cout << "removeVisiblePath: VisibleSet: ";
    for(TreePathSetItor i(_VisiblePathSet.begin()) ; i!=_VisiblePathSet.end() ; ++i)
    {
        i->getLastPathComponent()->getValueByStr(TempString);
        std::cout << TempString << ", ";
    }
    std::cout << std::endl;

    TreePathPreorderLessThan temp(_TreeModel);
    std::cout << temp.operator ()(Path,Path) << " : " << temp.operator ()(Path,Path) << std::endl;

    _VisiblePathSet.erase(_VisiblePathSet.find(Path));
	//Remove all visible decendents of Path
    TreePathSetItor VisibleSetItor(_VisiblePathSet.begin());
    while(VisibleSetItor != _VisiblePathSet.end())
    {
        if((*VisibleSetItor).isDescendant(Path))
        {
            //VisibleSetItor = _VisiblePathSet.erase(VisibleSetItor);
        }
        else
        {
            ++VisibleSetItor;
        }
    }
}
void AbstractTreeModelLayout::removeExpandedPath(const TreePath& Path)
{
    _ExpandedPathSet.erase(Path);
	//Remove all visible decendents of Path
    TreePathSetItor ExpandedSetItor(_ExpandedPathSet.begin());
    while(ExpandedSetItor != _ExpandedPathSet.end())
    {
        if((*ExpandedSetItor).isDescendant(Path))
        {
            //ExpandedSetItor = _ExpandedPathSet.erase(ExpandedSetItor);
        }
        else
        {
            ++ExpandedSetItor;
        }
    }
}

void AbstractTreeModelLayout::getVisibleDecendants(const TreePath& Path, std::vector<TreePath>& VisibleDecendants) const
{
    //Loop through all of the Children of the last node in Path
    UInt32 NumChildren(_TreeModel->getChildCount(Path.getLastPathComponent()));
    SharedFieldPtr Child;

    for(UInt32 i(0) ; i<NumChildren ; ++i)
    {
        Child = _TreeModel->getChild(Path.getLastPathComponent(), i);

        //Add This child to the Visible Decendants
        VisibleDecendants.push_back(Path.pathByAddingChild(Child));

        //If this child is expanded then add all of it's visible decendants
        if(isExpanded(Path.pathByAddingChild(Child)))
        {
            getVisibleDecendants(Path.pathByAddingChild(Child), VisibleDecendants);
        }
    }
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTreeModelLayout::AbstractTreeModelLayout(void) :
    Inherited(),
    _TreeModel(NULL),
    _TreeSelectionModel(NULL),
    _ExpandedPathSet(TreePathPreorderLessThan(NULL)),
    _VisiblePathSet(TreePathPreorderLessThan(NULL)),
    _ModelListener(AbstractTreeModelLayoutPtr(this)),
	_VetoPathExpantion(false),
	_VetoPathCollapse(false)
{
}

AbstractTreeModelLayout::AbstractTreeModelLayout(const AbstractTreeModelLayout &source) :
    Inherited(source),
        _TreeModel(source._TreeModel),
    _TreeSelectionModel(source._TreeSelectionModel),
    _ExpandedPathSet(source._ExpandedPathSet),
    _VisiblePathSet(source._VisiblePathSet),
    _ModelListener(AbstractTreeModelLayoutPtr(this)),
	_VetoPathExpantion(false),
	_VetoPathCollapse(false)
{
}

AbstractTreeModelLayout::~AbstractTreeModelLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTreeModelLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & RootVisibleInternalFieldMask)
    {
        if(getRootVisibleInternal())
        {
            _VisiblePathSet.insert(TreePath(_TreeModel->getRoot()));
        }
    }
}

void AbstractTreeModelLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractTreeModelLayout NI" << std::endl;
}

bool AbstractTreeModelLayout::TreePathPreorderLessThan::operator()(const TreePath& LeftPath,
                const TreePath& RightPath) const
{
    if(LeftPath.getDepth() != RightPath.getDepth())
    {
        if(LeftPath.isDescendant(RightPath)){return true;}
        else if(RightPath.isDescendant(LeftPath)){return false;}
    }

    TreePath CommonAncestor(LeftPath.getHighestDepthAncestor(RightPath));

    if(CommonAncestor.getPathCount() == 0)
    {
        return false;
    }

    UInt32 LeftNextDownAncestorIndex(_TreeModel->getIndexOfChild(CommonAncestor.getLastPathComponent(),LeftPath.getPathComponent(CommonAncestor.getDepth())));
    UInt32 RightNextDownAncestorIndex(_TreeModel->getIndexOfChild(CommonAncestor.getLastPathComponent(),RightPath.getPathComponent(CommonAncestor.getDepth())));

    return LeftNextDownAncestorIndex < RightNextDownAncestorIndex;


    /*UInt32 LeftIndex(0), RightIndex(0);
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
    }*/
}

AbstractTreeModelLayout::TreePathPreorderLessThan::TreePathPreorderLessThan(void) :
_TreeModel(NULL)
{
}

AbstractTreeModelLayout::TreePathPreorderLessThan::TreePathPreorderLessThan(TreeModelPtr Model) :
_TreeModel(Model)
{
}

void AbstractTreeModelLayout::ModelListener::treeNodesChanged(TreeModelEvent e)
{
    //This event inidicates changes that are not structural
    //So there are no changes to the Layout

    //Do nothing
}

void AbstractTreeModelLayout::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    //If the Nodes are inserted into a node that is expanded then
    //they are visible.
    if(_AbstractTreeModelLayout->areChildrenVisible(e.getPath()))
    {
        for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
        {
            _AbstractTreeModelLayout->insertVisiblePath( e.getTreePath().pathByAddingChild(e.getChildren()[i]) );
        }
    }
}

void AbstractTreeModelLayout::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    //If the Nodes are remove into a node that is expanded then
    //they are no longer visible.
    if(_AbstractTreeModelLayout->areChildrenVisible(e.getPath()))
    {
        //remove the nodes from the visible set
        for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
        {
            _AbstractTreeModelLayout->removeVisiblePath( e.getTreePath().pathByAddingChild(e.getChildren()[i]) );
            _AbstractTreeModelLayout->removeExpandedPath( e.getTreePath().pathByAddingChild(e.getChildren()[i]) );
        }
    }
}

void AbstractTreeModelLayout::ModelListener::treeStructureChanged(TreeModelEvent e)
{
    //If the node that the changes are rooted at is expanded then
    //redo the visibility calculations on the parent node
    if(_AbstractTreeModelLayout->areChildrenVisible(e.getPath()))
    {
        //Add the newly inserted nodes into the visible set
        _AbstractTreeModelLayout->setExpanded(e.getPath(), false);
        _AbstractTreeModelLayout->setExpanded(e.getPath(), true);
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

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGABSTRACTTREEMODELLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTTREEMODELLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTTREEMODELLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

