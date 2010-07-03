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

#include "OSGTextUIDrawObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextUIDrawObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGTextUIDrawObject.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextUIDrawObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextUIDrawObject::draw(Graphics* const Graphics, Real32 Opacity) const
{
	Graphics->drawText(getPosition(), getText(), getFont(), getColor(), getOpacity()*Opacity);
}

void TextUIDrawObject::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   Pnt2f TextTopLeft, TextBottomRight;
   getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
   TopLeft = getPosition();
   BottomRight = TopLeft + (TextBottomRight - TextTopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextUIDrawObject::TextUIDrawObject(void) :
    Inherited()
{
}

TextUIDrawObject::TextUIDrawObject(const TextUIDrawObject &source) :
    Inherited(source)
{
}

TextUIDrawObject::~TextUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextUIDrawObject::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextUIDrawObject::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextUIDrawObject NI" << std::endl;
}

OSG_END_NAMESPACE
