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
#include "Component/Tree/ModelLayout/OSGTreeModelLayout.h"
#include "Component/Tree/Selection/OSGDefaultTreeSelectionModel.h"
#include "Component/Container/OSGUIViewport.h"

#include "Component/Tree/ComponentGenerators/OSGDefaultTreeComponentGenerator.h"
#include "Component/Scroll/OSGScrollBar.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

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


void Tree::mousePressed(const MouseEvent& e)
{
    Pnt2f PointInCompSpace(DrawingSurfaceToComponent(e.getLocation(),ComponentPtr(this)));

    //Determine the row the mouse is located
    Int32 Row = getRowForLocation(PointInCompSpace);

    if(Row >= 0 && Row < getRowCount())
    {
        for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
        {
            if((_DrawnRows[i]._ExpandedComponent != NullFC &&
                _DrawnRows[i]._Row == Row &&
                _DrawnRows[i]._ExpandedComponent->isContained(e.getLocation()))
               ||
               (e.getClickCount() == 1 && 
                 _DrawnRows[i]._ValueComponent->isContained(e.getLocation())))
            {
                if(isExpanded(Row))
                {
                    collapseRow(Row);
                }
                else
                {
                    expandRow(Row);
                }
                //toggle the expansion of this node
                return;
            }
        }
		if(getParentWindow() != NullFC &&
		   getParentWindow()->getDrawingSurface() != NullFC &&
		   getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
			{
				getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionRow(), Row);
				getSelectionModel()->setLeadSelectionRow(Row);
			}
			else if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
			{
                // this toggles the interval
                if(getSelectionModel()->isRowSelected(Row))
                {
    				getSelectionModel()->removeSelectionRow(Row);
                }
                else
                {
				    getSelectionModel()->addSelectionRow(Row);
                }
				getSelectionModel()->setAnchorSelectionRow(Row);
			}
			else
			{
				getSelectionModel()->setSelectionRow(Row);
				getSelectionModel()->setAnchorSelectionRow(Row);
			}
		}
    }
	Container::mousePressed(e);
}

void Tree::keyTyped(const KeyEvent& e)
{
	switch(e.getKey())
	{
	case KeyEvent::KEY_UP:
        //Move Up one Row
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow > 0 && SelectedRow < getModelLayout()->getRowCount())
            {
                getSelectionModel()->setSelectionRow(SelectedRow - 1);
                scrollRowToVisible(SelectedRow - 1);
            }
        }
        break;
	case KeyEvent::KEY_DOWN:
        //Move Down one Row
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow >= 0 && SelectedRow < getModelLayout()->getRowCount()-1)
            {
                getSelectionModel()->setSelectionRow(SelectedRow + 1);
                scrollRowToVisible(SelectedRow + 1);
            }
        }
        break;
	case KeyEvent::KEY_RIGHT:
        //Move Down one depth
        {
            TreePath SelectedPath = getSelectionModel()->getSelectionPath();
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(!isExpanded(SelectedRow))
            {
                expandRow(SelectedRow);
            }
            else if(getModel()->getChildCount(SelectedPath.getLastPathComponent()) > 0)
            {
                TreePath ToPath = getModel()->getPath(getModel()->getChild(SelectedPath.getLastPathComponent(),0));
                getSelectionModel()->setSelectionPath(ToPath);
                scrollPathToVisible(ToPath);
            }
        }
        break;
	case KeyEvent::KEY_LEFT:
        //Move Up one depth
        {
            TreePath SelectedPath = getSelectionModel()->getSelectionPath();
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(isExpanded(SelectedRow))
            {
                collapseRow(SelectedRow);
            }
            else if((getRootVisible() && SelectedPath.getPathCount() > 1) ||
                (!getRootVisible() && SelectedPath.getPathCount() > 2))
            {
                TreePath ToPath(SelectedPath.getParentPath());
                getSelectionModel()->setSelectionPath(ToPath);
                scrollPathToVisible(ToPath);
            }
        }
		break;
	case KeyEvent::KEY_ENTER:
        {
            TreePath SelectedPath = getSelectionModel()->getSelectionPath();
		    if (getModel()->isLeaf(SelectedPath.getLastPathComponent()))
		    {
                //Send Action command for that leaf
		    }
		    else
		    {
                Int32 SelectedRow = getSelectionModel()->getSelectionRow();
                if(isExpanded(SelectedRow))
                {
                    collapseRow(SelectedRow);
                }
                else
                {
                    expandRow(SelectedRow);
                }
		    }
        }
		break;
	case KeyEvent::KEY_HOME:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != 0 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(0);
                scrollRowToVisible(0);
            }
        }
		break;
	case KeyEvent::KEY_END:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != getModelLayout()->getRowCount()-1 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(getModelLayout()->getRowCount()-1);
                scrollRowToVisible(getModelLayout()->getRowCount()-1);
            }
        }
		break;
	case KeyEvent::KEY_PAGE_UP:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != 0 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(osgMax(SelectedRow-(_BottomDrawnRow - _TopDrawnRow),0));
                scrollRowToVisible(osgMax(SelectedRow-(_BottomDrawnRow - _TopDrawnRow),0));
            }
        }
		break;
	case KeyEvent::KEY_PAGE_DOWN:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != getModelLayout()->getRowCount()-1 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(osgMin<Int32>(SelectedRow+(_BottomDrawnRow - _TopDrawnRow), getModelLayout()->getRowCount()-1));
                scrollRowToVisible(osgMin<Int32>(SelectedRow+(_BottomDrawnRow - _TopDrawnRow), getModelLayout()->getRowCount()-1));
            }
        }
		break;
	}

	Component::keyTyped(e);
}

void Tree::focusLost(const FocusEvent& e)
{
	//getSelectionModel()->clearSelection();
}

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
    return TreePath();
}

TreePath Tree::getClosestPathForLocation(const Pnt2f& Loc) const
{
    //TODO:Implement
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getPathClosestTo(Loc);
    }
    else
    {
        return TreePath();
    }
}

Int32 Tree::getClosestRowForLocation(const Pnt2f& Loc) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getRowForPath(getClosestPathForLocation(Loc));
    }
    else
    {
        return -1;
    }
}

TreePath Tree::getEditingPath(void) const
{
    //TODO:Implement
    return TreePath();
}



TreePath Tree::getPathForLocation(const Pnt2f& Loc) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getPathClosestTo(Loc);
    }
    else
    {
        return TreePath();
    }
}

Int32 Tree::getRowForLocation(const Pnt2f& Loc) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getRowForPath(getClosestPathForLocation(Loc));
    }
    else
    {
        return -1;
    }
}

Int32 Tree::getVisibleRowCount(void) const
{
    return getModelLayout()->getRowCount();
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
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Pnt2f ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);
	
	Pnt2f UnionTopLeft, UnionBottomRight;
	//Get the intersection of my bounds with my parent containers clip bounds
	quadIntersection(InsetsTopLeft, InsetsBottomRight,
		ClipTopLeft, ClipBottomRight,
		UnionTopLeft, UnionBottomRight);

	//Check if any scrolling is needed
	if(row <= _TopDrawnRow)
	{
		//Scroll Up so that this Index is The First Visible
		Pnt2f Pos(UnionTopLeft.x(), static_cast<Real32>(row) * getModelLayout()->getRowHeight());

		scrollToPoint(Pos);
	}
	else if(row >= _BottomDrawnRow && _BottomDrawnRow != -1)
	{
		UInt32 CorrectedRow;
		if(row >= getModelLayout()->getRowCount())
		{
			CorrectedRow = getModelLayout()->getRowCount()-1;
		}
		else
		{
			CorrectedRow = row;
		}

		//Scroll Down so that this Index is the last Visible
		Pnt2f Pos(UnionTopLeft.x(), (static_cast<Real32>(CorrectedRow) * getModelLayout()->getRowHeight()) - (UnionBottomRight.y()-UnionTopLeft.y()) + getModelLayout()->getRowHeight());

		scrollToPoint(Pos);
	}
}

void Tree::setAnchorSelectionPath(const TreePath& newPath)
{
    getSelectionModel()->setAnchorSelectionPath(newPath);
}

void Tree::setDragEnabled(bool b)
{
    //TODO:Implement
}

void Tree::setLeadSelectionPath(const TreePath& newPath)
{
    getSelectionModel()->setLeadSelectionPath(newPath);
}

void Tree::setModel(TreeModelPtr newModel)
{
    _Model = newModel;
    //Set the model used by the ModelLayout
    if(getModelLayout() != NullFC)
    {
        getModelLayout()->setModel(_Model);
    }

    updateEntireTree();
}

void Tree::setSelectionInterval(const Int32& index0, const Int32& index1)
{
	_SelectionModel->setSelectionInterval(index0,index1);
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
        if(getModelLayout() != NullFC)
        {
            _SelectionModel->setRowMapper(getModelLayout());
        }
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

Vec2f Tree::getPreferredScrollableViewportSize(void)
{
    //TODO:Implement
    return Vec2f();
}

Int32 Tree::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
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

Int32 Tree::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(orientation == ScrollBar::VERTICAL_ORIENTATION && getModelLayout() != NullFC)
    {
        return getModelLayout()->getRowHeight();
    }
    else
    {
        return Inherited::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation,direction);
    }
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
    updatePreferredSize();

    //Remove the previous drawn rows

    //Determine the drawn rows
    //getDrawnRows(_TopDrawnRow, _BottomDrawnRow);
	//updateRowsDrawn();

    //create the drawn components for these rows
}

void Tree::updateInsertedRows(const UInt32& Begining, const UInt32& NumInsertedRows)
{
    if(static_cast<Int32>(Begining) <= _TopDrawnRow)
    {
        for(Int32 i(1) ; i<=NumInsertedRows ; ++i)
        {
            _DrawnRows.push_front(createRowComponent(_TopDrawnRow+NumInsertedRows-i));
        }
        _BottomDrawnRow = _TopDrawnRow + _DrawnRows.size() -1;
    }
    else if(static_cast<Int32>(Begining) > _TopDrawnRow &&
            static_cast<Int32>(Begining) <= _BottomDrawnRow)
    {
        while(_DrawnRows.size() > Begining - _TopDrawnRow)
        {
            _DrawnRows.pop_back();
        }

        _BottomDrawnRow = _TopDrawnRow + _DrawnRows.size() -1;
    }

    updateRowsDrawn();
    updatePreferredSize();
}

void Tree::updateRemovedRows(const UInt32& Begining, const UInt32& NumRemovedRows)
{
    //If the removed rows are before or straddling the top
    if(static_cast<Int32>(Begining) <= _TopDrawnRow)
    {
        //Pop off the front to the New Top Drawn Row
        for(UInt32 i(0) ; i<osgMin<Int32>(NumRemovedRows,_BottomDrawnRow-_TopDrawnRow+1) ; ++i)
        {
            _DrawnRows.pop_front();
        }

        if(_DrawnRows.size() == 0)
        {
            _TopDrawnRow = -1;
            _BottomDrawnRow = -1;
        }
        else
        {
            _TopDrawnRow = _BottomDrawnRow-_DrawnRows.size() + 1;
        }
    }
    else if(static_cast<Int32>(Begining) > _TopDrawnRow &&
            static_cast<Int32>(Begining) <= _BottomDrawnRow)
    {
        while(_DrawnRows.size() > Begining - _TopDrawnRow)
        {
            _DrawnRows.pop_back();
        }

        _BottomDrawnRow = _TopDrawnRow + _DrawnRows.size() -1;
    }


    updateRowsDrawn();
    updatePreferredSize();

}

void Tree::updateRows(const UInt32& Begining, const UInt32& NumRows)
{
    for(UInt32 i(Begining) ; i<Begining+NumRows ; ++i)
    {
        if(i>=_TopDrawnRow && i<=_BottomDrawnRow)
        {
            _DrawnRows[i-_TopDrawnRow] =createRowComponent(i);
        }
    }
    updateChildren();
}

void Tree::updateRowsDrawn(void)
{
    Int32 NewTopDrawnRow,
          NewBottomDrawnRow;
    getDrawnRows(NewTopDrawnRow, NewBottomDrawnRow);

    if(_TopDrawnRow != -1 && NewTopDrawnRow > _TopDrawnRow)
    {
        //Remove all of the Drawn rows above NewTopDrawnRow
        for(Int32 i(_TopDrawnRow) ; i<osgMin(NewTopDrawnRow, _BottomDrawnRow+1) ; ++i)
        {
            _DrawnRows.pop_front();
        }
    }

    if(_BottomDrawnRow != -1 && NewBottomDrawnRow < _BottomDrawnRow)
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
        if(_TopDrawnRow != -1 || NewBottomDrawnRow != -1)
        {
            for(Int32 i(osgMin(_TopDrawnRow-1, NewBottomDrawnRow)) ; i>=NewTopDrawnRow ; --i)
            {
                _DrawnRows.push_front(createRowComponent(i));
            }
        }
    }

    if(NewBottomDrawnRow > _BottomDrawnRow)
    {
        if(NewTopDrawnRow != -1 || _BottomDrawnRow != -1)
        {
            //Insert all of the Drawn rows between _BottomDrawnRow and NewBottomDrawnRow
            for(Int32 i(osgMax(NewTopDrawnRow, _BottomDrawnRow+1)) ; i<=NewBottomDrawnRow ; ++i)
            {
                _DrawnRows.push_back(createRowComponent(i));
            }
        }
    }

    _TopDrawnRow = NewTopDrawnRow;
    _BottomDrawnRow = NewBottomDrawnRow;

    updateChildren();
}

Tree::TreeRowComponents Tree::createRowComponent(const UInt32& Row)
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
		if(getCellGenerator()->getType().isDerivedFrom(TreeComponentGenerator::getClassType()))
        {
            return TreeRowComponents( TreeComponentGenerator::Ptr::dcast(getCellGenerator())->getTreeExpandedComponent(TreePtr(this), NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), _Model->isLeaf(NodePath.getLastPathComponent()), Row, false),
                TreeComponentGenerator::Ptr::dcast(getCellGenerator())->getTreeComponent(TreePtr(this), NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), _Model->isLeaf(NodePath.getLastPathComponent()), Row, false),
                Row);
        }
        else
        {
            return TreeRowComponents(NullFC, getCellGenerator()->getComponent(TreePtr(this),NodePath.getLastPathComponent(), Row, 0,Selected, false),Row);
        }
    }
    else
    {
        return TreeRowComponents();
    }
}

void Tree::updateDrawnRow(const UInt32& Row)
{
    if(Row >= _TopDrawnRow &&
       Row <= _BottomDrawnRow)
    {
        _DrawnRows[Row-_TopDrawnRow] = createRowComponent(Row);
        updateChildren();
    }
}

void Tree::updateChildren(void)
{
    beginEditCP(TreePtr(this), ChildrenFieldMask);
        getChildren().clear();
        for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
        {
            if(_DrawnRows[i]._ExpandedComponent != NullFC)
            {
                getChildren().push_back(_DrawnRows[i]._ExpandedComponent);
            }
        }
        for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
        {
            getChildren().push_back(_DrawnRows[i]._ValueComponent);
        }
    endEditCP(TreePtr(this), ChildrenFieldMask);
}

void Tree::updateLayout(void)
{
    //Update the Position and Size of all the Drawn Rows
    for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
    {
        Pnt2f RowTopLeft((getPathForRow(_TopDrawnRow+i).getDepth()-1) * getModelLayout()->getDepthOffset(), getModelLayout()->getRowHeight()*(i+_TopDrawnRow));
        if(_DrawnRows[i]._ExpandedComponent != NullFC)
        {
            beginEditCP(_DrawnRows[i]._ExpandedComponent, Component::PositionFieldMask | Component::SizeFieldMask);
                _DrawnRows[i]._ExpandedComponent->setSize(_DrawnRows[i]._ExpandedComponent->getRequestedSize());
		        _DrawnRows[i]._ExpandedComponent->setPosition(RowTopLeft-Vec2f(_DrawnRows[i]._ExpandedComponent->getSize().x()+ 2.0f, -0.5f*(getModelLayout()->getRowHeight()-_DrawnRows[i]._ExpandedComponent->getSize().y())));
            endEditCP(_DrawnRows[i]._ExpandedComponent, Component::PositionFieldMask | Component::SizeFieldMask);
        }
        beginEditCP(_DrawnRows[i]._ValueComponent, Component::PositionFieldMask | Component::SizeFieldMask);
            _DrawnRows[i]._ValueComponent->setPosition(RowTopLeft);
            _DrawnRows[i]._ValueComponent->setSize(Vec2f(getSize().x()-_DrawnRows[i]._ValueComponent->getPosition().x(), getModelLayout()->getRowHeight()));
        endEditCP(_DrawnRows[i]._ValueComponent, Component::PositionFieldMask | Component::SizeFieldMask);
    }
}

void Tree::getDrawnRows(Int32& Beginning, Int32& End) const
{
    //Get My Clip Bounds
    Pnt2f ClipTopLeft, ClipBottomRight;
    getClipBounds(ClipTopLeft, ClipBottomRight);

    Beginning = getRowForLocation(ClipTopLeft);
    End = getRowForLocation(ClipBottomRight);
}

void Tree::updatePreferredSize(void)
{
    beginEditCP(TreePtr(this), PreferredSizeFieldMask);
        if(getModelLayout() != NullFC)
        {
            setPreferredSize(Vec2f(getPreferredSize().x(), getModelLayout()->getRowCount()* getModelLayout()->getRowHeight()));
        }
        else
        {
            setPreferredSize(Vec2f(0,0));
        }
    endEditCP(TreePtr(this), PreferredSizeFieldMask);
}

void Tree::updateExpandedPath(const TreePath& Path)
{
    Int32 Row(getModelLayout()->getRowForPath(Path));
    if(Row>=0 && Row <= _BottomDrawnRow)
    {
        _DrawnRows[Row-_TopDrawnRow] =createRowComponent(Row);
    }
    UInt32 VisibleChildren = getModelLayout()->getVisibleChildCount(Path);
    if(VisibleChildren > 0)
    {
        updateInsertedRows(Row+1,VisibleChildren);
    }
}

void Tree::updateCollapsedPath(const TreePath& Path)
{
    Int32 Row(getModelLayout()->getRowForPath(Path));
    if(Row>=0 && Row <= _BottomDrawnRow)
    {
        _DrawnRows[Row-_TopDrawnRow] =createRowComponent(Row);
    }
    UInt32 VisibleChildren = getModelLayout()->getVisibleChildCount(Path);
    if(VisibleChildren > 0)
    {
        updateRemovedRows(Row+1,VisibleChildren);
    }

    std::vector<TreePath> SelectedPaths(getSelectionModel()->getSelectionPaths());
    std::vector<TreePath> DescendantSelectedPaths;
    for(UInt32 i(0) ; i<SelectedPaths.size() ; ++i)
    {
        if(Path.isDescendant(SelectedPaths[i]))
        {
            DescendantSelectedPaths.push_back(SelectedPaths[i]);
        }
    }
    //Are there any Decendents of the collapsed Path that are selected
    if(DescendantSelectedPaths.size() > 0)
    {
        //Then remove all Decendents that have selection
        getSelectionModel()->removeSelectionPaths(DescendantSelectedPaths);

        //and add The Collapsed Path to the Selection
        getSelectionModel()->addSelectionPath(Path);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Tree::Tree(void) :
    Inherited(),
        _Model(NULL),
        _SelectionModel(new DefaultTreeSelectionModel()),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this)),
		_ModelLayoutListener(TreePtr(this)),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addTreeSelectionListener(&_SelectionListener);
        if(getModelLayout() != NullFC)
        {
            _SelectionModel->setRowMapper(getModelLayout());
        }
    }
}

Tree::Tree(const Tree &source) :
    Inherited(source),
        _Model(source._Model),
        _SelectionModel(new DefaultTreeSelectionModel()),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this)),
		_ModelLayoutListener(TreePtr(this)),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
    if(getModelLayout() != NullFC)
    {
        beginEditCP(TreePtr(this), ModelLayoutFieldMask);
			setModelLayout(TreeModelLayout::Ptr::dcast(getModelLayout()->shallowCopy()));
        endEditCP(TreePtr(this), ModelLayoutFieldMask);
		getModelLayout()->addTreeModelLayoutListener(&_ModelLayoutListener);
        getModelLayout()->addTreeModelListener(&_ModelListener);
    }
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addTreeSelectionListener(&_SelectionListener);
        if(getModelLayout() != NullFC)
        {
            _SelectionModel->setRowMapper(getModelLayout());
        }
    }
}

Tree::~Tree(void)
{
    delete _SelectionModel;
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
        _SelectionModel->setRowMapper(getModelLayout());
        updateEntireTree();
    }
    
    if(whichField & Tree::ClipBoundsFieldMask)
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
    Int32 Row(-1);
    for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
    {
        Row = _Tree->getModelLayout()->getRowForPath(_Tree->_Model->getPath(e.getChildren()[i]));
        if(Row != -1)
        {
            _Tree->updateRows(Row, 1);
        }
    }
}

void Tree::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    Int32 InsertedRow(-1);
    for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
    {
        InsertedRow = _Tree->getModelLayout()->getRowForPath(_Tree->_Model->getPath(e.getChildren()[i]));
        if(InsertedRow != -1)
        {
            _Tree->updateInsertedRows(InsertedRow, 1);
        }
    }
}

void Tree::ModelListener::treeNodesWillBeRemoved(TreeModelEvent e)
{
    _RomovedNodeRows.clear();
    Int32 RemovedRow(-1);
    std::vector<TreePath> VisibleDecendants;
    TreePath ThePath;
    for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
    {
        ThePath = _Tree->_Model->getPath(e.getChildren()[i]);
        //Get the row for this path
        RemovedRow = _Tree->getModelLayout()->getRowForPath(ThePath);
        _RomovedNodeRows.insert(RemovedRow);
        
        //Get the rows of all visible decendents
        VisibleDecendants.clear();
        _Tree->getModelLayout()->getVisibleDecendants(ThePath, VisibleDecendants);
        for(std::vector<TreePath>::iterator Itor(VisibleDecendants.begin()) ; Itor != VisibleDecendants.end(); ++Itor)
        {
            RemovedRow = _Tree->getModelLayout()->getRowForPath(*Itor);
            _RomovedNodeRows.insert(RemovedRow);
        }
        
    }
    

    std::vector<UInt32> RemovedSelectionRows;
    for(std::set<Int32>::iterator Itor(_RomovedNodeRows.begin()) ; Itor != _RomovedNodeRows.end(); ++Itor)
    {
        if((*Itor) >= 0)
        {
            RemovedSelectionRows.push_back(static_cast<UInt32>(*Itor));
        }
    }
    
    //Remove them from the selection
    _Tree->removeSelectionRows(RemovedSelectionRows);
}
void Tree::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    Int32 RemovedRow(-1);
    for(std::set<Int32>::iterator Itor(_RomovedNodeRows.begin()) ; Itor != _RomovedNodeRows.end(); ++Itor)
    {
        if((*Itor) != -1)
        {
            _Tree->updateRemovedRows((*Itor), 1);
        }
    }
    _RomovedNodeRows.clear();
}

void Tree::ModelListener::treeStructureChanged(TreeModelEvent e)
{
    //TODO: Implement
    _Tree->updatePreferredSize();
}

void Tree::SelectionListener::selectionAdded(TreeSelectionEvent e)
{
    for(UInt32 i(0) ; i<e.getElementsChanged().size() ; ++i)
    {
        for(Int32 j(e.getElementsChanged()[i].getMin()) ; 
            j<=e.getElementsChanged()[i].getMax() ;
            ++j)
        {
            _Tree->updateDrawnRow(j);
        }
    }
}

void Tree::SelectionListener::selectionRemoved(TreeSelectionEvent e)
{
    for(UInt32 i(0) ; i<e.getElementsChanged().size() ; ++i)
    {
        for(Int32 j(e.getElementsChanged()[i].getMin()) ; 
            j<=e.getElementsChanged()[i].getMax() ;
            ++j)
        {
            _Tree->updateDrawnRow(j);
        }
    }
}

void Tree::ModelLayoutListener::treeCollapsed(const TreeModelLayoutEvent& e)
{
    _Tree->updateCollapsedPath(e.getPath());
}

void Tree::ModelLayoutListener::treeExpanded(const TreeModelLayoutEvent& e)
{
    _Tree->updateExpandedPath(e.getPath());
}

void Tree::ModelLayoutListener::treeWillCollapse(const TreeModelLayoutEvent& e)
{
    //TODO: Implement
}

void Tree::ModelLayoutListener::treeWillExpand(const TreeModelLayoutEvent& e)
{
    //TODO: Implement
}

Tree::TreeRowComponents::TreeRowComponents(void) :  _ExpandedComponent(NullFC), _ValueComponent(NullFC), _Row(-1)
{
}

Tree::TreeRowComponents::TreeRowComponents(ComponentPtr ExpandedComponent, ComponentPtr ValueComponent, Int32 Row) :  _ExpandedComponent(ExpandedComponent), _ValueComponent(ValueComponent), _Row(Row)
{
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

