/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGPasswordField.h"
#include "Util/OSGUIDrawUtils.h"

#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>

#include "LookAndFeel/OSGLookAndFeelManager.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PasswordField
A UI Password Field  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PasswordField::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PasswordField::drawInternal(const GraphicsPtr TheGraphics) const
{
    Pnt2s TopLeft, BottomRight;
    Pnt2s TempPos;
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, getFont()->getBounds(getEcho()), getVerticalAlignment(), 0.0);
    
    //Text Color
    Color4f TextColor = getDrawnTextColor();
    if(getEcho() != "" && getFont() != NullFC)
    {

	    if(_TextSelectionStart >= _TextSelectionEnd)
	    {
	        TheGraphics->drawText(TempPos, getEcho(), getFont(), TextColor, getOpacity());
	    }
	    else
	    {
            //Draw Text Befor the Selection
		    TheGraphics->drawText(TempPos, getEcho().substr(0, _TextSelectionStart), getFont(), TextColor, getOpacity());

		    //Draw Selection
            Pnt2s TextTopLeft, TextBottomRight;
            getFont()->getBounds(getEcho().substr(0, _TextSelectionStart), TextTopLeft, TextBottomRight);

		    TheGraphics->drawQuad(TempPos + Vec2s(TextBottomRight.x(),0),
			    TempPos + Vec2s(getFont()->getBounds(getEcho().substr(0, _TextSelectionEnd)).x(), 0),
			    TempPos + Vec2s(getFont()->getBounds(getEcho().substr(0, _TextSelectionEnd))),
			    TempPos + Vec2s(TextBottomRight),
			    getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity());

            //Draw Selected Text
		    TheGraphics->drawText(TempPos + Vec2s(TextBottomRight.x(), 0), 
			    getEcho().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity());

		    //Eraw Text After selection
            getFont()->getBounds(getEcho().substr(0, _TextSelectionEnd), TextTopLeft, TextBottomRight);
		    TheGraphics->drawText(TempPos + Vec2s(TextBottomRight.x(), 0),
			    getEcho().substr(_TextSelectionEnd, getEcho().size()-_TextSelectionEnd), getFont(), TextColor, getOpacity());
	    }
    }

    if(getFocused() && _CurrentCaretBlinkElps <= 0.5*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
    {
   		    //Draw the caret
		    TheGraphics->drawLine(TempPos+Vec2s(getFont()->getBounds(getEcho().substr(0, getCaretPosition())).x(), 0),
	        TempPos + Vec2s(getFont()->getBounds(getEcho().substr(0, getCaretPosition())).x(),  getFont()->getBounds(getEcho()).y()), 
	        .5, TextColor, 1.0);
    }
}

void PasswordField::mouseClicked(const MouseEvent& e)
{	
	if(e.getButton() == e.BUTTON1)
	{

		if(e.getClickCount() == 2)
		{
			_TextSelectionStart = 0;
			_TextSelectionEnd = getText().size();
			setCaretPosition(getText().size());
		}
	}
	TextComponent::mouseClicked(e);

}


void PasswordField::mousePressed(const MouseEvent& e)
{
	Pnt2s TopLeftText, BottomRightText, TempPos;
	Pnt2s TopLeftText1, BottomRightText1;
	Pnt2s TopLeft, BottomRight;
	Pnt2s CurrentPosition;
	getFont()->getBounds(getEcho(), TopLeftText, BottomRightText);
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getVerticalAlignment(), 0.0);
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		//if the mouse is to the left of the text, set it to the begining.
		Pnt2s temp = DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this));
		if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() <= TempPos.x())
		{
			setCaretPosition(0);
		}		//if the mouse is to the right of the text, set it to the end
		else if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() >= TempPos.x()+BottomRightText.x())
		{
			setCaretPosition(getEcho().size());
		}
		else
		{
			for(UInt32 i = 0; i <getEcho().size(); i++)
			{		
				getFont()->getBounds(getEcho().substr(0, i), TopLeftText, BottomRightText);
				getFont()->getBounds(getEcho().substr(0, i+1), TopLeftText1, BottomRightText1);
				if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x()>BottomRightText.x()
				   && DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				{
					if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() <= (BottomRightText1.x()-BottomRightText.x())/2.0+0.5 + BottomRightText.x())
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
void PasswordField::mouseDragged(const MouseEvent& e)
{
	Pnt2s TopLeftText, BottomRightText, TempPos;
	Pnt2s TopLeftText1, BottomRightText1;
	Pnt2s TopLeft, BottomRight;
	Pnt2s CurrentPosition;
	Int32 OriginalPosition = getCaretPosition();
	getFont()->getBounds(getEcho(), TopLeftText, BottomRightText);
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getVerticalAlignment(), 0.0);
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		//if the mouse is to the left of the text, set it to the begining.
		Pnt2s temp = DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this));
		if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() <= TempPos.x())
		{
			setCaretPosition(0);
		}		//if the mouse is to the right of the text, set it to the end
		else if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() >= TempPos.x()+BottomRightText.x())
		{
			setCaretPosition(getEcho().size());
		}
		else
		{
			//check letter by letter for the mouse's position
			for(UInt32 i = 0; i <getEcho().size(); i++)
			{		
				getFont()->getBounds(getEcho().substr(0, i), TopLeftText, BottomRightText);
				getFont()->getBounds(getEcho().substr(0, i+1), TopLeftText1, BottomRightText1);
				if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x()>BottomRightText.x()
				   && DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				{
					if(DrawingSurfaceToComponent(e.getLocation(), TextFieldPtr(this)).x() < (BottomRightText1.x()-BottomRightText.x())/2.0 + BottomRightText.x())
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
	

	TextComponent::mouseDragged(e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PasswordField::PasswordField(void) :
    Inherited()
{
}

PasswordField::PasswordField(const PasswordField &source) :
    Inherited(source)
{
}

PasswordField::~PasswordField(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PasswordField::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if(whichField & TextFieldMask)
    {
        std::string EchoString("");
        for(UInt32 i(0) ; i<getText().size(); ++i)
        {
            EchoString = EchoString + getEchoChar();
        }
        setEcho(EchoString);
    }
}

void PasswordField::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PasswordField NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPASSWORDFIELDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPASSWORDFIELDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPASSWORDFIELDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

