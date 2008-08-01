#include "OSGDragGestureEvent.h"

OSG_BEGIN_NAMESPACE

EventType DragGestureEvent::_Type("DragGestureEvent", "EventType");

const EventType &DragGestureEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
