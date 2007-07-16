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

#include "OSGComponent.h"

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

void Component::getBounds(Pnt2s& TopLeft, Vec2s& Size)
{
   TopLeft = getPosition();
   Size = getSize();
}

void Component::getInsideBorderBounds(Pnt2s& TopLeft, Vec2s& Size)
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

void Component::getBoundsWindowSpace(Pnt2s& TopLeft, Vec2s& Size)
{
   TopLeft = getPosition();
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

