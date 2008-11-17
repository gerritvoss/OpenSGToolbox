#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &AdjustmentEvent::getClassType(void)
{
    return _Type;
}

inline
AdjustmentEvent::EventEnum AdjustmentEvent::getEvent(void) const
{
    return _Event;
}

inline
UInt32 AdjustmentEvent::getValue(void) const
{
    return _Value;
}

inline
bool AdjustmentEvent::getValueIsAdjusting(void) const
{
    return _ValueIsAdjusting;
}

inline
AdjustmentEvent:: AdjustmentEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, UInt32 Value, bool ValueIsAdjusting) :
   Event(Source, TimeStamp),
       _Event(TheEvent),
       _Value(Value),
       _ValueIsAdjusting(ValueIsAdjusting)
{
}

OSG_END_NAMESPACE
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
