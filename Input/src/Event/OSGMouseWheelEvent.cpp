#include "OSGMouseWheelEvent.h"

OSG_BEGIN_NAMESPACE

EventType MouseWheelEvent::_Type("MouseWheelEvent", "EventType");

const EventType &MouseWheelEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
