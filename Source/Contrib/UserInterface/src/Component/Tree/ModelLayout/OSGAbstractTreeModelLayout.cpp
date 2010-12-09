/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGAbstractTreeModelLayout.h"
#include <boost/bind.hpp>
#include "OSGTreeModelEventDetails.h"
#include <boost/bind.hpp>
#include "OSGTreeModelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractTreeModelLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractTreeModelLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTreeModelLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::vector<Int32> AbstractTreeModelLayout::getRowsForPaths(const std::vector<TreePath>& paths) const
{
    std::vector<Int32> Result;
    for(UInt32 i(0) ; i<paths.size() ; ++i)
    {
        Result.push_back(this->getRowForPath(paths[i]));
    }
    return Result;
}

TreeModel* AbstractTreeModelLayout::getModel(void) const
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
    setDepthOffsetInternal(depthOffset);
}

TreeSelectionModel* AbstractTreeModelLayout::getSelectionModel(void) const
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

void AbstractTreeModelLayout::setModel(TreeModel* const newModel)
{
    _TreeNodesChangedConnection.disconnect();
    _TreeNodesInsertedConnection.disconnect();
    _TreeNodesWillBeRemovedConnection.disconnect();
    _TreeNodesRemovedConnection.disconnect();
    _TreeStructureChangedConnection.disconnect();

    _TreeModel = newModel;

    _ExpandedPathSet.clear();

    _VisiblePathSet.clear();

    if(_TreeModel != NULL)
    {

        _TreeNodesChangedConnection = _TreeModel->connectTreeNodesChanged(boost::bind(&AbstractTreeModelLayout::handleTreeNodesChanged, this, _1));
        _TreeNodesInsertedConnection = _TreeModel->connectTreeNodesInserted(boost::bind(&AbstractTreeModelLayout::handleTreeNodesInserted, this, _1));
        _TreeNodesWillBeRemovedConnection = _TreeModel->connectTreeNodesWillBeRemoved(boost::bind(&AbstractTreeModelLayout::handleTreeNodesWillBeRemoved, this, _1));
        _TreeNodesRemovedConnection = _TreeModel->connectTreeNodesRemoved(boost::bind(&AbstractTreeModelLayout::handleTreeNodesRemoved, this, _1));
        _TreeStructureChangedConnection = _TreeModel->connectTreeStructureChanged(boost::bind(&AbstractTreeModelLayout::handleTreeStructureChanged, this, _1));

        TreePath RootPath(_TreeModel->getRootPath());
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
    setRootVisibleInternal(rootVisible);
}

void AbstractTreeModelLayout::setRowHeight(const Real32& rowHeight)
{
    setRowHeightInternal(rowHeight);
}

void AbstractTreeModelLayout::setSelectionModel(TreeSelectionModel* const newLSM)
{
    _TreeSelectionModel = newLSM;
}

void AbstractTreeModelLayout::setVisible(const TreePath& path)
{
    TreePath ThePath(path);
    while(!ThePath.empty())
    {
        setExpanded(ThePath, true);
        ThePath = ThePath.getParentPath();
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

void AbstractTreeModelLayout::getNodeDimensions(Pnt2f& TopLeft, Pnt2f& BottomRight, const boost::any& value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn)
{
    //TODO: Implement
}

void AbstractTreeModelLayout::produceTreeCollapsed(const TreePath& Path)
{
    TreeModelLayoutEventDetailsUnrecPtr Details = TreeModelLayoutEventDetails::create(this, getTimeStamp(), Path);

    Inherited::produceTreeCollapsed(Details);
}

void AbstractTreeModelLayout::produceTreeExpanded(const TreePath& Path)
{
    TreeModelLayoutEventDetailsUnrecPtr Details = TreeModelLayoutEventDetails::create(this, getTimeStamp(), Path);

    Inherited::produceTreeExpanded(Details);
}

void AbstractTreeModelLayout::produceTreeWillCollapse(const TreePath& Path)
{
    TreeModelLayoutEventDetailsUnrecPtr Details = TreeModelLayoutEventDetails::create(this, getTimeStamp(), Path);

    Inherited::produceTreeWillCollapse(Details);
}

void AbstractTreeModelLayout::produceTreeWillExpand(const TreePath& Path)
{
    TreeModelLayoutEventDetailsUnrecPtr Details = TreeModelLayoutEventDetails::create(this, getTimeStamp(), Path);

    Inherited::produceTreeWillExpand(Details);
}


bool AbstractTreeModelLayout::areChildrenVisible(const TreePath& path) const
{
    if(isRootVisible() ||
       (!isRootVisible() && path != _TreeModel->getRootPath()))
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
    if(isExpanded(Path))
    {
        std::vector<TreePath> VisibleDecendants;
        getVisibleDecendants(Path, VisibleDecendants);
        for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
        {
            _VisiblePathSet.insert(VisibleDecendants[i]);
        }
    }
}

void AbstractTreeModelLayout::removeVisiblePath(const TreePath& Path)
{
    _VisiblePathSet.erase(_VisiblePathSet.find(Path));
    _TreeModel->setAsNotVisible(Path);

    //Remove all visible decendents of Path
    removeVisibleDecendents(Path);
    /*TreePathSetItor VisibleSetItor(_VisiblePathSet.begin());
    while(VisibleSetItor != _VisiblePathSet.end())
    {
        if(Path.isDescendant((*VisibleSetItor)))
        {
            TreePathSetItor RemoveItor(VisibleSetItor);
            ++VisibleSetItor;
            _VisiblePathSet.erase(RemoveItor);
        }
        else
        {
            ++VisibleSetItor;
        }
    }*/
}

void AbstractTreeModelLayout::insertVisibleDecendents(const TreePath& Path)
{
    if(isVisible(Path) || (_TreeModel->getRootPath() == Path))
    {
        //Insert all visible decendents of Path
        std::vector<TreePath> VisibleDecendants;
        getVisibleDecendants(Path, VisibleDecendants);
        for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
        {            
            //Let the model know that this node is visible
            _TreeModel->setAsVisible(VisibleDecendants[i]);

            _VisiblePathSet.insert(VisibleDecendants[i]);
        }
    }
}

void AbstractTreeModelLayout::removeVisibleDecendents(const TreePath& Path)
{
    if(isVisible(Path) || _TreeModel->getRootPath() == Path)
    {
        //Remove all visible decendents of Path
        std::vector<TreePath> VisibleDecendants;
        getVisibleDecendants(Path, VisibleDecendants);
        for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
        {            
            //Let the model know that this node is visible
            _TreeModel->setAsNotVisible(VisibleDecendants[i]);

            _VisiblePathSet.erase(VisibleDecendants[i]);
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

        if(Path.isDescendant((*ExpandedSetItor)))
        {
            TreePathSetItor RemoveItor(ExpandedSetItor);
            ++ExpandedSetItor;
            _ExpandedPathSet.erase(RemoveItor);
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
    boost::any Child;

    TreePath ChildPath;
    for(UInt32 i(0) ; i<NumChildren ; ++i)
    {
        Child = _TreeModel->getChild(Path.getLastPathComponent(), i);

        ChildPath = Path.getChildPath(Child);
        //Add This child to the Visible Decendants
        VisibleDecendants.push_back(ChildPath);

        //If this child is expanded then add all of it's visible decendants
        if(isExpanded(ChildPath))
        {
            getVisibleDecendants(ChildPath, VisibleDecendants);
        }
    }
}

void AbstractTreeModelLayout::produceTreeNodesChanged(TreeModelEventDetails* const Details)
{
    Inherited::produceTreeNodesChanged(Details);
}

void AbstractTreeModelLayout::produceTreeNodesInserted(TreeModelEventDetails* const Details)
{
    Inherited::produceTreeNodesInserted(Details);
}

void AbstractTreeModelLayout::produceTreeNodesWillBeRemoved(TreeModelEventDetails* const Details)
{
    Inherited::produceTreeNodesWillBeRemoved(Details);
}

void AbstractTreeModelLayout::produceTreeNodesRemoved(TreeModelEventDetails* const Details)
{
    Inherited::produceTreeNodesRemoved(Details);
}

void AbstractTreeModelLayout::produceTreeStructureChanged(TreeModelEventDetails* const Details)
{
    Inherited::produceTreeStructureChanged(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTreeModelLayout::AbstractTreeModelLayout(void) :
    Inherited(),
    _TreeModel(NULL),
    _TreeSelectionModel(NULL),
    _ExpandedPathSet(),
    _VisiblePathSet(),
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
	_VetoPathExpantion(false),
	_VetoPathCollapse(false)
{
}

AbstractTreeModelLayout::~AbstractTreeModelLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTreeModelLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & RootVisibleInternalFieldMask)
    {
        if(getRootVisibleInternal())
        {
            _VisiblePathSet.insert(_TreeModel->getRootPath());
        }
    }
}

void AbstractTreeModelLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractTreeModelLayout NI" << std::endl;
}

void AbstractTreeModelLayout::handleTreeNodesChanged(TreeModelEventDetails* const e)
{
    //This event inidicates changes that are not structural
    //So there are no changes to the Layout

    //Pass the event along
    produceTreeNodesChanged(e);
}

void AbstractTreeModelLayout::handleTreeNodesInserted(TreeModelEventDetails* const e)
{
    //If the Nodes are inserted into a node that is expanded then
    //they are visible.
    if(areChildrenVisible(e->getPath()))
    {
        TreePath NodePath;
        for(UInt32 i(0) ; i<e->getChildren().size() ; ++i)
        {
            //Insert the path
            insertVisiblePath(e->getChildPath(i));
        }
    }
    produceTreeNodesInserted(e);
}


void AbstractTreeModelLayout::handleTreeNodesWillBeRemoved(TreeModelEventDetails* const e)
{
    produceTreeNodesWillBeRemoved(e);
    //If the Nodes are remove into a node that is expanded then
    //they are no longer visible.
    if(areChildrenVisible(e->getPath()))
    {
        //remove the nodes from the visible set
        for(UInt32 i(0) ; i<e->getChildren().size() ; ++i)
        {
            removeVisiblePath (e->getChildPath(i));
            removeExpandedPath(e->getChildPath(i));
        }
    }
}

void AbstractTreeModelLayout::handleTreeNodesRemoved(TreeModelEventDetails* const e)
{
    produceTreeNodesRemoved(e);
}

void AbstractTreeModelLayout::handleTreeStructureChanged(TreeModelEventDetails* const e)
{
    bool expanded(isExpanded(e->getPath()));

    //If the node that the changes are rooted at is expanded then
    if(expanded)
    {

        //collapse the node
        _ExpandedPathSet.erase(e->getPath());

        //remove all of the nodes that were visible decendents of the root of the change
        if(isVisible(e->getPath()) || _TreeModel->getRootPath() == e->getPath())
        {
            //Remove all visible decendents of Path
            std::vector<TreePath> VisibleDecendants;
            TreePathSet::iterator Itor(_VisiblePathSet.begin());
            for( ; Itor!=_VisiblePathSet.end() ; ++Itor)
            {
                if(Itor->isAncestor(e->getPath()))
                {
                    VisibleDecendants.push_back(*Itor);
                }
            }

            for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
            {
                _VisiblePathSet.erase(VisibleDecendants[i]);
            }
        }
    }

    produceTreeStructureChanged(e);

    //If is root node
    if(e->getPath().getDepth() == 1 || expanded)
    {
        setExpanded(e->getPath(), true);
    }
}

OSG_END_NAMESPACE
