#include "OSGCommandEvent.h"

OSG_BEGIN_NAMESPACE

EventType CommandEvent::_Type("CommandEvent", "EventType");

const EventType &CommandEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
