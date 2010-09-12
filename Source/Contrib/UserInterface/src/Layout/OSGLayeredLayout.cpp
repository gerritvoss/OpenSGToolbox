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

#include "OSGLayeredLayout.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLayeredLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGLayeredLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LayeredLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LayeredLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    Pnt2f windowTopLeft, windowBottomRight;
    dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(windowTopLeft, windowBottomRight);
    Vec2f windowSize(windowBottomRight-windowTopLeft);

    int maxX = 0;
    int maxY = 0;
    for(UInt32 i = 0; i < Components->size(); i++)
    {
        if((*Components)[i]->getSize() != windowSize)
        {
            (*Components)[i]->setSize(windowSize);
        }
    }
    for(UInt32 i = 0; i <Components->size(); i++)
    {
        if((*Components)[i]->getPosition() != windowTopLeft)
        {
            (*Components)[i]->setPosition(windowTopLeft);
        }
    }
}

Vec2f LayeredLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
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

Vec2f LayeredLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f LayeredLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f LayeredLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f LayeredLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LayeredLayout::LayeredLayout(void) :
    Inherited()
{
}

LayeredLayout::LayeredLayout(const LayeredLayout &source) :
    Inherited(source)
{
}

LayeredLayout::~LayeredLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LayeredLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LayeredLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LayeredLayout NI" << std::endl;
}

OSG_END_NAMESPACE
