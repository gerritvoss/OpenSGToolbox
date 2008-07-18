#include "OSGParticleEvent.h"

OSG_BEGIN_NAMESPACE

EventType ParticleEvent::_Type("ParticleEvent", "EventType");

const EventType &ParticleEvent::getType(void) const
{
    return _Type;
}

ParticleEvent::ParticleEvent(FieldContainerPtr Source, Time TimeStamp, Pnt3f ParticlePosition) :
   Event(Source, TimeStamp),
   _ParticlePosition(ParticlePosition)
{
}

OSG_END_NAMESPACE
