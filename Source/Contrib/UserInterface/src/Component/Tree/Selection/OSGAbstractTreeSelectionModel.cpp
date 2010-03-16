/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Aaron Cronk                                      *
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

#include "OSGConfig.h"

#include "OSGAbstractTreeSelectionModel.h"
#include "OSGTreeSelectionListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AbstractTreeSelectionModel
A AbstractTreeSelectionModel. 
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

EventConnection AbstractTreeSelectionModel::addTreeSelectionListener(TreeSelectionListenerPtr l)
{
	_SelectionListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractTreeSelectionModel::isTreeSelectionListenerAttached, this, l),
       boost::bind(&AbstractTreeSelectionModel::removeTreeSelectionListener, this, l));
}

bool AbstractTreeSelectionModel::isTreeSelectionListenerAttached(TreeSelectionListenerPtr l) const
{
    return _SelectionListeners.find(l) != _SelectionListeners.end();
}

void AbstractTreeSelectionModel::removeTreeSelectionListener(TreeSelectionListenerPtr l)
{
	TreeSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
	if(EraseIter != _SelectionListeners.end())
	{
		_SelectionListeners.erase(EraseIter);
	}
}

EventConnection AbstractTreeSelectionModel::addChangeListener(ChangeListenerPtr listener)
{
	_ChangeListeners.insert(listener);
   return EventConnection(
       boost::bind(&AbstractTreeSelectionModel::isChangeListenerAttached, this, listener),
       boost::bind(&AbstractTreeSelectionModel::removeChangeListener, this, listener));
}

bool AbstractTreeSelectionModel::isChangeListenerAttached(ChangeListenerPtr listener) const
{
    return _ChangeListeners.find(listener) != _ChangeListeners.end();
}

void AbstractTreeSelectionModel::removeChangeListener(ChangeListenerPtr listener)
{
	ChangeListenerSetIter EraseIter(_ChangeListeners.find(listener));
	if(EraseIter != _ChangeListeners.end())
	{
		_ChangeListeners.erase(EraseIter);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

void AbstractTreeSelectionModel::produceSelectionAdded(const std::vector<NumberRange>& ElementsAdded, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath)
{
    const TreeSelectionEventUnrecPtr TheEvent = TreeSelectionEvent::create(NULL, getSystemTime(), ElementsAdded, NewLeadSelectionPath, OldLeadSelectionPath);
	TreeSelectionListenerSet ModelListenerSet(_SelectionListeners);
	for(TreeSelectionListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
	{
		(*SetItor)->selectionAdded(TheEvent);
	}
}

void AbstractTreeSelectionModel::produceSelectionRemoved(const std::vector<NumberRange>& ElementsRemoved, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath)
{
    const TreeSelectionEventUnrecPtr TheEvent = TreeSelectionEvent::create(NULL, getSystemTime(), ElementsRemoved, NewLeadSelectionPath, OldLeadSelectionPath);
	TreeSelectionListenerSet ModelListenerSet(_SelectionListeners);
	for(TreeSelectionListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
	{
		(*SetItor)->selectionRemoved(TheEvent);
	}
}

OSG_END_NAMESPACE

