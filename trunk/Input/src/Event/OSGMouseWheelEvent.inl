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
