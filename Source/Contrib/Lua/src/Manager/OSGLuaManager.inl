/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

OSG_BEGIN_NAMESPACE

//! access the producer type of the class
inline
const EventProducerType &LuaManager::getProducerClassType(void)
{
    return _producerType;
}

//! access the producer type id of the class
inline
UInt32 LuaManager::getProducerClassTypeId(void)
{
    return _producerType.getId();
}

inline
void LuaManager::setEnableStackTrace(bool Enable)
{
    _EnableStackTrace = Enable;
}

inline
bool LuaManager::getEnableStackTrace(void) const
{
    return _EnableStackTrace;
}


inline
boost::signals2::connection LuaManager::attachActivity(UInt32 eventId,
                                           Activity* TheActivity)
{
    return connectLuaError(boost::bind(&Activity::eventProduced, ActivityUnrecPtr(TheActivity), _1, _2) );
}

inline
UInt32 LuaManager::getNumProducedEvents(void) const
{
    return getProducerType().getNumEventDescs();
}

inline
const EventDescription *LuaManager::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findEventDescription(ProducedEventName);
}

inline
const EventDescription *LuaManager::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getEventDescription(ProducedEventId);
}

inline
UInt32 LuaManager::getProducedEventId(const Char8 *ProducedEventName) const
{
    return getProducerType().getProducedEventId(ProducedEventName);
}

inline
lua_State *LuaManager::getLuaState(void)
{
    return _State;
}

inline
boost::signals2::connection  LuaManager::connectLuaError(const LuaErrorEventType::slot_type &listener, 
                                                                               boost::signals2::connect_position at)
{
    return _LuaErrorEvent.connect(listener, at);
}

inline
boost::signals2::connection  LuaManager::connectLuaError(const LuaErrorEventType::group_type &group,
                                                    const LuaErrorEventType::slot_type &listener, boost::signals2::connect_position at)
{
    return _LuaErrorEvent.connect(group, listener, at);
}

inline
void  LuaManager::disconnectLuaError(const LuaErrorEventType::group_type &group)
{
    _LuaErrorEvent.disconnect(group);
}

inline
void  LuaManager::disconnectAllSlotsLuaError(void)
{
    _LuaErrorEvent.disconnect_all_slots();
}

inline
bool  LuaManager::isEmptyLuaError(void) const
{
    return _LuaErrorEvent.empty();
}

inline
UInt32  LuaManager::numSlotsLuaError(void) const
{
    return _LuaErrorEvent.num_slots();
}

inline
void LuaManager::produceLuaError(LuaErrorEventDetailsType* const e)
{
    _LuaErrorEvent.set_combiner(ConsumableEventCombiner(e));
    _LuaErrorEvent(dynamic_cast<LuaErrorEventDetailsType* const>(e), LuaErrorEventId);
}

OSG_END_NAMESPACE

