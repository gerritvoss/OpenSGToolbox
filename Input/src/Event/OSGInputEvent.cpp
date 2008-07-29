#include "OSGInputEvent.h"

OSG_BEGIN_NAMESPACE

EventType InputEvent::_Type("InputEvent", "EventType");

const EventType &InputEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
