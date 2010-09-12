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

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGBaseInitFunctions.h"
#include "OSGLog.h"
#include "OSGEventDetails.h"
#include "OSGStatCollector.h"

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

/*! \class OSG::LuaManager
A FMod SoundManager Interface. 
*/

struct AddLuaInitFuncs
{
    AddLuaInitFuncs()
    {
        addPreFactoryInitFunction(boost::bind(&LuaManager::init));
        addPreFactoryExitFunction(boost::bind(&LuaManager::uninit));
    }
} AddLuaInitFuncsInstantiation;

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

LuaManager *LuaManager::_the  = NULL;
lua_State *LuaManager::_State = NULL;

//! WindowEventProducer Produced Events

EventDescription *LuaManager::_eventDesc[] =
{
    new EventDescription("LuaError", 
                          "Lua Error",
                          LuaErrorEventId, 
                          FieldTraits<LuaErrorEventDetails *>::getType(),
                          true,
                          NULL),
};

EventProducerType LuaManager::_producerType(
                                            "LuaManagerProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

StatElemDesc<StatTimeElem> LuaManager::statScriptsRunTime("ScriptsRunTime", 
                                                         "time to run the lua scripts");

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

bool LuaManager::recreateLuaState(void)
{
    //Close the Lua State
    if(_State != NULL)
    {
        SLOG << "LuaManager: closing Lua State." << std::endl;

        lua_close(_State);
        _State = NULL;

        SLOG << "LuaManager: Lua State Closed." << std::endl;
    }

    SLOG << "LuaManager: Opening Lua State." << std::endl;

    _State = lua_open();
    if(_State == NULL)
    {
        SWARNING << "LuaManager: Failed to open lua state." << std::endl;
        return false;
    }

    luaL_openlibs(_State); 

    //Load the OpenSG Bindings
    SLOG << "LuaManager: Loading OpenSG Bindings." << std::endl;
    luaopen_OSG(_State);

    SLOG << "LuaManager: Successfully opened Lua State." << std::endl;
    return true;
}

bool LuaManager::openLuaBindingLib(OpenBoundLuaLibFunctor OpenFunc)
{
    if(_State != NULL)
    {
        SLOG << "LuaManager: Opening Lua bindings lib." << std::endl;
        OpenFunc(_State);
        SLOG << "LuaManager: Succefully opened Lua bindings lib." << std::endl;
        return true;
    }
    else
    {
        SWARNING << "LuaManager: Failed to open lua binding, because the Lua State has not been created.." << std::endl;
        return false;
    }
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

    switch (ar->event)
    {
        case LUA_HOOKCALL:
            {
                //push function calls to the top of the callstack
                std::stringstream ss;
                ss << ar->short_src << ":"

                    << ar->linedefined << ": "
                    << (ar->name == NULL ? "[UNKNOWN]" : ar->name)
                    << " (" << ar->namewhat << ")";

                the()->_LuaStack.push_front(ss.str());
            }
            break;
        case LUA_HOOKRET:
            //pop the returned function from the callstack
            if (the()->_LuaStack.size()>0)
            {
                the()->_LuaStack.pop_front();
            }
            break;
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

int LuaManager::runScript(const std::string& Script)
{
    //Start the  scripts run time statistic
    StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

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
    if(s != 0)
    {
        //Error loading the string
        if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
        return s;
    }

    // execute Lua program
    s = lua_pcall(_State, 0, LUA_MULTRET, 0);
    checkError(s);

    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
    return s;
}

int LuaManager::runScript(const BoostPath& ScriptPath)
{
    if(boost::filesystem::exists(ScriptPath))
    {
        //Start the  scripts run time statistic
        StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
        if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

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
        if(s != 0)
        {
            //Error loading the string
            if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
            return s;
        }

        // execute Lua program
        s = lua_pcall(_State, 0, LUA_MULTRET, 0);
        checkError(s);

        if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
        return s;
    }
    else
    {
        SWARNING << "LuaManager::runScript(): File by path: " << ScriptPath.string() << ", does not exist." << std::endl;
        return 0;
    }
}

int LuaManager::runPushedFunction(UInt32 NumArgs, UInt32 NumReturns)
{
    //Start the  scripts run time statistic
    StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

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

    int s = lua_pcall(_State, NumArgs, NumReturns, 0);
    checkError(s);

    //Stop the  scripts run time statistic
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
    return s;
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
            produceLuaError(Status);
            lua_pop(_State, 1); // remove error message
            break;
        case LUA_ERRFILE:
            //File Read Error
            SWARNING << "Lua File Load Error: " << lua_tostring(_State, -1) << std::endl;
            printStackTrace();
            produceLuaError(Status);
            lua_pop(_State, 1); // remove error message
            break;
        case LUA_ERRMEM:
            //Memory Allocation Error
            SWARNING << "Lua Memory Allocation Error: " << lua_tostring(_State, -1) << std::endl;
            printStackTrace();
            produceLuaError(Status);
            lua_pop(_State, 1); // remove error message
            break;
        case LUA_ERRRUN:
            //Memory Allocation Error
            SWARNING << "Lua Runtime Error: " << lua_tostring(_State, -1) << std::endl;
            printStackTrace();
            produceLuaError(Status);
            lua_pop(_State, 1); // remove error message
            break;
        case LUA_ERRERR:
            //Memory Allocation Error
            SWARNING << "Lua Error in Error Handler: " << lua_tostring(_State, -1) << std::endl;
            printStackTrace();
            produceLuaError(Status);
            lua_pop(_State, 1); // remove error message
            break;
    }

    if(_EnableStackTrace)
    {
        _LuaStack.clear();
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


void LuaManager::produceLuaError(int Status)
{
    LuaErrorEventDetailsUnrecPtr Details = LuaErrorEventDetails::create(NULL, getSystemTime(), _State, Status, _LuaStack, _EnableStackTrace);
   
    produceLuaError(Details);
}

void LuaManager::setPackagePath(const std::string& Pattern)
{
    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaManager::getPackagePath(): package is not a table" << std::endl;
        return;
    }
    lua_pushlstring(_State, Pattern.c_str(), Pattern.size());
    lua_setfield(_State, 1, "path");
    lua_pop(_State, 1);
}

std::string LuaManager::getPackagePath(void) const
{
    std::string Result("");

    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaManager::getPackagePath(): package is not a table" << std::endl;
        return Result;
    }
    lua_getfield(_State, 1, "path");
    if (LUA_TSTRING != lua_type(_State, 2)) 
    {
        SWARNING << "LuaManager::getPackagePath(): package.path is not a string" << std::endl;
        lua_pop(_State, 1);
        return Result;
    }
    Result = lua_tostring(_State, 2);
    lua_pop(_State, 1);

    return Result;
}

void LuaManager::setPackageCPath(const std::string& Pattern)
{
    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaManager::getPackageCPath(): package is not a table" << std::endl;
        return;
    }
    lua_pushlstring(_State, Pattern.c_str(), Pattern.size());
    lua_setfield(_State, 1, "cpath");
    lua_pop(_State, 1);
}

std::string LuaManager::getPackageCPath(void) const
{
    std::string Result("");

    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaManager::getPackageCPath(): package is not a table" << std::endl;
        return Result;
    }
    lua_getfield(_State, 1, "cpath");
    if (LUA_TSTRING != lua_type(_State, 2)) 
    {
        SWARNING << "LuaManager::getPackageCPath(): package.cpath is not a string" << std::endl;
        lua_pop(_State, 1);
        return Result;
    }
    Result = lua_tostring(_State, 2);
    lua_pop(_State, 1);

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaManager::LuaManager(void) : 
    _EnableStackTrace(true)
{	
}

LuaManager::LuaManager(const LuaManager &source) : 
    _EnableStackTrace(source._EnableStackTrace)
{
    assert(false && "Sould NOT CALL LuaManager copy constructor");
}

LuaManager::~LuaManager(void)
{
}

#ifdef OSG_WITH_LUA_DEBUGGER


void LuaManager::setCallback(const boost::function<void (lua_details::LuaRunEvent, int)>& fn)
{
    _DebState->callback_ = fn;
}

void LuaManager::dump(ProgBuf& program, bool debug)
{
	program.clear();

	//lua_TValue* t= _DebState->L->top - 1;

	//if (!ttisfunction(t))
		//return;

	//const Proto* f= clvalue(t)->l.p; //toproto(_DebState->L, -1);
	//{
		//LuaLocker lock(_DebState->L);
        ////export this fn:
		////luaU_dump(_DebState->L, f, writer, &program, !debug);
        //assert(false && "Not Implemented");
	//}
}

Int32 LuaManager::call(void)
{
	int narg   = 0;
	//int base = lua_gettop(_DebState->L) - narg;  // function index
	int err_fn = 0;
	int status = lua_pcall(_DebState->L, narg, LUA_MULTRET, err_fn);

	return status;
}

void LuaManager::stepInto(void)
{
	_DebState->go(lua_details::State::StepInto);
}

void LuaManager::stepOver(void)
{
	_DebState->go(lua_details::State::StepOver);
}

void LuaManager::run(void)
{
	_DebState->go(lua_details::State::Run);
}

void LuaManager::stepOut(void)
{
	_DebState->go(lua_details::State::StepOut);
}

std::string LuaManager::status(void) const
{
	if (_DebState->is_execution_finished() || _DebState->status_ready_)
		return _DebState->status_msg_;

    return _DebState->is_running_ ? "Running" : "Stopped";
}

bool LuaManager::isRunning(void) const
{
    if (_DebState->is_execution_finished())
        return false;

	return _DebState->is_running_;
}

bool LuaManager::isFinished(void) const
{
	return _DebState->is_execution_finished();
}

bool LuaManager::isStopped(void) const
{
	return _DebState->is_data_available();
}

bool LuaManager::toggleBreakpoint(Int32 line)
{
	return _DebState->toggle_breakpoint(line);
}

void LuaManager::breakProg(void)
{
	_DebState->break_flag_ = true;
}

std::string LuaManager::getCallStack(void) const
{
	if (!_DebState->is_data_available())
		return std::string();

	std::ostringstream callstack;

	// local info= debug.getinfo(1)
//LUA_API int lua_getstack (lua_State *L, int level, lua_Debug *ar);

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	while (lua_getstack(_DebState->L, level++, &dbg))
	{
		if (lua_getinfo(_DebState->L, "Snl", &dbg) == 0)
		{
			callstack << "-- error at level " << level;
			break;
		}

		callstack << dbg.short_src;
		if (dbg.currentline > 0)
			callstack << ':' << dbg.currentline;

		if (*dbg.namewhat != '\0')  /* is there a name? */
			callstack << " in function " << dbg.name;
		else
		{
			if (*dbg.what == 'm')  /* main? */
				callstack << " in main chunk";
			else if (*dbg.what == 'C' || *dbg.what == 't')
				callstack << " ?";  /* C function or tail call */
			else
				callstack << " in file <" << dbg.short_src << ':' << dbg.linedefined << '>';
		}

		callstack << std::endl;
	}


	return callstack.str();
}


bool LuaManager::getLocalVars(std::vector<lua_details::Var>& out, Int32 level) const
{
	out.clear();

	if (!_DebState->is_data_available())
		return false;

	lua_Debug dbg;
	memset(&dbg, 0, sizeof(dbg));

	if (!lua_getstack(_DebState->L, level, &dbg))
		return false;

	if (lua_getinfo(_DebState->L, "Snl", &dbg))
	{
		const int SAFETY_COUNTER= 10000;

		for (int i= 1; i < SAFETY_COUNTER; ++i)
		{
			const char* name= lua_getlocal(_DebState->L, &dbg, i);

			if (name == 0)
				break;

			lua_details::pop_stack_elements pop(_DebState->L, 1);	// pop variable value eventually

			lua_details::Var var;
			var.name = name;
			lua_details::capture_value(_DebState->L, var.v, lua_gettop(_DebState->L));

			out.push_back(var);
		}
	}

	return true;
}

bool LuaManager::getGlobalVars(lua_details::TableInfo& out, bool deep) const
{
	if (!_DebState->is_data_available())
		return false;

	return lua_details::list_table(_DebState->L, LUA_GLOBALSINDEX, out, deep ? 1 : 0);
}

bool LuaManager::getValueStack(lua_details::ValueStack& stack) const
{
	if (!_DebState->is_data_available())
		return false;

	const size_t limit_table_elements_to= 10;

	return lua_details::list_virtual_stack(_DebState->L, stack, limit_table_elements_to);
}

bool LuaManager::getCallStack(lua_details::CallStack& stack) const
{
	if (!_DebState->is_data_available())
		return false;

	stack.clear();
	stack.reserve(8);

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	while (lua_getstack(_DebState->L, level++, &dbg))
	{
		lua_details::StackFrame frame;

		if (lua_getinfo(_DebState->L, "Snl", &dbg) == 0)
		{
			stack.push_back(frame);	// error encountered
			break;
		}

		lua_details::fill_frame(dbg, frame);

		stack.push_back(frame);
	}

	return true;
}

bool LuaManager::getCurrentSource(lua_details::StackFrame& top) const
{
	if (!_DebState->is_data_available())
		return false;

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	if (!lua_getstack(_DebState->L, level, &dbg) || !lua_getinfo(_DebState->L, "Snl", &dbg))
		return false;

	lua_details::fill_frame(dbg, top);

	return true;
}

#endif

OSG_END_NAMESPACE
