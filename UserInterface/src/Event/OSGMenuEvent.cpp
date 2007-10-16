#include "OSGMenuEvent.h"

OSG_BEGIN_NAMESPACE

EventType MenuEvent::_Type("MenuEvent", "EventType");

const EventType &MenuEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
