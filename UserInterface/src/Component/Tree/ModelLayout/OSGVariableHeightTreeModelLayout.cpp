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

#include "OSGVariableHeightTreeModelLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VariableHeightTreeModelLayout
A UI Variable Height Tree Model Layout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VariableHeightTreeModelLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void VariableHeightTreeModelLayout::getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight, TreePath path, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn) const
{
	//TODO:Implement
}

bool VariableHeightTreeModelLayout::isVisible(const TreePath& path) const const
{
	//TODO: Implement
	return false;
}

TreePath VariableHeightTreeModelLayout::getPathClosestTo(const UInt32& x, const UInt32& y) const
{
	//TODO:Implement
	return TreePath(SharedFieldPtr());
}

TreePath VariableHeightTreeModelLayout::getPathForRow(const UInt32& row) const
{
	//TODO:Implement
	return TreePath(SharedFieldPtr());
}

UInt32 VariableHeightTreeModelLayout::getPreferredHeight(void) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeModelLayout::getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeModelLayout::getRowCount(void) const
{
	//TODO: Implement
	return 0;
}

Int32 VariableHeightTreeModelLayout::getRowForPath(const TreePath& path) const
{
	//TODO: Implement
	return 0;
}

UInt32 VariableHeightTreeModelLayout::getVisibleChildCount(const TreePath& path) const
{
	//TODO: Implement
	return 0;
}


void VariableHeightTreeModelLayout::invalidatePathBounds(const TreePath& path)
{
	//TODO:Implement
}

void VariableHeightTreeModelLayout::invalidateSizes(void)
{
	//TODO:Implement
}

bool VariableHeightTreeModelLayout::isExpanded(const TreePath& path) const
{
	//TODO: Implement
	return false;
}

void VariableHeightTreeModelLayout::setExpanded(const TreePath& path, bool Expand)
{
	//TODO:Implement
}

void VariableHeightTreeModelLayout::setModel(TreeModelPtr newModel)
{
	//TODO:Implement
}


void VariableHeightTreeModelLayout::setRootVisible(bool rootVisible)
{
	//TODO:Implement
}

void VariableHeightTreeModelLayout::setRowHeight(const UInt32& rowHeight)
{
	//TODO:Implement
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VariableHeightTreeModelLayout::VariableHeightTreeModelLayout(void) :
    Inherited()
{
}

VariableHeightTreeModelLayout::VariableHeightTreeModelLayout(const VariableHeightTreeModelLayout &source) :
    Inherited(source)
{
}

VariableHeightTreeModelLayout::~VariableHeightTreeModelLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VariableHeightTreeModelLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void VariableHeightTreeModelLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump VariableHeightTreeModelLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGVARIABLEHEIGHTTREEMODELLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGVARIABLEHEIGHTTREEMODELLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGVARIABLEHEIGHTTREEMODELLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

