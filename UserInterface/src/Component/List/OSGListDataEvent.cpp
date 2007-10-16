#include "OSGListDataEvent.h"

OSG_BEGIN_NAMESPACE

EventType ListDataEvent::_Type("ListDataEvent", "EventType");

const EventType &ListDataEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
