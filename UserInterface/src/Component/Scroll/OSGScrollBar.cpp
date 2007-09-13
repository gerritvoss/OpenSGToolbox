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

#include "OSGScrollBar.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Component/Container/OSGFrame.h"

#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ScrollBar
A UI ScrollBar. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScrollBar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ScrollBar::updateLayout(void)
{
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

	Pnt2s TopLeft, BottomRight;
	getInsideInsetsBounds(TopLeft, BottomRight);

    Pnt2s Position;
    Vec2s Size;

    //Min Button
    Size[MajorAxis] = getMinButton()->getPreferredSize()[MajorAxis];
    Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

    Position = TopLeft;

    beginEditCP(getMinButton(), PositionFieldMask | SizeFieldMask);
        getMinButton()->setPosition(Position);
        getMinButton()->setSize(Size);
    endEditCP(getMinButton(), PositionFieldMask | SizeFieldMask);

    //Max Button
    Size[MajorAxis] = getMaxButton()->getPreferredSize()[MajorAxis];
    Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

    Position = BottomRight - Size;

    beginEditCP(getMaxButton(), PositionFieldMask | SizeFieldMask);
        getMaxButton()->setPosition(Position);
        getMaxButton()->setSize(Size);
    endEditCP(getMaxButton(), PositionFieldMask | SizeFieldMask);

    //Scroll Field
    Size[MajorAxis] = (BottomRight[MajorAxis] - TopLeft[MajorAxis]) - getMinButton()->getSize()[MajorAxis] - getMaxButton()->getSize()[MajorAxis];
    Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

    Position[MajorAxis] = getMinButton()->getPosition()[MajorAxis] + getMinButton()->getSize()[MajorAxis];
    Position[MinorAxis] = getMinButton()->getPosition()[MinorAxis];
    
    beginEditCP(getScrollField(), PositionFieldMask | SizeFieldMask);
        getScrollField()->setPosition(Position);
        getScrollField()->setSize(Size);
    endEditCP(getScrollField(), PositionFieldMask | SizeFieldMask);

    //ScrollBar
    updateScrollBarLayout();
}

void ScrollBar::updateScrollBarLayout(void)
{
    if(getModel() != NULL)
    {
        UInt16 MajorAxis, MinorAxis;
        if(getOrientation() == VERTICAL_ALIGNMENT)
        {
            MajorAxis = 1;
        }
        else
        {
            MajorAxis = 0;
        }
        MinorAxis = (MajorAxis+1)%2;

        Pnt2s Position;
        Vec2s Size;

        Position[MajorAxis] = getScrollField()->getPosition()[MajorAxis] + 
                            (static_cast<Real32>(getValue())/static_cast<Real32>(getMaximum() - getMinimum())) * (getScrollField()->getSize()[MajorAxis]);
        Position[MinorAxis] = getScrollField()->getPosition()[MinorAxis];

        Size[MajorAxis] = (static_cast<Real32>(getExtent())/static_cast<Real32>(getMaximum() - getMinimum())) * (getScrollField()->getSize()[MajorAxis]);
        Size[MinorAxis] = getScrollField()->getSize()[MinorAxis];

        beginEditCP(getScrollBar(), PositionFieldMask | SizeFieldMask);
            getScrollBar()->setPosition(Position);
            getScrollBar()->setSize(Size);
        endEditCP(getScrollBar(), PositionFieldMask | SizeFieldMask);
    }
}

void  ScrollBar::produceAdjustmentValueChanged(const AdjustmentEvent& e)
{
   for(AdjustmentListenerSetConstItor SetItor(_AdjustmentListeners.begin()) ; SetItor != _AdjustmentListeners.end() ; ++SetItor)
   {
      (*SetItor)->adjustmentValueChanged(e);
   }
}

void ScrollBar::setModel(BoundedRangeModel* Model)
{
    if(_Model != NULL)
    {
        _Model->removeChangeListener(&_BoundedRangeModelChangeListener);
    }
    _Model = Model;
    if(_Model != NULL)
    {
        _Model->addChangeListener(&_BoundedRangeModelChangeListener);
    }
}


void ScrollBar::scrollUnit(const Int32 Units)
{
    if(Units>0)
    {
        if(_Model->getValue() + _Model->getExtent() + Units * getUnitIncrement() > _Model->getMaximum())
        {
            _Model->setValue(_Model->getMaximum() - _Model->getExtent());
        }
        else
        {
            _Model->setValue(_Model->getValue() + Units * getUnitIncrement());
        }
    }
    else if(Units < 0)
    {
        if(_Model->getValue() + Units * static_cast<Int32>(getUnitIncrement()) < _Model->getMinimum())
        {
            _Model->setValue(_Model->getMinimum());
        }
        else
        {
            _Model->setValue(_Model->getValue() + Units * getUnitIncrement());
        }
    }
}

void ScrollBar::scrollBlock(const Int32 Blocks)
{
    if(Blocks>0)
    {
        if(_Model->getValue() + _Model->getExtent() + Blocks * getBlockIncrement() > _Model->getMaximum())
        {
            _Model->setValue(_Model->getMaximum() - _Model->getExtent());
        }
        else
        {
            _Model->setValue(_Model->getValue() + Blocks * getBlockIncrement());
        }
    }
    else if(Blocks < 0)
    {
        if(_Model->getValue() + Blocks * getBlockIncrement() < _Model->getMinimum())
        {
            _Model->setValue(_Model->getMinimum());
        }
        else
        {
            _Model->setValue(_Model->getValue() + Blocks * getBlockIncrement());
        }
    }
}

void ScrollBar::setMajorAxisScrollBarPosition(const Int16& Pos)
{
    
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    //Calculate the Value Based on the Bar Position
    Int32 ScrollValue( static_cast<Real32>(Pos - getScrollField()->getPosition()[MajorAxis])/static_cast<Real32>(getScrollField()->getSize()[MajorAxis]) * (getMaximum() - getMinimum()) );
    if(ScrollValue < getMinimum())
    {
        ScrollValue = getMinimum();
    }
    else if(ScrollValue + getExtent() > getMaximum())
    {
        ScrollValue = getMaximum() - getExtent();
    }
    _Model->setValue(ScrollValue);
}

void ScrollBar::mouseWheelMoved(const MouseWheelEvent& e)
{
    if(e.getScrollType() == MouseWheelEvent::BLOCK_SCROLL)
    {
        scrollBlock(-e.getScrollAmount());
    }
    else if(e.getScrollType() == MouseWheelEvent::UNIT_SCROLL)
    {
        scrollUnit(-e.getUnitsToScroll());
    }
    Container::mouseWheelMoved(e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ScrollBar::ScrollBar(void) :
    Inherited(),
        _Model(NULL),
        _BoundedRangeModelChangeListener(ScrollBarPtr(this)),
        _MinButtonActionListener(ScrollBarPtr(this)),
        _MaxButtonActionListener(ScrollBarPtr(this)),
        _ScrollBarListener(ScrollBarPtr(this)),
        _ScrollBarDraggedListener(ScrollBarPtr(this))
{
}

ScrollBar::ScrollBar(const ScrollBar &source) :
    Inherited(source),
        _Model(source._Model),
        _BoundedRangeModelChangeListener(ScrollBarPtr(this)),
        _MinButtonActionListener(ScrollBarPtr(this)),
        _MaxButtonActionListener(ScrollBarPtr(this)),
        _ScrollBarListener(ScrollBarPtr(this)),
        _ScrollBarDraggedListener(ScrollBarPtr(this))

{
    if(getMinButton() != NullFC &&
        getMaxButton() != NullFC &&
        getScrollBar() != NullFC &&
        getScrollField() != NullFC)
    {
        beginEditCP(ScrollBarPtr(this), MinButtonFieldMask | 
            MaxButtonFieldMask |
            ScrollBarFieldMask |
            ScrollFieldFieldMask);

        setMinButton(Button::Ptr::dcast(getMinButton()->shallowCopy()));
        setMaxButton(Button::Ptr::dcast(getMaxButton()->shallowCopy()));
        setScrollBar(Button::Ptr::dcast(getScrollBar()->shallowCopy()));
        setScrollField(UIDrawObjectCanvas::Ptr::dcast(getScrollField()->shallowCopy()));
        
        endEditCP(ScrollBarPtr(this), MinButtonFieldMask | 
            MaxButtonFieldMask |
            ScrollBarFieldMask |
            ScrollFieldFieldMask);
    }
}

ScrollBar::~ScrollBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScrollBar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if( (whichField & MinButtonFieldMask) ||
        (whichField & MaxButtonFieldMask) ||
        (whichField & ScrollBarFieldMask) ||
        (whichField & ScrollFieldFieldMask) )
    {
        beginEditCP(ScrollBarPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getScrollField() != NullFC) {getChildren().push_back(getScrollField());}
            if(getScrollBar() != NullFC) {getChildren().push_back(getScrollBar());}
            if(getMinButton() != NullFC) {getChildren().push_back(getMinButton());}
            if(getMaxButton() != NullFC) {getChildren().push_back(getMaxButton());}
        endEditCP(ScrollBarPtr(this), ChildrenFieldMask);
    }

    if((whichField & MinButtonFieldMask) &&
        getMinButton() != NullFC)
    {
        getMinButton()->addActionListener(&_MinButtonActionListener);
    }

    if((whichField & MaxButtonFieldMask) &&
        getMaxButton() != NullFC)
    {
        getMaxButton()->addActionListener(&_MaxButtonActionListener);
    }
    
    if((whichField & ScrollBarFieldMask) &&
        getScrollBar() != NullFC)
    {
        getScrollBar()->addMouseListener(&_ScrollBarListener);
    }
}

void ScrollBar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScrollBar NI" << std::endl;
}

void ScrollBar::BoundedRangeModelChangeListener::stateChanged(const ChangeEvent& e)
{
    _ScrollBar->updateScrollBarLayout();
}

void ScrollBar::MinButtonActionListener::actionPerformed(const ActionEvent& e)
{
    _ScrollBar->scrollUnit(-1);
}

void ScrollBar::MaxButtonActionListener::actionPerformed(const ActionEvent& e)
{
    _ScrollBar->scrollUnit(1);
}

void ScrollBar::ScrollBarListener::mousePressed(const MouseEvent& e)
{
	if(e.getButton() == e.BUTTON1)
	{
        _ScrollBar->_ScrollBarDraggedListener.setInitialMousePosition(ViewportToComponent(e.getLocation(), _ScrollBar, e.getViewport()));
        _ScrollBar->_ScrollBarDraggedListener.setInitialScrollBarPosition(_ScrollBar->getScrollBar()->getPosition());
        _ScrollBar->getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_ScrollBar->_ScrollBarDraggedListener));
        _ScrollBar->getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseListener(&(_ScrollBar->_ScrollBarDraggedListener));
    }
}

void ScrollBar::ScrollBarDraggedListener::mouseReleased(const MouseEvent& e)
{
	if(e.getButton() == e.BUTTON1)
	{
        _ScrollBar->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        _ScrollBar->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
    }
}

void ScrollBar::ScrollBarDraggedListener::mouseDragged(const MouseEvent& e)
{
	UInt32 AxisIndex(0);
    if(_ScrollBar->getOrientation() == HORIZONTAL_ALIGNMENT ) AxisIndex = 0;
    else  AxisIndex = 1;

    Pnt2s ComponentMousePosition(ViewportToComponent(e.getLocation(), _ScrollBar, e.getViewport()));

    _ScrollBar->setMajorAxisScrollBarPosition(
        _InitialScrollBarPosition[AxisIndex] + (ComponentMousePosition[AxisIndex] - _InitialMousePosition[AxisIndex]));
    //std::cout << "Diff "<< _InitialMousePosition[AxisIndex] - ComponentMousePosition[AxisIndex] << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSCROLLBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCROLLBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCROLLBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

