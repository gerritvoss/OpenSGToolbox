#include "OSGTableColumnModelEvent.h"

OSG_BEGIN_NAMESPACE

EventType TableColumnModelEvent::_Type("TableColumnModelEvent", "EventType");

const EventType &TableColumnModelEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
