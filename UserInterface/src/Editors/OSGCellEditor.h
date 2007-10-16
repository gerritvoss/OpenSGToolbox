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

#ifndef _OSG_UI_CELL_EDITOR_H_
#define _OSG_UI_CELL_EDITOR_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGField.h>
#include <OpenSG/Input/OSGEvent.h>
#include "OSGCellEditorListener.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING CellEditor
{
private:
protected:
public:
    //Adds a listener to the list that's notified when the editor stops, or cancels editing.
    virtual void addCellEditorListener(CellEditorListenerPtr l) = 0;

    //Removes a listener from the list that's notified
    virtual void removeCellEditorListener(CellEditorListenerPtr l) = 0;

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void) = 0;

    //Returns the value contained in the editor.
    virtual Field* getCellEditorValue(void) const = 0;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const = 0;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const = 0;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void) = 0;

};

typedef CellEditor* CellEditorPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_CELL_EDITOR_H_ */


