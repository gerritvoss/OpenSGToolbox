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

#include "OSGFixedHeightTreeModelLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FixedHeightTreeModelLayout
A UI Fixed Height Tree Model Layout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FixedHeightTreeModelLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FixedHeightTreeModelLayout::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const
{
	//TODO:Implement
}

bool FixedHeightTreeModelLayout::isVisible(const TreePath& path) const
{
    return _VisiblePathSet.find(path) != _VisiblePathSet.end();
}

TreePath FixedHeightTreeModelLayout::getPathClosestTo(const UInt32& x, const UInt32& y) const
{
    //Determine the row
    UInt32 Row(osgMin<UInt32>(y/getRowHeight(),getRowCount()-1));

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
        return TreePath(SharedFieldPtr());
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
    if(isVisible(path))
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
    if(Expand)
    {
		_VetoPathExpantion = false;

		if(!isExpanded(path))
		{
			produceTreeWillExpand(path);
			if(!_VetoPathExpantion)
			{
				_ExpandedPathSet.insert(path);

                if(isVisible(path) || TreePath(_TreeModel->getRoot()) == path)
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
		        
				if(isVisible(path) || TreePath(_TreeModel->getRoot()) == path)
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

void FixedHeightTreeModelLayout::setModel(TreeModelPtr newModel)
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

void FixedHeightTreeModelLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FixedHeightTreeModelLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FixedHeightTreeModelLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFIXEDHEIGHTTREEMODELLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFIXEDHEIGHTTREEMODELLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFIXEDHEIGHTTREEMODELLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

