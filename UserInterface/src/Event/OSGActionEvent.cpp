#include "OSGActionEvent.h"

OSG_BEGIN_NAMESPACE

EventType ActionEvent::_Type("ActionEvent", "EventType");

const EventType &ActionEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
