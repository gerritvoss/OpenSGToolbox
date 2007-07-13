#include "OSGInputConfig.h"

OSG_BEGIN_NAMESPACE

inline
WindowPtr WindowEvent::getWindow(void) const
{
	return _Window;
}

inline
WindowEvent::WindowEvent(FieldContainerPtr Source, Time TimeStamp, WindowPtr TheWindow) :
   Event(Source, TimeStamp),
   _Window(TheWindow)
{
}

OSG_END_NAMESPACE
