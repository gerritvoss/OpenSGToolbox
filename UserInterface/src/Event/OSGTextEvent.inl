#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
TextEvent::EventType TextEvent::getEvent(void) const
{
    return _Event;
}

inline
TextEvent:: TextEvent(FieldContainerPtr Source, Time TimeStamp, EventType TheEvent) :
   Event(Source, TimeStamp),
       _Event(TheEvent)
{
}

OSG_END_NAMESPACE
