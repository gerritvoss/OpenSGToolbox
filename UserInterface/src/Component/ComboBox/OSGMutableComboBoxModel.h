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

#ifndef _OSG_UI_MUTABLE_COMBOBOX_MODEL_H_
#define _OSG_UI_MUTABLE_COMBOBOX_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGComboBoxModel.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING MutableComboBoxModel : public ComboBoxModel
{
private:
protected:
public:
	//Adds an item at the end of the model.
	virtual void addElement(SharedFieldPtr obj) = 0;

	//Adds an item at a specific index.
	virtual void insertElementAt(SharedFieldPtr obj, const UInt32& index) = 0;

	//Removes an item from the model.
	virtual void removeElement(SharedFieldPtr obj) = 0;

	//Removes an item at a specific index.
	virtual void removeElementAt(const UInt32& index) = 0;

	//Removes all elements
	virtual void removeAllElements(void) = 0;
};

typedef MutableComboBoxModel* MutableComboBoxModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_MUTABLE_COMBOBOX_MODEL_H_ */

