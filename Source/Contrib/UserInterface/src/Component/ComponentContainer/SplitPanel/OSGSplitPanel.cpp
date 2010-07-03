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

#include "OSGSplitPanel.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawUtils.h"

#include "OSGSplitPanel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSplitPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGSplitPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SplitPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SplitPanel::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{
    // draw the two contained components and the divider
    if (getMinComponent() != NULL)
        getMinComponent()->draw(Graphics, getOpacity()*Opacity);
    if (getMaxComponent() != NULL)
        getMaxComponent()->draw(Graphics, getOpacity()*Opacity);
    if (getDividerDrawObject() != NULL)
        getDividerDrawObject()->draw(Graphics, getOpacity()*Opacity);
}

void SplitPanel::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
    Vec2f BorderSize(BottomRight - TopLeft);

    UInt32 AxisIndex(0);
    if(getOrientation() != SplitPanel::HORIZONTAL_ORIENTATION ) AxisIndex = 1;

    Vec2f minSize(0,0);
    Vec2f maxSize(0,0);
    Vec2f divSize(0,0);
    Pnt2f minPos(0,0);
    Pnt2f maxPos(0,0);
    Pnt2f divPos(0,0);

    if (getDividerPosition() < 0.0)
        setDividerPosition(0.5);
    if (getMinDividerPosition() < 0.0)
        setMinDividerPosition(0.0);
    if (getMaxDividerPosition() < 0.0)
        setMaxDividerPosition(1.0);

    UInt32 dividerPosition(getDividerPosition());
    if (getDividerPosition() <= 1.0)
        dividerPosition = BorderSize[AxisIndex] * getDividerPosition();

    // check the divider's min and max
    if (getMinDividerPosition() <= 1.0)
    {
        if (dividerPosition < getMinDividerPosition() * BorderSize[AxisIndex])
            dividerPosition = getMinDividerPosition() * BorderSize[AxisIndex];
    }
    else
    {
        if (dividerPosition < getMinDividerPosition())
            dividerPosition = getMinDividerPosition();
    }
    if (getMaxDividerPosition() <= 1.0)
    {
        if (dividerPosition > getMaxDividerPosition() * BorderSize[AxisIndex])
            dividerPosition = getMaxDividerPosition() * BorderSize[AxisIndex];
    }
    else
    {
        if (dividerPosition > getMaxDividerPosition())
            dividerPosition = getMaxDividerPosition();
    }

    // set the minimum component's size
    minSize[AxisIndex] = dividerPosition - getDividerSize()/2;

    // check its min and max
    if (getMinComponent() != NULL)
    {
        if (minSize[AxisIndex] < getMinComponent()->getMinSize()[AxisIndex])
        {
            dividerPosition -= getMinComponent()->getMinSize()[AxisIndex] - minSize[AxisIndex];
            minSize[AxisIndex] = getMinComponent()->getMinSize()[AxisIndex];
        }
        if (minSize[AxisIndex] > getMinComponent()->getMaxSize()[AxisIndex])
        {
            dividerPosition += minSize[AxisIndex] - getMinComponent()->getMaxSize()[AxisIndex];
            minSize[AxisIndex] = getMinComponent()->getMaxSize()[AxisIndex];
        }
    }

    // set the maximum component's size
    maxSize[AxisIndex] = BorderSize[AxisIndex] - minSize[AxisIndex] - getDividerSize();

    // check its min and max
    if (getMaxComponent() != NULL)
    {
        if (maxSize[AxisIndex] < getMaxComponent()->getMinSize()[AxisIndex])
        {
            dividerPosition -= getMaxComponent()->getMinSize()[AxisIndex] - maxSize[AxisIndex];
            minSize[AxisIndex] -= getMaxComponent()->getMinSize()[AxisIndex] - maxSize[AxisIndex];
            maxSize[AxisIndex] = getMaxComponent()->getMinSize()[AxisIndex];
        }
        if (maxSize[AxisIndex] > getMaxComponent()->getMaxSize()[AxisIndex])
        {
            dividerPosition += maxSize[AxisIndex] - getMaxComponent()->getMaxSize()[AxisIndex];
            minSize[AxisIndex] += maxSize[AxisIndex] - getMaxComponent()->getMaxSize()[AxisIndex];
            maxSize[AxisIndex] = getMaxComponent()->getMaxSize()[AxisIndex];
        }
    }

    // set the minor axis' size and max's position
    minSize[(AxisIndex+1)%2] = maxSize[(AxisIndex+1)%2] = BorderSize[(AxisIndex+1)%2];
    maxPos[AxisIndex] = minSize[AxisIndex] + getDividerSize();

    // set the divider's size and position
    divSize[AxisIndex] = getDividerSize();
    divSize[(AxisIndex+1)%2] = BorderSize[(AxisIndex+1)%2];
    divPos[AxisIndex] = dividerPosition - getDividerSize()/2;

    // set the components to the right size and positions
    if (getMinComponent() != NULL)
    {
        getMinComponent()->setSize(minSize);
        getMinComponent()->setPosition(minPos);
    }
    if (getMaxComponent() != NULL)
    {
        getMaxComponent()->setSize(maxSize);
        getMaxComponent()->setPosition(maxPos);
    }
    if (getDividerDrawObject() != NULL)
    {
        getDividerDrawObject()->setSize(divSize);
        getDividerDrawObject()->setPosition(divPos);
    }
}

void SplitPanel::setDividerDrawObject(UIDrawObjectCanvas* const value)
{
    if (getDividerDrawObject() != NULL)
    {
        getDividerDrawObject()->removeMouseListener(&_DividerListener);
    }
    _sfDividerDrawObject.setValue(value);
    if (getDividerDrawObject() != NULL)
    {
		value->addMouseListener(&_DividerListener);
	}
}

void SplitPanel::updateChildren(void)
{
    clearChildren();
    if(getDividerDrawObject() != NULL)
    {
        pushToChildren(getDividerDrawObject());
    }
    if(getMinComponent() != NULL)
    {
        pushToChildren(getMinComponent());
    }
    if(getMaxComponent() != NULL)
    {
        pushToChildren(getMaxComponent());
    }

}

void SplitPanel::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _DividerListener.cancel();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SplitPanel::onCreate(const SplitPanel * Id)
{
	Inherited::onCreate(Id);

	if(getDividerDrawObject() != NULL)
	{
        FieldContainerUnrecPtr TheDividerDrawObject(getDividerDrawObject()->shallowCopy());
        setDividerDrawObject(dynamic_pointer_cast<UIDrawObjectCanvas>(TheDividerDrawObject));
        if(getDividerDrawObject() != NULL)
        {
            getDividerDrawObject()->addMouseListener(&_DividerListener);
        }
	}
}

void SplitPanel::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

SplitPanel::SplitPanel(void) :
    Inherited(),
	_DividerListener (this),
	_DividerDraggedListener (this)
{
}

SplitPanel::SplitPanel(const SplitPanel &source) :
    Inherited(source),
	_DividerListener (this),
	_DividerDraggedListener (this)
{
}

SplitPanel::~SplitPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SplitPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if( (whichField & DividerSizeFieldMask) || (whichField & DividerPositionFieldMask) ||
		(whichField & OrientationFieldMask) )
    {
		updateLayout();
	}

    if( (whichField & DividerDrawObjectFieldMask) ||
        (whichField & MinComponentFieldMask) ||
        (whichField & MaxComponentFieldMask)
        )
    {
        updateChildren();
    }
    if( ((whichField & DividerDrawObjectFieldMask) ||
        (whichField & OrientationFieldMask) ||
        (whichField & ExpandableFieldMask)) && getDividerDrawObject() != NULL)
    {
            if(!getExpandable())
            {
                getDividerDrawObject()->setCursor(WindowEventProducer::CURSOR_POINTER);
            }
            else
            {
                if(getOrientation() == SplitPanel::HORIZONTAL_ORIENTATION)
                {
                    getDividerDrawObject()->setCursor(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
                }
                else
                {
                    getDividerDrawObject()->setCursor(WindowEventProducer::CURSOR_RESIZE_N_TO_S);
                }
            }
    }
}

void SplitPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SplitPanel NI" << std::endl;
}

SplitPanel::DividerListener::DividerListener(SplitPanel* const ptr) :
	_SplitPanel(ptr)
{
}
void SplitPanel::DividerListener::mouseClicked(const MouseEventUnrecPtr e)
{
}
void SplitPanel::DividerListener::mouseEntered(const MouseEventUnrecPtr e)
{
	if (_SplitPanel->getExpandable())
	{
		if(_SplitPanel->getParentWindow() != NULL && _SplitPanel->getParentWindow()->getParentDrawingSurface()!=NULL&&_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
		{
			if (_SplitPanel->getOrientation() == SplitPanel::HORIZONTAL_ORIENTATION)
			{
				_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
			}
			else
			{
				_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_N_TO_S);
			}
		}
	}
}
void SplitPanel::DividerListener::mouseExited(const MouseEventUnrecPtr e)
{
	if (_SplitPanel->getExpandable())
	{
		if(_SplitPanel->getParentWindow() != NULL && _SplitPanel->getParentWindow()->getParentDrawingSurface()!= NULL && _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
		{
			_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
		}
	}
}
void SplitPanel::DividerListener::mousePressed(const MouseEventUnrecPtr e)
{
	if (e->getButton() == MouseEvent::BUTTON1 &&
        _SplitPanel->getExpandable() &&
        _SplitPanel->getParentWindow() != NULL)
	{
		_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
        _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->addMouseListener(&(_SplitPanel->_DividerDraggedListener));
            _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(true);
	}
}
void SplitPanel::DividerListener::mouseReleased(const MouseEventUnrecPtr e)
{
}

void SplitPanel::DividerListener::cancel(void)
{
    _SplitPanel->_DividerDraggedListener.cancel();
}

SplitPanel::DividerDraggedListener::DividerDraggedListener(SplitPanel* const ptr) :
	_SplitPanel(ptr)
{
}
	
void SplitPanel::DividerDraggedListener::mouseClicked(const MouseEventUnrecPtr e)
{
}
void SplitPanel::DividerDraggedListener::mouseEntered(const MouseEventUnrecPtr e)
{
}
void SplitPanel::DividerDraggedListener::mouseExited(const MouseEventUnrecPtr e)
{
	//if(_SplitPanel->getParentWindow() != NULL)
	//{
	//	_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
	//	_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_SplitPanel->_DividerDraggedListener));
	//}
}
void SplitPanel::DividerDraggedListener::mousePressed(const MouseEventUnrecPtr e)
{
}
void SplitPanel::DividerDraggedListener::mouseReleased(const MouseEventUnrecPtr e)
{
    if(e->getButton() == MouseEvent::BUTTON1 && _SplitPanel->getParentWindow() != NULL)
	{
		_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
		_SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_SplitPanel->_DividerDraggedListener));
            _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(false);
    }
}

void SplitPanel::DividerDraggedListener::cancel(void)
{
    _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
    _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_SplitPanel->_DividerDraggedListener));
        _SplitPanel->getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(false);
}

void SplitPanel::DividerDraggedListener::mouseMoved(const MouseEventUnrecPtr e)
{
}
void SplitPanel::DividerDraggedListener::mouseDragged(const MouseEventUnrecPtr e)
{
	UInt32 AxisIndex(0);
	if(_SplitPanel->getOrientation() != SplitPanel::HORIZONTAL_ORIENTATION ) AxisIndex = 1;

	if(e->getButton() == e->BUTTON1)
	{
		Pnt2f temp = ViewportToComponent(e->getLocation(), _SplitPanel, e->getViewport());
			if (_SplitPanel->getDividerPosition() <= 1.0)
			{
				if (temp[AxisIndex] >= 0) // this ensures it stays as a percentage position
				{
					Pnt2f TopLeft, BottomRight;
					_SplitPanel->getInsideBorderBounds(TopLeft, BottomRight);
					Vec2f BorderSize(BottomRight - TopLeft);
					_SplitPanel->setDividerPosition((Real32)temp[AxisIndex]/(Real32)BorderSize[AxisIndex]);
				}
			}
			else
			{
				if (temp[AxisIndex] > 1) // this ensures it stays absolute position
				{
					_SplitPanel->setDividerPosition(temp[AxisIndex]);
				}
			}
		//_SplitPanel->updateLayout();
	}
}

OSG_END_NAMESPACE
