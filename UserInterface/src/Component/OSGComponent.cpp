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

void Component::getBounds(Pnt2s& TopLeft, Vec2s& Size) const
{
   TopLeft = getPosition();
   Size = getSize();
}

void Component::getInsideBorderBounds(Pnt2s& TopLeft, Vec2s& Size) const
{
   UInt16 TopInset(0), LeftInset(0), BottomInset(0), RightInset(0);
   if(getBorder() != NullFC)
   {
      //Get Border Insets
      getBorder()->getInsets(LeftInset,RightInset,TopInset,BottomInset);
   }
   TopLeft.setValues(LeftInset, TopInset);
   Size.setValues(getSize().x()-RightInset-LeftInset, getSize().y()-BottomInset-TopInset);
}

void Component::getBoundsRenderingSurfaceSpace(Pnt2s& TopLeft, Vec2s& Size) const
{
    Pnt2s ParentContainerTopLeft(0,0);
    Vec2s ParentContainerSize(0,0);
    if(getParentContainer() != NullFC)
    {
        Container::Ptr::dcast(getParentContainer())->getBoundsRenderingSurfaceSpace(ParentContainerTopLeft, ParentContainerSize);
    }
    TopLeft = ParentContainerTopLeft + Vec2s(getPosition());
    Size = getSize();
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
   getInsideBorderSizing(TopLeft, BottomRight);
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
        Pnt2s Quad1TopLeft,Quad2TopLeft;
        Vec2s Quad1Size,Quad2Size;

        Pnt2s ScissorQuadTopLeft;
        Vec2s ScissorQuadSize;
        if(getParentContainer() != NullFC)
        {
            getBounds(Quad1TopLeft,Quad1Size);
            Container::Ptr::dcast(getParentContainer())->getInsideBorderBounds(Quad2TopLeft,Quad2Size);

            quadIntersection(Pnt2s(0,0),Quad1Size,
                                Quad2TopLeft-Vec2s(Quad1TopLeft),Quad2Size,
                                ScissorQuadTopLeft,ScissorQuadSize);
        }
        else
        {
            ScissorQuadTopLeft = Pnt2s(0,0);
            ScissorQuadSize = getSize();
        }
        if(ScissorQuadSize.x() <= 0 || ScissorQuadSize.y()<= 0)
        {
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
        Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ScissorQuadTopLeft.x()),
              RightPlaneEquation(-1.0,0.0,0.0,ScissorQuadTopLeft.x()+ScissorQuadSize.x()),
              TopPlaneEquation(0.0,1.0,0.0,-ScissorQuadTopLeft.y()),
              BottomPlaneEquation(0.0,-1.0,0.0,ScissorQuadTopLeft.y()+ScissorQuadSize.y());
        
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

void Component::getInsideBorderSizing(Pnt2s& TopLeft, Pnt2s& BottomRight) const
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Component::Component(void) :
    Inherited()
{
}

Component::Component(const Component &source) :
    Inherited(source)
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

