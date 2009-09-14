/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
A UI AbstractTreeModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTreeModel::initMethod (void)
{
}


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

/*----------------------- constructors & destructors ----------------------*/

AbstractTreeModel::AbstractTreeModel(void) :
    Inherited()
{
}

AbstractTreeModel::AbstractTreeModel(const AbstractTreeModel &source) :
    Inherited(source)
{
}

AbstractTreeModel::~AbstractTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTreeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractTreeModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractTreeModel NI" << std::endl;
}


OSG_END_NAMESPACE

