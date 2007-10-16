#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &TextEvent::getClassType(void)
{
    return _Type;
}

inline
TextEvent::EventEnum TextEvent::getEvent(void) const
{
    return _Event;
}

inline
TextEvent:: TextEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent) :
   Event(Source, TimeStamp),
       _Event(TheEvent)
{
}

OSG_END_NAMESPACE
