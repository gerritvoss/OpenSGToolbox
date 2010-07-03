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
#include "OSGTableHeaderBase.h"
#include "OSGTableCellRenderer.h"
#include "OSGTableColumn.h"
#include "OSGTableColumnModelListener.h"
#include "OSGUIDrawObjectCanvas.h"

#include "OSGMouseListener.h"
#include "OSGMouseMotionListener.h"

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
    
    virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mouseMoved(const MouseEventUnrecPtr e);
    virtual void mousePressed(const MouseEventUnrecPtr e);
    
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

    //TableColumnModelListener
    class ColumnModelListener : public TableColumnModelListener
    {
      public :
        ColumnModelListener(TableHeader* TheTableHeader);

        virtual void columnAdded(const TableColumnModelEventUnrecPtr e);

        virtual void columnMarginChanged(const ChangeEventUnrecPtr e);

        virtual void columnMoved(const TableColumnModelEventUnrecPtr e);

        virtual void columnRemoved(const TableColumnModelEventUnrecPtr e);

        virtual void columnSelectionChanged(const ListSelectionEventUnrecPtr e);
      protected :
        TableHeader* _TableHeader;
    };

    friend class ColumnModelListener;

    ColumnModelListener _ColumnModelListener;

    class MarginDraggedListener : public MouseMotionListener, public MouseListener
    {
      public :
        MarginDraggedListener(TableHeader* ptr);
        virtual void mouseMoved(const MouseEventUnrecPtr e);
        virtual void mouseDragged(const MouseEventUnrecPtr e);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        void disconnect(void);
      protected :
        TableHeader* _TableHeader;
    };

	friend class _MarginDraggedListener;

	MarginDraggedListener _MarginDraggedListener;

	void updateColumnHeadersComponents(void);

	void checkMouseMargins(const MouseEventUnrecPtr e);
    
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
#include "OSGTableHeaderBase.inl"
#include "OSGTableHeader.inl"

#endif /* _OSGTABLEHEADER_H_ */
