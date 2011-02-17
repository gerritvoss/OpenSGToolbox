/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#define HSL _HighlightStartLine
#define HSI _HighlightStartIndex
#define HEL _HighlightEndLine
#define HEI _HighlightEndIndex


OSG_BEGIN_NAMESPACE


inline	
void FixedHeightLayoutManager::setCaretIndex(UInt32 value)
{
	_CaretIndex = value;
}

inline	
void FixedHeightLayoutManager::setCaretLine(UInt32 value)
{
	_CaretLine = value;
}

inline	UInt32 FixedHeightLayoutManager::getCaretIndex(void) const
{
	return _CaretIndex;
}
inline UInt32 FixedHeightLayoutManager::getCaretLine(void) const
{
	return _CaretLine;
}
inline bool FixedHeightLayoutManager::isSomethingSelected(void)
{
	 return (HSL != HEL ||  HSI != HEI);
}

inline void FixedHeightLayoutManager::setHighlight(UInt32 startline,UInt32 startindex,UInt32 endline,UInt32 endindex)
{
	HSL = startline;
	HSI= startindex;
	HEL= endline;
	HEI= endindex;
}
inline Real32 FixedHeightLayoutManager::getHeightOfLine(void)
{
	return heightOfLine;
}

inline Real32 FixedHeightLayoutManager::getCaretXPosition(void)
{
	return _CaretXPosition;
}

inline Real32 FixedHeightLayoutManager::getCaretYPosition(void)
{
	return _CaretYPosition;
}

inline Element* FixedHeightLayoutManager::getRootElement(void)
{
	return rootElement;
}

inline UInt32 FixedHeightLayoutManager::getHEI(void)
{
	return HEI;
}

inline UInt32 FixedHeightLayoutManager::getHEL(void)
{
	return HEL;
}

inline UInt32 FixedHeightLayoutManager::getHSI(void)
{
	return HSI;
}

inline UInt32 FixedHeightLayoutManager::getHSL(void)
{
	return HSL;
}

inline void FixedHeightLayoutManager::setHSL(UInt32 val)
{
	HSL = val;
}

inline void FixedHeightLayoutManager::setHSI(UInt32 val)
{
	HSI = val;
}

inline void FixedHeightLayoutManager::setHEL(UInt32 val)
{
	HEL = val;
}

inline void FixedHeightLayoutManager::setHEI(UInt32 val)
{
	HEI = val;
}

inline Real32 FixedHeightLayoutManager::getPreferredWidth(void)
{
	return _preferredWidth;
}

inline bool FixedHeightLayoutManager::getBracesHighlightFlag(void)
{
	return _BracesHighlightFlag;
}

inline UInt32 FixedHeightLayoutManager::getStartingBraceLine(void)
{
	return _StartingBraceLine;
}

inline UInt32 FixedHeightLayoutManager::getStartingBraceIndex(void)
{
	return _StartingBraceIndex;
}

inline UInt32 FixedHeightLayoutManager::getEndingBraceLine(void)
{
	return _EndingBraceLine;
}

inline UInt32 FixedHeightLayoutManager::getEndingBraceIndex(void)
{
	return _EndingBraceIndex;
}

inline Real32 FixedHeightLayoutManager::getGutterSpace(void)
{
	return _GutterSpace;
}

inline Real32 FixedHeightLayoutManager::getGutterSeparation(void)
{
	return _GutterSeparation;
}

OSG_END_NAMESPACE
