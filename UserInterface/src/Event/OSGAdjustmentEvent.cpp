#include "OSGAdjustmentEvent.h"

OSG_BEGIN_NAMESPACE

EventType AdjustmentEvent::_Type("AdjustmentEvent", "EventType");

const EventType &AdjustmentEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
