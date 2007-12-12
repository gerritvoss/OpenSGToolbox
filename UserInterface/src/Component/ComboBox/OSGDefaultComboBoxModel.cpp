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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultComboBoxModel.h"
#include "Component/List/OSGListDataListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultComboBoxModel
A DefaultComboBoxModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultComboBoxModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
}

void DefaultComboBoxModel::removeListDataListener(ListDataListenerPtr l)
{
   ListDataListenerSetIter EraseIter(_DataListeners.find(l));
   if(EraseIter != _DataListeners.end())
   {
      _DataListeners.erase(EraseIter);
   }
}

void DefaultComboBoxModel::addSelectionListener(ComboBoxSelectionListenerPtr l)
{
    _SelectionListeners.insert(l);
}

void DefaultComboBoxModel::removeSelectionListener(ComboBoxSelectionListenerPtr l)
{
   ComboBoxSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
   if(EraseIter != _SelectionListeners.end())
   {
      _SelectionListeners.erase(EraseIter);
   }
}

UInt32 DefaultComboBoxModel::getSize(void)
{
	return _FieldList.size();
}

SharedFieldPtr DefaultComboBoxModel::getElementAt(UInt32 index)
{
   return _FieldList[index];
}

SharedFieldPtr DefaultComboBoxModel::getSelectedItem(void) const
{
	if(_SelectedIndex < 0 ||
	   _SelectedIndex >= _FieldList.size())
	{
		return SharedFieldPtr();
	}
	else
	{
		return _FieldList[_SelectedIndex];
	}
}

Int32 DefaultComboBoxModel::getSelectedItemIndex(void) const
{
	return _SelectedIndex;
}

void DefaultComboBoxModel::setSelectedItem(const Int32& index)
{
	Int32 PreviousIndex(_SelectedIndex);
	_SelectedIndex = index;

	if(_SelectedIndex != PreviousIndex)
	{
		produceSelectionChanged(_SelectedIndex, PreviousIndex);
	}
}

void DefaultComboBoxModel::setSelectedItem(SharedFieldPtr anObject)
{
	Int32 PreviousIndex(_SelectedIndex);

	UInt32 index(0);
	while(index < _FieldList.size() && _FieldList[index] != anObject)
	{
		++index;
	}

	if(index < _FieldList.size())
	{
		_SelectedIndex = index;
	}
	else
	{
		_SelectedIndex = -1;
	}

	if(_SelectedIndex != PreviousIndex)
	{
		produceSelectionChanged(_SelectedIndex, PreviousIndex);
	}
}

void DefaultComboBoxModel::addElement(SharedFieldPtr anObject)
{
	_FieldList.push_back(anObject);
}

void DefaultComboBoxModel::insertElementAt(SharedFieldPtr anObject, const UInt32& index)
{
	if(index < _FieldList.size())
	{
		std::vector<SharedFieldPtr>::iterator InsertItor(_FieldList.begin());
		for(UInt32 i(0); i<index ; ++i ) ++InsertItor;

		_FieldList.insert(InsertItor, anObject);
	}
	else
	{
		_FieldList.push_back(anObject);
	}
}

void DefaultComboBoxModel::removeAllElements(void)
{
	_FieldList.clear();
}

void DefaultComboBoxModel::removeElement(SharedFieldPtr anObject)
{
	std::vector<SharedFieldPtr>::iterator SearchItor(std::find(_FieldList.begin(), _FieldList.end(), anObject));

	if(SearchItor != _FieldList.end())
	{
		_FieldList.erase(SearchItor);
	}
}

void DefaultComboBoxModel::removeElementAt(const UInt32& index)
{
	if(index < _FieldList.size())
	{
		std::vector<SharedFieldPtr>::iterator RemoveItor(_FieldList.begin());
		for(UInt32 i(0); i<index ; ++i ) ++RemoveItor;

		_FieldList.erase(RemoveItor);
	}
}

void DefaultComboBoxModel::produceListDataContentsChanged(void)
{
	ListDataEvent e(NullFC, getSystemTime(), 0, getSize()-1, ListDataEvent::CONTENTS_CHANGED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->contentsChanged(e);
   }
}

void DefaultComboBoxModel::produceListDataIntervalAdded(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalAdded(e);
   }
}

void DefaultComboBoxModel::produceListDataIntervalRemoved(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_REMOVED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalRemoved(e);
   }
}


void DefaultComboBoxModel::produceSelectionChanged(const Int32& CurrentIndex, const Int32& PreviousIndex)
{
	ComboBoxSelectionEvent e(NullFC, getSystemTime(), CurrentIndex, PreviousIndex);
	ComboBoxSelectionListenerSet SelectionListenerSet(_SelectionListeners);
	for(ComboBoxSelectionListenerSetConstIter SetItor(SelectionListenerSet.begin()) ; SetItor != SelectionListenerSet.end() ; ++SetItor)
	{
		(*SetItor)->selectionChanged(e);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultComboBoxModel::DefaultComboBoxModel() : _SelectedIndex(-1)
{
}
/*----------------------------- class specific ----------------------------*/
/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

