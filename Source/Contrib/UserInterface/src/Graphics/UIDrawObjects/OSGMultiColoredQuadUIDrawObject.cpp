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

#include "OSGMultiColoredQuadUIDrawObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMultiColoredQuadUIDrawObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGMultiColoredQuadUIDrawObject.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiColoredQuadUIDrawObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MultiColoredQuadUIDrawObject::draw(Graphics* const Graphics, Real32 Opacity) const
{
	Graphics->drawQuad(getPoint1(),getPoint2(),getPoint3(),getPoint4(),
                       getColor1(), getColor2(), getColor3(), getColor4(),
                       getOpacity()*Opacity);
}

void MultiColoredQuadUIDrawObject::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   TopLeft.setValues(
       osgMin(osgMin(osgMin(getPoint1().x(), getPoint2().x()),getPoint3().x()),getPoint4().x()),
       osgMin(osgMin(osgMin(getPoint1().y(), getPoint2().y()),getPoint3().y()),getPoint4().y()));
   
   BottomRight.setValues(
       osgMax(osgMax(osgMax(getPoint1().x(), getPoint2().x()),getPoint3().x()),getPoint4().x()),
       osgMax(osgMax(osgMax(getPoint1().y(), getPoint2().y()),getPoint3().y()),getPoint4().y()));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiColoredQuadUIDrawObject::MultiColoredQuadUIDrawObject(void) :
    Inherited()
{
}

MultiColoredQuadUIDrawObject::MultiColoredQuadUIDrawObject(const MultiColoredQuadUIDrawObject &source) :
    Inherited(source)
{
}

MultiColoredQuadUIDrawObject::~MultiColoredQuadUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiColoredQuadUIDrawObject::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MultiColoredQuadUIDrawObject::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MultiColoredQuadUIDrawObject NI" << std::endl;
}

OSG_END_NAMESPACE
