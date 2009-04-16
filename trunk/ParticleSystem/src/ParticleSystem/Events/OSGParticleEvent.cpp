#include "OSGParticleEvent.h"

OSG_BEGIN_NAMESPACE

EventType ParticleEvent::_Type("ParticleEvent", "EventType");

const EventType &ParticleEvent::getType(void) const
{
    return _Type;
}

ParticleEvent::ParticleEvent(FieldContainerPtr Source, Time TimeStamp,
	 Int32 Index,
	 ParticleSystemPtr System,
	 const Pnt3f& Position,
     const Pnt3f& SecPosition,
	 const Vec3f& Normal,
	 const Color4f& Color,
	 const Vec3f& Size,
	 Real32 Lifespan,
	 Real32 Age,
	 const Vec3f& Velocity,
	 const Vec3f& SecVelocity,
	 const Vec3f& Acceleration,
	 UInt64 Properties) :
   Event(Source, TimeStamp),
	 _ParticleIndex(Index),
	 _System(System),
	 _ParticlePosition(Position),
     _ParticleSecPosition(SecPosition),
	 _ParticleNormal(Normal),
	 _ParticleColor(Color),
	 _ParticleSize(Size),
	 _ParticleLifespan(Lifespan),
	 _ParticleAge(Age),
	 _ParticleVelocity(Velocity),
	 _ParticleSecVelocity(SecVelocity),
	 _ParticleAcceleration(Acceleration),
	 _ParticleProperties(Properties)
{
}

OSG_END_NAMESPACE
