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

#include "OSGDefaultTreeModel.h"
#include "OSGTreeModelListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTreeModel
A DefaultTreeModel. 
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

SharedFieldPtr DefaultTreeModel::getChild(SharedFieldPtr parent, const UInt32& index) const
{
    return _Root->getNodeFromUserObject(parent)->getChildAt(index)->getUserObject();
}

UInt32 DefaultTreeModel::getChildCount(SharedFieldPtr parent) const
{
    return _Root->getNodeFromUserObject(parent)->getChildCount();
}

UInt32 DefaultTreeModel::getIndexOfChild(SharedFieldPtr parent, SharedFieldPtr child) const
{
    TreeNodePtr ParentNode(_Root->getNodeFromUserObject(parent));
    return ParentNode->getIndex(ParentNode->getNodeFromUserObject(child));
}

SharedFieldPtr DefaultTreeModel::getRoot(void) const
{
    return _Root->getUserObject();
}

bool DefaultTreeModel::isLeaf(SharedFieldPtr node) const
{
    if(_AskAllowsChilren)
    {
        return !_Root->getNodeFromUserObject(node)->getAllowsChildren();
    }
    else
    {
        return _Root->getNodeFromUserObject(node)->getChildCount() == 0;
    }
}

void DefaultTreeModel::valueForPathChanged(TreePath path, SharedFieldPtr newValue)
{
    //Do nothing for the default Tree Model
}




void DefaultTreeModel::insertNodeInto(MutableTreeNodePtr newChild, MutableTreeNodePtr parent, const UInt32& index)
{
    parent->insert(newChild, index);
    //produceTreeStructureChanged();
}

void DefaultTreeModel::nodeChanged(TreeNodePtr node)
{
    //TODO:Implement
}

void DefaultTreeModel::nodesChanged(TreeNodePtr node, std::vector<UInt32> childIndices)
{
    //TODO:Implement
    //produceTreeNodesChanged();
}

void DefaultTreeModel::nodeStructureChanged(TreeNodePtr node)
{
    //TODO:Implement
    //produceTreeStructureChanged();
}

void DefaultTreeModel::nodesWereInserted(TreeNodePtr node, std::vector<UInt32> childIndices)
{
    std::vector<SharedFieldPtr> InstertedChildUserObjects;

    for(UInt32 i(0) ; i< childIndices.size() ; ++i)
    {
        InstertedChildUserObjects.push_back(node->getChildAt(childIndices[i])->getUserObject());
    }
    produceTreeNodesInserted(node->getPath(), childIndices, InstertedChildUserObjects);
}

void DefaultTreeModel::removeNodeFromParent(MutableTreeNodePtr node)
{
    node->removeFromParent();
    //produceTreeStructureChanged();
}

void DefaultTreeModel::setRoot(TreeNodePtr root)
{
    _Root = root;
    nodeChanged(_Root);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/
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

