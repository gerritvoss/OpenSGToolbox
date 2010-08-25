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

#include "OSGConfig.h"

#include "OSGChangeEventDetails.h"
#include "OSGCommandEventDetails.h"

OSG_BEGIN_NAMESPACE

//! access the producer type of the class
inline
const EventProducerType &CommandManager::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 CommandManager::getProducerClassTypeId(void)
{
    return _producerType.getId();
}
inline
boost::signals2::connection CommandManager::attachActivity(UInt32 eventId,
                                           Activity* TheActivity)
{
    return connectCommandExecuted(eventId, boost::bind(&Activity::eventProduced, ActivityUnrecPtr(TheActivity), _1, _2) );
}

inline
UInt32 CommandManager::getNumProducedEvents(void) const
{
    return getProducerType().getNumEventDescs();
}

inline
const EventDescription *CommandManager::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findEventDescription(ProducedEventName);
}

inline
const EventDescription *CommandManager::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getEventDescription(ProducedEventId);
}

inline
UInt32 CommandManager::getProducedEventId(const Char8 *ProducedEventName) const
{
    return getProducerType().getProducedEventId(ProducedEventName);
}

inline
boost::signals2::connection  CommandManager::connectCommandExecuted(const CommandExecutedEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _CommandExecutedEvent.connect(listener, at);
}

inline
boost::signals2::connection  CommandManager::connectCommandExecuted(const CommandExecutedEventType::group_type &group,
                                                    const CommandExecutedEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _CommandExecutedEvent.connect(group, listener, at);
}

inline
void  CommandManager::disconnectCommandExecuted(const CommandExecutedEventType::group_type &group)
{
    _CommandExecutedEvent.disconnect(group);
}

inline
void  CommandManager::disconnectAllSlotsCommandExecuted(void)
{
    _CommandExecutedEvent.disconnect_all_slots();
}

inline
bool  CommandManager::isEmptyCommandExecuted(void) const
{
    return _CommandExecutedEvent.empty();
}

inline
UInt32  CommandManager::numSlotsCommandExecuted(void) const
{
    return _CommandExecutedEvent.num_slots();
}

inline
void CommandManager::produceCommandExecuted(CommandExecutedEventDetailsType* const e)
{
    _CommandExecutedEvent.set_combiner(ConsumableEventCombiner(e));
    _CommandExecutedEvent(dynamic_cast<CommandExecutedEventDetailsType* const>(e), CommandExecutedEventId);
}

OSG_END_NAMESPACE

