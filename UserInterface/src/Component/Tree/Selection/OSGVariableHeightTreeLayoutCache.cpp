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

#include "OSGVariableHeightTreeLayoutCache.h"
#include "OSGTreeSelectionListener.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VariableHeightTreeLayoutCache
A VariableHeightTreeLayoutCache. 
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

void VariableHeightTreeLayoutCache::getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight, TreePath path, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn) const
{
	//TODO:Implement
}

bool VariableHeightTreeLayoutCache::getExpandedState(TreePath path) const const
{
	//TODO: Implement
	return false;
}

TreePath VariableHeightTreeLayoutCache::getPathClosestTo(const UInt32& x, const UInt32& y) const
{
	//TODO:Implement
	return TreePath(SharedFieldPtr());
}

TreePath VariableHeightTreeLayoutCache::getPathForRow(const UInt32& row) const
{
	//TODO:Implement
	return TreePath(SharedFieldPtr());
}

UInt32 VariableHeightTreeLayoutCache::getPreferredHeight(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeLayoutCache::getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeLayoutCache::getRowCount(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeLayoutCache::getRowForPath(TreePath path) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeLayoutCache::getVisibleChildCount(TreePath path) const
{
	//TODO: Implement
	return 0;
}


void VariableHeightTreeLayoutCache::invalidatePathBounds(TreePath path)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::invalidateSizes(void)
{
	//TODO:Implement
}

bool VariableHeightTreeLayoutCache::isExpanded(TreePath path) const
{
	//TODO: Implement
	return false;
}

void VariableHeightTreeLayoutCache::setExpandedState(TreePath path, bool isExpanded)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::setModel(TreeModelPtr newModel)
{
	//TODO:Implement
}


void VariableHeightTreeLayoutCache::setRootVisible(bool rootVisible)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::setRowHeight(const UInt32& rowHeight)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::treeNodesChanged(TreeModelEvent e)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::treeNodesInserted(TreeModelEvent e)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::treeNodesRemoved(TreeModelEvent e)
{
	//TODO:Implement
}

void VariableHeightTreeLayoutCache::treeStructureChanged(TreeModelEvent e)
{
	//TODO:Implement
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

