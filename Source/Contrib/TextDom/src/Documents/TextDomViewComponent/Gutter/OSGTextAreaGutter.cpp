/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
 *          Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
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

#include "OSGConfig.h"

#include "OSGTextAreaGutter.h"
#include "OSGTextDomArea.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextAreaGutterBase.cpp file.
// To modify it, please change the .fcd file (OSGTextAreaGutter.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextAreaGutter::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TextAreaGutter::drawInternal(Graphics * const TheGraphics, Real32 Opacity) const
{
    if(getTrackedArea() != NULL &&
       getFont() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideInsetsBounds(TopLeft, BottomRight);

        //Get the lines that are visible from the Tracked TextDomArea
        UInt32 topVisibleLine = getTrackedArea()->getMinVisibleLineNumber();
        UInt32 bottomVisibleLine = getTrackedArea()->getMaxVisibleLineNumber();

        Pnt2f TextDomClipTopLeft, TextDomClipBottomRight;
        getTrackedArea()->getClipBounds(TextDomClipTopLeft, TextDomClipBottomRight);

        std::string LineNumberText;
        Vec2f LineSize;
        //Only draw the line numbers for lines that are visible
        for(UInt32 i(topVisibleLine) ; i<bottomVisibleLine ; ++i)
        {
            LineNumberText = boost::lexical_cast<std::string>(getTrackedArea()->getDocumentLineNum(i)+1);
            LineSize.setValues(BottomRight.x()-TopLeft.x(),
                               getTrackedArea()->getLineHeight(i));

            Pnt2f TextAlignPos =
                calculateAlignment(Pnt2f(TopLeft.x(),
                                         getTrackedArea()->getLineVerticalPosition(i)
                                         - TextDomClipTopLeft.y()),
                                   LineSize,
                                   getFont()->getBounds(LineNumberText),
                                   getAlignment().y(),
                                   getAlignment().x());

            TheGraphics->drawText(TextAlignPos,
                                  LineNumberText,
                                  getFont(),
                                  getTextColor(),
                                  Opacity);
        }
    }
}

/*----------------------- constructors & destructors ----------------------*/

TextAreaGutter::TextAreaGutter(void) :
    Inherited()
{
}

TextAreaGutter::TextAreaGutter(const TextAreaGutter &source) :
    Inherited(source)
{
}

TextAreaGutter::~TextAreaGutter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextAreaGutter::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextAreaGutter::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextAreaGutter NI" << std::endl;
}

OSG_END_NAMESPACE
