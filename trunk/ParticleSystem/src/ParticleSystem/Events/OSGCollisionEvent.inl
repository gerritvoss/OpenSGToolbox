#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &CollisionEvent::getClassType(void)
{
    return _Type;
}

inline
const Real32 &CollisionEvent::getHitT(void) const
{
	return _HitT;
}

inline
const NodePtr &CollisionEvent::getHitNode(void) const
{
	return _HitNode;
}

inline
const Int32 &CollisionEvent::getHitPoly(void) const
{
	return _HitPoly;
}

inline
const Vec3f &CollisionEvent::getHitNormal(void) const
{
	return _HitNormal;
}

inline
const Pnt3f &CollisionEvent::getHitPoint(void) const
{
	return _HitPoint;
}

OSG_END_NAMESPACE
