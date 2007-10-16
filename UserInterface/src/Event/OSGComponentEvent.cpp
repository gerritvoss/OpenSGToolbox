#include "OSGComponentEvent.h"

OSG_BEGIN_NAMESPACE

EventType ComponentEvent::_Type("ComponentEvent", "EventType");

const EventType &ComponentEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
