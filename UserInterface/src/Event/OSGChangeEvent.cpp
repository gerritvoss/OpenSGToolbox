#include "OSGChangeEvent.h"

OSG_BEGIN_NAMESPACE

EventType ChangeEvent::_Type("ChangeEvent", "EventType");

const EventType &ChangeEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
