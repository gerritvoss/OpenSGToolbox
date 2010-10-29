/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGTextComponent.h"

#include "OSGTextComponent.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"


#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGTextComponent.fcd) and
// regenerate the base file.

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

void TextComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextComponent::keyTyped(KeyEventDetails* const e)
{
    switch(e->getKey())
    {
    case KeyEventDetails::KEY_C:
        if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
        {
            copy();
        }
        break;
    case KeyEventDetails::KEY_A:
        if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
        {
            selectAll();
        }
        break;
    default:
        Inherited::keyTyped(e);
        break;
    }
}

void TextComponent::setTextColors(const Color4f& TheColor)
{
    setTextColor(TheColor);
    setDisabledTextColor(TheColor);
    setFocusedTextColor(TheColor);
    setRolloverTextColor(TheColor);
}

void  TextComponent::produceTextValueChanged(void)
{
    TextEventDetailsUnrecPtr Details(TextEventDetails::create(this, getTimeStamp()));

    Inherited::produceTextValueChanged(Details);
}

void  TextComponent::produceCaretChanged(void)
{
    CaretEventDetailsUnrecPtr Details(CaretEventDetails::create(this, getTimeStamp(), getCaretPosition()));

    Inherited::produceCaretChanged(Details);
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
        setText(editText().erase(ClampedStart, ClampedEnd-ClampedStart));
    }
}

void TextComponent::clear(void)
{
    setText("");
    setCaretPosition(0);
}

void TextComponent::insert(const std::string& Text, UInt32 Position)
{
    setText(editText().insert(Position, Text));
    moveCaret(Text.size());
}

void TextComponent::moveCaret(Int32 delta)
{

    UInt32 NewCaretPosition(getCaretPosition());
    if(delta > 0)
    {
        if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&&getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL 
           && getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
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
        if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&&getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL
           && getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
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
        setCaretPosition(NewCaretPosition);
    }
}

void TextComponent::moveCaretToEnd(void)
{
    //Move the caret to the end
    if(getText().size() != getCaretPosition())
    {
        moveCaret(getText().size() - getCaretPosition());
    }
}

void TextComponent::moveCaretToBegin(void)
{
    //Move the caret to the begining
    if(getCaretPosition() != 0)
    {
        moveCaret(-getCaretPosition());
    }
}

void TextComponent::copy(void) const
{
    if(getParentWindow() != NULL && 
       getParentWindow()->getParentDrawingSurface() != NULL &&
       getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->putClipboard(getSelectedText());
    }
}

void TextComponent::select(const UInt32& Start,
                           const UInt32& End)
{
    UInt32 MinPos(osgMin(Start,End)), MaxPos(osgMax(Start,End));
    UInt32 ClampedStart = osgClamp<UInt32>(0, MinPos, osgMin<UInt32>(MaxPos,getText().size()));
    UInt32 ClampedEnd = osgClamp<UInt32>(osgMax<UInt32>(MinPos,0), MaxPos, getText().size());
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

void TextComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & TextFieldMask)
	{
		//Check the Caret Position
		if(getCaretPosition() > getText().size())
		{
            setCaretPosition(getText().size());
		}
		
		if(_TextSelectionStart > getText().size())
		{
			_TextSelectionStart = getText().size();
		}
		
		if(_TextSelectionEnd > getText().size())
		{
			_TextSelectionEnd = getText().size();
		}
		produceTextValueChanged();
	}
    if(whichField & CaretPositionFieldMask)
    {
        produceCaretChanged();
    }
}

void TextComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextComponent NI" << std::endl;
}

OSG_END_NAMESPACE
