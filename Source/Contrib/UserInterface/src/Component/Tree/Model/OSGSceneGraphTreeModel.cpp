/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGSceneGraphTreeModel.h"
#include "OSGNameAttachment.h"
#include "OSGNodeCore.h"

#include "OSGSceneGraphTreeModel.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneGraphTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneGraphTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneGraphTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

boost::any SceneGraphTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
        NodeUnrecPtr TheNode = boost::any_cast<NodeUnrecPtr>(parent);
        if(TheNode != NULL &&
           TheNode->getNChildren() > index)
        {
            return boost::any(NodeUnrecPtr(TheNode->getChild(index)));
        }
        else
        {
            return boost::any();
        }
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

boost::any SceneGraphTreeModel::getParent(const boost::any& node) const
{
    try
    {
        NodeUnrecPtr TheNode = boost::any_cast<NodeUnrecPtr>(node);
        if(TheNode != NULL &&
           TheNode != getInternalRoot() &&
           TheNode->getParent() != NULL)
        {
            return boost::any(NodeUnrecPtr(TheNode->getParent()));
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
    return boost::any();
}

UInt32 SceneGraphTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
        NodeUnrecPtr TheNode = boost::any_cast<NodeUnrecPtr>(parent);
        if(TheNode != NULL)
        {
            return TheNode->getNChildren();
        }
        else
        {
            return 0;
        }
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

UInt32 SceneGraphTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    try
    {
        NodeUnrecPtr ParentNode = boost::any_cast<NodeUnrecPtr>(parent);
        NodeUnrecPtr ChildNode = boost::any_cast<NodeUnrecPtr>(child);
        if(ParentNode != NULL &&
           ChildNode  != NULL)
        {
            return ParentNode->findChild(ChildNode);
        }
        else
        {
            return 0;
        }
    }
    catch(boost::bad_any_cast &)
    {
        return 0;
    }
}

boost::any SceneGraphTreeModel::getRoot(void) const
{
    return boost::any(NodeUnrecPtr(getInternalRoot()));
}

bool SceneGraphTreeModel::isLeaf(const boost::any& node) const
{
    return getChildCount(node) == 0;
}

void SceneGraphTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    try
    {
        NodeUnrecPtr NewNode = boost::any_cast<NodeUnrecPtr>(newValue);
        NodeUnrecPtr OldNode = boost::any_cast<NodeUnrecPtr>(path.getLastPathComponent());
        if(NewNode != NULL &&
           OldNode  != NULL &&
           NewNode != OldNode &&
           OldNode->getParent() != NULL)
        {
            NodeUnrecPtr ParentNode(OldNode->getParent());
            if(ParentNode->replaceChildBy(OldNode, NewNode))
            {
                UInt32 ChildIndex(ParentNode->findChild(NewNode));
                produceTreeStructureChanged(path.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, newValue));
            }
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
}

void SceneGraphTreeModel::setRoot(NodeUnrecPtr root)
{
    setInternalRoot(root);
}

NodeUnrecPtr SceneGraphTreeModel::getRootNode(void) const
{
    return getInternalRoot();
}

TreePath SceneGraphTreeModel::getPathForNode(NodeUnrecPtr theNode) const
{
    std::deque<boost::any> ResultPath;

    if(theNode != NULL &&
       getInternalRoot() != NULL &&
       theNode != getInternalRoot())
    {

        NodeUnrecPtr parentNode(theNode);
        while(parentNode != NULL &&
              parentNode != getInternalRoot())
        {
            ResultPath.push_front(boost::any(parentNode));
            parentNode = parentNode->getParent();
        }

        ResultPath.push_front(boost::any(getInternalRoot()));
    }

    return TreePath(ResultPath, TreeModelUnrecPtr(const_cast<SceneGraphTreeModel*>(this)));
}


bool SceneGraphTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        NodeUnrecPtr LeftNode = boost::any_cast<NodeUnrecPtr>(left);
        NodeUnrecPtr RightNode = boost::any_cast<NodeUnrecPtr>(right);

        return LeftNode == RightNode;
    }
    catch(boost::bad_any_cast &)
    {
        return false;
    }
}

void SceneGraphTreeModel::removeNode(const boost::any& nodeToBeRemoved)
{
    NodeRefPtr ntbr;
    try
    {
        ntbr = boost::any_cast<NodeUnrecPtr>(nodeToBeRemoved);
    }
    catch(boost::bad_any_cast &)
    {
        return;
    }

    NodeRefPtr parent = ntbr->getParent();

    TreePath pathOfNode = getPath(nodeToBeRemoved);
    if(parent!=NULL)
    {
        UInt32 ChildIndex(parent->findChild(ntbr));


        produceTreeNodesWillBeRemoved(pathOfNode.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, nodeToBeRemoved));
        parent->subChild(ntbr);
        produceTreeNodesRemoved(pathOfNode.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, nodeToBeRemoved));

        if(parent->getNChildren() == 0)
        {
            if(parent->getParent() != NULL)
            {
                std::vector<UInt32> childIndices;
                childIndices.push_back(parent->getParent()->findChild(parent));
                std::vector<boost::any> ChildUserObjects;
                for(UInt32 i(0) ; i< childIndices.size() ; ++i)
                {
                    ChildUserObjects.push_back(boost::any(parent->getParent()->getChild(childIndices[i])));
                }
                produceTreeNodesChanged(getPath(boost::any(parent->getParent())), childIndices, ChildUserObjects);
            }
        }
    }
}

void SceneGraphTreeModel::addNode(const boost::any& parent,const boost::any& nodeToBeAdded)
{
    NodeRefPtr parentNode;
    NodeRefPtr nodeToBeAddedNode;
    try
    {
        parentNode = boost::any_cast<NodeUnrecPtr>(parent);
        nodeToBeAddedNode = boost::any_cast<NodeUnrecPtr>(nodeToBeAdded);
    }
    catch(boost::bad_any_cast &)
    {
        return;
    }
    UInt32 ChildIndex(parentNode->getNChildren());
    parentNode->addChild(nodeToBeAddedNode);
    produceTreeNodesInserted(getPath(parent),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, nodeToBeAdded));

    if(parentNode->getNChildren() == 1)
    {
        if(parentNode->getParent() != NULL)
        {
            std::vector<UInt32> childIndices;
            childIndices.push_back(parentNode->getParent()->findChild(parentNode));
            std::vector<boost::any> ChildUserObjects;
            for(UInt32 i(0) ; i< childIndices.size() ; ++i)
            {
                ChildUserObjects.push_back(boost::any(parentNode->getParent()->getChild(childIndices[i])));
            }
            produceTreeNodesChanged(getPath(boost::any(parentNode->getParent())), childIndices, ChildUserObjects);
        }
    }
}	

void SceneGraphTreeModel::insertNode(const boost::any& parent,
                                     const boost::any& nodeToBeAdded,
                                     UInt32 Index)
{
    NodeRefPtr parentNode;
    NodeRefPtr nodeToBeAddedNode;
    try
    {
        parentNode = boost::any_cast<NodeUnrecPtr>(parent);
        nodeToBeAddedNode = boost::any_cast<NodeUnrecPtr>(nodeToBeAdded);
    }
    catch(boost::bad_any_cast &)
    {
        return;
    }
    parentNode->insertChild(Index, nodeToBeAddedNode);
    produceTreeNodesInserted(getPath(parent),std::vector<UInt32>(1, Index),std::vector<boost::any>(1, nodeToBeAdded));

    if(parentNode->getNChildren() == 1)
    {
        if(parentNode->getParent() != NULL)
        {
            std::vector<UInt32> childIndices;
            childIndices.push_back(parentNode->getParent()->findChild(parentNode));
            std::vector<boost::any> ChildUserObjects;
            for(UInt32 i(0) ; i< childIndices.size() ; ++i)
            {
                ChildUserObjects.push_back(boost::any(parentNode->getParent()->getChild(childIndices[i])));
            }
            produceTreeNodesChanged(getPath(boost::any(parentNode->getParent())), childIndices, ChildUserObjects);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneGraphTreeModel::SceneGraphTreeModel(void) :
    Inherited()
{
}

SceneGraphTreeModel::SceneGraphTreeModel(const SceneGraphTreeModel &source) :
    Inherited(source)
{
}

SceneGraphTreeModel::~SceneGraphTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneGraphTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & InternalRootFieldMask)
    {
        produceTreeStructureChanged(getPath(getInternalRoot()),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, boost::any(getInternalRoot())));
    }
}

void SceneGraphTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneGraphTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
