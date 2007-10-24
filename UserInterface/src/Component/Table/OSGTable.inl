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

OSG_BEGIN_NAMESPACE

inline
void Table::addColumn(TableColumnPtr aColumn)
{
    _ColumnModel->addColumn(aColumn);
}

inline
TableCellEditorPtr Table::getCellEditor(void) const
{
    return _CellEditor;
}

inline
TableColumnModelPtr Table::getColumnModel(void) const
{
    return _ColumnModel;
}

inline
bool Table::getColumnSelectionAllowed(void) const
{
    return _ColumnModel->getColumnSelectionAllowed();
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
TableModelPtr Table::getModel(void) const
{
    return _Model;
}

inline
UInt32 Table::getRowCount(void) const
{
    return _Model->getRowCount();
}

inline
UInt32 Table::getColumnCount(void) const
{
    return _Model->getColumnCount();
}

inline
Field* Table::getColumnValue(const UInt32& column) const
{
    return _Model->getColumnValue(column);
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
Field* Table::getValueAt(const UInt32& row, const UInt32& column) const
{
    return _Model->getValueAt(row, column);
}

inline
bool Table::isCellEditable(const UInt32& row, const UInt32& column) const
{
    return _Model->isCellEditable(row, column);
}

inline
bool Table::isColumnSelected(const UInt32& column) const
{
    return _ColumnModel->getSelectionModel()->isSelectedIndex(column);
}

inline
bool Table::isEditing(void) const
{
    return _EditingComponent == NullFC;
}

inline
bool Table::isRowSelected(const UInt32& row) const
{
    return _RowSelectionModel->isSelectedIndex(row);
}

inline
void Table::setCellEditor(TableCellEditorPtr anEditor)
{
    _CellEditor = anEditor;
}

inline
void Table::setColumnSelectionAllowed(bool columnSelectionAllowed)
{
    _ColumnModel->setColumnSelectionAllowed(columnSelectionAllowed);
    _RowSelectionModel->clearSelection();
    _ColumnModel->getSelectionModel()->clearSelection();
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
const FieldType* Table::getColumnType(const UInt32& column)
{
    return _Model->getColumnType(column);
}

inline
void Table::setDefaultEditor(const FieldType* columnType, TableCellEditorPtr editor)
{
    _DefaultCellEditorByTypeMap[columnType] = editor;
}

inline
void Table::setDefaultRenderer(const FieldType* columnType, TableCellRendererPtr renderer)
{
    _DefaultCellRendererByTypeMap[columnType] = renderer;
}

inline
void Table::setRowSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _RowSelectionModel->setSelectionInterval(index0, index1);
}

inline
void Table::setColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _ColumnModel->getSelectionModel()->setSelectionInterval(index0, index1);
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
    _ColumnModel->moveColumn(column, targetColumn);
}

inline
void Table::removeColumn(TableColumnPtr aColumn)
{
    _ColumnModel->removeColumn(aColumn);
}

inline
void Table::removeColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _ColumnModel->getSelectionModel()->removeIndexInterval(index0, index1);
}

inline
Int32 Table::getSelectedRow(void) const
{
    return _RowSelectionModel->getMinSelectionIndex();
}

inline
Int32 Table::getSelectedColumn(void) const
{
    return _ColumnModel->getSelectionModel()->getMinSelectionIndex();
}

inline
void Table::addColumnSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _ColumnModel->getSelectionModel()->addSelectionInterval(index0, index1);
}

inline
void Table::addRowSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    _RowSelectionModel->addSelectionInterval(index0, index1);
}

inline
void Table::setValueAt(Field* aValue, const UInt32& row, const UInt32& column)
{
    _Model->setValueAt(aValue, row, column);
}

inline
Int32 Table::columnAtPoint(const Pnt2s& point)
{
    return _ColumnModel->getColumnIndexAtX(point.x());
}

inline
bool Table::FieldTypePtrComparitor::operator()(const FieldType* s1, const FieldType* s2) const
{
    return s1->getId() < s2->getId();
}

OSG_END_NAMESPACE

#define OSGTABLE_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

