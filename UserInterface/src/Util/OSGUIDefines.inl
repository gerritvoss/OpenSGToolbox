#include <OpenSG/OSGConfig.h>


OSG_BEGIN_NAMESPACE

inline
bool isContainedBounds(const Pnt2f& Point, const ComponentPtr Comp)
{
	Pnt2f CompTopLeft,CompBottomRight;

	Comp->getBounds(CompTopLeft, CompBottomRight);

	return isContainedBounds(Point, CompTopLeft, CompBottomRight);
}

OSG_END_NAMESPACE
