#include "OSGUIDrawUtils.h"
#include "OSGUIDefines.h"

#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Misc/OSGRotatedComponent.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "UIDrawingSurface/OSGUIDrawingSurfaceMouseTransformFunctor.h"
#include "Graphics/UIDrawObjects/OSGUIDrawObject.h"

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

void componentQuadIntersection(const ComponentPtr c1,
                                const ComponentPtr c2,
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

bool isContainedClipBounds(const Pnt2f& Point, const ComponentPtr Comp)
{
	Pnt2f CompTopLeft,CompBottomRight;

	Comp->getClipBounds(CompTopLeft, CompBottomRight);

	//Point is in screen coordinates
	//Convert it into component coordinates
	return isContainedBounds(DrawingSurfaceToComponent(Point,Comp), CompTopLeft, CompBottomRight);
}

Pnt2f ViewportToDrawingSurface(const Pnt2f& ViewportPoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport)
{
    //Get Window to Drawing Surface
    Pnt2f DrawingSurfacePoint;
    DrawingSurface->getMouseTransformFunctor()->viewportToRenderingSurface(ViewportPoint,TheViewport,DrawingSurfacePoint);

    //Then get DrawingSurface to component
    return DrawingSurfacePoint;
}

Pnt2f DrawingSurfaceToViewport(const Pnt2f& DrawingSurfacePoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport)
{
    //TODO:Implement
    return Pnt2f(0,0);
}

Pnt2f ViewportToComponent(const Pnt2f& ViewportPoint, const ComponentPtr Comp, const ViewportPtr TheViewport)
{
    //Then get Viewport to component
    return DrawingSurfaceToComponent(ViewportToDrawingSurface(ViewportPoint, Comp->getParentWindow()->getDrawingSurface(), TheViewport), Comp);
}

Pnt2f ComponentToViewport(const Pnt2f& ComponentPoint, const ComponentPtr Comp, const ViewportPtr TheViewport)
{
    return DrawingSurfaceToViewport(ComponentToDrawingSurface(ComponentPoint, Comp), Comp->getParentWindow()->getDrawingSurface(), TheViewport);
}

Pnt2f DrawingSurfaceToComponent(const Pnt2f& DrawingSurfacePoint, const ComponentPtr Comp)
{
    std::deque<ComponentPtr> PathToComponent;
	Pnt2f Result(DrawingSurfacePoint);
	ComponentPtr CompRecurse = Comp;
	while(CompRecurse != NullFC)
	{
		PathToComponent.push_front(CompRecurse);
		CompRecurse = CompRecurse->getParentContainer();
	}

    bool WasPrevComponentRotated(false);
	for(UInt32 i(0) ; i<PathToComponent.size() ; ++i)
	{
        if(WasPrevComponentRotated)
        {
	        WasPrevComponentRotated = false;
		    Result = RotatedComponent::Ptr::dcast(PathToComponent[i-1])->getLocalToInternalComponent(Result);
        }
	    if(PathToComponent[i]->getType() == RotatedComponent::getClassType())
	    {
	        WasPrevComponentRotated = true;
		    Result -= Vec2f(PathToComponent[i]->getPosition());
	    }
	    else
	    {
		    Result -= Vec2f(PathToComponent[i]->getPosition());
		}
	}

	return Result;
}

Pnt2f ComponentToDrawingSurface(const Pnt2f& ComponentPoint, const ComponentPtr Comp)
{
	Pnt2f Result(ComponentPoint);
	ComponentPtr CompRecurse = Comp;
	while(CompRecurse != NullFC)
	{
		Result += Vec2f(CompRecurse->getPosition());
		CompRecurse = CompRecurse->getParentContainer();
	}
	return Result;
}

Pnt2f ComponentToFrame(const Pnt2f& ComponentPoint, const ComponentPtr Comp)
{
	Pnt2f Result(ComponentPoint);
	ComponentPtr CompRecurse = Comp;
	while(CompRecurse != NullFC &&
          CompRecurse != Comp->getParentWindow())
	{
		Result += Vec2f(CompRecurse->getPosition());
		CompRecurse = CompRecurse->getParentContainer();
	}
	return Result;
}

Pnt2f Rotate(const Pnt2f& Point, const Real32& Angle)
{
    return Pnt2f(Point.x()*osgcos(Angle) - Point.y()*osgsin(Angle), Point.x()*osgsin(Angle) + Point.y()*osgcos(Angle));
}


void getDrawObjectBounds(MFUIDrawObjectPtr DrawObjects, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
	if(DrawObjects.size() > 0)
	{
		Pnt2f TempTopLeft, TempBottomRight;
		DrawObjects.getValue(0)->getBounds(TopLeft, BottomRight);
		//Determine Top Left And Bottom Right
		for(UInt32 i(0) ; i<DrawObjects.size(); ++i)
		{
			DrawObjects.getValue(i)->getBounds(TempTopLeft, TempBottomRight);
		    TopLeft.setValues( osgMin(TopLeft.x(), TempTopLeft.x()),
				               osgMin(TopLeft.y(), TempTopLeft.y()) );

		    BottomRight.setValues(osgMax<UInt16>(BottomRight.x(), TempBottomRight.x()),
		                          osgMax<UInt16>(BottomRight.y(), TempBottomRight.y()) );
		}
	}
}


OSG_END_NAMESPACE
