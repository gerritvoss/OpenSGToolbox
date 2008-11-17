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
const EventType &FocusEvent::getClassType(void)
{
    return _Type;
}

inline
FocusEvent::EventEnum FocusEvent::getEvent(void) const
{
    return _Event;
}

inline
bool FocusEvent::getTemporary(void) const
{
    return _Temporary;
}

inline
ComponentPtr FocusEvent::getOpposite(void) const
{
    return _Opposite;
}

inline
FocusEvent::FocusEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, bool Temporary, ComponentPtr Opposite) :
   Event(Source, TimeStamp),
       _Event(TheEvent),
    _Temporary(Temporary),
    _Opposite(Opposite)
{
}

OSG_END_NAMESPACE
