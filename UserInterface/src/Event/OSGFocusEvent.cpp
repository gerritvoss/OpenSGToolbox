#include "OSGFocusEvent.h"

OSG_BEGIN_NAMESPACE

EventType FocusEvent::_Type("FocusEvent", "EventType");

const EventType &FocusEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
