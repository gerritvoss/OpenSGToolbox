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
const EventType &InputEvent::getClassType(void)
{
    return _Type;
}

inline
void InputEvent::consume(void) const
{
	_Consumed = true;
}

inline
bool InputEvent::isConsumed(void) const
{
    return _Consumed;
}

inline
WindowEventProducerPtr InputEvent::getEventProducer(void) const
{
    return _EventProducer;
}

inline
InputEvent::InputEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer) 
: Event(Source, TimeStamp),
_Consumed(false),
_EventProducer(Producer)
{}

    
OSG_END_NAMESPACE
