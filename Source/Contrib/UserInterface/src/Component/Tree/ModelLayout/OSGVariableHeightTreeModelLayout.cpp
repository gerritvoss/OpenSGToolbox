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

#include "OSGVariableHeightTreeModelLayout.h"
#include "OSGTreeModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVariableHeightTreeModelLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGVariableHeightTreeModelLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VariableHeightTreeModelLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 VariableHeightTreeModelLayout::getHeight(void) const
{
    //TODO:Implement
    return 0.0f;
}

void VariableHeightTreeModelLayout::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const
{
    //TODO:Implement
}

bool VariableHeightTreeModelLayout::isVisible(const TreePath& path) const
{
	//TODO: Implement
	return false;
}

TreePath VariableHeightTreeModelLayout::getPathClosestTo(const Pnt2f& Loc) const
{
	//TODO:Implement
	return TreePath();
}

TreePath VariableHeightTreeModelLayout::getPathForRow(const UInt32& row) const
{
	//TODO:Implement
	return TreePath();
}

Real32 VariableHeightTreeModelLayout::getPreferredHeight(void) const
{
	//TODO: Implement
	return 0;
}

Real32 VariableHeightTreeModelLayout::getPreferredWidth(Pnt2f& TopLeft, Pnt2f& BottomRight) const
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

void VariableHeightTreeModelLayout::setModel(TreeModel* const newModel)
{
	//TODO:Implement
}


void VariableHeightTreeModelLayout::setRootVisible(bool rootVisible)
{
	//TODO:Implement
}

void VariableHeightTreeModelLayout::setRowHeight(const Real32& rowHeight)
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

void VariableHeightTreeModelLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VariableHeightTreeModelLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VariableHeightTreeModelLayout NI" << std::endl;
}

OSG_END_NAMESPACE
