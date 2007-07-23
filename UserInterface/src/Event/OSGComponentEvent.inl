#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ComponentEvent::EventType ComponentEvent::getEvent(void) const
{
    return _Event;
}

inline
ComponentPtr ComponentEvent::getOriginator(void) const
{
    return _Originator;
}

inline
ComponentEvent::ComponentEvent(FieldContainerPtr Source, Time TimeStamp, EventType TheEvent, ComponentPtr Originator) :
   Event(Source, TimeStamp),
       _Event(TheEvent),
    _Originator(Originator)
{
}

OSG_END_NAMESPACE
