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

#ifndef _OSGABSTRACTTREEMODEL_H_
#define _OSGABSTRACTTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "Component/Tree/Model/OSGTreeModel.h"
#include <set>
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeModel class. See \ref 
           PageUserInterfaceAbstractTreeModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTreeModel : public TreeModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	//Adds a listener for the TreeModelEvent posted after the tree changes.
	virtual void addTreeModelListener(TreeModelListenerPtr l);

	//Removes a listener previously added with addTreeModelListener.
	virtual void removeTreeModelListener(TreeModelListenerPtr l);
  protected:

	typedef std::set<TreeModelListenerPtr> TreeModelListenerSet;
	typedef TreeModelListenerSet::iterator TreeModelListenerSetIter;
	typedef TreeModelListenerSet::const_iterator TreeModelListenerSetConstIter;
	TreeModelListenerSet _ModelListeners;

	void produceTreeNodesChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesInserted(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesWillBeRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeStructureChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
    /*==========================  PRIVATE  ================================*/
  private:
};

typedef AbstractTreeModel *AbstractTreeModelPtr;

OSG_END_NAMESPACE

#define OSGABSTRACTTREEMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTREEMODEL_H_ */
