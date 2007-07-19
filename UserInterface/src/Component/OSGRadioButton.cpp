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
#include "OSGUserInterfaceDef.h"
#include "Util/OSGUIDrawUtils.h"
#include "OSGRadioButton.h"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RadioButton
A UI Radio Button. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RadioButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RadioButton::drawInternal(const GraphicsPtr TheGraphics) const
{
	Pnt2s TopLeft, BottomRight;
	Pnt2s drawObjectTopLeft;
	Pnt2s TempPosition;
	Vec2s drawObjectSize;
	getInsideBorderBounds(TopLeft, BottomRight);
	//TempPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, drawObjectSize/2.0+TheGraphics->getTextBounds(getText(), getFont()), getVerticalAlignment(), getHorizontalAlignment());
   if(getActive()){
	   if(getChecked()){
			getActiveCheckedDrawObject()->getDrawObjectBounds(drawObjectTopLeft, drawObjectSize);
		    TempPosition = Pnt2s(drawObjectSize.x()+TheGraphics->getTextBounds(getText(), getFont()).x(), 0);
			TempPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, TempPosition, getVerticalAlignment(), getHorizontalAlignment());
			beginEditCP(getActiveCheckedDrawObject(), Component::PositionFieldMask);
				getActiveCheckedDrawObject()->setPosition(TempPosition);
			endEditCP(getActiveCheckedDrawObject(), Component::PositionFieldMask);
			getActiveCheckedDrawObject()->draw(TheGraphics);
	   }
	   else
	   {
			getActiveDrawObject()->getDrawObjectBounds(drawObjectTopLeft, drawObjectSize);
		    TempPosition = Pnt2s(drawObjectSize.x()+TheGraphics->getTextBounds(getText(), getFont()).x(), 0);
			TempPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, TempPosition, getVerticalAlignment(), getHorizontalAlignment());
			beginEditCP(getActiveDrawObject(), Component::PositionFieldMask);
				getActiveDrawObject()->setPosition(TempPosition);
			endEditCP(getActiveDrawObject(), Component::PositionFieldMask);
			getActiveDrawObject()->draw(TheGraphics);
	   }
   }
   else if(getChecked()){
	   getCheckedDrawObject()->getDrawObjectBounds(drawObjectTopLeft, drawObjectSize);
	   TempPosition = Pnt2s(drawObjectSize.x()+TheGraphics->getTextBounds(getText(), getFont()).x(), 0);
	   TempPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, TempPosition, getVerticalAlignment(), getHorizontalAlignment());
	   beginEditCP(getCheckedDrawObject(), Component::PositionFieldMask);
			getCheckedDrawObject()->setPosition(TempPosition);
		endEditCP(getCheckedDrawObject(), Component::PositionFieldMask);
		getCheckedDrawObject()->draw(TheGraphics);
   }
   else{
		getDrawObject()->getDrawObjectBounds(drawObjectTopLeft, drawObjectSize);
		TempPosition = Pnt2s(drawObjectSize.x()+TheGraphics->getTextBounds(getText(), getFont()).x(), 0);
		TempPosition = calculateAlignment(TopLeft, BottomRight-TopLeft, TempPosition, getVerticalAlignment(), getHorizontalAlignment());
		beginEditCP(getDrawObject(), Component::PositionFieldMask);
			getDrawObject()->setPosition(TempPosition);
		endEditCP(getDrawObject(), Component::PositionFieldMask);
		getDrawObject()->draw(TheGraphics);
   }

   TempPosition = Pnt2s(TempPosition.x() + 2*drawObjectSize.x(), TempPosition.y()-TheGraphics->getTextBounds(getText(), getFont()).y()/2.0);
   TheGraphics->drawText(TempPosition, getText(), getFont(), getForegroundColor(), getOpacity());
   
   
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RadioButton::RadioButton(void) :
    Inherited()
{
}

RadioButton::RadioButton(const RadioButton &source) :
    Inherited(source)
{
}

RadioButton::~RadioButton(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RadioButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RadioButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RadioButton NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGRADIOBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRADIOBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRADIOBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

