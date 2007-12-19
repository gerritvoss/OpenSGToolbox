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

#include "OSGEditableTextComponent.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::EditableTextComponent
A UI Editable Text Component. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void EditableTextComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void EditableTextComponent::keyPressed(const KeyEvent& e)
{
	Inherited::keyPressed(e);
}

void EditableTextComponent::keyReleased(const KeyEvent& e)
{
	Inherited::keyReleased(e);
}

void EditableTextComponent::keyTyped(const KeyEvent& e)
{
	
	if(getEnabled() && getEditable())
	{
		if(e.getKeyChar()>31 && e.getKeyChar() < 127)
		{
			if(_TextSelectionEnd > _TextSelectionStart)
			{
				//erase the selected portions and write in their place
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
					setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
					setText(getText().insert(_TextSelectionStart, std::string( 1,e.getKeyChar() )));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				setCaretPosition(_TextSelectionStart+1);
				_TextSelectionStart = getCaretPosition();
				_TextSelectionEnd = _TextSelectionStart;
			}
			else
			{
				//write at the current caret position
				e.getKeyChar();
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				setText(getText().insert(getCaretPosition(), std::string( 1,e.getKeyChar() )));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
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
				setCaretPosition(_TextSelectionStart);
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
					setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				_TextSelectionStart = getCaretPosition();
				_TextSelectionEnd = _TextSelectionStart;
			}
			else if(getCaretPosition() > 0)
			{	

					//erase at the current caret position
				setCaretPosition(getCaretPosition()-1);
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
					setText(getText().erase(getCaretPosition(), 1));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				_TextSelectionStart = getCaretPosition();
				_TextSelectionEnd = _TextSelectionStart;
			}
		}
		if(e.getKey()== e.KEY_DELETE)
		{
			if(_TextSelectionEnd > _TextSelectionStart)
			{
				//erase the selected portions
				setCaretPosition(_TextSelectionStart);
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
					setText(getText().erase(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				_TextSelectionStart = getCaretPosition();
				_TextSelectionEnd = _TextSelectionStart;
			}
			else if(getText().size()>0)
			{
				//erase at the current caret position
				beginEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
					setText(getText().erase(getCaretPosition(), 1));
				endEditCP(TextComponentPtr(this), EditableTextComponent::TextFieldMask);
				_TextSelectionStart = getCaretPosition();
				_TextSelectionEnd = _TextSelectionStart;
			}
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
	Inherited::keyTyped(e);
}
void EditableTextComponent::mouseEntered(const MouseEvent& e)
{
	if(getEnabled() && getEditable())
	{
		if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!=NullFC&&getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_I_BEAM);
		}
	}
	Inherited::mouseEntered(e);
}
void EditableTextComponent::mouseExited(const MouseEvent& e)
{
	if(getEnabled() && getEditable())
	{
		if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!= NullFC && getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
		{
			getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
		}
	}
	Inherited::mouseExited(e);
}

void EditableTextComponent::focusLost(const FocusEvent& e)
{
	if( getParentFrame() != NullFC &&
		getParentFrame()->getDrawingSurface() != NullFC &&
		getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC && 
		isContained(getParentFrame()->getDrawingSurface()->getEventProducer()->getMousePosition(), true))
    {
		getParentFrame()->getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
	}
	Inherited::focusLost(e);
}

UIBackgroundPtr EditableTextComponent::getDrawnBackground(void) const
{
	if(getEditable())
	{
		return Inherited::getDrawnBackground();
	}
	else
	{
		return getDisabledBackground();
	}
}

BorderPtr EditableTextComponent::getDrawnBorder(void) const
{
    return Inherited::getDrawnBorder();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

EditableTextComponent::EditableTextComponent(void) :
    Inherited()
{
}

EditableTextComponent::EditableTextComponent(const EditableTextComponent &source) :
    Inherited(source)
{
}

EditableTextComponent::~EditableTextComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void EditableTextComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void EditableTextComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump EditableTextComponent NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGEDITABLETEXTCOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGEDITABLETEXTCOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGEDITABLETEXTCOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

