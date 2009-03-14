/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "Models/OSGTableColumnModel.h"
#include "Models/OSGTableModel.h"

OSG_BEGIN_NAMESPACE

inline
void Table::addColumn(TableColumnPtr aColumn)
{
    getColumnModel()->addColumn(aColumn);
}

inline
bool Table::getColumnSelectionAllowed(void) const
{
    return getColumnModel()->getColumnSelectionAllowed();
}

inline
Int32 Table::getEditingColumn(void) const
{
    return _EditingColumn;
}

inline
Int32 Table::getEditingRow(void) const
{
    return _EditingRow;
}

inline
ComponentPtr Table::getEditorComponent(void) const
{
    return _EditingComponent;
}

inline
UInt32 Table::getRowCount(void) const
{
    return getModel()->getRowCount();
}

inline
UInt32 Table::getColumnCount(void) const
{
    return getModel()->getColumnCount();
}

inline
boost::any Table::getColumnValue(const UInt32& column) const
{
    return getModel()->getColumnValue(column);
}

inline
UInt32 Table::getSelectedColumnCount(void) const
{
    //TODO:Implement
    return 0;
}

inline
UInt32 Table::getSelectedRowCount(void) const
{
    //TODO:Implement
    return 0;
}

inline
ListSelectionModelPtr Table::getSelectionModel(void) const
{
    return _RowSelectionModel;
}

inline
boost::any Table::getValueAt(const UInt32& row, const UInt32& column) const
{
    return getModel()->getValueAt(row, column);
}

inline
bool Table::isCellEditable(const UInt32& row, const UInt32& column) const
{
    return getModel()->isCellEditable(row, column);
}

inline
bool Table::isColumnSelected(const UInt32& column) const
{
    return getColumnModel()->getSelectionModel()->isSelectedIndex(column);
}

inline
bool Table::isEditing(void) const
{
    return _EditingComponent != NullFC;
}

inline
bool Table::isRowSelected(const UInt32& row) const
{
    return _RowSelectionModel->isSelectedIndex(row);
}

inline
void Table::setColumnSelectionAllowed(bool columnSelectionAllowed)
{
    getColumnModel()->setColumnSelectionAllowed(columnSelectionAllowed);
    _RowSelectionModel->clearSelection();
    getColumnModel()->getSelectionModel()->clearSelection();
}

inline
void Table::setEditingColumn(const Int32& aColumn)
{
    _EditingColumn = aColumn;
}

inline
void Table::setEditingRow(const Int32& aRow)
{
    _EditingRow = aRow;
}

inline
const std::type_info& Table::getColumnType(const UInt32& column)
{
    return getModel()->getColumnType(column);
}

inline
void Table::setDefaultEditor(const std::type_info& TheType, TableCellEditorPtr editor)
{
    _DefaultCellEditorByTypeMap[std::string(TheType.name())] = editor;
}

inline
void Table::setDefaultRenderer(const std::type_info& TheType, TableCellRendererPtr renderer)
{
    _DefaultCellRendererByTypeMap[std::string(TheType.name())] = renderer;
}

inline
void Table::setRowSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _RowSelectionModel->setSelectionInterval(index0, index1);
}

inline
void Table::setColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    getColumnModel()->getSelectionModel()->setSelectionInterval(index0, index1);
}

inline
void Table::removeRowSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _RowSelectionModel->removeIndexInterval(index0, index1);
}

inline
bool Table::isCellSelected(const UInt32& row, const UInt32& column) const
{
    return isRowSelected(row) && isColumnSelected(column);
}

inline
void Table::moveColumn(const UInt32& column, const UInt32& targetColumn)
{
    getColumnModel()->moveColumn(column, targetColumn);
}

inline
void Table::removeColumn(TableColumnPtr aColumn)
{
    getColumnModel()->removeColumn(aColumn);
}

inline
void Table::removeColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    getColumnModel()->getSelectionModel()->removeIndexInterval(index0, index1);
}

inline
Int32 Table::getSelectedRow(void) const
{
    return _RowSelectionModel->getMinSelectionIndex();
}

inline
Int32 Table::getSelectedColumn(void) const
{
    return getColumnModel()->getSelectionModel()->getMinSelectionIndex();
}

inline
void Table::addColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    getColumnModel()->getSelectionModel()->addSelectionInterval(index0, index1);
}

inline
void Table::addRowSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _RowSelectionModel->addSelectionInterval(index0, index1);
}

inline
void Table::setValueAt(const boost::any& aValue, const UInt32& row, const UInt32& column)
{
    getModel()->setValueAt(aValue, row, column);
}

inline
Int32 Table::columnAtPoint(const Pnt2f& point)
{
    return getColumnModel()->getColumnIndexAtX(point.x());
}

OSG_END_NAMESPACE

#define OSGTABLE_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

