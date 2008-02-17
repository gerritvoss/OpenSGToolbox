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

#include "OSGAbstractListModel.h"
#include "OSGListDataListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractListModel
A AbstractListModel. 
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

UInt32 AbstractListModel::getSize(void)
{
	return _FieldList.size();
}

SharedFieldPtr AbstractListModel::getElementAt(UInt32 index)
{
	if(index < _FieldList.size())
	{
		FieldListItor SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<index ; ++i) {++SearchItor;}
		return (*SearchItor);
	}
	else
	{
		return SharedFieldPtr();
	}
}


void AbstractListModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
}

void AbstractListModel::removeListDataListener(ListDataListenerPtr l)
{
   ListDataListenerSetIter EraseIter(_DataListeners.find(l));
   if(EraseIter != _DataListeners.end())
   {
      _DataListeners.erase(EraseIter);
   }
}
 
void AbstractListModel::pushBack(SharedFieldPtr f){
	_FieldList.push_back(f);
	produceListDataIntervalAdded(_FieldList.size()-1,_FieldList.size()-1);
}

void AbstractListModel::popBack(void){
	_FieldList.pop_back();
	produceListDataIntervalRemoved(_FieldList.size(),_FieldList.size());
}

void AbstractListModel::pushFront(SharedFieldPtr f)
{
	_FieldList.push_front(f);
	produceListDataIntervalAdded(0,0);
}

void AbstractListModel::popFront(void)
{
	_FieldList.pop_front();
	produceListDataIntervalRemoved(0,0);
}

void AbstractListModel::insert(UInt32 Index, SharedFieldPtr f)
{
	if(Index < _FieldList.size())
	{
		FieldListItor SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<Index ; ++i) {++SearchItor;}
		_FieldList.insert(SearchItor, f);
		produceListDataIntervalAdded(Index,Index);
	}
	else
	{
		pushBack(f);
	}
}

void AbstractListModel::erase(UInt32 Index)
{
	if(Index < _FieldList.size())
	{
		FieldListItor SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<Index ; ++i) {++SearchItor;}
		_FieldList.erase(SearchItor);
		produceListDataIntervalRemoved(Index,Index);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractListModel::AbstractListModel(void)
{
}

AbstractListModel::~AbstractListModel(void)
{
}


/*----------------------------- class specific ----------------------------*/

void AbstractListModel::produceListDataContentsChanged(void)
{
	ListDataEvent e(NullFC, getSystemTime(), 0, _FieldList.size()-1, ListDataEvent::CONTENTS_CHANGED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->contentsChanged(e);
   }
}

void AbstractListModel::produceListDataIntervalAdded(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalAdded(e);
   }
}

void AbstractListModel::produceListDataIntervalRemoved(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_REMOVED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalRemoved(e);
   }
}

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

