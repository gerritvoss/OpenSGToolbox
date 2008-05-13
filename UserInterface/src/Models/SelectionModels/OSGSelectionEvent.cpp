#include "OSGSelectionEvent.h"

OSG_BEGIN_NAMESPACE

EventType SelectionEvent::_Type("SelectionEvent", "EventType");

const EventType &SelectionEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
