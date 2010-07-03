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

#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbsoluteLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGAbsoluteLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbsoluteLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbsoluteLayout::updateLayout(const MFUnrecChildComponentPtr* Components,
                                  const Component* ParentComponent) const
{
    Pnt2f ParentInsetsTopLeft, ParentInsetBottomRight;
    dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(ParentInsetsTopLeft, ParentInsetBottomRight);
    for(UInt32 i = 0 ; i<Components->size(); ++i)
    {
        //Calculate the Components Size
        (*Components)[i]->setSize((*Components)[i]->getPreferredSize());
        if((*Components)[i]->getConstraints() != NULL)
        {
            //Get the Components Position
            Pnt2f pos = dynamic_cast<AbsoluteLayoutConstraints*>((*Components)[i]->getConstraints())->getPosition();

            (*Components)[i]->setPosition(ParentInsetsTopLeft + pos.subZero());
        }
        else
        {
            (*Components)[i]->setPosition(ParentInsetsTopLeft);
        }
    }
}


Vec2f AbsoluteLayout::layoutSize(const MFUnrecChildComponentPtr* Components,
                                 const Component* ParentComponent,
                                 SizeType TheSizeType) const
{
    Vec2f Result(0.0,0.0);

    Vec2f ComponentSize;
    Pnt2f ComponentPosition;
    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        ComponentPosition = dynamic_cast<AbsoluteLayoutConstraints*>((*Components)[i]->getConstraints())->getPosition();

        ComponentSize = getComponentSize((*Components)[i],TheSizeType);
        if(ComponentPosition.x() + ComponentSize.x() > Result.x())
        {
            Result[0] = ComponentPosition.x() + ComponentSize.x();
        }
        if(ComponentPosition.y() + ComponentSize.y() > Result.y())
        {
            Result[1] = ComponentPosition.y() + ComponentSize.y();
        }
    }

    return Result;
}

Vec2f AbsoluteLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                                const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f AbsoluteLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                                  const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f AbsoluteLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                                  const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f AbsoluteLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components,
                                                const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbsoluteLayout::AbsoluteLayout(void) :
    Inherited()
{
}

AbsoluteLayout::AbsoluteLayout(const AbsoluteLayout &source) :
    Inherited(source)
{
}

AbsoluteLayout::~AbsoluteLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbsoluteLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbsoluteLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbsoluteLayout NI" << std::endl;
}

OSG_END_NAMESPACE
