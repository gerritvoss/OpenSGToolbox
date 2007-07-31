#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
Time UpdateEvent::getElapsedTime(void) const
{
	return _Elps;
}

inline
UpdateEvent::UpdateEvent(FieldContainerPtr Source, Time TimeStamp, Time Elps) :
   Event(Source, TimeStamp),
   _Elps(Elps)
{
}

OSG_END_NAMESPACE
