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

#include "OSGTree.h"
#include "OSGTreeModelEventDetails.h"
#include "OSGTreeModelLayout.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultTreeSelectionModel.h"
#include "OSGUIViewport.h"

#include "OSGDefaultTreeComponentGenerator.h"
#include "OSGScrollBar.h"
#include "OSGUIDrawUtils.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGTreeSelectionEventDetails.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeBase.cpp file.
// To modify it, please change the .fcd file (OSGTree.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Tree::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool Tree::useBoundsForClipping(void) const
{
    return false;
}

Vec2f Tree::getContentRequestedSize(void) const
{
    //Calculate the max between
    //   Preferred horizontal size
    //   The horizontal size used by the currently visible rows
    Real32 MaxHorizontal(getPreferredSize().x());
    for(UInt32 i(0) ; i<_DrawnRows.size(); ++i)
    {
        MaxHorizontal = osgMax(MaxHorizontal,
                               _DrawnRows[i]._ValueComponent->getRequestedSize().x() 
                                   + ((getPathForRow(_TopDrawnRow+i).getDepth()-1) * getModelLayout()->getDepthOffset()));
    }

    return Vec2f(MaxHorizontal, getModelLayout()->getRowCount()* getModelLayout()->getRowHeight());
}

void Tree::mousePressed(MouseEventDetails* const e)
{
    Pnt2f PointInCompSpace(DrawingSurfaceToComponent(e->getLocation(),this));

    //Determine the row the mouse is located
    Int32 Row = getRowForLocation(PointInCompSpace);

    if(Row >= 0 && Row < getRowCount())
    {
        for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
        {
            if((_DrawnRows[i]._ExpandedComponent != NULL &&
                _DrawnRows[i]._Row == Row &&
                _DrawnRows[i]._ExpandedComponent->isContained(e->getLocation()))
               ||
               (e->getClickCount() == 1 && 
                 _DrawnRows[i]._ValueComponent->isContained(e->getLocation())))
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
		if(getParentWindow() != NULL &&
		   getParentWindow()->getParentDrawingSurface() != NULL &&
		   getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
		{
			if(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
			{
				getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionRow(), Row);
				getSelectionModel()->setLeadSelectionRow(Row);
			}
			else if(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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
    else
    {
        //Clicked outside of the rows
        //Clear the selection
        if(getParentWindow() != NULL &&
           getParentWindow()->getParentDrawingSurface() != NULL &&
           getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
        {
            if(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() == 0)
            {
                getSelectionModel()->clearSelection();
            }
        }
    }

    //TODO: handle this better
    commitChanges();

    ComponentContainer::mousePressed(e);
}

void Tree::keyTyped(KeyEventDetails* const e)
{
	switch(e->getKey())
	{
	case KeyEventDetails::KEY_UP:
        //Move Up one Row
        {
            if(!getSelectionModel()->isSelectionEmpty())
            {
                Int32 SelectedRow = getSelectionModel()->getSelectionRow();
                if(SelectedRow > 0 && SelectedRow < getModelLayout()->getRowCount())
                {
                    getSelectionModel()->setSelectionRow(SelectedRow - 1);
                    scrollRowToVisible(SelectedRow - 1);
                }
            }
        }
        break;
	case KeyEventDetails::KEY_DOWN:
        //Move Down one Row
        {
            if(!getSelectionModel()->isSelectionEmpty())
            {
                Int32 SelectedRow = getSelectionModel()->getSelectionRow();
                if(SelectedRow >= 0 && SelectedRow < getModelLayout()->getRowCount()-1)
                {
                    getSelectionModel()->setSelectionRow(SelectedRow + 1);
                    scrollRowToVisible(SelectedRow + 1);
                }
            }
        }
        break;
	case KeyEventDetails::KEY_RIGHT:
        //Move Down one depth
        {
            if(!getSelectionModel()->isSelectionEmpty())
            {
                TreePath SelectedPath = getSelectionModel()->getSelectionPath();
                Int32 SelectedRow = getSelectionModel()->getSelectionRow();
                if(!isExpanded(SelectedRow))
                {
                    expandRow(SelectedRow);
                }
                else if(getModel()->getChildCount(SelectedPath.getLastPathComponent()) > 0)
                {
                    TreePath ToPath(SelectedPath.getChildPath(0));
                    getSelectionModel()->setSelectionPath(ToPath);
                    scrollPathToVisible(ToPath);
                }
            }
        }
        break;
	case KeyEventDetails::KEY_LEFT:
        //Move Up one depth
        {
            if(!getSelectionModel()->isSelectionEmpty())
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
        }
		break;
	case KeyEventDetails::KEY_ENTER:
        {
            if(!getSelectionModel()->isSelectionEmpty())
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
        }
		break;
	case KeyEventDetails::KEY_HOME:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != 0 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(0);
                scrollRowToVisible(0);
            }
        }
		break;
	case KeyEventDetails::KEY_END:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != getModelLayout()->getRowCount()-1 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(getModelLayout()->getRowCount()-1);
                scrollRowToVisible(getModelLayout()->getRowCount()-1);
            }
        }
		break;
	case KeyEventDetails::KEY_PAGE_UP:
        {
            Int32 SelectedRow = getSelectionModel()->getSelectionRow();
            if(SelectedRow != 0 && getModelLayout()->getRowCount() > 0)
            {
                getSelectionModel()->setSelectionRow(osgMax(SelectedRow-(_BottomDrawnRow - _TopDrawnRow),0));
                scrollRowToVisible(osgMax(SelectedRow-(_BottomDrawnRow - _TopDrawnRow),0));
            }
        }
		break;
	case KeyEventDetails::KEY_PAGE_DOWN:
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

void Tree::focusLost(FocusEventDetails* const e)
{
	//getSelectionModel()->clearSelection();
}

void Tree::addSelectionInterval(UInt32 index0, UInt32 index1)
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

void Tree::expandPath(const TreePath& path)
{
    for(UInt32 i(1) ; i<=path.getDepth() ; ++i)
    {
        getModelLayout()->setExpanded(TreePath(path,i), true);
    }
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
    if(getModelLayout() != NULL)
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
    if(getModelLayout() != NULL)
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
    if(getModelLayout() != NULL)
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
    if(getModelLayout() == NULL || getModelLayout()->getHeight() < Loc.y())
    {
        return -1;
    }
    else
    {
        return getModelLayout()->getRowForPath(getClosestPathForLocation(Loc));
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

void Tree::removeSelectionInterval(UInt32 index0, UInt32 index1)
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




void Tree::scrollRowToVisible(UInt32 row)
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

void Tree::setSelectionInterval(const Int32& index0, const Int32& index1)
{
	getSelectionModel()->setSelectionInterval(index0,index1);
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

void Tree::setVisibleRowCount(UInt32 newCount)
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
    return getRequestedSize();
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
    return false;
}


bool Tree::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool Tree::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

Int32 Tree::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(orientation == ScrollBar::VERTICAL_ORIENTATION && getModelLayout() != NULL)
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




TreeModel* Tree::getDefaultTreeModel(void)
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

std::vector<TreePath> Tree::getPathBetweenRows(UInt32 index0, UInt32 index1)
{
    //TODO:Implement
    return std::vector<TreePath>();
}

bool Tree::removeDescendantSelectedPaths(const TreePath& path, bool includePath)
{
    bool WasPathSelected(getSelectionModel()->isPathSelected(path));

    std::vector<TreePath> SelectedPaths = getSelectionModel()->getSelectionPaths();
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

    getSelectionModel()->removeSelectionPaths(PathsToRemove);

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
    return (getParentContainer() != NULL) && (getParentContainer()->getType() == UIViewport::getClassType());
}

UIViewport* Tree::getParentViewport(void) const
{
    if(isParentAViewport())
    {
        return dynamic_cast<UIViewport*>(getParentContainer());
    }
    else
    {
        return NULL;
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

void Tree::updateInsertedRows(UInt32 Begining, UInt32 NumInsertedRows)
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

void Tree::updateRemovedRows(UInt32 Begining, UInt32 NumRemovedRows)
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

void Tree::updateChangedNode(const TreePath& Path)
{
    //Nuke it
    clearRowsDrawn();
    updateRowsDrawn();
    updatePreferredSize();
}

void Tree::clearRowsDrawn(void)
{
    _TopDrawnRow = _BottomDrawnRow = -1;
    _DrawnRows.clear();
}

void Tree::updateRows(UInt32 Begining, UInt32 NumRows)
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

Tree::TreeRowComponents Tree::createRowComponent(UInt32 Row)
{
    if(getCellGenerator() != NULL)
    {
        TreePath NodePath(getModelLayout()->getPathForRow(Row));
        bool Selected;

        if(getSelectionModel() != NULL)
        {
            Selected = getSelectionModel()->isPathSelected(NodePath);
        }
        else
        {
            Selected = false;
        }
		if(getCellGenerator()->getType().isDerivedFrom(TreeComponentGenerator::getClassType()))
        {
            //Create the Expand component
            ComponentUnrecPtr NewExpComp(dynamic_cast<TreeComponentGenerator*>(getCellGenerator())->getTreeExpandedComponent(this, NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), getModel()->isLeaf(NodePath.getLastPathComponent()), Row, false));
            //Create the Row Component
            ComponentUnrecPtr NewComp(dynamic_cast<TreeComponentGenerator*>(getCellGenerator())->getTreeComponent(this, NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), getModel()->isLeaf(NodePath.getLastPathComponent()), Row, false));
            return TreeRowComponents( NewExpComp, NewComp, Row);
        }
        else
        {
            //Create the Row Component
            ComponentUnrecPtr NewComp(getCellGenerator()->getComponent(this,NodePath.getLastPathComponent(), Row, 0,Selected, false));
            return TreeRowComponents(NULL, NewComp,Row);
        }
    }
    else
    {
        return TreeRowComponents();
    }
}

void Tree::updateDrawnRow(UInt32 Row)
{
    if(Row >= _TopDrawnRow &&
       Row <= _BottomDrawnRow)
    {
        _DrawnRows[Row-_TopDrawnRow] = createRowComponent(Row);
        updateChildren();
        updateRowLayout(Row-_TopDrawnRow);
    }
}

void Tree::updateChildren(void)
{
    clearChildren();
    for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
    {
        if(_DrawnRows[i]._ExpandedComponent != NULL)
        {
            pushToChildren(_DrawnRows[i]._ExpandedComponent);
        }
        pushToChildren(_DrawnRows[i]._ValueComponent);
    }
}

void Tree::updateLayout(void)
{
    //Update the Position and Size of all the Drawn Rows
    for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
    {
        updateRowLayout(i);
    }
}

void Tree::updateRowLayout(UInt32 Row)
{
    Pnt2f RowTopLeft((getPathForRow(_TopDrawnRow+Row).getDepth()-1) * getModelLayout()->getDepthOffset(), getModelLayout()->getRowHeight()*(Row+_TopDrawnRow));
    if(_DrawnRows[Row]._ExpandedComponent != NULL)
    {
        _DrawnRows[Row]._ExpandedComponent->setSize(_DrawnRows[Row]._ExpandedComponent->getRequestedSize());
        _DrawnRows[Row]._ExpandedComponent->setPosition(RowTopLeft-Vec2f(_DrawnRows[Row]._ExpandedComponent->getSize().x()+ 2.0f, -0.5f*(getModelLayout()->getRowHeight()-_DrawnRows[Row]._ExpandedComponent->getSize().y())));
    }
    _DrawnRows[Row]._ValueComponent->setPosition(RowTopLeft);
    _DrawnRows[Row]._ValueComponent->setSize(Vec2f(getSize().x()-_DrawnRows[Row]._ValueComponent->getPosition().x(), getModelLayout()->getRowHeight()));
}

void Tree::getDrawnRows(Int32& Beginning, Int32& End) const
{
    //Get My Clip Bounds
    Pnt2f ClipTopLeft, ClipBottomRight;
    getClipBounds(ClipTopLeft, ClipBottomRight);

 	if(getModelLayout() != NULL)
 	{
        Beginning = getModelLayout()->getRowForPath(getClosestPathForLocation(ClipTopLeft));
        End       = osgMax(Beginning, getModelLayout()->getRowForPath(getClosestPathForLocation(ClipBottomRight)));
 	}
 	else
 	{
 		Beginning = End = -1;
 	}
}

void Tree::updatePreferredSize(void)
{
    if(getModelLayout() != NULL)
    {
        setPreferredSize(Vec2f(getPreferredSize().x(), getModelLayout()->getRowCount()* getModelLayout()->getRowHeight()));
    }
    else
    {
        setPreferredSize(Vec2f(0,0));
    }
}

void Tree::updateExpandedPath(const TreePath& Path)
{
    Int32 Row(getModelLayout()->getRowForPath(Path));
    if(Row <= _BottomDrawnRow)
    {
        if(Row>=0 && Row>=_TopDrawnRow)
        {
            _DrawnRows[Row-_TopDrawnRow] =createRowComponent(Row);
        }
        UInt32 VisibleChildren = getModelLayout()->getVisibleChildCount(Path);
        if(VisibleChildren > 0)
        {
            updateInsertedRows(Row+1,VisibleChildren);
        }
        else
        {
            updateChildren();
        }
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
    else
    {
        updateChildren();
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
void Tree::setModel          (TreeModel * const value)
{
    Inherited::setModel(value);
    
    //Set the model used by the ModelLayout
    if(getModelLayout() != NULL)
    {
        getModelLayout()->setModel(getModel());
    }

    updateEntireTree();
}

void Tree::setModelLayout    (TreeModelLayout * const value)
{
    Inherited::setModelLayout(value);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Tree::onCreate(const Tree * Id)
{
	Inherited::onCreate(Id);

    if(GlobalSystemState == Startup)
    {
        return;
    }

    DefaultTreeSelectionModelUnrecPtr SelModel = DefaultTreeSelectionModel::create();
    setSelectionModel(SelModel);
    _SelectionAddedConnection = getSelectionModel()->connectSelectionAdded(boost::bind(&Tree::handleSelectionAdded, this, _1));
    _SelectionRemovedConnection = getSelectionModel()->connectSelectionRemoved(boost::bind(&Tree::handleSelectionRemoved, this, _1));

    if(Id != NULL &&
       getModelLayout() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(Id->getModelLayout()->shallowCopy());
        setModelLayout(dynamic_pointer_cast<TreeModelLayout>(FCCopy));
    }
    else
    {
        FixedHeightTreeModelLayoutUnrecPtr TheModelLayout(FixedHeightTreeModelLayout::create());
        setModelLayout(TheModelLayout);
    }

    _ModelTreeNodesChangedConnection = getModelLayout()->connectTreeNodesChanged(boost::bind(&Tree::handleModelTreeNodesChanged, this, _1));
    _ModelTreeNodesInsertedConnection = getModelLayout()->connectTreeNodesInserted(boost::bind(&Tree::handleModelTreeNodesInserted, this, _1));
    _ModelTreeNodesWillBeRemovedConnection = getModelLayout()->connectTreeNodesWillBeRemoved(boost::bind(&Tree::handleModelTreeNodesWillBeRemoved, this, _1));
    _ModelTreeNodesRemovedConnection = getModelLayout()->connectTreeNodesRemoved(boost::bind(&Tree::handleModelTreeNodesRemoved, this, _1));
    _ModelTreeStructureChangedConnection = getModelLayout()->connectTreeStructureChanged(boost::bind(&Tree::handleModelTreeStructureChanged, this, _1));

    _ModelLayoutTreeCollapsedConnection = getModelLayout()->connectTreeCollapsed(boost::bind(&Tree::handleModelLayoutTreeCollapsed, this, _1));
    _ModelLayoutTreeExpandedConnection = getModelLayout()->connectTreeExpanded(boost::bind(&Tree::handleModelLayoutTreeExpanded, this, _1));

    if(getModelLayout() != NULL)
    {
        getSelectionModel()->setRowMapper(getModelLayout());
    }
}

void Tree::onDestroy()
{
}

void Tree::resolveLinks(void)
{
    Inherited::resolveLinks();

    _DrawnRows.clear();

    _ModelTreeNodesChangedConnection.disconnect();
    _ModelTreeNodesInsertedConnection.disconnect();
    _ModelTreeNodesWillBeRemovedConnection.disconnect();
    _ModelTreeNodesRemovedConnection.disconnect();
    _ModelTreeNodesChangedConnection.disconnect();
    _SelectionAddedConnection.disconnect();
    _SelectionRemovedConnection.disconnect();
    _ModelLayoutTreeCollapsedConnection.disconnect();
    _ModelLayoutTreeExpandedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

Tree::Tree(void) :
    Inherited(),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
}

Tree::Tree(const Tree &source) :
    Inherited(source),
        _TopDrawnRow(-1),
        _BottomDrawnRow(-1)
{
}

Tree::~Tree(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Tree::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    
    if(whichField & Tree::ClipBoundsFieldMask)
    {
        updateRowsDrawn();
    }

    if(whichField & (ModelLayoutFieldMask | RowHeightFieldMask) &&
       getModelLayout() != NULL)
    {
        getModelLayout()->setRowHeight(getRowHeight());
    }

    if(whichField & ModelLayoutFieldMask)
    {
        _ModelTreeNodesChangedConnection.disconnect();
        _ModelTreeNodesInsertedConnection.disconnect();
        _ModelTreeNodesWillBeRemovedConnection.disconnect();
        _ModelTreeNodesRemovedConnection.disconnect();
        _ModelTreeStructureChangedConnection.disconnect();
        _ModelLayoutTreeCollapsedConnection.disconnect();
        _ModelLayoutTreeExpandedConnection.disconnect();

        if(getModelLayout() != NULL)
        {
            //Set the model used by the ModelLayout
            getModelLayout()->setModel(getModel());
            _ModelTreeNodesChangedConnection = getModelLayout()->connectTreeNodesChanged(boost::bind(&Tree::handleModelTreeNodesChanged, this, _1));
            _ModelTreeNodesInsertedConnection = getModelLayout()->connectTreeNodesInserted(boost::bind(&Tree::handleModelTreeNodesInserted, this, _1));
            _ModelTreeNodesWillBeRemovedConnection = getModelLayout()->connectTreeNodesWillBeRemoved(boost::bind(&Tree::handleModelTreeNodesWillBeRemoved, this, _1));
            _ModelTreeNodesRemovedConnection = getModelLayout()->connectTreeNodesRemoved(boost::bind(&Tree::handleModelTreeNodesRemoved, this, _1));
            _ModelTreeStructureChangedConnection = getModelLayout()->connectTreeStructureChanged(boost::bind(&Tree::handleModelTreeStructureChanged, this, _1));
            _ModelLayoutTreeCollapsedConnection = getModelLayout()->connectTreeCollapsed(boost::bind(&Tree::handleModelLayoutTreeCollapsed, this, _1));
            _ModelLayoutTreeExpandedConnection = getModelLayout()->connectTreeExpanded(boost::bind(&Tree::handleModelLayoutTreeExpanded, this, _1));
            if(getSelectionModel())
            {
                getSelectionModel()->setRowMapper(getModelLayout());
            }
        }
        updateEntireTree();
    }

    if(whichField & ModelLayoutFieldMask)
    {
        _ModelTreeNodesChangedConnection.disconnect();
        _ModelTreeNodesInsertedConnection.disconnect();
        _ModelTreeNodesWillBeRemovedConnection.disconnect();
        _ModelTreeNodesRemovedConnection.disconnect();
        _ModelTreeStructureChangedConnection.disconnect();

        if(getModelLayout() != NULL)
        {
            //Set the model used by the ModelLayout
            getModelLayout()->setModel(getModel());
            _ModelTreeNodesChangedConnection = getModelLayout()->connectTreeNodesChanged(boost::bind(&Tree::handleModelTreeNodesChanged, this, _1));
            _ModelTreeNodesInsertedConnection = getModelLayout()->connectTreeNodesInserted(boost::bind(&Tree::handleModelTreeNodesInserted, this, _1));
            _ModelTreeNodesWillBeRemovedConnection = getModelLayout()->connectTreeNodesWillBeRemoved(boost::bind(&Tree::handleModelTreeNodesWillBeRemoved, this, _1));
            _ModelTreeNodesRemovedConnection = getModelLayout()->connectTreeNodesRemoved(boost::bind(&Tree::handleModelTreeNodesRemoved, this, _1));
            _ModelTreeStructureChangedConnection = getModelLayout()->connectTreeStructureChanged(boost::bind(&Tree::handleModelTreeStructureChanged, this, _1));
            if(getSelectionModel())
            {
                getSelectionModel()->setRowMapper(getModelLayout());
            }
        }
        updateEntireTree();
    }

    if(whichField & SelectionModelFieldMask)
    {
        _SelectionAddedConnection.disconnect();
        _SelectionRemovedConnection.disconnect();
        if(getSelectionModel() != NULL)
        {
            _SelectionAddedConnection = getSelectionModel()->connectSelectionAdded(boost::bind(&Tree::handleSelectionAdded, this, _1));
            _SelectionRemovedConnection = getSelectionModel()->connectSelectionRemoved(boost::bind(&Tree::handleSelectionRemoved, this, _1));
            if(getModelLayout() != NULL)
            {
                getSelectionModel()->setRowMapper(getModelLayout());
            }
        }
    }
}

void Tree::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Tree NI" << std::endl;
}

void Tree::handleModelTreeNodesChanged(TreeModelEventDetails* const e)
{
    Int32 Row(-1);
    for(UInt32 i(0) ; i<e->getChildren().size() ; ++i)
    {
        Row = getModelLayout()->getRowForPath(e->getChildPath(i));
        if(Row != -1)
        {
            updateRows(Row, 1);
        }
    }
}

void Tree::handleModelTreeNodesInserted(TreeModelEventDetails* const e)
{
    Int32 InsertedRow(-1);
    for(UInt32 i(0) ; i<e->getChildren().size() ; ++i)
    {
        InsertedRow = getModelLayout()->getRowForPath(e->getChildPath(i));
        if(InsertedRow != -1)
        {
            updateInsertedRows(InsertedRow, 1);
        }
    }
}

void Tree::handleModelTreeNodesWillBeRemoved(TreeModelEventDetails* const e)
{
    _RomovedNodeRows.clear();
    Int32 RemovedRow(-1);
    std::vector<TreePath> VisibleDecendants;
    TreePath ThePath;
    for(UInt32 i(0) ; i<e->getChildren().size() ; ++i)
    {
        ThePath = e->getChildPath(i);
        //Get the row for this path
        RemovedRow = getModelLayout()->getRowForPath(ThePath);
        _RomovedNodeRows.insert(RemovedRow);
        
        //Get the rows of all visible decendents
        VisibleDecendants.clear();
        getModelLayout()->getVisibleDecendants(ThePath, VisibleDecendants);
        for(std::vector<TreePath>::iterator Itor(VisibleDecendants.begin()) ; Itor != VisibleDecendants.end(); ++Itor)
        {
            RemovedRow = getModelLayout()->getRowForPath(*Itor);
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
    removeSelectionRows(RemovedSelectionRows);
}

void Tree::handleModelTreeNodesRemoved(TreeModelEventDetails* const e)
{
    Int32 RemovedRow(-1);
    for(std::set<Int32>::iterator Itor(_RomovedNodeRows.begin()) ; Itor != _RomovedNodeRows.end(); ++Itor)
    {
        if((*Itor) != -1)
        {
            updateRemovedRows((*Itor), 1);
        }
    }
    _RomovedNodeRows.clear();
}

void Tree::handleModelTreeStructureChanged(TreeModelEventDetails* const e)
{
    updateChangedNode(e->getPath());
}

void Tree::handleSelectionAdded(TreeSelectionEventDetails* const e)
{
    for(UInt32 i(0) ; i<e->getMFElementsChanged()->size() ; ++i)
    {
        for(Int32 j(e->getElementsChanged(i).x()) ; 
            j<=e->getElementsChanged(i).y() ;
            ++j)
        {
            updateDrawnRow(j);
        }
    }
}

void Tree::handleSelectionRemoved(TreeSelectionEventDetails* const e)
{
    for(UInt32 i(0) ; i<e->getMFElementsChanged()->size() ; ++i)
    {
        for(Int32 j(e->getElementsChanged(i).x()) ; 
            j<=e->getElementsChanged(i).y() ;
            ++j)
        {
            if(j>= 0 && j>= _TopDrawnRow && j<= _BottomDrawnRow)
            {
                updateDrawnRow(j);
            }
        }
    }
}

void Tree::handleModelLayoutTreeCollapsed(TreeModelLayoutEventDetails* const e)
{
    updateCollapsedPath(e->getPath());
}

void Tree::handleModelLayoutTreeExpanded(TreeModelLayoutEventDetails* const e)
{
    updateExpandedPath(e->getPath());
}

Tree::TreeRowComponents::TreeRowComponents(void) :  _ExpandedComponent(NULL), _ValueComponent(NULL), _Row(-1)
{
}

Tree::TreeRowComponents::TreeRowComponents(Component* const ExpandedComponent, Component* const ValueComponent, Int32 Row) :  _ExpandedComponent(ExpandedComponent), _ValueComponent(ValueComponent), _Row(Row)
{
}

OSG_END_NAMESPACE
