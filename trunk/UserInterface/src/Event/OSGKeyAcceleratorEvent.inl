/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
const EventType &KeyAcceleratorEvent::getClassType(void)
{
    return _Type;
}

inline
KeyAcceleratorEvent::EventEnum KeyAcceleratorEvent::getEvent(void) const
{
    return _Event;
}

inline
KeyAcceleratorEvent::KeyAcceleratorEvent(FieldContainerPtr Source, Time TimeStamp, KeyEvent::Key TheKey, UInt32 Modifiers, WindowPtr TheWindow, EventEnum TheEvent) :
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
