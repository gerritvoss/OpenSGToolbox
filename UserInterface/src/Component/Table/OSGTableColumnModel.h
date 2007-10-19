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

#ifndef _OSG_UI_TABLE_COLUMN_MODEL_H_
#define _OSG_UI_TABLE_COLUMN_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/OSGField.h>
#include "OSGTableColumn.h"
#include "Component/List/OSGListSelectionModel.h"
#include "OSGTableColumnModelListener.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING TableColumnModel : public IntrusivePtrImplBase
{
private:
protected:
public:
    //Adds a listener for table column model events.
    virtual void addColumnModelListener(TableColumnModelListenerPtr l) = 0;

    //Removes a listener for table column model events.
    virtual void removeColumnModelListener(TableColumnModelListenerPtr l) = 0;

    //Appends aColumn to the end of the tableColumns array.
    virtual void addColumn(const TableColumnPtr aColumn) = 0;

    //Returns the TableColumn object for the column at columnIndex.
    virtual TableColumnPtr getColumn(const UInt32& columnIndex) const = 0;

    //Returns the number of columns in the model.
    virtual UInt32 getColumnCount(void) const = 0;

    //Returns the index of the column that lies on the horizontal point, xPosition; or -1 if it lies outside the any of the column's bounds.
    virtual Int32 getColumnIndexAtX(UInt32 xPosition) const = 0;

    //Returns the width between the cells in each column.
    virtual UInt32 getColumnMargin(void) const = 0;

    //Returns an Enumeration of all the columns in the model.
    virtual std::vector<TableColumnPtr> getColumns(void) const = 0;

    //Returns true if columns may be selected.
    virtual bool getColumnSelectionAllowed(void) const = 0;

    //Returns the number of selected columns.
    virtual UInt32 getSelectedColumnCount(void) const = 0;

    //Returns an array of indicies of all selected columns.
    virtual std::vector<UInt32> getSelectedColumns(void) const = 0;

    //Returns the current selection model.
    virtual ListSelectionModelPtr getSelectionModel(void) const = 0;

    //Returns the total width of all the columns.
    virtual UInt32 getTotalColumnWidth(void) const = 0;

    //Moves the column and its header at columnIndex to newIndex.
    virtual void moveColumn(const UInt32& columnIndex, const UInt32& newIndex) = 0;

    //Deletes the TableColumn column from the tableColumns array.
    virtual void removeColumn(TableColumnPtr column) = 0;

    //Sets the TableColumn's column margin to newMargin.
    virtual void setColumnMargin(const UInt32& newMargin) = 0;

    //Sets whether the columns in this model may be selected.
    virtual void setColumnSelectionAllowed(const bool& flag) = 0;

    //Sets the selection model.
    virtual void setSelectionModel(ListSelectionModelPtr newModel) = 0;

};

typedef boost::intrusive_ptr<TableColumnModel> TableColumnModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TABLE_COLUMN_MODEL_H_ */

