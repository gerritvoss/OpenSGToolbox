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
#include "Util/OSGUIDefines.h"

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
    Pnt2s ParentInsetsTopLeft, ParentInsetBottomRight;
    Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(ParentInsetsTopLeft, ParentInsetBottomRight);
	
	Vec2s borderSize(ParentInsetBottomRight - ParentInsetsTopLeft);

	std::vector<UInt16> widths;
	std::vector<UInt16> posX;
	std::vector<UInt16> heights;
	std::vector<UInt16> posY;
	std::vector<Real32> columnWeights;
	std::vector<Real32> rowWeights;
	Real32 cumColumnWeights(0.0);
	Real32 cumRowWeights(0.0);

	Pnt2s offset(ParentInsetsTopLeft);
	Vec2s cellSize(0,0);
	Vec2s size(0,0);
	Real32 weight(0.0);
	UInt32 i;
	GridBagLayoutConstraintsPtr constraints;

	// check the number of weights. if there aren't enough, then it fills in
	// the blanks evenly.
	for (i = 0; i < getColumnWeights().size(); ++i)
	{
		columnWeights.push_back(getColumnWeights().getValue(i));
		cumColumnWeights += columnWeights[i];
	}
	for (i = 0; i < getRowWeights().size(); ++i)
	{
		rowWeights.push_back(getRowWeights().getValue(i));
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
			for (i = 0; i < getColumns() - columnWeights.size(); ++i)
				columnWeights.push_back(ratio);
		}
		else
		{
			// fill in equally spaced weights
			Real32 ratio( (1.0 - cumColumnWeights) / (getColumns() - columnWeights.size()) );
			for (i = 0; i < getColumns() - columnWeights.size(); ++i)
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
			for (i = 0; i < getRows() - rowWeights.size(); ++i)
				rowWeights.push_back(ratio);
		}
		else
		{
			// fill in equally spaced weights
			Real32 ratio( (1.0 - cumRowWeights) / (getRows() - rowWeights.size()) );
			for (i = 0; i < getRows() - rowWeights.size(); ++i)
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
		posX.push_back((UInt16)(weight*borderSize[0]));
		widths.push_back(posX[i]-posX[i-1]);
	}
	// i increments again before this statement, so it
	// still must be i-1
	widths.push_back(borderSize[0]-posX[i-1]);

	weight = 0.0;
	posY.push_back(0);
	for (i = 1; i < getRows(); ++i)
	{
		weight+=rowWeights[i-1];
		posY.push_back((UInt16)(weight*borderSize[1]));
		heights.push_back(posY[i]-posY[i-1]);
	}
	heights.push_back(borderSize[1]-posY[i-1]);

	// now go through each component and place them on the grid
	for (i = 0; i < Components.size(); ++i)
	{
		// begin by resetting offset to borderoffset and size to 0
		offset = ParentInsetsTopLeft;
		cellSize[0] = cellSize[1] = 0;
		size = Components.getValue(i)->getPreferredSize();
		constraints = GridBagLayoutConstraintsPtr::dcast(Components.getValue(i)->getConstraints());
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
			if ( (constraints->getFill() == FILL_BOTH || constraints->getFill() == FILL_HORIZONTAL) && constraints->getWeightX() > 0.0)
				size[0] = cellSize[0] * constraints->getWeightX();
			if ( (constraints->getFill() == FILL_BOTH || constraints->getFill() == FILL_VERTICAL) && constraints->getWeightY() > 0.0)
				size[1] = cellSize[1] * constraints->getWeightY();

			// check to see if it is bigger than the maximum size
			if (size[0] > Components.getValue(i)->getMaxSize()[0])
				size[0] = Components.getValue(i)->getMaxSize()[0];
			if (size[1] > Components.getValue(i)->getMaxSize()[1])
				size[1] = Components.getValue(i)->getMaxSize()[1];

			// check to see if it is smaller than the minimum size
			if (size[0] < Components.getValue(i)->getMinSize()[0]+constraints->getInternalPadX())
				size[0] = Components.getValue(i)->getMinSize()[0]+constraints->getInternalPadX();
			if (size[1] < Components.getValue(i)->getMinSize()[1]+constraints->getInternalPadY())
				size[1] = Components.getValue(i)->getMinSize()[1]+constraints->getInternalPadY();

			// check to see if it is too big for the cell
			if (size[0] > cellSize[0])
				size[0] = cellSize[0];
			if (size[1] > cellSize[1])
				size[1] = cellSize[1];

			// align it properly in the cell
			offset[0] += (cellSize[0] - size[0]) * constraints->getHorizontalAlignment();
			offset[1] += (cellSize[1] - size[1]) * constraints->getVerticalAlignment();
		}
		beginEditCP(Components.getValue(i), Component::SizeFieldMask|Component::PositionFieldMask);
			if (size[0] >= Components.getValue(i)->getMinSize().x() && size[1] > Components.getValue(i)->getMinSize().y())
				Components.getValue(i)->setSize(size);
			else
				Components.getValue(i)->setSize(Vec2s(0,0));
			Components.getValue(i)->setPosition(Pnt2s(offset));
		endEditCP(Components.getValue(i), Component::SizeFieldMask|Component::PositionFieldMask);
	}
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

