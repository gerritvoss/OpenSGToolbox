#include "OSGMouseWheelEvent.h"

OSG_BEGIN_NAMESPACE

EventType MouseWheelEvent::_Type("MouseWheelEvent", "InputEvent");

const EventType &MouseWheelEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
