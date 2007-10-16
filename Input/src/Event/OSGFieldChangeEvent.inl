#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &FieldChangeEvent::getClassType(void)
{
    return _Type;
}

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

OSG_END_NAMESPACE
