/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Lua                               *
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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define OSG_COMPILELUALIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGLog.h>

#include "OSGLuaManager.h"
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <sstream>

//This is the OSGBase wrapped module in Bindings/OSG_wrap.cpp
extern "C" int luaopen_OSG(lua_State* L); // declare the wrapped module

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LuaManager
A FMod SoundManager Interface. 
*/

struct AddLuaInitFuncs
{
    AddLuaInitFuncs()
    {
        addInitFunction(&LuaManager::init);
        addSystemExitFunction(&LuaManager::uninit);
    }
} AddLuaInitFuncsInstantiation;

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

LuaManager *LuaManager::_the = NULL;
lua_State *LuaManager::_State = NULL;

//! WindowEventProducer Produced Methods

MethodDescription *LuaManager::_methodDesc[] =
{
    new MethodDescription("LuaError", 
                     LuaErrorMethodId, 
                     SFEventPtr::getClassType(),
                     FunctorAccessMethod())
};

EventProducerType LuaManager::_producerType(
    "LuaManagerProducerType",
    "EventProducerType",
    NULL,
    InitEventProducerFunctor(),
    _methodDesc,
    sizeof(_methodDesc));

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const EventProducerType &LuaManager::getProducerType(void) const
{
    return _producerType;
}

LuaManager *LuaManager::the(void)
{
    if(_the == NULL)
    {
        _the = new LuaManager();
    }

    return _the;
}

void LuaManager::report_errors(lua_State *L, int status)
{
}

bool LuaManager::init(void)
{
    SLOG << "LuaManager Initializing." << std::endl;

    _State = lua_open();
    if(_State == NULL)
    {
        SWARNING << "Failed to create lua state." << std::endl;
        return false;
    }

    luaL_openlibs(_State); 

    //Load the OpenSG Bindings
    SLOG << "LuaManager Loading OpenSG Bindings." << std::endl;
    luaopen_OSG(_State);

    SLOG << "LuaManager Successfully Initialized." << std::endl;
    return true;
}

bool LuaManager::uninit(void)
{
    if(_State != NULL)
    {
        SLOG << "LuaManager Uninitializing." << std::endl;

        lua_close(_State);
        _State = NULL;

        SLOG << "LuaManager Successfully Uninitialized." << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

void LuaManager::FunctionHook(lua_State *l, lua_Debug *ar)
{
    //fill up the debug structure with information from the lua stack
    lua_getinfo(l, "Snl", ar);

    //push function calls to the top of the callstack
    if (ar->event == LUA_HOOKCALL)
    {
        std::stringstream ss;
        ss << ar->short_src << ":"

        << ar->linedefined << ": "
        << (ar->name == NULL ? "[UNKNOWN]" : ar->name)
        << " (" << ar->namewhat << ")";

        the()->_LuaStack.push_front(ss.str());
    }
    //pop the returned function from the callstack
    else if (ar->event ==LUA_HOOKRET)
    {
        if (the()->_LuaStack.size()>0)
        {
            the()->_LuaStack.pop_front();
        }
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LuaManager::runScript(const std::string& Script)
{
    //If Stack Trace is enabled
    if(_EnableStackTrace)
    {
        _LuaStack.clear();
        lua_sethook(_State,&LuaManager::FunctionHook,LUA_MASKCALL | LUA_MASKRET,0);
    }
    else
    {
        lua_sethook(_State,NULL,LUA_MASKCALL | LUA_MASKRET,0);
    }

    //Load the Script
    int s = luaL_loadstring(_State, Script.c_str());
    checkError(s);

    // execute Lua program
    s = lua_pcall(_State, 0, LUA_MULTRET, 0);
    checkError(s);
}

void LuaManager::runScript(const Path& ScriptPath)
{
    if(boost::filesystem::exists(ScriptPath))
    {
        //If Stack Trace is enabled
        if(_EnableStackTrace)
        {
            _LuaStack.clear();
            lua_sethook(_State,&LuaManager::FunctionHook,LUA_MASKCALL | LUA_MASKRET,0);
        }
        else
        {
            lua_sethook(_State,NULL,LUA_MASKCALL | LUA_MASKRET,0);
        }

        //Load the Script
        int s = luaL_loadfile(_State, ScriptPath.string().c_str());
        checkError(s);

        // execute Lua program
        s = lua_pcall(_State, 0, LUA_MULTRET, 0);
        checkError(s);
    }
    else
    {
        SWARNING << "LuaManager::runScript(): File by path: " << ScriptPath.string() << ", does not exist." << std::endl;
    }
}

EventConnection LuaManager::addLuaListener(LuaListenerPtr Listener)
{
   _LuaListeners.insert(Listener);
   
   return EventConnection(
       boost::bind(&LuaManager::isLuaListenerAttached, this, Listener),
       boost::bind(&LuaManager::removeLuaListener, this, Listener));
}

void LuaManager::removeLuaListener(LuaListenerPtr Listener)
{
    LuaListenerSetItor EraseIter(_LuaListeners.find(Listener));
    if(EraseIter != _LuaListeners.end())
    {
        _LuaListeners.erase(EraseIter);
    }
}

void LuaManager::checkError(int Status)
{
    switch(Status)
    {
    case 0:
        //No Error
        break;
    case LUA_ERRSYNTAX:
        //Syntax Error
        SWARNING << "Lua Syntax Error: " << lua_tostring(_State, -1) << std::endl;
        produceError(Status);
        lua_pop(_State, 1); // remove error message
        break;
    case LUA_ERRFILE:
        //File Read Error
        SWARNING << "Lua File Load Error: " << lua_tostring(_State, -1) << std::endl;
        printStackTrace();
        produceError(Status);
        lua_pop(_State, 1); // remove error message
        break;
    case LUA_ERRMEM:
        //Memory Allocation Error
        SWARNING << "Lua Memory Allocation Error: " << lua_tostring(_State, -1) << std::endl;
        printStackTrace();
        produceError(Status);
        lua_pop(_State, 1); // remove error message
        break;
    case LUA_ERRRUN:
        //Memory Allocation Error
        SWARNING << "Lua Runtime Error: " << lua_tostring(_State, -1) << std::endl;
        printStackTrace();
        produceError(Status);
        lua_pop(_State, 1); // remove error message
        break;
    case LUA_ERRERR:
        //Memory Allocation Error
        SWARNING << "Lua Error in Error Handler: " << lua_tostring(_State, -1) << std::endl;
        printStackTrace();
        produceError(Status);
        lua_pop(_State, 1); // remove error message
        break;
    }
    
}

void LuaManager::printStackTrace(void) const
{
    if(_EnableStackTrace)
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl;
        
        std::list<std::string>::const_iterator ListItor(_LuaStack.begin());
        for(; ListItor != _LuaStack.end() ; ++ListItor)
        {
            ss << "     " << (*ListItor) << std::endl;
        }
        SWARNING << ss.str();
    }
}


void LuaManager::produceError(int Status)
{
    LuaErrorEventPtr TheEvent = LuaErrorEvent::create( NullFC, getSystemTime(), _State, Status, _LuaStack, _EnableStackTrace);
    LuaListenerSet ListenerSet(_LuaListeners);
    for(LuaListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->error(TheEvent);
    }
    _Producer.produceEvent(LuaErrorMethodId,TheEvent);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaManager::LuaManager(void) : 
    _EnableStackTrace(true),
    _Producer(&_producerType)
{	
}

LuaManager::LuaManager(const LuaManager &source) : 
    _EnableStackTrace(source._EnableStackTrace),
    _Producer(&_producerType)
{
    assert(false && "Sould NOT CALL LuaManager copy constructor");
}

LuaManager::~LuaManager(void)
{
}

OSG_END_NAMESPACE
