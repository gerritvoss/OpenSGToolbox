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

#include "OSGFixedHeightTreeModelLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFixedHeightTreeModelLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGFixedHeightTreeModelLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FixedHeightTreeModelLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FixedHeightTreeModelLayout::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const
{
	//TODO:Implement
}

Real32 FixedHeightTreeModelLayout::getHeight(void) const
{
    return getRowHeight()*getRowCount();
}

bool FixedHeightTreeModelLayout::isVisible(const TreePath& path) const
{
    return _VisiblePathSet.find(path) != _VisiblePathSet.end();
}

TreePath FixedHeightTreeModelLayout::getPathClosestTo(const Pnt2f& Loc) const
{
    //Determine the row
    UInt32 Row(osgMin<UInt32>(Loc.y()/getRowHeight(),getRowCount()-1));

    //Get the Path for that row
	return getPathForRow(Row);
}

TreePath FixedHeightTreeModelLayout::getPathForRow(const UInt32& row) const
{
    //UInt32 RootVisibilityDependantRow(row);
    //if(!isRootVisible())
    //{
    //    RootVisibilityDependantRow += 1;
    //}

    UInt32 i(0);
    TreePathSetConstItor VisiblePathSetItor(_VisiblePathSet.begin());
    while(i<row && VisiblePathSetItor != _VisiblePathSet.end())
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
        return TreePath();
    }

}

UInt32 FixedHeightTreeModelLayout::getRowCount(void) const
{
    return _VisiblePathSet.size();
}

Int32 FixedHeightTreeModelLayout::getRowForPath(const TreePath& path) const
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

UInt32 FixedHeightTreeModelLayout::getVisibleChildCount(const TreePath& path) const
{
    if(isVisible(path) ||
       (path.getPathCount() == 1 && isExpanded(path)))
    {
        return _TreeModel->getChildCount(path.getLastPathComponent());
    }
    else
    {
        return 0;
    }
}

void FixedHeightTreeModelLayout::invalidatePathBounds(const TreePath& path)
{
	//TODO:Implement
}

void FixedHeightTreeModelLayout::invalidateSizes(void)
{
	//TODO:Implement
}

bool FixedHeightTreeModelLayout::isExpanded(const TreePath& path) const
{
	return _ExpandedPathSet.find(path) != _ExpandedPathSet.end();
}

void FixedHeightTreeModelLayout::setExpanded(const TreePath& path, bool Expand)
{
    if(!_TreeModel->isLeaf(path.getLastPathComponent()))
    {
        if(Expand)
        {
            _VetoPathExpantion = false;

            if(!isExpanded(path))
            {
                produceTreeWillExpand(path);
                if(!_VetoPathExpantion)
                {
                    _ExpandedPathSet.insert(path);

                    if(isVisible(path) || (_TreeModel->getRootPath() == path))
                    {
                        //Insert all visible decendents of Path
                        std::vector<TreePath> VisibleDecendants;
                        getVisibleDecendants(path, VisibleDecendants);
                        for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
                        {
                            _VisiblePathSet.insert(VisibleDecendants[i]);
                        }
                    }
                    produceTreeExpanded(path);
                }
            }
        }
        else
        {
            _VetoPathCollapse = false;
            if(isExpanded(path))
            {
                produceTreeWillCollapse(path);
                if(!_VetoPathCollapse)
                {
                    _ExpandedPathSet.erase(path);

                    if(isVisible(path) || _TreeModel->getRootPath() == path)
                    {
                        //Remove all visible decendents of Path
                        std::vector<TreePath> VisibleDecendants;
                        getVisibleDecendants(path, VisibleDecendants);
                        for(UInt32 i(0) ; i<VisibleDecendants.size() ; ++i)
                        {
                            _VisiblePathSet.erase(VisibleDecendants[i]);
                        }
                    }
                    produceTreeCollapsed(path);
                }
            }
        }
    }
}

void FixedHeightTreeModelLayout::setModel(TreeModel* const newModel)
{
	//TODO:Implement
    AbstractTreeModelLayout::setModel(newModel);
}

void FixedHeightTreeModelLayout::setRootVisible(bool rootVisible)
{
	//TODO:Implement
    AbstractTreeModelLayout::setRootVisible(rootVisible);
}

void FixedHeightTreeModelLayout::setRowHeight(const UInt32& rowHeight)
{
	//TODO:Implement
    AbstractTreeModelLayout::setRowHeight(rowHeight);

    invalidateSizes();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FixedHeightTreeModelLayout::FixedHeightTreeModelLayout(void) :
    Inherited()
{
}

FixedHeightTreeModelLayout::FixedHeightTreeModelLayout(const FixedHeightTreeModelLayout &source) :
    Inherited(source)
{
}

FixedHeightTreeModelLayout::~FixedHeightTreeModelLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FixedHeightTreeModelLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FixedHeightTreeModelLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FixedHeightTreeModelLayout NI" << std::endl;
}

OSG_END_NAMESPACE
