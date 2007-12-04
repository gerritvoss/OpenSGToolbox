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

#include "OSGAbstractComboBoxModel.h"
#include "Component/List/OSGListDataListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractComboBoxModel
A AbstractComboBoxModel. 
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

void AbstractComboBoxModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
}

void AbstractComboBoxModel::removeListDataListener(ListDataListenerPtr l)
{
   ListDataListenerSetIter EraseIter(_DataListeners.find(l));
   if(EraseIter != _DataListeners.end())
   {
      _DataListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

void AbstractComboBoxModel::produceListDataContentsChanged(void)
{
	ListDataEvent e(NullFC, getSystemTime(), 0, getSize()-1, ListDataEvent::CONTENTS_CHANGED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->contentsChanged(e);
   }
}

void AbstractComboBoxModel::produceListDataIntervalAdded(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(NullFC, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED, this);
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalAdded(e);
   }
}

void AbstractComboBoxModel::produceListDataIntervalRemoved(UInt32 index0, UInt32 index1)
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

