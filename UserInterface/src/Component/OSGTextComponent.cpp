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

#include "OSGTextComponent.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextComponent
A UI Button. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void  TextComponent::produceTextValueChanged(const TextEvent& e)
{
   for(TextListenerSetConstItor SetItor(_TextListeners.begin()) ; SetItor != _TextListeners.end() ; ++SetItor)
   {
      (*SetItor)->textValueChanged(e);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextComponent::TextComponent(void) :
    Inherited()
{
}

TextComponent::TextComponent(const TextComponent &source) :
    Inherited(source)
{
}

TextComponent::~TextComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/




void TextComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & TextFieldMask))
	{
		produceTextValueChanged(TextEvent(TextComponentPtr(this), getTimeStamp(), TextEvent::TEXT_CHANGED));
	}
}

void TextComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextComponent NI" << std::endl;
}
void TextComponent::select(const UInt32& index1,
						const UInt32& index2)
{
}
void TextComponent::selectAll(void)
{
	_TextSelectionStart = 0;
	_TextSelectionEnd = getText().size();
}
void TextComponent::setSelectionStart(const UInt32& index)
{
	if(index < getText().size())
	{
		_TextSelectionStart = index;
	}
	else
	{
		_TextSelectionStart = getText().size();
	}
}
void TextComponent::setSelectionEnd(const UInt32& index)
{
	if(index < getText().size())
	{
		_TextSelectionEnd = index;
	}
	else
	{
		_TextSelectionEnd = getText().size();
	}
}
std::string TextComponent::getSelectedText(void) const
{
	if(_TextSelectionEnd<getText().size())
	{
		return getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart);
	}
	else
	{
		return getText().substr(_TextSelectionStart);
	}
}

void TextComponent::keyPressed(const KeyEvent& e)
{

}

void TextComponent::keyReleased(const KeyEvent& e)
{

}

void TextComponent::keyTyped(const KeyEvent& e)
{

	if(e.getKeyChar()>31 && e.getKeyChar() < 127)
	{
		if(_TextSelectionEnd > _TextSelectionStart)
		{
			//erase the selected portions and write in their place
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
				setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
				setText(getText().insert(_TextSelectionStart, std::string( 1,e.getKeyChar() )));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			setCaretPosition(_TextSelectionStart);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
		else
		{
			//write at the current caret position
			e.getKeyChar();
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			setText(getText().insert(_TextSelectionStart, std::string( 1,e.getKeyChar() )));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			if(getCaretPosition() <getText().size())
			{
				setCaretPosition(getCaretPosition()+1);
			}
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
	}
	if(e.getKey()== e.KEY_BACK_SPACE)
	{
		if(_TextSelectionEnd > _TextSelectionStart)
		{
			//erase the selected portions
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
				setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			setCaretPosition(_TextSelectionStart);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
		else if(getCaretPosition() > 0)
		{	

				//erase at the current caret position
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
				setText(getText().erase(getCaretPosition()-1, 1));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			setCaretPosition(getCaretPosition()-1);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
	}
	if(e.getKey()== e.KEY_DELETE)
	{
		if(_TextSelectionEnd > _TextSelectionStart)
		{
			//erase the selected portions
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
				setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			setCaretPosition(_TextSelectionStart);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
		else if(getText().size()>0)
		{
			//erase at the current caret position
			beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
				setText(getText().erase(getCaretPosition(), 1));
			endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
	}
	
	if(e.getKey()== e.KEY_RIGHT ||e.getKey()== e.KEY_KEYPAD_RIGHT)
	{
		if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!=NullFC&&getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC 
			&& getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			if(_TextSelectionEnd > _TextSelectionStart && _TextSelectionEnd < getText().size() && getCaretPosition()>_TextSelectionStart)
			{
				setCaretPosition(getCaretPosition()+1);
				_TextSelectionEnd=getCaretPosition();
			}
			else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition() < getText().size())
			{
				setCaretPosition(getCaretPosition()+1);
				_TextSelectionStart = getCaretPosition();
			}
			else if(getCaretPosition()< getText().size() && _TextSelectionEnd <=_TextSelectionStart )
			{
				_TextSelectionStart = getCaretPosition();
				setCaretPosition(getCaretPosition()+1);
				_TextSelectionEnd = getCaretPosition();
			}
		}
		else if(_TextSelectionEnd > _TextSelectionStart)
		{
			//Caret is now the end of the selection
			setCaretPosition(_TextSelectionEnd);
			_TextSelectionStart = getCaretPosition();
		}
		else if(getCaretPosition() < getText().size())
		{
			//increment the caret position
			setCaretPosition(getCaretPosition()+1);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = getCaretPosition();
		}
	}
	if(e.getKey()== e.KEY_LEFT||e.getKey()== e.KEY_KEYPAD_LEFT)
	{

		if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!=NullFC&&getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC
			&& getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size() && getCaretPosition()>_TextSelectionStart && getCaretPosition()>0)
			{
				setCaretPosition(getCaretPosition()-1);
				_TextSelectionEnd=getCaretPosition();
			}
			else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition()>0)
			{
				setCaretPosition(getCaretPosition()-1);
				_TextSelectionStart = getCaretPosition();
			}
			else if(_TextSelectionEnd <=_TextSelectionStart && getCaretPosition()>0 )
			{
				_TextSelectionEnd = getCaretPosition();
				setCaretPosition(getCaretPosition()-1);
				_TextSelectionStart = getCaretPosition();
			}
		}
		else if(_TextSelectionEnd > _TextSelectionStart)
		{
			//Caret is now the start of the selection
			setCaretPosition(_TextSelectionStart);
			_TextSelectionEnd = getCaretPosition();
		}
		else if(getCaretPosition() > 0)
		{
			//decrement the caret position
			setCaretPosition(getCaretPosition()-1);
			_TextSelectionStart = getCaretPosition();
			_TextSelectionEnd = _TextSelectionStart;
		}
	}
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
    static Char8 cvsid_hpp       [] = OSGTEXTCOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTCOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTCOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

