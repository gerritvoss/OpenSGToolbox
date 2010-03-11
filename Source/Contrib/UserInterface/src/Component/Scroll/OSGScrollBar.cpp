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

EventConnection ScrollBar::addAdjustmentListener(AdjustmentListenerPtr Listener)
{
    _AdjustmentListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&ScrollBar::isAdjustmentListenerAttached, this, Listener),
                           boost::bind(&ScrollBar::removeAdjustmentListener, this, Listener));
}

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
    if(editMinButton() != NULL)
    {
        Size[MajorAxis] = editMinButton()->getPreferredSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position = TopLeft;

        editMinButton()->setPosition(Position);
        editMinButton()->setSize(Size);
    }

    //Max Button
    if(editMaxButton() != NULL)
    {
        Size[MajorAxis] = editMaxButton()->getPreferredSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position = BottomRight - Size;

        editMaxButton()->setPosition(Position);
        editMaxButton()->setSize(Size);
    }

    //Scroll Field
    if(editScrollField() != NULL)
    {
        Size[MajorAxis] = (BottomRight[MajorAxis] - TopLeft[MajorAxis]) - editMinButton()->getSize()[MajorAxis] - editMaxButton()->getSize()[MajorAxis];
        Size[MinorAxis] = BottomRight[MinorAxis] - TopLeft[MinorAxis];

        Position[MajorAxis] = editMinButton()->getPosition()[MajorAxis] + editMinButton()->getSize()[MajorAxis];
        Position[MinorAxis] = editMinButton()->getPosition()[MinorAxis];

        editScrollField()->setPosition(Position);
        editScrollField()->setSize(Size);
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

    Position[MajorAxis] = editScrollField()->getPosition()[MajorAxis] + 
        (static_cast<Real32>(getValue() - getMinimum())/static_cast<Real32>(getMaximum() - getMinimum() - getExtent())) * (editScrollField()->getSize()[MajorAxis] - editScrollBar()->getSize()[MajorAxis]);
    Position[MinorAxis] = editScrollField()->getPosition()[MinorAxis];

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

    Value = (Position[MajorAxis] - editScrollField()->getPosition()[MajorAxis])/(editScrollField()->getSize()[MajorAxis] - editScrollBar()->getSize()[MajorAxis])*static_cast<Real32>(getMaximum() - getMinimum() - getExtent()) + getMinimum();

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

    Size[MajorAxis] = osgMax<Real32>( getScrollBarMinLength(),(static_cast<Real32>(getExtent())/static_cast<Real32>(getMaximum() - getMinimum())) * (editScrollField()->getSize()[MajorAxis]));
    Size[MinorAxis] = editScrollField()->getSize()[MinorAxis];

    return Size;
}

void ScrollBar::updateScrollBarLayout(void)
{
    if(getRangeModel() != NULL && editScrollBar() != NULL)
    {
        editScrollBar()->setSize(calculateScrollBarSize());
        editScrollBar()->setPosition(calculateScrollBarPosition());
    }
}

void  ScrollBar::produceAdjustmentValueChanged(const AdjustmentEventUnrecPtr e)
{
    for(AdjustmentListenerSetConstItor SetItor(_AdjustmentListeners.begin()) ; SetItor != _AdjustmentListeners.end() ; ++SetItor)
    {
        (*SetItor)->adjustmentValueChanged(e);
    }
    _Producer.produceEvent(AdjustmentValueChangedMethodId,e);
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
    //Int32 ScrollValue( static_cast<Real32>(Pos - editScrollField()->getPosition()[MajorAxis])/static_cast<Real32>(editScrollField()->getSize()[MajorAxis]) * (getMaximum() - getMinimum()) + getMinimum());
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

void ScrollBar::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    if(getEnabled())
    {
        if(e->getScrollType() == MouseWheelEvent::BLOCK_SCROLL)
        {
            scrollBlock(-e->getScrollAmount());
        }
        else if(e->getScrollType() == MouseWheelEvent::UNIT_SCROLL)
        {
            scrollUnit(-e->getUnitsToScroll());
        }
    }
    ComponentContainer::mouseWheelMoved(e);
}

Button* ScrollBar::editMinButton(void) const
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

Button* ScrollBar::editMaxButton(void) const
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

Button* ScrollBar::editScrollField(void) const
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

Button* ScrollBar::editScrollBar(void) const
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
    _ScrollBarDraggedListener.disconnect();
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
}

void ScrollBar::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

ScrollBar::ScrollBar(void) :
    Inherited(),
    _BoundedRangeModelChangeListener(this),
    _MinButtonActionListener(this),
    _MaxButtonActionListener(this),
    _ScrollBarListener(this),
    _ScrollBarDraggedListener(this),
    _ScrollFieldListener(this)
{
}

ScrollBar::ScrollBar(const ScrollBar &source) :
    Inherited(source),
    _BoundedRangeModelChangeListener(this),
    _MinButtonActionListener(this),
    _MaxButtonActionListener(this),
    _ScrollBarListener(this),
    _ScrollBarDraggedListener(this),
    _ScrollFieldListener(this)
{
    if(getVerticalMinButton() != NULL &&
        getVerticalMaxButton() != NULL &&
        getVerticalScrollBar() != NULL &&
        getVerticalScrollField() != NULL)
    {
        FieldContainerUnrecPtr TempPtr(getVerticalMinButton()->shallowCopy());
        setVerticalMinButton(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getVerticalMaxButton()->shallowCopy();
        setVerticalMaxButton(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getVerticalScrollBar()->shallowCopy();
        setVerticalScrollBar(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getVerticalScrollField()->shallowCopy();
        setVerticalScrollField(dynamic_pointer_cast<Button>(TempPtr));
    }
    
    if(getHorizontalMinButton() != NULL &&
        getHorizontalMaxButton() != NULL &&
        getHorizontalScrollBar() != NULL &&
        getHorizontalScrollField() != NULL)
    {
        FieldContainerUnrecPtr TempPtr(getHorizontalMinButton()->shallowCopy());
        setHorizontalMinButton(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getHorizontalMaxButton()->shallowCopy();
        setHorizontalMaxButton(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getHorizontalScrollBar()->shallowCopy();
        setHorizontalScrollBar(dynamic_pointer_cast<Button>(TempPtr));

        TempPtr = getHorizontalScrollField()->shallowCopy();
        setHorizontalScrollField(dynamic_pointer_cast<Button>(TempPtr));
    }
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

    if((whichField & VerticalMinButtonFieldMask) &&
        getVerticalMinButton() != NULL)
    {
        getVerticalMinButton()->addMousePressedActionListener(&_MinButtonActionListener);
    }

    if((whichField & VerticalMaxButtonFieldMask) &&
        getVerticalMaxButton() != NULL)
    {
        getVerticalMaxButton()->addMousePressedActionListener(&_MaxButtonActionListener);
    }
    
    if((whichField & VerticalScrollBarFieldMask) &&
        getVerticalScrollBar() != NULL)
    {
        getVerticalScrollBar()->addMouseListener(&_ScrollBarListener);
    }
    
    if((whichField & VerticalScrollFieldFieldMask) &&
        getVerticalScrollField() != NULL)
    {
        getVerticalScrollField()->addMousePressedActionListener(&_ScrollFieldListener);
    }
    
    if((whichField & HorizontalMinButtonFieldMask) &&
        getHorizontalMinButton() != NULL)
    {
        getHorizontalMinButton()->addMousePressedActionListener(&_MinButtonActionListener);
    }

    if((whichField & HorizontalMaxButtonFieldMask) &&
        getHorizontalMaxButton() != NULL)
    {
        getHorizontalMaxButton()->addMousePressedActionListener(&_MaxButtonActionListener);
    }
    
    if((whichField & HorizontalScrollBarFieldMask) &&
        getHorizontalScrollBar() != NULL)
    {
        getHorizontalScrollBar()->addMouseListener(&_ScrollBarListener);
    }
    
    if((whichField & HorizontalScrollFieldFieldMask) &&
        getHorizontalScrollField() != NULL)
    {
        getHorizontalScrollField()->addMousePressedActionListener(&_ScrollFieldListener);
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
        if(getRangeModel() != NULL)
        {
            _RangeModelConnection = getRangeModel()->addChangeListener(&_BoundedRangeModelChangeListener);
        }
    }
}

void ScrollBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScrollBar NI" << std::endl;
}

void ScrollBar::BoundedRangeModelChangeListener::stateChanged(const ChangeEventUnrecPtr e)
{
    _ScrollBar->updateScrollBarLayout();
}

void ScrollBar::MinButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	if(_ScrollBar->getEnabled())
	{
		_ScrollBar->scrollUnit(-1);
	}
}

void ScrollBar::MaxButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	if(_ScrollBar->getEnabled())
	{
		_ScrollBar->scrollUnit(1);
	}
}

void ScrollBar::ScrollBarListener::mousePressed(const MouseEventUnrecPtr e)
{
	if(_ScrollBar->getEnabled() && e->getButton() == e->BUTTON1)
	{
        _ScrollBar->_ScrollBarDraggedListener.setInitialMousePosition(ViewportToComponent(e->getLocation(), _ScrollBar, e->getViewport()));
        _ScrollBar->_ScrollBarDraggedListener.setInitialScrollBarPosition(_ScrollBar->editScrollBar()->getPosition());
        _ScrollBar->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_ScrollBar->_ScrollBarDraggedListener));
        _ScrollBar->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&(_ScrollBar->_ScrollBarDraggedListener));
    }
}

void ScrollBar::ScrollBarDraggedListener::mouseReleased(const MouseEventUnrecPtr e)
{
	if(e->getButton() == e->BUTTON1)
	{
        disconnect();
    }
}

void ScrollBar::ScrollBarDraggedListener::disconnect(void)
{
    _ScrollBar->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    _ScrollBar->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
}

void ScrollBar::ScrollBarDraggedListener::mouseDragged(const MouseEventUnrecPtr e)
{
    Pnt2f ComponentMousePosition(ViewportToComponent(e->getLocation(), _ScrollBar, e->getViewport()));

    _ScrollBar->setMajorAxisScrollBarPosition(_InitialScrollBarPosition + (ComponentMousePosition - _InitialMousePosition));
    //std::cout << "Diff "<< _InitialMousePosition[AxisIndex] - ComponentMousePosition[AxisIndex] << std::endl;
}


void ScrollBar::ScrollFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
	if(_ScrollBar->getEnabled())
	{
		UInt32 AxisIndex(0);
		if(_ScrollBar->getOrientation() == ScrollBar::HORIZONTAL_ORIENTATION ) AxisIndex = 0;
		else  AxisIndex = 1;

		Pnt2f ComponentMousePosition(DrawingSurfaceToComponent(_ScrollBar->getParentWindow()->getDrawingSurface()->getMousePosition(), _ScrollBar));
		//Is Mouse Major axis on the min or max side of the scroll bar
		if(ComponentMousePosition[AxisIndex] < _ScrollBar->editScrollBar()->getPosition()[AxisIndex])
		{
			//Move the Bounded range model one block in the Min direction
			_ScrollBar->scrollBlock(-1);
		}
		else if(ComponentMousePosition[AxisIndex] > 
			(_ScrollBar->editScrollBar()->getPosition()[AxisIndex] + _ScrollBar->editScrollBar()->getSize()[AxisIndex]))
		{
			//Move the Bounded range model one block in the Max direction
			_ScrollBar->scrollBlock(1);
		}
	}
}

OSG_END_NAMESPACE
