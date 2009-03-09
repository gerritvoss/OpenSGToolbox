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
#include "Component/Tree/Model/OSGDefaultMutableTreeNode.h"

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

ModelTreeNodePtr DefaultTreeModel::getNodeForPath(const TreePath& ThePath) const
{
    try
    {
        ModelTreeNodePtr TheNode = boost::any_cast<ModelTreeNodePtr>(ThePath.getLastPathComponent());
        
        return TheNode;
    }
    catch(boost::bad_any_cast &)
    {
        return NullFC;
    }
}

boost::any DefaultTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
        ModelTreeNodePtr ParentNode = boost::any_cast<ModelTreeNodePtr>(parent);
        if(ParentNode != NullFC &&
           index < ParentNode->getChildCount())
        {
            ModelTreeNodePtr ChildNode = ParentNode->getChildAt(index);
            if(ChildNode != NullFC)
            {
                return boost::any(ChildNode);
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

    
boost::any DefaultTreeModel::getParent(const boost::any& node) const
{
    try
    {
        ModelTreeNodePtr Node = boost::any_cast<ModelTreeNodePtr>(node);
        if(Node != NullFC &&
           Node != _Root  &&
           Node->getParent() != NullFC)
        {
            return boost::any(Node->getParent());
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

UInt32 DefaultTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
        ModelTreeNodePtr ParentNode = boost::any_cast<ModelTreeNodePtr>(parent);
        if(ParentNode != NullFC)
        {
            return ParentNode->getChildCount();
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return 0;
}

UInt32 DefaultTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    try
    {
        ModelTreeNodePtr ParentNode = boost::any_cast<ModelTreeNodePtr>(parent);
        ModelTreeNodePtr ChildNode = boost::any_cast<ModelTreeNodePtr>(child);
        if(ParentNode != NullFC &&
           ChildNode != NullFC)
        {
            Int32 Index = ParentNode->getIndex(ChildNode);
            if(Index > 0)
            {
                return static_cast<UInt32>(Index);
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return 0;
}

boost::any DefaultTreeModel::getRoot(void) const
{
    if(_Root != NullFC)
    {
        return boost::any(_Root);
    }
    else
    {
        return boost::any();
    }
}

bool DefaultTreeModel::isLeaf(const boost::any& node) const
{
    try
    {
        ModelTreeNodePtr TheNode = boost::any_cast<ModelTreeNodePtr>(node);
        if(TheNode != NullFC)
        {
            if(_AskAllowsChilren)
            {
                return TheNode->getAllowsChildren();
            }
            else
            {
                return TheNode->getChildCount() == 0;
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return false;

}

void DefaultTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    //Do nothing for the default Tree Model
}




void DefaultTreeModel::insertNodeInto(MutableTreeNodePtr newChild, MutableTreeNodePtr parent, const UInt32& index)
{
    parent->insert(newChild, index);

    std::vector<UInt32> Indices;
    Indices.push_back(index);
    nodesWereInserted(parent, Indices);
	if(parent->getChildCount() == 1)
	{
		nodeChanged(parent);
	}
}

void DefaultTreeModel::nodeChanged(ModelTreeNodePtr node)
{
	if(node->getParent() != NullFC)
	{
		std::vector<UInt32> childIndices;
		childIndices.push_back(node->getParent()->getIndex(node));
		nodesChanged(node->getParent(), childIndices);
	}
}

void DefaultTreeModel::nodesChanged(ModelTreeNodePtr node, std::vector<UInt32> childIndices)
{
    std::vector<boost::any> ChildUserObjects;

    for(UInt32 i(0) ; i< childIndices.size() ; ++i)
    {
        ChildUserObjects.push_back(ModelTreeNode::Ptr::dcast(node->getChildAt(childIndices[i])));
    }

    produceTreeNodesChanged(getPath(boost::any(node)), childIndices, ChildUserObjects);
}

void DefaultTreeModel::nodeStructureChanged(ModelTreeNodePtr node)
{
    //TODO:Implement
    //produceTreeStructureChanged();
}

void DefaultTreeModel::nodesWereInserted(ModelTreeNodePtr node, std::vector<UInt32> childIndices)
{
    std::vector<boost::any> InstertedChildUserObjects;

    for(UInt32 i(0) ; i< childIndices.size() ; ++i)
    {
        InstertedChildUserObjects.push_back(ModelTreeNode::Ptr::dcast(node->getChildAt(childIndices[i])));
    }
    produceTreeNodesInserted(getPath(boost::any(node)), childIndices, InstertedChildUserObjects);
}

void DefaultTreeModel::removeNodeFromParent(MutableTreeNodePtr node)
{
    ModelTreeNodePtr Parent = node->getParent();

    std::vector<UInt32> ChildIndicies;
    ChildIndicies.push_back(Parent->getIndex(node));
    
    std::vector<boost::any> Children;
    Children.push_back(ModelTreeNode::Ptr::dcast(node));

    produceTreeNodesWillBeRemoved(getPath(boost::any(Parent)), ChildIndicies, Children);
    node->removeFromParent();
    produceTreeNodesRemoved(getPath(boost::any(Parent)), ChildIndicies, Children);
	if(Parent->getChildCount() == 0)
	{
		nodeChanged(Parent);
	}
}

void DefaultTreeModel::setRoot(ModelTreeNodePtr root)
{
    _Root = root;
    nodeChanged(_Root);
}

ModelTreeNodePtr DefaultTreeModel::getRootNode(void) const
{
    return _Root;
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

