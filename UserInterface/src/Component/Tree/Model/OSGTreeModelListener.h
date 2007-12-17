/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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

#ifndef _OSG_UI_TREE_MODEL_LISTENER_H_
#define _OSG_UI_TREE_MODEL_LISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTreeModelEvent.h"

#include <OpenSG/Input/OSGEventListener.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING TreeModelListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
public:

	//Invoked after a node (or a set of siblings) has changed in some way.
	virtual void treeNodesChanged(TreeModelEvent e) = 0;

	//Invoked after nodes have been inserted into the tree.
	virtual void treeNodesInserted(TreeModelEvent e) = 0;

	//Invoked after nodes have been removed from the tree.
	virtual void treeNodesRemoved(TreeModelEvent e) = 0;

	//Invoked after the tree has drastically changed structure from a given node down.
	virtual void treeStructureChanged(TreeModelEvent e) = 0;
};

typedef TreeModelListener* TreeModelListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TREE_MODEL_LISTENER_H_ */
