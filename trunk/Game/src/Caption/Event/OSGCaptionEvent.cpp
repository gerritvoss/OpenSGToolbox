#include "OSGCaptionEvent.h"

OSG_BEGIN_NAMESPACE

EventType CaptionEvent::_Type("CaptionEvent", "EventType");

const EventType &CaptionEvent::getType(void) const
{
    return _Type;
}

CaptionEvent::CaptionEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
