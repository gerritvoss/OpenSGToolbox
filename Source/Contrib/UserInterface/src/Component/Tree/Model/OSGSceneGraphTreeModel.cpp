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
        NodeRefPtr TheNode = boost::any_cast<NodeRefPtr>(parent);
        if(TheNode != NULL &&
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
        NodeRefPtr TheNode = boost::any_cast<NodeRefPtr>(node);
        if(TheNode != NULL &&
           TheNode != getInternalRoot() &&
           TheNode->getParent() != NULL)
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
        NodeRefPtr TheNode = boost::any_cast<NodeRefPtr>(parent);
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
        NodeRefPtr ParentNode = boost::any_cast<NodeRefPtr>(parent);
        NodeRefPtr ChildNode = boost::any_cast<NodeRefPtr>(child);
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
        NodeRefPtr NewNode = boost::any_cast<NodeRefPtr>(newValue);
        NodeRefPtr OldNode = boost::any_cast<NodeRefPtr>(path.getLastPathComponent());
        if(NewNode != NULL &&
           OldNode  != NULL &&
           NewNode != OldNode &&
           OldNode->getParent() != NULL)
        {
            NodeRefPtr ParentNode(OldNode->getParent());
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

void SceneGraphTreeModel::setRoot(NodeRefPtr root)
{
    setInternalRoot(root);
}

NodeRefPtr SceneGraphTreeModel::getRootNode(void) const
{
    return getInternalRoot();
}


bool SceneGraphTreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    try
    {
        NodeRefPtr LeftNode = boost::any_cast<NodeRefPtr>(left);
        NodeRefPtr RightNode = boost::any_cast<NodeRefPtr>(right);

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
