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

#include "OSGGlassLayer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGlassLayerBase.cpp file.
// To modify it, please change the .fcd file (OSGGlassLayer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GlassLayer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GlassLayer::draw(Graphics* const TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
    Pnt2f IntermediatePosition;
    Vec3f Bounds(BottomRight- TopLeft);
    
    //Setup the Blending equations properly
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glBegin(GL_TRIANGLE_FAN);
        glColor4f(getEdgeColor().red(),getEdgeColor().green(),getEdgeColor().blue(),getEdgeColor().alpha() * Opacity);
        glVertex2f(getStartPosition().x(), getEndPosition().y());
        glColor4f(getCenterColor().red(),getCenterColor().green(),getCenterColor().blue(),getCenterColor().alpha() * Opacity);
        glVertex2fv(getStartPosition().getValues());
        for(UInt32 i(0) ; i<_Segments.size(); ++i)
        {
            IntermediatePosition.setValues(_Segments[i].x() * Bounds.x(),_Segments[i].y() * Bounds.y());
            glVertex2fv(IntermediatePosition.getValues());
        }
        glVertex2fv(getEndPosition().getValues());
    glEnd();

    glDisable(GL_BLEND);

}

void GlassLayer::updateSegments(void)
{
    //Calculate a Cubic Hermite spline
    _Segments.clear();

    Vec2f Pos;
    Real32 t,
           t_sqr,
           t_cub;
    for(UInt32 i(1) ; i<getSegments() ; ++i)
    {
        t = static_cast<Real32>(i)/static_cast<Real32>(getSegments());
        t_sqr = t*t;
        t_cub = t_sqr*t;

        Pos = ( 2.0f * t_cub - 3.0f*t_sqr + 1.0f) * getStartPosition().subZero() +
              (        t_cub - 2.0f*t_sqr +    t) * getStartDirection() +
              (-2.0f * t_cub + 3.0f*t_sqr       ) * getEndPosition().subZero() +
              (        t_cub -      t_sqr       ) * getEndDirection();

        _Segments.push_back(Pos);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GlassLayer::GlassLayer(void) :
    Inherited()
{
}

GlassLayer::GlassLayer(const GlassLayer &source) :
    Inherited(source),
    _Segments(source._Segments)
{
}

GlassLayer::~GlassLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GlassLayer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & StartPositionFieldMask) ||
       (whichField & StartDirectionFieldMask) ||
       (whichField & EndPositionFieldMask) ||
       (whichField & EndDirectionFieldMask) ||
       (whichField & SegmentsFieldMask)
        )
    {
        updateSegments();
    }
}

void GlassLayer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GlassLayer NI" << std::endl;
}

OSG_END_NAMESPACE
