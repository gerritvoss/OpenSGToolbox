#include "OSGFieldChangeEvent.h"

OSG_BEGIN_NAMESPACE

EventType FieldChangeEvent::_Type("FieldChangeEvent", "EventType");

const EventType &FieldChangeEvent::getType(void) const
{
    return _Type;
}

FieldChangeEvent::FieldChangeEvent(FieldContainerPtr Source, Time TimeStamp, Field* TheField, FieldDescription* TheDescription) :
   Event(Source, TimeStamp),
   _Field(TheField),
   _FieldDescription(TheDescription)
{
}

OSG_END_NAMESPACE
