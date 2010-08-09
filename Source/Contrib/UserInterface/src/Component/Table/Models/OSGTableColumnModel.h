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

#ifndef _OSGTABLECOLUMNMODEL_H_
#define _OSGTABLECOLUMNMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableColumnModelBase.h"
#include "OSGField.h"
#include "OSGTableColumn.h"
#include "OSGListSelectionModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableColumnModel class. See \ref
           PageContribUserInterfaceTableColumnModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableColumnModel : public TableColumnModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableColumnModelBase Inherited;
    typedef TableColumnModel     Self;

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

    //Appends aColumn to the end of the tableColumns array.
    virtual void addColumn(TableColumn* const aColumn) = 0;

    //Returns the TableColumn object for the column at columnIndex.
    virtual TableColumn* getColumn(const UInt32& columnIndex) const = 0;

    //Returns the number of columns in the model.
    virtual UInt32 getColumnCount(void) const = 0;

    //Returns the index of the column that lies on the horizontal point, xPosition; or -1 if it lies outside the any of the column's bounds.
    virtual Int32 getColumnIndexAtX(UInt32 xPosition) const = 0;

    //Returns the width between the cells in each column.
    virtual UInt32 getColumnMargin(void) const = 0;

    //Returns an Enumeration of all the columns in the model.
    //virtual std::vector<TableColumnUnrecPtr> getColumns(void) const = 0;

    //Returns true if columns may be selected.
    virtual bool getColumnSelectionAllowed(void) const = 0;

    //Returns the number of selected columns.
    virtual UInt32 getSelectedColumnCount(void) const = 0;

    //Returns an array of indicies of all selected columns.
    virtual std::vector<UInt32> getSelectedColumns(void) const = 0;

    //Returns the total width of all the columns.
    virtual UInt32 getTotalColumnWidth(void) const = 0;

    //Moves the column and its header at columnIndex to newIndex.
    virtual void moveColumn(const UInt32& columnIndex, const UInt32& newIndex) = 0;

    //Deletes the TableColumn column from the tableColumns array.
    virtual void removeColumn(TableColumn* const column) = 0;

    //Sets the TableColumn's column margin to newMargin.
    virtual void setColumnMargin(const UInt32& newMargin) = 0;

    //Sets whether the columns in this model may be selected.
    virtual void setColumnSelectionAllowed(const bool& flag) = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableColumnModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableColumnModel(void);
    TableColumnModel(const TableColumnModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableColumnModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableColumnModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableColumnModel &source);
};

typedef TableColumnModel *TableColumnModelP;

OSG_END_NAMESPACE

#include "OSGTableColumnModelBase.inl"
#include "OSGTableColumnModel.inl"

#endif /* _OSGTABLECOLUMNMODEL_H_ */
