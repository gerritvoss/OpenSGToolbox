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

#include "OSGDefaultTreeModel.h"
#include "OSGDefaultMutableTreeNode.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ModelTreeNode* DefaultTreeModel::getNodeForPath(const TreePath& ThePath) const
{
    try
    {
        ModelTreeNodeRefPtr TheNode = boost::any_cast<ModelTreeNodeRefPtr>(ThePath.getLastPathComponent());

        return TheNode;
    }
    catch(boost::bad_any_cast &)
    {
        return NULL;
    }
}

boost::any DefaultTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
        ModelTreeNodeRefPtr ParentNode = boost::any_cast<ModelTreeNodeRefPtr>(parent);
        if(ParentNode != NULL &&
           index < ParentNode->getChildCount())
        {
            ModelTreeNodeRefPtr ChildNode = ParentNode->getChildAt(index);
            if(ChildNode != NULL)
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

UInt32 DefaultTreeModel::getChildCount(const boost::any& parent) const
{
    try
    {
        ModelTreeNodeRefPtr ParentNode = boost::any_cast<ModelTreeNodeRefPtr>(parent);
        if(ParentNode != NULL)
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
        ModelTreeNodeRefPtr ParentNode = boost::any_cast<ModelTreeNodeRefPtr>(parent);
        ModelTreeNodeRefPtr ChildNode = boost::any_cast<ModelTreeNodeRefPtr>(child);
        if(ParentNode != NULL &&
           ChildNode != NULL)
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
    if(getInternalRoot() != NULL)
    {
        return boost::any(ModelTreeNodeRefPtr(getInternalRoot()));
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
        ModelTreeNodeRefPtr TheNode = boost::any_cast<ModelTreeNodeRefPtr>(node);
        if(TheNode != NULL)
        {
            return (TheNode->getChildCount() == 0) || (getAskAllowsChildren() && !TheNode->getAllowsChildren());
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




void DefaultTreeModel::insertNodeInto(MutableTreeNode* const newChild, MutableTreeNode* const parent, const UInt32& index)
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

TreePath DefaultTreeModel::createPath(ModelTreeNode* const node) const
{
    std::deque<boost::any> PathVec;
    ModelTreeNodeRefPtr recNode(node);

    if(recNode != NULL)
    {
        while(recNode != NULL && recNode != getRootNode())
        {
            PathVec.push_front(boost::any(recNode));
            recNode = recNode->getParent();
        }
        if(recNode != NULL)
        {
            PathVec.push_front(boost::any(recNode));
        }
        else
        {
            return TreePath();
        }
    }

    return TreePath(PathVec, const_cast<DefaultTreeModel*>(this));
}

void DefaultTreeModel::nodeChanged(ModelTreeNode* const node)
{
    if(node->getParent() != NULL)
    {
        std::vector<UInt32> childIndices;
        childIndices.push_back(node->getParent()->getIndex(node));
        nodesChanged(node->getParent(), childIndices);
    }
}

void DefaultTreeModel::nodesChanged(ModelTreeNode* const node, std::vector<UInt32> childIndices)
{
    std::vector<boost::any> ChildUserObjects;

    for(UInt32 i(0) ; i< childIndices.size() ; ++i)
    {
        ChildUserObjects.push_back(dynamic_cast<ModelTreeNode*>(node->getChildAt(childIndices[i])));
    }

    produceTreeNodesChanged(createPath(node), childIndices, ChildUserObjects);
}

void DefaultTreeModel::nodeStructureChanged(ModelTreeNode* const node)
{
    //TODO:Implement
    //produceTreeStructureChanged();
}

void DefaultTreeModel::nodesWereInserted(ModelTreeNode* const node, std::vector<UInt32> childIndices)
{
    std::vector<boost::any> InstertedChildUserObjects;

    for(UInt32 i(0) ; i< childIndices.size() ; ++i)
    {
        InstertedChildUserObjects.push_back(dynamic_cast<ModelTreeNode*>(node->getChildAt(childIndices[i])));
    }
    produceTreeNodesInserted(createPath(node), childIndices, InstertedChildUserObjects);
}

void DefaultTreeModel::removeNodeFromParent(MutableTreeNode* const node)
{
    ModelTreeNodeRefPtr Parent = node->getParent();

    std::vector<UInt32> ChildIndicies;
    ChildIndicies.push_back(Parent->getIndex(node));

    std::vector<boost::any> Children;
    Children.push_back(dynamic_cast<ModelTreeNode*>(node));

    produceTreeNodesWillBeRemoved(createPath(Parent), ChildIndicies, Children);
    node->removeFromParent();
    produceTreeNodesRemoved(createPath(Parent), ChildIndicies, Children);
    if(Parent->getChildCount() == 0)
    {
        nodeChanged(Parent);
    }
}

void DefaultTreeModel::setRoot(ModelTreeNode* const root)
{
    setInternalRoot(root);
}

ModelTreeNode* DefaultTreeModel::getRootNode(void) const
{
    return getInternalRoot();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTreeModel::DefaultTreeModel(void) :
    Inherited()
{
}

DefaultTreeModel::DefaultTreeModel(const DefaultTreeModel &source) :
    Inherited(source)
{
}

DefaultTreeModel::~DefaultTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & InternalRootFieldMask)
    {
        if(getInternalRoot() != NULL)
        {
            nodeChanged(getInternalRoot());
        }
        else
        {
            //produceTreeStructureChanged();
        }
    }
}

void DefaultTreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
