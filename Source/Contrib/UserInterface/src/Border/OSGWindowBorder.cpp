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

#include "OSGWindowBorder.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGWindowBorderBase.cpp file.
// To modify it, please change the .fcd file (OSGWindowBorder.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowBorder::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void WindowBorder::draw(Graphics* const g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{
    Real32 LeftIn, RightIn, BottomIn, UpperIn;
    getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    if(getTitlebar() != NULL)
    {
        UpperIn += getTitlebar()->getSize().y();
    }
    getInnerBorder()->draw(g, x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn, Opacity);
    getOuterBorder()->draw(g, x, y, Width, Height, Opacity);

}

void WindowBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
    Real32 LeftIn, LeftIn2, RightIn, RightIn2, BottomIn, BottomIn2, UpperIn, UpperIn2;
    getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    getInnerBorder()->getInsets(LeftIn2, RightIn2,UpperIn2, BottomIn2) ;
    Left = LeftIn+LeftIn2;
    Right = RightIn+RightIn2;
    Bottom = BottomIn+BottomIn2;
    Top = UpperIn+UpperIn2;

    if(getTitlebar() != NULL)
    {
        Top += getTitlebar()->getSize().y();
    }
}

void WindowBorder::activateInternalDrawConstraints(Graphics* const g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    Real32 LeftIn, RightIn, BottomIn, UpperIn;
    getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    if(getTitlebar() != NULL)
    {
        UpperIn += getTitlebar()->getSize().y();
    }
    getOuterBorder()->activateInternalDrawConstraints(g, x, y, Width, Height);
    getInnerBorder()->activateInternalDrawConstraints(g,x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn);
}

bool WindowBorder::isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    Real32 LeftIn, RightIn, BottomIn, UpperIn;
    getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    if(getTitlebar() != NULL)
    {
        UpperIn += getTitlebar()->getSize().y();
    }
    return (getInnerBorder()->isContained(p,x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn) ||
            getOuterBorder()->isContained(p,x,y,Width,Height));
}

void WindowBorder::getTitlebarBounds(const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    Real32 LeftIn(0.0f), RightIn(0.0f), BottomIn(0.0f), UpperIn(0.0f);
    if(getOuterBorder() != NULL)
    {
        getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    }

    TopLeft.setValues(x+LeftIn, y+UpperIn);
    if(getTitlebar() != NULL)
    {
        UpperIn += getTitlebar()->getSize().y();
    }

    BottomRight.setValues(x+Width-RightIn, y+UpperIn);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowBorder::WindowBorder(void) :
    Inherited()
{
}

WindowBorder::WindowBorder(const WindowBorder &source) :
    Inherited(source)
{
}

WindowBorder::~WindowBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WindowBorder::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void WindowBorder::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump WindowBorder NI" << std::endl;
}

OSG_END_NAMESPACE
