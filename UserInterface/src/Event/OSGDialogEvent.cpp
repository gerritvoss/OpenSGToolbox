#include "OSGDialogEvent.h"

OSG_BEGIN_NAMESPACE

EventType DialogEvent::_Type("DialogEvent", "EventType");

const EventType &DialogEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
