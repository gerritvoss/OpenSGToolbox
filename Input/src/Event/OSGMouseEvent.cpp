#include "OSGMouseEvent.h"

OSG_BEGIN_NAMESPACE

EventType MouseEvent::_Type("MouseEvent", "EventType");

const EventType &MouseEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
