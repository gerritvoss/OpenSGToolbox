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

ButtonPtr ScrollBar::getMinButton(void)
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        return getVerticalMinButton();
    }
    else
    {
        return getHorizontalMinButton();
    }
}

ButtonPtr ScrollBar::getMaxButton(void)
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        return getVerticalMaxButton();
    }
    else
    {
        return getHorizontalMaxButton();
    }
}

ButtonPtr ScrollBar::getScrollField(void)
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        return getVerticalScrollField();
    }
    else
    {
        return getHorizontalScrollField();
    }
}

ButtonPtr ScrollBar::getScrollBar(void)
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        return getVerticalScrollBar();
    }
    else
    {
        return getHorizontalScrollBar();
    }
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
        _ScrollBarDraggedListener(ScrollBarPtr(this)),
        _ScrollFieldListener(ScrollBarPtr(this))
{
}

ScrollBar::ScrollBar(const ScrollBar &source) :
    Inherited(source),
        _Model(source._Model),
        _BoundedRangeModelChangeListener(ScrollBarPtr(this)),
        _MinButtonActionListener(ScrollBarPtr(this)),
        _MaxButtonActionListener(ScrollBarPtr(this)),
        _ScrollBarListener(ScrollBarPtr(this)),
        _ScrollBarDraggedListener(ScrollBarPtr(this)),
        _ScrollFieldListener(ScrollBarPtr(this))

{
    if(getVerticalMinButton() != NullFC &&
        getVerticalMaxButton() != NullFC &&
        getVerticalScrollBar() != NullFC &&
        getVerticalScrollField() != NullFC)
    {
        beginEditCP(ScrollBarPtr(this), VerticalMinButtonFieldMask | 
            VerticalMaxButtonFieldMask |
            VerticalScrollBarFieldMask |
            VerticalScrollFieldFieldMask);

        setVerticalMinButton(Button::Ptr::dcast(getVerticalMinButton()->shallowCopy()));
        setVerticalMaxButton(Button::Ptr::dcast(getVerticalMaxButton()->shallowCopy()));
        setVerticalScrollBar(Button::Ptr::dcast(getVerticalScrollBar()->shallowCopy()));
        setVerticalScrollField(Button::Ptr::dcast(getVerticalScrollField()->shallowCopy()));
        
        endEditCP(ScrollBarPtr(this), VerticalMinButtonFieldMask | 
            VerticalMaxButtonFieldMask |
            VerticalScrollBarFieldMask |
            VerticalScrollFieldFieldMask);
    }
    
    if(getHorizontalMinButton() != NullFC &&
        getHorizontalMaxButton() != NullFC &&
        getHorizontalScrollBar() != NullFC &&
        getHorizontalScrollField() != NullFC)
    {
        beginEditCP(ScrollBarPtr(this), HorizontalMinButtonFieldMask | 
            HorizontalMaxButtonFieldMask |
            HorizontalScrollBarFieldMask |
            HorizontalScrollFieldFieldMask);

        setHorizontalMinButton(Button::Ptr::dcast(getHorizontalMinButton()->shallowCopy()));
        setHorizontalMaxButton(Button::Ptr::dcast(getHorizontalMaxButton()->shallowCopy()));
        setHorizontalScrollBar(Button::Ptr::dcast(getHorizontalScrollBar()->shallowCopy()));
        setHorizontalScrollField(Button::Ptr::dcast(getHorizontalScrollField()->shallowCopy()));
        
        endEditCP(ScrollBarPtr(this), HorizontalMinButtonFieldMask | 
            HorizontalMaxButtonFieldMask |
            HorizontalScrollBarFieldMask |
            HorizontalScrollFieldFieldMask);
    }
}

ScrollBar::~ScrollBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScrollBar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if( (whichField & VerticalMinButtonFieldMask) ||
        (whichField & VerticalMaxButtonFieldMask) ||
        (whichField & VerticalScrollBarFieldMask) ||
        (whichField & VerticalScrollFieldFieldMask)||
        (whichField & HorizontalMinButtonFieldMask) ||
        (whichField & HorizontalMaxButtonFieldMask) ||
        (whichField & HorizontalScrollBarFieldMask) ||
        (whichField & HorizontalScrollFieldFieldMask) ||
        (whichField & OrientationFieldMask) )
    {
        beginEditCP(ScrollBarPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getOrientation() == VERTICAL_ALIGNMENT)
            {
                if(getVerticalScrollField() != NullFC) {getChildren().push_back(getVerticalScrollField());}
                if(getVerticalScrollBar() != NullFC) {getChildren().push_back(getVerticalScrollBar());}
                if(getVerticalMinButton() != NullFC) {getChildren().push_back(getVerticalMinButton());}
                if(getVerticalMaxButton() != NullFC) {getChildren().push_back(getVerticalMaxButton());}
            }
            else
            {
                if(getHorizontalScrollField() != NullFC) {getChildren().push_back(getHorizontalScrollField());}
                if(getHorizontalScrollBar() != NullFC) {getChildren().push_back(getHorizontalScrollBar());}
                if(getHorizontalMinButton() != NullFC) {getChildren().push_back(getHorizontalMinButton());}
                if(getHorizontalMaxButton() != NullFC) {getChildren().push_back(getHorizontalMaxButton());}
            }
        endEditCP(ScrollBarPtr(this), ChildrenFieldMask);
    }

    if((whichField & VerticalMinButtonFieldMask) &&
        getVerticalMinButton() != NullFC)
    {
        getVerticalMinButton()->addMousePressedActionListener(&_MinButtonActionListener);
    }

    if((whichField & VerticalMaxButtonFieldMask) &&
        getVerticalMaxButton() != NullFC)
    {
        getVerticalMaxButton()->addMousePressedActionListener(&_MaxButtonActionListener);
    }
    
    if((whichField & VerticalScrollBarFieldMask) &&
        getVerticalScrollBar() != NullFC)
    {
        getVerticalScrollBar()->addMouseListener(&_ScrollBarListener);
    }
    
    if((whichField & VerticalScrollFieldFieldMask) &&
        getVerticalScrollField() != NullFC)
    {
        getVerticalScrollField()->addMousePressedActionListener(&_ScrollFieldListener);
    }
    
    if((whichField & HorizontalMinButtonFieldMask) &&
        getHorizontalMinButton() != NullFC)
    {
        getHorizontalMinButton()->addMousePressedActionListener(&_MinButtonActionListener);
    }

    if((whichField & HorizontalMaxButtonFieldMask) &&
        getHorizontalMaxButton() != NullFC)
    {
        getHorizontalMaxButton()->addMousePressedActionListener(&_MaxButtonActionListener);
    }
    
    if((whichField & HorizontalScrollBarFieldMask) &&
        getHorizontalScrollBar() != NullFC)
    {
        getHorizontalScrollBar()->addMouseListener(&_ScrollBarListener);
    }
    
    if((whichField & HorizontalScrollFieldFieldMask) &&
        getHorizontalScrollField() != NullFC)
    {
        getHorizontalScrollField()->addMousePressedActionListener(&_ScrollFieldListener);
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


void ScrollBar::ScrollFieldListener::actionPerformed(const ActionEvent& e)
{
	UInt32 AxisIndex(0);
    if(_ScrollBar->getOrientation() == HORIZONTAL_ALIGNMENT ) AxisIndex = 0;
    else  AxisIndex = 1;

    Pnt2s ComponentMousePosition(DrawingSurfaceToComponent(_ScrollBar->getParentFrame()->getDrawingSurface()->getMousePosition(), _ScrollBar));
    //Is Mouse Major axis on the min or max side of the scroll bar
    if(ComponentMousePosition[AxisIndex] < _ScrollBar->getScrollBar()->getPosition()[AxisIndex])
    {
        //Move the Bounded range model one block in the Min direction
        _ScrollBar->scrollBlock(-1);
    }
    else if(ComponentMousePosition[AxisIndex] > 
        (_ScrollBar->getScrollBar()->getPosition()[AxisIndex] + _ScrollBar->getScrollBar()->getSize()[AxisIndex]))
    {
        //Move the Bounded range model one block in the Max direction
        _ScrollBar->scrollBlock(1);
    }
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

