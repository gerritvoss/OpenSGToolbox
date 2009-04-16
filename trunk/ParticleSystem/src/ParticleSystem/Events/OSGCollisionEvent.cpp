#include "OSGCollisionEvent.h"

OSG_BEGIN_NAMESPACE

EventType CollisionEvent::_Type("CollisionEvent", "EventType");

const EventType &CollisionEvent::getType(void) const
{
    return _Type;
}


CollisionEvent::CollisionEvent(FieldContainerPtr Source, Time TimeStamp,
	   Real32 HitT,
	   NodePtr HitNode,
	   Int32 HitPoly,
	   Vec3f HitNormal,
	   Pnt3f HitPoint) :
   Event(Source, TimeStamp),
   _HitT(HitT),
   _HitNode(HitNode),
   _HitPoly(HitPoly),
   _HitNormal(HitNormal),
   _HitPoint(HitPoint)
{
}

OSG_END_NAMESPACE
