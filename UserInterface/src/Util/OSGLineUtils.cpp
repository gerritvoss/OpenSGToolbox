#include "OSGLineUtils.h"


OSG_BEGIN_NAMESPACE

bool intersectLineRect ( const Line& l,
		 const Pnt3f & RectPoint1,
		const Pnt3f & RectPoint2,
		const Pnt3f & RectPoint3,
		const Pnt3f & RectPoint4,
		Real32 &t
	)
{
	// Eps (1E-6f) didn't work with very small geometries!
    static const Real32 sEps = 1E-10f;

	Vec3f RectSide1(RectPoint2-RectPoint1);
	Vec3f RectSide2(RectPoint4-RectPoint1);
	Vec3f n = RectSide1.cross(RectSide2);
	
	Vec3f w(RectPoint1-l.getPosition());

	t = -(-n.dot(w)) / (n.dot(l.getDirection()));

    return true;
}

OSG_END_NAMESPACE