#include "OSGTableModelEvent.h"

OSG_BEGIN_NAMESPACE

EventType TableModelEvent::_Type("TableModelEvent", "EventType");

const EventType &TableModelEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
