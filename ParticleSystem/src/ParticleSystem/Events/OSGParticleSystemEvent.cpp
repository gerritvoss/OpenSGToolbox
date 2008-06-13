#include "OSGParticleSystemEvent.h"

OSG_BEGIN_NAMESPACE

EventType ParticleSystemEvent::_Type("ParticleSystemEvent", "EventType");

const EventType &ParticleSystemEvent::getType(void) const
{
    return _Type;
}

ParticleSystemEvent::ParticleSystemEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
