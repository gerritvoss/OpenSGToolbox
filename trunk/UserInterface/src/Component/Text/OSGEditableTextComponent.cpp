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
#include "Component/Container/Window/OSGInternalWindow.h"
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
	
    if(getEnabled() && getEditable() && !(e.getModifiers() &( KeyEvent::KEY_MODIFIER_ALT | KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_META )))
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
	
	UInt32 NewCaretPosition(getCaretPosition());
	if(e.getKey()== e.KEY_RIGHT ||e.getKey()== e.KEY_KEYPAD_RIGHT)
	{
		if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC 
			&& getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			if(_TextSelectionEnd > _TextSelectionStart && _TextSelectionEnd < getText().size() && getCaretPosition()>_TextSelectionStart)
			{
				NewCaretPosition = getCaretPosition()+1;
				_TextSelectionEnd=NewCaretPosition;
			}
			else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition() < getText().size())
			{
				NewCaretPosition = getCaretPosition()+1;
				_TextSelectionStart = NewCaretPosition;
			}
			else if(getCaretPosition()< getText().size() && _TextSelectionEnd <=_TextSelectionStart )
			{
				_TextSelectionStart = NewCaretPosition;
				NewCaretPosition = getCaretPosition()+1;
				_TextSelectionEnd = NewCaretPosition;
			}
		}
		else if(_TextSelectionEnd > _TextSelectionStart)
		{
			//Caret is now the end of the selection
			NewCaretPosition = _TextSelectionEnd;
			_TextSelectionStart = NewCaretPosition;
		}
		else if(getCaretPosition() < getText().size())
		{
			//increment the caret position
			NewCaretPosition = getCaretPosition()+1;
			_TextSelectionStart = NewCaretPosition;
			_TextSelectionEnd = NewCaretPosition;
		}
	}
	if(e.getKey()== e.KEY_LEFT||e.getKey()== e.KEY_KEYPAD_LEFT)
	{

		if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC
			&& getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size() && getCaretPosition()>_TextSelectionStart && getCaretPosition()>0)
			{
				NewCaretPosition = getCaretPosition()-1;
				_TextSelectionEnd=NewCaretPosition;
			}
			else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition()>0)
			{
				NewCaretPosition = getCaretPosition()-1;
				_TextSelectionStart = NewCaretPosition;
			}
			else if(_TextSelectionEnd <=_TextSelectionStart && getCaretPosition()>0 )
			{
				_TextSelectionEnd = NewCaretPosition;
				NewCaretPosition = getCaretPosition()-1;
				_TextSelectionStart = NewCaretPosition;
			}
		}
		else if(_TextSelectionEnd > _TextSelectionStart)
		{
			//Caret is now the start of the selection
			NewCaretPosition = _TextSelectionStart;
			_TextSelectionEnd = NewCaretPosition;
		}
		else if(getCaretPosition() > 0)
		{
			//decrement the caret position
			NewCaretPosition = getCaretPosition()-1;
			_TextSelectionStart = NewCaretPosition;
			_TextSelectionEnd = _TextSelectionStart;
		}
	}
	
	if(NewCaretPosition != getCaretPosition())
	{
		beginEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(NewCaretPosition);
		endEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
	}

	Inherited::keyTyped(e);
}

LayerPtr EditableTextComponent::getDrawnBackground(void) const
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

LayerPtr EditableTextComponent::getDrawnForeground(void) const
{
	if(getEditable())
	{
		return Inherited::getDrawnForeground();
	}
	else
	{
		return getDisabledForeground();
	}
}

BorderPtr EditableTextComponent::getDrawnBorder(void) const
{
    return Inherited::getDrawnBorder();
}

void EditableTextComponent::setupCursor(void)
{
    UInt32 Cursor;
    if(getEnabled() && getEditable())
    {
        Cursor = WindowEventProducer::CURSOR_I_BEAM;
    }
    else
    {
        Cursor = WindowEventProducer::CURSOR_POINTER;
    }
    if(Cursor != getCursor())
    {
        beginEditCP(EditableTextComponentPtr(this) , CursorFieldMask);
            setCursor(Cursor);
        endEditCP(EditableTextComponentPtr(this) , CursorFieldMask);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

EditableTextComponent::EditableTextComponent(void) :
    Inherited()
{
    setupCursor();
}

EditableTextComponent::EditableTextComponent(const EditableTextComponent &source) :
    Inherited(source)
{
    setupCursor();
}

EditableTextComponent::~EditableTextComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void EditableTextComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & EnabledFieldMask) || (whichField & EditableFieldMask))
    {
        setupCursor();
    }
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

