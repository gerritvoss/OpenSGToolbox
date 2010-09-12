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

#include "OSGTable.h"
#include "OSGTableHeader.h"

#include "OSGTable.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGDefaultTableColumnModel.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"

#include "OSGDefaultTableCellRenderer.h"
#include "OSGDefaultTableCellEditor.h"
#include "OSGTableCellEditor.h"
#include "OSGTableColumnModelEventDetails.h"
#include "OSGTableModelEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTableBase.cpp file.
// To modify it, please change the .fcd file (OSGTable.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Table::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool Table::useBoundsForClipping(void) const
{
    return false;
}

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
            Inherited::getGlobalCellEditor()->stopCellEditing();
        }
    }

    setGlobalCellEditor(getCellEditor(Row, Column));
    _EditingColumn = Column;
    _EditingRow = Row;

    if(Inherited::getGlobalCellEditor()->getType().isDerivedFrom(TableCellEditor::getClassType()))
    {
        _EditingComponent = dynamic_cast<TableCellEditor*>(Inherited::getGlobalCellEditor())->getTableCellEditorComponent(this, getModel()->getValueAt(Row, Column), isSelected(Row, Column), Row, Column);
    }
    else
    {
        _EditingComponent = Inherited::getGlobalCellEditor()->getCellEditor(getModel()->getValueAt(Row, Column), isSelected(Row, Column));
    }


    _EditingCanceledConnection = Inherited::getGlobalCellEditor()->connectEditingCanceled(boost::bind(&Table::handleEditingCanceled, this, _1));
    _EditingStoppedConnection = Inherited::getGlobalCellEditor()->connectEditingStopped(boost::bind(&Table::handleEditingStopped, this, _1));

    updateItem(Row*getModel()->getColumnCount() + Column);
    _EditingComponent->setFocused(false);
    _EditingComponent->takeFocus();
}

Vec2f Table::getContentRequestedSize(void) const
{
    Pnt2f BorderTopLeft, BorderBottomRight;
    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
    Real32 CumulativeHeight(BorderTopLeft.y() +
                            getChildren(getMFChildren()->size()-1)->getPosition().y() +
                            getChildren(getMFChildren()->size()-1)->getSize().y());

    for(UInt32 Row(0) ; Row<getModel()->getRowCount() ; ++Row)
    {
        CumulativeHeight += getRowMargin() + getRowHeight();
    }


    Pnt2f TopLeft, BottomRight;
    getBounds(TopLeft, BottomRight);

    return Vec2f(getColumnModel()->getTotalColumnWidth() + (BottomRight.x() - TopLeft.x() - BorderBottomRight.x() + BorderTopLeft.x()),
                 CumulativeHeight + (BottomRight.y() - TopLeft.y() - BorderBottomRight.y() + BorderTopLeft.y()));
}

void Table::checkCellEdit(EventDetails* const e, const UInt32& Row, const UInt32& Column)
{
    //Check if this cell is editable
    if(getModel()->isCellEditable(Row, Column))
    {
        //Check if this event will start an edit
        TableCellEditorRefPtr Editor(getCellEditor(Row, Column));
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
            if(getChildren(Row*getModel()->getColumnCount() + Column)->getFocused())
            {
                return true;
            }
        }
    }
    return false;
}

void Table::keyTyped(KeyEventDetails* const e)
{
    bool noFocus = true;
    if (e->getKey() == KeyEventDetails::KEY_UP || 
        e->getKey() == KeyEventDetails::KEY_DOWN || 
        e->getKey() == KeyEventDetails::KEY_RIGHT || 
        e->getKey() == KeyEventDetails::KEY_LEFT || 
        e->getKey() == KeyEventDetails::KEY_ENTER)
    {
        for(Int32 i(getMFChildren()->size()-2) ; i>=0 && noFocus; --i)
        {
            if (getChildren(i)->getFocused())
            {
                noFocus = false; // this exits the loop
                Int32 index(0);
                switch(e->getKey())
                {
                    case KeyEventDetails::KEY_UP:
                        index = i-static_cast<Int32>(getModel()->getColumnCount());
                        if(index < 0)
                        {
                            index = i;
                        }
                        break;
                    case KeyEventDetails::KEY_DOWN:
                        index = i+static_cast<Int32>(getModel()->getColumnCount());
                        if(index > getModel()->getColumnCount() * getModel()->getRowCount() - 1)
                        {
                            index = i;
                        }
                        break;
                    case KeyEventDetails::KEY_LEFT:
                        index = i-1;
                        if((index/getModel()->getColumnCount()) != (i/getModel()->getColumnCount()))
                        {
                            index = i;
                        }
                        break;
                    case KeyEventDetails::KEY_RIGHT:
                        index = i+1;
                        if((index/getModel()->getColumnCount()) != (i/getModel()->getColumnCount()))
                        {
                            index = i;
                        }
                        break;
                    case KeyEventDetails::KEY_ENTER:
                        {
                            index = i;
                            UInt32 Row(index/getColumnModel()->getColumnCount()),
                                   Column(index%getColumnModel()->getColumnCount());
                            if (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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
                getChildren(index)->takeFocus();
                UInt32 Row(index/getColumnModel()->getColumnCount()),
                       Column(index%getColumnModel()->getColumnCount());
                if (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
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

void Table::mouseClicked(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            if(i != getMFChildren()->size()-1)
            {
                checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
            getChildren(i)->mouseClicked(e);
            break;
        }
    }
    Component::mouseClicked(e);
}

void Table::mouseReleased(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            if(i != getMFChildren()->size()-1)
            {
                checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
            getChildren(i)->mouseReleased(e);
            break;
        }
    }
    Component::mouseReleased(e);
}

void Table::mouseMoved(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            if(i != getMFChildren()->size()-1)
            {
                checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
            getChildren(i)->mouseMoved(e);
        }
    }
    Component::mouseMoved(e);
}

void Table::mouseDragged(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            if(i != getMFChildren()->size()-1)
            {
                checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
            getChildren(i)->mouseDragged(e);
        }
    }
    Component::mouseDragged(e);
}

void Table::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            if(i != getMFChildren()->size()-1)
            {
                checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
            }
            getChildren(i)->mouseWheelMoved(e);
        }
    }
    Component::mouseWheelMoved(e);
}

void Table::produceMouseExitOnComponent(MouseEventDetails* const e, Component* const Comp)
{
    UInt32 i(0);
    while(i<getMFChildren()->size()-1 && getChildren(i) != Comp)
    {
        ++i;
    }
    if(i < getMFChildren()->size()-1)
    {
        checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
    }
    Inherited::produceMouseExitOnComponent(e,Comp);
}

void Table::produceMouseEnterOnComponent(MouseEventDetails* const e, Component* const Comp)
{
    UInt32 i(0);
    while(i<getMFChildren()->size()-1 && getChildren(i) != Comp)
    {
        ++i;
    }
    if(i < getMFChildren()->size()-1)
    {
        checkCellEdit(e, i/getColumnModel()->getColumnCount(), i%getColumnModel()->getColumnCount());
    }
    Inherited::produceMouseEnterOnComponent(e,Comp);
}

void Table::mousePressed(MouseEventDetails* const e)
{
    bool isContained(false);
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());

        //Table Header
        if(isContained && i==getMFChildren()->size()-1)
        {
            //Give myself temporary focus
            takeFocus(true);
            if(!getChildren(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
            {
                getChildren(i)->takeFocus();
            }
            getChildren(i)->mousePressed(e);
            break;
        }
        else if(isContained)
        {
            UInt32 Row(i/getColumnModel()->getColumnCount()),
                   Column(i%getColumnModel()->getColumnCount());
            //Give myself temporary focus
            takeFocus(true);
            if(!getChildren(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
            {
                getChildren(i)->takeFocus();
                if(getParentWindow() != NULL &&
                   getParentWindow()->getParentDrawingSurface() != NULL &&
                   getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
                {
                    if(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
                    {
                        changeSelection(Row, Column, false, true);
                    }
                    else if(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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
            getChildren(i)->mousePressed(e);
            break;
        }
    }
    if(isContained)
    {
        //Remove my temporary focus
        giveFocus(NULL, false);
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
            getRowSelectionModel()->isSelectedIndex(Row);
    }
    else
    {
        return (getColumnModel()->getColumnSelectionAllowed() &&
                getColumnModel()->getSelectionModel()->isSelectedIndex(Column))
            ||
            (getRowSelectionAllowed() &&
             getRowSelectionModel()->isSelectedIndex(Row));
    }
}

void Table::updateItem(const UInt32& index)
{
    UInt32 Row(index/getColumnModel()->getColumnCount()),
           Column(index%getColumnModel()->getColumnCount());

    //Transfer focus, enabled
    ComponentRefPtr PrevComponent = getChildren(index);
    _ItemFocusGainedConnections[getChildren(index)].disconnect();
    _ItemFocusGainedConnections.erase(_ItemFocusGainedConnections.find(getChildren(index)));
    _ItemFocusLostConnections[getChildren(index)].disconnect();
    _ItemFocusLostConnections.erase(_ItemFocusLostConnections.find(getChildren(index)));

    //Check if this cell is being Edited
    if(isEditing() && Row == _EditingRow && Column == _EditingColumn)
    {
        replaceInChildren(index, _EditingComponent);
    }
    else //Non-Editing Cell
    {
        boost::any CellValue = getModel()->getValueAt(Row, Column);

        ComponentUnrecPtr NewComp(getCellRenderer(Row, Column)->getTableCellRendererComponent(this, CellValue, isSelected(Row, Column), PrevComponent->getFocused(), Row, Column));
        replaceInChildren(index, NewComp);
    }
    if(PrevComponent->getFocused())
    {
        //getChildren(index)->takeFocus();
        getParentWindow()->setFocusedComponent(getChildren(index));
    }
    _ItemFocusGainedConnections[getChildren(index)] = getChildren(index)->connectFocusGained(boost::bind(&Table::handleItemFocusGained, this, _1));
    _ItemFocusLostConnections[getChildren(index)] = getChildren(index)->connectFocusGained(boost::bind(&Table::handleItemFocusLost, this, _1));

    getChildren(index)->setFocused(PrevComponent->getFocused());
    if(getChildren(index)->getPosition() != PrevComponent->getPosition())
    {
        getChildren(index)->setPosition(PrevComponent->getPosition());
    }
    if(getChildren(index)->getSize() != PrevComponent->getSize())
    {
        getChildren(index)->setSize(PrevComponent->getSize());
    }
    getChildren(index)->setParentWindow(PrevComponent->getParentWindow());
    getChildren(index)->updateClipBounds();
}
void Table::handleItemFocusGained(FocusEventDetails* const e)
{
    //Find this component
    Component* Child = dynamic_cast<Component*>(e->getSource());
    UInt32 index(0);
    for( ; index< getMFChildren()->size(); ++index)
    {
        if(Child == getChildren(index))
        {
            updateItem(index);
            return;
        }
    }
}

void Table::handleItemFocusLost(FocusEventDetails* const e)
{
    //Find this component
    Component* Child = dynamic_cast<Component*>(e->getSource());
    UInt32 index(0);
    for( ; index< getMFChildren()->size(); ++index)
    {
        if(Child == getChildren(index))
        {
            updateItem(index);
            return;
        }
    }
}

void Table::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
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
    if(getMFChildren()->size() == 0){ return; }
    Pnt2f BorderTopLeft, BorderBottomRight;
    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);


    //Position and size the Header
    UInt32 HeaderIndex = getMFChildren()->size()-1;
    getChildren(HeaderIndex)->setPosition(BorderTopLeft);
    getChildren(HeaderIndex)->setSize(getChildren(HeaderIndex)->getPreferredSize());


    //Position and size all of the cells
    UInt32 CellIndex(0);
    Real32 CumulativeWidth(0);
    Real32 CumulativeHeight(BorderTopLeft.y() +
                            getChildren(HeaderIndex)->getPosition().y() +
                            getChildren(HeaderIndex)->getSize().y());
    for(UInt32 Row(0) ; Row<getModel()->getRowCount() ; ++Row)
    {
        CumulativeWidth = BorderTopLeft.x();
        CumulativeHeight += getRowMargin();
        for(UInt32 Column(0) ; Column<getModel()->getColumnCount() ; ++Column)
        {
            CellIndex = Row*getModel()->getColumnCount() + Column;

            getChildren(CellIndex)->setPosition(Pnt2f(CumulativeWidth, CumulativeHeight));

            getChildren(CellIndex)->setSize(Vec2f(
                                                    getColumnModel()->getColumn(Column)->getWidth(),
                                                    getRowHeight()));


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
        setPreferredSize(NewPreferredSize);
    }
}

void Table::updateTableComponents(void)
{
    if(getModel() == NULL || getColumnModel() == NULL)
    {
        return;
    }
    boost::any CellValue;

    clearTable();
    for(UInt32 Row(0) ; Row<getModel()->getRowCount() ; ++Row)
    {
        for(UInt32 Column(0) ; Column<getModel()->getColumnCount() ; ++Column)
        {

            //TODO: Add Focusing
            CellValue = getModel()->getValueAt(Row, Column);
            ComponentUnrecPtr NewComp(getCellRenderer(Row, Column)->getTableCellRendererComponent(this, CellValue, isSelected(Row, Column), false, Row, Column));
            pushToTable(NewComp);
        }
    }

    //Remove focus binding
    for(std::map<Component*, boost::signals2::connection>::iterator MapItor(_ItemFocusGainedConnections.begin());
        MapItor != _ItemFocusGainedConnections.end();
        ++MapItor)
    {
        MapItor->second.disconnect();
    }
    for(std::map<Component*, boost::signals2::connection>::iterator MapItor(_ItemFocusLostConnections.begin());
        MapItor != _ItemFocusLostConnections.end();
        ++MapItor)
    {
        MapItor->second.disconnect();
    }

    clearChildren();

    //Add all of the Table Components
    for(UInt32 i(0); i<getMFTable()->size() ; ++i)
    {
        pushToChildren(getTable(i));
        _ItemFocusGainedConnections[getChildren(i)] = getChildren(i)->connectFocusGained(boost::bind(&Table::handleItemFocusGained, this, _1));
        _ItemFocusLostConnections[getChildren(i)] = getChildren(i)->connectFocusLost(boost::bind(&Table::handleItemFocusLost, this, _1));
    }

    pushToChildren(getHeader());

}

void Table::handleContentsHeaderRowChanged(TableModelEventDetails* const e)
{
    if(getAutoCreateColumnsFromModel() && getModel() != NULL)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::handleContentsChanged(TableModelEventDetails* const e)
{
    if(getAutoCreateColumnsFromModel() && getModel() != NULL)
    {
        createColumnsFromModel();
    }
    updateTableComponents();
}

void Table::handleIntervalAdded(TableModelEventDetails* const e)
{
    updateTableComponents();
}

void Table::handleIntervalRemoved(TableModelEventDetails* const e)
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
                   getRowSelectionModel()->isSelectedIndex(rowIndex))
                {
                    getColumnModel()->getSelectionModel()->setSelectionInterval(columnIndex, columnIndex);
                    getRowSelectionModel()->setSelectionInterval(rowIndex, rowIndex);
                }
                else
                {
                    getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                    getRowSelectionModel()->removeSelectionInterval(rowIndex, rowIndex);
                }
            }
            else if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
            }
            else if(getRowSelectionAllowed())
            {
                getRowSelectionModel()->removeSelectionInterval(rowIndex, rowIndex);
            }
        }
        else  //Extend False
        {
            if(getColumnModel()->getSelectionModel()->isSelectedIndex(columnIndex) &&
               getRowSelectionModel()->isSelectedIndex(rowIndex))
            {
                if(getColumnModel()->getColumnSelectionAllowed())
                {
                    getColumnModel()->getSelectionModel()->removeSelectionInterval(columnIndex, columnIndex);
                }
                if(getRowSelectionAllowed())
                {
                    getRowSelectionModel()->removeSelectionInterval(rowIndex, rowIndex);
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
                    getRowSelectionModel()->setSelectionInterval(rowIndex, rowIndex);
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
                getRowSelectionModel()->addSelectionInterval(getRowSelectionModel()->getAnchorSelectionIndex(), rowIndex);
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
                getRowSelectionModel()->clearSelection();
            }

            //Ensure new cell is selected
            if(getColumnModel()->getColumnSelectionAllowed())
            {
                getColumnModel()->getSelectionModel()->addSelectionInterval(columnIndex, columnIndex);
            }
            if(getRowSelectionAllowed())
            {
                getRowSelectionModel()->addSelectionInterval(rowIndex, rowIndex);
            }
        }
    }
}

void Table::clearSelection(void)
{
    getColumnModel()->getSelectionModel()->clearSelection();
    getRowSelectionModel()->clearSelection();
}

void Table::handleColumnAdded(TableColumnModelEventDetails* const e)
{
    updateTableComponents();
}

void Table::handleColumnMarginChanged(ChangeEventDetails* const e)
{
    updateLayout();
}

void Table::handleColumnMoved(TableColumnModelEventDetails* const e)
{
    updateTableComponents();
}

void Table::handleColumnRemoved(TableColumnModelEventDetails* const e)
{
    updateTableComponents();
}

void Table::handleColumnSelectionChanged(ListSelectionEventDetails* const e)
{
    for(UInt32 i(0) ; i<getMFTable()->size() ; ++i)
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

bool Table::editCellAt(const UInt32& row, const UInt32& column, EventDetails* const e)
{
    //TODO:Implement
    checkCellEdit(e, row, column);
    return true;
}

void Table::handleEditingCanceled(ChangeEventDetails* const e)
{
    _EditingCanceledConnection.disconnect();
    _EditingStoppedConnection.disconnect();
    setGlobalCellEditor(NULL);
    _EditingComponent = NULL;
    updateItem(_EditingRow*getModel()->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;
}

void Table::handleEditingStopped(ChangeEventDetails* const e)
{
    getModel()->setValueAt(Inherited::getGlobalCellEditor()->getCellEditorValue(), _EditingRow, _EditingColumn);

    _EditingCanceledConnection.disconnect();
    _EditingStoppedConnection.disconnect();
    setGlobalCellEditor(NULL);
    _EditingComponent = NULL;
    updateItem(_EditingRow*getModel()->getColumnCount() + _EditingColumn);
    _EditingRow = -1;
    _EditingColumn = -1;

}

TableCellEditor* Table::getCellEditor(const UInt32& row, const UInt32& column) const
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
    if(getColumnModel()->getColumn(column) != NULL &&
        getColumnModel()->getColumn(column)->getCellRenderer() != NULL)
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
            if(getRowSelectionModel()->isSelectedIndex(i))
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
                            getMFChildren()->back()->getPosition().y() +
                            getMFChildren()->back()->getSize().y());

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
    getRowSelectionModel()->setSelectionInterval(0, getModel()->getRowCount());
}

void Table::setCellSelectionEnabled(bool cellSelectionEnabled)
{
    getColumnModel()->setColumnSelectionAllowed(cellSelectionEnabled);
    setRowSelectionAllowed(cellSelectionEnabled);
}

void Table::handleRowSelectionChanged(ListSelectionEventDetails* const e)
{
    for(UInt32 i(0) ; i<getMFTable()->size() ; ++i)
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

    setRowMargin(RowMargin);
}

//void Table::setRowHeight(const UInt32& row, const UInt32& rowHeight)
//{
//TODO:Implement
//}

void Table::setShowGrid(bool showGrid)
{
    setShowHorizontalLines(showGrid);
    setShowVerticalLines(showGrid);
}

TableCellEditor* Table::getDefaultEditor(const std::type_info& TheType) const
{
    CellEditorByTypeMap::const_iterator FindItor(_DefaultCellEditorByTypeMap.find(std::string(TheType.name())));
    if(FindItor != _DefaultCellEditorByTypeMap.end())
    {
        return (*FindItor).second;
    }
    else
    {
        SWARNING << "No Default Table Cell Editor for type: " << TheType.name() << "." << std::endl;
        if(_DefaultCellEditor == NULL)
        {
            _DefaultCellEditor = DefaultTableCellEditor::create();
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
            _DefaultCellRenderer = TableCellRendererPtr(new DefaultTableCellRenderer());
        }
        return _DefaultCellRenderer;
    }
}

void Table::createColumnsFromModel(void)
{
    _ColumnMarginChangedConnection.disconnect();
    _ColumnMovedConnection.disconnect();
    _ColumnRemovedConnection.disconnect();
    _ColumnAddedConnection.disconnect();
    _ColumnSelectionChangedConnection.disconnect();

	if(getColumnModel()->getColumnCount() > getModel()->getColumnCount())
	{
		//Clear the old columns from the ColumnModel
		while(getColumnModel()->getColumnCount() > getModel()->getColumnCount())
		{
			getColumnModel()->removeColumn(getColumnModel()->getColumn(getColumnModel()->getColumnCount()-1));
		}
	}
	else if(getColumnModel()->getColumnCount() < getModel()->getColumnCount())
	{
        //Add the Columns to the Model
		TableColumnRefPtr NewColumn;
		while(getColumnModel()->getColumnCount() < getModel()->getColumnCount())
		{
			NewColumn = TableColumn::create();
			getColumnModel()->addColumn(NewColumn);
		}
	}


	//Add the Column's values
    for(UInt32 i(0) ; i<getColumnModel()->getColumnCount() ; ++i)
    {
        getColumnModel()->getColumn(i)->setHeaderValue(getModel()->getColumnValue(i));
    }
    _ColumnMarginChangedConnection = getColumnModel()->connectColumnMarginChanged(boost::bind(&Table::handleColumnMarginChanged, this, _1));
    _ColumnMovedConnection = getColumnModel()->connectColumnMoved(boost::bind(&Table::handleColumnMoved, this, _1));
    _ColumnRemovedConnection = getColumnModel()->connectColumnRemoved(boost::bind(&Table::handleColumnRemoved, this, _1));
    _ColumnAddedConnection = getColumnModel()->connectColumnAdded(boost::bind(&Table::handleColumnAdded, this, _1));
    _ColumnSelectionChangedConnection = getColumnModel()->connectColumnSelectionChanged(boost::bind(&Table::handleColumnSelectionChanged, this, _1));
}

void Table::setHeader(TableHeader * const value)
{
	Inherited::setHeader(value);

    if(getHeader() != NULL)
    {
        getHeader()->setColumnModel(getColumnModel());
    }
}

void Table::setModel(TableModel * const value)
{
    _ContentsHeaderRowChangedConnection.disconnect();
    _ContentsChangedConnection.disconnect();
    _IntervalAddedConnection.disconnect();
    _IntervalRemovedConnection.disconnect();

	Inherited::setModel(value);
    if(getModel() != NULL)
    {
        if(getAutoCreateColumnsFromModel())
        {
            createColumnsFromModel();
        }
        _ContentsHeaderRowChangedConnection = getModel()->connectContentsHeaderRowChanged(boost::bind(&Table::handleContentsChanged, this, _1));
        _ContentsChangedConnection = getModel()->connectContentsChanged(boost::bind(&Table::handleContentsChanged, this, _1));
        _IntervalAddedConnection = getModel()->connectIntervalAdded(boost::bind(&Table::handleIntervalAdded, this, _1));
        _IntervalRemovedConnection = getModel()->connectIntervalRemoved(boost::bind(&Table::handleIntervalRemoved, this, _1));
    }
    updateTableComponents();
}

void Table::setColumnModel(TableColumnModel * const value)
{
    _ColumnMarginChangedConnection.disconnect();
    _ColumnMovedConnection.disconnect();
    _ColumnRemovedConnection.disconnect();
    _ColumnAddedConnection.disconnect();
    _ColumnSelectionChangedConnection.disconnect();
	Inherited::setColumnModel(value);

    if(getHeader() != NULL)
    {
        getHeader()->setColumnModel(getColumnModel());
    }
    if(getColumnModel() != NULL)
    {
        if(getModel() != NULL && getAutoCreateColumnsFromModel())
        {
            createColumnsFromModel();
        }
        _ColumnMarginChangedConnection = getColumnModel()->connectColumnMarginChanged(boost::bind(&Table::handleColumnMarginChanged, this, _1));
        _ColumnMovedConnection = getColumnModel()->connectColumnMoved(boost::bind(&Table::handleColumnMoved, this, _1));
        _ColumnRemovedConnection = getColumnModel()->connectColumnRemoved(boost::bind(&Table::handleColumnRemoved, this, _1));
        _ColumnAddedConnection = getColumnModel()->connectColumnAdded(boost::bind(&Table::handleColumnAdded, this, _1));
        _ColumnSelectionChangedConnection = getColumnModel()->connectColumnSelectionChanged(boost::bind(&Table::handleColumnSelectionChanged, this, _1));
    }
    updateTableComponents();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Table::onCreate(const Table * Id)
{
    Inherited::onCreate(Id);

    if(GlobalSystemState == Startup)
    {
        return;
    }

    if(getModel() != NULL)
    {
        _ContentsHeaderRowChangedConnection = getModel()->connectContentsHeaderRowChanged(boost::bind(&Table::handleContentsChanged, this, _1));
        _ContentsChangedConnection = getModel()->connectContentsChanged(boost::bind(&Table::handleContentsChanged, this, _1));
        _IntervalAddedConnection = getModel()->connectIntervalAdded(boost::bind(&Table::handleIntervalAdded, this, _1));
        _IntervalRemovedConnection = getModel()->connectIntervalRemoved(boost::bind(&Table::handleIntervalRemoved, this, _1));
    }
    if(getColumnModel() != NULL)
    {
        if(getAutoCreateColumnsFromModel() && getModel() != NULL)
        {
            createColumnsFromModel();
        }
        DefaultListSelectionModelUnrecPtr ColumnSelModel = DefaultListSelectionModel::create();
        getColumnModel()->setSelectionModel(ColumnSelModel);

        _ColumnMarginChangedConnection = getColumnModel()->connectColumnMarginChanged(boost::bind(&Table::handleColumnMarginChanged, this, _1));
        _ColumnMovedConnection = getColumnModel()->connectColumnMoved(boost::bind(&Table::handleColumnMoved, this, _1));
        _ColumnRemovedConnection = getColumnModel()->connectColumnRemoved(boost::bind(&Table::handleColumnRemoved, this, _1));
        _ColumnAddedConnection = getColumnModel()->connectColumnAdded(boost::bind(&Table::handleColumnAdded, this, _1));
        _ColumnSelectionChangedConnection = getColumnModel()->connectColumnSelectionChanged(boost::bind(&Table::handleColumnSelectionChanged, this, _1));
    }

    DefaultListSelectionModelUnrecPtr RowSelModel = DefaultListSelectionModel::create();
    setRowSelectionModel(RowSelModel);

    if(Id != NULL &&
       getHeader() != NULL)
    {
        //Ignore Table types
        //Otherwise, if the Header points to this table, there will be an infinite
        //recursion in the deepClone

        //Clone the Header
        FieldContainerUnrecPtr FCCopy(deepClone(getHeader(),
                                                std::vector<const OSG::ReflexiveContainerType *>(),
                                                std::vector<const OSG::ReflexiveContainerType *>(1, &Table::getClassType())));
        setHeader(dynamic_pointer_cast<TableHeader>(FCCopy));
        getHeader()->setColumnModel(getColumnModel());
    }
    updateTableComponents();
}

void Table::onDestroy()
{
    _RowSelectionChangedConnection.disconnect();

    _EditingCanceledConnection.disconnect();
    _EditingStoppedConnection.disconnect();
    
    _ColumnMarginChangedConnection.disconnect();
    _ColumnMovedConnection.disconnect();
    _ColumnRemovedConnection.disconnect();
    _ColumnAddedConnection.disconnect();
    _ColumnSelectionChangedConnection.disconnect();

    _ContentsHeaderRowChangedConnection.disconnect();
    _ContentsChangedConnection.disconnect();
    _IntervalAddedConnection.disconnect();
    _IntervalRemovedConnection.disconnect();

    for(std::map<Component*, boost::signals2::connection>::iterator MapItor(_ItemFocusGainedConnections.begin());
        MapItor != _ItemFocusGainedConnections.end();
        ++MapItor)
    {
        MapItor->second.disconnect();
    }
    for(std::map<Component*, boost::signals2::connection>::iterator MapItor(_ItemFocusLostConnections.begin());
        MapItor != _ItemFocusLostConnections.end();
        ++MapItor)
    {
        MapItor->second.disconnect();
    }
}

/*----------------------- constructors & destructors ----------------------*/

Table::Table(void) :
    Inherited(),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NULL)
{
}

Table::Table(const Table &source) :
    Inherited(source),
    _EditingColumn(-1),
    _EditingRow(-1),
    _EditingComponent(NULL),
    _DefaultCellEditorByTypeMap(source._DefaultCellEditorByTypeMap),
    _DefaultCellRendererByTypeMap(source._DefaultCellRendererByTypeMap)
{
}

Table::~Table(void)
{
}

/*----------------------------- class specific ----------------------------*/


void Table::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & RowSelectionAllowedFieldMask)
    {
        getRowSelectionModel()->clearSelection();
        if(getColumnModel() != NULL &&
           getColumnModel()->getSelectionModel() != NULL)
        {
            //getColumnModel()->getSelectionModel()->clearSelection();
        }
    }
    if(whichField & RowSelectionModelFieldMask)
    {
        _RowSelectionChangedConnection.disconnect();
        if(getRowSelectionModel() != NULL)
        {
            _RowSelectionChangedConnection = getRowSelectionModel()->connectSelectionChanged(boost::bind(&Table::handleRowSelectionChanged, this, _1));
        }
    }
}

void Table::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Table NI" << std::endl;
}

OSG_END_NAMESPACE
