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

#include "OSGUIRectangleMouseTransformFunctor.h"
#include "OSGLine.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGCamera.h"

#include "OSGUIRectangleMouseTransformFunctor.h"
#include "OSGUIRectangle.h"
#include "OSGLineUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIRectangleMouseTransformFunctorBase.cpp file.
// To modify it, please change the .fcd file (OSGUIRectangleMouseTransformFunctor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIRectangleMouseTransformFunctor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool UIRectangleMouseTransformFunctor::viewportToRenderingSurface(const Pnt2f& ViewportPoint,
                                                                  const Viewport* TheViewport,
                                                                  Pnt2f& Result) const
{
    //Get Viewport to View Space line
    Line l;
    if( !TheViewport->getCamera()->calcViewRay( l, ViewportPoint.x(), ViewportPoint.y(), *TheViewport ) )
    {
        return false;
    }

    //Transform Line to UIRectangle Space
    Matrix m ;
    dynamic_cast<Node*>(getParent()->getParents().front())->getToWorld(m);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(l.getPosition (), pos);
    m.mult    (l.getDirection(), dir);

    l.setValue(pos, dir);
    //ia->scale(dir.length());

    //Intersect the Line with the UIRectangle quad
    Real32 t;
    if(!intersectLineRect(l,getParent()->getPoint(),
                          getParent()->getPoint() + Vec3f(getParent()->getWidth(),0,0),
                          getParent()->getPoint() + Vec3f(getParent()->getWidth(),getParent()->getHeight(),0),
                          getParent()->getPoint() + Vec3f(0,getParent()->getHeight(),0)
                          ,t))
    {
        return false;
    }

    //Return the point on the quad of the intersection if there was one
    Result.setValues(l.getPosition().x() + t*l.getDirection().x() - getParent()->getPoint().x(), 
                     getParent()->getHeight() - l.getPosition().y() - t*l.getDirection().y() + getParent()->getPoint().y());
    return true;
}

bool UIRectangleMouseTransformFunctor::renderingSurfaceToViewport(const Pnt2f& RenderingSurfacePoint,
                                                                  const Viewport* TheViewport,
                                                                  Pnt2f& Result) const
{
    Result = RenderingSurfacePoint;
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIRectangleMouseTransformFunctor::UIRectangleMouseTransformFunctor(void) :
    Inherited()
{
}

UIRectangleMouseTransformFunctor::UIRectangleMouseTransformFunctor(const UIRectangleMouseTransformFunctor &source) :
    Inherited(source)
{
}

UIRectangleMouseTransformFunctor::~UIRectangleMouseTransformFunctor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIRectangleMouseTransformFunctor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void UIRectangleMouseTransformFunctor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIRectangleMouseTransformFunctor NI" << std::endl;
}

OSG_END_NAMESPACE
