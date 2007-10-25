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

#ifndef _OSG_UI_ABSTRACT_CELL_EDITOR_H_
#define _OSG_UI_ABSTRACT_CELL_EDITOR_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGCellEditor.h"
#include <set>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING AbstractCellEditor : virtual public CellEditor
{
private:
protected:
	typedef std::set<CellEditorListenerPtr> CellEditorListenerSet;
    typedef CellEditorListenerSet::iterator CellEditorListenerSetItor;
    typedef CellEditorListenerSet::const_iterator CellEditorListenerSetConstItor;
	CellEditorListenerSet _CellEditorListeners;

    
	void produceEditingCanceled(void);
	void produceEditingStopped(void);
public:
    //Adds a listener to the list that's notified when the editor stops, or cancels editing.
    virtual void addCellEditorListener(CellEditorListenerPtr l);

    //Removes a listener from the list that's notified
    virtual void removeCellEditorListener(CellEditorListenerPtr l);

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

};

typedef AbstractCellEditor* AbstractCellEditorPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_ABSTRACT_CELL_EDITOR_H_ */


