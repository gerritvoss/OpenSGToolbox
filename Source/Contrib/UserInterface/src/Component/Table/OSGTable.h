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

#ifndef _OSGTABLE_H_
#define _OSGTABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableBase.h"
#include "OSGTableCellEditorFields.h"
#include "OSGTableCellRenderer.h"
#include "OSGTableColumnFields.h"
#include "OSGListSelectionEventDetailsFields.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGTableColumnModelEventDetailsFields.h"
#include "OSGTableModelEventDetailsFields.h"
#include <boost/any.hpp>
#include <typeinfo>

OSG_BEGIN_NAMESPACE

/*! \brief Table class. See \ref
           PageContribUserInterfaceTable for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Table : public TableBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ResizeModes
    {
        AUTO_RESIZE_ALL_COLUMNS        = 0,
        AUTO_RESIZE_LAST_COLUMN        = 1,
        AUTO_RESIZE_NEXT_COLUMN        = 2,
        AUTO_RESIZE_OFF                = 3,
        AUTO_RESIZE_SUBSEQUENT_COLUMNS = 4
    };

    typedef TableBase Inherited;
    typedef Table     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */	//Focus Events

    //Mouse Events
    virtual void mouseClicked(MouseEventDetails* const e);
    virtual void mousePressed(MouseEventDetails* const e);
    virtual void mouseReleased(MouseEventDetails* const e);

	//Mouse Motion Events
    virtual void mouseMoved(MouseEventDetails* const e);
    virtual void mouseDragged(MouseEventDetails* const e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);
    
	virtual void keyTyped(KeyEventDetails* const e);

    virtual void updateLayout(void);

	virtual Vec2f getContentRequestedSize(void) const;

    //Appends aColumn to the end of the array of columns held by this JTable's column model.
    void addColumn(TableColumn* const aColumn);

    //Adds the columns from index0 to index1, inclusive, to the current selection.
    void addColumnSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Adds the rows from index0 to index1, inclusive, to the current selection.
    void addRowSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Updates the selection models of the table, depending on the state of the two flags: toggle and extend.
    void changeSelection(const UInt32& rowIndex, const UInt32& columnIndex, bool toggle, bool extend);

    //Deselects all selected columns and rows.
    void clearSelection(void);

    //Returns the index of the column that point lies in, or -1 if the result is not in the range [0,  getColumnCount(void)-1].
    Int32 columnAtPoint(const Pnt2f& point);

    //Returns the default table model object, which is a DefaultTableModel.
    //protected  TableModel* createDefaultDataModel(void);

    //Returns the default selection model object, which is a DefaultListSelectionModel.
    //protected  ListSelectionModel createDefaultSelectionModel(void);

    //Returns the default table header object, which is a JTableHeader.
    //protected  JTableHeader createDefaultTableHeader(void);

    //Programmatically starts editing the cell at row and column, if the cell is editable.
    bool editCellAt(const UInt32& row, const UInt32& column);

    //Programmatically starts editing the cell at row and column, if the cell is editable.
    bool editCellAt(const UInt32& row, const UInt32& column, EventDetails* const e);


    //Returns an appropriate editor for the cell specified by row and column.
    TableCellEditor* getCellEditor(const UInt32& row, const UInt32& column) const;

    //Returns a rectangle for the cell that lies at the intersection of row and column.
    //Rectangle getCellRect(int row, int column, bool includeSpacing);

    //Returns an appropriate renderer for the cell specified by this row and column.
    TableCellRendererPtr getCellRenderer(const UInt32& row, const UInt32& column) const;

    //Returns the type of the column appearing in the view at column position column.
    const std::type_info& getColumnType(const UInt32& column);

    //Returns the number of columns in the column model.
    UInt32 getColumnCount(void) const;

    //Returns the TableColumnModel that contains all column information of this table.
    //TableColumnModel* getColumnModel(void) const;

    //Returns the name of the column appearing in the view at column position column.
    boost::any getColumnValue(const UInt32& column) const;

    //Returns true if columns can be selected.
    bool getColumnSelectionAllowed(void) const;

    //Returns the editor to be used when no editor has been set in a TableColumn.
    TableCellEditor* getDefaultEditor(const std::type_info& TheType) const;

    //Returns the cell renderer to be used when no renderer has been set in a TableColumn.
    TableCellRendererPtr getDefaultRenderer(const std::type_info& TheType) const;

    //Returns the index of the column that contains the cell currently being edited.
    Int32 getEditingColumn(void) const;

    //Returns the index of the row that contains the cell currently being edited.
    Int32 getEditingRow(void) const;

    //Returns the component that is handling the editing session.
    Component* getEditorComponent(void) const;

    //Returns the TableModel that provides the data displayed by this JTable.
    //TableModel* getModel(void) const;

    //Returns the number of rows in this table's model.
    UInt32 getRowCount(void) const;

    //Returns visibleRect.height or visibleRect.width, depending on this table's orientation.
    //Int32 getScrollableBlockIncrement(Rectangle visibleRect, UInt32 orientation, Int32 direction) const;

    //Returns the scroll increment (in pixels) that completely exposes one new row or column (depending on the orientation).
    //Int32 getScrollableUnitIncrement(Rectangle visibleRect, const UInt32& orientation, const UInt32& direction) const;

    //Returns the index of the first selected column, -1 if no column is selected.
    Int32 getSelectedColumn(void) const;

    //Returns the number of selected columns.
    UInt32 getSelectedColumnCount(void) const;

    //Returns the indices of all selected columns.
    std::vector<UInt32> getSelectedColumns(void) const;

    //Returns the index of the first selected row, -1 if no row is selected.
    Int32 getSelectedRow(void) const;

    //Returns the number of selected rows.
    UInt32 getSelectedRowCount(void) const;

    //Returns the indices of all selected rows.
    std::vector<UInt32> getSelectedRows(void) const;

    //Returns the cell value at row and column.
    boost::any getValueAt(const UInt32& row, const UInt32& column) const;

    //Returns true if the cell at row and column is editable.
    bool isCellEditable(const UInt32& row, const UInt32& column) const;

    //Returns true if the cell at the specified position is selected.
    bool isCellSelected(const UInt32& row, const UInt32& column) const;

    //Returns true if the column at the specified index is selected.
    bool isColumnSelected(const UInt32& column) const;

    //Returns true if a cell is being edited.
    bool isEditing(void) const;

    
    bool isSelected(const UInt32& Row, const UInt32& Column) const;

    //Returns true if the row at the specified index is selected.
    bool isRowSelected(const UInt32& row) const;

    //Moves the column column to the position currently occupied by the column targetColumn in the view.
    void moveColumn(const UInt32& column, const UInt32& targetColumn);

    //Removes aColumn from this JTable's array of columns.
    void removeColumn(TableColumn* const aColumn);

    //Deselects the columns from index0 to index1, inclusive.
    void removeColumnSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Deselects the rows from index0 to index1, inclusive.
    void removeRowSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Returns the index of the row that point lies in, or -1 if the result is not in the range [0, getRowCount(void)-1].
    Int32 rowAtPoint(const Pnt2f& point);

    //Selects all rows, columns, and cells in the table.
    void selectAll(void);

    //Sets whether this table allows both a column selection and a row selection to exist simultaneously.
    void setCellSelectionEnabled(bool cellSelectionEnabled);

    //Sets the column model for this table to newModel and registers for listener notifications from the new column model.
    //void setColumnModel(TableColumnModel* const columnModel);

    //Sets whether the columns in this model can be selected.
    void setColumnSelectionAllowed(bool columnSelectionAllowed);

    //Selects the columns from index0 to index1, inclusive.
    void setColumnSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Sets a default cell editor to be used if no editor has been set in a TableColumn.
    void setDefaultEditor(const std::type_info& TheType, TableCellEditor* const editor);

    //Sets a default cell renderer to be used if no renderer has been set in a TableColumn.
    void setDefaultRenderer(const std::type_info& TheType, TableCellRendererPtr renderer);

    //Sets the dragEnabled property, which must be true to enable automatic drag handling (the first part of drag and drop) on this component.
    void setDragEnabled(bool b);

    //Sets the editingColumn variable.
    void setEditingColumn(const Int32& aColumn);

    //Sets the editingRow variable.
    void setEditingRow(const Int32& aRow);

    //Sets the rowMargin and the columnMargin -- the height and width of the space between cells -- to intercellSpacing.
    void setIntercellSpacing(const UInt32& RowMargin, const UInt32& ColumnMargin);


    //Sets the data model for this table to newModel and registers with it for listener notifications from the new data model.
    //void setModel(TableModel* const dataModel);

    //Sets the height for row to rowHeight, revalidates, and repaints.
    //void setRowHeight(const UInt32& row, const UInt32& rowHeight);

    //Selects the rows from index0 to index1, inclusive.
    void setRowSelectionInterval(const UInt32& index0, const UInt32& index1);

    //Sets whether the table draws grid lines around cells.
    void setShowGrid(bool showGrid);

    //Sets the value for the cell in the table model at row and column.
    void setValueAt(const boost::any& aValue, const UInt32& row, const UInt32& column);
	

    void setHeader         (TableHeader * const value);
    void setModel          (TableModel * const value);
    void setColumnModel    (TableColumnModel * const value);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Table(void);
    Table(const Table &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Table(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Table *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    //Invoked when the an event from the Row ListSelectionModel occurs
    void handleRowSelectionChanged(ListSelectionEventDetails* const e);
    boost::signals2::connection _RowSelectionChangedConnection;

    //Invoked when editing is canceled.
    void handleEditingCanceled(ChangeEventDetails* const e);
    //Invoked when editing is finished.
    void handleEditingStopped(ChangeEventDetails* const e);
    boost::signals2::connection _EditingCanceledConnection,
                                _EditingStoppedConnection;

    //Invoked when a column is moved due to a margin change.
    void handleColumnMarginChanged(ChangeEventDetails* const e);
    //Invoked when a column is repositioned.
    void handleColumnMoved(TableColumnModelEventDetails* const e);
    //Invoked when a column is removed from the table column model.
    void handleColumnRemoved(TableColumnModelEventDetails* const e);
    //Invoked when a column is added to the table column model.
    void handleColumnAdded(TableColumnModelEventDetails* const e);
    //Invoked when the selection model of the TableColumnModel is changed.
    void handleColumnSelectionChanged(ListSelectionEventDetails* const e);
    boost::signals2::connection _ColumnMarginChangedConnection,
                                _ColumnMovedConnection,
                                _ColumnRemovedConnection,
                                _ColumnAddedConnection,
                                _ColumnSelectionChangedConnection;
	
    void handleItemFocusGained(FocusEventDetails* const e);
	void handleItemFocusLost(FocusEventDetails* const e);
    std::map<Component*, boost::signals2::connection> _ItemFocusGainedConnections,
                                                      _ItemFocusLostConnections;
    
	//Sent when the contents of the table header row has changed
	void handleContentsHeaderRowChanged(TableModelEventDetails* const e);
	//Sent when the contents of the table has changed in a way that's too complex to characterize with the previous methods.
	void handleContentsChanged(TableModelEventDetails* const e);
	//Sent after the an interval was added to the table model
	void handleIntervalAdded(TableModelEventDetails* const e);
	//Sent after the an interval was removed to the table model
	void handleIntervalRemoved(TableModelEventDetails* const e);
    boost::signals2::connection _ContentsHeaderRowChangedConnection,
                                _ContentsChangedConnection,
                                _IntervalAddedConnection,
                                _IntervalRemovedConnection;



    virtual bool useBoundsForClipping(void) const;

    Int32 _EditingColumn;

    Int32 _EditingRow;

    ComponentRefPtr _EditingComponent;

    typedef std::map<std::string, TableCellEditorRefPtr> CellEditorByTypeMap;
    typedef CellEditorByTypeMap::iterator CellEditorByTypeMapItor;

    typedef std::map<std::string, TableCellRendererPtr> CellRendererByTypeMap;
    typedef CellRendererByTypeMap::iterator CellRendererByTypeMapItor;

    CellEditorByTypeMap _DefaultCellEditorByTypeMap;

    CellRendererByTypeMap _DefaultCellRendererByTypeMap;

    mutable TableCellEditorRefPtr _DefaultCellEditor;
    mutable TableCellRendererPtr _DefaultCellRenderer;
    
    
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
	void updateTableComponents(void);
	void createColumnsFromModel(void);
    void updateItem(const UInt32& index);
    void checkCellEdit(EventDetails* const e, const UInt32& Row, const UInt32& Column);
    void startEditing(const UInt32& Row, const UInt32& Column);
    bool getFocusedCell(UInt32& Row, UInt32& Column) const;
    
	virtual void produceMouseExitOnComponent(MouseEventDetails* const e, Component* const Comp);
	virtual void produceMouseEnterOnComponent(MouseEventDetails* const e, Component* const Comp);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Table &source);
};

typedef Table *TableP;

OSG_END_NAMESPACE

#include "OSGTableColumnModel.h"
#include "OSGTableModel.h"
#include "OSGTableHeader.h"
#include "OSGTableBase.inl"
#include "OSGTable.inl"

#endif /* _OSGTABLE_H_ */
