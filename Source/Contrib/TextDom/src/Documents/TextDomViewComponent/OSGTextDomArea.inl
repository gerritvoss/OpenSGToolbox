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
#include "OSGTextFileHandler.h"
#include "OSGTextDomLayoutManager.h"

OSG_BEGIN_NAMESPACE

inline
void TextDomArea::saveFile(const BoostPath& pathOfFile)
{
    TextFileHandler::the()->forceWrite(getDocumentModel(),pathOfFile);
}

inline
UInt32 TextDomArea::getMinVisibleLineNumber(void) const
{
    return getLayoutManager()->getTopmostVisibleLineNumber();
}

inline
UInt32 TextDomArea::getMaxVisibleLineNumber(void) const
{
    return getMinVisibleLineNumber() + getLayoutManager()->getLinesToBeDisplayed();
}

inline
UInt32 TextDomArea::getNumDocumentLines(void) const
{
    /*! \todo Implement*/
    return 0;
}

inline
UInt32 TextDomArea::getNumLines(void) const
{
    /*! \todo Implement*/
    return getNumDocumentLines();
}

inline
bool TextDomArea::isWrappedLine(UInt32 LineNum) const
{
    /*! \todo Implement*/
    return false;
}

inline
Real32 TextDomArea::getLineHeight(UInt32 LineNum) const
{
    /*! \todo Take into account variable line height*/
    return getLayoutManager()->getHeightOfLine();
}

inline
std::string TextDomArea::getText(void) const
{
    return getDocumentModel()->getText(0,-1);
}

inline
UInt32 TextDomArea::getDocumentLineNum(UInt32 LineNum) const
{
    /*! \todo Implement*/
    return LineNum;
}

inline
Real32 TextDomArea::getLineVerticalPosition(UInt32 LineNum) const
{
    /*! \todo Take into account variable line height*/
    return static_cast<Real32>(LineNum) * getLineHeight(LineNum);
}

OSG_END_NAMESPACE
