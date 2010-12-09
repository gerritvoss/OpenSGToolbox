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

#include "OSGScrollBar.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGInternalWindow.h"

#include "OSGUIDrawUtils.h"
#include "OSGDefaultBoundedRangeModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScrollBarBase.cpp file.
// To modify it, please change the .fcd file (OSGScrollBar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScrollBar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ScrollBar::updateLayout(void)
{
    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    Pnt2f TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);

    Pnt2f Position;
    Vec2f Size;

    //Min Button
    if(getMinButton() != NULL)
    {
        Size[MajorAxis] = getMinButton()->getPreferredSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position = TopLeft;

        if(getMinButton()->getPosition() != Position)
        {
            getMinButton()->setPosition(Position);
        }
        if(getMinButton()->getSize() != Size)
        {
            getMinButton()->setSize(Size);
        }
    }

    //Max Button
    if(getMaxButton() != NULL)
    {
        Size[MajorAxis] = getMaxButton()->getPreferredSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position = BottomRight - Size;

        if(getMaxButton()->getPosition() != Position)
        {
            getMaxButton()->setPosition(Position);
        }
        if(getMaxButton()->getSize() != Size)
        {
            getMaxButton()->setSize(Size);
        }
    }

    //Scroll Field
    if(getScrollField() != NULL)
    {
        Size[MajorAxis] = (BottomRight[MajorAxis] - TopLeft[MajorAxis]) - getMinButton()->getSize()[MajorAxis] - getMaxButton()->getSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position[MajorAxis] = getMinButton()->getPosition()[MajorAxis] + getMinButton()->getSize()[MajorAxis];
        Position[MinorAxis] = getMinButton()->getPosition()[MinorAxis];

        if(getScrollField()->getPosition() != Position)
        {
            getScrollField()->setPosition(Position);
        }
        if(getScrollField()->getSize() != Size)
        {
            getScrollField()->setSize(Size);
        }
    }

    //ScrollBar
    updateScrollBarLayout();
}

Pnt2f ScrollBar::calculateScrollBarPosition(void) const
{
    Pnt2f Position;

    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    Position[MajorAxis] = getScrollField()->getPosition()[MajorAxis] + 
        (static_cast<Real32>(getValue() - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum() - getExtent())) * (getScrollField()->getSize()[MajorAxis] - getScrollBar()->getSize()[MajorAxis]);
    Position[MinorAxis] = getScrollField()->getPosition()[MinorAxis];

    return Position;
}

Int32 ScrollBar::calculateValueFromPosition(const Pnt2f Position) const
{
    Int32 Value;

    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    Value = (Position[MajorAxis] - getScrollField()->getPosition()[MajorAxis])/(getScrollField()->getSize()[MajorAxis] - getScrollBar()->getSize()[MajorAxis])*static_cast<Real32>(getMaximum() - getMinimum() - getExtent()) + getMinimum();

    return Value;

}

Vec2f ScrollBar::calculateScrollBarSize(void) const
{
    Vec2f Size;

    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    Size[MajorAxis] = osgMax<Real32>( getScrollBarMinLength(),(static_cast<Real32>(getExtent())/static_cast<Real32>(getMaximum() - getMinimum())) * (getScrollField()->getSize()[MajorAxis]));
    Size[MinorAxis] = getScrollField()->getSize()[MinorAxis];

    return Size;
}

void ScrollBar::updateScrollBarLayout(void)
{
    if(getRangeModel() != NULL && getScrollBar() != NULL)
    {
        Vec2f Size(calculateScrollBarSize());
        if(getScrollBar()->getSize() != Size)
        {
            getScrollBar()->setSize(Size);
        }
        Pnt2f Pos(calculateScrollBarPosition());
        if(getScrollBar()->getPosition() != Pos)
        {
            getScrollBar()->setPosition(Pos);
        }
    }
}

void  ScrollBar::produceAdjustmentValueChanged(AdjustmentEventDetails* const Details)
{
    Inherited::produceAdjustmentValueChanged(Details);
}

void ScrollBar::scrollUnit(const Int32 Units)
{
    if(Units>0)
    {
        if(getRangeModel()->getValue() + getRangeModel()->getExtent() + Units * getUnitIncrement() > getRangeModel()->getMaximum())
        {
            getRangeModel()->setValue(getRangeModel()->getMaximum() - getRangeModel()->getExtent());
        }
        else
        {
            getRangeModel()->setValue(getRangeModel()->getValue() + Units * getUnitIncrement());
        }
    }
    else if(Units < 0)
    {
        if(getRangeModel()->getValue() + Units * static_cast<Int32>(getUnitIncrement()) < getRangeModel()->getMinimum())
        {
            getRangeModel()->setValue(getRangeModel()->getMinimum());
        }
        else
        {
            getRangeModel()->setValue(getRangeModel()->getValue() + Units * getUnitIncrement());
        }
    }
}

void ScrollBar::scrollBlock(const Int32 Blocks)
{
    if(Blocks>0)
    {
        if(getRangeModel()->getValue() + getRangeModel()->getExtent() + Blocks * getBlockIncrement() > getRangeModel()->getMaximum())
        {
            getRangeModel()->setValue(getRangeModel()->getMaximum() - getRangeModel()->getExtent());
        }
        else
        {
            getRangeModel()->setValue(getRangeModel()->getValue() + Blocks * getBlockIncrement());
        }
    }
    else if(Blocks < 0)
    {
        if(getRangeModel()->getValue() + Blocks * getBlockIncrement() < getRangeModel()->getMinimum())
        {
            getRangeModel()->setValue(getRangeModel()->getMinimum());
        }
        else
        {
            getRangeModel()->setValue(getRangeModel()->getValue() + Blocks * getBlockIncrement());
        }
    }
}

void ScrollBar::setMajorAxisScrollBarPosition(const Pnt2f& Pos)
{

    UInt16 MajorAxis, MinorAxis;
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    MinorAxis = (MajorAxis+1)%2;

    //Calculate the Value Based on the Bar Position
    //Int32 ScrollValue( static_cast<Real32>(Pos - getScrollField()->getPosition()[MajorAxis])/static_cast<Real32>(getScrollField()->getSize()[MajorAxis]) * (getMaximum() - getMinimum()) + getMinimum());
    Int32 ScrollValue(calculateValueFromPosition(Pos));
    if(ScrollValue < getMinimum())
    {
        ScrollValue = getMinimum();
    }
    else if(ScrollValue + getExtent() > getMaximum())
    {
        ScrollValue = getMaximum() - getExtent();
    }
    getRangeModel()->setValue(ScrollValue);
}

void ScrollBar::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    if(getEnabled())
    {
        if(e->getScrollType() == MouseWheelEventDetails::BLOCK_SCROLL)
        {
            scrollBlock(-e->getScrollAmount());
        }
        else if(e->getScrollType() == MouseWheelEventDetails::UNIT_SCROLL)
        {
            scrollUnit(-e->getUnitsToScroll());
        }
    }
    ComponentContainer::mouseWheelMoved(e);
}

Button* ScrollBar::getMinButton(void) const
{
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        return getVerticalMinButton();
    }
    else
    {
        return getHorizontalMinButton();
    }
}

Button* ScrollBar::getMaxButton(void) const
{
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        return getVerticalMaxButton();
    }
    else
    {
        return getHorizontalMaxButton();
    }
}

Button* ScrollBar::getScrollField(void) const
{
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        return getVerticalScrollField();
    }
    else
    {
        return getHorizontalScrollField();
    }
}

Button* ScrollBar::getScrollBar(void) const
{
    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        return getVerticalScrollBar();
    }
    else
    {
        return getHorizontalScrollBar();
    }
}

void ScrollBar::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _ScrollBarDragMouseDraggedConnection.disconnect();
    _ScrollBarDragMouseReleasedConnection.disconnect();
}

void ScrollBar::setRangeModel(BoundedRangeModel * const value)
{
    _RangeModelConnection.disconnect();
    Inherited::setRangeModel(value);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ScrollBar::onCreate(const ScrollBar * Id)
{
	Inherited::onCreate(Id);

    DefaultBoundedRangeModelUnrecPtr TheModel(DefaultBoundedRangeModel::create());
    setRangeModel(TheModel);

    if(Id != NULL)
    {
        if(Id->getVerticalMinButton() != NULL &&
            Id->getVerticalMaxButton() != NULL &&
            Id->getVerticalScrollBar() != NULL &&
            Id->getVerticalScrollField() != NULL)
        {
            FieldContainerUnrecPtr TempPtr(Id->getVerticalMinButton()->shallowCopy());
            setVerticalMinButton(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getVerticalMaxButton()->shallowCopy();
            setVerticalMaxButton(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getVerticalScrollBar()->shallowCopy();
            setVerticalScrollBar(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getVerticalScrollField()->shallowCopy();
            setVerticalScrollField(dynamic_pointer_cast<Button>(TempPtr));
        }
        
        if(Id->getHorizontalMinButton() != NULL &&
            Id->getHorizontalMaxButton() != NULL &&
            Id->getHorizontalScrollBar() != NULL &&
            Id->getHorizontalScrollField() != NULL)
        {
            FieldContainerUnrecPtr TempPtr(Id->getHorizontalMinButton()->shallowCopy());
            setHorizontalMinButton(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getHorizontalMaxButton()->shallowCopy();
            setHorizontalMaxButton(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getHorizontalScrollBar()->shallowCopy();
            setHorizontalScrollBar(dynamic_pointer_cast<Button>(TempPtr));

            TempPtr = Id->getHorizontalScrollField()->shallowCopy();
            setHorizontalScrollField(dynamic_pointer_cast<Button>(TempPtr));
        }
    }
}

void ScrollBar::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

ScrollBar::ScrollBar(void) :
    Inherited()
{
}

ScrollBar::ScrollBar(const ScrollBar &source) :
    Inherited(source)
{
}

ScrollBar::~ScrollBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScrollBar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

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
            clearChildren();
            if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
            {
                if(getVerticalScrollField() != NULL) {pushToChildren(getVerticalScrollField());}
                if(getVerticalScrollBar() != NULL) {pushToChildren(getVerticalScrollBar());}
                if(getVerticalMinButton() != NULL) {pushToChildren(getVerticalMinButton());}
                if(getVerticalMaxButton() != NULL) {pushToChildren(getVerticalMaxButton());}
            }
            else
            {
                if(getHorizontalScrollField() != NULL) {pushToChildren(getHorizontalScrollField());}
                if(getHorizontalScrollBar() != NULL) {pushToChildren(getHorizontalScrollBar());}
                if(getHorizontalMinButton() != NULL) {pushToChildren(getHorizontalMinButton());}
                if(getHorizontalMaxButton() != NULL) {pushToChildren(getHorizontalMaxButton());}
            }
    }

    if(getOrientation() == ScrollBar::VERTICAL_ORIENTATION)
    {
        if(whichField & VerticalMinButtonFieldMask)
        {
            _MinActionConnection.disconnect();
            if(getVerticalMinButton() != NULL)
            {
                _MinActionConnection = getVerticalMinButton()->connectMousePressedActionPerformed(boost::bind(&ScrollBar::handleMinButtonAction, this, _1));
            }
        }

        if(whichField & VerticalMaxButtonFieldMask)
        {
            _MaxActionConnection.disconnect();
            if(getVerticalMaxButton() != NULL)
            {
                _MaxActionConnection = getVerticalMaxButton()->connectMousePressedActionPerformed(boost::bind(&ScrollBar::handleMaxButtonAction, this, _1));
            }
        }
        
        if(whichField & VerticalScrollBarFieldMask)
        {
            _ScrollBarMousePressedConnection.disconnect();
            if(getVerticalScrollBar() != NULL)
            {
                _ScrollBarMousePressedConnection = getVerticalScrollBar()->connectMousePressed(boost::bind(&ScrollBar::handleScrollBarMousePressed, this, _1));
            }
        }
        
        if(whichField & VerticalScrollFieldFieldMask)
        {
            _ScrollFieldActionConnection.disconnect();
            if(getVerticalScrollField() != NULL)
            {
                _ScrollFieldActionConnection = getVerticalScrollField()->connectActionPerformed(boost::bind(&ScrollBar::handleScrollFieldAction, this, _1));
            }
        }
    }
    else
    {
        if(whichField & HorizontalMinButtonFieldMask)
        {
            _MinActionConnection.disconnect();
            if(getHorizontalMinButton() != NULL)
            {
                _MinActionConnection = getHorizontalMinButton()->connectMousePressedActionPerformed(boost::bind(&ScrollBar::handleMinButtonAction, this, _1));
            }
        }

        if(whichField & HorizontalMaxButtonFieldMask)
        {
            _MaxActionConnection.disconnect();
            if(getHorizontalMaxButton() != NULL)
            {
                _MaxActionConnection = getHorizontalMaxButton()->connectMousePressedActionPerformed(boost::bind(&ScrollBar::handleMaxButtonAction, this, _1));
            }
        }
        
        if(whichField & HorizontalScrollBarFieldMask)
        {
            _ScrollBarMousePressedConnection.disconnect();
            if(getHorizontalScrollBar() != NULL)
            {
                _ScrollBarMousePressedConnection = getHorizontalScrollBar()->connectMousePressed(boost::bind(&ScrollBar::handleScrollBarMousePressed, this, _1));
            }
        }
        
        if(whichField & HorizontalScrollFieldFieldMask)
        {
            _ScrollFieldActionConnection.disconnect();
            if(getHorizontalScrollField() != NULL)
            {
                _ScrollFieldActionConnection = getHorizontalScrollField()->connectActionPerformed(boost::bind(&ScrollBar::handleScrollFieldAction, this, _1));
            }
        }
    }

	if(whichField & EnabledFieldMask)
	{
		if(getVerticalMinButton() != NULL)
		{
				getVerticalMinButton()->setEnabled(getEnabled());
		}
		if(getVerticalMaxButton() != NULL)
		{
				getVerticalMaxButton()->setEnabled(getEnabled());
		}
		if(getVerticalScrollBar() != NULL)
		{
				getVerticalScrollBar()->setEnabled(getEnabled());
		}
		if(getVerticalScrollField() != NULL)
		{
				getVerticalScrollField()->setEnabled(getEnabled());
		}
		if(getHorizontalMinButton() != NULL)
		{
				getHorizontalMinButton()->setEnabled(getEnabled());
		}
		if(getHorizontalMaxButton() != NULL)
		{
				getHorizontalMaxButton()->setEnabled(getEnabled());
		}
		if(getHorizontalScrollBar() != NULL)
		{
				getHorizontalScrollBar()->setEnabled(getEnabled());
		}
		if(getHorizontalScrollField() != NULL)
		{
				getHorizontalScrollField()->setEnabled(getEnabled());
		}
	}
    if(whichField & RangeModelFieldMask)
    {
        _RangeModelConnection.disconnect();
        if(getRangeModel() != NULL)
        {
            _RangeModelConnection = getRangeModel()->connectStateChanged(boost::bind(&ScrollBar::handleRangeModelStateChanged, this, _1));
        }
    }
}

void ScrollBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScrollBar NI" << std::endl;
}

void ScrollBar::handleRangeModelStateChanged(ChangeEventDetails* const e)
{
    updateScrollBarLayout();
}

void ScrollBar::handleMinButtonAction(ActionEventDetails* const e)
{
	if(getEnabled())
	{
		scrollUnit(-1);
	}
}

void ScrollBar::handleMaxButtonAction(ActionEventDetails* const e)
{
	if(getEnabled())
	{
		scrollUnit(1);
	}
}

void ScrollBar::handleScrollBarMousePressed(MouseEventDetails* const e)
{
    if(getEnabled() && e->getButton() == MouseEventDetails::BUTTON1)
	{
        _ScrollBarInitialMousePosition = ViewportToComponent(e->getLocation(), this, e->getViewport());
        _ScrollBarInitialScrollBarPosition = getScrollBar()->getPosition();

        _ScrollBarDragMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&ScrollBar::handleScrollBarDragMouseDragged, this, _1));
        _ScrollBarDragMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&ScrollBar::handleScrollBarDragMouseReleased, this, _1));
    }
}

void ScrollBar::handleScrollBarDragMouseReleased(MouseEventDetails* const e)
{
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
        _ScrollBarDragMouseDraggedConnection.disconnect();
        _ScrollBarDragMouseReleasedConnection.disconnect();
    }
}

void ScrollBar::handleScrollBarDragMouseDragged(MouseEventDetails* const e)
{
    Pnt2f ComponentMousePosition(ViewportToComponent(e->getLocation(), this, e->getViewport()));

    setMajorAxisScrollBarPosition(_ScrollBarInitialScrollBarPosition + (ComponentMousePosition - _ScrollBarInitialMousePosition));
}


void ScrollBar::handleScrollFieldAction(ActionEventDetails* const e)
{
	if(getEnabled())
	{
		UInt32 AxisIndex(0);
		if(getOrientation() == ScrollBar::HORIZONTAL_ORIENTATION ) AxisIndex = 0;
		else  AxisIndex = 1;

		Pnt2f ComponentMousePosition(DrawingSurfaceToComponent(getParentWindow()->getParentDrawingSurface()->getMousePosition(), this));
		//Is Mouse Major axis on the min or max side of the scroll bar
		if(ComponentMousePosition[AxisIndex] < getScrollBar()->getPosition()[AxisIndex])
		{
			//Move the Bounded range model one block in the Min direction
			scrollBlock(-1);
		}
		else if(ComponentMousePosition[AxisIndex] > 
			(getScrollBar()->getPosition()[AxisIndex] + getScrollBar()->getSize()[AxisIndex]))
		{
			//Move the Bounded range model one block in the Max direction
			scrollBlock(1);
		}
	}
}

OSG_END_NAMESPACE
