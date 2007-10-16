#include "OSGFieldChangeEvent.h"

OSG_BEGIN_NAMESPACE

FieldChangeEvent::FieldChangeEvent(FieldContainerPtr Source, Time TimeStamp, Field* TheField, FieldDescription* TheDescription) :
   Event(Source, TimeStamp),
   _Field(TheField),
   _FieldDescription(TheDescription)
{
}

OSG_END_NAMESPACE
