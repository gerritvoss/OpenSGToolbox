#include "OSGInputConfig.h"

#include "OSGInputSettings.h"

OSG_BEGIN_NAMESPACE

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
MouseWheelEvent::MouseWheelEvent(FieldContainerPtr Source, Time TimeStamp, Int32 WheelRotation, ScrollType TheScrollType)
: Event(Source, TimeStamp),
_WheelRotation(WheelRotation),
_ScrollType(TheScrollType)
{}

OSG_END_NAMESPACE
