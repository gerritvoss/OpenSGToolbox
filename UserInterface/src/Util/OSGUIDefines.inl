#include <OpenSG/OSGConfig.h>


OSG_BEGIN_NAMESPACE

inline
bool isContainedBounds(const Pnt2s& Point, const ComponentPtr Comp)
{
	Pnt2s CompTopLeft,CompBottomRight;

	Comp->getBounds(CompTopLeft, CompBottomRight);

	return isContainedBounds(Point, CompTopLeft, CompBottomRight);
}

OSG_END_NAMESPACE
