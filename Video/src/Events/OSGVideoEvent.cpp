#include "OSGVideoEvent.h"
#include "OSGVideoWrapper.h"

OSG_BEGIN_NAMESPACE

EventType VideoEvent::_Type("VideoEvent", "EventType");

const EventType &VideoEvent::getType(void) const
{
    return _Type;
}

VideoEvent::VideoEvent(FieldContainerPtr Source, Time TimeStamp, VideoWrapperPtr SourceVideo) :
   Event(Source, TimeStamp),
   _SourceVideo(SourceVideo)
{
}
OSG_END_NAMESPACE
