#include "OSGListSelectionEvent.h"

OSG_BEGIN_NAMESPACE

EventType ListSelectionEvent::_Type("ListSelectionEvent", "EventType");

const EventType &ListSelectionEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
