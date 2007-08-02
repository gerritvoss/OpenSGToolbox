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

Field* AbstractListModel::getElementAt(UInt32 index)
{
   return _FieldList[index];
}


void AbstractListModel::addListDataListener(ListDataListenerPtr l)
{
   if(std::find(_DataListeners.begin(), _DataListeners.end(), l) != _DataListeners.end())
   {
	   _DataListeners.push_back(l);
   }
}

void AbstractListModel::removeListDataListener(ListDataListenerPtr l)
{
   if(std::find(_DataListeners.begin(), _DataListeners.end(), l) != _DataListeners.end())
   {
	   _DataListeners.remove(l);
   }
}
 
void AbstractListModel::pushBack(Field* f){
	_FieldList.push_back(f);
	produceListDataIntervalAdded(_FieldList.size()-1,_FieldList.size());
}

void AbstractListModel::popBack(void){
	_FieldList.pop_back();
	produceListDataIntervalRemoved(_FieldList.size(),_FieldList.size());
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
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin() ; Iter != _DataListeners.end() ; ++Iter)
	{
		(*Iter)->contentsChanged(e);
	}
}

void AbstractListModel::produceListDataIntervalAdded(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED, this);
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin(); Iter != _DataListeners.end(); ++Iter)
	{
		(*Iter)->intervalAdded(e);
	}
}

void AbstractListModel::produceListDataIntervalRemoved(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_REMOVED, this);
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin(); Iter != _DataListeners.end(); ++Iter)
	{
		(*Iter)->intervalRemoved(e);
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

