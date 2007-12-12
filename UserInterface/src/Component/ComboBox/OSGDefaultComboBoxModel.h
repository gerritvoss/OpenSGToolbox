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

#include "OSGMutableComboBoxModel.h"
#include <vector>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultComboBoxModel class. See \ref 
           PageUserInterfaceDefaultComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultComboBoxModel : public MutableComboBoxModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	virtual void addListDataListener(ListDataListenerPtr l);
	
	virtual void removeListDataListener(ListDataListenerPtr l);

	virtual void addSelectionListener(ComboBoxSelectionListenerPtr l);
	
	virtual void removeSelectionListener(ComboBoxSelectionListenerPtr l);

	virtual UInt32 getSize(void);

	virtual SharedFieldPtr getElementAt(UInt32 index);

	//Returns the selected item
	virtual SharedFieldPtr getSelectedItem(void) const;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index);
	
	//Set the selected item.
	virtual void setSelectedItem(SharedFieldPtr anObject);
	
	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const;

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
	Int32 _SelectedIndex;

	typedef std::set<ListDataListenerPtr> ListDataListenerSet;
	typedef ListDataListenerSet::iterator ListDataListenerSetIter;
	typedef ListDataListenerSet::const_iterator ListDataListenerSetConstIter;
	ListDataListenerSet _DataListeners;

	void produceListDataContentsChanged(void);
	void produceListDataIntervalAdded(UInt32 index0, UInt32 index1);
	void produceListDataIntervalRemoved(UInt32 index0, UInt32 index1);

	typedef std::set<ComboBoxSelectionListenerPtr> ComboBoxSelectionListenerSet;
	typedef ComboBoxSelectionListenerSet::iterator ComboBoxSelectionListenerSetIter;
	typedef ComboBoxSelectionListenerSet::const_iterator ComboBoxSelectionListenerSetConstIter;
	ComboBoxSelectionListenerSet _SelectionListeners;

	void produceSelectionChanged(const Int32& CurrentIndex, const Int32& PreviousIndex);

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultComboBoxModel *DefaultComboBoxModelPtr;

OSG_END_NAMESPACE

#define OSGDEFAULTCOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTCOMBOBOXMODEL_H_ */
