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

#include "OSGEditableTextComponent.h"
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGEditableTextComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGEditableTextComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void EditableTextComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void EditableTextComponent::keyPressed(KeyEventDetails* const e)
{
	Inherited::keyPressed(e);
}

void EditableTextComponent::keyReleased(KeyEventDetails* const e)
{
	Inherited::keyReleased(e);
}

void EditableTextComponent::keyTyped(KeyEventDetails* const e)
{
	
    if(getEnabled() && 
       getEditable())
    {
        if(!(e->getModifiers() &( KeyEventDetails::KEY_MODIFIER_ALT | KeyEventDetails::KEY_MODIFIER_CONTROL | KeyEventDetails::KEY_MODIFIER_META )))
        {
            UChar8 TheCharacter(e->getKeyChar());
		    if(TheCharacter>31 && TheCharacter < 127)
		    {
			    if(hasSelection())
			    {
                    deleteSelectedText();
				    setCaretPosition(_TextSelectionStart);
			    }
                insert(std::string( 1,TheCharacter ), _TextSelectionStart);
			    _TextSelectionStart = getCaretPosition();
			    _TextSelectionEnd = _TextSelectionStart;
		    }
    	
            switch(e->getKey())
            {
            case KeyEventDetails::KEY_BACK_SPACE:
			    if(hasSelection())
			    {
                    deleteSelectedText();
			    }
			    else
			    {	
                    //erase at the current caret position
                    Int32 DeleteIndex(getCaretPosition());
                    if(DeleteIndex != 0)
                    {
                        moveCaret(-1);
                        deleteRange(DeleteIndex-1, DeleteIndex);
                    }
			    }
                break;
            case KeyEventDetails::KEY_DELETE:
			    if(hasSelection())
			    {
                    deleteSelectedText();
			    }
			    else if(getText().size()>0)
			    {
				    //erase at the current caret position
                    deleteRange(getCaretPosition(), getCaretPosition()+1);
				    _TextSelectionStart = getCaretPosition();
				    _TextSelectionEnd = _TextSelectionStart;
			    }
                break;
            case KeyEventDetails::KEY_RIGHT:
            case KeyEventDetails::KEY_KEYPAD_RIGHT:
                moveCaret(1);
                break;
            case KeyEventDetails::KEY_LEFT:
            case KeyEventDetails::KEY_KEYPAD_LEFT:
                moveCaret(-1);
                break;
            case KeyEventDetails::KEY_HOME:
                moveCaretToBegin();
                break;
            case KeyEventDetails::KEY_PAGE_UP:
                moveCaretToBegin();
                break;
            case KeyEventDetails::KEY_END:
                moveCaretToEnd();
                break;
            case KeyEventDetails::KEY_PAGE_DOWN:
                moveCaretToEnd();
                break;
            }
        }
        else
        {
            switch(e->getKey())
            {
            case KeyEventDetails::KEY_V:
                if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
                {
                    paste();
                }
                break;
            case KeyEventDetails::KEY_X:
                if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
                {
                    cut();
                }
                break;
            }
        }
	}

	Inherited::keyTyped(e);
}

Layer* EditableTextComponent::getDrawnBackground(void) const
{
	if(getEditable())
	{
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBackground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBackground();
            }
            else
            {
                return getBackground();
            }
        }
        else
        {
            return getDisabledBackground();
        }
	}
	else
	{
		return getDisabledBackground();
	}
}

Layer* EditableTextComponent::getDrawnForeground(void) const
{
	if(getEditable())
	{
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedForeground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverForeground();
            }
            else
            {
                return getForeground();
            }
        }
        else
        {
            return getDisabledForeground();
        }
	}
	else
	{
		return getDisabledForeground();
	}
}

Border* EditableTextComponent::getDrawnBorder(void) const
{
	if(getEditable())
	{
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBorder();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBorder();
            }
            else
            {
                return getBorder();
            }
        }
        else
        {
            return getDisabledBorder();
        }
	}
	else
	{
		return getDisabledBorder();
	}
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
        setCursor(Cursor);
    }
}

void EditableTextComponent::overwriteSelection(const std::string& Text)
{
    //Delete selected text
    deleteSelectedText();

    //Write to Caret position
    insert(Text, getCaretPosition());
}

void EditableTextComponent::cut(void)
{
    copy();
    deleteSelectedText();
}

void EditableTextComponent::paste(void)
{
    if(getParentWindow() != NULL && 
        getParentWindow()->getParentDrawingSurface() != NULL &&
        getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        write(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getClipboard());
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

void EditableTextComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

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

OSG_END_NAMESPACE
