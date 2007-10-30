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

#ifndef _OSG_UI_TABLE_MODEL_H_
#define _OSG_UI_TABLE_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

#include "OSGTableModelListener.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING TableModel : public IntrusivePtrImplBase
{
private:
protected:
public:

    //Adds a listener to the list that is notified each time a change to the data model occurs.
    virtual void addTableModelListener(TableModelListenerPtr l) = 0;
    
    //Removes a listener from the list that is notified each time a change to the data model occurs.
    virtual void removeTableModelListener(TableModelListenerPtr l) = 0;
    
    //Returns the number of columns in the model.
    virtual UInt32 getColumnCount(void) const = 0;
    
    //Returns the name of the column at columnIndex.
    virtual SharedFieldPtr getColumnValue(UInt32 columnIndex) const = 0;
    
    //Returns the number of rows in the model.
    virtual UInt32 getRowCount(void) const = 0;
    
    //Returns the value for the cell at columnIndex and rowIndex.
    virtual SharedFieldPtr getValueAt(UInt32 rowIndex, UInt32 columnIndex) const = 0;
    
    //Returns true if the cell at rowIndex and columnIndex is editable.
    virtual bool isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const = 0;
    
    //Sets the value in the cell at columnIndex and rowIndex to aValue.
    virtual void setValueAt(SharedFieldPtr aValue, UInt32 rowIndex, UInt32 columnIndex) = 0;

    //Returns the most specific superclass for all the cell values in the column.
    virtual const FieldType* getColumnType(const UInt32& columnIndex) = 0;
};

typedef boost::intrusive_ptr<TableModel> TableModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TABLE_MODEL_H_ */

