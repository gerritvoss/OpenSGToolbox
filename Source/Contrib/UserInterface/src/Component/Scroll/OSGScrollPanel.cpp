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

#include "OSGScrollPanel.h"
#include "OSGUIViewport.h"
#include "OSGScrollBar.h"
#include "OSGButton.h"
#include "OSGDefaultBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScrollPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGScrollPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScrollPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ScrollPanel::setViewComponent(Component* const TheComponent)
{
    if(getView() == NULL)
    {
        UIViewportRefPtr NewView  = UIViewport::create();
        
        NewView->setViewComponent(TheComponent);
        setView(NewView);
    }
    else
    {
        getView()->setViewComponent(TheComponent);
    }

    updateRangeModels();
}

void ScrollPanel::updateRangeModels(void)
{
    if(getView() != NULL &&
       getView()->getViewComponent() != NULL )
    {
        getVerticalRangeModel()->setRangeProperties(
            getView()->getViewPosition().y(),
            getView()->getSize().y(),
            0,
            getView()->getViewComponent()->getSize().y(),
            false);
        
        getHorizontalRangeModel()->setRangeProperties(
            getView()->getViewPosition().x(),
            getView()->getSize().x(),
            0,
            getView()->getViewComponent()->getSize().x(),
            false);

            //getVerticalScrollBar()->setBlockIncrement(getVerticalRangeModel()->getExtent());
            getVerticalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::VERTICAL_ORIENTATION, 1));
            
            getVerticalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::VERTICAL_ORIENTATION, 1));
        
            //getHorizontalScrollBar()->setBlockIncrement(getHorizontalRangeModel()->getExtent());
            getHorizontalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::HORIZONTAL_ORIENTATION, 1));
            
            getHorizontalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::HORIZONTAL_ORIENTATION, 1));
    }
}

ScrollBar* ScrollPanel::getVerticalScrollBar(void)
{
    if(getInternalVerticalScrollBar() == NULL)
    {
        ScrollBarRefPtr NewVerticalScrollBar = ScrollBar::create();
        NewVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);

        setInternalVerticalScrollBar(NewVerticalScrollBar);
    }
    return getInternalVerticalScrollBar();
}

ScrollBar* ScrollPanel::getHorizontalScrollBar(void)
{
    if(getInternalHorizontalScrollBar() == NULL)
    {
        ScrollBarRefPtr NewHorizontalScrollBar = ScrollBar::create();
            NewHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);


            setInternalHorizontalScrollBar(NewHorizontalScrollBar);
    }
    return getInternalHorizontalScrollBar();
}

void ScrollPanel::updateLayout(void)
{

	Pnt2f TopLeft, BottomRight;
	getInsideInsetsBounds(TopLeft, BottomRight);

    Vec2f ViewportSize(BottomRight - TopLeft);
    Pnt2f ViewportPosition(TopLeft);

    bool VerticalScrollbarShown;
    //Determine if Vertical Scrollbar is shown
    if(getVerticalScrollBarDisplayPolicy() == SCROLLBAR_AS_ALWAYS ||
       (getVerticalScrollBarDisplayPolicy() == SCROLLBAR_AS_NEEDED &&
       getVerticalRangeModel()->getExtent() < (getVerticalRangeModel()->getMaximum() - getVerticalRangeModel()->getMinimum()) ))
    {
        VerticalScrollbarShown = true;
        getVerticalScrollBar()->setVisible(true);
    }
    else
    {
        VerticalScrollbarShown = false;
        if(getVerticalScrollBar()->getVisible())
        {
            getVerticalScrollBar()->setVisible(false);
            getVerticalScrollBar()->setValue(getVerticalScrollBar()->getMinimum());
        }
    }

    bool HorizontalScrollbarShown;
    //Determine if Horizontal Scrollbar is shown
    if(getHorizontalScrollBarDisplayPolicy() == SCROLLBAR_AS_ALWAYS ||
       (getHorizontalScrollBarDisplayPolicy() == SCROLLBAR_AS_NEEDED &&
       getHorizontalRangeModel()->getExtent() < (getHorizontalRangeModel()->getMaximum() - getHorizontalRangeModel()->getMinimum()) ))
    {
        HorizontalScrollbarShown = true;
        getHorizontalScrollBar()->setVisible(true);
    }
    else
    {
        HorizontalScrollbarShown = false;
		if(getHorizontalScrollBar()->getVisible())
        {
            getHorizontalScrollBar()->setVisible(false);
            getHorizontalRangeModel()->setValue(getHorizontalRangeModel()->getMinimum());
        }
    }

    //Set the ScrollBar Position and Sizes
    if(VerticalScrollbarShown && HorizontalScrollbarShown)
    {
        Vec2f VerticalScrollbarSize(getVerticalScrollBar()->getPreferredSize().x(), (BottomRight.y() - TopLeft.y() - getHorizontalScrollBar()->getPreferredSize().y())),
              HorizontalScrollbarSize((BottomRight.x() - TopLeft.x() - getVerticalScrollBar()->getPreferredSize().x()), getHorizontalScrollBar()->getPreferredSize().y());

        Pnt2f VerticalScrollbarPosition,
              HorizontalScrollbarPosition;

        if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_LEFT &&
           getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_TOP)
        {
            VerticalScrollbarPosition.setValues(TopLeft.x(), BottomRight.y() - VerticalScrollbarSize.y());
            HorizontalScrollbarPosition.setValues(BottomRight.x() - HorizontalScrollbarSize.x(), TopLeft.y());
            ViewportPosition = TopLeft + Vec2f(VerticalScrollbarSize.x(), HorizontalScrollbarSize.y());
        }
        else if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_LEFT &&
           getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_BOTTOM)
        {
            VerticalScrollbarPosition = TopLeft;
            HorizontalScrollbarPosition = BottomRight - HorizontalScrollbarSize;
            ViewportPosition = TopLeft + Vec2f(VerticalScrollbarSize.x(), 0.0f);
        }
        else if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_RIGHT &&
           getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_TOP)
        {
            VerticalScrollbarPosition = BottomRight - VerticalScrollbarSize;
            HorizontalScrollbarPosition = TopLeft;
            ViewportPosition = TopLeft + Vec2f(0.0f, HorizontalScrollbarSize.y());
        }
        else if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_RIGHT &&
           getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_BOTTOM)
        {
            VerticalScrollbarPosition.setValues(BottomRight.x() - VerticalScrollbarSize.x(), TopLeft.y());
            HorizontalScrollbarPosition.setValues(TopLeft.x(), BottomRight.y() - HorizontalScrollbarSize.y());
            ViewportPosition = TopLeft;
        }
        //Vertical
        if( getVerticalScrollBar()->getSize() != VerticalScrollbarSize)
        {
            getVerticalScrollBar()->setSize(VerticalScrollbarSize);
        }
        if( getVerticalScrollBar()->getPosition() != VerticalScrollbarPosition)
        {
            getVerticalScrollBar()->setPosition(VerticalScrollbarPosition);
        }

        //Horizontal
        if( getHorizontalScrollBar()->getSize() != HorizontalScrollbarSize)
        {
            getHorizontalScrollBar()->setSize(HorizontalScrollbarSize);
        }
        if( getHorizontalScrollBar()->getPosition() != HorizontalScrollbarPosition)
        {
            getHorizontalScrollBar()->setPosition(HorizontalScrollbarPosition);
        }

        ViewportSize = ViewportSize - Vec2f(getVerticalScrollBar()->getSize().x(), getHorizontalScrollBar()->getSize().y());
    }
    else if(VerticalScrollbarShown)
    {
        Vec2f Size(getVerticalScrollBar()->getPreferredSize().x(), (BottomRight.y() - TopLeft.y()));
        if( getVerticalScrollBar()->getSize() != Size)
        {
            getVerticalScrollBar()->setSize(Size);
        }
        if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_LEFT)
        {
            if( getVerticalScrollBar()->getPosition() != TopLeft)
            {
                getVerticalScrollBar()->setPosition(TopLeft);
            }
            ViewportPosition = TopLeft+Vec2f(getVerticalScrollBar()->getSize().x(),0.0f);
        }
        else
        {
            if( getVerticalScrollBar()->getPosition() != BottomRight-getVerticalScrollBar()->getSize())
            {
                getVerticalScrollBar()->setPosition(BottomRight-getVerticalScrollBar()->getSize());
            }
            ViewportPosition = TopLeft;
        }
        ViewportSize = ViewportSize - Vec2f(getVerticalScrollBar()->getSize().x(), 0);
    }
    else if(HorizontalScrollbarShown)
    {
        Vec2f Size((BottomRight.x() - TopLeft.x()), getHorizontalScrollBar()->getPreferredSize().y());
        if( getHorizontalScrollBar()->getSize() != Size)
        {
            getHorizontalScrollBar()->setSize(Size);
        }
        if(getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_TOP)
        {
            if( getHorizontalScrollBar()->getPosition() != TopLeft)
            {
                getHorizontalScrollBar()->setPosition(TopLeft);
            }
            ViewportPosition = TopLeft+Vec2f(0.0f,getVerticalScrollBar()->getSize().y());
        }
        else
        {
            if( getHorizontalScrollBar()->getPosition() != BottomRight-getHorizontalScrollBar()->getSize())
            {
                getHorizontalScrollBar()->setPosition(BottomRight-getHorizontalScrollBar()->getSize());
            }
            ViewportPosition = TopLeft;
        }
        ViewportSize = ViewportSize - Vec2f(0, getHorizontalScrollBar()->getSize().y());
    }

    //Set the Viewports position and size
    if(getView() != NULL)
    {
        ViewportSize.setValues(osgMax(0.0f,ViewportSize.x()),
                               osgMax(0.0f,ViewportSize.y()));
        if(getView()->getPosition() != ViewportPosition)
        {
            getView()->setPosition(ViewportPosition);
        }
        if(getView()->getSize() != ViewportSize)
        {
            getView()->setSize(ViewportSize);
        }
    }
    

    //Update my Size if nessicary
    if(getVerticalResizePolicy() == RESIZE_TO_VIEW ||
        getHorizontalResizePolicy() == RESIZE_TO_VIEW)
    {
        Vec2f Size(getPreferredSize());
        if(getView() != NULL && 
           getView()->getViewComponent() != NULL && 
           getVerticalResizePolicy() == RESIZE_TO_VIEW)
        {
            Size[1] = getView()->getViewComponent()->getPreferredSize()[1];
            if(HorizontalScrollbarShown)
            {
               Size[1] += getHorizontalScrollBar()->getSize()[1];
            }
        }
        if(getView() != NULL && 
           getView()->getViewComponent() != NULL && 
           getHorizontalResizePolicy() == RESIZE_TO_VIEW)
        {
            Size[0] = getView()->getViewComponent()->getPreferredSize()[0];
            if(VerticalScrollbarShown)
            {
               Size[0] += getVerticalScrollBar()->getSize()[0];
            }
        }
        if(Size != getPreferredSize())
        {
                setPreferredSize(Size);
        }
    }
}

void ScrollPanel::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    ComponentContainer::mouseWheelMoved(e);

    if(getView() != NULL &&
       getView()->isContained(e->getLocation(), true) &&
       !e->getConsumed())
    {
        if(e->getScrollType() == MouseWheelEventDetails::BLOCK_SCROLL)
        {
            if(getVerticalScrollBar()->getVisible())
            {
                getVerticalScrollBar()->scrollBlock(-e->getScrollAmount());
                e->setConsumed(true);
            }
            else if(getHorizontalScrollBar()->getVisible())
            {
                getHorizontalScrollBar()->scrollBlock(-e->getScrollAmount());
                e->setConsumed(true);
            }
        }
        else if(e->getScrollType() == MouseWheelEventDetails::UNIT_SCROLL)
        {
            if(getVerticalScrollBar()->getVisible())
            {
                getVerticalScrollBar()->scrollUnit(-e->getUnitsToScroll());
                e->setConsumed(true);
            }
            else if(getHorizontalScrollBar()->getVisible())
            {
                getHorizontalScrollBar()->scrollUnit(-e->getUnitsToScroll());
                e->setConsumed(true);
            }
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ScrollPanel::onCreate(const ScrollPanel * Id)
{
	Inherited::onCreate(Id);

    ScrollBarRefPtr NewVerticalScrollBar = ScrollBar::create();
    if(NewVerticalScrollBar != NULL)
    {
        NewVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    }

    ScrollBarRefPtr NewHorizontalScrollBar = ScrollBar::create();
    if(NewHorizontalScrollBar != NULL)
    {
        NewHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    }

    setInternalVerticalScrollBar(NewVerticalScrollBar);
    setInternalHorizontalScrollBar(NewHorizontalScrollBar);

    DefaultBoundedRangeModelUnrecPtr VertModel(DefaultBoundedRangeModel::create());
    DefaultBoundedRangeModelUnrecPtr HorModel(DefaultBoundedRangeModel::create());

    setVerticalRangeModel(VertModel);
    setHorizontalRangeModel(HorModel);
}

void ScrollPanel::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

ScrollPanel::ScrollPanel(void) :
    Inherited()
{
}

ScrollPanel::ScrollPanel(const ScrollPanel &source) :
    Inherited(source)
{
}

ScrollPanel::~ScrollPanel(void)
{
    _ViewportStateChangedConnection.disconnect();
    _VertRangeModelStateChangedConnection.disconnect();
    _HorzRangeModelStateChangedConnection.disconnect();
}

/*----------------------------- class specific ----------------------------*/

void ScrollPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & ViewFieldMask)
        && getView() != NULL)
    {    
        _ViewportStateChangedConnection.disconnect();
        _ViewportStateChangedConnection = getView()->connectStateChanged(boost::bind(&ScrollPanel::handleViewportStateChanged, this, _1));

        updateRangeModels();
    }
    if((whichField & InternalVerticalScrollBarFieldMask) ||
        (whichField & InternalHorizontalScrollBarFieldMask) ||
        (whichField & ViewFieldMask))
    {
        clearChildren();
        if(getView() != NULL){pushToChildren(getView());}
        if(getInternalVerticalScrollBar() != NULL){pushToChildren(getInternalVerticalScrollBar());}
        if(getInternalHorizontalScrollBar() != NULL)
        {
            pushToChildren(getInternalHorizontalScrollBar());
        }
    }
    if(whichField & VerticalRangeModelFieldMask)
    {
        _VertRangeModelStateChangedConnection.disconnect();
        if(getVerticalRangeModel() != NULL)
        {
            _VertRangeModelStateChangedConnection = getVerticalRangeModel()->connectStateChanged(boost::bind(&ScrollPanel::handleRangeModelStateChanged, this, _1));
        }
    }
    if(whichField & HorizontalRangeModelFieldMask)
    {
        _HorzRangeModelStateChangedConnection.disconnect();
        if(getHorizontalRangeModel() != NULL)
        {
            _HorzRangeModelStateChangedConnection = getHorizontalRangeModel()->connectStateChanged(boost::bind(&ScrollPanel::handleRangeModelStateChanged, this, _1));
        }
    }

    if((whichField & InternalVerticalScrollBarFieldMask) &&
        getInternalVerticalScrollBar() != NULL)
    {
        getInternalVerticalScrollBar()->setRangeModel(getVerticalRangeModel());
    }
    
    if((whichField & InternalHorizontalScrollBarFieldMask) &&
        getInternalHorizontalScrollBar() != NULL)
    {
        getInternalHorizontalScrollBar()->setRangeModel(getHorizontalRangeModel());
    }
}

void ScrollPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScrollPanel NI" << std::endl;
}

void ScrollPanel::handleViewportStateChanged(ChangeEventDetails* const e)
{
    updateRangeModels();
}

void ScrollPanel::handleRangeModelStateChanged(ChangeEventDetails* const e)
{
    if(getView() != NULL)
    {
        Pnt2f NewViewPos(getHorizontalRangeModel()->getValue(), getVerticalRangeModel()->getValue());
        if(NewViewPos != getView()->getViewPosition())
        {
            getView()->setViewPosition(NewViewPos);
        }
    }

    updateLayout();
}

OSG_END_NAMESPACE
