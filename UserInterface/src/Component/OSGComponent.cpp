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

void Component::drawBorder(const GraphicsPtr TheGraphics) const
{
   if(getBorder() != NullFC)
   {
      //Draw My Border
	  if(getEnabled())
	  {
		getBorder()->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity());
	  }
	  else
	  {
		getDisabledBorder()->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity());
	  }
   }
}

void Component::drawBackground(const GraphicsPtr TheGraphics) const
{
   //Draw the Background on the Inside of my border
   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   if(getBackground() != NullFC)
   {
	  if(getEnabled())
	  {
	     getBackground()->draw(TheGraphics, TopLeft, BottomRight, getOpacity());
	  }
	  else
	  {
	     getDisabledBackground()->draw(TheGraphics, TopLeft, BottomRight, getOpacity());
	  }
   }
}

void Component::draw(const GraphicsPtr TheGraphics) const
{
	if (!getVisible())
		return;

    //Translate to my position
    glTranslatef(getPosition().x(), getPosition().y(), 0);

    //Get Clipping initial settings
    //bool WasClippingEnabled = glIsEnabled(GL_SCISSOR_TEST);
    bool WasClippPlane0Enabled = glIsEnabled(GL_CLIP_PLANE0);
    bool WasClippPlane1Enabled = glIsEnabled(GL_CLIP_PLANE1);
    bool WasClippPlane2Enabled = glIsEnabled(GL_CLIP_PLANE2);
    bool WasClippPlane3Enabled = glIsEnabled(GL_CLIP_PLANE3);
    if(getClipping())
    {
        //glScissor
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        Pnt2s ClipTopLeft,ClipBottomRight;
		getClipBounds(ClipTopLeft,ClipBottomRight);
        if(ClipBottomRight.x()-ClipTopLeft.x() <= 0 || ClipBottomRight.y()-ClipTopLeft.y()<= 0)
        {
			//Translate to my position
			glTranslatef(-getPosition().x(), -getPosition().y(), 0);
            return;
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

    //Draw My Border
    drawBorder(TheGraphics);

    //Draw My Background
    drawBackground(TheGraphics);

    //Draw Internal
    drawInternal(TheGraphics);
    glTranslatef(-getPosition().x(), -getPosition().y(), 0);
    
    //Set Clipping to initial settings
    if(getClipping())
    {
        if(!WasClippPlane0Enabled){glDisable(GL_CLIP_PLANE0);}
        if(!WasClippPlane1Enabled){glDisable(GL_CLIP_PLANE1);}
        if(!WasClippPlane2Enabled){glDisable(GL_CLIP_PLANE2);}
        if(!WasClippPlane3Enabled){glDisable(GL_CLIP_PLANE3);}
    }
}


void Component::updateClipBounds(void)
{
	Pnt2s TopLeft, BottomRight;
	if(getParentContainer() == NullFC)
	{
		TopLeft = getPosition();
		BottomRight = (getPosition()+getSize());
	}
	else
	{
		Container::Ptr::dcast(getParentContainer())->updateClipBounds();
        Pnt2s MyTopLeft,ContainerTopLeft,
			  MyBottomRight, ContainerBottomRight;

        getBounds(MyTopLeft,MyBottomRight);
		Container::Ptr::dcast(getParentContainer())->getClipBounds(ContainerTopLeft,ContainerBottomRight);
		
		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerTopLeft,ContainerBottomRight,
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
	std::cout << getType().getCName() << " mouseClicked" << std::endl;
	produceMouseClicked(e);
}

void Component::mouseEntered(const MouseEvent& e)
{
	std::cout << getType().getCName() << " mouseEntered" << std::endl;
	produceMouseEntered(e);
}

void Component::mouseExited(const MouseEvent& e)
{
	std::cout << getType().getCName() << " mouseExited" << std::endl;
	produceMouseExited(e);
}

void Component::mousePressed(const MouseEvent& e)
{
	std::cout << getType().getCName() << " mousePressed" << std::endl;
	produceMousePressed(e);
}

void Component::mouseReleased(const MouseEvent& e)
{
	std::cout << getType().getCName() << " mouseReleased" << std::endl;
	produceMouseReleased(e);
}


void Component::mouseMoved(const MouseEvent& e)
{
	//std::cout << getType().getCName() << " mouseMoved" << std::endl;
	produceMouseMoved(e);
}

void Component::mouseDragged(const MouseEvent& e)
{
	//std::cout << getType().getCName() << " mouseDragged" << std::endl;
	produceMouseDragged(e);
}

void Component::mouseWheelMoved(const MouseWheelEvent& e)
{
	std::cout << getType().getCName() << " mouseWheelMoved" << std::endl;
	produceMouseWheelMoved(e);
}

void Component::keyPressed(const KeyEvent& e)
{
	std::cout << getType().getCName() << " keyPressed" << std::endl;
	produceKeyPressed(e);
}

void Component::keyReleased(const KeyEvent& e)
{
	std::cout << getType().getCName() << " keyReleased" << std::endl;
	produceKeyReleased(e);
}

void Component::keyTyped(const KeyEvent& e)
{
	std::cout << getType().getCName() << " keyTyped" << std::endl;
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

