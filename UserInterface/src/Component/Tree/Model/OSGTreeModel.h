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

#ifndef _OSG_UI_TREE_MODEL_H_
#define _OSG_UI_TREE_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

OSG_BEGIN_NAMESPACE
class TreeModelListener;
class TreePath;
typedef TreeModelListener* TreeModelListenerPtr;
	 
class OSG_USERINTERFACELIB_DLLMAPPING TreeModel
{
private:
protected:
public:

	//Adds a listener for the TreeModelEvent posted after the tree changes.
	virtual void addTreeModelListener(TreeModelListenerPtr l) = 0;

	//Removes a listener previously added with addTreeModelListener.
	virtual void removeTreeModelListener(TreeModelListenerPtr l) = 0;

	//Returns the child of parent at index index in the parent's child array.
	virtual SharedFieldPtr getChild(SharedFieldPtr parent, const UInt32& index) const = 0;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(SharedFieldPtr parent) const = 0;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(SharedFieldPtr parent, SharedFieldPtr child) const = 0;

	//Returns the root of the tree.
	virtual SharedFieldPtr getRoot(void) const = 0;

	//Returns true if node is a leaf.
	virtual bool isLeaf(SharedFieldPtr node) const = 0;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, SharedFieldPtr newValue) = 0;
};

typedef TreeModel* TreeModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TREE_MODEL_H_ */

