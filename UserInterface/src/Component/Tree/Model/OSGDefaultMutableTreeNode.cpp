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

#include "OSGDefaultMutableTreeNode.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultMutableTreeNode
A UI Default Mutable Tree Node. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultMutableTreeNode::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


bool DefaultMutableTreeNode::getAllowsChildren(void) const
{
	return getAllowsChildrenInternal();
}

TreeNodePtr DefaultMutableTreeNode::getChildAt(const UInt32& childIndex) const
{
	if(childIndex > getChildrenInternal().size())
	{
		return NullFC;
	}
	else
	{
		return getChildrenInternal()[childIndex];
	}
}

UInt32 DefaultMutableTreeNode::getChildCount(void) const
{
	return getChildrenInternal().size();
}

Int32 DefaultMutableTreeNode::getIndex(TreeNodePtr node) const
{
	for(Int32 i(0) ; i<getChildrenInternal().size() ; ++i)
	{
		if(getChildrenInternal()[i] == node)
		{
			return i;
		}
	}

	return -1;
}

TreeNodePtr DefaultMutableTreeNode::getParent(void) const
{
	return getParentInternal();
}

bool DefaultMutableTreeNode::isLeaf(void) const
{
	return !getAllowsChildrenInternal();
}

void DefaultMutableTreeNode::insert(MutableTreeNodePtr child, const UInt32& index)
{
	if(index < getChildrenInternal().size())
	{
		MFMutableTreeNodePtr::iterator InsertPos(getChildrenInternal().begin());
		InsertPos += index;

		//Remove the Child from the old parent
		child->removeFromParent();

		//Add the Child
		beginEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
			getChildrenInternal().insert(InsertPos, child);
		endEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);

		//Set the Childs Parent
		child->setParent(MutableTreeNodePtr(this));
	}
}

void DefaultMutableTreeNode::remove(const UInt32& index)
{
	if(index < getChildrenInternal().size())
	{
		MFMutableTreeNodePtr::iterator RemovePos(getChildrenInternal().begin());
		RemovePos += index;

		beginEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
			getChildrenInternal().erase(RemovePos);
		endEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
	}
}

void DefaultMutableTreeNode::remove(MutableTreeNodePtr node)
{
	MFMutableTreeNodePtr::iterator RemovePos(getChildrenInternal().find(node));
	if(RemovePos != getChildrenInternal().end())
	{
		beginEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
			getChildrenInternal().erase(RemovePos);
		endEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
	}
}

void DefaultMutableTreeNode::removeFromParent(void)
{
	if(getParentInternal() != NullFC)
	{
		getParentInternal()->remove(MutableTreeNodePtr(this));
	}
}

void DefaultMutableTreeNode::setParent(MutableTreeNodePtr newParent)
{
	beginEditCP(DefaultMutableTreeNodePtr(this), ParentInternalFieldMask);
		setParentInternal(newParent);
	endEditCP(DefaultMutableTreeNodePtr(this), ParentInternalFieldMask);
}

void DefaultMutableTreeNode::setUserObject(SharedFieldPtr object)
{
	_UserObject = object;
}

void DefaultMutableTreeNode::add(MutableTreeNodePtr newChild)
{
	insert(newChild, getChildrenInternal().size()-1);
}

MutableTreeNodePtr DefaultMutableTreeNode::getChildAfter(MutableTreeNodePtr aChild) const
{
	MFMutableTreeNodePtr::const_iterator ChildPos(getChildrenInternal().find(aChild));
	if(ChildPos == getChildrenInternal().end())
	{
		return NullFC;
	}
	else
	{
		MFMutableTreeNodePtr::const_iterator NextChildPos(ChildPos);
		++NextChildPos;
		if(NextChildPos == getChildrenInternal().end())
		{
			return NullFC;
		}
		else
		{
			return (*NextChildPos);
		}
	}
}

MutableTreeNodePtr DefaultMutableTreeNode::getChildBefore(MutableTreeNodePtr aChild) const
{
	MFMutableTreeNodePtr::const_iterator ChildPos(getChildrenInternal().find(aChild));
	if(ChildPos == getChildrenInternal().end())
	{
		return NullFC;
	}
	else
	{
		if(ChildPos == getChildrenInternal().begin())
		{
			return NullFC;
		}
		else
		{
			++ChildPos;
			return (*ChildPos);
		}
	}
}

UInt32 DefaultMutableTreeNode::getDepth(void) const
{
	UInt32 Max(0);
	for(UInt32 i(0) ; i<getChildrenInternal().size() ; ++i)
	{
		Max = osgMax(Max, DefaultMutableTreeNode::Ptr::dcast(getChildrenInternal()[i])->getDepth());
	}
	return Max+1;
}

MutableTreeNodePtr DefaultMutableTreeNode::getFirstChild(void) const
{
	if(getChildrenInternal().size() > 0)
	{
		return getChildrenInternal().front();
	}
	else
	{
		return NullFC;
	}
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getFirstLeaf(void) const
{
	DefaultMutableTreeNodePtr Child(DefaultMutableTreeNodePtr(this));
	while(!Child->isLeaf())
	{
		Child = DefaultMutableTreeNode::Ptr::dcast(Child->getChildrenInternal().front());
	}
	return Child;
}

MutableTreeNodePtr DefaultMutableTreeNode::getLastChild(void) const
{
	if(getChildrenInternal().size() > 0)
	{
		return getChildrenInternal().back();
	}
	else
	{
		return NullFC;
	}
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getLastLeaf(void) const
{
	DefaultMutableTreeNodePtr Child(DefaultMutableTreeNodePtr(this));
	while(!Child->isLeaf())
	{
		Child = DefaultMutableTreeNode::Ptr::dcast(Child->getChildrenInternal().back());
	}
	return Child;
}

UInt32 DefaultMutableTreeNode::getLeafCount(void) const
{
	UInt32 Count(0);
	for(UInt32 i(0) ; i<getChildrenInternal().size() ; ++i)
	{
		if(DefaultMutableTreeNode::Ptr::dcast(getChildrenInternal()[i])->isLeaf())
		{
			++Count;
		}
		else
		{
			Count += DefaultMutableTreeNode::Ptr::dcast(getChildrenInternal()[i])->getLeafCount();
		}
	}
	return Count;
}

UInt32 DefaultMutableTreeNode::getLevel(void) const
{
	TreeNodePtr ParentNode(getParent());
	UInt32 Level(0);
	while(ParentNode != NullFC)
	{
		ParentNode = ParentNode->getParent();
		++Level;
	}

	return Level;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getNextLeaf(void) const
{
	//TODO:Implement
	return NullFC;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getNextNode(void) const
{
	//TODO:Implement
	return NullFC;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getNextSibling(void) const
{
	if(getParentInternal() != NullFC)
	{
		return DefaultMutableTreeNode::Ptr::dcast(getParentInternal()->getChildAt(getParentInternal()->getIndex(DefaultMutableTreeNodePtr(this))+1));
	}
	else
	{
		return NullFC;
	}
}

std::vector<MutableTreeNodePtr> DefaultMutableTreeNode::getPath(void) const
{
	std::vector<MutableTreeNodePtr> Path;

	MutableTreeNodePtr Node(MutableTreeNodePtr(this));
	while(Node != NullFC)
	{
		Path.push_back(Node);
		Node = MutableTreeNode::Ptr::dcast(Node->getParent());
	}

	std::reverse(Path.begin(), Path.end());

	return Path;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getPreviousLeaf(void) const
{
	//TODO:Implement
	return NullFC;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getPreviousNode(void) const
{
	//TODO:Implement
	return NullFC;
}

DefaultMutableTreeNodePtr DefaultMutableTreeNode::getPreviousSibling(void) const
{
	if(getParentInternal() != NullFC)
	{
		Int32 MyIndex(getParentInternal()->getIndex(DefaultMutableTreeNodePtr(this)));
		if(MyIndex < 1)
		{
			return NullFC;
		}
		else
		{
			return DefaultMutableTreeNode::Ptr::dcast(getParentInternal()->getChildAt(MyIndex-1));
		}
	}
	else
	{
		return NullFC;
	}
}

MutableTreeNodePtr DefaultMutableTreeNode::getRoot(void) const
{
	TreeNodePtr ParentNode(getParent());
	while(ParentNode != NullFC)
	{
		ParentNode = ParentNode->getParent();
	}

	return MutableTreeNode::Ptr::dcast(ParentNode);
}

MutableTreeNodePtr DefaultMutableTreeNode::getSharedAncestor(DefaultMutableTreeNodePtr aNode) const
{
	if(DefaultMutableTreeNodePtr(this) == aNode)
	{
		return aNode;
	}

	std::vector<MutableTreeNodePtr> MyPathToRoot(getPath()),
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
		return NullFC;
	}
}

UInt32 DefaultMutableTreeNode::getSiblingCount(void) const
{
	if(getParentInternal() != NullFC)
	{
		return getParentInternal()->getChildCount() - 1;
	}
}

SharedFieldPtr DefaultMutableTreeNode::getUserObject(void) const
{
	return _UserObject;
}

std::vector<SharedFieldPtr> DefaultMutableTreeNode::getUserObjectPath(void) const
{
	std::vector<SharedFieldPtr> UserObjectPath;

	DefaultMutableTreeNodePtr Node(DefaultMutableTreeNodePtr(this));
	while(Node != NullFC)
	{
		UserObjectPath.push_back(Node->getUserObject());
		Node = DefaultMutableTreeNode::Ptr::dcast(Node->getParent());
	}

	std::reverse(UserObjectPath.begin(), UserObjectPath.end());

	//TODO:Implement
	return UserObjectPath;
}

bool DefaultMutableTreeNode::isNodeAncestor(MutableTreeNodePtr anotherNode) const
{
	std::vector<MutableTreeNodePtr> MyPathToRoot(getPath());
	for(UInt32 i(0) ; i<MyPathToRoot.size() ; ++i)
	{
		if(MyPathToRoot[i] == anotherNode)
		{
			return true;
		}
	}

	return false;
}

bool DefaultMutableTreeNode::isNodeChild(MutableTreeNodePtr aNode) const
{
	for(UInt32 i(0) ; i<getChildrenInternal().size() ; ++i)
	{
		if(getChildrenInternal()[i] == aNode)
		{
			return true;
		}
	}
	return false;
}

bool DefaultMutableTreeNode::isNodeDescendant(DefaultMutableTreeNodePtr anotherNode) const
{
	if(DefaultMutableTreeNodePtr(this) == anotherNode)
	{
		return anotherNode;
	}

	for(UInt32 i(0) ; i<getChildrenInternal().size() ; ++i)
	{
		if(DefaultMutableTreeNode::Ptr::dcast(getChildrenInternal()[i])->isNodeDescendant(anotherNode))
		{
			return true;
		}
	}

	return false;
}

bool DefaultMutableTreeNode::isNodeRelated(DefaultMutableTreeNodePtr aNode) const
{
	return getRoot() == aNode->getRoot();
}

bool DefaultMutableTreeNode::isNodeSibling(MutableTreeNodePtr anotherNode) const
{
	if(getParentInternal() != NullFC)
	{
		for(UInt32 i(0) ; i<DefaultMutableTreeNode::Ptr::dcast(getParentInternal())->getChildrenInternal().size() ; ++i)
		{
			if(DefaultMutableTreeNode::Ptr::dcast(getParentInternal())->getChildrenInternal()[i] == anotherNode)
			{
				return true;
			}
		}
	}

	return false;
}

bool DefaultMutableTreeNode::isRoot(void) const
{
	return getParent() != NullFC;
}

void DefaultMutableTreeNode::removeAllChildren(void)
{
	beginEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
		getChildrenInternal().clear();
	endEditCP(DefaultMutableTreeNodePtr(this), ChildrenInternalFieldMask);
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

void DefaultMutableTreeNode::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultMutableTreeNode::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultMutableTreeNode NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDEFAULTMUTABLETREENODEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTMUTABLETREENODEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTMUTABLETREENODEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

