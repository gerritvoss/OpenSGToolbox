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

#include "OSGTableHeader.h"

#include "OSGTable.h"
#include "Component/List/OSGDefaultListSelectionModel.h"
#include "Component/Table/Models/OSGDefaultTableColumnModel.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

#include "Component/Table/ComponentGenerators/OSGDefaultTableCellRenderer.h"
#include "Component/Table/Editors/OSGDefaultTableCellEditor.h"
#include "Component/Table/Editors/OSGTableCellEditor.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Table
A UI Table. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Table::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Table::startEditing(const UInt32& Row, const UInt32& Column)
{
    //If the table is already editing
    if(isEditing())
    {
        //Check if we are already editing the requested cell
        if(_EditingRow == Row && _EditingColumn == Column)
        {
            return;
        }
        else
        {
            //If we are not editing the requested cell, stop the previous editing
            Inherited::getCellEditor()->stopCellEditing();
        }
    }
    
    beginEditCP(TablePtr(this), CellEditorFieldMask);
        setCellEditor(getCellEditor(Row, Column));
    endEditCP(TablePtr(this), CellEditorFieldMask);
    _EditingColumn = Column;
    _EditingRow = Row;
    
    if(Inherited::getCellEditor()->getType().isDerivedFrom(TableCellEditor::getClassType()))
    {
        _EditingComponent = TableCellEditor::Ptr::dcast(Inherited::getCellEditor())->getTableCellEditorComponent(TablePtr(this), getModel()->getValueAt(Row, Column), isSelected(Row, Column), Row, Column);
    }
    else
    {
        _EditingComponent = Inherited::getCellEditor()->getCellEditor(getModel()->getValueAt(Row, Column), isSelected(Row, Column));
    }

    

    Inherited::getCellEditor()->addCellEditorListener(this);

    updateItem(Row*getModel()->getColumnCount() + Column);
	_EditingComponent->setFocused(false);
    _EditingComponent->takeFocus();
}

void Table::checkCellEdit(const EventPtr e, const UInt32& Row, const UInt32& Column)
{
    //Check if this cell is editable
    if(getModel()->isCellEditable(Row, Column))
    {
        //Check if this event will start an edit
        TableCellEditorPtr Editor(getCellEditor(Row, Column));
        if(Editor->isCellEditable(e))
        {
            //Then start Editing
            startEditing(Row, Column);
        }
    }
}

bool Table::getFocusedCell(UInt32& Row, UInt32& Column) const
{
    for(Row = 0 ; Row<getModel()->getRowCount(); ++Row)
    {
        for(Column = 0 ; Column<getModel()->getColumnCount(); ++Column)
        {
            if(getChildren()[Row*getModel()->getColumnCount() + Column]->getFocused())
            {
                return true;
            }
        }
    }
    return false;
}

void Table::keyTyped(const KeyEventPtr e)
{
	bool noFocus = true;
	if (e->getKey() == KeyEvent::KEY_UP || 
        e->getKey() == KeyEvent::KEY_DOWN || 
        e->getKey() == KeyEvent::KEY_RIGHT || 
        e->getKey() == KeyEvent::KEY_LEFT || 
        e->getKey() == KeyEvent::KEY_ENTER)
	{
		for(Int32 i(getChildren().size()-2) ; i>=0 && noFocus; --i)
		{
			if (getChildren()[i]->getFocused())
			{
				noFocus = false; // this exits the loop
				Int32 index(0);
                switch(e->getKey())
                {
                case KeyEvent::KEY_UP:
                    index = i-static_cast<Int32>(getModel()->getColumnCount());
                    if(index < 0)
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_DOWN:
                    index = i+static_cast<Int32>(getModel()->getColumnCount());
                    if(index > getModel()->getColumnCount() * getModel()->getRowCount() - 1)
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_LEFT:
                    index = i-1;
                    if((index/getModel()->getColumnCount()) != (i/getModel()->getColumnCount()))
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_RIGHT:
                    index = i+1;
                    if((index/getModel()->getColumnCount()) != (i/getModel()->getColumnCount()))
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_ENTER:
                    {
                    index = i;
                    UInt32 Row(index/getColumnModel()->getColumnCount()),
                        Column(index%getColumnModel()->getColumnCount());
					if (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
                        changeSelection(Row,Column,true,true);
					}
					else
					{
                        changeSelection(Row,Column,false,false);
					}
                    break;
                    }
                default:
                    break;
                }
				getChildren()[index]->takeFocus();
                UInt32 Row(index/getColumnModel()->getColumnCount()),
                    Column(index%getColumnModel()->getColumnCount());
				if (e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
				{
					changeSelection(Row, Column, false, true);
				}
			}
		}
	}

    UInt32 Row, Column;
    if(getFocusedCell(Row, Column))
    {
	   checkCellEdit(e, Row, Column);
    }
	Component::keyTyped(e);
}
     
void Table::mouseClicked(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
			getChildren()[i]->mouseClicked(e);
			break;
		}
    }
	Component::mouseClicked(e);
}

void Table::mouseReleased(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
			getChildren()[i]->mouseReleased(e);
			break;
		}
    }
	Component::mouseReleased(e);
}

void Table::mouseMoved(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
			getChildren()[i]->mouseMoved(e);
		}
    }
	Component::mouseMoved(e);
}

void Table::mouseDragged(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
			getChildren()[i]->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void Table::mouseWheelMoved(const MouseWheelEventPtr e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
			getChildren()[i]->mouseWheelMoved(e);
        }
    }
	Component::mouseWheelMoved(e);
}

void Table::produceMouseExitOnComponent(const MouseEventPtr e, ComponentPtr Comp)
{
    UInt32 i(0);
    while(i<getChildren().size()-1 && getChildren()[i] != Comp)
    {
        ++i;
    }
    if(i < getChildren().size()-1)
    {
	   checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
    }
    Inherited::produceMouseExitOnComponent(e,Comp);
}

void Table::produceMouseEnterOnComponent(const MouseEventPtr e, ComponentPtr Comp)
{
    UInt32 i(0);
    while(i<getChildren().size()-1 && getChildren()[i] != Comp)
    {
        ++i;
    }
    if(i < getChildren().size()-1)
    {
	   checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
    }
    Inherited::produceMouseEnterOnComponent(e,Comp);
}

void Table::keyReleased(const KeyEventPtr e)
{
}

void Table::keyPressed(const KeyEventPtr e)
{
}


void Table::mousePressed(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());

        //Table Header
        if(isContained && i==getChildren().size()-1)
	    {
		    //Give myself temporary focus
		    takeFocus(true);
		    if(!getChildren()[i]->getType().isDerivedFrom(Container::getClassType()))
		    {
			    getChildren()[i]->takeFocus();
		    }
		    getChildren()[i]->mousePressed(e);
            break;
	    }
		else if(isContained)
		{
            UInt32 Row(i/getColumnModel()->getColumnCount()),
                Column(i%getColumnModel()->getColumnCount());
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren()[i]->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren()[i]->takeFocus();
				if(getParentWindow() != NullFC &&
				   getParentWindow()->getDrawingSurface() != NullFC &&
				   getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
				{
					if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						changeSelection(Row, Column, false, true);
					}
					else if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
						changeSelection(Row, Column, true, true);
					}
					else
					{
						changeSelection(Row, Column, false, false);
					}
				}
			}
	        checkCellEdit(e, Row, Column);
			getChildren()[i]->mousePressed(e);
			break;
		}
    }
	if(isContained)
	{
		//Remove my temporary focus
		giveFocus(NullFC, false);
	}
	else
	{
		//Give myself permanent focus
		takeFocus();
    }
	Component::mousePressed(e);
}

bool Table::isSelected(const UInt32& Row, const UInt32& Column) const
{
    if(getColumnModel()->getColumnSelectionAllowed() && getRowSelectionAllowed())
    {
        return getColumnModel()->getSelectionModel()->isSelectedIndex(Column) &&
            _RowSelectionModel->isSelectedIndex(Row);
    }
    else
    {
        return (getColumnModel()->getColumnSelectionAllowed() &&
                    getColumnModel()->getSelectionModel()->isSelectedIndex(Column))
                    ||
                    (getRowSelectionAllowed() &&
                    _RowSelectionModel->isSelectedIndex(Row));
    }
}

void Table::updateItem(const UInt32& index)
{
    UInt32 Row(index/getColumnModel()->getColumnCount()),
           Column(index%getColumnModel()->getColumnCount());

	//Transfer focus, enabled, Listeners
	ComponentPtr PrevComponent = getChildren()[index];
	getChildren()[index]->removeFocusListener(this);
	
    //Check if this cell is being Edited
    if(isEditing() && Row == _EditingRow && Column == _EditingColumn)
    {
        getChildren()[index] = _EditingComponent;
    }
    else //Non-Editing Cell
    {
        boost::any CellValue = getModel()->getValueAt(Row, Column);
    
        getChildren()[index] = getCellRenderer(Row, Column)->getTableCellRendererComponent(TablePtr(this), CellValue, isSelected(Row, Column), PrevComponent->getFocused(), Row, Column);
    }
    if(PrevComponent->getFocused())
    {
        //getChildren()[index]->takeFocus();
        getParentWindow()->setFocusedComponent(getChildren()[index]);
    }
	getChildren()[index]->addFocusListener(this);
	getChildren()[index]->setFocused(PrevComponent->getFocused());
	getChildren()[index]->setPosition(PrevComponent->getPosition());
	getChildren()[index]->setSize(PrevComponent->getSize());
	getChildren()[index]->setParentContainer(PrevComponent->getParentContainer());
	getChildren()[index]->setParentWindow(PrevComponent->getParentWindow());
	getChildren()[index]->updateClipBounds();
}
void Table::focusGained(const FocusEventPtr e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e->getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren()[index])
			{
				break;
			}
		}
		updateItem(index);
	}
}

void Table::focusLost(const FocusEventPtr e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e->getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren()[index])
			{
				break;
			}
		}
		updateItem(index);
	}
}
void Table::drawInternal(const GraphicsPtr TheGraphics, Real32 Opacity) const
{
    if(getShowVerticalLines() || getShowHorizontalLines())
    {
	    Pnt2f BorderTopLeft, BorderBottomRight;
	    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

        if(getShowVerticalLines())
        {
            UInt32 CumulativeColumnWidth(BorderTopLeft.x());
            for(UInt32 i(0) ; i<getColumnModel()->getColumnCount() ; ++i)
            {
                CumulativeColumnWidth += getColumnModel()->getColumn(i)->getWidth();
                TheGraphics->drawRect(Pnt2f(CumulativeColumnWidth, BorderTopLeft.y()),
                                    Pnt2f(CumulativeColumnWidth+getColumnModel()->getColumnMargin(), BorderBottomRight.y()),
                                    getGridColor(), getOpacity()*Opacity);
                CumulativeColumnWidth += getColumnModel()->getColumnMargin();
            }
        }

        if(getShowHorizontalLines())
        {
            UInt32 CumulativeColumnHeight(getHeader()->getPosition().y() + getHeader()->getSize().y());
            for(UInt32 i(0) ; i<getModel()->getRowCount() ; ++i)
            {
                TheGraphics->drawRect(Pnt2f(BorderTopLeft.x(), CumulativeColumnHeight),
                                    Pnt2f(BorderBottomRight.x(), CumulativeColumnHeight + getRowMargin()),
                                    getGridColor(), getOpacity()*Opacity);
                CumulativeColumnHeight += getRowMargin();
                CumulativeColumnHeight += getRowHeight();
            }
            
        }
    }

    Inherited::drawInternal(TheGraphics,Opacity);
}


void Table::updateLayout(void)
{
    if(getChildren().size() == 0){ return; }
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	

    //Position and size the Header
    UInt32 HeaderIndex = getChildren().size()-1;
    beginEditCP(getChildren()[HeaderIndex], PositionFieldMask | SizeFieldMask);
        getChildren()[HeaderIndex]->setPosition(BorderTopLeft);
        getChildren()[HeaderIndex]->setSize(getChildren()[HeaderIndex]->getPreferredSize());
    endEditCP(getChildren()[HeaderIndex], PositionFieldMask | SizeFieldMask);


    //Position and size all of the cells
    UInt32 CellIndex(0);
    UInt32 CumulativeWidth(0);
    UInt32 CumulativeHeight(BorderTopLeft.y() +
                            getChildren()[HeaderIndex]->getPosition().y() +
                            getChildren()[HeaderIndex]->getSize().y());
    for(UInt32 Row(0) ; Row<getModel()->getRowCount() ; ++Row)
    {
        CumulativeWidth = BorderTopLeft.x();
        CumulativeHeight += getRowMargin();
        for(UInt32 Column(0) ; Column<getModel()->getColumnCount() ; ++Column)
        {
            CellIndex = Row*getModel()->getColumnCount() + Column;
            beginEditCP(getChildren()[CellIndex], PositionFieldMask | SizeFieldMask);
                
                getChildren()[CellIndex]->setPosition(Pnt2f(CumulativeWidth, CumulativeHeight));

                getChildren()[CellIndex]->setSize(Vec2f(
                    getColumnModel()->getColumn(Column)->getWidth(),
                    getRowHeight()));

            endEditCP(getChildren()[CellIndex], PositionFieldMask | SizeFieldMask);

            CumulativeWidth += getColumnModel()->getColumn(Column)->getWidth() + 
                getColumnModel()->getColumnMargin();
        }
        CumulativeHeight += getRowHeight();
    }
    
    //Update My Preferred Size
	Pnt2f TopLeft, BottomRight;
	getBounds(TopLeft, BottomRight);

    Vec2f NewPreferredSize(getColumnModel()->getTotalColumnWidth() + (BottomRight.x() - TopLeft.x() - BorderBottomRight.x() + BorderTopLeft.x()),
                               CumulativeHeight + (BottomRight.y() - TopLeft.y() - BorderBottomRight.y() + BorderTopLeft.y()));
    if(NewPreferredSize != getPreferredSize())
    {
        beginEditCP(TablePtr(this), PreferredSizeFieldMask);
            setPreferredSize(NewPreferredSize);
        endEditCP(TablePtr(this), PreferredSizeFieldMask);
    }
}

void Table::updateTableComponents(void)
{
    if(getModel() == NullFC || getColumnModel() == NullFC)
    {
        return;
    }
    boost::any CellValue;

    beginEditCP(TablePtr(this), TableFieldMask);
    getTable().clear();
    for(UInt32 Row(0) ; Row<getModel()->getRowCount() ; ++Row)
    {
        for(UInt32 Column(0) ; Column<getModel()->getColumnCount() ; ++Column)
        {

            //TODO: Add Focusing
            CellValue = getModel()->getValueAt(Row, Column);
            getTable().push_back(
            getCellRenderer(Row, Column)->getTableCellRendererComponent(TablePtr(this), CellValue, isSelected(Row, Column), false, Row, Column));
        }
    }
    endEditCP(TablePtr(this), TableFieldMask);

    //Remove focus Listeners
    for(UInt32 i(0) ; i+1< getChildren().size() ; ++i)
    {
        getChildren()[i]->removeFocusListener(this);
    }

    beginEditCP(TablePtr(this) , ChildrenFieldMask);
        getChildren().clear();

        //Add all of the Table Components
        for(UInt32 i(0); i<getTable().size() ; ++i)
        {
            getChildren().push_back(getTable()[i]);
			getChildren()[i]->addFocusListener(this);
        }

        getChildren().push_back(getHeader());
        
    endEditCP(TablePtr(this) , ChildrenFieldMask);
}

void Table::contentsHeaderRowChanged(const TableModelEventPtr e)
{
    if(getAutoCreateColumnsFromModel() && getModel() != NullFC)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::contentsChanged(const TableModelEventPtr e)
{
    if(getAutoCreateColumnsFromModel() && getModel() != NullFC)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::intervalAdded(const TableModelEventPtr e)
{
    updateTableComponents();
}

void Table::intervalRemoved(const TableModelEventPtr e)
{
    updateTableComponents();
}

void Table::changeSelection(const UInt32& rowIndex, const UInt32& columnIndex, bool toggle, bool extend)
{
    if(toggle)  //Toggle True
    {
        if(extend)  //Extend True
        {
            if(getColumnModel()->getColumnSelectionAllowed() &&
                getRowSelectionAllowed())
            {
                if(getColumnModel()->getSelectionModel()->isSelectedIndex(columnIndex) !=
                   _RowSelectionModel->isSelectedIndex(rowIndex))
                {
                    getColumnModel()->getSelectionModel()->setSelectionInterval(columnIndex, columnIndex);
                    _RowSelectionModel->setSelectionInterval(rowIndex, rowIndex);
                }
                else
                {
                    getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                    _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
                }
            }
            else if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
            }
            else if(getRowSelectionAllowed())
            {
                _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
            }
        }
        else  //Extend False
        {
            if(getColumnModel()->getSelectionModel()->isSelectedIndex(columnIndex) &&
               _RowSelectionModel->isSelectedIndex(rowIndex))
            {
                if(getColumnModel()->getColumnSelectionAllowed())
                {
                    getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                }
                if(getRowSelectionAllowed())
                {
                    _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
                }
            }
            else
            {
                if(getColumnModel()->getColumnSelectionAllowed())
                {
                    getColumnModel()->getSelectionModel()->setSelectionInterval(columnIndex, columnIndex);
                }
                if(getRowSelectionAllowed())
                {
                    _RowSelectionModel->setSelectionInterval(rowIndex, rowIndex);
                }
            }
        }
    }
    else  //Toggle False
    {
        if(extend)  //Extend True
        {
            if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->addSelectionInterval(getColumnModel()->getSelectionModel()->getAnchorSelectionIndex(), columnIndex);
            }
            if(getRowSelectionAllowed())
            {
                _RowSelectionModel->addSelectionInterval(_RowSelectionModel->getAnchorSelectionIndex(), rowIndex);
            }
        }
        else  //Extend False
        {
            //Clear old selection
            if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->clearSelection();
            }
            if(getRowSelectionAllowed())
            {
                _RowSelectionModel->clearSelection();
            }

            //Ensure new cell is selected
            if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->addSelectionInterval(columnIndex, columnIndex);
            }
            if(getRowSelectionAllowed())
            {
                _RowSelectionModel->addSelectionInterval(rowIndex, rowIndex);
            }
        }
    }
}

void Table::clearSelection(void)
{
    getColumnModel()->getSelectionModel()->clearSelection();
    _RowSelectionModel->clearSelection();
}

void Table::columnAdded(const TableColumnModelEventPtr e)
{
    updateTableComponents();
}

void Table::columnMarginChanged(const ChangeEventPtr e)
{
    updateLayout();
}

void Table::columnMoved(const TableColumnModelEventPtr e)
{
    updateTableComponents();
}

void Table::columnRemoved(const TableColumnModelEventPtr e)
{
    updateTableComponents();
}

void Table::columnSelectionChanged(const ListSelectionEventPtr e)
{
    for(UInt32 i(0) ; i<getTable().size() ; ++i)
    {
        updateItem(i);
    }
}

bool Table::editCellAt(const UInt32& row, const UInt32& column)
{
    //TODO:Implement
    startEditing(row, column);
    return true;
}

bool Table::editCellAt(const UInt32& row, const UInt32& column, const EventPtr e)
{
    //TODO:Implement
    checkCellEdit(e, row, column);
    return true;
}

void Table::editingCanceled(const ChangeEventPtr e)
{
    Inherited::getCellEditor()->removeCellEditorListener(this);
    beginEditCP(TablePtr(this), CellEditorFieldMask);
        setCellEditor(NullFC);
    endEditCP(TablePtr(this), CellEditorFieldMask);
    _EditingComponent = NullFC;
    updateItem(_EditingRow*getModel()->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;
}

void Table::editingStopped(const ChangeEventPtr e)
{
    getModel()->setValueAt(Inherited::getCellEditor()->getCellEditorValue(), _EditingRow, _EditingColumn);

    
    Inherited::getCellEditor()->removeCellEditorListener(this);
    beginEditCP(TablePtr(this), CellEditorFieldMask);
        setCellEditor(NullFC);
    endEditCP(TablePtr(this), CellEditorFieldMask);
    _EditingComponent = NullFC;
    updateItem(_EditingRow*getModel()->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;

}

TableCellEditorPtr Table::getCellEditor(const UInt32& row, const UInt32& column) const
{
    if(getColumnModel()->getColumn(column)->getCellEditor() != NULL)
    {
        return getColumnModel()->getColumn(column)->getCellEditor();
    }
    else if(getModel()->getColumnType(column) != typeid(void))
    {
        return getDefaultEditor(getModel()->getColumnType(column));
    }
    else
    {
        return getDefaultEditor(getModel()->getValueAt(row,column).type());
    }
}

TableCellRendererPtr Table::getCellRenderer(const UInt32& row, const UInt32& column) const
{
    if(getColumnModel()->getColumn(column)->getCellRenderer() != NULL)
    {
        return getColumnModel()->getColumn(column)->getCellRenderer();
    }
    else if(getModel()->getColumnType(column) != typeid(void))
    {
        return getDefaultRenderer(getModel()->getColumnType(column));
    }
    else
    {
        return getDefaultRenderer(getModel()->getValueAt(row,column).type());
    }
}

std::vector<UInt32> Table::getSelectedColumns(void) const
{
    return getColumnModel()->getSelectedColumns();
}

std::vector<UInt32> Table::getSelectedRows(void) const
{
    if(getRowSelectionAllowed())
    {
        std::vector<UInt32> SelectedVector;
        for(UInt32 i(0) ; i<getModel()->getRowCount() ; ++i)
        {
            if(_RowSelectionModel->isSelectedIndex(i))
            {
                SelectedVector.push_back(i);
            }
        }
        return SelectedVector;
    }
    else
    {
        return std::vector<UInt32>();
    }
}

Int32 Table::rowAtPoint(const Pnt2f& point)
{
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
    
    UInt32 CumulativeHeight(BorderTopLeft.y() +
                            getChildren().back()->getPosition().y() +
                            getChildren().back()->getSize().y());

    for(Int32 i(0) ; i<getModel()->getRowCount() ; ++i)
    {
        CumulativeHeight +=getRowMargin();
        if(point.x() <= CumulativeHeight)
        {
            return i-1;
        }
        CumulativeHeight += getRowHeight();
    }

    return -1;
}

void Table::selectAll(void)
{
    getColumnModel()->getSelectionModel()->setSelectionInterval(0, getModel()->getColumnCount());
    _RowSelectionModel->setSelectionInterval(0, getModel()->getRowCount());
}

void Table::setCellSelectionEnabled(bool cellSelectionEnabled)
{
    getColumnModel()->setColumnSelectionAllowed(cellSelectionEnabled);
    beginEditCP(TablePtr(this), RowSelectionAllowedFieldMask);
        setRowSelectionAllowed(cellSelectionEnabled);
    endEditCP(TablePtr(this), RowSelectionAllowedFieldMask);
}

void Table::selectionChanged(const ListSelectionEventPtr e)
{
    for(UInt32 i(0) ; i<getTable().size() ; ++i)
    {
        updateItem(i);
    }
}

void Table::setDragEnabled(bool b)
{
    //TODO:Implement
}

void Table::setIntercellSpacing(const UInt32& RowMargin, const UInt32& ColumnMargin)
{
    getColumnModel()->setColumnMargin(ColumnMargin);

    beginEditCP(TablePtr(this), RowMarginFieldMask);
        setRowMargin(RowMargin);
    endEditCP(TablePtr(this), RowMarginFieldMask);
}

//void Table::setRowHeight(const UInt32& row, const UInt32& rowHeight)
//{
    //TODO:Implement
//}

void Table::setShowGrid(bool showGrid)
{
    beginEditCP(TablePtr(this), ShowHorizontalLinesFieldMask | ShowVerticalLinesFieldMask);
        setShowHorizontalLines(showGrid);
        setShowVerticalLines(showGrid);
    endEditCP(TablePtr(this), ShowHorizontalLinesFieldMask | ShowVerticalLinesFieldMask);
}

TableCellEditorPtr Table::getDefaultEditor(const std::type_info& TheType) const
{
    CellEditorByTypeMap::const_iterator FindItor(_DefaultCellEditorByTypeMap.find(std::string(TheType.name())));
    if(FindItor != _DefaultCellEditorByTypeMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        SWARNING << "No Default Table Cell Editor for type: " << TheType.name() << "." << std::endl;
        if(_DefaultCellEditor == NullFC)
        {
            _DefaultCellEditor = DefaultTableCellEditor::create();
            addRefCP(_DefaultCellEditor);
        }
        return _DefaultCellEditor;
    }
}

TableCellRendererPtr Table::getDefaultRenderer(const std::type_info& TheType) const
{
    CellRendererByTypeMap::const_iterator FindItor(_DefaultCellRendererByTypeMap.find(std::string(TheType.name())));
    if(FindItor != _DefaultCellRendererByTypeMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        SWARNING << "No Default Table Cell Renderer for type: " << TheType.name() << "." << std::endl;
        if(_DefaultCellRenderer == NULL)
        {
            _DefaultCellRenderer = new DefaultTableCellRenderer();
        }
        return _DefaultCellRenderer;
    }
}


void Table::setSelectionModel(ListSelectionModelPtr newModel)
{
    if(_RowSelectionModel.get() != NULL)
    {
        _RowSelectionModel->removeListSelectionListener(this);
    }
    _RowSelectionModel = newModel;
    if(_RowSelectionModel.get() != NULL)
    {
        _RowSelectionModel->addListSelectionListener(this);
    }
}

void Table::createColumnsFromModel(void)
{
    getColumnModel()->removeColumnModelListener(this);
    //Clear the old columns from the ColumnModel
    while(getColumnModel()->getColumnCount() > 0)
    {
        getColumnModel()->removeColumn(getColumnModel()->getColumn(0));
    }

    //Add the Columns to the Model
    TableColumnPtr NewColumn;
    for(UInt32 i(0) ; i<getModel()->getColumnCount() ; ++i)
    {
        NewColumn = TableColumn::create();
        NewColumn->setHeaderValue(getModel()->getColumnValue(i));
        getColumnModel()->addColumn(NewColumn);
    }
    getColumnModel()->addColumnModelListener(this);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Table::Table(void) :
    Inherited(),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NullFC)
{
}

Table::Table(const Table &source) :
    Inherited(source),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NullFC),
    _RowSelectionModel(ListSelectionModelPtr(new DefaultListSelectionModel())),
    _DefaultCellEditorByTypeMap(source._DefaultCellEditorByTypeMap),
    _DefaultCellRendererByTypeMap(source._DefaultCellRendererByTypeMap)
{
    if(getModel() != NullFC)
    {
        getModel()->addTableModelListener(this);
    }
    if(getColumnModel() != NullFC)
    {
        if(getAutoCreateColumnsFromModel() && getModel() != NullFC)
        {
            createColumnsFromModel();
        }
        getColumnModel()->setSelectionModel(ListSelectionModelPtr(new DefaultListSelectionModel()));
        getColumnModel()->addColumnModelListener(this);
    }
    if(_RowSelectionModel.get() != NULL)
    {
        _RowSelectionModel->addListSelectionListener(this);
    }

    if(getHeader() != NullFC)
    {
        //Set the Table that the Header Points to to NullFC,
        //Otherwise, if the Header points to this table, there will be an infinite
        //recursion in the deepClone
        getHeader()->setTable(NullFC);

        //Clone the Header
        setHeader(TableHeader::Ptr::dcast(deepClone(getHeader())));
        beginEditCP(getHeader(), TableFieldMask);
            getHeader()->setTable(TablePtr(this));
        endEditCP(getHeader(), TableFieldMask);
        beginEditCP(getHeader(), TableHeader::ColumnModelFieldMask);
            getHeader()->setColumnModel(getColumnModel());
        endEditCP(getHeader(), TableHeader::ColumnModelFieldMask);
    }
    updateTableComponents();
}

Table::~Table(void)
{
    if(_DefaultCellEditor != NullFC)
    {
        subRefCP(_DefaultCellEditor);
    }
}

/*----------------------------- class specific ----------------------------*/

void Table::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & HeaderFieldMask) &&
        getHeader() != NullFC)
    {
        beginEditCP(getHeader(), TableFieldMask);
            getHeader()->setTable(TablePtr(this));
        endEditCP(getHeader(), TableFieldMask);
        beginEditCP(getHeader(), TableHeader::ColumnModelFieldMask);
            getHeader()->setColumnModel(getColumnModel());
        endEditCP(getHeader(), TableHeader::ColumnModelFieldMask);
    }

    if(whichField & RowSelectionAllowedFieldMask)
    {
        _RowSelectionModel->clearSelection();
        if(getColumnModel()->getSelectionModel().get() != NULL)
        {
            getColumnModel()->getSelectionModel()->clearSelection();
        }
    }

    if(whichField & ColumnModelFieldMask)
    {
        //if(_ColumnModel.get() != NULL)
        //{
        //    _ColumnModel->removeColumnModelListener(this);
        //}
        //_ColumnModel = columnModel;
        if(getHeader() != NullFC)
        {
            getHeader()->setColumnModel(getColumnModel());
        }
        if(getColumnModel() != NullFC)
        {
            if(getModel() != NullFC && getAutoCreateColumnsFromModel())
            {
                createColumnsFromModel();
            }
            getColumnModel()->addColumnModelListener(this);
        }
        updateTableComponents();
    }
    if(whichField & ModelFieldMask)
    {
        //if(_Model.get() != NULL)
        //{
        //    _Model->removeTableModelListener(this);
        //}
        //_Model = dataModel;
        if(getModel() != NullFC)
        {
            if(getAutoCreateColumnsFromModel())
            {
                createColumnsFromModel();
            }
            getModel()->addTableModelListener(this);
        }
        updateTableComponents();
    }
}

void Table::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Table NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTABLEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTABLEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTABLEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

