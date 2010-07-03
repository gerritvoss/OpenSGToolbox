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

#include "OSGDiscUIDrawObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDiscUIDrawObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGDiscUIDrawObject.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DiscUIDrawObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DiscUIDrawObject::draw(Graphics* const Graphics, Real32 Opacity) const
{
	Graphics->drawDisc(getCenter(), getWidth(), getHeight(), getStartAngleRad(), getEndAngleRad(), getSubDivisions(), getCenterColor(), getOuterColor(), getOpacity()*Opacity);
}

void DiscUIDrawObject::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	TopLeft = Pnt2f(getCenter().x()-getWidth(), getCenter().y()-getHeight());
	BottomRight = Pnt2f(getCenter().x()+getWidth(), getCenter().y()+getHeight());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DiscUIDrawObject::DiscUIDrawObject(void) :
    Inherited()
{
}

DiscUIDrawObject::DiscUIDrawObject(const DiscUIDrawObject &source) :
    Inherited(source)
{
}

DiscUIDrawObject::~DiscUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DiscUIDrawObject::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DiscUIDrawObject::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DiscUIDrawObject NI" << std::endl;
}

OSG_END_NAMESPACE
