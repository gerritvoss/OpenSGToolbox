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

#include "OSGTree.h"
#include "Util/OSGUIDefines.h"
#include "Component/Tree/ModelLayout/OSGTreeModelLayout.h"
#include "Component/Container/OSGUIViewport.h"

#include "Component/Tree/ComponentGenerators/OSGDefaultTreeComponentGenerator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Tree
A UI Tree. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Tree::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Tree::addSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(getModelLayout()->getPathForRow(i));
    }

    addSelectionPaths(Paths);
}

void Tree::addSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(getModelLayout()->getPathForRow(*Itor));
    }

    addSelectionPaths(Paths);
}




void Tree::cancelEditing(void)
{
    //TODO:Implement
}

TreePath Tree::getAnchorSelectionPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

TreePath Tree::getClosestPathForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getPathClosestTo(x,y);
    }
    else
    {
        return TreePath(SharedFieldPtr());
    }
}

Int32 Tree::getClosestRowForLocation(const UInt32& x, const UInt32& y) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getRowForPath(getClosestPathForLocation(x,y));
    }
    else
    {
        return -1;
    }
    //TODO:Implement
}

TreePath Tree::getEditingPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}



TreePath Tree::getPathForLocation(const UInt32& x, const UInt32& y) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getPathClosestTo(x,y);
    }
    else
    {
        return TreePath(SharedFieldPtr());
    }
    //TODO:Implement
}

Int32 Tree::getRowForLocation(const UInt32& x, const UInt32& y) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getRowForPath(getClosestPathForLocation(x,y));
    }
    else
    {
        return -1;
    }
    //TODO:Implement
}

Int32 Tree::getVisibleRowCount(void) const
{
    //TODO:Implement
    return 0;
}

bool Tree::isEditing(void) const
{
    //TODO:Implement
    return false;
}

bool Tree::isPathEditable(const TreePath& path) const
{
    //TODO:Implement
    return false;
}

void Tree::removeSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(getModelLayout()->getPathForRow(i));
    }

    removeSelectionPaths(Paths);
}

void Tree::removeSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(getModelLayout()->getPathForRow(*Itor));
    }

    removeSelectionPaths(Paths);
}




void Tree::scrollRowToVisible(const UInt32& row)
{
    //TODO:Implement
}

void Tree::setAnchorSelectionPath(const TreePath& newPath)
{
    //TODO:Implement
}

void Tree::setDragEnabled(bool b)
{
    //TODO:Implement
}

void Tree::setLeadSelectionPath(const TreePath& newPath)
{
    //TODO:Implement
    //_SelectionModel->set
}

void Tree::setModel(TreeModelPtr newModel)
{
    if(_Model != NULL)
    {
        _Model->removeTreeModelListener(&_ModelListener);
    }
    _Model = newModel;
    //Set the model used by the ModelLayout
    if(getModelLayout() != NullFC)
    {
        getModelLayout()->setModel(_Model);
    }
    if(_Model != NULL)
    {
        _Model->addTreeModelListener(&_ModelListener);
    }

    updateEntireTree();
}

void Tree::setSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(getModelLayout()->getPathForRow(i));
    }

    setSelectionPaths(Paths);
}

void Tree::setSelectionModel(TreeSelectionModelPtr selectionModel)
{
    if(_SelectionModel != NULL)
    {
        _SelectionModel->removeTreeSelectionListener(&_SelectionListener);
    }
    _SelectionModel = selectionModel;
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addTreeSelectionListener(&_SelectionListener);
    }
}

void Tree::setSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(getModelLayout()->getPathForRow(*Itor));
    }

    setSelectionPaths(Paths);
}

void Tree::setVisibleRowCount(const UInt32& newCount)
{
    //TODO:Implement
}

void Tree::startEditingAtPath(const TreePath& path)
{
    //TODO:Implement
}

bool Tree::stopEditing(void)
{
    //TODO:Implement
    return false;
}

void Tree::treeDidChange(void)
{
    //TODO:Implement
}

Vec2s Tree::getPreferredScrollableViewportSize(void)
{
    //TODO:Implement
    return Vec2s();
}

Int32 Tree::getScrollableBlockIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
}

bool Tree::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool Tree::getScrollableTracksViewportWidth(void)
{
    return true;
}

Int32 Tree::getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    //TODO:Implement
    return 0;
}

void Tree::clearToggledPaths(void)
{
    std::vector<TreePath> ExpandedPaths = getModelLayout()->getExpandedPaths();
    for(std::vector<TreePath>::iterator Itor(ExpandedPaths.begin()) ; Itor != ExpandedPaths.end() ; ++Itor)
    {
        getModelLayout()->setExpanded((*Itor), false);
    }
}




TreeModelPtr Tree::getDefaultTreeModel(void)
{
    //TODO:Implement
    return NULL;
}

std::vector<TreePath> Tree::getDescendantToggledPaths(const TreePath& parent)
{
    std::vector<TreePath> ExpandedPaths = getModelLayout()->getExpandedPaths();
    std::vector<TreePath> Result;
    
    for(std::vector<TreePath>::iterator Itor(ExpandedPaths.begin()) ; Itor != ExpandedPaths.end() ; ++Itor)
    {
        if(parent.isDescendant(*Itor))
        {
            Result.push_back(*Itor);
        }
    }

    return Result;
}

std::vector<TreePath> Tree::getPathBetweenRows(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
    return std::vector<TreePath>();
}

bool Tree::removeDescendantSelectedPaths(const TreePath& path, bool includePath)
{
    bool WasPathSelected(_SelectionModel->isPathSelected(path));

    std::vector<TreePath> SelectedPaths = _SelectionModel->getSelectionPaths();
    std::vector<TreePath> PathsToRemove;
    
    for(std::vector<TreePath>::iterator Itor(SelectedPaths.begin()) ; Itor != SelectedPaths.end() ; ++Itor)
    {
        if(path.isDescendant(*Itor))
        {
            PathsToRemove.push_back(*Itor);
        }
    }

    if(includePath && WasPathSelected)
    {
        PathsToRemove.push_back(path);
    }

    _SelectionModel->removeSelectionPaths(PathsToRemove);

    return WasPathSelected;
}

void Tree::removeDescendantToggledPaths(const std::vector<TreePath>& toRemove)
{
    std::vector<TreePath> ExpandedPaths = getModelLayout()->getExpandedPaths();
    
    for(std::vector<TreePath>::const_iterator ToRemoveItor(toRemove.begin()) ; ToRemoveItor != toRemove.end() ; ++ToRemoveItor)
    {
        for(std::vector<TreePath>::iterator ExpandedPathsItor(ExpandedPaths.begin()) ; ExpandedPathsItor != ExpandedPaths.end() ; ++ExpandedPathsItor)
        {
            if(ToRemoveItor->isDescendant(*ExpandedPathsItor))
            {
                getModelLayout()->setExpanded(*ExpandedPathsItor, false);
            }
        }
    }
}

void Tree::setExpandedState(const TreePath& path, bool state)
{
    getModelLayout()->setVisible(path);
    getModelLayout()->setExpanded(path, state);
}

bool Tree::isParentAViewport(void) const
{
    return (getParentContainer() != NullFC) && (getParentContainer()->getType() == UIViewport::getClassType());
}

UIViewportPtr Tree::getParentViewport(void) const
{
    if(isParentAViewport())
    {
        return UIViewport::Ptr::dcast(getParentContainer());
    }
    else
    {
        return NullFC;
    }
}

void Tree::updateChangedPath(const TreePath& Path)
{
    //TODO:Implement
}

void Tree::updateEntireTree(void)
{
    //TODO:Implement

    //Remove the previous drawn rows

    //Determine the drawn rows
    getDrawnRows(_TopDrawnRow, _BottomDrawnRow);

    //create the drawn components for these rows
}

void Tree::updateInsertedRows(const UInt32& Begining, const UInt32& NumInsertedRows)
{
    //TODO:Implement
}

void Tree::updateRemovedRows(const UInt32& Begining, const UInt32& NumRemovedRows)
{
    //TODO:Implement
}

void Tree::updateRows(const UInt32& Begining, const UInt32& NumRows)
{
    //TODO:Implement
}

void Tree::updateRowsDrawn(void)
{
    Int32 NewTopDrawnRow,
          NewBottomDrawnRow;
    getDrawnRows(NewTopDrawnRow, NewBottomDrawnRow);

    if(NewTopDrawnRow > _TopDrawnRow)
    {
        //Remove all of the Drawn rows above NewTopDrawnRow
        for(Int32 i(_TopDrawnRow) ; i<osgMin(NewTopDrawnRow, _BottomDrawnRow) ; ++i)
        {
            _DrawnRows.pop_front();
        }
    }

    if(NewBottomDrawnRow < _BottomDrawnRow)
    {
        //Remove all of the Drawn rows below NewBottomDrawnRow
        for(Int32 i(osgMax(NewBottomDrawnRow+1, _TopDrawnRow)) ; i<=_BottomDrawnRow ; ++i)
        {
            _DrawnRows.pop_back();
        }
    }


    if(NewTopDrawnRow < _TopDrawnRow)
    {
        //Insert all of the Drawn rows between NewTopDrawnRow and _TopDrawnRow
        for(Int32 i(NewTopDrawnRow) ; i<osgMin(_TopDrawnRow, NewBottomDrawnRow) ; ++i)
        {
            _DrawnRows.push_front(createRowComponent(i));
        }
    }

    if(NewBottomDrawnRow > _BottomDrawnRow)
    {
        //Insert all of the Drawn rows between _BottomDrawnRow and NewBottomDrawnRow
        for(Int32 i(osgMax(NewTopDrawnRow, _BottomDrawnRow+1)) ; i<=NewBottomDrawnRow ; ++i)
        {
            _DrawnRows.push_back(createRowComponent(i));
        }
    }

    _TopDrawnRow = NewTopDrawnRow;
    _BottomDrawnRow = NewBottomDrawnRow;

    beginEditCP(TreePtr(this), ChildrenFieldMask);
        getChildren().clear();
        for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
        {
            getChildren().push_back(_DrawnRows[i]);
        }
    endEditCP(TreePtr(this), ChildrenFieldMask);
}

ComponentPtr Tree::createRowComponent(const UInt32& Row)
{
    if(getCellGenerator() != NullFC)
    {
        TreePath NodePath(getModelLayout()->getPathForRow(Row));
        bool Selected;

        if(_SelectionModel != NULL)
        {
            Selected = _SelectionModel->isPathSelected(NodePath);
        }
        else
        {
            Selected = false;
        }
        if(getCellGenerator()->getType() == DefaultTreeComponentGenerator::getClassType())
        {
            return DefaultTreeComponentGenerator::Ptr::dcast(getCellGenerator())->getTreeComponent(TreePtr(this), NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), _Model->isLeaf(NodePath.getLastPathComponent()), Row, false);
        }
        else
        {
            return getCellGenerator()->getComponent(TreePtr(this),NodePath.getLastPathComponent(),Selected, false);
        }
    }
    else
    {
        return NullFC;
    }
}

void Tree::updateDrawnRow(const UInt32& Row)
{
    if(Row >= 0)
    {
    }
}

void Tree::updateLayout(void)
{
    //Update the Position and Size of all the Drawn Rows
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren(i), Component::PositionFieldMask | Component::SizeFieldMask);
            getChildren(i)->setPosition(Pnt2s(0, getModelLayout()->getRowHeight()*(i+_TopDrawnRow)));
            getChildren(i)->setSize(Vec2s(getSize().x(), getModelLayout()->getRowHeight()));
        endEditCP(getChildren(i), Component::PositionFieldMask | Component::SizeFieldMask);
    }
}

void Tree::getDrawnRows(Int32& Beginning, Int32& End) const
{
    //Get My Clip Bounds
    Pnt2s ClipTopLeft, ClipBottomRight;
    getClipBounds(ClipTopLeft, ClipBottomRight);

    Beginning = getRowForLocation(ClipTopLeft.x(), ClipTopLeft.y());
    End = getRowForLocation(ClipBottomRight.x(), ClipBottomRight.y());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Tree::Tree(void) :
    Inherited(),
        _Model(NULL),
        _SelectionModel(NULL),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this)),
		_ModelLayoutListener(TreePtr(this)),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
}

Tree::Tree(const Tree &source) :
    Inherited(source),
        _Model(source._Model),
        _SelectionModel(source._SelectionModel),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this)),
		_ModelLayoutListener(TreePtr(this)),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
}

Tree::~Tree(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Tree::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ModelLayoutFieldMask) &&
        getModelLayout() != NullFC)
    {
        //Set the model used by the ModelLayout
        getModelLayout()->setModel(_Model);
		getModelLayout()->addTreeModelLayoutListener(&_ModelLayoutListener);
        updateEntireTree();
    }
    
    if((whichField & Tree::ClipTopLeftFieldMask) ||
       (whichField & Tree::ClipBottomRightFieldMask))
    {
        updateRowsDrawn();
    }
}

void Tree::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Tree NI" << std::endl;
}

void Tree::ModelListener::treeNodesChanged(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeStructureChanged(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::SelectionListener::valueChanged(TreeSelectionEvent e)
{
    //TODO: Implement
}

void Tree::ModelLayoutListener::treeCollapsed(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
}

void Tree::ModelLayoutListener::treeExpanded(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
}

void Tree::ModelLayoutListener::treeWillCollapse(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
}

void Tree::ModelLayoutListener::treeWillExpand(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
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
    static Char8 cvsid_hpp       [] = OSGTREEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTREEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTREEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

