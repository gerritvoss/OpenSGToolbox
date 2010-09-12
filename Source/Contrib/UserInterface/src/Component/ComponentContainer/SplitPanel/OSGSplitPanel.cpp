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
        if(getMinComponent()->getSize() != minSize)
        {
            getMinComponent()->setSize(minSize);
        }
        if(getMinComponent()->getPosition() != minPos)
        {
            getMinComponent()->setPosition(minPos);
        }
    }
    if (getMaxComponent() != NULL)
    {
        if(getMaxComponent()->getSize() != maxSize)
        {
            getMaxComponent()->setSize(maxSize);
        }
        if(getMaxComponent()->getPosition() != maxPos)
        {
            getMaxComponent()->setPosition(maxPos);
        }
    }
    if (getDividerDrawObject() != NULL)
    {
        if(getDividerDrawObject()->getSize() != divSize)
        {
            getDividerDrawObject()->setSize(divSize);
        }
        if(getDividerDrawObject()->getPosition() != divPos)
        {
            getDividerDrawObject()->setPosition(divPos);
        }
    }
}

void SplitPanel::setDividerDrawObject(UIDrawObjectCanvas* const value)
{
    if (getDividerDrawObject() != NULL)
    {
        _MouseEnteredConnection.disconnect();
        _MouseExitedConnection.disconnect();
        _MousePressedConnection.disconnect();
    }
    _sfDividerDrawObject.setValue(value);
    if (getDividerDrawObject() != NULL)
    {
        _MouseEnteredConnection = value->connectMouseEntered(boost::bind(&SplitPanel::dividerMouseEntered, this, _1));
        _MouseExitedConnection = value->connectMouseExited(boost::bind(&SplitPanel::dividerMouseExited, this, _1));
        _MousePressedConnection = value->connectMousePressed(boost::bind(&SplitPanel::dividerMousePressed, this, _1));
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
    _MouseEnteredConnection.disconnect();
    _MouseExitedConnection.disconnect();
    _MousePressedConnection.disconnect();
    _DragMouseDraggedConnection.disconnect();
    _DragMouseReleasedConnection.disconnect();
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
            _MouseEnteredConnection = getDividerDrawObject()->connectMouseEntered(boost::bind(&SplitPanel::dividerMouseEntered, this, _1));
            _MouseExitedConnection = getDividerDrawObject()->connectMouseExited(boost::bind(&SplitPanel::dividerMouseExited, this, _1));
            _MousePressedConnection = getDividerDrawObject()->connectMousePressed(boost::bind(&SplitPanel::dividerMousePressed, this, _1));
        }
	}
}

void SplitPanel::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

SplitPanel::SplitPanel(void) :
    Inherited()
{
}

SplitPanel::SplitPanel(const SplitPanel &source) :
    Inherited(source)
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

void SplitPanel::dividerMouseEntered(MouseEventDetails* const e)
{
	if (getExpandable())
	{
		if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&&getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
		{
			if (getOrientation() == SplitPanel::HORIZONTAL_ORIENTATION)
			{
				getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
			}
			else
			{
				getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_N_TO_S);
			}
		}
	}
}
void SplitPanel::dividerMouseExited(MouseEventDetails* const e)
{
	if (getExpandable())
	{
		if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!= NULL && getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
		{
			getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
		}
	}
}
void SplitPanel::dividerMousePressed(MouseEventDetails* const e)
{
	if (e->getButton() == MouseEventDetails::BUTTON1 &&
        getExpandable())
	{
        _DragMouseDraggedConnection.disconnect();
        _DragMouseReleasedConnection.disconnect();

        _DragMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&SplitPanel::dividerDragMouseDragged, this, _1));
        _DragMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&SplitPanel::dividerDragMouseReleased, this, _1));

        getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(true);
	}
}
	
void SplitPanel::dividerDragMouseReleased(MouseEventDetails* const e)
{
    if(e->getButton() == MouseEventDetails::BUTTON1)
	{
        _DragMouseDraggedConnection.disconnect();
        _DragMouseReleasedConnection.disconnect();
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(false);
    }
}

void SplitPanel::dividerDragCancel(void)
{
    _DragMouseDraggedConnection.disconnect();
    _DragMouseReleasedConnection.disconnect();
    getParentWindow()->getParentDrawingSurface()->getEventProducer()->setLockCursor(false);
}

void SplitPanel::dividerDragMouseDragged(MouseEventDetails* const e)
{
	UInt32 AxisIndex(0);
	if(getOrientation() != SplitPanel::HORIZONTAL_ORIENTATION ) AxisIndex = 1;

	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
		Pnt2f temp = ViewportToComponent(e->getLocation(), this, e->getViewport());
			if (getDividerPosition() <= 1.0)
			{
				if (temp[AxisIndex] >= 0) // this ensures it stays as a percentage position
				{
					Pnt2f TopLeft, BottomRight;
					getInsideBorderBounds(TopLeft, BottomRight);
					Vec2f BorderSize(BottomRight - TopLeft);
					setDividerPosition((Real32)temp[AxisIndex]/(Real32)BorderSize[AxisIndex]);
				}
			}
			else
			{
				if (temp[AxisIndex] > 1) // this ensures it stays absolute position
				{
					setDividerPosition(temp[AxisIndex]);
				}
			}
		//updateLayout();
	}
}

OSG_END_NAMESPACE
