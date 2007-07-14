#include "OSGInputConfig.h"

OSG_BEGIN_NAMESPACE

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
KeyEvent::KeyEvent(FieldContainerPtr Source, Time TimeStamp, Key TheKey, UInt32 Modifiers) :
   Event(Source, TimeStamp),
   _Key(TheKey),
   _Modifiers(Modifiers)
{
}

OSG_END_NAMESPACE
