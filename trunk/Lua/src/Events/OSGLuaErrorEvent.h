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

#ifndef _OSGLUAERROREVENT_H_
#define _OSGLUAERROREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGLuaDef.h"

#include <OpenSG/Toolbox/OSGEvent.h>
#include <list>

#include "lua.hpp"

OSG_BEGIN_NAMESPACE

class OSG_LUALIB_DLLMAPPING LuaErrorEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
      
    LuaErrorEvent(FieldContainerPtr Source, Time TimeStamp, lua_State* State, int LuaStatus, const std::list<std::string>& StackTrace, bool EnableStackTrace);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);

    const lua_State* getLuaState(void) const;
    int              getStatus(void) const;
    std::string      getErrorString(void) const;
    const std::list<std::string>& getStackTrace(void) const;
    bool              getEnableStackTrace(void) const;
    
  protected:

    lua_State *_State;
    int        _LuaStatus;
    std::list<std::string> _LuaStack;
    bool _EnableStackTrace;
  
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGLuaErrorEvent.inl"

#endif /* _OSGLUAERROREVENT_H_ */
