#include "OSGKeyAcceleratorEvent.h"

OSG_BEGIN_NAMESPACE

EventType KeyAcceleratorEvent::_Type("KeyAcceleratorEvent", "EventType");

const EventType &KeyAcceleratorEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
