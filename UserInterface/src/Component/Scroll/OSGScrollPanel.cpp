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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGScrollPanel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ScrollPanel
A UI ScrollPanel 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScrollPanel::initMethod (void)
{
}


void ScrollPanel::setViewComponent(ComponentPtr TheComponent)
{
    if(getView() == NullFC)
    {
        UIViewportPtr NewView  = UIViewport::create();
        
        beginEditCP(NewView, UIViewport::ViewComponentFieldMask);
            NewView->setViewComponent(TheComponent);
        endEditCP(NewView, UIViewport::ViewComponentFieldMask);
        beginEditCP(ScrollPanelPtr(this), ScrollPanel::ViewFieldMask);
            setView(NewView);
        endEditCP(ScrollPanelPtr(this), ScrollPanel::ViewFieldMask);
    }
    else
    {
        beginEditCP(getView(), UIViewport::ViewComponentFieldMask);
            getView()->setViewComponent(TheComponent);
        endEditCP(getView(), UIViewport::ViewComponentFieldMask);
    }
    getView()->addChangeListener(&_ViewportChangeListener);

    updateRangeModels();
}

void ScrollPanel::updateRangeModels(void)
{
    getView()->removeChangeListener(&_ViewportChangeListener);
    
    _ViewportVerticalRangeModel.setRangeProperties(
        getView()->getViewPosition().y(),
        getView()->getSize().y(),
        0,
        getView()->getViewComponent()->getSize().y(),
        false);
    
    _ViewportHorizontalRangeModel.setRangeProperties(
        getView()->getViewPosition().x(),
        getView()->getSize().x(),
        0,
        getView()->getViewComponent()->getSize().x(),
        false);

    beginEditCP(getVerticalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
        //getVerticalScrollBar()->setBlockIncrement(_ViewportVerticalRangeModel.getExtent());
        getVerticalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::VERTICAL_ORIENTATION, 1));
        
        getVerticalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::VERTICAL_ORIENTATION, 1));
    endEditCP(getVerticalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
    
    beginEditCP(getHorizontalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
        //getHorizontalScrollBar()->setBlockIncrement(_ViewportHorizontalRangeModel.getExtent());
        getHorizontalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::HORIZONTAL_ORIENTATION, 1));
        
        getHorizontalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), ScrollBar::HORIZONTAL_ORIENTATION, 1));
    endEditCP(getHorizontalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
    
    getView()->addChangeListener(&_ViewportChangeListener);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ScrollBarPtr ScrollPanel::getVerticalScrollBar(void)
{
    if(getInternalVerticalScrollBar() == NullFC)
    {
        ScrollBarPtr NewVerticalScrollBar = ScrollBar::create();
        beginEditCP(NewVerticalScrollBar, ScrollBar::OrientationFieldMask);
            NewVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
        endEditCP(NewVerticalScrollBar, ScrollBar::OrientationFieldMask);


        beginEditCP(ScrollPanelPtr(this), InternalVerticalScrollBarFieldMask);
            setInternalVerticalScrollBar(NewVerticalScrollBar);
        endEditCP(ScrollPanelPtr(this), InternalVerticalScrollBarFieldMask);
    }
    return getInternalVerticalScrollBar();
}

ScrollBarPtr ScrollPanel::getHorizontalScrollBar(void)
{
    if(getInternalHorizontalScrollBar() == NullFC)
    {
        ScrollBarPtr NewHorizontalScrollBar = ScrollBar::create();
        beginEditCP(NewHorizontalScrollBar, ScrollBar::OrientationFieldMask);
            NewHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
        endEditCP(NewHorizontalScrollBar, ScrollBar::OrientationFieldMask);


        beginEditCP(ScrollPanelPtr(this), InternalHorizontalScrollBarFieldMask);
            setInternalHorizontalScrollBar(NewHorizontalScrollBar);
        endEditCP(ScrollPanelPtr(this), InternalHorizontalScrollBarFieldMask);
    }
    return getInternalHorizontalScrollBar();
}

void ScrollPanel::updateLayout(void)
{
    bool VerticalScrollbarShown;
    //Determine if Vertical Scrollbar is shown
    if(getVerticalScrollBarDisplayPolicy() == SCROLLBAR_AS_ALWAYS ||
       (getVerticalScrollBarDisplayPolicy() == SCROLLBAR_AS_NEEDED &&
       _ViewportVerticalRangeModel.getExtent() < (_ViewportVerticalRangeModel.getMaximum() - _ViewportVerticalRangeModel.getMinimum()) ))
    {
        VerticalScrollbarShown = true;
        beginEditCP(getVerticalScrollBar(), ScrollBar::VisibleFieldMask);
            getVerticalScrollBar()->setVisible(true);
        endEditCP(getVerticalScrollBar(), ScrollBar::VisibleFieldMask);
    }
    else
    {
        VerticalScrollbarShown = false;
        beginEditCP(getVerticalScrollBar(), ScrollBar::VisibleFieldMask);
            getVerticalScrollBar()->setVisible(false);
        endEditCP(getVerticalScrollBar(), ScrollBar::VisibleFieldMask);

		if(getView() != NullFC)
		{
			beginEditCP(getView(), UIViewport::ViewPositionFieldMask);
				getView()->setViewPosition(Pnt2f(getView()->getViewPosition().x(), 0.0f));
			endEditCP(getView(), UIViewport::ViewPositionFieldMask);
		}
    }

    bool HorizontalScrollbarShown;
    //Determine if Horizontal Scrollbar is shown
    if(getHorizontalScrollBarDisplayPolicy() == SCROLLBAR_AS_ALWAYS ||
       (getHorizontalScrollBarDisplayPolicy() == SCROLLBAR_AS_NEEDED &&
       _ViewportHorizontalRangeModel.getExtent() < (_ViewportHorizontalRangeModel.getMaximum() - _ViewportHorizontalRangeModel.getMinimum()) ))
    {
        HorizontalScrollbarShown = true;
        beginEditCP(getHorizontalScrollBar(), ScrollBar::VisibleFieldMask);
            getHorizontalScrollBar()->setVisible(true);
        endEditCP(getHorizontalScrollBar(), ScrollBar::VisibleFieldMask);
    }
    else
    {
        HorizontalScrollbarShown = false;
        beginEditCP(getHorizontalScrollBar(), ScrollBar::VisibleFieldMask);
            getHorizontalScrollBar()->setVisible(false);
        endEditCP(getHorizontalScrollBar(), ScrollBar::VisibleFieldMask);
		if(getView() != NullFC)
		{
			beginEditCP(getView(), UIViewport::ViewPositionFieldMask);
				getView()->setViewPosition(Pnt2f(0.0f, getView()->getViewPosition().y()));
			endEditCP(getView(), UIViewport::ViewPositionFieldMask);
		}
    }

	Pnt2f TopLeft, BottomRight;
	getInsideInsetsBounds(TopLeft, BottomRight);

    Vec2f ViewportSize(BottomRight - TopLeft);
    Pnt2f ViewportPosition(TopLeft);

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
        beginEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getVerticalScrollBar()->setSize(VerticalScrollbarSize);
            getVerticalScrollBar()->setPosition(VerticalScrollbarPosition);
        endEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);

        //Horizontal
        beginEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getHorizontalScrollBar()->setSize(HorizontalScrollbarSize);
            getHorizontalScrollBar()->setPosition(HorizontalScrollbarPosition);
        endEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);

        ViewportSize = ViewportSize - Vec2f(getVerticalScrollBar()->getSize().x(), getHorizontalScrollBar()->getSize().y());
    }
    else if(VerticalScrollbarShown)
    {
        beginEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getVerticalScrollBar()->setSize(Vec2f(getVerticalScrollBar()->getPreferredSize().x(), (BottomRight.y() - TopLeft.y()) ));
            if(getVerticalScrollBarAlignment() == SCROLLBAR_ALIGN_LEFT)
            {
                getVerticalScrollBar()->setPosition(TopLeft);
                ViewportPosition = TopLeft+Vec2f(getVerticalScrollBar()->getSize().x(),0.0f);
            }
            else
            {
                getVerticalScrollBar()->setPosition(BottomRight-getVerticalScrollBar()->getSize());
                ViewportPosition = TopLeft;
            }
        endEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
        ViewportSize = ViewportSize - Vec2f(getVerticalScrollBar()->getSize().x(), 0);
    }
    else if(HorizontalScrollbarShown)
    {
        beginEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getHorizontalScrollBar()->setSize(Vec2f((BottomRight.x() - TopLeft.x()), getHorizontalScrollBar()->getPreferredSize().y()) );
            if(getHorizontalScrollBarAlignment() == SCROLLBAR_ALIGN_TOP)
            {
                getHorizontalScrollBar()->setPosition(TopLeft);
                ViewportPosition = TopLeft+Vec2f(0.0f,getVerticalScrollBar()->getSize().y());
            }
            else
            {
                getHorizontalScrollBar()->setPosition(BottomRight-getHorizontalScrollBar()->getSize());
                ViewportPosition = TopLeft;
            }
        endEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
        ViewportSize = ViewportSize - Vec2f(0, getHorizontalScrollBar()->getSize().y());
    }

    //Set the Viewports position and size
    if(getView() != NullFC)
    {
		UInt32 FieldsToChange(0);
		if(getView()->getPosition() != ViewportPosition)
		{
			FieldsToChange |= UIViewport::PositionFieldMask;
		}
		if(getView()->getSize() != ViewportSize)
		{
			FieldsToChange |= UIViewport::SizeFieldMask;
		}
        beginEditCP(getView(), FieldsToChange);
		
			if(getView()->getPosition() != ViewportPosition)
			{
				getView()->setPosition(ViewportPosition);
			}
			if(getView()->getSize() != ViewportSize)
			{
				getView()->setSize(ViewportSize);
			}
        endEditCP(getView(), FieldsToChange);
    }
    

    //Update my Size if nessicary
    if(getVerticalResizePolicy() == RESIZE_TO_VIEW ||
        getHorizontalResizePolicy() == RESIZE_TO_VIEW)
    {
        Vec2f Size(getPreferredSize());
        if(getView() != NullFC && getVerticalResizePolicy() == RESIZE_TO_VIEW)
        {
            Size[1] = getView()->getViewComponent()->getPreferredSize()[1];
            if(HorizontalScrollbarShown)
            {
               Size[1] += getHorizontalScrollBar()->getSize()[1];
            }
        }
        if(getView() != NullFC && getHorizontalResizePolicy() == RESIZE_TO_VIEW)
        {
            Size[0] = getView()->getViewComponent()->getPreferredSize()[0];
            if(VerticalScrollbarShown)
            {
               Size[0] += getVerticalScrollBar()->getSize()[0];
            }
        }
        if(Size != getPreferredSize())
        {
            beginEditCP(ScrollPanelPtr(this), PreferredSizeFieldMask);
                setPreferredSize(Size);
            endEditCP(ScrollPanelPtr(this), PreferredSizeFieldMask);
        }
    }
}

void ScrollPanel::mouseWheelMoved(const MouseWheelEvent& e)
{
    if(getView() != NullFC && getView()->isContained(e.getLocation(), true))
    {
        if(e.getScrollType() == MouseWheelEvent::BLOCK_SCROLL)
        {
            if(getVerticalScrollBar()->getVisible())
            {
                getVerticalScrollBar()->scrollBlock(-e.getScrollAmount());
            }
            else if(getHorizontalScrollBar()->getVisible())
            {
                getHorizontalScrollBar()->scrollBlock(-e.getScrollAmount());
            }
        }
        else if(e.getScrollType() == MouseWheelEvent::UNIT_SCROLL)
        {
            if(getVerticalScrollBar()->getVisible())
            {
                getVerticalScrollBar()->scrollUnit(-e.getUnitsToScroll());
            }
            else if(getHorizontalScrollBar()->getVisible())
            {
                getHorizontalScrollBar()->scrollUnit(-e.getUnitsToScroll());
            }
        }
    }
    Container::mouseWheelMoved(e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScrollPanel::ScrollPanel(void) :
    Inherited(),
    _ViewportChangeListener(ScrollPanelPtr(this)),
    _ViewportRangeModelChangeListener(ScrollPanelPtr(this))
{
    _ViewportVerticalRangeModel.addChangeListener(&_ViewportRangeModelChangeListener);
    _ViewportHorizontalRangeModel.addChangeListener(&_ViewportRangeModelChangeListener);
}

ScrollPanel::ScrollPanel(const ScrollPanel &source) :
    Inherited(source),
    _ViewportChangeListener(ScrollPanelPtr(this)),
    _ViewportRangeModelChangeListener(ScrollPanelPtr(this))
{
    _ViewportVerticalRangeModel.addChangeListener(&_ViewportRangeModelChangeListener);
    _ViewportHorizontalRangeModel.addChangeListener(&_ViewportRangeModelChangeListener);
    
    ScrollBarPtr NewVerticalScrollBar = ScrollBar::create();
    beginEditCP(NewVerticalScrollBar, ScrollBar::OrientationFieldMask);
        NewVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    endEditCP(NewVerticalScrollBar, ScrollBar::OrientationFieldMask);

    ScrollBarPtr NewHorizontalScrollBar = ScrollBar::create();
    beginEditCP(NewHorizontalScrollBar, ScrollBar::OrientationFieldMask);
        NewHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    endEditCP(NewHorizontalScrollBar, ScrollBar::OrientationFieldMask);

    beginEditCP(ScrollPanelPtr(this), InternalVerticalScrollBarFieldMask | InternalHorizontalScrollBarFieldMask);
        setInternalVerticalScrollBar(NewVerticalScrollBar);
        setInternalHorizontalScrollBar(NewHorizontalScrollBar);
    endEditCP(ScrollPanelPtr(this), InternalVerticalScrollBarFieldMask | InternalHorizontalScrollBarFieldMask);

}

ScrollPanel::~ScrollPanel(void)
{
    _ViewportVerticalRangeModel.removeChangeListener(&_ViewportRangeModelChangeListener);
    _ViewportHorizontalRangeModel.removeChangeListener(&_ViewportRangeModelChangeListener);
}

/*----------------------------- class specific ----------------------------*/

void ScrollPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ViewFieldMask)
        && getView() != NullFC)
    {
        updateRangeModels();
    }
    if((whichField & InternalVerticalScrollBarFieldMask) ||
        (whichField & InternalHorizontalScrollBarFieldMask) ||
        (whichField & ViewFieldMask))
    {
        beginEditCP(ScrollPanelPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getView() != NullFC){getChildren().push_back(getView());}
            if(getInternalVerticalScrollBar() != NullFC){getChildren().push_back(getInternalVerticalScrollBar());}
            if(getInternalHorizontalScrollBar() != NullFC)
            {
                getChildren().push_back(getInternalHorizontalScrollBar());
            }
        endEditCP(ScrollPanelPtr(this), ChildrenFieldMask);
    }

    if((whichField & InternalVerticalScrollBarFieldMask) &&
        getInternalVerticalScrollBar() != NullFC)
    {
        getInternalVerticalScrollBar()->setModel(&_ViewportVerticalRangeModel);
    }
    
    if((whichField & InternalHorizontalScrollBarFieldMask) &&
        getInternalHorizontalScrollBar() != NullFC)
    {
        getInternalHorizontalScrollBar()->setModel(&_ViewportHorizontalRangeModel);
    }
}

void ScrollPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScrollPanel NI" << std::endl;
}


void ScrollPanel::ViewportChangeListener::stateChanged(const ChangeEvent& e)
{
    _ScrollPanel->updateRangeModels();
}

void ScrollPanel::ViewportRangeModelChangeListener::stateChanged(const ChangeEvent& e)
{
    beginEditCP(_ScrollPanel->getView(), UIViewport::ViewPositionFieldMask);
        _ScrollPanel->getView()->setViewPosition(
            Pnt2f(_ScrollPanel->_ViewportHorizontalRangeModel.getValue(), _ScrollPanel->_ViewportVerticalRangeModel.getValue()) );
    endEditCP(_ScrollPanel->getView(), UIViewport::ViewPositionFieldMask);

    _ScrollPanel->updateLayout();
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
    static Char8 cvsid_hpp       [] = OSGSCROLLPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCROLLPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCROLLPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

