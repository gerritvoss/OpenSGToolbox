/*---------------------------------------------------------------------------*\
 *                      OpenSG ToolBox UserInterface                         *
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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>

#include "OSGComponent.h"
#include "Component/Container/OSGContainer.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "UIDrawingSurface/OSGUIDrawingSurfaceMouseTransformFunctor.h"
#include "Component/Misc/OSGToolTip.h"
#include "Util/OSGUIDrawUtils.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Scroll/OSGScrollBar.h"

#include "Component/Misc/OSGRotatedComponent.h"


#include "Component/Container/OSGUIViewport.h"
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Component
A UI Component Interface.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  Component::BordersFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::BorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledBorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedBorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverBorderFieldId);

const OSG::BitVector  Component::BackgroundsFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::BackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledBackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedBackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverBackgroundFieldId);

const OSG::BitVector  Component::ForegroundsFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::ForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverForegroundFieldId);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Component::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Pnt2f Component::getParentToLocal(const Pnt2f& Location)
{
    return Location - getPosition();
}

UInt32 Component::queryCursor(const Pnt2f& CursorLoc) const
{
	return WindowEventProducer::CURSOR_POINTER;
}

Vec2f Component::getRequestedSize(void) const
{
	return getBorderingLength() + getContentRequestedSize();
}

Vec2f Component::getContentRequestedSize(void) const
{
	return Vec2f(0.0,0.0);
}

Vec2f Component::getBorderingLength(void) const
{
	Pnt2f BoundsTopLeft, BoundsBottomRight;
	Pnt2f InsideBorderTopLeft, InsideBorderBottomRight;
	
	getBounds(BoundsTopLeft, BoundsBottomRight);
	getInsideBorderBounds(InsideBorderTopLeft, InsideBorderBottomRight);
	
	return (BoundsBottomRight - BoundsTopLeft) - (InsideBorderBottomRight - InsideBorderTopLeft);
}

void Component::setBorders(BorderPtr TheBorder)
{
	setBorder(TheBorder);
	setDisabledBorder(TheBorder);
	setFocusedBorder(TheBorder);
	setRolloverBorder(TheBorder);
}

void Component::setBackgrounds(LayerPtr TheBackground)
{
	setBackground(TheBackground);
	setDisabledBackground(TheBackground);
	setFocusedBackground(TheBackground);
	setRolloverBackground(TheBackground);
}


void Component::setForegrounds(LayerPtr TheForeground)
{
	setForeground(TheForeground);
	setDisabledForeground(TheForeground);
	setFocusedForeground(TheForeground);
	setRolloverForeground(TheForeground);
}

BorderPtr Component::getDrawnBorder(void) const
{
	if(getEnabled())
	{
        if(getFocused())
        {
            return getFocusedBorder();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBorder();
        }
        else
        {
            return getBorder();
        }
    }
    else
    {
        return getDisabledBorder();
    }
}

LayerPtr Component::getDrawnBackground(void) const
{
	if(getEnabled())
	{
        if(getFocused())
        {
            return getFocusedBackground();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBackground();
        }
        else
        {
            return getBackground();
        }
    }
    else
    {
        return getDisabledBackground();
    }
}

LayerPtr Component::getDrawnForeground(void) const
{
	if(getEnabled())
	{
        if(getFocused())
        {
            return getFocusedForeground();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverForeground();
        }
        else
        {
            return getForeground();
        }
    }
    else
    {
        return getDisabledForeground();
    }
}

bool Component::isContained(const Pnt2f& p, bool TestAgainstClipBounds) const
{
    Pnt2f PointInCompSpace(DrawingSurfaceToComponent(p,ComponentPtr(this)));
    BorderPtr DrawnBorder(getDrawnBorder());
    Pnt2f TopLeft, BottomRight;
    if(TestAgainstClipBounds && getClipping())
    {
        TopLeft = getClipTopLeft();
        BottomRight = getClipBottomRight();
    }
    else
    {
        TopLeft.setValues(0,0);
        BottomRight = Pnt2f(getSize());
    }
    
    if(DrawnBorder == NullFC)
    {
        return isContainedBounds(PointInCompSpace, TopLeft, BottomRight);
    }
    else
    {
        return isContainedBounds(PointInCompSpace, TopLeft, BottomRight) && 
            DrawnBorder->isContained(PointInCompSpace,0,0,getSize().x(),getSize().y());
    }
}

Pnt2f Component::getToolTipLocation(Pnt2f MousePosition)
{
    //TODO:Implement
    return DrawingSurfaceToComponent(MousePosition,ComponentPtr(this)) + Vec2f(5,20);
}

ToolTipPtr Component::createToolTip(void)
{
    return ToolTip::create();
}

void Component::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   TopLeft = Pnt2f(0,0);
   BottomRight = Pnt2f(getSize());
}

void Component::getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   Real32 TopInset(0), LeftInset(0), BottomInset(0), RightInset(0);

   if(getBorder() != NullFC)
   {
      //Get Border Insets
      getBorder()->getInsets(LeftInset,RightInset,TopInset,BottomInset);
   }
   TopLeft.setValues(LeftInset, TopInset);
   BottomRight.setValues(TopLeft.x()+getSize().x()-(LeftInset + RightInset), TopLeft.y()+getSize().y()-(TopInset + BottomInset));
}

void Component::getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    Pnt2f ParentContainerTopLeft(0,0),ParentContainerBottomRight(0,0);
    if(getParentContainer() != NullFC)
    {
        Container::Ptr::dcast(getParentContainer())->getBoundsRenderingSurfaceSpace(ParentContainerTopLeft, ParentContainerBottomRight);
    }
    TopLeft = ParentContainerTopLeft + Vec2f(getPosition());
    BottomRight = TopLeft + getSize();
}

void Component::drawBorder(const GraphicsPtr TheGraphics, const BorderPtr Border) const
{
   if(Border != NullFC)
   {
      //Draw My Border
      Border->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity());
   }
}

void Component::drawBackground(const GraphicsPtr TheGraphics, const LayerPtr Background) const
{
   //Draw the Background on the Inside of my border
   if(Background != NullFC)
   {
       Pnt2f TopLeft, BottomRight;
       getInsideBorderBounds(TopLeft, BottomRight);
	   Background->draw(TheGraphics, TopLeft, BottomRight, getOpacity());
   }
}

void Component::drawForeground(const GraphicsPtr TheGraphics, const LayerPtr Foreground) const
{
   //Draw the Foreground on the Inside of my border
   if(Foreground != NullFC)
   {
       Pnt2f TopLeft, BottomRight;
       getInsideBorderBounds(TopLeft, BottomRight);
	   Foreground->draw(TheGraphics, TopLeft, BottomRight, getOpacity());
   }
}

bool Component::setupClipping(const GraphicsPtr Graphics) const
{
    //Get Clipping initial settings
    //bool WasClippingEnabled = glIsEnabled(GL_SCISSOR_TEST);
    GLboolean WasClippPlane0Enabled = glIsEnabled(GL_CLIP_PLANE0);
    GLboolean WasClippPlane1Enabled = glIsEnabled(GL_CLIP_PLANE1);
    GLboolean WasClippPlane2Enabled = glIsEnabled(GL_CLIP_PLANE2);
    GLboolean WasClippPlane3Enabled = glIsEnabled(GL_CLIP_PLANE3);
    if(getClipping())
    {
        //glClipPlane
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        Pnt2f ClipTopLeft,ClipBottomRight;
		getClipBounds(ClipTopLeft,ClipBottomRight);
        if(ClipBottomRight.x()-ClipTopLeft.x() <= 0 || ClipBottomRight.y()-ClipTopLeft.y()<= 0)
        {
            return false;
        }

        if(!WasClippPlane0Enabled) { glEnable(GL_CLIP_PLANE0); }
        if(!WasClippPlane1Enabled) { glEnable(GL_CLIP_PLANE1); }
        if(!WasClippPlane2Enabled) { glEnable(GL_CLIP_PLANE2); }
        if(!WasClippPlane3Enabled) { glEnable(GL_CLIP_PLANE3); }
        
        //Clip Plane Equations
        //Clip Planes get transformed by the ModelViewMatrix when set
        //So we can rely on the fact that our current coordinate space
        //is relative to the this components position
		Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ClipTopLeft.x()+ Graphics->getClipPlaneOffset()),
              RightPlaneEquation(-1.0,0.0,0.0,ClipBottomRight.x() + Graphics->getClipPlaneOffset()),
              TopPlaneEquation(0.0,1.0,0.0,-ClipTopLeft.y() + Graphics->getClipPlaneOffset()),
              BottomPlaneEquation(0.0,-1.0,0.0,ClipBottomRight.y() + Graphics->getClipPlaneOffset());
        
        glClipPlane(GL_CLIP_PLANE0,LeftPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE1,RightPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE2,TopPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE3,BottomPlaneEquation.getValues());
    }
	return true;
}

void Component::draw(const GraphicsPtr TheGraphics) const
{
	if (!getVisible())
		return;

    //Translate to my position
    glTranslatef(getPosition().x(), getPosition().y(), 0);

	if(!setupClipping(TheGraphics))
	{
		//Translate to my position
		glTranslatef(-getPosition().x(), -getPosition().y(), 0);
		return;
	}

	//Draw My Border
    BorderPtr DrawnBorder = getDrawnBorder();
	drawBorder(TheGraphics, DrawnBorder);

    //Activate Border Drawing Constrants
    if(DrawnBorder != NullFC)
    {
        DrawnBorder->activateInternalDrawConstraints(TheGraphics,0,0,getSize().x(),getSize().y());
    }

    
	//Draw My Background
	drawBackground(TheGraphics, getDrawnBackground());

    //Draw Internal
    drawInternal(TheGraphics);
    
	//Draw My Foreground
	drawForeground(TheGraphics, getDrawnForeground());
    
    //Deactivate Border Drawing Constrants
    if(DrawnBorder != NullFC)
    {
        DrawnBorder->deactivateInternalDrawConstraints(TheGraphics,0,0,getSize().x(),getSize().y());
    }


    //Undo the Translation to Component Space
    glTranslatef(-getPosition().x(), -getPosition().y(), 0);
    
    //Set Clipping to initial settings
    if(getClipping())
    {
		//TODO:Fix
        //if(!WasClippPlane0Enabled){glDisable(GL_CLIP_PLANE0);}
        //if(!WasClippPlane1Enabled){glDisable(GL_CLIP_PLANE1);}
        //if(!WasClippPlane2Enabled){glDisable(GL_CLIP_PLANE2);}
        //if(!WasClippPlane3Enabled){glDisable(GL_CLIP_PLANE3);}
    }
}


void Component::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	if(getParentContainer() == NullFC ||
        getParentContainer()->getType() == RotatedComponent::getClassType())
	{
		//If I have no parent container use my bounds
		getBounds(TopLeft, BottomRight);
	}
	else
	{
		//Get the intersection of:
		     //My Bounds
		     //My Parent Containers Clip Bounds
		     //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Update my Parent Container's Clip Bounds
		//Container::Ptr::dcast(getParentContainer())->updateClipBounds();

		//Get Parent Container's Clip Bounds
		Pnt2f ContainerClipTopLeft, ContainerClipBottomRight;
		Container::Ptr::dcast(getParentContainer())->getClipBounds(ContainerClipTopLeft,ContainerClipBottomRight);
		
        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
		ContainerClipBottomRight -= Vec2f(getPosition());

		//Get Parent Container's Inset Bounds
		Pnt2f ContainerInsetTopLeft, ContainerInsetBottomRight;
		Container::Ptr::dcast(getParentContainer())->getInsideInsetsBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);
		
        //Parent Container's Inset Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerInsetTopLeft -= Vec2f(getPosition());
		ContainerInsetBottomRight -= Vec2f(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);

		quadIntersection(TopLeft,BottomRight,
			ContainerInsetTopLeft,ContainerInsetBottomRight,
			TopLeft, BottomRight);
	}
	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	beginEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
}

void Component::mouseClicked(const MouseEvent& e)
{
	produceMouseClicked(e);
}

void Component::mouseEntered(const MouseEvent& e)
{
	produceMouseEntered(e);
}

void Component::mouseExited(const MouseEvent& e)
{
	produceMouseExited(e);
}

void Component::mousePressed(const MouseEvent& e)
{
	produceMousePressed(e);

	if(e.getButton() == MouseEvent::BUTTON3
	&& getPopupMenu() != NullFC)
	{
	    beginEditCP(getPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
	       getPopupMenu()->setInvoker(ComponentPtr(this));
	       getPopupMenu()->setVisible(true);
	       getPopupMenu()->setPosition(DrawingSurfaceToComponent(e.getLocation(),getParentWindow()));
	    endEditCP(getPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
	    
        beginEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
            getParentWindow()->getActivePopupMenus().push_back(getPopupMenu());
        endEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
	}
}

void Component::mouseReleased(const MouseEvent& e)
{
	produceMouseReleased(e);
}


void Component::mouseMoved(const MouseEvent& e)
{
	
	if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
		getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(queryCursor(e.getLocation()));
	}
	produceMouseMoved(e);
}

void Component::mouseDragged(const MouseEvent& e)
{
	produceMouseDragged(e);
}

void Component::mouseWheelMoved(const MouseWheelEvent& e)
{
	produceMouseWheelMoved(e);
}

void Component::keyPressed(const KeyEvent& e)
{
	produceKeyPressed(e);
}

void Component::keyReleased(const KeyEvent& e)
{
	produceKeyReleased(e);
}

void Component::keyTyped(const KeyEvent& e)
{
	produceKeyTyped(e);
}

void Component::focusGained(const FocusEvent& e)
{
	produceFocusGained(e);
}

void Component::focusLost(const FocusEvent& e)
{
	produceFocusLost(e);
}

//Producers
void Component::produceMouseWheelMoved(const MouseWheelEvent& e)
{
   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseWheelMoved(e);
   }
}

void Component::produceMouseMoved(const MouseEvent& e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->mouseMoved(e);
   }
}

void Component::produceMouseDragged(const MouseEvent& e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseDragged(e);
   }
}

void Component::produceMouseClicked(const MouseEvent& e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseClicked(e);
   }
}

void Component::produceMouseEntered(const MouseEvent& e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseEntered(e);
   }
}

void Component::produceMouseExited(const MouseEvent& e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseExited(e);
   }
}

void Component::produceMousePressed(const MouseEvent& e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mousePressed(e);
   }
}

void Component::produceMouseReleased(const MouseEvent& e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseReleased(e);
   }
}

void Component::produceKeyPressed(const KeyEvent& e)
{
	KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->keyPressed(e);
   }
}

void Component::produceKeyReleased(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyReleased(e);
   }
}

void Component::produceKeyTyped(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyTyped(e);
   }
}

void  Component::produceFocusGained(const FocusEvent& e)
{
	FocusListenerSet ListenerSet(_FocusListeners);
   for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->focusGained(e);
   }
}

void  Component::produceFocusLost(const FocusEvent& e)
{
	FocusListenerSet ListenerSet(_FocusListeners);
   for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->focusLost(e);
   }
}

void  Component::produceComponentHidden(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentHidden(e);
   }
}

void  Component::produceComponentVisible(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentVisible(e);
   }
}

void  Component::produceComponentMoved(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentMoved(e);
   }
}

void  Component::produceComponentResized(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentResized(e);
   }
}

void  Component::produceComponentEnabled(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentEnabled(e);
   }
}

void  Component::produceComponentDisabled(const ComponentEvent& e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentDisabled(e);
   }
}

bool Component::giveFocus(ComponentPtr NewFocusedComponent, bool Temporary)
{
    if(!getFocusable())
    {
        return false;
    }
    else if(ComponentPtr(this) == NewFocusedComponent)
    {
		return true;
    }
	else
	{
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(false);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
        focusLost(FocusEvent(ComponentPtr(this),getSystemTime(),FocusEvent::FOCUS_LOST,Temporary, NewFocusedComponent));
		return true;
	}
}

bool Component::takeFocus(bool Temporary)
{
    if(!getFocusable())
    {
        return false;
    }
    else
    {
		if(getFocused() &&
		   getParentWindow() != NullFC &&
		   getParentWindow()->getFocusedComponent() == ComponentPtr(this))
		{
			return true;
		}
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(true);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
		if(Temporary || getParentWindow() == NullFC)
		{
            focusGained(FocusEvent(ComponentPtr(this),getSystemTime(),FocusEvent::FOCUS_GAINED,Temporary, NullFC));
		}
		else
		{
			if(getParentWindow()->getFocusedComponent() != NullFC)
			{
				getParentWindow()->getFocusedComponent()->giveFocus(ComponentPtr(this));
			}
		    getParentWindow()->setFocusedComponent(ComponentPtr(this));
            focusGained(FocusEvent(ComponentPtr(this),getSystemTime(),FocusEvent::FOCUS_GAINED,Temporary, getParentWindow()->getFocusedComponent()));
			//beginEditCP(getParentWindow(), InternalWindow::FocusedComponentFieldMask);
			//endEditCP(getParentWindow(), InternalWindow::FocusedComponentFieldMask);
		}
		return true;
    }
}

Real32 Component::getBaseline(const Real32& x, const Real32& y) const
{
    return -1;
}

Vec2f Component::getPreferredScrollableViewportSize(void)
{
    return getPreferredSize();
}

Int32 Component::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
}

bool Component::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool Component::getScrollableTracksViewportWidth(void)
{
    return false;
}

Int32 Component::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * 5;
}

void Component::scrollToPoint(const Pnt2f& PointInComponent)
{
	if(getParentContainer() != NullFC &&
		getParentContainer()->getType() == UIViewport::getClassType())
	{
		beginEditCP(getParentContainer(), UIViewport::ViewPositionFieldMask);
			UIViewport::Ptr::dcast(getParentContainer())->setViewPosition(PointInComponent);
		endEditCP(getParentContainer(), UIViewport::ViewPositionFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Component::Component(void) :
    Inherited(),
		_MouseInComponentLastMouse(false),
        _TimeSinceMouseEntered(0.0),
        _ComponentUpdater(ComponentPtr(this)),
        _ActivateToolTipListener(ComponentPtr(this)),
        _DeactivateToolTipListener(ComponentPtr(this))
{
}

Component::Component(const Component &source) :
    Inherited(source),
		_MouseInComponentLastMouse(false),
        _TimeSinceMouseEntered(0.0),
        _ComponentUpdater(ComponentPtr(this)),
        _ActivateToolTipListener(ComponentPtr(this)),
        _DeactivateToolTipListener(ComponentPtr(this))
{
}

Component::~Component(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Component::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if( (whichField & MinSizeFieldMask) ||
        (whichField & MaxSizeFieldMask) ||
        (whichField & PreferredSizeFieldMask) ||
        (whichField & ConstraintsFieldMask))
    {
        //Layout needs to be recalculated for my parent Container
        updateContainerLayout();
    }
	
    if( (whichField & SizeFieldMask) ||
        (whichField & PositionFieldMask) )
	{
		updateClipBounds();
	}

    if( (whichField & ConstraintsFieldMask) &&
        getConstraints() != NullFC)
    {
        beginEditCP(getConstraints(), LayoutConstraints::ParentComponentFieldMask);
           getConstraints()->setParentComponent(ComponentPtr(this));
        endEditCP(getConstraints(), LayoutConstraints::ParentComponentFieldMask);
    }
    
    if( (whichField & SizeFieldMask) )
    {
        produceComponentResized( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_RESIZED, ComponentPtr(this)) );
    }
    if( (whichField & PositionFieldMask) )
    {
        produceComponentMoved( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_MOVED, ComponentPtr(this)) );
    }
    if( (whichField & EnabledFieldMask) )
    {
        if(getEnabled())
        {
            produceComponentEnabled( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_ENABLED, ComponentPtr(this)) );    
        }
        else
        {
            produceComponentDisabled( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_DISABLED, ComponentPtr(this)) );    
        }
     }
    if( (whichField & VisibleFieldMask) )
    {
        if(getVisible())
        {
            produceComponentVisible( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_VISIBLE, ComponentPtr(this)) );    
        }
        else
        {
            produceComponentHidden( ComponentEvent(ComponentPtr(this),getSystemTime(),ComponentEvent::COMPONENT_HIDDEN, ComponentPtr(this)) );    
        }
     }
    
    if( (whichField & ToolTipTextFieldMask))
    {
        if(getToolTipText().compare(std::string("")) != 0)
        {
            addMouseListener(&_ActivateToolTipListener);
        }
        else
        {
            removeMouseListener(&_ActivateToolTipListener);
        }
    }
}

void Component::updateContainerLayout(void)
{
    if(getParentContainer() != NullFC)
    {
        Container::Ptr::dcast(getParentContainer())->updateLayout();
    }
}

void Component::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Component NI" << std::endl;
}


void Component::ComponentUpdater::update(const UpdateEvent& e)
{
    _Component->_TimeSinceMouseEntered += e.getElapsedTime();
    if(_Component->_TimeSinceMouseEntered >= LookAndFeelManager::the()->getLookAndFeel()->getToolTipPopupTime() &&
        _Component->getParentWindow() != NullFC &&
        _Component->getParentWindow()->getActiveToolTip() == NullFC)
    {
        ToolTipPtr TheToolTip = _Component->createToolTip();
        beginEditCP(TheToolTip, ToolTip::TippedComponentFieldMask | ToolTip::PositionFieldMask | ToolTip::TextFieldMask);
            TheToolTip->setTippedComponent(_Component);
            if(_Component->getParentWindow() != NullFC &&
               _Component->getParentWindow()->getDrawingSurface() != NullFC)
            {
                TheToolTip->setPosition(ComponentToFrame(_Component->getToolTipLocation(
                    _Component->getParentWindow()->getDrawingSurface()->getMousePosition()), _Component));
            }
            else
            {
                TheToolTip->setPosition(ComponentToFrame(_Component->getToolTipLocation(Pnt2f(0,0)),_Component));
            }
            TheToolTip->setText(_Component->getToolTipText());
        endEditCP(TheToolTip, ToolTip::TippedComponentFieldMask | ToolTip::PositionFieldMask | ToolTip::TextFieldMask);

        if(_Component->getParentWindow() != NullFC)
        {
            beginEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
                _Component->getParentWindow()->setActiveToolTip(TheToolTip);
            endEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
        }
        
        _Component->addMouseListener(&(_Component->_DeactivateToolTipListener));
    }
}

void Component::ActivateToolTipListener::mouseClicked(const MouseEvent& e)
{
}

void Component::ActivateToolTipListener::mouseEntered(const MouseEvent& e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
	if( _Component->getParentWindow() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_Component->_ComponentUpdater));
	}
}

void Component::ActivateToolTipListener::mouseExited(const MouseEvent& e)
{
    if( _Component->getParentWindow() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&(_Component->_ComponentUpdater));
	}
}

void Component::ActivateToolTipListener::mousePressed(const MouseEvent& e)
{
}

void Component::ActivateToolTipListener::mouseReleased(const MouseEvent& e)
{
}

void Component::DeactivateToolTipListener::mouseClicked(const MouseEvent& e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NullFC)
    {
        beginEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
                _Component->getParentWindow()->setActiveToolTip(NullFC);
        endEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
    }
    _Component->removeMouseListener(this);
}

void Component::DeactivateToolTipListener::mouseEntered(const MouseEvent& e)
{
}

void Component::DeactivateToolTipListener::mouseExited(const MouseEvent& e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NullFC)
    {
        beginEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
                _Component->getParentWindow()->setActiveToolTip(NullFC);
        endEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
    }
    _Component->removeMouseListener(this);

}

void Component::DeactivateToolTipListener::mousePressed(const MouseEvent& e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NullFC)
    {
        beginEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
                _Component->getParentWindow()->setActiveToolTip(NullFC);
        endEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
    }
    _Component->removeMouseListener(this);
}

void Component::DeactivateToolTipListener::mouseReleased(const MouseEvent& e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NullFC)
    {
        beginEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
                _Component->getParentWindow()->setActiveToolTip(NullFC);
        endEditCP(_Component->getParentWindow(), InternalWindow::ActiveToolTipFieldMask);
    }
    _Component->removeMouseListener(this);
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
    static Char8 cvsid_hpp       [] = OSGCOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

