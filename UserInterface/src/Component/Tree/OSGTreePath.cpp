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

#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TreePath
A TreePath. 
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

bool TreePath::isDescendant(TreePath aTreePath) const
{
    UInt32 i(0);
    while(i<aTreePath._Path.size() && aTreePath._Path[i]._NodeIndex != _Path.front()._NodeIndex )
    {
         ++i;
    }

    if(i<aTreePath._Path.size() && _Path.size() <= aTreePath._Path.size() - i)
    {
        for(UInt32 j(0) ; j<_Path.size() ; ++j)
        {
             if(_Path[j]._NodeIndex != aTreePath._Path[i+j]._NodeIndex)
             {
                 return false;
             }
        }
        return true;
    }
    else
    {
	   return false;
    }
}

TreePath TreePath::pathByAddingChild(const boost::any& child, UInt32 childIndex) const
{
	PathVectorType Path(_Path);
	Path.push_back(NodePairType(child,childIndex));
	return TreePath(Path);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreePath::TreePath(const boost::any& singlePath, UInt32 childIndex)
{
	_Path.push_back(NodePairType(singlePath,childIndex));
}

TreePath::TreePath(const PathVectorType& path) :
    _Path(path)
{
}

TreePath::TreePath(void)
{
}
TreePath::TreePath(const PathVectorType& path, const UInt32& length)
{
    if(path.size() > 0)
    {
        _Path = path;
		if(_Path.size() > length)
		{
			_Path.resize(length);
		}
    }
}
/*----------------------------- class specific ----------------------------*/

bool TreePath::operator==(const TreePath& Right) const
{
    if(_Path.size() == Right._Path.size())
    {
        for(UInt32 i(0) ; i<_Path.size() ; ++i)
        {
             if(_Path[i]._NodeIndex != Right._Path[i]._NodeIndex)
             {
                 return false;
             }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool TreePath::operator<(const TreePath& RightPath) const
{
    if(_Path.size() != RightPath._Path.size())
    {
        return _Path.size() < RightPath._Path.size();
    }
    else if(_Path.size() == 0)
    {
        return false;
    }
    else
    {
        for(UInt32 i(0) ; i<_Path.size() ; ++i)
        {
            return _Path[i]._NodeIndex < RightPath._Path[i]._NodeIndex;
        }
        return false;
    }
}

TreePath TreePath::getHighestDepthAncestor(const TreePath& aTreePath) const
{
    UInt32 Depth(1);
    
    while( Depth < getDepth() &&
           Depth < aTreePath.getDepth() &&
           TreePath(_Path, Depth) == TreePath(aTreePath._Path, Depth) )
    {
        ++Depth;
    }

    if(Depth > 0)
    {
        return TreePath(_Path, Depth-1);
    }
    else
    {
        return TreePath();
    }
}
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

