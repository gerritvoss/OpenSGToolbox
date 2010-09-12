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

#include "OSGOverlayLayout.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGOverlayLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGOverlayLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void OverlayLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void OverlayLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
	Pnt2f borderTopLeft, borderBottomRight;
	dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);

	int maxX = 0;
	int maxY = 0;
	for(UInt32 i = 0; i < Components->size(); i++)
    {
        if((*Components)[i]->getSize() != (*Components)[i]->getPreferredSize())
        {
            (*Components)[i]->setSize((*Components)[i]->getPreferredSize());
        }
		if((*Components)[i]->getSize().x()>maxX)
        {
			maxX = (*Components)[i]->getSize().x();
        }
		if((*Components)[i]->getSize().y()>maxY)
        {
			maxY = (*Components)[i]->getSize().y();
        }
	}
    Pnt2f Pos;
	//overlay layout simply draws all the components on top of each other, with the reference point for all the components being the same
	for(UInt32 i = 0; i <Components->size(); i++)
    {
        Pos = borderTopLeft + 
            Vec2f((maxX-(*Components)[i]->getSize().x())/2.0,
			(maxY-(*Components)[i]->getSize().y())/2.0);
        if((*Components)[i]->getPosition() != Pos)
        {
		    (*Components)[i]->setPosition(Pos);
        }
	}
}

Vec2f OverlayLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
{
    Vec2f Result(0.0,0.0);

    Vec2f ComponentSize;
    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        ComponentSize = getComponentSize((*Components)[i],TheSizeType);
        if(ComponentSize.x() > Result.x())
        {
            Result[0] = ComponentSize.x();
        }
        if(ComponentSize.y() > Result.y())
        {
            Result[1] = ComponentSize.y();
        }
    }

    return Result;
}

Vec2f OverlayLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f OverlayLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f OverlayLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f OverlayLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

OverlayLayout::OverlayLayout(void) :
    Inherited()
{
}

OverlayLayout::OverlayLayout(const OverlayLayout &source) :
    Inherited(source)
{
}

OverlayLayout::~OverlayLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void OverlayLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void OverlayLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump OverlayLayout NI" << std::endl;
}

OSG_END_NAMESPACE
