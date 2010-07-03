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

#include "OSGDefaultMutableTreeNode.h"
#include "OSGMutableTreeNode.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultMutableTreeNodeBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultMutableTreeNode.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultMutableTreeNode::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DefaultMutableTreeNode::getAllowsChildren(void) const
{
    return getAllowsChildrenInternal();
}

ModelTreeNode* DefaultMutableTreeNode::getChildAt(const UInt32& childIndex) const
{
    if(childIndex > getMFChildrenInternal()->size())
    {
        return NULL;
    }
    else
    {
        return getChildrenInternal(childIndex);
    }
}

UInt32 DefaultMutableTreeNode::getChildCount(void) const
{
    return getMFChildrenInternal()->size();
}

Int32 DefaultMutableTreeNode::getIndex(ModelTreeNode* const node) const
{
    for(Int32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(getChildrenInternal(i) == node)
        {
            return i;
        }
    }

    return -1;
}

ModelTreeNode* DefaultMutableTreeNode::getParent(void) const
{
    return getParentInternal();
}

bool DefaultMutableTreeNode::isLeaf(void) const
{
    return !getAllowsChildrenInternal() || getMFChildrenInternal()->size() == 0;
}

void DefaultMutableTreeNode::insert(MutableTreeNode* const child, const UInt32& index)
{
    if(index <= getMFChildrenInternal()->size())
    {
        MFChildrenInternalType::iterator InsertPos(editMFChildrenInternal()->begin());
        InsertPos += index;

        //Remove the Child from the old parent
        child->removeFromParent();

        //Add the Child
        editMFChildrenInternal()->insert(InsertPos, child);

        //Set the Childs Parent
        child->setParent(this);
    }
}

void DefaultMutableTreeNode::remove(const UInt32& index)
{
    if(index < getMFChildrenInternal()->size())
    {
        removeFromChildrenInternal(index);
    }
}

void DefaultMutableTreeNode::remove(MutableTreeNode* const node)
{
    removeObjFromChildrenInternal(node);
}

void DefaultMutableTreeNode::removeFromParent(void)
{
    if(getParentInternal() != NULL)
    {
        getParentInternal()->remove(this);
    }
}

void DefaultMutableTreeNode::setParent(MutableTreeNode* const newParent)
{
    setParentInternal(newParent);
}

void DefaultMutableTreeNode::setUserObject(const boost::any& object)
{
    _UserObject = object;
}

void DefaultMutableTreeNode::add(MutableTreeNode* const newChild)
{
    insert(newChild, getMFChildrenInternal()->size()-1);
}

MutableTreeNode* DefaultMutableTreeNode::getChildAfter(MutableTreeNode* const aChild) const
{
    UInt32 i(0);
    for( ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(getChildrenInternal(i) == aChild &&
           i+1 != getMFChildrenInternal()->size())
        {
            return getChildrenInternal(i+1);
        }
    }

    return NULL;
}

MutableTreeNode* DefaultMutableTreeNode::getChildBefore(MutableTreeNode* const aChild) const
{
    UInt32 i(1);
    for( ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(getChildrenInternal(i) == aChild)
        {
            return getChildrenInternal(i-1);
        }
    }

    return NULL;
}

UInt32 DefaultMutableTreeNode::getHeight(void) const
{
    UInt32 Max(0);
    for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
    {
        Max = osgMax(Max, dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->getHeight());
    }
    return Max+1;
}

MutableTreeNode* DefaultMutableTreeNode::getFirstChild(void) const
{
    if(getMFChildrenInternal()->size() > 0)
    {
        return getMFChildrenInternal()->front();
    }
    else
    {
        return NULL;
    }
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getFirstLeaf(void) const
{
    const DefaultMutableTreeNode* Child(this);
    while(!Child->isLeaf())
    {
        Child =
            dynamic_cast<const DefaultMutableTreeNode*>(Child->getMFChildrenInternal()->front());
    }
    return const_cast<DefaultMutableTreeNode*>(Child);
}

MutableTreeNode* DefaultMutableTreeNode::getLastChild(void) const
{
    if(getMFChildrenInternal()->size() > 0)
    {
        return getMFChildrenInternal()->back();
    }
    else
    {
        return NULL;
    }
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getLastLeaf(void) const
{
    const DefaultMutableTreeNode* Child(this);
    while(!Child->isLeaf())
    {
        Child =
            dynamic_cast<DefaultMutableTreeNode*>(Child->getMFChildrenInternal()->back());
    }
    return const_cast<DefaultMutableTreeNode*>(Child);
}

UInt32 DefaultMutableTreeNode::getLeafCount(void) const
{
    UInt32 Count(0);
    for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->isLeaf())
        {
            ++Count;
        }
        else
        {
            Count += dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->getLeafCount();
        }
    }
    return Count;
}

UInt32 DefaultMutableTreeNode::getDepth(void) const
{
    ModelTreeNodeRefPtr ParentNode(getParent());
    UInt32 Depth(0);
    while(ParentNode != NULL)
    {
        ParentNode = ParentNode->getParent();
        ++Depth;
    }

    return Depth;
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getNextLeaf(void) const
{
    const DefaultMutableTreeNode* ParentNode(this);
    while(ParentNode->getParentInternal() != NULL && ParentNode->getNextSibling() == NULL)
    {
        ParentNode = dynamic_cast<const DefaultMutableTreeNode*>(ParentNode->getParentInternal());
    }

    if(ParentNode->getParentInternal() != NULL)
    {
        return ParentNode->getNextSibling()->getFirstLeaf();
    }
    else
    {
        return NULL;
    }
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getNextNode(void) const
{
    if(getMFChildrenInternal()->size() != 0)
    {
        return const_cast<DefaultMutableTreeNode*>(dynamic_cast<const
            DefaultMutableTreeNode*>(getMFChildrenInternal()->front()));
    }
    else
    {
        const DefaultMutableTreeNode* ParentNode(this);
        const DefaultMutableTreeNode* NextSibling;
        while(ParentNode != NULL)
        {
            NextSibling = ParentNode->getNextSibling();
            if(NextSibling != NULL)
            {
                return const_cast<DefaultMutableTreeNode*>(NextSibling);
            }
            ParentNode = dynamic_cast<const DefaultMutableTreeNode*>(ParentNode->getParentInternal());
        }
    }

    return NULL;
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getNextSibling(void) const
{
    if(getParentInternal() != NULL)
    {
        return
            dynamic_cast<DefaultMutableTreeNode*>(getParentInternal()->getChildAt(getParentInternal()->getIndex(MutableTreeNodeRefPtr(const_cast<DefaultMutableTreeNode*>(this))+1)));
    }
    else
    {
        return NULL;
    }
}

std::vector<MutableTreeNodeRefPtr> DefaultMutableTreeNode::getPath(void) const
{
    std::vector<MutableTreeNodeRefPtr> Path;

    const MutableTreeNode* Node(this);
    while(Node != NULL)
    {
        Path.push_back(const_cast<MutableTreeNode*>(Node));
        Node = dynamic_cast<const MutableTreeNode*>(Node->getParent());
    }

    std::reverse(Path.begin(), Path.end());

    return Path;
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousLeaf(void) const
{
    const DefaultMutableTreeNode* ParentNode(this);
    while(ParentNode->getParentInternal() != NULL && ParentNode->getPreviousSibling() == NULL)
    {
        ParentNode = dynamic_cast<const DefaultMutableTreeNode*>(ParentNode->getParentInternal());
    }

    if(ParentNode->getParentInternal() != NULL)
    {
        return ParentNode->getPreviousSibling()->getLastLeaf();
    }
    else
    {
        return NULL;
    }
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousNode(void) const
{
    if(getParentInternal() != NULL)
    {
        if(dynamic_cast<const
           DefaultMutableTreeNode*>(getParentInternal())->getFirstChild() == this)
        {
            return const_cast<DefaultMutableTreeNode*>(dynamic_cast<const
                                                       DefaultMutableTreeNode*>(getParentInternal()));
        }
        else
        {
            const DefaultMutableTreeNode* RightMostNode(getPreviousSibling());
            while(!RightMostNode->isLeaf())
            {
                RightMostNode =
                    dynamic_cast<const DefaultMutableTreeNode*>(RightMostNode->getMFChildrenInternal()->back());
            }
            return const_cast<DefaultMutableTreeNode*>(RightMostNode);
        }
    }
    else
    {
        return NULL;
    }
}

DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousSibling(void) const
{
    if(getParentInternal() != NULL)
    {
        Int32
            MyIndex(getParentInternal()->getIndex(DefaultMutableTreeNodeRefPtr(const_cast<DefaultMutableTreeNode*>(this))));
        if(MyIndex < 1)
        {
            return NULL;
        }
        else
        {
            return dynamic_cast<DefaultMutableTreeNode*>(getParentInternal()->getChildAt(MyIndex-1));
        }
    }
    else
    {
        return NULL;
    }
}

MutableTreeNode* DefaultMutableTreeNode::getRoot(void) const
{
    ModelTreeNodeRefPtr ParentNode(getParent());
    while(ParentNode != NULL)
    {
        ParentNode = ParentNode->getParent();
    }

    return dynamic_pointer_cast<MutableTreeNode>(ParentNode);
}

MutableTreeNode* DefaultMutableTreeNode::getSharedAncestor(DefaultMutableTreeNode* const aNode) const
{
    if(this == aNode)
    {
        return aNode;
    }

    std::vector<MutableTreeNodeRefPtr> MyPathToRoot(getPath()),
        OtherNodePathToRoot(aNode->getPath());

    UInt32 Index(0);
    while(Index < MyPathToRoot.size() && Index < OtherNodePathToRoot.size() &&
          MyPathToRoot[Index] == OtherNodePathToRoot[Index])
    {
        ++Index;
    }

    if(Index != MyPathToRoot.size() && Index != OtherNodePathToRoot.size())
    {
        return MyPathToRoot[Index-1];
    }
    else
    {
        return NULL;
    }
}

UInt32 DefaultMutableTreeNode::getSiblingCount(void) const
{
    if(getParentInternal() != NULL)
    {
        return getParentInternal()->getChildCount() - 1;
    }
    else
    {
        return 0;
    }
}

boost::any DefaultMutableTreeNode::getUserObject(void) const
{
    return _UserObject;
}

std::vector<boost::any> DefaultMutableTreeNode::getUserObjectPath(void) const
{
    std::vector<boost::any> UserObjectPath;

    const DefaultMutableTreeNode* Node(this);
    while(Node != NULL)
    {
        UserObjectPath.push_back(Node->getUserObject());
        Node = dynamic_cast<const
            DefaultMutableTreeNode*>(Node->getParent());
    }

    std::reverse(UserObjectPath.begin(), UserObjectPath.end());

    return UserObjectPath;
}

bool DefaultMutableTreeNode::isNodeAncestor(MutableTreeNode* const anotherNode) const
{
    std::vector<MutableTreeNodeRefPtr> MyPathToRoot(getPath());
    for(UInt32 i(0) ; i<MyPathToRoot.size() ; ++i)
    {
        if(MyPathToRoot[i] == anotherNode)
        {
            return true;
        }
    }

    return false;
}

bool DefaultMutableTreeNode::isNodeChild(MutableTreeNode* const aNode) const
{
    for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(getChildrenInternal(i) == aNode)
        {
            return true;
        }
    }
    return false;
}

bool DefaultMutableTreeNode::isNodeDescendant(DefaultMutableTreeNode* const anotherNode) const
{
    if(this == anotherNode)
    {
        return anotherNode;
    }

    for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
    {
        if(dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->isNodeDescendant(anotherNode))
        {
            return true;
        }
    }

    return false;
}

bool DefaultMutableTreeNode::isNodeRelated(DefaultMutableTreeNode* const aNode) const
{
    return getRoot() == aNode->getRoot();
}

bool DefaultMutableTreeNode::isNodeSibling(MutableTreeNode* const anotherNode) const
{
    if(getParentInternal() != NULL)
    {
        for(UInt32 i(0) ; i<dynamic_cast<DefaultMutableTreeNode*>(getParentInternal())->getMFChildrenInternal()->size() ; ++i)
        {
            if(dynamic_cast<const DefaultMutableTreeNode*>(getParentInternal())->getChildrenInternal(i) == anotherNode)
            {
                return true;
            }
        }
    }

    return false;
}

bool DefaultMutableTreeNode::isRoot(void) const
{
    return getParent() != NULL;
}

void DefaultMutableTreeNode::removeAllChildren(void)
{
    clearChildrenInternal();
}

void DefaultMutableTreeNode::heightFirst(std::vector<DefaultMutableTreeNodeRefPtr>& Result) const
{
    //Call the postorder traversal
    postorder(Result);
}

void DefaultMutableTreeNode::postorder(std::vector<DefaultMutableTreeNodeRefPtr>& Result) const
{
    if(!isLeaf())
    {
        for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
        {
            dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->postorder(Result);
        }
    }

    //Push Myself on the Vector
    Result.push_back(DefaultMutableTreeNodeRefPtr(const_cast<DefaultMutableTreeNode*>(this)));
}

void DefaultMutableTreeNode::preorder(std::vector<DefaultMutableTreeNodeRefPtr>& Result) const
{
    //Push Myself on the Vector
    Result.push_back(DefaultMutableTreeNodeRefPtr(const_cast<DefaultMutableTreeNode*>(this)));

    if(!isLeaf())
    {
        for(UInt32 i(0) ; i<getMFChildrenInternal()->size() ; ++i)
        {
            dynamic_cast<DefaultMutableTreeNode*>(getChildrenInternal(i))->preorder(Result);
        }
    }
}

void DefaultMutableTreeNode::breadthFirst(std::vector<DefaultMutableTreeNodeRefPtr>& Result) const
{
    //Push Myself on the Vector
    Result.push_back(DefaultMutableTreeNodeRefPtr(const_cast<DefaultMutableTreeNode*>(this)));


    std::vector<ModelTreeNodeRefPtr> CurrentDepthNodes;
    std::vector<ModelTreeNodeRefPtr> NextDepthNodes(getChildren());
    while(NextDepthNodes.size() != 0)
    {
        for(UInt32 i(0) ; i<NextDepthNodes.size() ; ++i)
        {
            Result.push_back(dynamic_pointer_cast<DefaultMutableTreeNode>(NextDepthNodes[i]));
        }

        CurrentDepthNodes = NextDepthNodes;
        NextDepthNodes.clear();
        std::vector<ModelTreeNodeRefPtr> Children;
        for(UInt32 i(0) ; i<CurrentDepthNodes.size() ; ++i)
        {
            Children = CurrentDepthNodes[i]->getChildren();
            NextDepthNodes.insert(NextDepthNodes.end(), Children.begin(), Children.end());
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultMutableTreeNode::DefaultMutableTreeNode(void) :
    Inherited()
{
}

DefaultMutableTreeNode::DefaultMutableTreeNode(const DefaultMutableTreeNode &source) :
    Inherited(source)
{
}

DefaultMutableTreeNode::~DefaultMutableTreeNode(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultMutableTreeNode::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultMutableTreeNode::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultMutableTreeNode NI" << std::endl;
}

OSG_END_NAMESPACE
