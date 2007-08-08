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

#include "Util/OSGUIDrawUtils.h"
#include <OpenSG/OSGConfig.h>
#include "Util/OSGUIDefines.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Component/Container/OSGFrame.h"

#include "OSGSplitPanel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SplitPanel
A UI Split Panel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SplitPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SplitPanel::drawInternal(const GraphicsPtr Graphics) const
{
	// draw the two contained components and the divider
	if (getMinComponent() != NullFC)
		getMinComponent()->draw(Graphics);
	if (getMaxComponent() != NullFC)
		getMaxComponent()->draw(Graphics);
	if (getDividerDrawObject() != NullFC)
		getDividerDrawObject()->draw(Graphics);
}

void SplitPanel::updateLayout(void)
{
	Pnt2s TopLeft, BottomRight;
	getInsideBorderBounds(TopLeft, BottomRight);
	Vec2s BorderSize(BottomRight - TopLeft);

	UInt32 AxisIndex(0);
	if(getAlignment() != HORIZONTAL_ALIGNMENT ) AxisIndex = 1;

	Vec2s minSize(0,0);
	Vec2s maxSize(0,0);
	Vec2s divSize(0,0);
	Pnt2s minPos(0,0);
	Pnt2s maxPos(0,0);
	Pnt2s divPos(0,0);

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
	if (getMinComponent() != NullFC)
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
	if (getMaxComponent() != NullFC)
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
	if (getMinComponent() != NullFC)
	{
		beginEditCP(getMinComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
			getMinComponent()->setSize(minSize);
			getMinComponent()->setPosition(minPos);
		endEditCP(getMinComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
	}
	if (getMaxComponent() != NullFC)
	{
		beginEditCP(getMaxComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
			getMaxComponent()->setSize(maxSize);
			getMaxComponent()->setPosition(maxPos);
		endEditCP(getMaxComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
	}
	if (getDividerDrawObject() != NullFC)
	{
		beginEditCP(getDividerDrawObject(), Component::SizeFieldMask|Component::PositionFieldMask);
			getDividerDrawObject()->setSize(divSize);
			getDividerDrawObject()->setPosition(divPos);
		endEditCP(getDividerDrawObject(), Component::SizeFieldMask|Component::PositionFieldMask);
	}
}

void SplitPanel::setDividerDrawObject(const UIDrawObjectCanvasPtr &value)
{
	if (getDividerDrawObject() != NullFC)
	{
		getChildren().erase(getChildren().find(_sfDividerDrawObject.getValue()));
		getDividerDrawObject()->removeMouseListener(&_DividerListener);
	}
    _sfDividerDrawObject.setValue(value);
	getChildren().addValue(value);
	value->addMouseListener(&_DividerListener);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SplitPanel::SplitPanel(void) :
    Inherited(),
	_DividerListener (SplitPanelPtr(this)),
	_DividerDraggedListener (SplitPanelPtr(this))
{
}

SplitPanel::SplitPanel(const SplitPanel &source) :
    Inherited(source),
	_DividerListener (SplitPanelPtr(this)),
	_DividerDraggedListener (SplitPanelPtr(this))
{
	if(getDividerDrawObject() != NullFC)
	{
	   getDividerDrawObject()->addMouseListener(&_DividerListener);
	}
}

SplitPanel::~SplitPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SplitPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if( (whichField & DividerSizeFieldMask) || (whichField & DividerPositionFieldMask) ||
		(whichField & AlignmentFieldMask) )
    {
		updateLayout();
	}
}

void SplitPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SplitPanel NI" << std::endl;
}

SplitPanel::DividerListener::DividerListener(SplitPanelPtr ptr) :
	_SplitPanel(ptr)
{
}
void SplitPanel::DividerListener::mouseClicked(const MouseEvent& e)
{
}
void SplitPanel::DividerListener::mouseEntered(const MouseEvent& e)
{
	if (_SplitPanel->getExpandable())
	{
		if(_SplitPanel->getParentFrame() != NullFC && _SplitPanel->getParentFrame()->getDrawingSurface()!=NullFC&&_SplitPanel->getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			if (_SplitPanel->getAlignment() == HORIZONTAL_ALIGNMENT)
			{
				_SplitPanel->getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_W_TO_E);
			}
			else
			{
				_SplitPanel->getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_RESIZE_N_TO_S);
			}
		}
	}
}
void SplitPanel::DividerListener::mouseExited(const MouseEvent& e)
{
	if (_SplitPanel->getExpandable())
	{
		if(_SplitPanel->getParentFrame() != NullFC && _SplitPanel->getParentFrame()->getDrawingSurface()!= NullFC && _SplitPanel->getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			_SplitPanel->getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
		}
	}
}
void SplitPanel::DividerListener::mousePressed(const MouseEvent& e)
{
	if (_SplitPanel->getExpandable())
	{
		if(_SplitPanel->getParentFrame() != NullFC)
		{
			_SplitPanel->getParentFrame()->addMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
			_SplitPanel->getParentFrame()->addMouseListener(&(_SplitPanel->_DividerDraggedListener));
		}
	}
}
void SplitPanel::DividerListener::mouseReleased(const MouseEvent& e)
{
}

SplitPanel::DividerDraggedListener::DividerDraggedListener(SplitPanelPtr ptr) :
	_SplitPanel(ptr)
{
}
	
void SplitPanel::DividerDraggedListener::mouseClicked(const MouseEvent& e)
{
}
void SplitPanel::DividerDraggedListener::mouseEntered(const MouseEvent& e)
{
}
void SplitPanel::DividerDraggedListener::mouseExited(const MouseEvent& e)
{
	if(_SplitPanel->getParentFrame() != NullFC)
	{
		_SplitPanel->getParentFrame()->removeMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
		_SplitPanel->getParentFrame()->removeMouseListener(&(_SplitPanel->_DividerDraggedListener));
	}
}
void SplitPanel::DividerDraggedListener::mousePressed(const MouseEvent& e)
{
}
void SplitPanel::DividerDraggedListener::mouseReleased(const MouseEvent& e)
{
	if(_SplitPanel->getParentFrame() != NullFC)
	{
		_SplitPanel->getParentFrame()->removeMouseMotionListener(&(_SplitPanel->_DividerDraggedListener));
		_SplitPanel->getParentFrame()->removeMouseListener(&(_SplitPanel->_DividerDraggedListener));
	}
}
void SplitPanel::DividerDraggedListener::mouseMoved(const MouseEvent& e)
{
}
void SplitPanel::DividerDraggedListener::mouseDragged(const MouseEvent& e)
{
	UInt32 AxisIndex(0);
	if(_SplitPanel->getAlignment() != HORIZONTAL_ALIGNMENT ) AxisIndex = 1;

	if(e.getButton() == e.BUTTON1)
	{
		Pnt2s temp = DrawingSurfaceToComponent(e.getLocation(), _SplitPanel);
		beginEditCP(_SplitPanel, DividerPositionFieldMask);
			if (_SplitPanel->getDividerPosition() <= 1.0)
			{
				if (temp[AxisIndex] >= 0) // this ensures it stays as a percentage position
				{
					Pnt2s TopLeft, BottomRight;
					_SplitPanel->getInsideBorderBounds(TopLeft, BottomRight);
					Vec2s BorderSize(BottomRight - TopLeft);
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
		endEditCP(_SplitPanel, DividerPositionFieldMask);
		//_SplitPanel->updateLayout();
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
    static Char8 cvsid_hpp       [] = OSGSPLITPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPLITPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPLITPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

