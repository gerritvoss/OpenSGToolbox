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

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractTreeSelectionModel.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTreeSelectionModel
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

void AbstractTreeSelectionModel::addTreeSelectionListener(TreeSelectionListenerPtr l)
{
	_SelectionListeners.insert(l);
}

void AbstractTreeSelectionModel::removeTreeSelectionListener(TreeSelectionListenerPtr l)
{
	TreeSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
	if(EraseIter != _SelectionListeners.end())
	{
		_SelectionListeners.erase(EraseIter);
	}
}

void AbstractTreeSelectionModel::addChangeListener(ChangeListenerPtr listener)
{
	_ChangeListeners.insert(listener);
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

void AbstractTreeSelectionModel::produceValueChanged(std::vector<TreePath> Paths, std::vector<bool> IsNew, TreePath NewLeadSelectionPath, TreePath OldLeadSelectionPath)
{
	TreeSelectionEvent TheEvent(NullFC, getSystemTime(), Paths, IsNew, NewLeadSelectionPath, OldLeadSelectionPath);
	TreeSelectionListenerSet ModelListenerSet(_SelectionListeners);
	for(TreeSelectionListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
	{
		(*SetItor)->valueChanged(TheEvent);
	}
}

void AbstractTreeSelectionModel::produceStateChanged(void)
{
	ChangeEvent TheEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED);
	ChangeListenerSet ListenerSet(_ChangeListeners);
	for(ChangeListenerSetConstIter SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
	{
	  (*SetItor)->stateChanged(TheEvent);
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

