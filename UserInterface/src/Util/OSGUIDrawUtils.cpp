#include "OSGUIDrawUtils.h"

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

OSG_END_NAMESPACE
