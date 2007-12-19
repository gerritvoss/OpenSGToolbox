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

