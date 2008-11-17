/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
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
