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

#ifndef _OSGTABLEHEADER_H_
#define _OSGTABLEHEADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTableColumnModelListener.h"

#include "OSGTableHeaderBase.h"
#include "OSGTableCellRenderer.h"
#include "OSGTableColumn.h"

#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief TableHeader class. See \ref 
           PageUserInterfaceTableHeader for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TableHeader : public TableHeaderBase
{
  private:

    typedef TableHeaderBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    
    virtual void mouseExited(const MouseEvent& e);
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    
    virtual void updateLayout(void);
    
    //Returns a pointer to the column that point lies in, or -1 if it lies out of bounds.
    //The point is assumed to be in TableHeader coordinate space
    TableColumnPtr columnAtPoint(const Pnt2f& point) const;
    
    //Returns the TableColumnModel that contains all column information of this table header.
    //TableColumnModelPtr getColumnModel(void) const;
    
    //Returns the default renderer used when no headerRenderer is defined by a TableColumn.
    TableCellRendererPtr getDefaultRenderer(void) const;
    
    //Returns the the dragged column, if and only if, a drag is in process, otherwise returns null.
    TableColumnPtr getDraggedColumn(void) const;
    
    //Returns the column's horizontal distance from its original position, if and only if, a drag is in process.
    Real32 getDraggedDistance(void) const;
    
    //Returns the rectangle containing the header tile at column.
    void getHeaderBounds(const UInt32 ColumnIndex, Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    
    //Returns the resizing column.
    Int32 getResizingColumn(void) const;
    
    //Sets the column model for this table to newModel and registers for listener notifications from the new column model.
    //void setColumnModel(TableColumnModelPtr columnModel);
    
    //Sets the default renderer to be used when no headerRenderer is defined by a TableColumn.
    void setDefaultRenderer(TableCellRendererPtr defaultRenderer);
    
    //Sets the header's draggedColumn to aColumn.
    void setDraggedColumn(TableColumnPtr aColumn);
    
    //Sets the header's draggedDistance to distance.
    void setDraggedDistance(const Real32& distance);
    
    //Sets the header's resizingColumn to aColumn.
    void setResizingColumn(Int32 aColumn);
          
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

    //The Default Table Header Renderer
    TableCellRendererPtr _DefaultTableHeaderRenderer;
    
    //The index of the column being dragged.
    TableColumnPtr _DraggedColumn;
    
    //The distance from its original position the column has been dragged.
    Real32 _DraggedDistance;
    
    //The index of the column being resized.
    Int32 _ResizingColumn;

    //TableColumnModelListener
	class ColumnModelListener : public TableColumnModelListener
	{
	public :
		ColumnModelListener(TableHeader* TheTableHeader);
		
        virtual void columnAdded(const TableColumnModelEvent& e);
    
        virtual void columnMarginChanged(const ChangeEvent& e);
    
        virtual void columnMoved(const TableColumnModelEvent& e);
    
        virtual void columnRemoved(const TableColumnModelEvent& e);
    
        virtual void columnSelectionChanged(const ListSelectionEvent& e);
	protected :
		TableHeader* _TableHeader;
	};

	friend class ColumnModelListener;

	ColumnModelListener _ColumnModelListener;
	
	class MarginDraggedListener : public MouseMotionListener, public MouseListener
	{
	public :
		MarginDraggedListener(TableHeader* ptr);
		virtual void mouseMoved(const MouseEvent& e);
		virtual void mouseDragged(const MouseEvent& e);
		
		virtual void mouseClicked(const MouseEvent& e);
		virtual void mouseEntered(const MouseEvent& e);
		virtual void mouseExited(const MouseEvent& e);
		virtual void mousePressed(const MouseEvent& e);
		virtual void mouseReleased(const MouseEvent& e);
	protected :
		TableHeader* _TableHeader;
	};

	friend class _MarginDraggedListener;

	MarginDraggedListener _MarginDraggedListener;

	void updateColumnHeadersComponents(void);

	void checkMouseMargins(const MouseEvent& e);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TableHeaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TableHeader &source);
};

typedef TableHeader *TableHeaderP;

OSG_END_NAMESPACE

#include "OSGTableHeaderBase.inl"
#include "OSGTableHeader.inl"

#define OSGTABLEHEADER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTABLEHEADER_H_ */
