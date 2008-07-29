/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGFunctionComponentPanel.h"

#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Util/OSGUIDrawUtils.h"

#include <OpenSG/OSGGL.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FunctionComponentPanel
A User Interface Panel that contains Function Components. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FunctionComponentPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FunctionComponentPanel::setupCursor(Pnt2f MouseLocation)
{
    UInt32 Cursor;
	if(getTabOverLocation(MouseLocation) != TAB_NONE)
	{
		Cursor = WindowEventProducer::CURSOR_POINTER;
	}
	else
	{
		if(_drawComponentResizeSquares)
		{
			Cursor = WindowEventProducer::CURSOR_RESIZE_ALL;
		}
		else
		{
			Cursor = WindowEventProducer::CURSOR_POINTER;
		}
	}
    
    if(Cursor != getCursor())
    {
        beginEditCP(FunctionComponentPanelPtr(this) , CursorFieldMask);
            setCursor(Cursor);
        endEditCP(FunctionComponentPanelPtr(this) , CursorFieldMask);
    }
    if(_ResizableComponent != NullFC && Cursor != _ResizableComponent->getCursor())
    {
        beginEditCP(_ResizableComponent , CursorFieldMask);
            _ResizableComponent->setCursor(Cursor);
        endEditCP(_ResizableComponent , CursorFieldMask);
    }
}

Pnt2f FunctionComponentPanel::getParentToLocal(const Pnt2f& Location)
{
    if(getZoom() == 1.0f)
    {
	    return Inherited::getParentToLocal(Location);
    }
    else
    {
        return (Location - getPosition())*(1.0/getZoom());
    }
}

Vec2f &FunctionComponentPanel::getPreferredSize  (void)
{
    if(getZoom() == 1.0f)
    {
        return Inherited::getPreferredSize();
    }
    else
    {
        return getZoomedPreferredSize();
    }
}

const Vec2f &FunctionComponentPanel::getPreferredSize  (void) const
{
    if(getZoom() == 1.0f)
    {
        return Inherited::getPreferredSize();
    }
    else
    {
        return getZoomedPreferredSize();
    }
}

void FunctionComponentPanel::drawInternal(const GraphicsPtr Graphics) const
{
	if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
		//Attatch a Key and mouse listener to Event Producer
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(const_cast<FunctionComponentPanel*>(this)->_ComponentPanelMoveListener));
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&(const_cast<FunctionComponentPanel*>(this)->_ComponentPanelMoveListener));
		getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&(const_cast<FunctionComponentPanel*>(this)->_ComponentPanelMoveListener));
	}
	
	if(getDrawMiniMap())
	{
		//Calculate minimap size
		Vec2f ComponentPanelSize = Vec2f(_sfPreferredSize.getValue());
		Vec2f MinimapSize = ComponentPanelSize * getMiniMapSize();
	
		//Get bounds of function component panel
		Pnt2f TopLeft = getClipTopLeft(), BottomRight = getClipBottomRight();
		
		//Calculate minimap alignment
		Pnt2f AlignedMapPosition;
		Pnt2f MapTopLeft, MapBottomRight;
		MapTopLeft = Pnt2f(0.0f, 0.0f);
		MapBottomRight = MapTopLeft + MinimapSize;
		AlignedMapPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (MapBottomRight - MapTopLeft), getMiniMapAlignment().y(), getMiniMapAlignment().x());
		
		drawMiniMap(Graphics, AlignedMapPosition, AlignedMapPosition + MinimapSize);
	}
	
	Real32 xScale, yScale;
	xScale = FunctionComponentPanelPtr(this)->getZoom();
	yScale = FunctionComponentPanelPtr(this)->getZoom();
	
	glPushMatrix();
	//glTranslatef(xTranslation, yTranslation, 0.0f);
	glScalef(xScale, yScale, 1.0f);
	
	Inherited::drawInternal(Graphics);
	
	glPopMatrix();
	
	setupClipping(Graphics);

	if(_drawComponentResizeSquares)
	{
		Pnt2f ResizableComponentTopLeft, ResizableComponentBottomRight, ResizableComponentTopRight, ResizableComponentBottomLeft, ResizableComponentTop, ResizableComponentBottom, ResizableComponentLeft, ResizableComponentRight;
		ResizableComponentTopLeft = getZoom() * (_ResizableComponent->getPosition());
		ResizableComponentBottomRight = ResizableComponentTopLeft + getZoom() * (_ResizableComponent->getSize());
		ResizableComponentTopRight = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()), 0.0f));
		ResizableComponentBottomLeft = ResizableComponentTopLeft + (Pnt2f(0.0f, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y())));
		ResizableComponentTop = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()) / 2, 0.0f));
		ResizableComponentBottom = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()) / 2, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y())));
		ResizableComponentLeft = ResizableComponentTopLeft + (Pnt2f(0.0f, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y()) / 2));
		ResizableComponentRight = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()), (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y()) / 2));
		
		Vec2f TabSize = getResizeTabsSize() * getZoom();
		
		Graphics->drawRect(ResizableComponentTopLeft - TabSize, ResizableComponentTopLeft + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentBottomRight - TabSize, ResizableComponentBottomRight + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentTopRight - TabSize, ResizableComponentTopRight + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentBottomLeft - TabSize, ResizableComponentBottomLeft + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentTop - TabSize, ResizableComponentTop + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentBottom - TabSize, ResizableComponentBottom + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentLeft - TabSize, ResizableComponentLeft + TabSize, getResizeTabsColor(), 1.0);
		Graphics->drawRect(ResizableComponentRight - TabSize, ResizableComponentRight + TabSize, getResizeTabsColor(), 1.0);
	}
}

void FunctionComponentPanel::drawMiniMap(const GraphicsPtr Graphics, const Pnt3f& TopLeft, const Pnt3f BottomRight) const
{
	//Drawing Minimap
	Graphics->drawRect(TopLeft, BottomRight, Color4f(0.75f, 0.75f, 1.0f, 1.0f), 0.5);
	
	//Draw rectangle if zoomed in
	if (getZoom() != 1.0)
	{
	/*
		Pnt2f AreaViewedTopLeft, AreaViewedBottomRight, AreaViewedTopRight, AreaViewedBottomLeft;
		AreaViewedTopLeft = Pnt2f(TopLeft + getClipTopLeft() * getMiniMapSize());
		AreaViewedBottomRight = Pnt2f(TopLeft + getClipBottomRight() * getMiniMapSize());
		AreaViewedTopRight = AreaViewedTopLeft + Pnt2f((AreaViewedBottomRight.x() - AreaViewedTopLeft.x()), 0.0f);
		AreaViewedBottomLeft = AreaViewedTopLeft + Pnt2f(0.0f, (AreaViewedBottomRight.y() - AreaViewedTopLeft.y()));
		*/
		
		
		Pnt2f AreaViewedTopLeft, AreaViewedBottomRight, AreaViewedTopRight, AreaViewedBottomLeft;
		AreaViewedTopLeft = Pnt2f(TopLeft.x() + getClipTopLeft().x() * getMiniMapSize(), TopLeft.y() + getClipTopLeft().y() * getMiniMapSize());
		AreaViewedBottomRight = Pnt2f(AreaViewedTopLeft.x() + ((BottomRight.x() - TopLeft.x()) / getZoom()), (AreaViewedTopLeft.y() + (BottomRight.y() - TopLeft.y()) / getZoom()));
		AreaViewedTopRight = AreaViewedTopLeft + Pnt2f((AreaViewedBottomRight.x() - AreaViewedTopLeft.x()), 0.0f);
		AreaViewedBottomLeft = AreaViewedTopLeft + Pnt2f(0.0f, (AreaViewedBottomRight.y() - AreaViewedTopLeft.y()));
		
		Graphics->drawLine(AreaViewedTopLeft, AreaViewedTopRight, 1.0, Color4f(0.0f, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawLine(AreaViewedTopRight, AreaViewedBottomRight, 1.0, Color4f(0.0f, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawLine(AreaViewedBottomLeft, AreaViewedBottomRight, 1.0, Color4f(0.0f, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawLine(AreaViewedTopLeft, AreaViewedBottomLeft, 1.0, Color4f(0.0f, 0.0f, 0.0f, 1.0f), 1.0);
	}
	
	//Get bounds of function component panel
	Pnt2f PanelTopLeft, PanelBottomRight;
	getInsideBorderBounds(PanelTopLeft, PanelBottomRight);
	
	//Determine how much to scale The internally drawn components
	//To match the MiniMap Size
	Real32 xTranslation, yTranslation, xScale, yScale;
	xTranslation = TopLeft.x();
	yTranslation = TopLeft.y();
	xScale = (BottomRight.x() - TopLeft.x()) / (PanelBottomRight.x() - PanelTopLeft.x());
	yScale = (BottomRight.y() - TopLeft.y()) / (PanelBottomRight.y() - PanelTopLeft.y());
	
	glPushMatrix();
	glTranslatef(xTranslation, yTranslation, 0.0f);
	glScalef(xScale, yScale, 1.0f);
	
	Inherited::drawInternal(Graphics);
	
	glPopMatrix();
}

FunctionComponentPanel::ResizeTab FunctionComponentPanel::getTabOverLocation(const Pnt2f& Location) const
{
	if (_drawComponentResizeSquares)
	{
		Pnt2f ResizableComponentTopLeft, ResizableComponentBottomRight, ResizableComponentTopRight, ResizableComponentBottomLeft, ResizableComponentTop, ResizableComponentBottom, ResizableComponentLeft, ResizableComponentRight;
		ResizableComponentTopLeft = getZoom() * (_ResizableComponent->getPosition());
		ResizableComponentBottomRight = ResizableComponentTopLeft + getZoom() * (_ResizableComponent->getSize());
		ResizableComponentTopRight = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()), 0.0f));
		ResizableComponentBottomLeft = ResizableComponentTopLeft + (Pnt2f(0.0f, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y())));
		ResizableComponentTop = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()) / 2, 0.0f));
		ResizableComponentBottom = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()) / 2, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y())));
		ResizableComponentLeft = ResizableComponentTopLeft + (Pnt2f(0.0f, (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y()) / 2));
		ResizableComponentRight = ResizableComponentTopLeft + (Pnt2f((ResizableComponentBottomRight.x() - ResizableComponentTopLeft.x()), (ResizableComponentBottomRight.y() - ResizableComponentTopLeft.y()) / 2));
		
		Vec2f TabSize = getResizeTabsSize() * getZoom();
		
		if((Location.x() > (ResizableComponentTopLeft.x() - TabSize.x())) && (Location.x() < (ResizableComponentTopLeft.x() + TabSize.x())) &&
			(Location.y() > (ResizableComponentTopLeft.y() - TabSize.y())) && (Location.y() < (ResizableComponentTopLeft.y() + TabSize.y())))
		{
			return TAB_TOP_LEFT;
		}
		else
		{
			if((Location.x() > (ResizableComponentTop.x() - TabSize.x())) && (Location.x() < (ResizableComponentTop.x() + TabSize.x())) &&
				(Location.y() > (ResizableComponentTop.y() - TabSize.y())) && (Location.y() < (ResizableComponentTop.y() + TabSize.y())))
			{
				return TAB_TOP;
			}
			else
			{
				if((Location.x() > (ResizableComponentTopRight.x() - TabSize.x())) && (Location.x() < (ResizableComponentTopRight.x() + TabSize.x())) &&
					(Location.y() > (ResizableComponentTopRight.y() - TabSize.y())) && (Location.y() < (ResizableComponentTopRight.y() + TabSize.y())))
				{
					return TAB_TOP_RIGHT;
				}
				else
				{
					if((Location.x() > (ResizableComponentRight.x() - TabSize.x())) && (Location.x() < (ResizableComponentRight.x() + TabSize.x())) &&
						(Location.y() > (ResizableComponentRight.y() - TabSize.y())) && (Location.y() < (ResizableComponentRight.y() + TabSize.y())))
					{
						return TAB_RIGHT;
					}
					else
					{
						if((Location.x() > (ResizableComponentBottomRight.x() - TabSize.x())) && (Location.x() < (ResizableComponentBottomRight.x() + TabSize.x())) &&
							(Location.y() > (ResizableComponentBottomRight.y() - TabSize.y())) && (Location.y() < (ResizableComponentBottomRight.y() + TabSize.y())))
						{
							return TAB_BOTTOM_RIGHT;
						}
						else
						{
							if((Location.x() > (ResizableComponentBottom.x() - TabSize.x())) && (Location.x() < (ResizableComponentBottom.x() + TabSize.x())) &&
								(Location.y() > (ResizableComponentBottom.y() - TabSize.y())) && (Location.y() < (ResizableComponentBottom.y() + TabSize.y())))
							{
								return TAB_BOTTOM;
							}
							else
							{
								if((Location.x() > (ResizableComponentBottomLeft.x() - TabSize.x())) && (Location.x() < (ResizableComponentBottomLeft.x() + TabSize.x())) &&
									(Location.y() > (ResizableComponentBottomLeft.y() - TabSize.y())) && (Location.y() < (ResizableComponentBottomLeft.y() + TabSize.y())))
								{
									return TAB_BOTTOM_LEFT;
								}
								else
								{
									if((Location.x() > (ResizableComponentLeft.x() - TabSize.x())) && (Location.x() < (ResizableComponentLeft.x() + TabSize.x())) &&
										(Location.y() > (ResizableComponentLeft.y() - TabSize.y())) && (Location.y() < (ResizableComponentLeft.y() + TabSize.y())))
									{
										return TAB_LEFT;
									}
									else
									{
										return TAB_NONE;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void FunctionComponentPanel::updateLayout(void)
{
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(i<getChildrenPositions().size() && i<getChildrenSizes().size())
        {
            beginEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
                getChildren()[i]->setPosition(getChildrenPositions()[i]);
                getChildren()[i]->setSize(getChildrenSizes()[i]);
            endEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
        }
    }
}

void FunctionComponentPanel::mousePressed(const MouseEvent& e)
{
	Inherited::mousePressed(e);
}

void FunctionComponentPanel::mouseDragged(const MouseEvent& e)
{
	Inherited::mouseDragged(e);
}

void FunctionComponentPanel::mouseMoved(const MouseEvent& e)
{
	Inherited::mouseMoved(e);
}

void FunctionComponentPanel::keyReleased(const KeyEvent& e)
{
	Inherited::keyReleased(e);
}

void FunctionComponentPanel::mouseWheelMoved(const MouseWheelEvent& e)
{
    if(e.getScrollType() == MouseWheelEvent::BLOCK_SCROLL)
    {
        //scrollBlock(-e.getScrollAmount());
		
		Real32 newZoom = FunctionComponentPanelPtr(this)->getZoom() + e.getScrollAmount();
		
		beginEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomFieldMask);
			FunctionComponentPanelPtr(this)->setZoom(newZoom);
		endEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomFieldMask);
    }
    else if(e.getScrollType() == MouseWheelEvent::UNIT_SCROLL)
    {
        //scrollUnit(-e.getUnitsToScroll());
		
		Real32 newZoom = FunctionComponentPanelPtr(this)->getZoom() + 0.05 * e.getUnitsToScroll();
		
		if (newZoom < 0.1)
		{
			newZoom = 0.1;
		}
		
		beginEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomFieldMask);
			FunctionComponentPanelPtr(this)->setZoom(newZoom);
		endEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomFieldMask);
    }
    Container::mouseWheelMoved(e);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FunctionComponentPanel::FunctionComponentPanel(void) :
    Inherited(),
        _ComponentMoveListener(FunctionComponentPanelPtr(this)),
        _ComponentPanelMoveListener(FunctionComponentPanelPtr(this)),
		_ComponentResizeListener(FunctionComponentPanelPtr(this)),
        _drawComponentResizeSquares(false)
		//_overResizeSquare(false)
{
	
}

FunctionComponentPanel::FunctionComponentPanel(const FunctionComponentPanel &source) :
    Inherited(source),
        _ComponentMoveListener(FunctionComponentPanelPtr(this)),
		_ComponentPanelMoveListener(FunctionComponentPanelPtr(this)),
		_ComponentResizeListener(FunctionComponentPanelPtr(this)),
        _drawComponentResizeSquares(false)
		//_overResizeSquare(false)
{

}

FunctionComponentPanel::~FunctionComponentPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FunctionComponentPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ChildrenFieldMask)
    {
        if(getChildren().size() > getChildrenPositions().size())
        {
		    Pnt2f TopLeft, BottomRight;
		    getInsideInsetsBounds(TopLeft, BottomRight);

            beginEditCP(FunctionComponentPanelPtr(this), ChildrenPositionsFieldMask | ChildrenSizesFieldMask);
                while(getChildren().size() > getChildrenPositions().size())
                {
                    getChildrenPositions().push_back(TopLeft);
                    getChildrenSizes().push_back(getChildren()[getChildrenSizes().size()]->getRequestedSize());

                }
            endEditCP(FunctionComponentPanelPtr(this), ChildrenPositionsFieldMask | ChildrenSizesFieldMask);
        }
        else if(getChildren().size() < getChildrenPositions().size())
        {
            beginEditCP(FunctionComponentPanelPtr(this), ChildrenPositionsFieldMask | ChildrenSizesFieldMask);
                getChildrenPositions().resize(getChildren().size());
                getChildrenSizes().resize(getChildren().size());
            endEditCP(FunctionComponentPanelPtr(this), ChildrenPositionsFieldMask | ChildrenSizesFieldMask);
        }
    }

    if((whichField & ChildrenPositionsFieldMask) ||
        (whichField & ChildrenSizesFieldMask))
    {
        updateLayout();
    }

    if(whichField & ZoomFieldMask)
    {
            beginEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomedPreferredSizeFieldMask);
				setZoomedPreferredSize(getSFPreferredSize()->getValue()*getZoom());
            endEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomedPreferredSizeFieldMask);
	}
	
	if(whichField & ZoomedPreferredSizeFieldMask)
	{
        updateContainerLayout();
	}
	
}

void FunctionComponentPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FunctionComponentPanel NI" << std::endl;
}


void FunctionComponentPanel::ComponentPanelMoveListener::mousePressed(const MouseEvent& e)
{
	if(_FunctionComponentPanel->_drawComponentResizeSquares && _FunctionComponentPanel->getTabOverLocation(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport())) != TAB_NONE)
	{
		for(Int32 i(_FunctionComponentPanel->getChildren().size()-1) ; i>=0 ; --i)
		{
			bool isContained(false);
			if(_FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation(), true) || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() + _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true)
			   || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() - _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true))
			{
				isContained = true;
			}
			if(isContained)
			{
				//Set The Active Component
				_FunctionComponentPanel->_ComponentResizeListener.setActiveComponent(i);
				//Set the Initial Position
				_FunctionComponentPanel->_ComponentResizeListener.setInitialPosition(e.getLocation());
				
				//Attach Listeners
				_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&(_FunctionComponentPanel->_ComponentResizeListener));
				_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&(_FunctionComponentPanel->_ComponentResizeListener));
				_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_FunctionComponentPanel->_ComponentResizeListener));
				_FunctionComponentPanel->_ComponentResizeListener.setResizeTab(_FunctionComponentPanel->getTabOverLocation(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport())));
			}
		}
		
		
	}
	else
	{
		if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()!=NullFC&& _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
			_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
			
			
			for(Int32 i(_FunctionComponentPanel->getChildren().size()-1) ; i>=0 ; --i)
			{
				bool isContained(false);
				if(_FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation(), true) || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() + _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true)
					|| _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() - _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true))
				{
					isContained = true;
				}
				if(isContained)
				{
					//Set The Active Component
					_FunctionComponentPanel->_ComponentMoveListener.setActiveComponent(i);
					//Set the Initial Position
					_FunctionComponentPanel->_ComponentMoveListener.setInitialPosition(e.getLocation());
					
					//Attach Listeners
					_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&(_FunctionComponentPanel->_ComponentMoveListener));
					_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&(_FunctionComponentPanel->_ComponentMoveListener));
					_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_FunctionComponentPanel->_ComponentMoveListener));
				}
			}
		}
	}
}


void FunctionComponentPanel::ComponentPanelMoveListener::mouseMoved(const MouseEvent& e)
{
	if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()!=NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
        _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
    {
		
		bool isContained(false);
		for(Int32 i(_FunctionComponentPanel->getChildren().size()-1) ; i>=0 ; --i)
		{
			if(_FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation(), true) || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() + _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true)
			   || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() - _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true))
			{
				isContained = true;
				_FunctionComponentPanel->_ResizableComponent = _FunctionComponentPanel->getChildren()[i];
				_FunctionComponentPanel->_ComponentResizeListener.setActiveComponent(i);
			}
			
			if(isContained)
			{
				_FunctionComponentPanel->_drawComponentResizeSquares = true;
			}
			else
			{
				_FunctionComponentPanel->_drawComponentResizeSquares = false;
			}
			
		}
	}
	else
	{
		if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()!=NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			for(Int32 i(_FunctionComponentPanel->getChildren().size()-1) ; i>=0 ; --i)
			{
				if(_FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation(), true) || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() + _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true)
				   || _FunctionComponentPanel->getChildren()[i]->isContained(e.getLocation() - _FunctionComponentPanel->getResizeAreaOfEffectOffset() * _FunctionComponentPanel->getZoom(), true))
				{
					_FunctionComponentPanel->_ResizableComponent = _FunctionComponentPanel->getChildren()[i];
					i = -1;
				}
				
				else
				{
					_FunctionComponentPanel->_drawComponentResizeSquares = false;
				}
			}
		}
		else
		{
			_FunctionComponentPanel->_drawComponentResizeSquares = false;
		}
	}
    _FunctionComponentPanel->setupCursor(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()));
	//Inherited::mouseMoved(e);
}

void FunctionComponentPanel::ComponentPanelMoveListener::mouseDragged(const MouseEvent& e)
{
}

void FunctionComponentPanel::ComponentPanelMoveListener::keyReleased(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_CONTROL)
	{
		_FunctionComponentPanel->_drawComponentResizeSquares = false;
	}
	if(_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
	    _FunctionComponentPanel->setupCursor(_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->getMousePosition());
	}
	//Inherited::keyReleased(e);
}

void FunctionComponentPanel::ComponentPanelMoveListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_CONTROL && _FunctionComponentPanel->_ResizableComponent != NullFC)
	{
		_FunctionComponentPanel->_drawComponentResizeSquares = true;
	}
	else
	{
		_FunctionComponentPanel->_drawComponentResizeSquares = false;
	}
    if(_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
	    _FunctionComponentPanel->setupCursor(_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->getMousePosition());
	}
}



void FunctionComponentPanel::ComponentMoveListener::mouseReleased(const MouseEvent& e)
{
	detach();
	_FunctionComponentPanel->_ComponentResizeListener.setActiveComponent(_ActiveComponent);
}

void FunctionComponentPanel::ComponentMoveListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		detach();
		
		//Set the Active Component's Position back to it's initial position
		beginEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask);	
			_FunctionComponentPanel->getChildrenPositions()[_ActiveComponent].setValue(_InitialComponentPosition);
		endEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask);

	}
}

void FunctionComponentPanel::ComponentMoveListener::mouseDragged(const MouseEvent& e)
{
    
	if(_FunctionComponentPanel != NullFC)
	{
		//Move the Position of the Component based on the mouse position and it's initial position
		Pnt2f InitialPositionsDifference = Pnt2f(_InitialComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
		Pnt2f AbsolutePosition = Pnt2f(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()) + InitialPositionsDifference);
		Pnt2f NewPosition = AbsolutePosition;
		
		//Test AbsolutePosition to make sure Component is inside parent container
		Pnt2f AbsolutePositionBottomRight, ContainerTopLeft, ContainerBottomRight;
		AbsolutePositionBottomRight = AbsolutePosition + _FunctionComponentPanel->getChildren()[_ActiveComponent]->getSize();
		_FunctionComponentPanel->getInsideInsetsBounds(ContainerTopLeft, ContainerBottomRight);
		if(AbsolutePosition.x() < ContainerTopLeft.x())
		{
			NewPosition[0] = ContainerTopLeft.x();
		}
		if(AbsolutePosition.y() < ContainerTopLeft.y())
		{
			NewPosition[1] = ContainerTopLeft.y();
		}
		if(AbsolutePositionBottomRight.x() > ContainerBottomRight.x())
		{
			NewPosition[0] = ContainerBottomRight.x() - _FunctionComponentPanel->getChildren()[_ActiveComponent]->getSize().x();
		}
		if(AbsolutePositionBottomRight.y() > ContainerBottomRight.y())
		{
			NewPosition[1] = ContainerBottomRight.y() - _FunctionComponentPanel->getChildren()[_ActiveComponent]->getSize().y();
		}
		
		//Set new position
		beginEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask);	
			_FunctionComponentPanel->getChildrenPositions()[_ActiveComponent].setValue(NewPosition);
		endEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask);
	}
}

void FunctionComponentPanel::ComponentMoveListener::detach(void)
{
    if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()!=NullFC&& _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    }
}

void FunctionComponentPanel::ComponentMoveListener::setActiveComponent(UInt32 Index)
{
	_ActiveComponent = Index;
    _InitialComponentPosition = _FunctionComponentPanel->getChildrenPositions()[_ActiveComponent];
}




void FunctionComponentPanel::ComponentResizeListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		detach();
		
		//Set the Active Component's size and position back to it's initial size and position
		beginEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask | FunctionComponentPanel::ChildrenSizesFieldMask);	
			_FunctionComponentPanel->getChildrenPositions()[_ActiveResizeComponent].setValue(_InitialResizeComponentPosition);
			_FunctionComponentPanel->getChildrenSizes()[_ActiveResizeComponent].setValue(_InitialResizeComponentSize);
		endEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask | FunctionComponentPanel::ChildrenSizesFieldMask);

	}
}

void FunctionComponentPanel::ComponentResizeListener::mouseReleased(const MouseEvent& e)
{
	detach();
}

void FunctionComponentPanel::ComponentResizeListener::mouseDragged(const MouseEvent& e)
{
    if(_FunctionComponentPanel != NullFC)
	{
		Vec2f MouseMovedDistance;
		Pnt2f AbsolutePosition, NewPosition;
		switch (_ResizeTab)
		{
			case TAB_TOP_LEFT:
				{
					//Mouse moved distance
					MouseMovedDistance = Vec2f(ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()) - ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()));
					
					//New position
					Vec2f InitialPositionsDifference = Vec2f(_InitialResizeComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
					AbsolutePosition = Pnt2f(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()) + InitialPositionsDifference);
				}
				break;
			
			case TAB_TOP:
				{
					//Vertical mouse moved distance
					MouseMovedDistance = Vec2f(0.0f, _InitialPosition.y() - e.getLocation().y());
					
					//New position
					Vec2f InitialPositionsDifference = Vec2f(_InitialResizeComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
					AbsolutePosition = Pnt2f(_FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().x(), ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()).y() + InitialPositionsDifference.y());
				}
				break;
				
			case TAB_TOP_RIGHT:
				{
					//Mouse moved distance
					MouseMovedDistance = Vec2f(e.getLocation().x() - _InitialPosition.x(), _InitialPosition.y() - e.getLocation().y());
					
					//New position
					Vec2f InitialPositionsDifference = Vec2f(_InitialResizeComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
					AbsolutePosition = Pnt2f(_FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().x(), ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()).y() + InitialPositionsDifference.y());
				}
				break;
				
			case TAB_RIGHT:
				{
					//Horizontal mouse moved distance
					MouseMovedDistance = Vec2f(e.getLocation().x() - _InitialPosition.x(), 0.0f);
					
					//Position stays the same
					AbsolutePosition = _InitialResizeComponentPosition;
				}
				break;
			
			case TAB_BOTTOM_RIGHT:
				{
					//Mouse moved distance
					MouseMovedDistance = Vec2f(e.getLocation() - _InitialPosition);
					
					//Position stays the same
					AbsolutePosition = _InitialResizeComponentPosition;
				}
				break;
			
			case TAB_BOTTOM:
				{
					//Vertical mouse moved distance
					MouseMovedDistance = Vec2f(0.0f, e.getLocation().y() - _InitialPosition.y());
					
					//Position stays the same
					AbsolutePosition = _InitialResizeComponentPosition;
				}
				break;
			
			case TAB_BOTTOM_LEFT:
				{
					//Mouse moved distance
					MouseMovedDistance = Vec2f(_InitialPosition.x() - e.getLocation().x(), e.getLocation().y() - _InitialPosition.y());
					
					//New position
					Vec2f InitialPositionsDifference = Vec2f(_InitialResizeComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
					AbsolutePosition = Pnt2f(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()).x() + InitialPositionsDifference.x(), _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().y());
				}
				break;
				
			case TAB_LEFT:
				{
					//Horizontal mouse moved distance
					MouseMovedDistance = Vec2f(_InitialPosition.x() - e.getLocation().x(), 0.0f);
					
					//New position
					Vec2f InitialPositionsDifference = Vec2f(_InitialResizeComponentPosition - ViewportToComponent(_InitialPosition, _FunctionComponentPanel, e.getViewport()));
					AbsolutePosition = Pnt2f(ViewportToComponent(e.getLocation(), _FunctionComponentPanel, e.getViewport()).x() + InitialPositionsDifference.x(), _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().y());
				}
				break;
		}
		
		//Calculate new size
		Vec2f NewSize = _InitialResizeComponentSize + MouseMovedDistance;
		
		//Calculate new position
		NewPosition = AbsolutePosition;
		Pnt2f AbsolutePositionBottomRight, ContainerTopLeft, ContainerBottomRight;
		AbsolutePositionBottomRight = AbsolutePosition + _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize();
		_FunctionComponentPanel->getInsideInsetsBounds(ContainerTopLeft, ContainerBottomRight);
		
		
		//Test AbsolutePosition to make sure Component is inside parent container
		if(AbsolutePosition.x() < ContainerTopLeft.x())
		{
			NewPosition[0] = ContainerTopLeft.x();
			NewSize[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().x();
		}
		if(AbsolutePosition.y() < ContainerTopLeft.y())
		{
			NewPosition[1] = ContainerTopLeft.y();
			NewSize[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().y();
		}
		if(AbsolutePositionBottomRight.x() > ContainerBottomRight.x())
		{
			NewPosition[0] = ContainerBottomRight.x() - _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().x();
			NewSize[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().x();
		}
		if(AbsolutePositionBottomRight.y() > ContainerBottomRight.y())
		{
			NewPosition[1] = ContainerBottomRight.y() - _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().y();
			NewSize[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getSize().y();
		}
		
		
		//Test new size
		if(NewSize.x() > _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMaxSize().x())
		{
			NewSize[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMaxSize().x();
			NewPosition[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().x();
		}
		if(NewSize.y() > _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMaxSize().y())
		{
			NewSize[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMaxSize().y();
			NewPosition[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().y();
		}
		if(NewSize.x() < _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMinSize().x())
		{
			NewSize[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMinSize().x();
			NewPosition[0] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().x();
		}
		if(NewSize.y() < _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMinSize().y())
		{
			NewSize[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getMinSize().y();
			NewPosition[1] = _FunctionComponentPanel->getChildren()[_ActiveResizeComponent]->getPosition().y();
		}
		
		//Set new position and size
		beginEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask | FunctionComponentPanel::ChildrenSizesFieldMask);	
			_FunctionComponentPanel->getChildrenPositions()[_ActiveResizeComponent].setValue(NewPosition);
			_FunctionComponentPanel->getChildrenSizes()[_ActiveResizeComponent].setValue(NewSize);
		endEditCP(_FunctionComponentPanel, FunctionComponentPanel::ChildrenPositionsFieldMask | FunctionComponentPanel::ChildrenSizesFieldMask);
		}
}

void FunctionComponentPanel::ComponentResizeListener::detach(void)
{
    if(_FunctionComponentPanel->getParentWindow() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface() != NullFC && _FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
		_FunctionComponentPanel->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    }
}

void FunctionComponentPanel::ComponentResizeListener::setActiveComponent(UInt32 Index)
{
	_ActiveResizeComponent = Index;
    _InitialResizeComponentPosition = _FunctionComponentPanel->getChildrenPositions()[_ActiveResizeComponent];
	_InitialResizeComponentSize = _FunctionComponentPanel->getChildrenSizes()[_ActiveResizeComponent];
}

void FunctionComponentPanel::ComponentResizeListener::setResizeTab(ResizeTab Tab)
{
	_ResizeTab = Tab;
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
    static Char8 cvsid_hpp       [] = OSGFUNCTIONCOMPONENTPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFUNCTIONCOMPONENTPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFUNCTIONCOMPONENTPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

