/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGChangeEventDetails.h"

OSG_BEGIN_NAMESPACE

//! access the producer type of the class
inline
const EventProducerType &SpinnerModel::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 SpinnerModel::getProducerClassTypeId(void)
{
    return _producerType.getId();
}
inline
boost::signals2::connection SpinnerModel::attachActivity(UInt32 eventId,
                                           Activity* TheActivity)
{
    return connectStateChanged(eventId, boost::bind(&Activity::eventProduced, ActivityUnrecPtr(TheActivity), _1, _2) );
}

inline
UInt32 SpinnerModel::getNumProducedEvents(void) const
{
    return getProducerType().getNumEventDescs();
}

inline
const EventDescription *SpinnerModel::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findEventDescription(ProducedEventName);
}

inline
const EventDescription *SpinnerModel::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getEventDescription(ProducedEventId);
}

inline
UInt32 SpinnerModel::getProducedEventId(const Char8 *ProducedEventName) const
{
    return getProducerType().getProducedEventId(ProducedEventName);
}

inline
boost::signals2::connection  SpinnerModel::connectStateChanged(const StateChangedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _StateChangedEvent.connect(listener, at);
}

inline
boost::signals2::connection  SpinnerModel::connectStateChanged(const StateChangedEventType::group_type &group,
                                                    const StateChangedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _StateChangedEvent.connect(group, listener, at);
}

inline
void  SpinnerModel::disconnectStateChanged(const StateChangedEventType::group_type &group)
{
    _StateChangedEvent.disconnect(group);
}

inline
void  SpinnerModel::disconnectAllSlotsStateChanged(void)
{
    _StateChangedEvent.disconnect_all_slots();
}

inline
bool  SpinnerModel::isEmptyStateChanged(void) const
{
    return _StateChangedEvent.empty();
}

inline
UInt32  SpinnerModel::numSlotsStateChanged(void) const
{
    return _StateChangedEvent.num_slots();
}

inline
void SpinnerModel::produceStateChanged(StateChangedEventDetailsType* const e)
{
    _StateChangedEvent.set_combiner(ConsumableEventCombiner(e));
    _StateChangedEvent(dynamic_cast<StateChangedEventDetailsType* const>(e), StateChangedEventId);
}

OSG_END_NAMESPACE

