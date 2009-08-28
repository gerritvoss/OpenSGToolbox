/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Physics                             *
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
const lua_State* LuaErrorEvent::getLuaState(void) const
{
    return _State;
}

inline
int LuaErrorEvent::getStatus(void) const
{
    return _LuaStatus;
}

inline
std::string LuaErrorEvent::getErrorString(void) const
{
    return lua_tostring(_State, -1);
}

inline
LuaErrorEvent::LuaErrorEvent(FieldContainerPtr Source, Time TimeStamp, lua_State* State, int LuaStatus) :
   Event(Source, TimeStamp),
    _State(State),
    _LuaStatus(LuaStatus)
{
}

OSG_END_NAMESPACE

