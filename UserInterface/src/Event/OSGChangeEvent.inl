#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &ChangeEvent::getClassType(void)
{
    return _Type;
}

inline
ChangeEvent::EventEnum ChangeEvent::getEvent(void) const
{
    return _Event;
}

inline
ChangeEvent:: ChangeEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent) :
   Event(Source, TimeStamp),
       _Event(TheEvent)
{
}

OSG_END_NAMESPACE
