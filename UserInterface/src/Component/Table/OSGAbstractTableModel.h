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

#ifndef _OSG_UI_ABSTRACT_TABLE_MODEL_H_
#define _OSG_UI_ABSTRACT_TABLE_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTableModel.h"
#include <set>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING AbstractTableModel : public TableModel
{
protected:
	typedef std::set<TableModelListenerPtr> TableModelListenerSet;
    typedef TableModelListenerSet::iterator TableModelListenerSetItor;
    typedef TableModelListenerSet::const_iterator TableModelListenerSetConstItor;
	TableModelListenerSet _ModelListeners;

	void produceContentsHeaderRowChanged(UInt32 FirstColumn, UInt32 LastColumn);
	void produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
    
public:

    //Adds a listener to the list that is notified each time a change to the data model occurs.
    virtual void addTableModelListener(TableModelListenerPtr l);
    
    //Removes a listener from the list that is notified each time a change to the data model occurs.
    virtual void removeTableModelListener(TableModelListenerPtr l);
    
    //Returns the name of the column at columnIndex.
    virtual std::string getColumnName(UInt32 columnIndex) const;
    
    //Returns true if the cell at rowIndex and columnIndex is editable.
    virtual bool isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const;
    
    //Sets the value in the cell at columnIndex and rowIndex to aValue.
    virtual void setValueAt(Field* aValue, UInt32 rowIndex, UInt32 columnIndex);
    
};

typedef boost::intrusive_ptr<AbstractTableModel> AbstractTableModelPtr;

OSG_END_NAMESPACE

#include "OSGAbstractTableModel.inl"

#endif /* _OSG_UI_ABSTRACT_TABLE_MODEL_H_ */

