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

#include "OSGModelTreeNode.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ModelTreeNode
A UI Tree Node. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ModelTreeNode::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::vector<ModelTreeNodePtr> ModelTreeNode::getChildren(void) const
{
    std::vector<ModelTreeNodePtr> Result;
    for(UInt32 i(0) ; i<getChildCount() ; ++i)
    {
        Result.push_back(getChildAt(i));
    }

    return Result;
}

ModelTreeNodePtr ModelTreeNode::getNodeFromUserObject(SharedFieldPtr object)
{
    if(object == getUserObject())
    {
        return ModelTreeNodePtr(this);
    }
    else
    {
        ModelTreeNodePtr Node;
        for(UInt32 i(0) ; i<getChildCount() ; ++i)
        {
            Node = getChildAt(i)->getNodeFromUserObject(object);
            if(Node != NullFC)
            {
                return Node;
            }
        }
        return NullFC;
    }
}

TreePath ModelTreeNode::getPath(void) const
{
    std::vector<SharedFieldPtr> Path;

    ModelTreeNodePtr Node(this);
    while(Node != NullFC)
    {
        Path.push_back(Node->getUserObject());
        Node = Node->getParent();
    }

	std::reverse(Path.begin(), Path.end());
    return TreePath(Path);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ModelTreeNode::ModelTreeNode(void) :
    Inherited()
{
}

ModelTreeNode::ModelTreeNode(const ModelTreeNode &source) :
    Inherited(source)
{
}

ModelTreeNode::~ModelTreeNode(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ModelTreeNode::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ModelTreeNode::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ModelTreeNode NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMODELTREENODEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMODELTREENODEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMODELTREENODEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

