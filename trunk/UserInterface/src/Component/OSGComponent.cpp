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

#include <boost/bind.hpp>

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

EventConnection Component::addKeyListener(KeyListenerPtr Listener)
{
   _KeyListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isKeyListenerAttached, this, Listener),
       boost::bind(&Component::removeKeyListener, this, Listener));
}

void Component::removeKeyListener(KeyListenerPtr Listener)
{
   KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
   if(EraseIter != _KeyListeners.end())
   {
      _KeyListeners.erase(EraseIter);
   }
}

EventConnection Component::addMouseListener(MouseListenerPtr Listener)
{
   _MouseListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isMouseListenerAttached, this, Listener),
       boost::bind(&Component::removeMouseListener, this, Listener));
}

void Component::removeMouseListener(MouseListenerPtr Listener)
{
   MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
   if(EraseIter != _MouseListeners.end())
   {
      _MouseListeners.erase(EraseIter);
   }
}

EventConnection Component::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
   _MouseWheelListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isMouseWheelListenerAttached, this, Listener),
       boost::bind(&Component::removeMouseWheelListener, this, Listener));
}

void Component::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
   MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
   if(EraseIter != _MouseWheelListeners.end())
   {
      _MouseWheelListeners.erase(EraseIter);
   }
}

EventConnection Component::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
   _MouseMotionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isMouseMotionListenerAttached, this, Listener),
       boost::bind(&Component::removeMouseMotionListener, this, Listener));
}

void Component::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
   MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
   if(EraseIter != _MouseMotionListeners.end())
   {
      _MouseMotionListeners.erase(EraseIter);
   }
}

EventConnection Component::addFocusListener(FocusListenerPtr Listener)
{
   _FocusListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isFocusListenerAttached, this, Listener),
       boost::bind(&Component::removeFocusListener, this, Listener));
}

void Component::removeFocusListener(FocusListenerPtr Listener)
{
   FocusListenerSetItor EraseIter(_FocusListeners.find(Listener));
   if(EraseIter != _FocusListeners.end())
   {
      _FocusListeners.erase(EraseIter);
   }
}

EventConnection Component::addComponentListener(ComponentListener* Listener)
{
   _ComponentListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Component::isComponentListenerAttached, this, Listener),
       boost::bind(&Component::removeComponentListener, this, Listener));
}

void Component::removeComponentListener(ComponentListener* Listener)
{
   ComponentListenerSetItor EraseIter(_ComponentListeners.find(Listener));
   if(EraseIter != _ComponentListeners.end())
   {
      _ComponentListeners.erase(EraseIter);
   }
}

Pnt2f Component::getClipTopLeft(void) const
{
	return Pnt2f(ComponentBase::getClipBounds()[0], ComponentBase::getClipBounds()[1]);
}

Pnt2f Component::getClipBottomRight(void) const
{
	return Pnt2f(ComponentBase::getClipBounds()[2], ComponentBase::getClipBounds()[3]);
}

void Component::setClipTopLeft    (const Pnt2f &value)
{
	setClipBounds(Pnt4f(value[0], value[1], ComponentBase::getClipBounds()[2],ComponentBase::getClipBounds()[3]));
}

void Component::setClipBottomRight(const Pnt2f &value)
{
	setClipBounds(Pnt4f(ComponentBase::getClipBounds()[0],ComponentBase::getClipBounds()[1], value[0], value[1]));
}

Pnt2f Component::getParentToLocal(const Pnt2f& Location)
{
    return Location - getPosition();
}

Pnt2f Component::getLocalToParent(const Pnt2f& Location)
{
    return Location + getPosition();
}

UInt32 Component::queryCursor(const Pnt2f& CursorLoc) const
{
	return getCursor();
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
      Border->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity(), getClipping());
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

    if(getClipping())
    {    
		//Get Clipping initial settings
		Pnt2f ClipTopLeft,ClipBottomRight;
		getClipBounds(ClipTopLeft,ClipBottomRight);

		Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ClipTopLeft.x()+ Graphics->getClipPlaneOffset()),
		  RightPlaneEquation(-1.0,0.0,0.0,ClipBottomRight.x() + Graphics->getClipPlaneOffset()),
		  TopPlaneEquation(0.0,1.0,0.0,-ClipTopLeft.y() + Graphics->getClipPlaneOffset()),
		  BottomPlaneEquation(0.0,-1.0,0.0,ClipBottomRight.y() + Graphics->getClipPlaneOffset());

        //glClipPlane
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        if(ClipBottomRight.x()-ClipTopLeft.x() <= 0 || ClipBottomRight.y()-ClipTopLeft.y()<= 0)
        {
			return false;
        }

        if(!glIsEnabled(GL_CLIP_PLANE0)) { glEnable(GL_CLIP_PLANE0); }
        if(!glIsEnabled(GL_CLIP_PLANE1)) { glEnable(GL_CLIP_PLANE1); }
        if(!glIsEnabled(GL_CLIP_PLANE2)) { glEnable(GL_CLIP_PLANE2); }
        if(!glIsEnabled(GL_CLIP_PLANE3)) { glEnable(GL_CLIP_PLANE3); }
        
        //Clip Plane Equations
        //Clip Planes get transformed by the ModelViewMatrix when set
        //So we can rely on the fact that our current coordinate space
        //is relative to the this components position
        
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

	//Activate My Border Drawing constraints
    BorderPtr DrawnBorder = getDrawnBorder();
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
    
    //Set Clipping to initial settings
	setupClipping(TheGraphics);

    //Draw all parts that should not be clipped against
    drawUnclipped(TheGraphics);

    //Undo the Translation to Component Space
    glTranslatef(-getPosition().x(), -getPosition().y(), 0);
}


void Component::drawUnclipped(const GraphicsPtr TheGraphics) const
{
	//Draw Border
	drawBorder(TheGraphics, getDrawnBorder());
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
	beginEditCP(ComponentPtr(this), Component::ClipBoundsFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipBoundsFieldMask);
}

void Component::mouseClicked(const MouseEventPtr e)
{
	produceMouseClicked(e);
}

void Component::mouseEntered(const MouseEventPtr e)
{
	produceMouseEntered(e);
}

void Component::mouseExited(const MouseEventPtr e)
{
	produceMouseExited(e);
}

void Component::mousePressed(const MouseEventPtr e)
{
	produceMousePressed(e);

	if(e->getButton() == MouseEvent::BUTTON3
	&& getPopupMenu() != NullFC)
	{
	    beginEditCP(getPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
	       getPopupMenu()->setInvoker(ComponentPtr(this));
	       getPopupMenu()->setVisible(true);
	       getPopupMenu()->setPosition(ViewportToComponent(e->getLocation(),getParentWindow(),e->getViewport()));
	    endEditCP(getPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
	    
        beginEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
            getParentWindow()->getActivePopupMenus().push_back(getPopupMenu());
        endEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
	}
}

void Component::mouseReleased(const MouseEventPtr e)
{
	produceMouseReleased(e);
}


void Component::mouseMoved(const MouseEventPtr e)
{
	
	if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
		getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(queryCursor(e->getLocation()));
	}
	produceMouseMoved(e);
}

void Component::mouseDragged(const MouseEventPtr e)
{
	produceMouseDragged(e);
}

void Component::mouseWheelMoved(const MouseWheelEventPtr e)
{
	produceMouseWheelMoved(e);
}

void Component::keyPressed(const KeyEventPtr e)
{
	produceKeyPressed(e);
}

void Component::keyReleased(const KeyEventPtr e)
{
	produceKeyReleased(e);
}

void Component::keyTyped(const KeyEventPtr e)
{
	produceKeyTyped(e);
}

void Component::focusGained(const FocusEventPtr e)
{
	produceFocusGained(e);
}

void Component::focusLost(const FocusEventPtr e)
{
	produceFocusLost(e);
}

//Producers
void Component::produceMouseWheelMoved(const MouseWheelEventPtr e)
{
   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseWheelMoved(e);
   }
   _Producer.produceEvent(MouseWheelMovedMethodId,e);
}

void Component::produceMouseMoved(const MouseEventPtr e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->mouseMoved(e);
   }
   _Producer.produceEvent(MouseMovedMethodId,e);
}

void Component::produceMouseDragged(const MouseEventPtr e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseDragged(e);
   }
   _Producer.produceEvent(MouseDraggedMethodId,e);
}

void Component::produceMouseClicked(const MouseEventPtr e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseClicked(e);
   }
   _Producer.produceEvent(MouseClickedMethodId,e);
}

void Component::produceMouseEntered(const MouseEventPtr e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseEntered(e);
   }
   _Producer.produceEvent(MouseEnteredMethodId,e);
}

void Component::produceMouseExited(const MouseEventPtr e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseExited(e);
   }
   _Producer.produceEvent(MouseExitedMethodId,e);
}

void Component::produceMousePressed(const MouseEventPtr e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mousePressed(e);
   }
   _Producer.produceEvent(MousePressedMethodId,e);
}

void Component::produceMouseReleased(const MouseEventPtr e)
{
	MouseListenerSet ListenerSet(_MouseListeners);
   for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->mouseReleased(e);
   }
   _Producer.produceEvent(MouseReleasedMethodId,e);
}

void Component::produceKeyPressed(const KeyEventPtr e)
{
	KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->keyPressed(e);
   }
   _Producer.produceEvent(KeyPressedMethodId,e);
}

void Component::produceKeyReleased(const KeyEventPtr e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyReleased(e);
   }
   _Producer.produceEvent(KeyReleasedMethodId,e);
}

void Component::produceKeyTyped(const KeyEventPtr e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyTyped(e);
   }
   _Producer.produceEvent(KeyTypedMethodId,e);
}

void  Component::produceFocusGained(const FocusEventPtr e)
{
	FocusListenerSet ListenerSet(_FocusListeners);
   for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->focusGained(e);
   }
   _Producer.produceEvent(FocusGainedMethodId,e);
}

void  Component::produceFocusLost(const FocusEventPtr e)
{
	FocusListenerSet ListenerSet(_FocusListeners);
   for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->focusLost(e);
   }
   _Producer.produceEvent(FocusLostMethodId,e);
}

void  Component::produceComponentHidden(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentHidden(e);
   }
   _Producer.produceEvent(ComponentHiddenMethodId,e);
}

void  Component::produceComponentVisible(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentVisible(e);
   }
   _Producer.produceEvent(ComponentVisibleMethodId,e);
}

void  Component::produceComponentMoved(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentMoved(e);
   }
   _Producer.produceEvent(ComponentMovedMethodId,e);
}

void  Component::produceComponentResized(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentResized(e);
   }
   _Producer.produceEvent(ComponentResizedMethodId,e);
}

void  Component::produceComponentEnabled(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentEnabled(e);
   }
   _Producer.produceEvent(ComponentEnabledMethodId,e);
}

void  Component::produceComponentDisabled(const ComponentEventPtr e)
{
   for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
   {
      (*SetItor)->componentDisabled(e);
   }
   _Producer.produceEvent(ComponentDisabledMethodId,e);
}

bool Component::giveFocus(ComponentPtr NewFocusedComponent, bool Temporary)
{
	if(ComponentPtr(this) == NewFocusedComponent)
    {
		return true;
    }
	else
	{
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(false);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
        focusLost(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, NewFocusedComponent));
		return true;
	}
}

bool Component::takeFocus(bool Temporary)
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
        focusGained(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, NullFC));
	}
	else
	{
		if(getParentWindow()->getFocusedComponent() != NullFC)
		{
			getParentWindow()->getFocusedComponent()->giveFocus(ComponentPtr(this));
		}
	    getParentWindow()->setFocusedComponent(ComponentPtr(this));
        focusGained(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, getParentWindow()->getFocusedComponent()));
		//beginEditCP(getParentWindow(), InternalWindow::FocusedComponentFieldMask);
		//endEditCP(getParentWindow(), InternalWindow::FocusedComponentFieldMask);
	}
	return true;
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
        produceComponentResized( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );
    }
    if( (whichField & PositionFieldMask) )
    {
        produceComponentMoved( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );
    }
    if( (whichField & EnabledFieldMask) )
    {
        if(getEnabled())
        {
            produceComponentEnabled( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );    
        }
        else
        {
            produceComponentDisabled( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );    
        }
     }
    if( (whichField & VisibleFieldMask) )
    {
        if(getVisible())
        {
            produceComponentVisible( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );    
        }
        else
        {
            produceComponentHidden( ComponentEvent::create(ComponentPtr(this),getSystemTime()) );    
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
    
    if((whichField & CursorFieldMask) &&
        _MouseInComponentLastMouse &&
        getParentWindow() != NullFC &&
        getParentWindow()->getDrawingSurface() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
        getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(getCursor());
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


void Component::ComponentUpdater::update(const UpdateEventPtr e)
{
    _Component->_TimeSinceMouseEntered += e->getElapsedTime();
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

void Component::ActivateToolTipListener::mouseClicked(const MouseEventPtr e)
{
}

void Component::ActivateToolTipListener::mouseEntered(const MouseEventPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
	if( _Component->getParentWindow() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_Component->_ComponentUpdater));
	}
}

void Component::ActivateToolTipListener::mouseExited(const MouseEventPtr e)
{
    if( _Component->getParentWindow() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface() != NullFC &&
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		_Component->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&(_Component->_ComponentUpdater));
	}
}

void Component::ActivateToolTipListener::mousePressed(const MouseEventPtr e)
{
}

void Component::ActivateToolTipListener::mouseReleased(const MouseEventPtr e)
{
}

void Component::DeactivateToolTipListener::mouseClicked(const MouseEventPtr e)
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

void Component::DeactivateToolTipListener::mouseEntered(const MouseEventPtr e)
{
}

void Component::DeactivateToolTipListener::mouseExited(const MouseEventPtr e)
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

void Component::DeactivateToolTipListener::mousePressed(const MouseEventPtr e)
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

void Component::DeactivateToolTipListener::mouseReleased(const MouseEventPtr e)
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

OSG_END_NAMESPACE

