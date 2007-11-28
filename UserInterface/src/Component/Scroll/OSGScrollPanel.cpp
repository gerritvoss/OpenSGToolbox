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
        getVerticalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), VERTICAL_ALIGNMENT, 1));
        
        getVerticalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), VERTICAL_ALIGNMENT, 1));
    endEditCP(getVerticalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
    
    beginEditCP(getHorizontalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
        //getHorizontalScrollBar()->setBlockIncrement(_ViewportHorizontalRangeModel.getExtent());
        getHorizontalScrollBar()->setBlockIncrement(getView()->getViewComponent()->getScrollableBlockIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), HORIZONTAL_ALIGNMENT, 1));
        
        getHorizontalScrollBar()->setUnitIncrement(getView()->getViewComponent()->getScrollableUnitIncrement(getView()->getViewPosition(), getView()->getViewPosition() + getView()->getSize(), HORIZONTAL_ALIGNMENT, 1));
    endEditCP(getHorizontalScrollBar(), ScrollBar::BlockIncrementFieldMask | ScrollBar::UnitIncrementFieldMask);
    
    getView()->addChangeListener(&_ViewportChangeListener);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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
    }

	Pnt2s TopLeft, BottomRight;
	getInsideInsetsBounds(TopLeft, BottomRight);

    Vec2s ViewportSize(BottomRight - TopLeft);

    //Set the ScrollBar Position and Sizes
    if(VerticalScrollbarShown && HorizontalScrollbarShown)
    {
        //Vertical
        beginEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getVerticalScrollBar()->setSize(Vec2s(getVerticalScrollBar()->getPreferredSize().x(), (BottomRight.y() - TopLeft.y() - getHorizontalScrollBar()->getPreferredSize().y()) ));
            getVerticalScrollBar()->setPosition(Pnt2s(BottomRight.x() - getVerticalScrollBar()->getSize().x(), TopLeft.y()));
        endEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);

        //Horizontal
        beginEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getHorizontalScrollBar()->setSize(Vec2s((BottomRight.x() - TopLeft.x() - getVerticalScrollBar()->getPreferredSize().x()), getHorizontalScrollBar()->getPreferredSize().y()) );
            getHorizontalScrollBar()->setPosition(Pnt2s(TopLeft.x(), BottomRight.y() - getHorizontalScrollBar()->getSize().y()));
        endEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);

        ViewportSize = ViewportSize - Vec2s(getVerticalScrollBar()->getSize().x(), getHorizontalScrollBar()->getSize().y());
    }
    else if(VerticalScrollbarShown)
    {
        beginEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getVerticalScrollBar()->setSize(Vec2s(getVerticalScrollBar()->getPreferredSize().x(), (BottomRight.y() - TopLeft.y()) ));
            getVerticalScrollBar()->setPosition(BottomRight-getVerticalScrollBar()->getSize());
        endEditCP(getVerticalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
        ViewportSize = ViewportSize - Vec2s(getVerticalScrollBar()->getSize().x(), 0);
    }
    else if(HorizontalScrollbarShown)
    {
        beginEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
            getHorizontalScrollBar()->setSize(Vec2s((BottomRight.x() - TopLeft.x()), getHorizontalScrollBar()->getPreferredSize().y()) );
            getHorizontalScrollBar()->setPosition(BottomRight-getHorizontalScrollBar()->getSize());
        endEditCP(getHorizontalScrollBar(), ScrollBar::SizeFieldMask | ScrollBar::PositionFieldMask);
        ViewportSize = ViewportSize - Vec2s(0, getHorizontalScrollBar()->getSize().y());
    }

    //Set the Viewports position and size
    if(getView() != NullFC)
    {
        beginEditCP(getView(), UIViewport::SizeFieldMask | UIViewport::PositionFieldMask);
            getView()->setPosition(Pnt2s(0,0));
            getView()->setSize(ViewportSize);
        endEditCP(getView(), UIViewport::SizeFieldMask | UIViewport::PositionFieldMask);
    }
    

    //Update my Size if nessicary
    if(getVerticalResizePolicy() == RESIZE_TO_VIEW ||
        getHorizontalResizePolicy() == RESIZE_TO_VIEW)
    {
        Vec2s Size(getPreferredSize());
        if(getVerticalResizePolicy() == RESIZE_TO_VIEW)
        {
            Size[1] = getView()->getViewComponent()->getPreferredSize()[1];
            if(HorizontalScrollbarShown)
            {
               Size[1] += getHorizontalScrollBar()->getSize()[1];
            }
        }
        if(getHorizontalResizePolicy() == RESIZE_TO_VIEW)
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
    
    if(getVerticalScrollBar() != NullFC &&
        getHorizontalScrollBar() != NullFC)
    {
        beginEditCP(ScrollPanelPtr(this), VerticalScrollBarFieldMask | 
            HorizontalScrollBarFieldMask);

        setVerticalScrollBar(ScrollBar::Ptr::dcast(getVerticalScrollBar()->shallowCopy()));
        setHorizontalScrollBar(ScrollBar::Ptr::dcast(getHorizontalScrollBar()->shallowCopy()));
        
        endEditCP(ScrollPanelPtr(this), VerticalScrollBarFieldMask | 
            HorizontalScrollBarFieldMask);
    }
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
    if((whichField & VerticalScrollBarFieldMask) ||
        (whichField & HorizontalScrollBarFieldMask) ||
        (whichField & ViewFieldMask))
    {
        beginEditCP(ScrollPanelPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getView() != NullFC){getChildren().push_back(getView());}
            if(getVerticalScrollBar() != NullFC){getChildren().push_back(getVerticalScrollBar());}
            if(getHorizontalScrollBar() != NullFC)
            {
                getChildren().push_back(getHorizontalScrollBar());
            }
        endEditCP(ScrollPanelPtr(this), ChildrenFieldMask);
    }

    if((whichField & VerticalScrollBarFieldMask) &&
        getVerticalScrollBar() != NullFC)
    {
        getVerticalScrollBar()->setModel(&_ViewportVerticalRangeModel);
    }
    
    if((whichField & HorizontalScrollBarFieldMask) &&
        getHorizontalScrollBar() != NullFC)
    {
        getHorizontalScrollBar()->setModel(&_ViewportHorizontalRangeModel);
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
            Pnt2s(_ScrollPanel->_ViewportHorizontalRangeModel.getValue(), _ScrollPanel->_ViewportVerticalRangeModel.getValue()) );
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

