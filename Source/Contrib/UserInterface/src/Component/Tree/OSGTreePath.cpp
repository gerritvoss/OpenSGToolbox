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

#include "OSGConfig.h"

#include "OSGTreePath.h"
#include "OSGBaseFunctions.h"
#include "OSGTreeModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TreePath
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
bool TreePath::empty(void) const
{
    return (_Model == NULL || _Path.size() == 0);
}

TreePath::TreePath(const TreePath& p) :
  _Path(p._Path), _Model(p._Model)
{
}

TreePath::TreePath(const PathVectorType& path, TreeModel * const theModel) :
  _Path(path), _Model(theModel)
{
}

TreePath::TreePath(const TreePath& p, boost::any child) :
    _Path(p._Path),
    _Model(p._Model)
{
    _Path.push_back(child);
}

TreePath::TreePath(boost::any value, TreeModel * const theModel) :
    _Path(1, value),
    _Model(theModel)
{
}


TreePath::TreePath(const std::deque<boost::any>& path, TreeModel * const theModel) :
  _Path(path.begin(), path.end()), _Model(theModel)
{
}

TreePath::TreePath(const TreePath& p, UInt32 len) : _Model(p._Model)
{
    if(len <= p._Path.size())
    {
        _Path.insert(_Path.begin(), p._Path.begin(), p._Path.begin() + len);
    }
}

TreePath::TreePath(void) :
  _Path(), _Model(NULL)
{
}

bool TreePath::depthFirstLessThan(const TreePath& Right) const
{
    if(_Model != Right._Model)
    {
        return false;
    }
    UInt32 LeftChildIndex,RightChildIndex;
    for(UInt32 i(0) ; i<osgMin<UInt32>(getPathCount(), Right.getPathCount())-1 ; ++i)
    {
        LeftChildIndex = _Model->getIndexOfChild(getPathComponent(i),getPathComponent(i+1));
        RightChildIndex = _Model->getIndexOfChild(Right.getPathComponent(i),Right.getPathComponent(i+1));
        if(LeftChildIndex != RightChildIndex)
        {
            return LeftChildIndex < RightChildIndex;
        }
    }

    return getDepth() > Right.getDepth();
}

bool TreePath::breadthFirstLessThan(const TreePath& Right) const
{
    if(_Model != Right._Model)
    {
        return false;
    }
    UInt32 LeftChildIndex,RightChildIndex;
    for(Int32 i(0) ; i<osgMin<Int32>(getPathCount(), Right.getPathCount())-1 ; ++i)
    {
        LeftChildIndex = _Model->getIndexOfChild(getPathComponent(i),getPathComponent(i+1));
        RightChildIndex = _Model->getIndexOfChild(Right.getPathComponent(i),Right.getPathComponent(i+1));
        if(LeftChildIndex != RightChildIndex)
        {
            return LeftChildIndex < RightChildIndex;
        }
    }

    return getDepth() < Right.getDepth();
}

bool TreePath::isDescendant(const TreePath& aTreePath) const
{
    if(_Model == aTreePath._Model &&
        getPathCount() < aTreePath.getPathCount())
    {
        for(UInt32 i(0) ; i<getPathCount()-1 ; ++i)
        {
            if( _Model->getIndexOfChild(getPathComponent(i),getPathComponent(i+1))
                !=
                _Model->getIndexOfChild(aTreePath.getPathComponent(i),aTreePath.getPathComponent(i+1)))
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

bool TreePath::operator==(const TreePath& Right) const
{
    if(_Model != Right._Model)
    {
        return false;
    }

    if(getPathCount() == Right.getPathCount())
    {
        for(UInt32 i(0) ; i<osgMin<UInt32>(getPathCount(), Right.getPathCount())-1 ; ++i)
        {
            if( _Model->getIndexOfChild(getPathComponent(i),getPathComponent(i+1))
                !=
                _Model->getIndexOfChild(Right.getPathComponent(i),Right.getPathComponent(i+1)))
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

TreePath TreePath::getHighestDepthAncestor(const TreePath& aTreePath) const
{
    if(_Model == aTreePath._Model &&
       !empty() && !aTreePath.empty())
    {
        UInt32 i(0);
        for( ; i<osgMin<UInt32>(getPathCount(),aTreePath.getPathCount())-1 ; ++i)
        {
            if( _Model->getIndexOfChild(getPathComponent(i),getPathComponent(i+1))
                !=
                _Model->getIndexOfChild(aTreePath.getPathComponent(i),aTreePath.getPathComponent(i+1)))
            {
                break;
            }
        }
        return TreePath(*this, i);
    }
    else
    {
        return TreePath();
    }
}

TreePath TreePath::getChildPath(UInt32 index) const
{
    if(_Model != NULL &&
       _Path.size() != 0)
    {
        boost::any child(_Model->getChild(_Path.back(),index));
        if(!child.empty())
        {
            return TreePath(*this, child);
        }
    }
    return TreePath();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

