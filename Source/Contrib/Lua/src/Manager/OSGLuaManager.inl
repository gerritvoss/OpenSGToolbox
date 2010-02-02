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
bool LuaManager::isLuaListenerAttached(LuaListenerRefPtr Listener) const
{
    return _LuaListeners.find(Listener) != _LuaListeners.end();
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
EventConnection LuaManager::attachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    return _Producer.attachActivity(TheActivity, ProducedEventId);
}

inline
bool LuaManager::isActivityAttached(ActivityRefPtr TheActivity, UInt32 ProducedEventId) const
{
    return _Producer.isActivityAttached(TheActivity, ProducedEventId);
}

inline
UInt32 LuaManager::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    return _Producer.getNumActivitiesAttached(ProducedEventId);
}

inline
ActivityRefPtr LuaManager::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    return _Producer.getAttachedActivity(ProducedEventId,ActivityIndex);
}

inline
void LuaManager::detachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    _Producer.detachActivity(TheActivity, ProducedEventId);
}

inline
UInt32 LuaManager::getNumProducedEvents(void) const
{
    return _Producer.getNumProducedEvents();
}

inline
const MethodDescription *LuaManager::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventDescription(ProducedEventName);
}

inline
const MethodDescription *LuaManager::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return _Producer.getProducedEventDescription(ProducedEventId);
}

inline
UInt32 LuaManager::getProducedEventId(const Char8 *ProducedEventName) const
{
    return _Producer.getProducedEventId(ProducedEventName);
}

inline
lua_State *LuaManager::getLuaState(void)
{
    return _State;
}

OSG_END_NAMESPACE

