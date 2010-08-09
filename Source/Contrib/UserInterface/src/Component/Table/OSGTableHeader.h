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

#ifndef _OSGTABLEHEADER_H_
#define _OSGTABLEHEADER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableHeaderBase.h"
#include "OSGTableCellRenderer.h"
#include "OSGTableColumnFields.h"
#include "OSGTableColumnModelEventDetailsFields.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGListSelectionEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableHeader class. See \ref
           PageContribUserInterfaceTableHeader for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableHeader : public TableHeaderBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableHeaderBase Inherited;
    typedef TableHeader     Self;

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

    /*! \}                                                                 */
    
    virtual void mouseExited(MouseEventDetails* const e);
    virtual void mouseMoved(MouseEventDetails* const e);
    virtual void mousePressed(MouseEventDetails* const e);
    
    virtual void updateLayout(void);
    
    //Returns a pointer to the column that point lies in, or -1 if it lies out of bounds.
    //The point is assumed to be in TableHeader coordinate space
    TableColumn* columnAtPoint(const Pnt2f& point) const;
    
    //Returns the TableColumnModel that contains all column information of this table header.
    //TableColumnModel* getColumnModel(void) const;
    
    //Returns the default renderer used when no headerRenderer is defined by a TableColumn.
    TableCellRendererPtr getDefaultRenderer(void) const;
    
    //Returns the the dragged column, if and only if, a drag is in process, otherwise returns null.
    TableColumn* getDraggedColumn(void) const;
    
    //Returns the column's horizontal distance from its original position, if and only if, a drag is in process.
    Real32 getDraggedDistance(void) const;
    
    //Returns the rectangle containing the header tile at column.
    void getHeaderBounds(const UInt32 ColumnIndex, Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    
    //Returns the resizing column.
    Int32 getResizingColumn(void) const;
    
    //Sets the column model for this table to newModel and registers for listener notifications from the new column model.
    //void setColumnModel(TableColumnModel* const columnModel);
    
    //Sets the default renderer to be used when no headerRenderer is defined by a TableColumn.
    void setDefaultRenderer(TableCellRendererPtr defaultRenderer);
    
    //Sets the header's draggedColumn to aColumn.
    void setDraggedColumn(TableColumn* const aColumn);
    
    //Sets the header's draggedDistance to distance.
    void setDraggedDistance(const Real32& distance);
    
    //Sets the header's resizingColumn to aColumn.
    void setResizingColumn(Int32 aColumn);
          
    virtual void detachFromEventProducer(void);
	
	void setColumnModel    (TableColumnModel * const value);

    Table* getTable(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableHeaderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableHeader(void);
    TableHeader(const TableHeader &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableHeader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const TableHeader *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    //The Default Table Header Renderer
    TableCellRendererPtr _DefaultTableHeaderRenderer;
    
    //The index of the column being dragged.
    TableColumn* _DraggedColumn;
    
    //The distance from its original position the column has been dragged.
    Real32 _DraggedDistance;
    
    //The index of the column being resized.
    Int32 _ResizingColumn;

    void handleColumnAdded(TableColumnModelEventDetails* const e);
    void handleColumnMarginChanged(ChangeEventDetails* const e);
    void handleColumnMoved(TableColumnModelEventDetails* const e);
    void handleColumnRemoved(TableColumnModelEventDetails* const e);
    void handleColumnSelectionChanged(ListSelectionEventDetails* const e);
    boost::signals2::connection _ColumnAddedConnection,
                                _ColumnMarginChangedConnection,
                                _ColumnMovedConnection,
                                _ColumnRemovedConnection,
                                _ColumnSelectionChangedConnection;

    void handleColBorderMouseDragged(MouseEventDetails* const e);
    void mouseColBorderMouseReleased(MouseEventDetails* const e);
    boost::signals2::connection _ColBorderMouseDraggedConnection,
                                _ColBorderMouseReleasedConnection;

        
    void updateColumnHeadersComponents(void);

	void checkMouseMargins(MouseEventDetails* const e);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableHeaderBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableHeader &source);
};

typedef TableHeader *TableHeaderP;

OSG_END_NAMESPACE

#include "OSGTable.h"
#include "OSGTableColumnModel.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTableHeaderBase.inl"
#include "OSGTableHeader.inl"

#endif /* _OSGTABLEHEADER_H_ */
