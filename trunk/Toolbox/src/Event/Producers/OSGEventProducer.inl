/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventProducerType &EventProducer::getProducerClassType(void)
{
    return _ProducerClassType;
}

inline
UInt32 EventProducer::getProducerClassTypeId(void)
{
    return _ProducerClassType.getId();
}

inline
const EventProducerType &EventProducer::getProducerType(void) const
{
    return *_ProducerType;
}

inline
UInt32 EventProducer::getNumProducedEvents(void) const
{
    return getProducerType().getNumMethodDescs();
}

inline
const MethodDescription *EventProducer::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findMethodDescription(ProducedEventName);
}

inline
const MethodDescription *EventProducer::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getMethodDescription(ProducedEventId);
}

//Activities
inline
EventConnection EventProducer::attachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName)
{
    return attachActivity(TheActivity, getProducedEventId(ProducedEventName));
}

inline
bool EventProducer::isActivityAttached(ActivityPtr TheActivity, const Char8 *ProducedEventName) const
{
    return isActivityAttached(TheActivity, getProducedEventId(ProducedEventName));
}

inline
UInt32 EventProducer::getNumActivitiesAttached(const Char8 *ProducedEventName) const
{
    return getNumActivitiesAttached(getProducedEventId(ProducedEventName));
}

inline
ActivityPtr EventProducer::getAttachedActivity(const Char8 *ProducedEventName, UInt32 ActivityIndex) const
{
    return getAttachedActivity(getProducedEventId(ProducedEventName), ActivityIndex);
}

inline
void EventProducer::detachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName)
{
    return detachActivity(TheActivity, getProducedEventId(ProducedEventName));
}


//EventListeners
inline
EventConnection EventProducer::attachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName)
{
    return attachEventListener(TheEventListener, getProducedEventId(ProducedEventName));
}

inline
bool EventProducer::isEventListenerAttached(EventListenerPtr TheEventListener, const Char8 *ProducedEventName) const
{
    return isEventListenerAttached(TheEventListener, getProducedEventId(ProducedEventName));
}

inline
UInt32 EventProducer::getNumEventListenersAttached(const Char8 *ProducedEventName) const
{
    return getNumEventListenersAttached(getProducedEventId(ProducedEventName));
}

inline
EventListenerPtr EventProducer::getAttachedEventListener(const Char8 *ProducedEventName, UInt32 EventListenerIndex) const
{
    return getAttachedEventListener(getProducedEventId(ProducedEventName), EventListenerIndex);
}

inline
void EventProducer::detachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName)
{
    return detachEventListener(TheEventListener, getProducedEventId(ProducedEventName));
}

inline
void EventProducer::setType(const EventProducerType* TheProducerType)
{
    _ProducerType = TheProducerType;
}

OSG_END_NAMESPACE

