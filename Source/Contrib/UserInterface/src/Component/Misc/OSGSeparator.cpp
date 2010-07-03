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

#include "OSGSeparator.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSeparatorBase.cpp file.
// To modify it, please change the .fcd file (OSGSeparator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Separator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Separator::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
   
    //Calculate Alignment
    Pnt2f AlignedPosition;
    Pnt2f LineTopLeft(0,0), LineBottomRight(getSeparatorSize(),getSeparatorSize());

    if(getOrientation() == Separator::VERTICAL_ORIENTATION)
    {
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (LineBottomRight - LineTopLeft),0.0, 0.5);

        Graphics->drawRect(AlignedPosition, AlignedPosition + Vec2f(getSeparatorSize(),BottomRight.y() - TopLeft.y()), getColor(), getOpacity()*Opacity);
    }
    else
    {
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (LineBottomRight - LineTopLeft),0.5, 0.0);

        Graphics->drawRect(AlignedPosition, AlignedPosition + Vec2f(BottomRight.x() - TopLeft.x(),getSeparatorSize()), getColor(), getOpacity()*Opacity);
    }
}

Vec2f Separator::getContentRequestedSize(void) const
{
    return Vec2f(getSeparatorSize(), getSeparatorSize());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Separator::Separator(void) :
    Inherited()
{
}

Separator::Separator(const Separator &source) :
    Inherited(source)
{
}

Separator::~Separator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Separator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Separator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Separator NI" << std::endl;
}

OSG_END_NAMESPACE
