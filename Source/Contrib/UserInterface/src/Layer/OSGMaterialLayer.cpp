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

#include "OSGMaterialLayer.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMaterialLayerBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialLayer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialLayer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MaterialLayer::draw(Graphics* const TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
    if(!getMaterial())
    {
        return;
    }

	glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	GLdouble Plane0[4], Plane1[4], Plane2[4], Plane3[4];
	glGetClipPlane(GL_CLIP_PLANE0, Plane0);
	glGetClipPlane(GL_CLIP_PLANE1, Plane1);
	glGetClipPlane(GL_CLIP_PLANE2, Plane2);
	glGetClipPlane(GL_CLIP_PLANE3, Plane3);

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);

	// The clipping plane for the background must get set to inside the
	// border of the component. It was the outside of the component,
	// so it has to be reset to the stored values from above at the end.
	Vec4d LeftPlaneEquation(1.0,0.0,0.0,-TopLeft.x()),
          RightPlaneEquation(-1.0,0.0,0.0,BottomRight.x()),
          TopPlaneEquation(0.0,1.0,0.0,-TopLeft.y()),
          BottomPlaneEquation(0.0,-1.0,0.0,BottomRight.y());
    
    glClipPlane(GL_CLIP_PLANE0,LeftPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE1,RightPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE2,TopPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE3,BottomPlaneEquation.getValues());

	Vec2f BackgroundSize (BottomRight - TopLeft);

	Vec2f Size(0.0,0.0);
	switch(getScale())
	{
	case SCALE_ABSOLUTE:
	   Size.setValue(getScaleAbsoluteSize());
	   break;
	default:
	case SCALE_STRETCH:
	   Size.setValue(BackgroundSize);
	   break;
	}

	Pnt2f Pos( calculateAlignment(TopLeft,BackgroundSize, Size, getVerticalAlignment(), getHorizontalAlignment()) );

	TheGraphics->drawQuad(Pos, Pnt2f(Pos.x()+Size.x(), Pos.y()), Pos+Size, Pnt2f(Pos.x(), Pos.y()+Size.y()),
            Vec2f(0.0, 0.0), Vec2f(1.0, 0.0), Vec2f(1.0, 1.0), Vec2f(0.0, 1.0),
            getMaterial(), Opacity);

	glPopAttrib();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MaterialLayer::MaterialLayer(void) :
    Inherited()
{
}

MaterialLayer::MaterialLayer(const MaterialLayer &source) :
    Inherited(source)
{
}

MaterialLayer::~MaterialLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialLayer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MaterialLayer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MaterialLayer NI" << std::endl;
}

OSG_END_NAMESPACE
