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

#include "OSGPolygonUIDrawObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPolygonUIDrawObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGPolygonUIDrawObject.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PolygonUIDrawObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PolygonUIDrawObject::draw(Graphics* const Graphics, Real32 Opacity) const
{
	Graphics->drawPolygon(*getMFVerticies(), getColor(), getOpacity()*Opacity);
}

void PolygonUIDrawObject::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	if(getMFVerticies()->size() > 0)
	{
		TopLeft = getVerticies(0);
		BottomRight = TopLeft;
		//Determine Top Left And Bottom Right
		for(UInt32 i(0) ; i<getMFVerticies()->size(); ++i)
		{
		    TopLeft.setValues( osgMin(TopLeft.x(), getVerticies(i).x()),
				               osgMin(TopLeft.y(), getVerticies(i).y()) );

		    BottomRight.setValues(osgMax<Real32>(BottomRight.x(), getVerticies(i).x()),
		                          osgMax<Real32>(BottomRight.y(), getVerticies(i).y()) );
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PolygonUIDrawObject::PolygonUIDrawObject(void) :
    Inherited()
{
}

PolygonUIDrawObject::PolygonUIDrawObject(const PolygonUIDrawObject &source) :
    Inherited(source)
{
}

PolygonUIDrawObject::~PolygonUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PolygonUIDrawObject::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PolygonUIDrawObject::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PolygonUIDrawObject NI" << std::endl;
}

OSG_END_NAMESPACE
