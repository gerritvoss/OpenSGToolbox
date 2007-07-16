#include "OSGUIDrawUtils.h"
#include "OSGUIDefines.h"

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

Pnt2s OSG_USERINTERFACELIB_DLLMAPPING calculateAlignment(const Pnt2s& Position1, const Vec2s& Size1, const Vec2s& Size2, const UInt32& VAlign, const UInt32& HAlign)
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
}

OSG_END_NAMESPACE
