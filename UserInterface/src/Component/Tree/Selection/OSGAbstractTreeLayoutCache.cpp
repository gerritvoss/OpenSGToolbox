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

#include "OSGAbstractTreeLayoutCache.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTreeLayoutCache
A AbstractTreeLayoutCache. 
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

std::vector<UInt32> AbstractTreeLayoutCache::getRowsForPaths(std::vector<TreePath> paths) const
{
	std::vector<UInt32> Result;
	for(UInt32 i(0) ; i<paths.size() ; ++i)
	{
		Result.push_back(this->getRowForPath(paths[i]));
	}
	return Result;
}

TreeModelPtr AbstractTreeLayoutCache::getModel(void) const
{
	return _TreeModel;
}

//AbstractLayoutCache.NodeDimensions AbstractTreeLayoutCache::getNodeDimensions(void) const;

UInt32 AbstractTreeLayoutCache::getPreferredHeight(void) const
{
	if(isFixedRowHeight())
	{
		return getRowHeight() * getRowCount();
	}
	else
	{
		//TODO: Implement
		return 0;
	}
}

UInt32 AbstractTreeLayoutCache::getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
	//TODO: Implement
	return 0;
}

UInt32 AbstractTreeLayoutCache::getRowHeight(void) const
{
	return _RowHeight;
}

TreeSelectionModelPtr AbstractTreeLayoutCache::getSelectionModel(void) const
{
	return _TreeSelectionModel;
}

bool AbstractTreeLayoutCache::isFixedRowHeight(void) const
{
	return _RowHeight > 0;
}

bool AbstractTreeLayoutCache::isRootVisible(void) const
{
	return _RootVisible;
}

void AbstractTreeLayoutCache::setModel(TreeModelPtr newModel)
{
    _TreeModel = newModel;
}

//void AbstractTreeLayoutCache::setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

void AbstractTreeLayoutCache::setRootVisible(bool rootVisible)
{
	_RootVisible = rootVisible;
}

void AbstractTreeLayoutCache::setRowHeight(const UInt32& rowHeight)
{
	_RowHeight = rowHeight;
}

void AbstractTreeLayoutCache::setSelectionModel(TreeSelectionModelPtr newLSM)
{
	_TreeSelectionModel = newLSM;
}

void AbstractTreeLayoutCache::getNodeDimensions(Pnt2s& TopLeft, Pnt2s& BottomRight, SharedFieldPtr value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn)
{
	//TODO: Implement
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

