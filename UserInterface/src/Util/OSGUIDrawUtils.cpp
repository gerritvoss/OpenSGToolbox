#include "OSGUIDrawUtils.h"
#include "OSGUIDefines.h"

#include "Component/Container/OSGFrame.h"
#include "Component/OSGRotatedComponent.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "UIDrawingSurface/OSGUIDrawingSurfaceMouseTransformFunctor.h"

#include <deque>

OSG_BEGIN_NAMESPACE

void convertTopLeftToCenteredLine(const Pnt2s& Point1, const Pnt2s& Point2, const UInt16 Width,Pnt2s& ResultPoint1, Pnt2s& ResultPoint2)
{
   Vec3s DirOffset = (Pnt3s(Point1.x(),Point1.y(),0) - Pnt3s(Point2.x(),Point2.y(),0)).cross(Vec3s(0,0,-1));
   DirOffset.normalize();
   DirOffset *= Width/2;

   ResultPoint1 = Point1 + Vec2s(DirOffset.x(),DirOffset.y());
   ResultPoint2 = Point2 + Vec2s(DirOffset.x(),DirOffset.y());
}

void convertTopRightToCenteredLine(const Pnt2s& Point1, const Pnt2s& Point2, const UInt16 Width,Pnt2s& ResultPoint1, Pnt2s& ResultPoint2)
{
   Vec3s DirOffset = (Pnt3s(Point1.x(),Point1.y(),0) - Pnt3s(Point2.x(),Point2.y(),0)).cross(Vec3s(0,0,1));
   DirOffset.normalize();
   DirOffset *= Width/2;

   ResultPoint1 = Point1 + Vec2s(DirOffset.x(),DirOffset.y());
   ResultPoint2 = Point2 + Vec2s(DirOffset.x(),DirOffset.y());
}

Pnt2s calculateAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const Real32& VAlign, const Real32& HAlign)
{
	Pnt2s AlignedPosition;

	AlignedPosition[0] = Position1[0]+HAlign*(Size1[0]-Size2[0]);
	AlignedPosition[1] = Position1[1]+VAlign*(Size1[1]-Size2[1]);
	
	return AlignedPosition;
}

/*Pnt2s calculateAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const UInt32& VAlign, const UInt32& HAlign)
{
	Pnt2s AlignedPosition;

	switch(VAlign)
	{
	case VERTICAL_TOP:
	 //VerticalTop
	 AlignedPosition[1] = Position1[1];
	  break;
	case VERTICAL_BOTTOM:
	 //VerticalBottom
	 AlignedPosition[1] = Position1[1]+Size1[1]-Size2[1];
	  break;
	case VERTICAL_CENTER:
	 //VerticalCenter
	 AlignedPosition[1] = Position1[1]+0.5*(Size1[1]-Size2[1]);
	  break;
	default:
	  break;
	}

	switch(HAlign)
	{
	case HORIZONTAL_LEFT:
	 //HorizontalLeft
	 AlignedPosition[0] = Position1[0];
	  break;
	case HORIZONTAL_RIGHT:
	 //HorizontalRight
	 AlignedPosition[0] = Position1[0]+Size1[0]-Size2[0];
	  break;
	case HORIZONTAL_CENTER:
	 //HorizontalCenter
	 AlignedPosition[0] = Position1[0]+0.5*(Size1[0]-Size2[0]);
	  break;
	default:
	  break;
	}

	return AlignedPosition;
}*/

void quadIntersection(const Pnt2s& Quad1TopLeft, const Pnt2s& Quad1BottomRight,
                      const Pnt2s& Quad2TopLeft, const Pnt2s& Quad2BottomRight,
                      Pnt2s& ResultQuadTopLeft, Pnt2s& ResultQuadBottomRight)
{
    ResultQuadTopLeft[0] = osgMax(Quad1TopLeft[0],Quad2TopLeft[0]);
    ResultQuadTopLeft[1] = osgMax(Quad1TopLeft[1],Quad2TopLeft[1]);
    
    ResultQuadBottomRight[0] = osgMin(Quad1BottomRight[0],Quad2BottomRight[0]);
    ResultQuadBottomRight[1] = osgMin(Quad1BottomRight[1],Quad2BottomRight[1]);
}

void componentQuadIntersection(const ComponentPtr c1,
                                const ComponentPtr c2,
                                Pnt2s& ResultQuadTopLeft, Pnt2s& ResultQuadBottomRight)
{
    Pnt2s Quad1TopLeft,Quad2TopLeft;
    Pnt2s Quad1BottomRight,Quad2BottomRight;

    c1->getBoundsRenderingSurfaceSpace(Quad1TopLeft,Quad1BottomRight);
    c2->getBoundsRenderingSurfaceSpace(Quad2TopLeft,Quad2BottomRight);

    quadIntersection(Quad1TopLeft,Quad1BottomRight,
                     Quad2TopLeft,Quad2BottomRight,
                     ResultQuadTopLeft,ResultQuadBottomRight);
}

bool isContainedBounds(const Pnt2s& Point, const Pnt2s& TopLeft, const Pnt2s& BottomRight)
{
	return (Point.x() >= TopLeft.x()) &&
		(Point.x() <= BottomRight.x()) &&
		(Point.y() >= TopLeft.y()) &&
		(Point.y() <= BottomRight.y());
}

bool isContainedClipBounds(const Pnt2s& Point, const ComponentPtr Comp)
{
	Pnt2s CompTopLeft,CompBottomRight;

	Comp->getClipBounds(CompTopLeft, CompBottomRight);

	//Point is in screen coordinates
	//Convert it into component coordinates
	return isContainedBounds(DrawingSurfaceToComponent(Point,Comp), CompTopLeft, CompBottomRight);
}

Pnt2s ViewportToDrawingSurface(const Pnt2s& ViewportPoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport)
{
    //Get Window to Drawing Surface
    Pnt2s DrawingSurfacePoint;
    DrawingSurface->getMouseTransformFunctor()->viewportToRenderingSurface(ViewportPoint,TheViewport,DrawingSurfacePoint);

    //Then get DrawingSurface to component
    return DrawingSurfacePoint;
}

Pnt2s DrawingSurfaceToViewport(const Pnt2s& DrawingSurfacePoint, const UIDrawingSurfacePtr DrawingSurface, const ViewportPtr TheViewport)
{
    //TODO:Implement
    return Pnt2s(0,0);
}

Pnt2s ViewportToComponent(const Pnt2s& ViewportPoint, const ComponentPtr Comp, const ViewportPtr TheViewport)
{
    //Then get Viewport to component
    return DrawingSurfaceToComponent(ViewportToDrawingSurface(ViewportPoint, Comp->getParentFrame()->getDrawingSurface(), TheViewport), Comp);
}

Pnt2s ComponentToViewport(const Pnt2s& ComponentPoint, const ComponentPtr Comp, const ViewportPtr TheViewport)
{
    return DrawingSurfaceToViewport(ComponentToDrawingSurface(ComponentPoint, Comp), Comp->getParentFrame()->getDrawingSurface(), TheViewport);
}

Pnt2s DrawingSurfaceToComponent(const Pnt2s& DrawingSurfacePoint, const ComponentPtr Comp)
{
    std::deque<ComponentPtr> PathToComponent;
	Pnt2s Result(DrawingSurfacePoint);
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
		    Result -= Vec2s(PathToComponent[i]->getPosition());
	    }
	    else
	    {
		    Result -= Vec2s(PathToComponent[i]->getPosition());
		}
	}

	return Result;
}

Pnt2s ComponentToDrawingSurface(const Pnt2s& ComponentPoint, const ComponentPtr Comp)
{
	Pnt2s Result(ComponentPoint);
	ComponentPtr CompRecurse = Comp;
	while(CompRecurse != NullFC)
	{
		Result += Vec2s(CompRecurse->getPosition());
		CompRecurse = CompRecurse->getParentContainer();
	}
	return Result;
}

Pnt2s ComponentToFrame(const Pnt2s& ComponentPoint, const ComponentPtr Comp)
{
	Pnt2s Result(ComponentPoint);
	ComponentPtr CompRecurse = Comp;
	while(CompRecurse != NullFC &&
          CompRecurse != Comp->getParentFrame())
	{
		Result += Vec2s(CompRecurse->getPosition());
		CompRecurse = CompRecurse->getParentContainer();
	}
	return Result;
}

Pnt2s OSG_USERINTERFACELIB_DLLMAPPING Rotate(const Pnt2s& Point, const Real32& Angle)
{
    return Pnt2s(Point.x()*osgcos(Angle) - Point.y()*osgsin(Angle), Point.x()*osgsin(Angle) + Point.y()*osgcos(Angle));
}


OSG_END_NAMESPACE
