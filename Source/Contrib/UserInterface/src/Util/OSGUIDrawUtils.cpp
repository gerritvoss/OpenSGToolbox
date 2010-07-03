/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include "OSGUIDrawUtils.h"

#include "OSGInternalWindow.h"
#include "OSGRotatedComponent.h"
#include "OSGUIDrawingSurface.h"
#include "OSGComponent.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"
#include "OSGUIDrawObject.h"

#include <deque>

OSG_BEGIN_NAMESPACE

Pnt2f calculateAlignment(const Pnt2f& Position1, const Vec2f& Size1, const Vec2f& Size2, const Real32& VAlign, const Real32& HAlign)
{
	Pnt2f AlignedPosition;

	AlignedPosition[0] = Position1[0]+HAlign*(Size1[0]-Size2[0]);
	AlignedPosition[1] = Position1[1]+VAlign*(Size1[1]-Size2[1]);
	
	return AlignedPosition;
}

void quadIntersection(const Pnt2f& Quad1TopLeft, const Pnt2f& Quad1BottomRight,
                      const Pnt2f& Quad2TopLeft, const Pnt2f& Quad2BottomRight,
                      Pnt2f& ResultQuadTopLeft, Pnt2f& ResultQuadBottomRight)
{
    ResultQuadTopLeft[0] = osgMax(Quad1TopLeft[0],Quad2TopLeft[0]);
    ResultQuadTopLeft[1] = osgMax(Quad1TopLeft[1],Quad2TopLeft[1]);
    
    ResultQuadBottomRight[0] = osgMin(Quad1BottomRight[0],Quad2BottomRight[0]);
    ResultQuadBottomRight[1] = osgMin(Quad1BottomRight[1],Quad2BottomRight[1]);
}

void componentQuadIntersection(const Component* c1,
                                const Component* c2,
                                Pnt2f& ResultQuadTopLeft, Pnt2f& ResultQuadBottomRight)
{
    Pnt2f Quad1TopLeft,Quad2TopLeft;
    Pnt2f Quad1BottomRight,Quad2BottomRight;

    c1->getBoundsRenderingSurfaceSpace(Quad1TopLeft,Quad1BottomRight);
    c2->getBoundsRenderingSurfaceSpace(Quad2TopLeft,Quad2BottomRight);

    quadIntersection(Quad1TopLeft,Quad1BottomRight,
                     Quad2TopLeft,Quad2BottomRight,
                     ResultQuadTopLeft,ResultQuadBottomRight);
}

bool isContainedBounds(const Pnt2f& Point, const Pnt2f& TopLeft, const Pnt2f& BottomRight)
{
    return (Point.x() >= TopLeft.x()) &&
        (Point.x() <= BottomRight.x()) &&
        (Point.y() >= TopLeft.y()) &&
        (Point.y() <= BottomRight.y());
}

bool isContainedClipBounds(const Pnt2f& Point, const Component* Comp)
{
    Pnt2f CompTopLeft,CompBottomRight;

    Comp->getClipBounds(CompTopLeft, CompBottomRight);

    //Point is in screen coordinates
    //Convert it into component coordinates
    return isContainedBounds(DrawingSurfaceToComponent(Point,Comp), CompTopLeft, CompBottomRight);
}

Pnt2f ViewportToDrawingSurface(const Pnt2f& ViewportPoint, 
                               const UIDrawingSurface* DrawingSurface,
                               const Viewport* TheViewport)
{
    //Get Window to Drawing Surface
    Pnt2f DrawingSurfacePoint;
    DrawingSurface->getMouseTransformFunctor()->viewportToRenderingSurface(ViewportPoint,TheViewport,DrawingSurfacePoint);

    //Then get DrawingSurface to component
    return DrawingSurfacePoint;
}

Pnt2f DrawingSurfaceToViewport(const Pnt2f& DrawingSurfacePoint,
                               const UIDrawingSurface* DrawingSurface,
                               const Viewport* TheViewport)
{
    //Get Window to Drawing Surface
    Pnt2f ViewportPoint;
    DrawingSurface->getMouseTransformFunctor()->renderingSurfaceToViewport(DrawingSurfacePoint, TheViewport, ViewportPoint);

    //Then get DrawingSurface to component
    return ViewportPoint;
}

Pnt2f ViewportToComponent(const Pnt2f& ViewportPoint, const Component* Comp, const Viewport* TheViewport)
{
    //Then get Viewport to component
    return DrawingSurfaceToComponent(ViewportToDrawingSurface(ViewportPoint, Comp->getParentWindow()->getParentDrawingSurface(), TheViewport), Comp);
}

Pnt2f ViewportToWindow(const Pnt2f& ViewportPoint, const Viewport* TheViewport)
{
    return Pnt2f(ViewportPoint.x() + TheViewport->getPixelLeft(), (TheViewport->getPixelTop() - TheViewport->getPixelBottom()) - ViewportPoint.y());
}

Pnt2f ComponentToViewport(const Pnt2f& ComponentPoint, const Component* Comp, const Viewport* TheViewport)
{
    return DrawingSurfaceToViewport(ComponentToDrawingSurface(ComponentPoint, Comp), Comp->getParentWindow()->getParentDrawingSurface(), TheViewport);
}

Pnt2f ComponentToWindow(const Pnt2f& ComponentPoint, const Component* Comp, const Viewport* TheViewport)
{
    return ViewportToWindow(ComponentToViewport(ComponentPoint, Comp, TheViewport), TheViewport);
}

Pnt2f DrawingSurfaceToComponent(const Pnt2f& DrawingSurfacePoint, const Component* Comp)
{
    std::deque<const Component*> PathToComponent;
    Pnt2f Result(DrawingSurfacePoint);
    const Component* CompRecurse = Comp;
    while(CompRecurse != NULL)
    {
        PathToComponent.push_front(CompRecurse);
        CompRecurse = CompRecurse->getParentContainer();
    }

    //bool WasPrevComponentRotated(false);
    for(UInt32 i(0) ; i<PathToComponent.size() ; ++i)
    {
        Result = PathToComponent[i]->getParentToLocal(Result);
        /*if(WasPrevComponentRotated)
        {
            WasPrevComponentRotated = false;
            Result = dynamic_pointer_cast<RotatedComponent>(PathToComponent[i-1])->getLocalToInternalComponent(Result);
        }
        if(PathToComponent[i]->getType() == RotatedComponent::getClassType())
        {
            WasPrevComponentRotated = true;
            Result -= Vec2f(PathToComponent[i]->getPosition());
        }
        else
        {
            Result -= Vec2f(PathToComponent[i]->getPosition());
        }*/
    }

    return Result;
}

Pnt2f ComponentToDrawingSurface(const Pnt2f& ComponentPoint, const Component* Comp)
{
    Pnt2f Result(ComponentPoint);
    const Component* CompRecurse = Comp;
    while(CompRecurse != NULL)
    {
        Result += Vec2f(CompRecurse->getPosition());
        CompRecurse = CompRecurse->getParentContainer();
    }
    return Result;
}

Pnt2f ComponentToComponent(const Pnt2f& ComponentPoint, const Component* Comp, const Component* ParentComp)
{
    Pnt2f Result(ComponentPoint);
    const Component* CompRecurse = Comp;
    while(CompRecurse != NULL &&
          CompRecurse != ParentComp)
    {
        Result = CompRecurse->getLocalToParent(Result);
        CompRecurse = CompRecurse->getParentContainer();
    }
    return Result;
}

Pnt2f ComponentToFrame(const Pnt2f& ComponentPoint, const Component* Comp)
{
    Pnt2f Result(ComponentPoint);
    const Component* CompRecurse = Comp;
    while(CompRecurse != NULL &&
          CompRecurse != Comp->getParentWindow())
    {
        Result = CompRecurse->getLocalToParent(Result);
        CompRecurse = CompRecurse->getParentContainer();
    }
    return Result;
}

Pnt2f Rotate(const Pnt2f& Point, const Real32& Angle)
{
    return Pnt2f(Point.x()*osgCos(Angle) - Point.y()*osgSin(Angle), Point.x()*osgSin(Angle) + Point.y()*osgCos(Angle));
}


void getDrawObjectBounds(const MFUnrecUIDrawObjectPtr& DrawObjects, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    if(DrawObjects.size() > 0)
    {
        Pnt2f TempTopLeft, TempBottomRight;
        DrawObjects[0]->getBounds(TopLeft, BottomRight);
        //Determine Top Left And Bottom Right
        for(UInt32 i(0) ; i<DrawObjects.size(); ++i)
        {
            DrawObjects[i]->getBounds(TempTopLeft, TempBottomRight);
            TopLeft.setValues( osgMin(TopLeft.x(), TempTopLeft.x()),
                               osgMin(TopLeft.y(), TempTopLeft.y()) );

            BottomRight.setValues(osgMax<UInt16>(BottomRight.x(), TempBottomRight.x()),
                                  osgMax<UInt16>(BottomRight.y(), TempBottomRight.y()) );
        }
    }
}


OSG_END_NAMESPACE
