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

#include "OSGTextComponent.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>


#include <boost/bind.hpp>

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

const OSG::BitVector  TextComponent::TextColorsFieldMask = 
    (TypeTraits<BitVector>::One << TextComponentBase::TextColorFieldId) |
    (TypeTraits<BitVector>::One << TextComponentBase::DisabledTextColorFieldId) |
    (TypeTraits<BitVector>::One << TextComponentBase::FocusedTextColorFieldId) |
    (TypeTraits<BitVector>::One << TextComponentBase::RolloverTextColorFieldId);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection TextComponent::addTextListener(TextListenerPtr Listener)
{
   _TextListeners.insert(Listener);
   return EventConnection(
       boost::bind(&TextComponent::isTextListenerAttached, this, Listener),
       boost::bind(&TextComponent::removeTextListener, this, Listener));
}

void TextComponent::removeTextListener(TextListenerPtr Listener)
{
   TextListenerSetItor EraseIter(_TextListeners.find(Listener));
   if(EraseIter != _TextListeners.end())
   {
      _TextListeners.erase(EraseIter);
   }
}

EventConnection TextComponent::addCaretListener(CaretListenerPtr Listener)
{
   _CaretListeners.insert(Listener);
   return EventConnection(
       boost::bind(&TextComponent::isCaretListenerAttached, this, Listener),
       boost::bind(&TextComponent::removeCaretListener, this, Listener));
}

void TextComponent::removeCaretListener(CaretListenerPtr Listener)
{
   CaretListenerSetItor EraseIter(_CaretListeners.find(Listener));
   if(EraseIter != _CaretListeners.end())
   {
      _CaretListeners.erase(EraseIter);
   }
}

void TextComponent::keyTyped(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_C && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL) &&
        getParentWindow() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer())
    {
        getParentWindow()->getDrawingSurface()->getEventProducer()->putClipboard(getSelectedText());
    }
    else if(e->getKey() == KeyEvent::KEY_A && (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL))
    {
        selectAll();
    }
    else
    {
        Inherited::keyTyped(e);
    }
}

void TextComponent::setTextColors(const Color4f& TheColor)
{
	setTextColor(TheColor);
	setDisabledTextColor(TheColor);
	setFocusedTextColor(TheColor);
	setRolloverTextColor(TheColor);
}

void  TextComponent::produceTextValueChanged(const TextEventPtr e)
{
   for(TextListenerSetConstItor SetItor(_TextListeners.begin()) ; SetItor != _TextListeners.end() ; ++SetItor)
   {
      (*SetItor)->textValueChanged(e);
   }
   _Producer.produceEvent(TextValueChangedMethodId,e);
}

void  TextComponent::produceCaretChanged(const CaretEventPtr e)
{
   for(CaretListenerSetConstItor SetItor(_CaretListeners.begin()) ; SetItor != _CaretListeners.end() ; ++SetItor)
   {
      (*SetItor)->caretChanged(e);
   }
   _Producer.produceEvent(CaretChangedMethodId,e);
}

Color4f TextComponent::getDrawnTextColor(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(_MouseInComponentLastMouse)
        {
            return getRolloverTextColor();
        }
        else
        {
            return getTextColor();
        }
    }
    else
    {
        return getDisabledTextColor();
    }
}

void TextComponent::deleteSelectedText(void)
{
    if(hasSelection())
    {
	    //erase the selected portions
	    setCaretPosition(_TextSelectionStart);
        deleteRange(_TextSelectionStart, _TextSelectionEnd);
	    _TextSelectionStart = getCaretPosition();
	    _TextSelectionEnd = _TextSelectionStart;
    }
}

void TextComponent::deleteRange(UInt32 Start, UInt32 End)
{
    UInt32 ClampedStart = osgClamp<UInt32>(0, Start, osgMin<UInt32>(End,getText().size()));
    UInt32 ClampedEnd = osgClamp<UInt32>(osgMax<UInt32>(Start,0), End, getText().size());
    if(ClampedEnd-ClampedStart > 0)
    {
        beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
            setText(editText().erase(ClampedStart, ClampedEnd-ClampedStart));
        endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
    }
}

void TextComponent::clear(void)
{
    beginEditCP(TextComponentPtr(this),TextFieldMask);
        setText("");
    endEditCP(TextComponentPtr(this),TextFieldMask);
}

void TextComponent::insert(const std::string& Text, UInt32 Position)
{
    beginEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
	    setText(editText().insert(Position, Text));
    endEditCP(TextComponentPtr(this), TextComponent::TextFieldMask);
    moveCaret(Text.size());
}

void TextComponent::moveCaret(Int32 delta)
{
    
	UInt32 NewCaretPosition(getCaretPosition());
    if(delta > 0)
    {
	    if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC 
		    && getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
	    {
		    if(_TextSelectionEnd > _TextSelectionStart && _TextSelectionEnd < getText().size() && getCaretPosition()>_TextSelectionStart)
		    {
			    NewCaretPosition = getCaretPosition()+delta;
			    _TextSelectionEnd=NewCaretPosition;
		    }
		    else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition() < getText().size())
		    {
			    NewCaretPosition = getCaretPosition()+delta;
			    _TextSelectionStart = NewCaretPosition;
		    }
		    else if(getCaretPosition()< getText().size() && _TextSelectionEnd <=_TextSelectionStart )
		    {
			    _TextSelectionStart = NewCaretPosition;
			    NewCaretPosition = getCaretPosition()+delta;
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
		    NewCaretPosition = getCaretPosition()+delta;
		    _TextSelectionStart = NewCaretPosition;
		    _TextSelectionEnd = NewCaretPosition;
	    }
    }
    else if(delta < 0)
    {
	    if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC
		    && getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
	    {
		    if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size() && getCaretPosition()>_TextSelectionStart && getCaretPosition()>0)
		    {
			    NewCaretPosition = getCaretPosition()+delta;
			    _TextSelectionEnd=NewCaretPosition;
		    }
		    else if(_TextSelectionEnd >_TextSelectionStart && _TextSelectionEnd <= getText().size()&& getCaretPosition()>0)
		    {
			    NewCaretPosition = getCaretPosition()+delta;
			    _TextSelectionStart = NewCaretPosition;
		    }
		    else if(_TextSelectionEnd <=_TextSelectionStart && getCaretPosition()>0 )
		    {
			    _TextSelectionEnd = NewCaretPosition;
			    NewCaretPosition = getCaretPosition()+delta;
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
		    NewCaretPosition = getCaretPosition()+delta;
		    _TextSelectionStart = NewCaretPosition;
		    _TextSelectionEnd = _TextSelectionStart;
	    }
    }
    
	
	if(NewCaretPosition != getCaretPosition())
	{
		beginEditCP(TextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(NewCaretPosition);
		endEditCP(TextComponentPtr(this), CaretPositionFieldMask);
	}
}

void TextComponent::moveCaretToEnd(void)
{
	//Move the caret to the end
	if(getText().size() != getCaretPosition())
	{
		beginEditCP(TextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(getText().size());
		endEditCP(TextComponentPtr(this), CaretPositionFieldMask);
	}
}

void TextComponent::moveCaretToBegin(void)
{
	//Move the caret to the begining
	if(0 != getCaretPosition())
	{
		beginEditCP(TextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(0);
		endEditCP(TextComponentPtr(this), CaretPositionFieldMask);
	}
}

void TextComponent::copy(void) const
{
    if(getParentWindow() != NullFC && 
        getParentWindow()->getDrawingSurface() != NullFC &&
        getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
        getParentWindow()->getDrawingSurface()->getEventProducer()->putClipboard(getSelectedText());
    }
}

void TextComponent::select(const UInt32& Start,
						const UInt32& End)
{
    UInt32 ClampedStart = osgClamp<UInt32>(0, Start, osgMin<UInt32>(End,getText().size()));
    UInt32 ClampedEnd = osgClamp<UInt32>(osgMax<UInt32>(Start,0), End, getText().size());
    _TextSelectionStart = ClampedStart;
    _TextSelectionEnd = ClampedEnd;
}

std::string TextComponent::getSelectedText(void) const
{
    if(hasSelection())
    {
        return getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart);
    }
    else
    {
        return std::string("");
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextComponent::TextComponent(void) :
    Inherited(),
        _TextSelectionStart(0),
        _TextSelectionEnd(0)
{
}

TextComponent::TextComponent(const TextComponent &source) :
    Inherited(source),
    _TextSelectionStart(0),
    _TextSelectionEnd(0)
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
		//Check the Caret Position
		if(getCaretPosition() > getText().size())
		{
			beginEditCP(TextComponentPtr(this), CaretPositionFieldMask);
				setCaretPosition(getText().size());
			endEditCP(TextComponentPtr(this), CaretPositionFieldMask);
		}
		
		if(_TextSelectionStart > getText().size())
		{
			_TextSelectionStart = getText().size();
		}
		
		if(_TextSelectionEnd > getText().size())
		{
			_TextSelectionEnd = getText().size();
		}
		produceTextValueChanged(TextEvent::create(TextComponentPtr(this), getTimeStamp()));
	}
    if(whichField & CaretPositionFieldMask)
    {
        produceCaretChanged(CaretEvent::create(TextComponentPtr(this), getSystemTime(), getCaretPosition()));
    }
}

void TextComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextComponent NI" << std::endl;
}

OSG_END_NAMESPACE

