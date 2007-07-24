#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ButtonSelectedEvent::EventType ButtonSelectedEvent::getEvent(void) const
{
    return _Event;
}

inline
ButtonPtr ButtonSelectedEvent::getButton(void) const
{
    return _Button;
}

inline
ButtonSelectedEvent::ButtonSelectedEvent(FieldContainerPtr Source, Time TimeStamp, EventType TheEvent, ButtonPtr Button) :
   Event(Source, TimeStamp),
       _Event(TheEvent),
    _Button(Button)
{
}

OSG_END_NAMESPACE
