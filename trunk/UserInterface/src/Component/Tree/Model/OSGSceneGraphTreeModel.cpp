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

#include "OSGSceneGraphTreeModel.h"
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGNodeCore.h>

#include "OSGSceneGraphTreeModel.h"
#include "Component/Tree/OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SceneGraphTreeModel
A UI SceneGraphTreeModel.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneGraphTreeModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
boost::any SceneGraphTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    try
    {
		NodePtr TheNode = boost::any_cast<NodePtr>(parent);
        if(TheNode != NullFC &&
           TheNode->getNChildren() > index)
        {
            return boost::any(TheNode->getChild(index));
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
        NodePtr TheNode = boost::any_cast<NodePtr>(node);
        if(TheNode != NullFC &&
            TheNode != getInternalRoot() &&
            TheNode->getParent() != NullFC)
        {
            return boost::any(TheNode->getParent());
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
        NodePtr TheNode = boost::any_cast<NodePtr>(parent);
        if(TheNode != NullFC)
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
        NodePtr ParentNode = boost::any_cast<NodePtr>(parent);
        NodePtr ChildNode = boost::any_cast<NodePtr>(child);
        if(ParentNode != NullFC &&
           ChildNode  != NullFC)
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
    return boost::any(getInternalRoot());
}

bool SceneGraphTreeModel::isLeaf(const boost::any& node) const
{
    return getChildCount(node) == 0;
}

void SceneGraphTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    try
    {
        NodePtr NewNode = boost::any_cast<NodePtr>(newValue);
        NodePtr OldNode = boost::any_cast<NodePtr>(path.getLastPathComponent());
        if(NewNode != NullFC &&
           OldNode  != NullFC &&
		   NewNode != OldNode &&
		   OldNode->getParent() != NullFC)
        {
			NodePtr ParentNode(OldNode->getParent());
			beginEditCP(ParentNode, Node::ChildrenFieldMask);
				if(ParentNode->replaceChildBy(OldNode, NewNode))
				{
					endEditCP(ParentNode, Node::ChildrenFieldMask);
					UInt32 ChildIndex(ParentNode->findChild(NewNode));
					produceTreeStructureChanged(path.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, newValue));
				}
				else
				{
					endEditNotChangedCP(ParentNode, Node::ChildrenFieldMask);
				}
        }
    }
    catch(boost::bad_any_cast &)
    {
    }
}

void SceneGraphTreeModel::setRoot(NodePtr root)
{
    beginEditCP(SceneGraphTreeModelPtr(this), InternalRootFieldMask);
        setInternalRoot(root);
    endEditCP(SceneGraphTreeModelPtr(this), InternalRootFieldMask);
}

NodePtr SceneGraphTreeModel::getRootNode(void) const
{
    return getInternalRoot();
}


bool SceneGraphTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        NodePtr LeftNode = boost::any_cast<NodePtr>(left);
        NodePtr RightNode = boost::any_cast<NodePtr>(right);

        return LeftNode == RightNode;
    }
    catch(boost::bad_any_cast &)
    {
        return false;
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

void SceneGraphTreeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

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

