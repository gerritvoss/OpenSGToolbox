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

#include "OSGUIViewport.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGUIViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIViewport::getViewBounds(Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    TopLeft.setValues(getViewPosition().x(),getViewPosition().y());
    BottomRight = TopLeft + (InsetsBottomRight - InsetsTopLeft);
}

void UIViewport::maximizeVisibility(const Pnt2f& TopLeft, const Pnt2f& BottomRight)
{
    //Scroll as little as possible until as much as can be is visible

    Pnt2f ViewTopLeft, ViewBottomRight;
    getViewBounds(ViewTopLeft,ViewBottomRight);

    Pnt2f NewViewPosition(getViewPosition());

    //Vertical
    if(ViewTopLeft.y() > TopLeft.y())
    {
        //Scroll up
        NewViewPosition[1] = TopLeft.y();

    }
    else if(ViewBottomRight.y() < BottomRight.y())
    {
        Pnt2f InsetsTopLeft, InsetsBottomRight;
        getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
        //Scroll down
        NewViewPosition[1] = BottomRight.y() - (InsetsBottomRight - InsetsTopLeft).y();
    }

    //Horizontal
    if(ViewTopLeft.x() > TopLeft.x())
    {
        //Scroll left
        NewViewPosition[0] = TopLeft.x();

    }
    else if(ViewBottomRight.x() < BottomRight.x())
    {
        Pnt2f InsetsTopLeft, InsetsBottomRight;
        getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

        //Scroll right
        NewViewPosition[0] = BottomRight.x() - (InsetsBottomRight - InsetsTopLeft).x();
    }

    setViewPosition(NewViewPosition);
}

void UIViewport::updateLayout(void)
{
    if(getViewComponent() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideInsetsBounds(TopLeft, BottomRight);

        getViewComponent()->editPosition().setValues(TopLeft.x()-getViewPosition().x(),TopLeft.y()-getViewPosition().y());
        updateViewComponentSize();

        produceStateChanged();
    }
}

void UIViewport::produceStateChanged(void)
{
    ChangeEventDetailsUnrecPtr Details(ChangeEventDetails::create(this, getSystemTime()));

    Inherited::produceStateChanged(Details);
}

Vec2f UIViewport::getCorrectedViewSize(void) const
{
    if(getViewSize() != Vec2f(-1,-1))
    {
        return getViewSize();
    }
    else
    {
        return getViewComponent()->getPreferredScrollableViewportSize();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIViewport::UIViewport(void) :
    Inherited()
{
}

UIViewport::UIViewport(const UIViewport &source) :
    Inherited(source)
{
}

UIViewport::~UIViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & ViewComponentFieldMask)
    {
        clearChildren();
        if(getViewComponent() != NULL)
        {
            pushToChildren(getViewComponent());
        }
    }

    if((whichField & ViewSizeFieldMask) && getViewComponent() != NULL)
    {
        updateViewComponentSize();

        produceStateChanged();
    }

    if((whichField & ViewPositionFieldMask) && getViewComponent() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideInsetsBounds(TopLeft, BottomRight);

        getViewComponent()->editPosition().setValues(TopLeft.x()-getViewPosition().x(),TopLeft.y()-getViewPosition().y());

        produceStateChanged();
    }

    if((whichField & ViewSizeFieldMask) ||
       (whichField & ViewPositionFieldMask) ||
       (whichField & SizeFieldMask))
    {
        produceStateChanged();
    }

    if(whichField & SizeFieldMask &&
       getViewComponent() != NULL &&
       (getViewComponent()->getScrollableTracksViewportHeight() ||
        getViewComponent()->getScrollableTracksViewportWidth() ||
        getViewComponent()->getScrollableHeightMinTracksViewport() ||
        getViewComponent()->getScrollableWidthMinTracksViewport()))
    {
        updateViewComponentSize();
    }
}

void UIViewport::dump(      UInt32    ,
                            const BitVector ) const
{
    SLOG << "Dump UIViewport NI" << std::endl;
}

void UIViewport::updateViewComponentSize(void)
{
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    Vec2f Size(getCorrectedViewSize());

    if(getViewComponent()->getScrollableTracksViewportHeight())
    {
        Size[1] = (InsetsBottomRight - InsetsTopLeft).y();
    }
    if(getViewComponent()->getScrollableHeightMinTracksViewport())
    {
        Size[1] = osgMax(Size[1],(InsetsBottomRight - InsetsTopLeft).y());
    }

    if(getViewComponent()->getScrollableTracksViewportWidth())
    {
        Size[0] = (InsetsBottomRight - InsetsTopLeft).x();
    }
    if(getViewComponent()->getScrollableWidthMinTracksViewport())
    {
        Size[0] = osgMax(Size[0],(InsetsBottomRight - InsetsTopLeft).x());
    }
    if(Size != getViewComponent()->getSize())
    {
        getViewComponent()->setSize(Size);
    }
}

OSG_END_NAMESPACE
