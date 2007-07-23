/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGComponent.h"
#include "OSGContainer.h"
#include "Util/OSGUIDrawUtils.h"

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

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Component::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Component::getInsideBorderBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
   UInt16 TopInset(0), LeftInset(0), BottomInset(0), RightInset(0);

   if(getBorder() != NullFC)
   {
      //Get Border Insets
      getBorder()->getInsets(LeftInset,RightInset,TopInset,BottomInset);
   }
   TopLeft.setValues(LeftInset, TopInset);
   BottomRight.setValues(TopLeft.x()+getSize().x()-(LeftInset + RightInset), TopLeft.y()+getSize().y()-(TopInset + BottomInset));
}

void Component::getBoundsRenderingSurfaceSpace(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
    Pnt2s ParentContainerTopLeft(0,0),ParentContainerBottomRight(0,0);
    if(getParentContainer() != NullFC)
    {
        Container::Ptr::dcast(getParentContainer())->getBoundsRenderingSurfaceSpace(ParentContainerTopLeft, ParentContainerBottomRight);
    }
    TopLeft = ParentContainerTopLeft + Vec2s(getPosition());
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

void Component::drawBackground(const GraphicsPtr TheGraphics, const UIBackgroundPtr Background) const
{
   //Draw the Background on the Inside of my border
   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   if(Background != NullFC)
   {
	   Background->draw(TheGraphics, TopLeft, BottomRight, getOpacity());
   }
}

bool Component::setupClipping(const GraphicsPtr Graphics) const
{
    //Get Clipping initial settings
    //bool WasClippingEnabled = glIsEnabled(GL_SCISSOR_TEST);
    bool WasClippPlane0Enabled = glIsEnabled(GL_CLIP_PLANE0);
    bool WasClippPlane1Enabled = glIsEnabled(GL_CLIP_PLANE1);
    bool WasClippPlane2Enabled = glIsEnabled(GL_CLIP_PLANE2);
    bool WasClippPlane3Enabled = glIsEnabled(GL_CLIP_PLANE3);
    if(getClipping())
    {
        //glClipPlane
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        Pnt2s ClipTopLeft,ClipBottomRight;
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
        Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ClipTopLeft.x()),
              RightPlaneEquation(-1.0,0.0,0.0,ClipBottomRight.x()),
              TopPlaneEquation(0.0,1.0,0.0,-ClipTopLeft.y()),
              BottomPlaneEquation(0.0,-1.0,0.0,ClipBottomRight.y());
        
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

	if(getEnabled())
	{
		//Draw My Border
		drawBorder(TheGraphics, getBorder());

		//Draw My Background
		drawBackground(TheGraphics, getBackground());
	}
	else
	{
		//Draw My Border
		drawBorder(TheGraphics, getDisabledBorder());

		//Draw My Background
		drawBackground(TheGraphics, getDisabledBackground());
	}

    //Draw Internal
    drawInternal(TheGraphics);
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
	Pnt2s TopLeft, BottomRight;
	if(getParentContainer() == NullFC)
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
        Pnt2s MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Update my Parent Container's Clip Bounds
		Container::Ptr::dcast(getParentContainer())->updateClipBounds();

		//Get Parent Container's Clip Bounds
		Pnt2s ContainerClipTopLeft, ContainerClipBottomRight;
		Container::Ptr::dcast(getParentContainer())->getClipBounds(ContainerClipTopLeft,ContainerClipBottomRight);
		ContainerClipTopLeft -= Vec2s(Container::Ptr::dcast(getParentContainer())->getLeftInset(), Container::Ptr::dcast(getParentContainer())->getTopInset());
		ContainerClipBottomRight -= Vec2s(Container::Ptr::dcast(getParentContainer())->getLeftInset(), Container::Ptr::dcast(getParentContainer())->getTopInset());

		
		//Get Parent Container's Inset Bounds
		Pnt2s ContainerInsetTopLeft, ContainerInsetBottomRight;
		Container::Ptr::dcast(getParentContainer())->getInsideInsetsBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);
		ContainerInsetTopLeft -= Vec2s(Container::Ptr::dcast(getParentContainer())->getLeftInset(), Container::Ptr::dcast(getParentContainer())->getTopInset());
		ContainerInsetBottomRight -= Vec2s(Container::Ptr::dcast(getParentContainer())->getLeftInset(), Container::Ptr::dcast(getParentContainer())->getTopInset());
		
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
		setClipTopLeft(TopLeft - Vec2s(getPosition()));
		setClipBottomRight(BottomRight - Vec2s(getPosition()));
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
}

void Component::mouseReleased(const MouseEvent& e)
{
	produceMouseReleased(e);
}


void Component::mouseMoved(const MouseEvent& e)
{
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
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseClicked(e);
   }
}

void Component::produceMouseEntered(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseEntered(e);
   }
}

void Component::produceMouseExited(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseExited(e);
   }
}

void Component::produceMousePressed(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mousePressed(e);
   }
}

void Component::produceMouseReleased(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseReleased(e);
   }
}

void Component::produceKeyPressed(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
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
   for(FocusListenerSetConstItor SetItor(_FocusListeners.begin()) ; SetItor != _FocusListeners.end() ; ++SetItor)
   {
      (*SetItor)->focusGained(e);
   }
}

void  Component::produceFocusLost(const FocusEvent& e)
{
   for(FocusListenerSetConstItor SetItor(_FocusListeners.begin()) ; SetItor != _FocusListeners.end() ; ++SetItor)
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

bool Component::giveFocus(void)
{
    if(!getFocusable())
    {
        return false;
    }
    else
    {
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(true);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
        produceFocusGained(FocusEvent(ComponentPtr(this),getSystemTime(),FocusEvent::FOCUS_GAINED,false, NullFC));
    }
}

bool Component::takeFocus(void)
{
    if(!getFocusable())
    {
        return false;
    }
    else
    {
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(false);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
        produceFocusLost(FocusEvent(ComponentPtr(this),getSystemTime(),FocusEvent::FOCUS_LOST,false, NullFC));
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Component::Component(void) :
    Inherited(),
		_MouseInComponentLastMouse(false)
{
}

Component::Component(const Component &source) :
    Inherited(source),
		_MouseInComponentLastMouse(false)
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

