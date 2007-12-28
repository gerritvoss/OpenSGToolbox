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

#include "OSGFixedHeightTreeLayoutCache.h"
#include "Component/Tree/Selection/OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FixedHeightTreeLayoutCache
A FixedHeightTreeLayoutCache. 
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

void FixedHeightTreeLayoutCache::getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight, TreePath path, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn) const
{
	//TODO:Implement
}

bool FixedHeightTreeLayoutCache::isVisible(const TreePath& path) const
{
    return _VisiblePathSet.find(path) != _VisiblePathSet.end();
}

TreePath FixedHeightTreeLayoutCache::getPathClosestTo(const UInt32& x, const UInt32& y) const
{
    //Determine the row
    UInt32 Row(y/getRowHeight());

    //Get the Path for that row
	return getPathForRow(Row);
}

TreePath FixedHeightTreeLayoutCache::getPathForRow(const UInt32& row) const
{
    UInt32 RootVisibilityDependantRow(row);
    if(!isRootVisible())
    {
        RootVisibilityDependantRow += 1;
    }

    UInt32 i(0);
    TreePathSetConstItor VisiblePathSetItor(_VisiblePathSet.begin());
    while(i<RootVisibilityDependantRow && VisiblePathSetItor != _VisiblePathSet.end())
    {
        ++i;
        ++VisiblePathSetItor;
    }
    if(VisiblePathSetItor != _VisiblePathSet.end())
    {
        return (*VisiblePathSetItor);
    }
    else
    {
        return TreePath(SharedFieldPtr());
    }

}

UInt32 FixedHeightTreeLayoutCache::getRowCount(void) const
{
    if(isRootVisible())
    {
        return _VisiblePathSet.size();
    }
    else
    {
        return _VisiblePathSet.size()-1;
    }
}

Int32 FixedHeightTreeLayoutCache::getRowForPath(const TreePath& path) const
{
    UInt32 i(0);
    TreePathSetConstItor VisiblePathSetItor(_VisiblePathSet.begin());
    while( VisiblePathSetItor != _VisiblePathSet.end() && path != (*VisiblePathSetItor))
    {
        ++i;
        ++VisiblePathSetItor;
    }

    if(VisiblePathSetItor != _VisiblePathSet.end())
    {
        return i;
    }
    else
    {
        return -1;
    }
}

UInt32 FixedHeightTreeLayoutCache::getVisibleChildCount(const TreePath& path) const
{
    if(isVisible(path))
    {
        return _TreeModel->getChildCount(path.getLastPathComponent());
    }
    else
    {
        return 0;
    }
}

void FixedHeightTreeLayoutCache::invalidatePathBounds(const TreePath& path)
{
	//TODO:Implement
}

void FixedHeightTreeLayoutCache::invalidateSizes(void)
{
	//TODO:Implement
}

bool FixedHeightTreeLayoutCache::isExpanded(const TreePath& path) const
{
	return _ExpandedPathSet.find(path) != _ExpandedPathSet.end();
}

void FixedHeightTreeLayoutCache::setExpanded(const TreePath& path, bool isExpanded)
{
    if(isExpanded)
    {
        _ExpandedPathSet.insert(path);

        if(isVisible(path))
        {
            //Insert all visible decendents of Path
            std::vector<TreePath> VisibleDecendants;
            getVisibleDecendants(path, VisibleDecendants);
            for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
            {
                _VisiblePathSet.insert(VisibleDecendants[i]);
            }
        }
    }
    else
    {
        _ExpandedPathSet.erase(path);
        
        if(isVisible(path))
        {
            //Remove all visible decendents of Path
            std::vector<TreePath> VisibleDecendants;
            getVisibleDecendants(path, VisibleDecendants);
            for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
            {
                _VisiblePathSet.erase(VisibleDecendants[i]);
            }
        }
    }
}

void FixedHeightTreeLayoutCache::getVisibleDecendants(const TreePath& Path, std::vector<TreePath>& VisibleDecendants) const
{
    //Loop through all of the Children of the last node in Path
    UInt32 NumChildren(_TreeModel->getChildCount(Path.getLastPathComponent()));
    SharedFieldPtr Child;

    for(UInt32 i(0) ; i<NumChildren ; ++i)
    {
        Child = _TreeModel->getChild(Path.getLastPathComponent(), i);

        //Add This child to the Visible Decendants
        VisibleDecendants.push_back(Path.pathByAddingChild(Child));

        //If this child is expanded then add all of it's visible decendants
        if(isExpanded(Path.pathByAddingChild(Child)))
        {
            getVisibleDecendants(Path.pathByAddingChild(Child), VisibleDecendants);
        }
    }
}

void FixedHeightTreeLayoutCache::setModel(TreeModelPtr newModel)
{
	//TODO:Implement
    AbstractTreeLayoutCache::setModel(newModel);
}

void FixedHeightTreeLayoutCache::setRootVisible(bool rootVisible)
{
	//TODO:Implement
    AbstractTreeLayoutCache::setRootVisible(rootVisible);
}

void FixedHeightTreeLayoutCache::setRowHeight(const UInt32& rowHeight)
{
	//TODO:Implement
    AbstractTreeLayoutCache::setRowHeight(rowHeight);

    invalidateSizes();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

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

