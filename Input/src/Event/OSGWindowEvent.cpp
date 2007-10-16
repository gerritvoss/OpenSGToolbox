#include "OSGWindowEvent.h"

OSG_BEGIN_NAMESPACE

EventType WindowEvent::_Type("WindowEvent", "EventType");

const EventType &WindowEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
