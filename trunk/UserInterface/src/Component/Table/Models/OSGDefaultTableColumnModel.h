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

#ifndef _OSGDEFAULTTABLECOLUMNMODEL_H_
#define _OSGDEFAULTTABLECOLUMNMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultTableColumnModelBase.h"
#include "Component/List/OSGListSelectionListener.h"
#include <OpenSG/Input/OSGFieldChangeListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTableColumnModel class. See \ref 
           PageUserInterfaceDefaultTableColumnModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultTableColumnModel : public DefaultTableColumnModelBase
{
  private:

    typedef DefaultTableColumnModelBase Inherited;

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

    //Appends aColumn to the end of the tableColumns array.
    virtual void addColumn(const TableColumnPtr aColumn);

    //Returns the TableColumn object for the column at columnIndex.
    virtual TableColumnPtr getColumn(const UInt32& columnIndex) const;

    //Returns the number of columns in the model.
    virtual UInt32 getColumnCount(void) const;

    //Returns the index of the column that lies on the horizontal point, xPosition; or -1 if it lies outside the any of the column's bounds.
    virtual Int32 getColumnIndexAtX(UInt32 xPosition) const;

    //Returns the width between the cells in each column.
    virtual UInt32 getColumnMargin(void) const;

    //Returns an Enumeration of all the columns in the model.
    virtual std::vector<TableColumnPtr> getColumns(void) const;

    //Returns true if columns may be selected.
    virtual bool getColumnSelectionAllowed(void) const;

    //Returns the number of selected columns.
    virtual UInt32 getSelectedColumnCount(void) const;

    //Returns an array of indicies of all selected columns.
    virtual std::vector<UInt32> getSelectedColumns(void) const;

    //Returns the current selection model.
    virtual ListSelectionModelPtr getSelectionModel(void) const;

    //Returns the total width of all the columns.
    virtual UInt32 getTotalColumnWidth(void) const;

    //Moves the column and its header at columnIndex to newIndex.
    virtual void moveColumn(const UInt32& columnIndex, const UInt32& newIndex);

    //Deletes the TableColumn column from the tableColumns array.
    virtual void removeColumn(TableColumnPtr column);

    //Sets the TableColumn's column margin to newMargin.
    virtual void setColumnMargin(const UInt32& newMargin);

    //Sets whether the columns in this model may be selected.
    virtual void setColumnSelectionAllowed(const bool& flag);

    //Sets the selection model.
    virtual void setSelectionModel(ListSelectionModelPtr newModel);
    
    
    /*=========================  PROTECTED  ===============================*/
  protected:
    typedef std::vector<TableColumnPtr> TableColumnVector;

    // Variables should all be in DefaultTableColumnModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTableColumnModel(void);
    DefaultTableColumnModel(const DefaultTableColumnModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTableColumnModel(void); 

    /*! \}                                                                 */
    
    void recalcWidthCache(void);
    static ListSelectionModelPtr createSelectionModel(void);

    UInt32 _ColumnMargin;
    bool _ColumnSelectionAllowed;;
    ListSelectionModelPtr _SelectionModel;
    TableColumnVector _Columns;
    UInt32 _TotalColumnWidth;
    
    
	class TableSelectionListener : public ListSelectionListener
	{
	public :
		TableSelectionListener(DefaultTableColumnModelPtr TheDefaultTableColumnModel);
		
        //A ListSelectionListener that forwards ListSelectionEvents when there is a column selection change
        virtual void selectionChanged(const ListSelectionEventPtr e);
	protected :
		DefaultTableColumnModelPtr _DefaultTableColumnModel;
	};

	friend class TableSelectionListener;

	TableSelectionListener _TableSelectionListener;
    
	class TableFieldChangeListener : public FieldChangeListener
	{
	public :
		TableFieldChangeListener(DefaultTableColumnModelPtr TheDefaultTableColumnModel);
		
        virtual void fieldChanged(const FieldChangeEventPtr e);
	protected :
		DefaultTableColumnModelPtr _DefaultTableColumnModel;
	};

	friend class TableFieldChangeListener;

	TableFieldChangeListener _TableFieldChangeListener;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultTableColumnModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultTableColumnModel &source);
};

typedef DefaultTableColumnModel *DefaultTableColumnModelP;

OSG_END_NAMESPACE

#include "OSGDefaultTableColumnModelBase.inl"
#include "OSGDefaultTableColumnModel.inl"

#define OSGDEFAULTTABLECOLUMNMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTTABLECOLUMNMODEL_H_ */
