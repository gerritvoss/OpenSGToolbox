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

#ifndef _OSGDEFAULTTREEMODEL_H_
#define _OSGDEFAULTTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "Component/Tree/Model/OSGAbstractTreeModel.h"
#include "Component/Tree/Model/OSGDefaultMutableTreeNodeFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeModel class. See \ref 
           PageUserInterfaceDefaultTreeModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultTreeModel : public AbstractTreeModel
{
    /*==========================  PUBLIC  =================================*/
  public:

	//Returns the child of parent at index index in the parent's child array.
	virtual SharedFieldPtr getChild(SharedFieldPtr parent, const UInt32& index) const;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(SharedFieldPtr parent) const;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(SharedFieldPtr parent, SharedFieldPtr child) const;

	//Returns the root of the tree.
	virtual SharedFieldPtr getRoot(void) const;

	//Returns true if node is a leaf.
	virtual bool isLeaf(SharedFieldPtr node) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, SharedFieldPtr newValue);



    //Tells how leaf nodes are determined.
    bool asksAllowsChildren(void);

    //Builds the parents of node up to and including the root node, where the original node is the last element in the returned array.
    std::vector<MutableTreeNodePtr> getPathToRoot(ModelTreeNodePtr aNode);

    //Invoked this to insert newChild at location index in parents children.
    void insertNodeInto(MutableTreeNodePtr newChild, MutableTreeNodePtr parent, const UInt32& index);

    //Invoke this method after you've changed how node is to be represented in the tree.
    void nodeChanged(ModelTreeNodePtr node);

    //Invoke this method after you've changed how the children identified by childIndicies are to be represented in the tree.
    void nodesChanged(ModelTreeNodePtr node, std::vector<UInt32> childIndices);

    //Invoke this method if you've totally changed the children of node and its childrens children...
    void nodeStructureChanged(ModelTreeNodePtr node);

    //Invoke this method after you've inserted some TreeNodes into node.
    void nodesWereInserted(ModelTreeNodePtr node, std::vector<UInt32> childIndices);

    //Invoke this method after you've removed some TreeNodes from node.
    void nodesWereRemoved(ModelTreeNodePtr node, std::vector<UInt32> childIndices, std::vector<SharedFieldPtr> removedChildren);

    //Invoke this method if you've modified the TreeNodes upon which this model depends.
    void reload(void);

    //Invoke this method if you've modified the TreeNodes upon which this model depends.
    void reload(ModelTreeNodePtr node);

    //Message this to remove node from its parent.
    void removeNodeFromParent(MutableTreeNodePtr node);

    //Sets whether or not to test leafness by asking getAllowsChildren(void) or isLeaf(void) to the TreeNodes.
    void setAsksAllowsChildren(bool newValue);

    //Sets the root to root.
    void setRoot(ModelTreeNodePtr root);

    //Get the ModelTreeNodePtr to the Root Node
    ModelTreeNodePtr getRootNode(void) const;

  protected:
      ModelTreeNodePtr _Root;
      //Determines how the isLeaf method figures out if a node is a leaf node. If true, a node is a leaf node if it does not allow children.
      bool _AskAllowsChilren;

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultTreeModel *DefaultTreeModelPtr;

OSG_END_NAMESPACE

#define OSGDEFAULTTREEMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTTREEMODEL_H_ */
