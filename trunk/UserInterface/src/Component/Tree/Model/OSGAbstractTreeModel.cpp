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

#include "OSGAbstractTreeModel.h"
#include "OSGTreeModelListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTreeModel
A AbstractTreeModel. 
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

EventConnection AbstractTreeModel::addTreeModelListener(TreeModelListenerPtr l)
{
    _ModelListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractTreeModel::isTreeModelListenerAttached, this, l),
       boost::bind(&AbstractTreeModel::removeTreeModelListener, this, l));
}

bool AbstractTreeModel::isTreeModelListenerAttached(TreeModelListenerPtr l) const
{
    return _ModelListeners.find(l) != _ModelListeners.end();
}

void AbstractTreeModel::removeTreeModelListener(TreeModelListenerPtr l)
{
   TreeModelListenerSetIter EraseIter(_ModelListeners.find(l));
   if(EraseIter != _ModelListeners.end())
   {
      _ModelListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

void AbstractTreeModel::produceTreeNodesChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEvent TheEvent(NullFC, getSystemTime(), Parent, ChildIndices, Children);
   TreeModelListenerSet ModelListenerSet(_ModelListeners);
   for(TreeModelListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->treeNodesChanged(TheEvent);
   }
}

void AbstractTreeModel::produceTreeNodesInserted(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEvent TheEvent(NullFC, getSystemTime(), Parent, ChildIndices, Children);
   TreeModelListenerSet ModelListenerSet(_ModelListeners);
   for(TreeModelListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->treeNodesInserted(TheEvent);
   }
}

void AbstractTreeModel::produceTreeNodesWillBeRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEvent TheEvent(NullFC, getSystemTime(), Parent, ChildIndices, Children);
   TreeModelListenerSet ModelListenerSet(_ModelListeners);
   for(TreeModelListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->treeNodesWillBeRemoved(TheEvent);
   }
}

void AbstractTreeModel::produceTreeNodesRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEvent TheEvent(NullFC, getSystemTime(), Parent, ChildIndices, Children);
   TreeModelListenerSet ModelListenerSet(_ModelListeners);
   for(TreeModelListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->treeNodesRemoved(TheEvent);
   }
}

void AbstractTreeModel::produceTreeStructureChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children)
{
   TreeModelEvent TheEvent(NullFC, getSystemTime(), Parent, ChildIndices, Children);
   TreeModelListenerSet ModelListenerSet(_ModelListeners);
   for(TreeModelListenerSetConstIter SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->treeStructureChanged(TheEvent);
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

