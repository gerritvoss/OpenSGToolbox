/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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
#include "OSGTextDomArea.h"
#include "OSGTextAreaGutter.h"

OSG_BEGIN_NAMESPACE

inline
void AdvancedTextDomArea::setTextDomArea(TextDomArea* const duplicatedTextDom)
{
	return setTextArea(duplicatedTextDom);
}

inline
TextDomArea* AdvancedTextDomArea::getTextDomArea(void) const
{
	return getTextArea();
}

inline
void AdvancedTextDomArea::setText(const std::string& txt)
{
	if(getTextArea() != NULL)
	{	
		getTextArea()->setText(txt);
	}
}

inline
void AdvancedTextDomArea::setEditable(bool val)
{
	if(getTextArea() != NULL)
	{	
		getTextArea()->setEditable(val);
	}
}

inline
Real32 AdvancedTextDomArea::getGutterWidth(void) const
{
    return getGutter()->getPreferredSize().x();
}

inline
void AdvancedTextDomArea::setGutterWidth(Real32 Width)
{
    return getGutter()->setPreferredSize(Vec2f(Width,
                                               getGutter()->getPreferredSize().y()));
}


inline
Vec2f AdvancedTextDomArea::getGutterSize(void) const
{
    return getGutter()->getSize();
}

inline
const Vec2f& AdvancedTextDomArea::getGutterAlignment(void) const
{
    return getGutter()->getAlignment();
}

inline
const Color4f& AdvancedTextDomArea::getGutterTextColor(void) const
{
    return getGutter()->getTextColor();
}

inline
UIFont* AdvancedTextDomArea::getGutterFont (void) const
{
    return getGutter()->getFont();
}

inline
void AdvancedTextDomArea::setGutterAlignment(const Vec2f& Align)
{
    getGutter()->setAlignment(Align);
}

inline
void AdvancedTextDomArea::setGutterTextColor(const Color4f& Color)
{
    getGutter()->setTextColor(Color);
}

inline
void AdvancedTextDomArea::setGutterFont(UIFont* const Font)
{
    getGutter()->setFont(Font);
}

OSG_END_NAMESPACE
