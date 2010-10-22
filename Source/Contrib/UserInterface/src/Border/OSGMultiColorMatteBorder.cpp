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

#include "OSGMultiColorMatteBorder.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiColorMatteBorderBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiColorMatteBorder.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiColorMatteBorder::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MultiColorMatteBorder::draw(Graphics* const g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{
    //x, y is upper left point

    //Top
    g->drawQuad(
                Pnt2f(x+getLeftWidth(),y),
                Pnt2f(x+Width, y),
                Pnt2f(x+Width, y+getTopWidth()),
                Pnt2f(x+getLeftWidth(), y+getTopWidth()),
                getTopLineTopColor(),
                getTopLineTopColor(),
                getTopLineBottomColor(),
                getTopLineBottomColor(),
                Opacity);
    //Left
    g->drawQuad(
                Pnt2f(x,y),
                Pnt2f(x+getLeftWidth(), y),
                Pnt2f(x+getLeftWidth(), y+Height-getBottomWidth()),
                Pnt2f(x, y+Height-getBottomWidth()),
                getLeftLineLeftColor(),
                getLeftLineRightColor(),
                getLeftLineRightColor(),
                getLeftLineLeftColor(),
                Opacity);
    //Right
    g->drawQuad(
                Pnt2f(x+Width-getRightWidth(),y+getTopWidth()),
                Pnt2f(x+Width, y+getTopWidth()),
                Pnt2f(x+Width, y+Height),
                Pnt2f(x+Width-getRightWidth(), y+Height),
                getRightLineLeftColor(),
                getRightLineRightColor(),
                getRightLineRightColor(),
                getRightLineLeftColor(),
                Opacity);
    //Bottom
    g->drawQuad(
                Pnt2f(x,y+Height-getBottomWidth()),
                Pnt2f(x+Width-getRightWidth(), y+Height-getBottomWidth()),
                Pnt2f(x+Width-getRightWidth(), y+Height),
                Pnt2f(x, y+Height),
                getBottomLineTopColor(),
                getBottomLineTopColor(),
                getBottomLineBottomColor(),
                getBottomLineBottomColor(),
                Opacity);
    //g->drawQuad(Pnt2f(x, y+Height-getBottomWidth()), Pnt2f(x+Width, y+Height), getBottomColor(), Opacity);

}

void MultiColorMatteBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
    Left = getLeftWidth();
    Right = getRightWidth();
    Top = getTopWidth();
    Bottom = getBottomWidth();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiColorMatteBorder::MultiColorMatteBorder(void) :
    Inherited()
{
}

MultiColorMatteBorder::MultiColorMatteBorder(const MultiColorMatteBorder &source) :
    Inherited(source)
{
}

MultiColorMatteBorder::~MultiColorMatteBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiColorMatteBorder::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MultiColorMatteBorder::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiColorMatteBorder NI" << std::endl;
}

OSG_END_NAMESPACE
