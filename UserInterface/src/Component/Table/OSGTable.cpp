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
#include "Component/Table/OSGDefaultTableColumnModel.h"
#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

#include "Component/Table/DefaultRenderers/OSGDefaultTableCellRenderer.h"
#include "Component/Table/DefaultEditors/OSGDefaultTableCellEditor.h"

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
            _CellEditor->stopCellEditing();
        }
    }
    
    _CellEditor = getCellEditor(Row, Column);
    _EditingColumn = Column;
    _EditingRow = Row;
    _EditingComponent = _CellEditor->getTableCellEditorComponent(TablePtr(this), _Model->getValueAt(Row, Column), isSelected(Row, Column), Row, Column);

    _CellEditor->addCellEditorListener(this);

    updateItem(Row*_Model->getColumnCount() + Column);
	_EditingComponent->setFocused(false);
    _EditingComponent->takeFocus();
}

void Table::checkCellEdit(const Event& e, const UInt32& Row, const UInt32& Column)
{
    //Check if this cell is editable
    if(_Model->isCellEditable(Row, Column))
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
    for(Row = 0 ; Row<_Model->getRowCount(); ++Row)
    {
        for(Column = 0 ; Column<_Model->getColumnCount(); ++Column)
        {
            if(getChildren().getValue(Row*_Model->getColumnCount() + Column)->getFocused())
            {
                return true;
            }
        }
    }
    return false;
}

void Table::keyTyped(const KeyEvent& e)
{
	bool noFocus = true;
	if (e.getKey() == KeyEvent::KEY_UP || 
        e.getKey() == KeyEvent::KEY_DOWN || 
        e.getKey() == KeyEvent::KEY_RIGHT || 
        e.getKey() == KeyEvent::KEY_LEFT || 
        e.getKey() == KeyEvent::KEY_ENTER)
	{
		for(Int32 i(getChildren().size()-2) ; i>=0 && noFocus; --i)
		{
			if (getChildren().getValue(i)->getFocused())
			{
				noFocus = false; // this exits the loop
				Int32 index(0);
                switch(e.getKey())
                {
                case KeyEvent::KEY_UP:
                    index = i-static_cast<Int32>(_Model->getColumnCount());
                    if(index < 0)
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_DOWN:
                    index = i+static_cast<Int32>(_Model->getColumnCount());
                    if(index > _Model->getColumnCount() * _Model->getRowCount() - 1)
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_LEFT:
                    index = i-1;
                    if((index/_Model->getColumnCount()) != (i/_Model->getColumnCount()))
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_RIGHT:
                    index = i+1;
                    if((index/_Model->getColumnCount()) != (i/_Model->getColumnCount()))
                    {
                        index = i;
                    }
                    break;
                case KeyEvent::KEY_ENTER:
                    {
                    index = i;
                    UInt32 Row(index/_ColumnModel->getColumnCount()),
                        Column(index%_ColumnModel->getColumnCount());
					if (e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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
				getChildren().getValue(index)->takeFocus();
                UInt32 Row(index/_ColumnModel->getColumnCount()),
                    Column(index%_ColumnModel->getColumnCount());
				if (e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
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
     
void Table::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
            }
			getChildren().getValue(i)->mouseClicked(e);
			break;
		}
    }
	Component::mouseClicked(e);
}

void Table::mouseReleased(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
            }
			getChildren().getValue(i)->mouseReleased(e);
			break;
		}
    }
	Component::mouseReleased(e);
}

void Table::mouseMoved(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
            }
			getChildren().getValue(i)->mouseMoved(e);
		}
    }
	Component::mouseMoved(e);
}

void Table::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
            }
			getChildren().getValue(i)->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void Table::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
            if(i != getChildren().size()-1)
            {
	            checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
            }
			getChildren().getValue(i)->mouseWheelMoved(e);
        }
    }
	Component::mouseWheelMoved(e);
}

void Table::produceMouseExitOnComponent(const MouseEvent& e, ComponentPtr Comp)
{
    UInt32 i(0);
    while(i<getChildren().size()-1 && getChildren().getValue(i) != Comp)
    {
        ++i;
    }
    if(i < getChildren().size()-1)
    {
	   checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
    }
    Inherited::produceMouseExitOnComponent(e,Comp);
}

void Table::produceMouseEnterOnComponent(const MouseEvent& e, ComponentPtr Comp)
{
    UInt32 i(0);
    while(i<getChildren().size()-1 && getChildren().getValue(i) != Comp)
    {
        ++i;
    }
    if(i < getChildren().size()-1)
    {
	   checkCellEdit(e, i/_ColumnModel->getColumnCount(), i%_ColumnModel->getColumnCount());
    }
    Inherited::produceMouseEnterOnComponent(e,Comp);
}

void Table::keyReleased(const KeyEvent& e)
{
}

void Table::keyPressed(const KeyEvent& e)
{
}


void Table::mousePressed(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());

        //Table Header
        if(isContained && i==getChildren().size()-1)
	    {
		    //Give myself temporary focus
		    takeFocus(true);
		    if(!getChildren().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
		    {
			    getChildren().getValue(i)->takeFocus();
		    }
		    getChildren().getValue(i)->mousePressed(e);
            break;
	    }
		else if(isContained)
		{
            UInt32 Row(i/_ColumnModel->getColumnCount()),
                Column(i%_ColumnModel->getColumnCount());
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren().getValue(i)->takeFocus();
				if(getParentFrame() != NullFC &&
				   getParentFrame()->getDrawingSurface() != NullFC &&
				   getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
				{
					if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						changeSelection(Row, Column, false, true);
					}
					else if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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
			getChildren().getValue(i)->mousePressed(e);
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
    if(_ColumnModel->getColumnSelectionAllowed() && getRowSelectionAllowed())
    {
        return _ColumnModel->getSelectionModel()->isSelectedIndex(Column) &&
            _RowSelectionModel->isSelectedIndex(Row);
    }
    else
    {
        return (_ColumnModel->getColumnSelectionAllowed() &&
                    _ColumnModel->getSelectionModel()->isSelectedIndex(Column))
                    ||
                    (getRowSelectionAllowed() &&
                    _RowSelectionModel->isSelectedIndex(Row));
    }
}

void Table::updateItem(const UInt32& index)
{
    UInt32 Row(index/_ColumnModel->getColumnCount()),
           Column(index%_ColumnModel->getColumnCount());

	//Transfer focus, enabled, Listeners
	ComponentPtr PrevComponent = getChildren().getValue(index);
	getChildren().getValue(index)->removeFocusListener(this);
	
    //Check if this cell is being Edited
    if(isEditing() && Row == _EditingRow && Column == _EditingColumn)
    {
        getChildren().setValue(_EditingComponent, index);
    }
    else //Non-Editing Cell
    {
        SharedFieldPtr CellValue = _Model->getValueAt(Row, Column);
    
        getChildren().setValue(getCellRenderer(Row, Column)->getTableCellRendererComponent(TablePtr(this), CellValue, isSelected(Row, Column), PrevComponent->getFocused(), Row, Column)
                    ,index);
    }
    if(PrevComponent->getFocused())
    {
        //getChildren().getValue(index)->takeFocus();
        getParentFrame()->setFocusedComponent(getChildren().getValue(index));
    }
	getChildren().getValue(index)->addFocusListener(this);
	getChildren().getValue(index)->setFocused(PrevComponent->getFocused());
	getChildren().getValue(index)->setPosition(PrevComponent->getPosition());
	getChildren().getValue(index)->setSize(PrevComponent->getSize());
	getChildren().getValue(index)->setParentContainer(PrevComponent->getParentContainer());
	getChildren().getValue(index)->setParentFrame(PrevComponent->getParentFrame());
	getChildren().getValue(index)->updateClipBounds();
}
void Table::focusGained(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		updateItem(index);
	}
}

void Table::focusLost(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		updateItem(index);
	}
}
void Table::drawInternal(const GraphicsPtr TheGraphics) const
{
    if(getShowVerticalLines() || getShowHorizontalLines())
    {
	    Pnt2s BorderTopLeft, BorderBottomRight;
	    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

        if(getShowVerticalLines())
        {
            UInt32 CumulativeColumnWidth(BorderTopLeft.x());
            for(UInt32 i(0) ; i<_ColumnModel->getColumnCount() ; ++i)
            {
                CumulativeColumnWidth += _ColumnModel->getColumn(i)->getWidth();
                TheGraphics->drawRect(Pnt2s(CumulativeColumnWidth, BorderTopLeft.y()),
                                    Pnt2s(CumulativeColumnWidth+_ColumnModel->getColumnMargin(), BorderBottomRight.y()),
                                    getGridColor(), getOpacity());
                CumulativeColumnWidth += _ColumnModel->getColumnMargin();
            }
        }

        if(getShowHorizontalLines())
        {
            UInt32 CumulativeColumnHeight(getHeader()->getPosition().y() + getHeader()->getSize().y());
            for(UInt32 i(0) ; i<_Model->getRowCount() ; ++i)
            {
                TheGraphics->drawRect(Pnt2s(BorderTopLeft.x(), CumulativeColumnHeight),
                                    Pnt2s(BorderBottomRight.x(), CumulativeColumnHeight + getRowMargin()),
                                    getGridColor(), getOpacity());
                CumulativeColumnHeight += getRowMargin();
                CumulativeColumnHeight += getRowHeight();
            }
            
        }
    }

    Inherited::drawInternal(TheGraphics);
}


void Table::updateLayout(void)
{
    if(getChildren().size() == 0){ return; }
	Pnt2s BorderTopLeft, BorderBottomRight;
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
    for(UInt32 Row(0) ; Row<_Model->getRowCount() ; ++Row)
    {
        CumulativeWidth = BorderTopLeft.x();
        CumulativeHeight += getRowMargin();
        for(UInt32 Column(0) ; Column<_Model->getColumnCount() ; ++Column)
        {
            CellIndex = Row*_Model->getColumnCount() + Column;
            beginEditCP(getChildren()[CellIndex], PositionFieldMask | SizeFieldMask);
                
                getChildren()[CellIndex]->setPosition(Pnt2s(CumulativeWidth, CumulativeHeight));

                getChildren()[CellIndex]->setSize(Vec2s(
                    _ColumnModel->getColumn(Column)->getWidth(),
                    getRowHeight()));

            endEditCP(getChildren()[CellIndex], PositionFieldMask | SizeFieldMask);

            CumulativeWidth += _ColumnModel->getColumn(Column)->getWidth() + 
                _ColumnModel->getColumnMargin();
        }
        CumulativeHeight += getRowHeight();
    }
    
    //Update My Preferred Size
	Pnt2s TopLeft, BottomRight;
	getBounds(TopLeft, BottomRight);

    Vec2s NewPreferredSize(_ColumnModel->getTotalColumnWidth() + (BottomRight.x() - TopLeft.x() - BorderBottomRight.x() + BorderTopLeft.x()),
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
    if(_Model == NULL || _ColumnModel == NULL)
    {
        return;
    }
    SharedFieldPtr CellValue;

    beginEditCP(TablePtr(this), TableFieldMask);
    getTable().clear();
    for(UInt32 Row(0) ; Row<_Model->getRowCount() ; ++Row)
    {
        for(UInt32 Column(0) ; Column<_Model->getColumnCount() ; ++Column)
        {

            //TODO: Add Focusing
            CellValue = _Model->getValueAt(Row, Column);
            getTable().push_back(
            getCellRenderer(Row, Column)->getTableCellRendererComponent(TablePtr(this), CellValue, isSelected(Row, Column), false, Row, Column));
        }
    }
    endEditCP(TablePtr(this), TableFieldMask);

    //Remove focus Listeners
    for(UInt32 i(0) ; i+1< getChildren().size() ; ++i)
    {
        getChildren().getValue(i)->removeFocusListener(this);
    }

    beginEditCP(TablePtr(this) , ChildrenFieldMask);
        getChildren().clear();

        //Add all of the Table Components
        for(UInt32 i(0); i<getTable().size() ; ++i)
        {
            getChildren().push_back(getTable()[i]);
			getChildren().getValue(i)->addFocusListener(this);
        }

        getChildren().push_back(getHeader());
        
    endEditCP(TablePtr(this) , ChildrenFieldMask);
}

void Table::contentsHeaderRowChanged(const TableModelEvent& e)
{
    if(getAutoCreateColumnsFromModel() && _Model != NULL)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::contentsChanged(const TableModelEvent& e)
{
    if(getAutoCreateColumnsFromModel() && _Model != NULL)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::intervalAdded(const TableModelEvent& e)
{
    updateTableComponents();
}

void Table::intervalRemoved(const TableModelEvent& e)
{
    updateTableComponents();
}

void Table::changeSelection(const UInt32& rowIndex, const UInt32& columnIndex, bool toggle, bool extend)
{
    if(toggle)  //Toggle True
    {
        if(extend)  //Extend True
        {
            if(_ColumnModel->getColumnSelectionAllowed() &&
                getRowSelectionAllowed())
            {
                if(_ColumnModel->getSelectionModel()->isSelectedIndex(columnIndex) !=
                   _RowSelectionModel->isSelectedIndex(rowIndex))
                {
                    _ColumnModel->getSelectionModel()->setSelectionInterval(columnIndex, columnIndex);
                    _RowSelectionModel->setSelectionInterval(rowIndex, rowIndex);
                }
                else
                {
                    _ColumnModel->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                    _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
                }
            }
            else if(_ColumnModel->getColumnSelectionAllowed())
            {
                _ColumnModel->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
            }
            else if(getRowSelectionAllowed())
            {
                _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
            }
        }
        else  //Extend False
        {
            if(_ColumnModel->getSelectionModel()->isSelectedIndex(columnIndex) &&
               _RowSelectionModel->isSelectedIndex(rowIndex))
            {
                if(_ColumnModel->getColumnSelectionAllowed())
                {
                    _ColumnModel->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                }
                if(getRowSelectionAllowed())
                {
                    _RowSelectionModel->removeSelectionInterval(rowIndex, rowIndex);
                }
            }
            else
            {
                if(_ColumnModel->getColumnSelectionAllowed())
                {
                    _ColumnModel->getSelectionModel()->setSelectionInterval(columnIndex, columnIndex);
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
            if(_ColumnModel->getColumnSelectionAllowed())
            {
                _ColumnModel->getSelectionModel()->addSelectionInterval(_ColumnModel->getSelectionModel()->getAnchorSelectionIndex(), columnIndex);
            }
            if(getRowSelectionAllowed())
            {
                _RowSelectionModel->addSelectionInterval(_RowSelectionModel->getAnchorSelectionIndex(), rowIndex);
            }
        }
        else  //Extend False
        {
            //Clear old selection
            if(_ColumnModel->getColumnSelectionAllowed())
            {
                _ColumnModel->getSelectionModel()->clearSelection();
            }
            if(getRowSelectionAllowed())
            {
                _RowSelectionModel->clearSelection();
            }

            //Ensure new cell is selected
            if(_ColumnModel->getColumnSelectionAllowed())
            {
                _ColumnModel->getSelectionModel()->addSelectionInterval(columnIndex, columnIndex);
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
    _ColumnModel->getSelectionModel()->clearSelection();
    _RowSelectionModel->clearSelection();
}

void Table::columnAdded(const TableColumnModelEvent& e)
{
    updateTableComponents();
}

void Table::columnMarginChanged(const ChangeEvent& e)
{
    updateLayout();
}

void Table::columnMoved(const TableColumnModelEvent& e)
{
    updateTableComponents();
}

void Table::columnRemoved(const TableColumnModelEvent& e)
{
    updateTableComponents();
}

void Table::columnSelectionChanged(const ListSelectionEvent& e)
{
    for(UInt32 i(0) ; i<getTable().size() ; ++i)
    {
        updateItem(i);
    }
}

void Table::createDefaultColumnsFromModel(void)
{
    //TODO:Implement
}

bool Table::editCellAt(const UInt32& row, const UInt32& column)
{
    //TODO:Implement
    return true;
}

bool Table::editCellAt(const UInt32& row, const UInt32& column, const Event& e)
{
    //TODO:Implement
    return true;
}

void Table::editingCanceled(const ChangeEvent& e)
{
    //TODO:Implement
    _CellEditor->removeCellEditorListener(this);
    _CellEditor = NULL;
    _EditingComponent = NullFC;
    updateItem(_EditingRow*_Model->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;
}

void Table::editingStopped(const ChangeEvent& e)
{
    //TODO:Implement
    _Model->setValueAt(_CellEditor->getCellEditorValue(), _EditingRow, _EditingColumn);

    
    _CellEditor->removeCellEditorListener(this);
    _CellEditor = NULL;
    _EditingComponent = NullFC;
    updateItem(_EditingRow*_Model->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;

}

TableCellEditorPtr Table::getCellEditor(const UInt32& row, const UInt32& column) const
{
    if(_ColumnModel->getColumn(column)->getCellEditor() != NULL)
    {
        return _ColumnModel->getColumn(column)->getCellEditor();
    }
    else
    {
        return getDefaultEditor(_Model->getColumnType(column));
    }
}

TableCellRendererPtr Table::getCellRenderer(const UInt32& row, const UInt32& column) const
{
    if(_ColumnModel->getColumn(column)->getCellRenderer() != NULL)
    {
        return _ColumnModel->getColumn(column)->getCellRenderer();
    }
    else if(_Model->getColumnType(column) != NULL)
    {
        return getDefaultRenderer(_Model->getColumnType(column));
    }
    else
    {
        return getDefaultRenderer(&(_Model->getValueAt(row,column)->getType()));
    }
}

std::vector<UInt32> Table::getSelectedColumns(void) const
{
    return _ColumnModel->getSelectedColumns();
}

std::vector<UInt32> Table::getSelectedRows(void) const
{
    if(getRowSelectionAllowed())
    {
        std::vector<UInt32> SelectedVector;
        for(UInt32 i(0) ; i<_Model->getRowCount() ; ++i)
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

void Table::removeEditor(void)
{
    //TODO:Implement
}

Int32 Table::rowAtPoint(const Pnt2s& point)
{
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
    
    UInt32 CumulativeHeight(BorderTopLeft.y() +
                            getChildren().back()->getPosition().y() +
                            getChildren().back()->getSize().y());

    for(Int32 i(0) ; i<_Model->getRowCount() ; ++i)
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
    _ColumnModel->getSelectionModel()->setSelectionInterval(0, _Model->getColumnCount());
    _RowSelectionModel->setSelectionInterval(0, _Model->getRowCount());
}

void Table::setCellSelectionEnabled(bool cellSelectionEnabled)
{
    _ColumnModel->setColumnSelectionAllowed(cellSelectionEnabled);
    beginEditCP(TablePtr(this), RowSelectionAllowedFieldMask);
        setRowSelectionAllowed(cellSelectionEnabled);
    endEditCP(TablePtr(this), RowSelectionAllowedFieldMask);
}

void Table::selectionChanged(const ListSelectionEvent& e)
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
    _ColumnModel->setColumnMargin(ColumnMargin);

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

TableCellEditorPtr Table::getDefaultEditor(const FieldType* columnType) const
{
    CellEditorByTypeMap::const_iterator FindItor(_DefaultCellEditorByTypeMap.find(columnType));
    if(FindItor != _DefaultCellEditorByTypeMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        if(columnType != NULL)
        {
            SWARNING << "No Default Table Cell Editor for type: " << columnType->getCName() << "." << std::endl;
        }
        return TableCellEditorPtr(new DefaultTableCellEditor(3));
    }
}

TableCellRendererPtr Table::getDefaultRenderer(const FieldType* columnType) const
{
    CellRendererByTypeMap::const_iterator FindItor(_DefaultCellRendererByTypeMap.find(columnType));
    if(FindItor != _DefaultCellRendererByTypeMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        SWARNING << "No Default Table Cell Renderer for type: " << columnType->getCName() << "." << std::endl;
        return TableCellRendererPtr(new DefaultTableCellRenderer());
    }
}

void Table::setModel(TableModelPtr dataModel)
{
    if(_Model.get() != NULL)
    {
        _Model->removeTableModelListener(this);
    }
    _Model = dataModel;
    if(_Model.get() != NULL)
    {
        if(getAutoCreateColumnsFromModel())
        {
            createColumnsFromModel();
        }
        _Model->addTableModelListener(this);
    }
    updateTableComponents();
}

void Table::setColumnModel(TableColumnModelPtr columnModel)
{
    if(_ColumnModel.get() != NULL)
    {
        _ColumnModel->removeColumnModelListener(this);
    }
    _ColumnModel = columnModel;
    if(getHeader() != NullFC)
    {
        getHeader()->setColumnModel(_ColumnModel);
    }
    if(_ColumnModel.get() != NULL)
    {
        if(_Model != NULL && getAutoCreateColumnsFromModel())
        {
            createColumnsFromModel();
        }
        _ColumnModel->addColumnModelListener(this);
    }
    updateTableComponents();
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
    _ColumnModel->removeColumnModelListener(this);
    //Clear the old columns from the ColumnModel
    while(_ColumnModel->getColumnCount() > 0)
    {
        _ColumnModel->removeColumn(_ColumnModel->getColumn(0));
    }

    //Add the Columns to the Model
    TableColumnPtr NewColumn;
    for(UInt32 i(0) ; i<_Model->getColumnCount() ; ++i)
    {
        NewColumn = TableColumn::create();
        NewColumn->setHeaderValue(_Model->getColumnValue(i));
        _ColumnModel->addColumn(NewColumn);
    }
    _ColumnModel->addColumnModelListener(this);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Table::Table(void) :
    Inherited(),
    _CellEditor(NULL),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NullFC)
{
}

Table::Table(const Table &source) :
    Inherited(source),
    _CellEditor(NULL),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NullFC),
    _ColumnModel(TableColumnModelPtr(new DefaultTableColumnModel())),
    _Model(source._Model),
    _RowSelectionModel(ListSelectionModelPtr(new DefaultListSelectionModel())),
    _DefaultCellEditorByTypeMap(source._DefaultCellEditorByTypeMap),
    _DefaultCellRendererByTypeMap(source._DefaultCellRendererByTypeMap)
{
    if(_Model.get() != NULL)
    {
        _Model->addTableModelListener(this);
    }
    if(_ColumnModel.get() != NULL)
    {
        if(getAutoCreateColumnsFromModel() && _Model != NULL)
        {
            createColumnsFromModel();
        }
        _ColumnModel->setSelectionModel(ListSelectionModelPtr(new DefaultListSelectionModel()));
        _ColumnModel->addColumnModelListener(this);
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
        getHeader()->setColumnModel(_ColumnModel);
    }
    updateTableComponents();
}

Table::~Table(void)
{
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
        getHeader()->setColumnModel(_ColumnModel);
    }

    if(whichField & RowSelectionAllowedFieldMask)
    {
        _RowSelectionModel->clearSelection();
        _ColumnModel->getSelectionModel()->clearSelection();
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

