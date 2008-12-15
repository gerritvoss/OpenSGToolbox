#include "OSGMiniMapEvent.h"

OSG_BEGIN_NAMESPACE

EventType MiniMapEvent::_Type("MiniMapEvent", "EventType");

const EventType &MiniMapEvent::getType(void) const
{
    return _Type;
}

MiniMapEvent::MiniMapEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
