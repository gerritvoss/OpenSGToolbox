/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

OSG_BEGIN_NAMESPACE

inline
void GlyphView::setElement(ElementRefPtr& theElement)
{
	_Element = theElement;
	init();
}

inline
void GlyphView::setCaretLocation(Int32 loc)
{
	_Location = loc;
}

inline 
void GlyphView::init(void)
{
	temp = dynamic_pointer_cast<PlainDocumentLeafElement>(_Element);
}

inline void GlyphView::setInitialPosition(Pnt2f init)
{
	_InitialPosition = init;
}

inline 	void GlyphView::setLines(UInt32 lines)
{
	_Lines = lines;
}
inline 	void GlyphView::setLineHeight(Real32 lineheight)
{
	_LineHeight = lineheight;
}

inline 	void GlyphView::setLineWidth(Real32 lineWidth)
{
	_LineWidth = lineWidth;
}


inline void GlyphView::setFont(UIFontRefPtr font)
{
	_Font = font;
}

inline void GlyphView::setLineNumber(UInt32 lineNumber)
{
	_LineNumber = lineNumber;
}

OSG_END_NAMESPACE
