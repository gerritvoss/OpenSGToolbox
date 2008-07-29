#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &KeyEvent::getClassType(void)
{
    return _Type;
}

inline
KeyEvent::Key KeyEvent::getKey(void) const
{
   return _Key;
}

inline
UInt32 KeyEvent::getModifiers(void) const
{
   return _Modifiers;
}

inline
UChar8 KeyEvent::getKeyChar(void) const
{
   return getCharFromKey(_Key, _Modifiers);
}

inline
WindowPtr KeyEvent::getWindow(void) const
{
	return _Window;
}

inline
KeyEvent::KeyEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer, Key TheKey, UInt32 Modifiers, WindowPtr TheWindow) :
   InputEvent(Source, TimeStamp,Producer),
   _Key(TheKey),
   _Modifiers(Modifiers),
   _Window(TheWindow)
{
}

inline
UInt64 KeyEvent::ModifiedKey::getHashable(void) const
{
    return (static_cast<UInt64>(_Modifiers) << 32) | (static_cast<UInt64>(_Key));
}

OSG_END_NAMESPACE
