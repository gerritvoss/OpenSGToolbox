#include "OSGTextEvent.h"

OSG_BEGIN_NAMESPACE

EventType TextEvent::_Type("TextEvent", "EventType");

const EventType &TextEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
