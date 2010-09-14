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

#include "OSGGridLayout.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGridLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGGridLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GridLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GridLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
	Pnt2f borderTopLeft, borderBottomRight;
	dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);

	Real32 Xpos = 0;
	Real32 Ypos = 0;
	Real32 maxSizeX = (borderSize.x()-getHorizontalGap()*(getColumns()-1)) / static_cast<Real32>(getColumns());
	Real32 maxSizeY = 0.0f;//(borderSize.y()-getVerticalGap()*getRows()) / static_cast<Real32>(getRows());
	Int32 numComp = Components->size();
	Real32 buttonXSize, buttonYSize;

	//set the size to the perfered sizes
	for(UInt16 i = 0; i<Components->size(); i++)
    {
		if ((*Components)[i] != NULL) 
		{
			if((*Components)[i]->getPreferredSize().x()>maxSizeX)
				maxSizeX = (*Components)[i]->getPreferredSize().x();
			if((*Components)[i]->getPreferredSize().y()>maxSizeY)
				maxSizeY = (*Components)[i]->getPreferredSize().y();
		}
	}
	//set the  size of the button
	for(UInt16 i = 0; i < Components->size(); i++)
    {
		if ((*Components)[i] != NULL) 
		{
			if(maxSizeX < (*Components)[i]->getMaxSize().x())
            {
				buttonXSize = maxSizeX;
            }
			else
				buttonXSize = (*Components)[i]->getMaxSize().x();
			if(maxSizeY<(*Components)[i]->getMaxSize().y())
            {
				buttonYSize = maxSizeY;
            }
			else
            {
				buttonYSize = (*Components)[i]->getMaxSize().y();
            }
            
            if((*Components)[i]->getSize() != Vec2f(buttonXSize, buttonYSize))
            {
			   (*Components)[i]->setSize(Vec2f(buttonXSize, buttonYSize));
            }
		}
	}


	//position each component
	for(UInt16 i = 0; i < osgMin(getRows(), numComp/getColumns()); i++)
    {
		if ((*Components)[i] != NULL) 
		{
            Pnt2f Pos;
			for(UInt16 j = 0; j < osgMin(getColumns(),numComp - i*getColumns()) ; j++)
            {
                Pos = borderTopLeft + Vec2f(Xpos, Ypos);
                if((*Components)[i*getColumns()+j]->getPosition() != Pos)
                {
                    (*Components)[i*getColumns()+j]->setPosition(Pos);
                }
				Xpos = Xpos + (maxSizeX+getHorizontalGap());
			}
			Xpos = 0;
			Ypos += maxSizeY+getVerticalGap();
		}
	}
}


Vec2f GridLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
{
    if(getRows() == 0 || getColumns() == 0)
    {
        return Vec2f(1.0f,1.0f);
    }

	Real32 maxSizeX = 0.0f;
	Real32 maxSizeY = 0.0f;

    Vec2f ComponentSize;
	//set the size to the perfered sizes for the buttons
	for(UInt16 i = 0; i<Components->size(); i++){
		if ((*Components)[i] != NULL) 
		{
            ComponentSize = getComponentSize((*Components)[i],TheSizeType);
			if(ComponentSize.x()>maxSizeX)
				maxSizeX = ComponentSize.x();
			if(ComponentSize.y()>maxSizeY)
				maxSizeY = ComponentSize.y();
		}
	}

    return Vec2f(maxSizeX * static_cast<Real32>(getColumns()) + getHorizontalGap() * static_cast<Real32>(getColumns()-1),
                 maxSizeY * static_cast<Real32>(getRows()) + getVerticalGap() * static_cast<Real32>(getRows()-1));
}

Vec2f GridLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f GridLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f GridLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f GridLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GridLayout::GridLayout(void) :
    Inherited()
{
}

GridLayout::GridLayout(const GridLayout &source) :
    Inherited(source)
{
}

GridLayout::~GridLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GridLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ( RowsFieldMask | 
                      ColumnsFieldMask | 
                      HorizontalGapFieldMask | 
                      VerticalGapFieldMask))
    {
        updateParentContainers();
    }
}

void GridLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GridLayout NI" << std::endl;
}

OSG_END_NAMESPACE
