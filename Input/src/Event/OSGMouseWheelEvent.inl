#include <OpenSG/OSGConfig.h>

#include "OSGInputSettings.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &MouseWheelEvent::getClassType(void)
{
    return _Type;
}

inline
Int32 MouseWheelEvent::getWheelRotation(void) const
{
   return _WheelRotation;
}

inline
Int32 MouseWheelEvent::getScrollAmount(void) const
{
   return _WheelRotation;
}

inline
Int32 MouseWheelEvent::getUnitsToScroll(void) const
{
   if(_ScrollType == UNIT_SCROLL)
   {
      return _WheelRotation * static_cast<Int32>( InputSettings::the()->getUnitsPerMouseScrollClick() );
   }
   else
   {
      return 0;
   }
}

inline
MouseWheelEvent::ScrollType MouseWheelEvent::getScrollType(void) const
{
   return _ScrollType;
}

inline
Pnt2f MouseWheelEvent::getLocation(void) const
{
   return _Location;
}

inline
ViewportPtr MouseWheelEvent::getViewport(void) const
{
	return _Viewport;
}

inline
MouseWheelEvent::MouseWheelEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer, Int32 WheelRotation, ScrollType TheScrollType, Pnt2f Location, ViewportPtr TheViewport)
: InputEvent(Source, TimeStamp,Producer),
_WheelRotation(WheelRotation),
_ScrollType(TheScrollType),
_Location(Location),
   _Viewport(TheViewport)
{}

OSG_END_NAMESPACE
