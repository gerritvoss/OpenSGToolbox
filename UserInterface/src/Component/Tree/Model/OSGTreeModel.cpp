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

#include "OSGTreeModel.h"
#include "Component/Tree/OSGTreePath.h"
#include <deque>
#include <OpenSG/OSGBaseFunctions.h>

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

TreePath TreeModel::getPath(const boost::any& node) const
{
    std::deque<boost::any> PathVector;

    boost::any RecNode(node);
    while(!RecNode.empty())
    {
        PathVector.push_front(RecNode);
        RecNode = getParent(RecNode);
    }

    return TreePath(PathVector, this);
}

bool TreeModel::depthFirstLessThan(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));
    return LeftPath.depthFirstLessThan(RightPath);
}

bool TreeModel::breadthFirstLessThan(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));
    return LeftPath.breadthFirstLessThan(RightPath);
}

bool TreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));

    if(LeftPath.getPathCount() == RightPath.getPathCount())
    {
        for(UInt32 i(0) ; i<osgMin<UInt32>(LeftPath.getPathCount(), RightPath.getPathCount())-1 ; ++i)
        {
            if( getIndexOfChild(LeftPath.getPathComponent(i),LeftPath.getPathComponent(i+1))
                !=
                getIndexOfChild(RightPath.getPathComponent(i),RightPath.getPathComponent(i+1)))
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/


OSG_END_NAMESPACE

