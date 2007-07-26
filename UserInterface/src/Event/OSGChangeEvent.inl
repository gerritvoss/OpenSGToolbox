#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ChangeEvent::EventType ChangeEvent::getEvent(void) const
{
    return _Event;
}

inline
ChangeEvent:: ChangeEvent(FieldContainerPtr Source, Time TimeStamp, EventType TheEvent) :
   Event(Source, TimeStamp),
       _Event(TheEvent)
{
}

OSG_END_NAMESPACE
