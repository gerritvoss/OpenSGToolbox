#include "OSGUndoableEditEvent.h"

OSG_BEGIN_NAMESPACE

EventType UndoableEditEvent::_Type("UndoableEditEvent", "EventType");

const EventType &UndoableEditEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
