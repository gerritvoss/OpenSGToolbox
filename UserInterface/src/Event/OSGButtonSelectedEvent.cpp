#include "OSGButtonSelectedEvent.h"

OSG_BEGIN_NAMESPACE

EventType ButtonSelectedEvent::_Type("ButtonSelectedEvent", "EventType");

const EventType &ButtonSelectedEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
