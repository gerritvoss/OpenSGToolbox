#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
Field* FieldChangeEvent::getField(void) const
{
	return _Field;
}

inline
FieldDescription* FieldChangeEvent::getFieldDescription(void) const
{
	return _FieldDescription;
}

inline
FieldChangeEvent::FieldChangeEvent(FieldContainerPtr Source, Time TimeStamp, Field* TheField, FieldDescription* TheDescription) :
   Event(Source, TimeStamp),
   _Field(TheField),
   _FieldDescription(TheDescription)
{
}

OSG_END_NAMESPACE
