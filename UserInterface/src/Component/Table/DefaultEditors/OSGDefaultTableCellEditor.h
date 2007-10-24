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

#ifndef _OSG_UI_DEFAULT_TABLE_CELL_EDITOR_H_
#define _OSG_UI_DEFAULT_TABLE_CELL_EDITOR_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "Editors/OSGAbstractCellEditor.h"
#include "Component/Table/OSGTableCellEditor.h"

#include "Event/OSGActionListener.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING DefaultTableCellEditor : public AbstractCellEditor, public TableCellEditor, public ActionListener
{
private:
protected:
    UInt32 _ClickCountToStart;
    ComponentPtr _EditingComponent;
    Field* _Value;
public:
    
	virtual ComponentPtr getTableCellEditorComponent(TablePtr table, Field* value, bool isSelected, UInt32 row, UInt32 column);

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Returns the value contained in the editor.
    virtual Field* getCellEditorValue(void) const;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    //Returns the number of clicks needed to start editing.
    UInt32 getClickCountToStart(void) const;

    //Returns a reference to the editor component.
    ComponentPtr getComponent(void) const;

    //Specifies the number of clicks needed to start editing.
    void setClickCountToStart(const UInt32& count);
    
    virtual void actionPerformed(const ActionEvent& e);
};

typedef boost::intrusive_ptr<DefaultTableCellEditor> DefaultTableCellEditorPtr;

OSG_END_NAMESPACE

#include "OSGDefaultTableCellEditor.inl"

#endif /* _OSG_UI_DEFAULT_TABLE_CELL_EDITOR_H_ */


