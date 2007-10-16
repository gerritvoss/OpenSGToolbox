#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &ButtonSelectedEvent::getClassType(void)
{
    return _Type;
}

inline
ButtonSelectedEvent::EventEnum ButtonSelectedEvent::getEvent(void) const
{
    return _Event;
}

inline
ButtonPtr ButtonSelectedEvent::getButton(void) const
{
    return _Button;
}

inline
ButtonSelectedEvent::ButtonSelectedEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, ButtonPtr Button) :
   Event(Source, TimeStamp),
       _Event(TheEvent),
    _Button(Button)
{
}

OSG_END_NAMESPACE
