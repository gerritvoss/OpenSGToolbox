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
		if(getParentWindow() != NullFC &&
		   getParentWindow()->getDrawingSurface() != NullFC &&
		   getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
			{
				getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionRow(), Row);
			}
			else if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
			{
				getSelectionModel()->removeSelectionRow(Row);// this toggles the interval
			}
			else
			{
				getSelectionModel()->setSelectionRow(Row);
			}
		}
    }
	Container::mousePressed(e);
}

void Tree::keyTyped(const KeyEvent& e)
{
	bool UpdateSelectionIndex(false);
	Int32 ListIndex(0);
	switch(e.getKey())
	{
	case KeyEvent::KEY_UP:
	case KeyEvent::KEY_DOWN:
	case KeyEvent::KEY_RIGHT:
	case KeyEvent::KEY_LEFT:
			//ListIndex = osgMax(_FocusedIndex-1,0);
			//UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_ENTER:
		if (e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
		//	getSelectionModel()->removeSelectionInterval(_FocusedIndex,_FocusedIndex);// this toggles the interval
		}
		else
		{
		//	getSelectionModel()->setSelectionInterval(_FocusedIndex, _FocusedIndex);
		}
		break;
	case KeyEvent::KEY_HOME:
		//ListIndex = 0;
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_END:
		//ListIndex = getModel()->getSize()-1;
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_UP:
		//ListIndex = osgMax(_FocusedIndex-(_BottomDrawnIndex - _TopDrawnIndex),0);
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_DOWN:
		//ListIndex = osgMin<Int32>(_FocusedIndex+(_BottomDrawnIndex - _TopDrawnIndex), getModel()->getSize()-1);
		UpdateSelectionIndex = true;
		break;
	}
	
	if(UpdateSelectionIndex)
	{
		/*focusIndex(ListIndex);
		getSelectionModel()->setLeadSelectionIndex(ListIndex);
		if (e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), ListIndex);
		}
		else
		{
			getSelectionModel()->setAnchorSelectionIndex(ListIndex);
		}*/
	}

	Component::keyTyped(e);
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
    return TreePath(SharedFieldPtr());
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
        return TreePath(SharedFieldPtr());
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
    //TODO:Implement
}

TreePath Tree::getEditingPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}



TreePath Tree::getPathForLocation(const Pnt2f& Loc) const
{
    if(getModelLayout() != NullFC)
    {
        return getModelLayout()->getPathClosestTo(Loc);
    }
    else
    {
        return TreePath(SharedFieldPtr());
    }
    //TODO:Implement
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
    updatePreferredSize();
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

    //Remove the previous drawn rows

    //Determine the drawn rows
    //getDrawnRows(_TopDrawnRow, _BottomDrawnRow);
	//updateRowsDrawn();

    //create the drawn components for these rows
}

void Tree::updateInsertedRows(const UInt32& Begining, const UInt32& NumInsertedRows)
{
    Int32 NewTopDrawnRow,
          NewBottomDrawnRow;
    getDrawnRows(NewTopDrawnRow, NewBottomDrawnRow);

    if(Begining <= _TopDrawnRow)
    {
        for(Int32 i(NumInsertedRows-1) ; i>=0 ; --i)
        {
            _DrawnRows.push_front(createRowComponent(NewTopDrawnRow+i));
        }
        Int32 NumToPop(NewBottomDrawnRow - NewTopDrawnRow - _DrawnRows.size());
        for(Int32 i(0) ; i<NumToPop ; ++i)
        {
            _DrawnRows.pop_back();
        }
    }
    else if(Begining <= NewBottomDrawnRow)
    {
        std::vector<ComponentPtr> RowsPushedDown;
        Int32 NumToPop(_BottomDrawnRow - Begining + 1);
        for(Int32 i(0) ; i<NumToPop ; ++i)
        {
            RowsPushedDown.push_back(_DrawnRows.back());
            _DrawnRows.pop_back();
        }
        for(Int32 i(0) ; i<NumInsertedRows ; ++i)
        {
            _DrawnRows.push_back(createRowComponent(Begining+i));
        }
        for(Int32 i(RowsPushedDown.size()-1) ; i>=0 ; --i)
        {
            _DrawnRows.push_back(RowsPushedDown[i]);
        }
        NumToPop = NewBottomDrawnRow - NewTopDrawnRow - _DrawnRows.size();
        for(Int32 i(0) ; i<NumToPop ; ++i)
        {
            _DrawnRows.pop_back();
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

    updateLayout();
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
		if(getCellGenerator()->getType().isDerivedFrom(TreeComponentGenerator::getClassType()))
        {
            return TreeComponentGenerator::Ptr::dcast(getCellGenerator())->getTreeComponent(TreePtr(this), NodePath.getLastPathComponent(), Selected, getModelLayout()->isExpanded(NodePath), _Model->isLeaf(NodePath.getLastPathComponent()), Row, false);
        }
        else
        {
            return getCellGenerator()->getComponent(TreePtr(this),NodePath.getLastPathComponent(), Row, 0,Selected, false);
        }
    }
    else
    {
        return NullFC;
    }
}

void Tree::updateDrawnRow(const UInt32& Row)
{
    if(Row >= _TopDrawnRow &&
       Row <= _BottomDrawnRow)
    {
        _DrawnRows[Row-_TopDrawnRow] = createRowComponent(Row);
        //TODO: Optimize this!!!!!!!
        beginEditCP(TreePtr(this), ChildrenFieldMask);
            getChildren().setValue(_DrawnRows[Row-_TopDrawnRow],Row-_TopDrawnRow);
        endEditCP(TreePtr(this), ChildrenFieldMask);
    }
}

void Tree::updateLayout(void)
{
    //Update the Position and Size of all the Drawn Rows
    for(UInt32 i(0) ; i<_DrawnRows.size() ; ++i)
    {
        beginEditCP(_DrawnRows[i], Component::PositionFieldMask | Component::SizeFieldMask);
		_DrawnRows[i]->setPosition(Pnt2f((getPathForRow(_TopDrawnRow+i).getDepth()-1) * getModelLayout()->getDepthOffset(), getModelLayout()->getRowHeight()*(i+_TopDrawnRow)));
            _DrawnRows[i]->setSize(Vec2f(getSize().x()-_DrawnRows[i]->getPosition().x(), getModelLayout()->getRowHeight()));
        endEditCP(_DrawnRows[i], Component::PositionFieldMask | Component::SizeFieldMask);
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
        updatePreferredSize();
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
    //TODO: Implement
}

void Tree::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    Int32 InsertedRow(-1);
    for(UInt32 i(0) ; i<e.getChildren().size() ; ++i)
    {
        InsertedRow = _Tree->getModelLayout()->getRowForPath(e.getTreePath().pathByAddingChild(e.getChildren()[i]));
        if(InsertedRow != -1)
        {
            _Tree->updateInsertedRows(InsertedRow, 1);
        }
    }
    _Tree->updatePreferredSize();
}

void Tree::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    //TODO: Implement
    _Tree->updatePreferredSize();
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
        for(UInt32 j(e.getElementsChanged()[i].getMin()) ; 
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
        for(UInt32 j(e.getElementsChanged()[i].getMin()) ; 
            j<=e.getElementsChanged()[i].getMax() ;
            ++j)
        {
            _Tree->updateDrawnRow(j);
        }
    }
}

void Tree::ModelLayoutListener::treeCollapsed(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
    _Tree->updatePreferredSize();
}

void Tree::ModelLayoutListener::treeExpanded(const TreeModelLayoutEvent& event)
{
    //TODO: Implement
    _Tree->updatePreferredSize();
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

