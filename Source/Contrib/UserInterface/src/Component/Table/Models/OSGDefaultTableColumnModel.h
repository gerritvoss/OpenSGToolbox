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

#ifndef _OSGDEFAULTTABLECOLUMNMODEL_H_
#define _OSGDEFAULTTABLECOLUMNMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultTableColumnModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTableColumnModel class. See \ref
           PageContribUserInterfaceDefaultTableColumnModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTableColumnModel : public DefaultTableColumnModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTableColumnModelBase Inherited;
    typedef DefaultTableColumnModel     Self;

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
    virtual void addColumn(TableColumn* const aColumn);

    //Returns the TableColumn object for the column at columnIndex.
    virtual TableColumn* getColumn(const UInt32& columnIndex) const;

    //Returns the number of columns in the model.
    virtual UInt32 getColumnCount(void) const;

    //Returns the index of the column that lies on the horizontal point, xPosition; or -1 if it lies outside the any of the column's bounds.
    virtual Int32 getColumnIndexAtX(UInt32 xPosition) const;

    //Returns the width between the cells in each column.
    virtual UInt32 getColumnMargin(void) const;

    //Returns an Enumeration of all the columns in the model.
    //virtual std::vector<TableColumnUnrecPtr> getColumns(void) const;

    //Returns true if columns may be selected.
    virtual bool getColumnSelectionAllowed(void) const;

    //Returns the number of selected columns.
    virtual UInt32 getSelectedColumnCount(void) const;

    //Returns an array of indicies of all selected columns.
    virtual std::vector<UInt32> getSelectedColumns(void) const;

    //Returns the total width of all the columns.
    virtual UInt32 getTotalColumnWidth(void) const;

    //Moves the column and its header at columnIndex to newIndex.
    virtual void moveColumn(const UInt32& columnIndex, const UInt32& newIndex);

    //Deletes the TableColumn column from the tableColumns array.
    virtual void removeColumn(TableColumn* const column);

    //Sets the TableColumn's column margin to newMargin.
    virtual void setColumnMargin(const UInt32& newMargin);

    //Sets whether the columns in this model may be selected.
    virtual void setColumnSelectionAllowed(const bool& flag);

    /*=========================  PROTECTED  ===============================*/

  protected:

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    void recalcWidthCache(void);

    UInt32 _ColumnMargin;
    bool _ColumnSelectionAllowed;;
    UInt32 _TotalColumnWidth;
    
    void handleSelectionChanged(ListSelectionEventDetails* const e);
    boost::signals2::connection _SelectionChangedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTableColumnModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTableColumnModel &source);
};

typedef DefaultTableColumnModel *DefaultTableColumnModelP;

OSG_END_NAMESPACE

#include "OSGDefaultTableColumnModelBase.inl"
#include "OSGDefaultTableColumnModel.inl"

#endif /* _OSGDEFAULTTABLECOLUMNMODEL_H_ */
