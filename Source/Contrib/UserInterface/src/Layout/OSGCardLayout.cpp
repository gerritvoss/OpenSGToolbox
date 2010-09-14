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

#include "OSGCardLayout.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCardLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGCardLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CardLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CardLayout::first(ComponentContainer* const TheContainer)
{
    setCard(0);
}

void CardLayout::last(ComponentContainer* const TheContainer)
{
    setCard(TheContainer->getMFChildren()->size()-1);
}

void CardLayout::next(ComponentContainer* const TheContainer)
{	
    setCard((getCard()+1)%TheContainer->getMFChildren()->size());
}

void CardLayout::previous(ComponentContainer* const TheContainer)
{   
    setCard((getCard()-1)%TheContainer->getMFChildren()->size());
}

void CardLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    if(getCard() >= Components->size())
    {
        SWARNING << "CardLayout::updateLayout: The Index set for Card is: "<< getCard() << ", but there are only "
            << Components->size() << " components in the container this layout is attached to" << std::endl;
        return;
    }

    /*!
      Draw the current "card" component centered in the parent component
      and set to the size of the parent component, or to its max size
      */
    Pnt2f borderTopLeft, borderBottomRight;
    dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
    Vec2f borderSize(borderBottomRight-borderTopLeft);
    Vec2f size(borderSize),offset;
    ComponentRefPtr curCard((*Components)[getCard()]);

    for(UInt32 i(0) ; i<Components->size() ; ++i)
    {
        if((*Components)[i] != curCard &&
            (*Components)[i]->getSize() != Vec2f(0.0f,0.0f))
        {
            (*Components)[i]->setSize(Vec2f(0.0f,0.0f));
        }
    }
    // check each dimension against the max size of the component;
    if (size[0] > curCard->getMaxSize()[0]) 
        size[0] = curCard->getMaxSize()[0];
    if (size[1] > curCard->getMaxSize()[1]) 
        size[1] = curCard->getMaxSize()[1];
    // set the component to its parent component's size, or its max size
    if(curCard->getSize() != size)
    {
        curCard->setSize(size);
    }

    offset[0] = (borderSize.x()-size.x())/2;
    offset[1] = (borderSize.y()-size.y())/2;

    Pnt2f Pos(borderTopLeft + Vec2f(offset));
    if(curCard->getPosition() != Pos)
    {
        curCard->setPosition(Pos);
    }

}


Vec2f CardLayout::layoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent, SizeType TheSizeType) const
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

Vec2f CardLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f CardLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f CardLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f CardLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CardLayout::CardLayout(void) :
    Inherited()
{
}

CardLayout::CardLayout(const CardLayout &source) :
    Inherited(source)
{
}

CardLayout::~CardLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CardLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & CardFieldMask)
    {
        updateParentContainers();
    }
}

void CardLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CardLayout NI" << std::endl;
}

OSG_END_NAMESPACE
