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

#include "OSGPolygonBorder.h"
#include "OSGMathUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPolygonBorderBase.cpp file.
// To modify it, please change the .fcd file (OSGPolygonBorder.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PolygonBorder::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PolygonBorder::draw(Graphics* const g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{
    if(Clipping)
    {
        deactivateInternalDrawConstraints(g,x,y,Width,Height);
    }
    if(getWidth() > 0.0)
    {
        Int32 NumVertices(getMFVertices()->size());
        Pnt2f p1,
              p2;
        Pnt2f pi1,pi2;
        Real32 t1,t2;

        Vec2f Scale(Width,Height);
        Vec2f ThisEdge, NextEdge, ThisEdgeOffset, NextEdgeOffset;
        glBegin(GL_QUAD_STRIP);
        for(Int32 i(0) ; i<=NumVertices ; ++i)
        {
            //ThisEdge
            if(i == 0)
            {
                ThisEdge=getVertices((i+1)%NumVertices)-getVertices(i%NumVertices);
                scaleUp(ThisEdge, Scale);


                ThisEdgeOffset.setValues(-ThisEdge.y(), ThisEdge.x());
                ThisEdgeOffset.normalize();
                ThisEdgeOffset *= getWidth();
            }
            else
            {
                ThisEdge = NextEdge;
                ThisEdgeOffset = NextEdgeOffset;
            }

            //Next Edge
            NextEdge=getVertices((i+2)%NumVertices)-getVertices((i+1)%NumVertices);
            scaleUp(NextEdge, Scale);

            //Next Edge Offset
            NextEdgeOffset.setValues(-NextEdge.y(), NextEdge.x());
            NextEdgeOffset.normalize();
            NextEdgeOffset *= getWidth();

            p2 = getVertices((i+1)%NumVertices);
            scaleUp(p2, Scale);


            //Find the intersecting point of the Offset Edges
            pi1 = p2+ThisEdgeOffset;
            pi2 = p2+NextEdgeOffset;
            if(intersectLines(pi1,ThisEdge,pi2,NextEdge,t1,t2,p1) == -1)
            {
                //The edges are coincident
                //Use pi1
                p1 = pi1;
            }


            glVertex2fv(p1.getValues());
            glVertex2fv(p2.getValues());
        }
        glEnd();
    }
}

void PolygonBorder::scaleUp(Pnt2f& TheVector, const Vec2f& Scale) const
{
    TheVector[0] = TheVector[0] *Scale[0];
    TheVector[1] = TheVector[1] *Scale[1];
}
void PolygonBorder::scaleUp(Vec2f& TheVector, const Vec2f& Scale) const
{
    TheVector[0] = TheVector[0] *Scale[0];
    TheVector[1] = TheVector[1] *Scale[1];
}

void PolygonBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
    //TODO:Implement
    Left=Right=Top=Bottom = getWidth(); //wrong, but what else are you supposed to do?
}

void PolygonBorder::activateInternalDrawConstraints(Graphics* const g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    GLenum DepthTextEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    g->incrDrawBounderiesNesting();

    g->initAddDrawBounderies();

    glBegin(GL_POLYGON);
    Pnt2f p1,
          p2;
    Pnt2f pi1,pi2;
    Real32 t1,t2;

    Vec2f Scale(Width,Height);
    Vec2f ThisEdge, NextEdge, ThisEdgeOffset, NextEdgeOffset;
    UInt32 NumVertices(getMFVertices()->size());
    for(Int32 i(0) ; i<=NumVertices ; ++i)
    {
        //ThisEdge
        if(i == 0)
        {
            ThisEdge=getVertices((i+1)%NumVertices)-getVertices(i%NumVertices);
            scaleUp(ThisEdge, Scale);


            ThisEdgeOffset.setValues(-ThisEdge.y(), ThisEdge.x());
            ThisEdgeOffset.normalize();
            ThisEdgeOffset *= getWidth();
        }
        else
        {
            ThisEdge = NextEdge;
            ThisEdgeOffset = NextEdgeOffset;
        }

        //Next Edge
        NextEdge=getVertices((i+2)%NumVertices)-getVertices((i+1)%NumVertices);
        scaleUp(NextEdge, Scale);

        //Next Edge Offset
        NextEdgeOffset.setValues(-NextEdge.y(), NextEdge.x());
        NextEdgeOffset.normalize();
        NextEdgeOffset *= getWidth();

        p2 = getVertices((i+1)%NumVertices);
        scaleUp(p2, Scale);


        //Find the intersecting point of the Offset Edges
        pi1 = p2+ThisEdgeOffset;
        pi2 = p2+NextEdgeOffset;
        if(intersectLines(pi1,ThisEdge,pi2,NextEdge,t1,t2,p1) == -1)
        {
            //The edges are coincident
            //Use pi1
            p1 = pi1;
        }
        glVertex2fv(p1.getValues());
    }
    glEnd();

    g->uninitAddDrawBounderies();

    g->activateDrawBounderiesTest();

    if(DepthTextEnabled) {glEnable(GL_DEPTH_TEST);}
}

void PolygonBorder::deactivateInternalDrawConstraints(Graphics* const g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    g->decrDrawBounderiesNestring();

    g->initRemoveDrawBounderies();

    glBegin(GL_QUADS);
    glVertex2s(x-2,y-2);
    glVertex2s(x+Width+2,y-2);
    glVertex2s(x+Width+2,y+Height+2);
    glVertex2s(x-2,y+Height+2);
    glEnd();

    g->uninitRemoveDrawBounderies();

    g->deactivateDrawBounderiesTest();
}

bool PolygonBorder::isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    UInt32 NumVertices(getMFVertices()->size());
    Vec3f Edge,
          PointEdge;

    for(UInt32 i(0) ; i<NumVertices ; ++i)
    {
        Edge.setValues((getVertices((i+1)%NumVertices).x()-getVertices(i).x())*Width, (getVertices((i+1)%NumVertices).y()-getVertices(i).y())*Height, 0.0f);
        PointEdge.setValues(p.x()-getVertices(i).x()*Width, p.y()-getVertices(i).y()*Height, 0.0f);

        if(Edge.cross(PointEdge).z() < 0.0)
        {
            return false;
        }
    }
    return true;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PolygonBorder::PolygonBorder(void) :
    Inherited()
{
}

PolygonBorder::PolygonBorder(const PolygonBorder &source) :
    Inherited(source)
{
}

PolygonBorder::~PolygonBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PolygonBorder::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PolygonBorder::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PolygonBorder NI" << std::endl;
}

OSG_END_NAMESPACE
