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

#include "OSGBorderLayout.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBorderLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGBorderLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BorderLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BorderLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
	Pnt2f borderTopLeft, borderBottomRight;
	dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);

	Real32 NorthHeight(0);
	Real32 SouthHeight(0);
	Real32 WestWidth(0);
	Real32 EastWidth(0);
	Vec2f size;
	Vec2f offset;

	// the first pass through gets some crucial dimensions to determine
	// the sizes of the buttons
	for(UInt32 i = 0 ; i<Components->size(); ++i)
    {
		if((*Components)[i]->getConstraints() != NULL)
		{
			switch (dynamic_cast<BorderLayoutConstraints*>((*Components)[i]->getConstraints())->getRegion()) {
				// don't need to do anything with the center quite yet
				case BorderLayoutConstraints::BORDER_NORTH:
					NorthHeight = (*Components)[i]->getPreferredSize().y();
					break;
				case BorderLayoutConstraints::BORDER_EAST:
					EastWidth = (*Components)[i]->getPreferredSize().x();
					break;
				case BorderLayoutConstraints::BORDER_SOUTH:
					SouthHeight = (*Components)[i]->getPreferredSize().y();
					break;
				case BorderLayoutConstraints::BORDER_WEST:
					WestWidth = (*Components)[i]->getPreferredSize().x();
					break;
				default:
					break; 
			}
		}
	}
    Pnt2f Pos;
	// this second pass sets its size and draws them
	for(UInt32 i = 0 ; i<Components->size(); ++i)
    {
		// Find its region and draw it accordingly
		if((*Components)[i]->getConstraints() != NULL)
		{
			switch (dynamic_cast<BorderLayoutConstraints*>((*Components)[i]->getConstraints())->getRegion()) {
				case BorderLayoutConstraints::BORDER_CENTER: 
					// set up the size of the button and its extra displacement
					if ((*Components)[i]->getMaxSize().x() < borderSize.x()-(WestWidth+EastWidth))
					{
						size[0] = (*Components)[i]->getMaxSize().x();
						offset[0] = (borderSize.x()-(WestWidth+EastWidth)-size[0])/2 + WestWidth;
					}
					else
					{
						size[0] = borderSize.x()-(WestWidth+EastWidth);
						offset[0] = WestWidth;
					}
					if ((*Components)[i]->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = (*Components)[i]->getMaxSize().y();
						offset[1] = (borderSize.y()-(NorthHeight+SouthHeight)-size[1])/2 + NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offset[1] = NorthHeight;
					}
					break;
				case BorderLayoutConstraints::BORDER_NORTH:
					// set up the size of the button and its extra displacement
					size[1] = (*Components)[i]->getPreferredSize().y();
					offset[1] = 0;
					if ((*Components)[i]->getMaxSize().x() < borderSize.x())
					{
						size[0] = (*Components)[i]->getMaxSize().x();
						offset[0] = (borderSize.x()-size[0])/2;
					}
					else
					{
						size[0] = borderSize.x();
						offset[0] = 0;
					}
					break;
				case BorderLayoutConstraints::BORDER_EAST:
					// set up the size of the button and its extra displacement
					size[0] = (*Components)[i]->getPreferredSize().x();
					offset[0] = borderSize.x()-size.x();
					if ((*Components)[i]->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = (*Components)[i]->getMaxSize().y();
						offset[1] = (borderSize.y()-size[1]-(NorthHeight+SouthHeight))/2+NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offset[1] = NorthHeight;
					}
					break;
				case BorderLayoutConstraints::BORDER_SOUTH:
					// set up the size of the button and its extra displacement
					size[1] = (*Components)[i]->getPreferredSize().y();
					offset[1] = borderSize.y()-size[1];
					if ((*Components)[i]->getMaxSize().x() < borderSize.x())
					{
						size[0] = (*Components)[i]->getMaxSize().x();
						offset[0] = (borderSize.x()-size[0])/2;
					}
					else
					{
						size[0] = borderSize.x();
						offset[0] = 0;
					}
					break;
				case BorderLayoutConstraints::BORDER_WEST:
					// set up the size of the button and its extra displacement
					size[0] = (*Components)[i]->getPreferredSize().x();
					offset[0] = 0;
					if ((*Components)[i]->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = (*Components)[i]->getMaxSize().y();
						offset[1] = (borderSize.y()-size[1]-(NorthHeight+SouthHeight))/2 + NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offset[1] = NorthHeight;
					}
					break;
				default:
					// if it isn't any of the regions, set it up to not be drawn
					size[0] = size[1] = offset[0] = offset[1] = 0;
					break; 
			}
			
			size[0] = osgMin(osgMax(size[0], (*Components)[i]->getMinSize().x()), (*Components)[i]->getMaxSize().x());
			size[1] = osgMin(osgMax(size[1], (*Components)[i]->getMinSize().y()), (*Components)[i]->getMaxSize().y());
            // now set the position and size of the button
            if((*Components)[i]->getSize() != size)
            {
                (*Components)[i]->setSize(size);
            }
            Pos = borderTopLeft + Vec2f(offset);
            if((*Components)[i]->getPosition() != Pos)
            {
                (*Components)[i]->setPosition(Pos);
            }
		}
	}
}

Vec2f BorderLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
{
    Vec2f Result(0.0,0.0);

    Vec2f WestSize(0.0,0.0),
        EastSize(0.0,0.0),
        NorthSize(0.0,0.0),
        SouthSize(0.0,0.0),
        CenterSize(0.0,0.0);
    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        switch(dynamic_cast<BorderLayoutConstraints*>((*Components)[i]->getConstraints())->getRegion())
        {
        case BorderLayoutConstraints::BORDER_WEST:
            WestSize = getComponentSize((*Components)[i],TheSizeType);
            break;
        case BorderLayoutConstraints::BORDER_EAST:
            EastSize = getComponentSize((*Components)[i],TheSizeType);
            break;
        case BorderLayoutConstraints::BORDER_NORTH:
            NorthSize = getComponentSize((*Components)[i],TheSizeType);
            break;
        case BorderLayoutConstraints::BORDER_SOUTH:
            SouthSize = getComponentSize((*Components)[i],TheSizeType);
            break;
        case BorderLayoutConstraints::BORDER_CENTER:
            CenterSize = getComponentSize((*Components)[i],TheSizeType);
            break;
        }
    }

    switch(TheSizeType)
    {
    case MAX_SIZE:
        Result[0] = osgMin(osgMin(EastSize.x() + CenterSize.x() + WestSize.x(),NorthSize.x()),SouthSize.x());
        Result[1] = osgMin(osgMin(EastSize.y(), CenterSize.y()), WestSize.y()) + NorthSize.y() + SouthSize.y();
        break;
    case MIN_SIZE:
    case PREFERRED_SIZE:
    case REQUESTED_SIZE:
    default:
        Result[0] = osgMax(osgMax(EastSize.x() + CenterSize.x() + WestSize.x(),NorthSize.x()),SouthSize.x());
        Result[1] = osgMax(osgMax(EastSize.y(), CenterSize.y()), WestSize.y()) + NorthSize.y() + SouthSize.y();
        break;
    }

    return Result;
}

Vec2f BorderLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f BorderLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f BorderLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f BorderLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BorderLayout::BorderLayout(void) :
    Inherited()
{
}

BorderLayout::BorderLayout(const BorderLayout &source) :
    Inherited(source)
{
}

BorderLayout::~BorderLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BorderLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BorderLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BorderLayout NI" << std::endl;
}

OSG_END_NAMESPACE
