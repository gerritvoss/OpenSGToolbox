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

#include <OpenSG/OSGConfig.h>

#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GridBagLayout
A UI GridBagLayout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GridBagLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GridBagLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    Pnt2f ParentInsetsTopLeft, ParentInsetBottomRight;
    Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(ParentInsetsTopLeft, ParentInsetBottomRight);
	
	Vec2f borderSize(ParentInsetBottomRight - ParentInsetsTopLeft);

	std::vector<Real32> widths;
	std::vector<Real32> posX;
	std::vector<Real32> heights;
	std::vector<Real32> posY;
	std::vector<Real32> columnWeights;
	std::vector<Real32> rowWeights;
	Real32 cumColumnWeights(0.0);
	Real32 cumRowWeights(0.0);

	Pnt2f offset(ParentInsetsTopLeft);
	Vec2f cellSize(0,0);
	Vec2f size(0,0);
	Real32 weight(0.0);
	UInt32 i;
	GridBagLayoutConstraintsPtr constraints;

	// check the number of weights. if there aren't enough, then it fills in
	// the blanks evenly.
	for (i = 0; i < getColumnWeights().size(); ++i)
	{
		columnWeights.push_back(getColumnWeights()[i]);
		cumColumnWeights += columnWeights[i];
	}
	for (i = 0; i < getRowWeights().size(); ++i)
	{
		rowWeights.push_back(getRowWeights()[i]);
		cumRowWeights += rowWeights[i];
	}

	// fix the weights so there are the correct number of them, and they add up to 1.0
	if (columnWeights.size() < getColumns())
	{
		if (cumColumnWeights > .95)
		{
			// first make the existing weights fill their portion of the grid
			Real32 ratio( ((Real32)columnWeights.size()/(Real32)getColumns()) / cumColumnWeights );
			for (i = 0; i < columnWeights.size(); ++i)
				columnWeights[i] *= ratio;
			// then add in equally spaced weights
			ratio = (1.0 - (Real32)columnWeights.size()/(Real32)getColumns()) / (getColumns() - columnWeights.size());
			UInt32 NumToAdd(getColumns() - columnWeights.size());
			for (i = 0; i < NumToAdd; ++i)
				columnWeights.push_back(ratio);
		}
		else
		{
			// fill in equally spaced weights
			Real32 ratio( (1.0 - cumColumnWeights) / static_cast<Real32>(getColumns() - columnWeights.size()) );
			UInt32 NumToAdd(getColumns() - columnWeights.size());
			for (i = 0; i < NumToAdd; ++i)
				columnWeights.push_back(ratio);
		}
	}
	else if (osgabs(cumColumnWeights-1.0) > 0.01)
	{
		// force the total weight to be 1.0
		Real32 ratio(1.0 / cumColumnWeights);
		for (i = 0; i < columnWeights.size(); ++i)
			columnWeights[i] *= ratio;
	}
	if (rowWeights.size() < getRows())
	{
		if (cumRowWeights > .95)
		{
			// first make the existing weights fill their portion of the grid
			Real32 ratio( ((Real32)rowWeights.size()/(Real32)getRows()) / cumRowWeights );
			for (i = 0; i < rowWeights.size(); ++i)
				rowWeights[i] *= ratio;
			// then add in equally spaced weights
			ratio = (1.0 - (Real32)rowWeights.size()/(Real32)getRows()) / (getRows() - rowWeights.size());
			UInt32 NumToAdd(getRows() - rowWeights.size());
			for (i = 0; i < NumToAdd; ++i)
				rowWeights.push_back(ratio);
		}
		else
		{
			// fill in equally spaced weights
			Real32 ratio( (1.0 - cumRowWeights) / static_cast<Real32>(getRows() - rowWeights.size()) );
			UInt32 NumToAdd(getRows() - rowWeights.size());
			for (i = 0; i < NumToAdd; ++i)
				rowWeights.push_back(ratio);
		}
	}
	else if (osgabs(cumRowWeights-1.0) > 0.01)
	{
		// force the total weight to be 1.0
		Real32 ratio(1.0 / cumRowWeights);
		for (i = 0; i < rowWeights.size(); ++i)
			rowWeights[i] *= ratio;
	}

	// set up all of the positions and sizes of the grid
	posX.push_back(0);
	for (i = 1; i < getColumns(); ++i)
	{
		weight+=columnWeights[i-1];
		Real32 Width;
		Width = osgMin(columnWeights[i-1] * borderSize.x(), borderSize.x() - posX.back());
		if(i-1<getColumnWidths().size())
		{
			Width = osgMax(Width, getColumnWidths()[i-1]);
		}
		widths.push_back(Width);
		posX.push_back(posX.back() + widths.back());
	}
	// i increments again before this statement, so it
	// still must be i-1
	widths.push_back(borderSize.x()-posX.back());

	weight = 0.0;
	posY.push_back(0);
	for (i = 1; i < getRows(); ++i)
	{
		weight+=rowWeights[i-1];
		Real32 Height;
		Height = osgMin(rowWeights[i-1] * borderSize.y(), borderSize.y() - posY.back());
		if(i-1<getRowHeights().size())
		{
			Height = osgMax(Height, getRowHeights()[i-1]);
		}
		heights.push_back(Height);
		posY.push_back(posY.back() + heights.back());
	}
	// i increments again before this statement, so it
	// still must be i-1
	heights.push_back(borderSize.y()-posY.back());

	// now go through each component and place them on the grid
	for (i = 0; i < Components.size(); ++i)
	{
		// begin by resetting offset to borderoffset and size to 0
		offset = ParentInsetsTopLeft;
		cellSize[0] = cellSize[1] = 0;
		size = Components[i]->getPreferredSize();
		constraints = GridBagLayoutConstraintsPtr::dcast(Components[i]->getConstraints());
		if(constraints != NullFC)
		{
			// find the offsets for the cell, including the padding
			if (constraints->getGridX() < posX.size())
				offset[0] += posX[constraints->getGridX()] + constraints->getPadLeft();
			if (constraints->getGridY() < posY.size())
				offset[1] += posY[constraints->getGridY()] + constraints->getPadTop();

			// find the size of cell/cells containing the component
			for (UInt16 j = 0; j < constraints->getGridWidth() && constraints->getGridX()+j < widths.size(); ++j)
				cellSize[0] += widths[constraints->getGridX()+j];
			for (UInt16 j = 0; j < constraints->getGridHeight() && constraints->getGridY()+j < heights.size(); ++j)
				cellSize[1] += heights[constraints->getGridY()+j];

			// remove the padding from the size of the cell
			cellSize[0] -= constraints->getPadRight() + constraints->getPadLeft();
			cellSize[1] -= constraints->getPadTop() + constraints->getPadBottom();

			// set the size of the component by the size of the cell/cells if it set to fill
			if ( (constraints->getFill() == GridBagLayoutConstraints::FILL_BOTH || constraints->getFill() == GridBagLayoutConstraints::FILL_HORIZONTAL) && constraints->getWeightX() > 0.0)
				size[0] = cellSize[0] * constraints->getWeightX();
			if ( (constraints->getFill() == GridBagLayoutConstraints::FILL_BOTH || constraints->getFill() == GridBagLayoutConstraints::FILL_VERTICAL) && constraints->getWeightY() > 0.0)
				size[1] = cellSize[1] * constraints->getWeightY();

			// check to see if it is bigger than the maximum size
			if (size[0] > Components[i]->getMaxSize()[0])
				size[0] = Components[i]->getMaxSize()[0];
			if (size[1] > Components[i]->getMaxSize()[1])
				size[1] = Components[i]->getMaxSize()[1];

			// check to see if it is smaller than the minimum size
			if (size[0] < Components[i]->getMinSize()[0]+constraints->getInternalPadX())
				size[0] = Components[i]->getMinSize()[0]+constraints->getInternalPadX();
			if (size[1] < Components[i]->getMinSize()[1]+constraints->getInternalPadY())
				size[1] = Components[i]->getMinSize()[1]+constraints->getInternalPadY();

			// check to see if it is too big for the cell
			if (size[0] > cellSize[0])
				size[0] = cellSize[0];
			if (size[1] > cellSize[1])
				size[1] = cellSize[1];

			// align it properly in the cell
			offset[0] += (cellSize[0] - size[0]) * constraints->getHorizontalAlignment();
			offset[1] += (cellSize[1] - size[1]) * constraints->getVerticalAlignment();
		}
		beginEditCP(Components[i], Component::SizeFieldMask|Component::PositionFieldMask);
			if (size[0] >= Components[i]->getMinSize().x() && size[1] > Components[i]->getMinSize().y())
				Components[i]->setSize(size);
			else
				Components[i]->setSize(Vec2f(0,0));
			Components[i]->setPosition(Pnt2f(offset));
		endEditCP(Components[i], Component::SizeFieldMask|Component::PositionFieldMask);
	}
}


Vec2f GridBagLayout::layoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent, SizeType TheSizeType) const
{
    Vec2f Result(0.0,0.0);

    //TODO: Implement

    assert(false && "GridBagLayout::layoutSize NOT IMPLEMENTED");

    return Result;
}

Vec2f GridBagLayout::minimumContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f GridBagLayout::requestedContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f GridBagLayout::preferredContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f GridBagLayout::maximumContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GridBagLayout::GridBagLayout(void) :
    Inherited()
{
}

GridBagLayout::GridBagLayout(const GridBagLayout &source) :
    Inherited(source)
{
}

GridBagLayout::~GridBagLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GridBagLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GridBagLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GridBagLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRIDBAGLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRIDBAGLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRIDBAGLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

