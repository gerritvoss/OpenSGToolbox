#include "OSGPopupMenuEvent.h"

OSG_BEGIN_NAMESPACE

EventType PopupMenuEvent::_Type("PopupMenuEvent", "EventType");

const EventType &PopupMenuEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
