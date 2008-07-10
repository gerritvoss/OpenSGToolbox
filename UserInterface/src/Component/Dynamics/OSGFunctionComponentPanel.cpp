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

#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/UserInterface//OSGUIDrawUtils.h>

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

UInt32 FunctionComponentPanel::queryCursor(const Pnt2f& CursorLoc) const
{
	return WindowEventProducer::CURSOR_HAND;
	return Inherited::queryCursor(CursorLoc);
}

Pnt2f FunctionComponentPanel::getParentToLocal(const Pnt2f& Location)
{
    //TODO: Implement
    Pnt2f Result(Inherited::getParentToLocal(Location));
	
	
    return Result;
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
	
	if(getDrawMiniMap())
	{
		//Calculate minimap size
		Vec2f ComponentPanelSize = Vec2f(getSize());
		Vec2f MinimapSize = ComponentPanelSize * getMiniMapSize();
	
		//Get bounds of function component panel
		Pnt2f TopLeft, BottomRight;
		getInsideBorderBounds(TopLeft, BottomRight);
		
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
		Pnt2f ResizableComponentTopRight, ResizableComponentBottomLeft, ResizableComponentTop, ResizableComponentBottom, ResizableComponentLeft, ResizableComponentRight, BoxSize;
		ResizableComponentTopRight = _ResizableComponentTopLeft + Pnt2f((_ResizableComponentBottomRight.x() - _ResizableComponentTopLeft.x()), 0.0f);
		ResizableComponentBottomLeft = _ResizableComponentTopLeft + Pnt2f(0.0f, (_ResizableComponentBottomRight.y() - _ResizableComponentTopLeft.y()));
		ResizableComponentTop = _ResizableComponentTopLeft + Pnt2f((_ResizableComponentBottomRight.x() - _ResizableComponentTopLeft.x()) / 2, 0.0f);
		ResizableComponentBottom = _ResizableComponentTopLeft + Pnt2f((_ResizableComponentBottomRight.x() - _ResizableComponentTopLeft.x()) / 2, (_ResizableComponentBottomRight.y() - _ResizableComponentTopLeft.y()));
		ResizableComponentLeft = _ResizableComponentTopLeft + Pnt2f(0.0f, (_ResizableComponentBottomRight.y() - _ResizableComponentTopLeft.y()) / 2);
		ResizableComponentRight = _ResizableComponentTopLeft + Pnt2f((_ResizableComponentBottomRight.x() - _ResizableComponentTopLeft.x()), (_ResizableComponentBottomRight.y() - _ResizableComponentTopLeft.y()) / 2);
		BoxSize = Pnt2f(4.0f, 4.0f);
		
		Graphics->drawRect(_ResizableComponentTopLeft - BoxSize, _ResizableComponentTopLeft + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(_ResizableComponentBottomRight - BoxSize, _ResizableComponentBottomRight + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentTopRight - BoxSize, ResizableComponentTopRight + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentBottomLeft - BoxSize, ResizableComponentBottomLeft + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentTop - BoxSize, ResizableComponentTop + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentBottom - BoxSize, ResizableComponentBottom + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentLeft - BoxSize, ResizableComponentLeft + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
		Graphics->drawRect(ResizableComponentRight - BoxSize, ResizableComponentRight + BoxSize, Color4f(0.0, 0.0f, 0.0f, 1.0f), 1.0);
	}
}

void FunctionComponentPanel::drawMiniMap(const GraphicsPtr Graphics, const Pnt3f& TopLeft, const Pnt3f BottomRight) const
{
	//Drawing Minimap
	Graphics->drawRect(TopLeft, BottomRight, Color4f(0.75f, 0.75f, 1.0f, 1.0f), 0.5);
	
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


void FunctionComponentPanel::updateLayout(void)
{
    //Do Nothing
}

void FunctionComponentPanel::mousePressed(const MouseEvent& e)
{
    if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
    {
		
		bool isContained(false);
		for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
		{
			isContained = getChildren()[i]->isContained(e.getLocation(), true);
			if(isContained)
			{
				//Set The Active Component
				_ComponentMoveListener.setActiveComponent(getChildren()[i]);
				//Set the Initial Position
				_ComponentMoveListener.setInitialPosition(e.getLocation());
				
				//Attach Listeners
				getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_ComponentMoveListener);
				getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_ComponentMoveListener);
				getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_ComponentMoveListener);
			}
		}
    }
    else
    {
        Inherited::mousePressed(e);
    }
}

void FunctionComponentPanel::mouseDragged(const MouseEvent& e)
{
	if(_drawComponentResizeSquares)
	{
		_ResizableComponentTopLeft = _ResizableComponent->getPosition();
		_ResizableComponentBottomRight = _ResizableComponent->getPosition() + _ResizableComponent->getSize();
	}
	else
	{
		_ResizableComponentTopLeft = Pnt2f(0.0f, 0.0f);
		_ResizableComponentBottomRight = Pnt2f(0.0f, 0.0f);
	}
	
	Inherited::mouseDragged(e);
}

void FunctionComponentPanel::mouseMoved(const MouseEvent& e)
{
	if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
    {
		
		bool isContained(false);
		for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
		{
			isContained = getChildren()[i]->isContained(e.getLocation(), true);
			if(isContained)
			{
				_drawComponentResizeSquares = true;
				_ResizableComponent = getChildren()[i];
			}
			else
			{
				_drawComponentResizeSquares = false;
				_ResizableComponent = NullFC;
			}
		}
	}
	else
	{
		_drawComponentResizeSquares = false;
		_ResizableComponent = NullFC;
	}
	
	if(_drawComponentResizeSquares)
	{
		_ResizableComponentTopLeft = _ResizableComponent->getPosition();
		_ResizableComponentBottomRight = _ResizableComponent->getPosition() + _ResizableComponent->getSize();
	}
	else
	{
		_ResizableComponentTopLeft = Pnt2f(0.0f, 0.0f);
		_ResizableComponentBottomRight = Pnt2f(0.0f, 0.0f);
	}
	
	Inherited::mouseMoved(e);
}

void FunctionComponentPanel::keyReleased(const KeyEvent& e)
{
	std::cout << "Key Released " << e.getKey() << std::endl;
	std::cout << "Modifier Released " << e.getModifiers() << std::endl;
	if(e.getKey() == KeyEvent::KEY_CONTROL)
	{
		_drawComponentResizeSquares = false;
		_ResizableComponentTopLeft = Pnt2f(0.0f, 0.0f);
		_ResizableComponentBottomRight = Pnt2f(0.0f, 0.0f);
	}
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
        _ComponentMoveListener(FunctionComponentPanelPtr(this))
{
	//getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseWheelListener(_MouseWheelListener);
}

FunctionComponentPanel::FunctionComponentPanel(const FunctionComponentPanel &source) :
    Inherited(source),
        _ComponentMoveListener(FunctionComponentPanelPtr(this))
{
	//getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseWheelListener(_MouseWheelListener);
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
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            beginEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
                getChildren()[i]->setPosition(Pnt2f(0.0f,0.0f));
                getChildren()[i]->setSize(getChildren()[i]->getRequestedSize());
            endEditCP(getChildren()[i], Component::PositionFieldMask | Component::SizeFieldMask);
        }
    }
	
	
    if(whichField & ZoomFieldMask)
    {
			/*std::cout << "getPreferredSize: " << getPreferredSize() << std::endl;
            beginEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomedPreferredSizeFieldMask);
				setZoomedPreferredSize(getPreferredSize()*getZoom());
            endEditCP(FunctionComponentPanelPtr(this), FunctionComponentPanel::ZoomedPreferredSizeFieldMask);
			std::cout << "getZoomedPreferredSize: " << getZoomedPreferredSize() << std::endl;*/
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


void FunctionComponentPanel::ComponentMoveListener::mouseReleased(const MouseEvent& e)
{
	detach();
}

void FunctionComponentPanel::ComponentMoveListener::keyPressed(const KeyEvent& e)
{
    //TODO:Implement
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		detach();
		
		//Set the Active Component's Position back to it's initial position
		beginEditCP(_ActiveComponent, Component::PositionFieldMask);	
			_ActiveComponent->setPosition(_InitialComponentPosition);
		endEditCP(_ActiveComponent, Component::PositionFieldMask);

	}
}

void FunctionComponentPanel::ComponentMoveListener::mouseDragged(const MouseEvent& e)
{
    
	if(_ActiveComponent != NullFC && _ActiveComponent->getParentContainer() != NullFC)
	{
		//Move the Position of the Component based on the mouse position and it's initial position
		Pnt2f InitialPositionsDifference = Pnt2f(_InitialComponentPosition - ViewportToComponent(_InitialPosition, _ActiveComponent->getParentContainer(), e.getViewport()));
		Pnt2f AbsolutePosition = Pnt2f(ViewportToComponent(e.getLocation(), _ActiveComponent->getParentContainer(), e.getViewport()) + InitialPositionsDifference);
		Pnt2f NewPosition = AbsolutePosition;
		
		//Test AbsolutePosition to make sure Component is inside parent container
		Pnt2f AbsolutePositionBottomRight, ContainerTopLeft, ContainerBottomRight;
		AbsolutePositionBottomRight = AbsolutePosition + _ActiveComponent->getSize();
		_ActiveComponent->getParentContainer()->getInsideInsetsBounds(ContainerTopLeft, ContainerBottomRight);
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
			NewPosition[0] = ContainerBottomRight.x() - _ActiveComponent->getSize().x();
		}
		if(AbsolutePositionBottomRight.y() > ContainerBottomRight.y())
		{
			NewPosition[1] = ContainerBottomRight.y() - _ActiveComponent->getSize().y();
		}
		
		//Set new position
		beginEditCP(_ActiveComponent, Component::PositionFieldMask);
			_ActiveComponent->setPosition(NewPosition);
		endEditCP(_ActiveComponent, Component::PositionFieldMask);
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

void FunctionComponentPanel::ComponentMoveListener::setActiveComponent(ComponentPtr TheComponent)
{
	_ActiveComponent = TheComponent;
	if(_ActiveComponent != NullFC)
	{
		_InitialComponentPosition = _ActiveComponent->getPosition();
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
    static Char8 cvsid_hpp       [] = OSGFUNCTIONCOMPONENTPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFUNCTIONCOMPONENTPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFUNCTIONCOMPONENTPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

