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

#ifndef _OSG_UI_COMBOBOX_MODEL_H_
#define _OSG_UI_COMBOBOX_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "Component/List/OSGListModel.h"
#include "OSGComboBoxSelectionListener.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING ComboBoxModel : public ListModel
{
private:
protected:
public:
	//Returns the selected item
	virtual SharedFieldPtr getSelectedItem(void) const = 0;

	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const = 0;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index) = 0;
	
	//Set the selected item.
	virtual void setSelectedItem(SharedFieldPtr anObject) = 0;
	
	virtual void addSelectionListener(ComboBoxSelectionListenerPtr l) = 0;

	virtual void removeSelectionListener(ComboBoxSelectionListenerPtr l) = 0;
};

typedef ComboBoxModel* ComboBoxModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_COMBOBOX_MODEL_H_ */

