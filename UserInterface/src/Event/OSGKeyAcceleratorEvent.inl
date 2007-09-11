#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
KeyAcceleratorEvent::EventType KeyAcceleratorEvent::getEvent(void) const
{
    return _Event;
}

inline
KeyAcceleratorEvent::KeyAcceleratorEvent(FieldContainerPtr Source, Time TimeStamp, KeyEvent::Key TheKey, UInt32 Modifiers, WindowPtr TheWindow, EventType TheEvent) :
   Event(Source, TimeStamp),
   _Key(TheKey),
   _Modifiers(Modifiers),
   _Window(TheWindow),
       _Event(TheEvent)
{
}

inline
KeyEvent::Key KeyAcceleratorEvent::getKey(void) const
{
   return _Key;
}

inline
UInt32 KeyAcceleratorEvent::getModifiers(void) const
{
   return _Modifiers;
}

inline
WindowPtr KeyAcceleratorEvent::getWindow(void) const
{
	return _Window;
}
OSG_END_NAMESPACE
