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

#ifndef _OSGDEFAULTCOMBOBOXMODEL_H_
#define _OSGDEFAULTCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractComboBoxModel.h"
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultComboBoxModel class. See \ref 
           PageUserInterfaceDefaultComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultComboBoxModel : public AbstractComboBoxModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	virtual UInt32 getSize(void);

	virtual SharedFieldPtr getElementAt(UInt32 index);

	//Returns the selected item
	virtual SharedFieldPtr getSelectedItem(void) const;

	//Set the selected item.
	virtual void setSelectedItem(const UInt32& index);

	//Adds an item at the end of the model.
	void addElement(SharedFieldPtr anObject);

	//Adds an item at a specific index.
	void insertElementAt(SharedFieldPtr anObject, const UInt32& index);

	//Empties the list.
	void removeAllElements(void);

	//Removes an item from the model.
	void removeElement(SharedFieldPtr anObject);

	//Removes an item at a specific index.
	void removeElementAt(const UInt32& index);

	DefaultComboBoxModel();
  protected:
	std::vector<SharedFieldPtr> _FieldList;
	UInt32 _SelectedIndex;

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultComboBoxModel *DefaultComboBoxModelPtr;

OSG_END_NAMESPACE

#define OSGDEFAULTCOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTCOMBOBOXMODEL_H_ */
