#include "OSGInventoryEvent.h"

OSG_BEGIN_NAMESPACE

EventType InventoryEvent::_Type("InventoryEvent", "EventType");

const EventType &InventoryEvent::getType(void) const
{
    return _Type;
}

InventoryEvent::InventoryEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
