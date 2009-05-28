#include "OSGDialogEvent.h"

OSG_BEGIN_NAMESPACE

EventType DialogEvent::_Type("DialogEvent", "EventType");

const EventType &DialogEvent::getType(void) const
{
    return _Type;
}

DialogEvent::DialogEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
