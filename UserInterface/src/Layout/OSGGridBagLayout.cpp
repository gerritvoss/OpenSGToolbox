/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
	Pnt2s borderOffset;
	Vec2s borderSize;
	ParentComponent->getInsideBorderBounds(borderOffset, borderSize);
	borderSize -= borderOffset;

	std::vector<UInt16> widths;
	std::vector<UInt16> posX;
	std::vector<UInt16> heights;
	std::vector<UInt16> posY;

	Pnt2s offset(borderOffset);
	Vec2s size(0,0);
	Real32 weight(0.0);
	UInt32 i;
	GridBagLayoutConstraintsPtr constraints;

	// check to make sure there are enough ColumnHeights and RowWidths
	/*while (getColumnHeights().size() < getColumns())
		getColumnHeights().addValue(0);
	while (getRowWidths().size() < getRows())
		getRowWidths().addValue(0);*/

	// set up all of the positions and sizes of the grid
	posX.push_back(0);
	for (i = 1; i < getColumns(); ++i)
	{
		weight+=getColumnWeights().getValue(i-1);
		posX.push_back((UInt16)(weight*borderSize[0]));
		widths.push_back(posX[i]-posX[i-1]);
		//getRowWidths().setValue(posX[i]-posX[i-1], i-1);
	}
	// i increments again before this statement, so it
	// still must be i-1
	widths.push_back(borderSize[0]-posX[i-1]);

	weight = 0.0;
	posY.push_back(0);
	for (i = 1; i < getRows(); ++i)
	{
		weight+=getRowWeights().getValue(i-1);
		posY.push_back((UInt16)(weight*borderSize[1]));
		heights.push_back(posY[i]-posY[i-1]);
		//getColumnHeights.setValue(posY[i]-posY[i-1], i-1);
	}
	heights.push_back(borderSize[1]-posY[i-1]);

	// now go through each component and place them on the grid
	for (i = 0; i < Components.size(); ++i)
	{
		// begin by resetting offset to borderoffset and size to 0
		offset = borderOffset;
		size[0] = size[1] = 0;
		constraints = GridBagLayoutConstraintsPtr::dcast(Components.getValue(i)->getConstraints());
		if(constraints != NullFC)
		{
			if (constraints->getGridX() < posX.size())
				offset[0] += posX[constraints->getGridX()];

			if (constraints->getGridY() < posY.size())
				offset[1] += posY[constraints->getGridY()];

			for (UInt16 j = 0; j < constraints->getGridWidth() && constraints->getGridX()+j < widths.size(); ++j)
				size[0] += widths[constraints->getGridX()+j];
			
			for (UInt16 j = 0; j < constraints->getGridHeight() && constraints->getGridY()+j < heights.size(); ++j)
				size[1] += heights[constraints->getGridY()+j];
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

