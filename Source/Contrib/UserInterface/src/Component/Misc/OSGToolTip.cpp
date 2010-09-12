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

#include "OSGToolTip.h"
#include "OSGUIDrawUtils.h"
#include "OSGBorder.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGToolTipBase.cpp file.
// To modify it, please change the .fcd file (OSGToolTip.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ToolTip::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ToolTip::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    if(getText() != "" && getFont() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);

        Pnt2f TextTopLeft, TextBottomRight;
        getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
        TheGraphics->drawText(calculateAlignment(TopLeft, 
                                                 BottomRight-TopLeft,
                                                 (TextBottomRight-TextTopLeft),
                                                 getAlignment().y(),
                                                 getAlignment().x()),
                              getText(),
                              getFont(),
                              getTextColor(),
                              getOpacity()*Opacity);
    }
}

Vec2f ToolTip::calculatePreferredSize(void) const
{
    if(getFont() == NULL)
    {
        return getPreferredSize();
    }

    Real32 Top(0),Bottom(0),Left(0),Right(0);
    if(getDrawnBorder() != NULL)
    {
        getDrawnBorder()->getInsets(Left, Right, Top, Bottom);
    }

    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    return TextBottomRight - TextTopLeft + Vec2f(Left+Right+2, Top+Bottom+2);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ToolTip::ToolTip(void) :
    Inherited()
{
}

ToolTip::ToolTip(const ToolTip &source) :
    Inherited(source)
{
}

ToolTip::~ToolTip(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ToolTip::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & TextFieldMask)
    {
        setPreferredSize(calculatePreferredSize());
        if(getSize() != getPreferredSize())
        {
            setSize(getPreferredSize());
        }
    }
}

void ToolTip::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ToolTip NI" << std::endl;
}

OSG_END_NAMESPACE
