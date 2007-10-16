#include "OSGUpdateEvent.h"

OSG_BEGIN_NAMESPACE

EventType UpdateEvent::_Type("UpdateEvent", "EventType");

const EventType &UpdateEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
