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


#include "Component/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "LookAndFeel/OSGLookAndFeelManager.h"

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
   TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, TheGraphics->getTextBounds(getText(), getFont()), getVerticalAlignment(), 0.0);
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
  if(getText() != "" && getFont() != NullFC)
   {

	  if(_TextSelectionStart >= _TextSelectionEnd)
	  {
	      TheGraphics->drawText(TempPos, getText(), getFont(), ForeColor, getOpacity());
	  }
	  else
	  {
		  TheGraphics->drawText(TempPos, getText().substr(0, _TextSelectionStart), getFont(), ForeColor, getOpacity());
		  //Draw Selection
		  TheGraphics->drawQuad(TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont()).x(), 0),
			 TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont()).x(), 0),
			 TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont())),
			 TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont())),
			  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity()); 
		  TheGraphics->drawText(TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionStart), getFont()).x(), 0), 
			  getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity());

		  //draw end text
		  TheGraphics->drawText(TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, _TextSelectionEnd), getFont()).x(), 0),
			  getText().substr(_TextSelectionEnd, getText().size()-_TextSelectionEnd), getFont(), ForeColor, getOpacity());
	   }
   }

   if(getFocused() && _TextSelectionStart>=_TextSelectionEnd && _CurrentCaretBlinkElps <= 0.5*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
	   ;
   		  //Draw the caret
		  TheGraphics->drawLine(TempPos+Vec2s(TheGraphics->getTextBounds(getText().substr(0, getCaretPosition()), getFont()).x(), 0),
	      TempPos + Vec2s(TheGraphics->getTextBounds(getText().substr(0, getCaretPosition()), getFont()).x(),  TheGraphics->getTextBounds(getText(), getFont()).y()), 
	      .5, ForeColor, 1.0);
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

void TextField::mouseClicked(const MouseEvent& e)
{	
	Int32 Position;
	Int32 BeginWord = 0;
	Int32 EndWord = getText().size();
	if(e.getButton() == e.BUTTON1)
	{

		if(e.getClickCount() == 2)
		{
			Pnt2s TopLeftText, BottomRightText, TempPos;
			Pnt2s TopLeftText1, BottomRightText1;
			Pnt2s TopLeft, BottomRight;
			Pnt2s CurrentPosition;
			getFont()->getBounds(getText(), TopLeftText, BottomRightText);
			getInsideBorderBounds(TopLeft, BottomRight);
			TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText, getVerticalAlignment(), 0.0);

			//set caret position to proper place
			//if the mouse is to the left of the text, set it to the begining.
			Pnt2s temp = WindowToComponent(e.getLocation(), TextFieldPtr(this));
			if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= TempPos.x())
			{
				Position = 0;
			}		//if the mouse is to the right of the text, set it to the end
			else if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() >= TempPos.x()+BottomRightText.x())
			{
				Position = getText().size();
			}
			else
			{
				for(UInt32 i = 0; i <getText().size(); i++)
				{		
					getFont()->getBounds(getText().substr(0, i), TopLeftText, BottomRightText);
					getFont()->getBounds(getText().substr(0, i+1), TopLeftText1, BottomRightText1);
					if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x()>BottomRightText.x()
					   && WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
					{
						Position = i;
						break;
					}
				}
			}
			if(isPunctuationChar(getText()[Position]))
			{
				EndWord = Position + 1;
				BeginWord = Position;
			}
			else{
				for(Int32 i = Position; i < getText().size(); i++)
				{
					if(!isWordChar(getText()[i]))
					{
						EndWord = i;
						break;
					}
				}
				for(Int32 i = Position; i >= 0; i--)
				{
					if(!isWordChar(getText()[i]))
					{
						BeginWord = i + 1;
						break;
					}
				}
			}
			_TextSelectionEnd = EndWord;
			_TextSelectionStart = BeginWord;
			setCaretPosition(EndWord);
		}
	}
	TextComponent::mouseClicked(e);

}


void TextField::mousePressed(const MouseEvent& e)
{
	Pnt2s TopLeftText, BottomRightText, TempPos;
	Pnt2s TopLeftText1, BottomRightText1;
	Pnt2s TopLeft, BottomRight;
	Pnt2s CurrentPosition;
	getFont()->getBounds(getText(), TopLeftText, BottomRightText);
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText, getVerticalAlignment(), 0.0);
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		//if the mouse is to the left of the text, set it to the begining.
		Pnt2s temp = WindowToComponent(e.getLocation(), TextFieldPtr(this));
		if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= TempPos.x())
		{
			setCaretPosition(0);
		}		//if the mouse is to the right of the text, set it to the end
		else if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() >= TempPos.x()+BottomRightText.x())
		{
			setCaretPosition(getText().size());
		}
		else
		{
			for(UInt32 i = 0; i <getText().size(); i++)
			{		
				getFont()->getBounds(getText().substr(0, i), TopLeftText, BottomRightText);
				getFont()->getBounds(getText().substr(0, i+1), TopLeftText1, BottomRightText1);
				if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x()>BottomRightText.x()
				   && WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				{
					if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= (BottomRightText1.x()-BottomRightText.x())/2.0+0.5 + BottomRightText.x())
					{
						setCaretPosition(i);
						break;
					}
					else
					{
						setCaretPosition(i+1);
						break;
					}
				}
			}
		}

		_TextSelectionEnd = getCaretPosition();
		_TextSelectionStart = getCaretPosition();
	}
	TextComponent::mousePressed(e);
}
void TextField::mouseDragged(const MouseEvent& e)
{
	Pnt2s TopLeftText, BottomRightText, TempPos;
	Pnt2s TopLeftText1, BottomRightText1;
	Pnt2s TopLeft, BottomRight;
	Pnt2s CurrentPosition;
	Int32 OriginalPosition = getCaretPosition();
	getFont()->getBounds(getText(), TopLeftText, BottomRightText);
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText, getVerticalAlignment(), 0.0);
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		//if the mouse is to the left of the text, set it to the begining.
		Pnt2s temp = WindowToComponent(e.getLocation(), TextFieldPtr(this));
		if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= TempPos.x())
		{
			setCaretPosition(0);
		}		//if the mouse is to the right of the text, set it to the end
		else if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() >= TempPos.x()+BottomRightText.x())
		{
			setCaretPosition(getText().size());
		}
		else
		{
			//check letter by letter for the mouse's position
			for(UInt32 i = 0; i <getText().size(); i++)
			{		
				getFont()->getBounds(getText().substr(0, i), TopLeftText, BottomRightText);
				getFont()->getBounds(getText().substr(0, i+1), TopLeftText1, BottomRightText1);
				if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x()>BottomRightText.x()
				   && WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				{
					if(WindowToComponent(e.getLocation(), TextFieldPtr(this)).x() < (BottomRightText1.x()-BottomRightText.x())/2.0 + BottomRightText.x())
					{

						setCaretPosition(i);
						break;
					}
					else
					{

						setCaretPosition(i+1);
						break;
					}
				}
			}
		}
	}
	
	if(getCaretPosition() < OriginalPosition)
	{
		if(getCaretPosition() < _TextSelectionStart)
		{
			_TextSelectionStart = getCaretPosition();
		}
		else
		{
			_TextSelectionEnd = getCaretPosition();
		}
	}
	else if(getCaretPosition() > OriginalPosition)
	{
		if(getCaretPosition() > _TextSelectionEnd)
		{
			_TextSelectionEnd = getCaretPosition();
		}
		else
		{
			_TextSelectionStart = getCaretPosition();
		}
	}
}


void TextField::produceActionPerformed(const ActionEvent& e)
{
   for(ActionListenerSetConstItor SetItor(_ActionListeners.begin()) ; SetItor != _ActionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->actionPerformed(e);
   }
}

void TextField::update(const UpdateEvent& e)
{
   _CurrentCaretBlinkElps += e.getElapsedTime();
   if(_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
	   _CurrentCaretBlinkElps -= osgfloor<Time>(_CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
   }
}

void TextField::focusGained(const FocusEvent& e)
{
	if( getParentFrame() != NullFC &&
		getParentFrame()->getDrawingSurface() != NullFC &&
		getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		getParentFrame()->getDrawingSurface()->getEventProducer()->addUpdateListener(this);
	}
	TextComponent::focusGained(e);
}

void TextField::focusLost(const FocusEvent& e)
{
	if( getParentFrame() != NullFC &&
		getParentFrame()->getDrawingSurface() != NullFC &&
		getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
	}
	TextComponent::focusLost(e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextField::TextField(void) :
    Inherited(),
		_CurrentCaretBlinkElps(0.0)
{
}

TextField::TextField(const TextField &source) :
    Inherited(source),
		_CurrentCaretBlinkElps(0.0)
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

