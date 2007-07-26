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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>
#include "Util/OSGUIDrawUtils.h"

#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"

#include "OSGTextField.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextField
A UI TextField 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextField::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextField::drawInternal(const GraphicsPtr TheGraphics) const
{
   Pnt2s TopLeft, BottomRight;
   Pnt2s TempPos;
   getInsideBorderBounds(TopLeft, BottomRight);
   TempPos = calculateAlignment(TopLeft, TheGraphics->getTextBounds(getText(), getFont()), BottomRight-TopLeft, getVerticalAlignment(), getHorizontalAlignment());
   if(getText() != "" && getFont() != NullFC)
   {
	  //Foreground Color
	  Color4f ForeColor;
	  if(getEnabled())
	  {
		  ForeColor = getForegroundColor();
	  }
	  else
	  {
		  ForeColor = getDisabledForegroundColor();
	  }
	  if(_TextSelectionStart >= _TextSelectionEnd)
	  {
	      TheGraphics->drawText(TempPos, getText(), getFont(), ForeColor, getOpacity());
		  //Draw the caret
		  TheGraphics->drawLine(TempPos+Pnt2s(TheGraphics->getTextBounds(getText().substr(0, getCaretPosition()), getFont()).x()+ TopLeft.x(), TopLeft.y()),
	      TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, getCaretPosition()), getFont()).x()+TopLeft.x(),  TheGraphics->getTextBounds(getText(), getFont()).y()+TopLeft.y()), 
	      .5, ForeColor, 1.0);
	  }
	  else
	  {
		  TheGraphics->drawText(TempPos, getText().substr(0, _TextSelectionStart), getFont(), ForeColor, getOpacity());
		  //Draw Selection
		  TheGraphics->drawQuad(TempPos+Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont()).x(), 0),
			 TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont()).x(), 0),
			 TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont())),
			 TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont())),
			  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity()); 
		  TheGraphics->drawText(TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont()).x(), 0), 
			  getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity());

		  //draw end text
		  TheGraphics->drawText(TempPos + Pnt2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont()).x(), 0),
			  getText().substr(_TextSelectionEnd, getText().size()-_TextSelectionEnd), getFont(), ForeColor, getOpacity());
	   }
   }
}
void TextField::keyTyped(const KeyEvent& e)
{
	if(e.getKey() == e.KEY_ENTER)
	{
		produceActionPerformed(ActionEvent(TextFieldPtr(this), getTimeStamp()));
	}

	TextComponent::keyTyped(e);
}

void TextField::produceActionPerformed(const ActionEvent& e)
{
   for(ActionListenerSetConstItor SetItor(_ActionListeners.begin()) ; SetItor != _ActionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->actionPerformed(e);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextField::TextField(void) :
    Inherited()
{
}

TextField::TextField(const TextField &source) :
    Inherited(source)
{
}

TextField::~TextField(void)
{
}


/*----------------------------- class specific ----------------------------*/

void TextField::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TextField::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextField NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTEXTFIELDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTFIELDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTFIELDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

