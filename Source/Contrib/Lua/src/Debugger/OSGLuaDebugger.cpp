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

#include "OSGLuaDebugger.h"
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <sstream>

#include "OSGLuaDetailsStackFrame.h"
#include "OSGLuaDetailsLuaField.h"
#include "OSGLuaDetailsBreakpoint.h"
#include "OSGLuaUtils.h"

OSG_BEGIN_NAMESPACE

extern "C" int luaopen_OSG(lua_State* L); // declare the wrapped module

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LuaDebugger
A FMod SoundManager Interface. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

LuaDebugger *LuaDebugger::_the  = NULL;
lua_State *LuaDebugger::_State = NULL;

//! WindowEventProducer Produced Events

EventDescription *LuaDebugger::_eventDesc[] =
{
    new EventDescription("LuaError", 
                          "Lua Error",
                          LuaErrorEventId, 
                          FieldTraits<LuaErrorEventDetails *>::getType(),
                          true,
                          NULL),
};

EventProducerType LuaDebugger::_producerType(
                                            "LuaDebuggerProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

StatElemDesc<StatTimeElem> LuaDebugger::statScriptsRunTime("ScriptsRunTime", 
                                                         "time to run the lua scripts");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const EventProducerType &LuaDebugger::getProducerType(void) const
{
    return _producerType;
}

LuaDebugger *LuaDebugger::the(void)
{
    if(_the == NULL)
    {
        _the = new LuaDebugger();
    }

    return _the;
}

int LuaDebugger::handleLuaError(lua_State *L)
{
    //Produce the Lua Error event
    the()->produceLuaError(LUA_ERRRUN);

    return 1;
}

bool LuaDebugger::init(void)
{
    SLOG << "LuaDebugger Initializing." << std::endl;

    _State = lua_open();
    if(_State == NULL)
    {
        SWARNING << "Failed to create lua state." << std::endl;
        return false;
    }
    else
    {
        the()->L = _State;
    }

    luaL_openlibs(_State); 

    //Load the OpenSG Bindings
    SLOG << "LuaDebugger Loading OpenSG Bindings." << std::endl;
    luaopen_OSG(_State);

    SLOG << "LuaDebugger Successfully Initialized." << std::endl;
    return true;
}

bool LuaDebugger::recreateLuaState(void)
{
    //Close the Lua State
    if(_State != NULL)
    {
        SLOG << "LuaDebugger: closing Lua State." << std::endl;

        lua_close(_State);
        _State = NULL;

        SLOG << "LuaDebugger: Lua State Closed." << std::endl;
    }

    SLOG << "LuaDebugger: Opening Lua State." << std::endl;

    _State = lua_open();
    if(_State == NULL)
    {
        SWARNING << "LuaDebugger: Failed to open lua state." << std::endl;
        return false;
    }
    else
    {
        the()->L = _State;
    }

    luaL_openlibs(_State); 

    //Load the OpenSG Bindings
    SLOG << "LuaDebugger: Loading OpenSG Bindings." << std::endl;
    luaopen_OSG(_State);

    SLOG << "LuaDebugger: Successfully opened Lua State." << std::endl;
    return true;
}

bool LuaDebugger::openLuaBindingLib(OpenBoundLuaLibFunctor OpenFunc)
{
    if(_State != NULL)
    {
        SLOG << "LuaDebugger: Opening Lua bindings lib." << std::endl;
        OpenFunc(_State);
        SLOG << "LuaDebugger: Succefully opened Lua bindings lib." << std::endl;
        return true;
    }
    else
    {
        SWARNING << "LuaDebugger: Failed to open lua binding, because the Lua State has not been created.." << std::endl;
        return false;
    }
}

bool LuaDebugger::uninit(void)
{
    if(_State != NULL)
    {
        SLOG << "LuaDebugger Uninitializing." << std::endl;

        lua_close(_State);
        _State = NULL;

        SLOG << "LuaDebugger Successfully Uninitialized." << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool LuaDebugger::is_execution_finished(void) const
{
    //TODO: Implement
    //return true;
    return false;
    
    //return ::WaitForSingleObject(*thread_, 0) != WAIT_TIMEOUT; }
}

void LuaDebugger::go(RunMode mode)
{
	if (is_execution_finished())
		return;

	run_mode_ = mode;
	break_flag_ = false;
	stop_at_level_ = func_call_level_;
}

// internal Lua data is only available when VM stopped at a breakpoint
bool LuaDebugger::is_data_available() const
{
	if (is_execution_finished())
		return false;

	return !is_running_;
}

bool LuaDebugger::breakpoint_at_line(UInt32 line) const
{
	//CSingleLock lock(&breakpoints_lock_, true);

    lua_details::BreakpointMap::const_iterator it= breakpoints_.find(line);

	if (it == breakpoints_.end())
		return false;

	return (it->second & lua_details::BPT_MASK) == lua_details::BPT_EXECUTE;
}

bool LuaDebugger::breakpoint_at_line(const std::string& filename, UInt32 line) const
{
	//CSingleLock lock(&breakpoints_lock_, true);
	lua_details::FileBreakpointMap::const_iterator fileMapIt= file_breakpoints_.find(filename);
    if(fileMapIt == file_breakpoints_.end())
    {
        return false;
    }

	lua_details::BreakpointMap::const_iterator it= fileMapIt->second.find(line);

	if (it == breakpoints_.end())
		return false;

	return (it->second & lua_details::BPT_MASK) == lua_details::BPT_EXECUTE;
}


bool LuaDebugger::toggle_breakpoint(UInt32 line)
{
	//CSingleLock lock(&breakpoints_lock_, true);

	if (breakpoint_at_line(line))
	{
		breakpoints_.erase(line);
		return false;
	}
	else
	{
		breakpoints_[line] = lua_details::BPT_EXECUTE;
		return true;
	}
}

bool LuaDebugger::toggle_breakpoint(const std::string& filename, UInt32 line)
{
	//CSingleLock lock(&breakpoints_lock_, true);
    
    if(file_breakpoints_.find(filename) == file_breakpoints_.end())
    {
        file_breakpoints_[filename] = lua_details::BreakpointMap();
    }

	if (breakpoint_at_line(filename, line))
	{
		file_breakpoints_[filename].erase(line);
		return false;
	}
	else
	{
		file_breakpoints_[filename][line] = lua_details::BPT_EXECUTE;
		return true;
	}
}

void LuaDebugger::notify(LuaRunEvent ev, lua_Debug* dbg)
{
	if (callback_)
	{
		try
		{
			callback_(ev, dbg != 0 ? dbg->currentline : -1);
		}
		catch (...)
		{
		}
	}
}


void LuaDebugger::exec_hook_function(lua_State* L, lua_Debug* dbg)
{
    if (the()->abort_flag_)
    {
        lua_error(L);		// abort now
        return;
    }

    switch (dbg->event)
    {
    case LUA_HOOKCOUNT:
        the()->count_hook(L, dbg);
        break;

    case LUA_HOOKCALL:
        the()->call_hook(L, dbg);
        break;

    case LUA_HOOKRET:
    case LUA_HOOKTAILRET:	//verify
        the()->ret_hook(L, dbg);
        break;

    case LUA_HOOKLINE:
        the()->line_hook(L, dbg);
        break;
    }
}


void LuaDebugger::count_hook(lua_State* L, lua_Debug*)
{
	if (break_flag_)
	{
		lua_Debug dbg;
		memset(&dbg, 0, sizeof(dbg));
		dbg.currentline = -1;

		if (lua_getstack(L, 0, &dbg))
		{
			// retrieve current line number, count hook doesn't provide it
			int stat= lua_getinfo(L, "l", &dbg);
			if (stat == 0)
				dbg.currentline = -1;
		}

		// break signaled; stop
		suspend_exec(&dbg, true);
	}
}


void LuaDebugger::call_hook(lua_State* L, lua_Debug* dbg)
{
	func_call_level_++;
}


void LuaDebugger::ret_hook(lua_State* L, lua_Debug* dbg)
{
	func_call_level_--;
}


void LuaDebugger::line_hook(lua_State* L, lua_Debug* dbg)
{
	if (break_flag_)
	{
		// break signaled; stop
		suspend_exec(dbg, true);
	}
	else if (run_mode_ == StepOver)
	{
		if (stop_at_level_ >= func_call_level_)	// 'step over' done?
			suspend_exec(dbg, true);	// stop now
	}
	else if (run_mode_ == StepOut)
	{
		if (stop_at_level_ > func_call_level_)	// 'step out' done?
			suspend_exec(dbg, true);	// stop now
	}
	else if (run_mode_ == Run)	// run without delay?
	{
		// check breakpoints
        if(dbg->source[0] == '@') //Is the current source in a file
        {
            std::string Filename(dbg->source);
            Filename = Filename.substr(1);

            if (breakpoint_at_line(Filename, dbg->currentline))
                suspend_exec(dbg, true);	// stop now; there's a breakpoint at the current line
        }
        else
        {
            if (breakpoint_at_line(dbg->currentline))
                suspend_exec(dbg, true);	// stop now; there's a breakpoint at the current line
        }
	}
	else
		suspend_exec(dbg, false);	// line-by-line execution, so stop
}


void LuaDebugger::suspend_exec(lua_Debug* dbg, bool forced)
{
	//if (forced)
		//step_event_.ResetEvent();

	// step by step execution

	notify(NewLine, dbg);

	//if (::WaitForSingleObject(step_event_, 0) != WAIT_OBJECT_0)		// blocked?
	//{
		//is_running_ = false;
		//CSingleLock wait(&step_event_, true);
	//}

	if (abort_flag_)
	{
		lua_error(L);		// abort now
		return;
	}

	is_running_ = true;

	//step_event_.ResetEvent();
}

int LuaDebugger::runScript(const std::string& Script)
{
    //Start the  scripts run time statistic
    StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

    //Push on an error handler
    lua_pushcfunction(_State, LuaDebugger::handleLuaError);

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
    s = lua_pcall(_State, 0, LUA_MULTRET, 1);
    if(s != 0)
    {
        lua_pop(_State, 1); // remove error message
    }

    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
    return s;
}

int LuaDebugger::runScript(const BoostPath& ScriptPath)
{
    if(boost::filesystem::exists(ScriptPath))
    {
        //Start the  scripts run time statistic
        StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
        if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

        //Push on an error handler
        lua_pushcfunction(_State, LuaDebugger::handleLuaError);

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
        s = lua_pcall(_State, 0, LUA_MULTRET, 1);
        if(s != 0)
        {
            lua_pop(_State, 1); // remove error message
        }

        if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
        return s;
    }
    else
    {
        SWARNING << "LuaDebugger::runScript(): File by path: " << ScriptPath.string() << ", does not exist." << std::endl;
        return 0;
    }
}

int LuaDebugger::runPushedFunction(UInt32 NumArgs, UInt32 NumReturns)
{
    //Start the  scripts run time statistic
    StatTimeElem *ScriptsRunTimeStatElem = StatCollector::getGlobalElem(statScriptsRunTime);
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->start(); }

    //Push on an error handler
    lua_pushcfunction(_State, LuaDebugger::handleLuaError);

    //Put the function at index 1
    lua_insert(_State, 1);

    int s = lua_pcall(_State, NumArgs, NumReturns, 1);
    if(s != 0)
    {
        lua_pop(_State, 1); // remove error message
    }

    //Stop the  scripts run time statistic
    if(ScriptsRunTimeStatElem) { ScriptsRunTimeStatElem->stop(); }
    return s;
}

void LuaDebugger::checkError(int Status)
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
}

void LuaDebugger::printStackTrace(void) const
{
    SWARNING << getCallStack();
}


void LuaDebugger::produceLuaError(int Status)
{
    LuaErrorEventDetailsUnrecPtr Details = LuaErrorEventDetails::create(NULL, getSystemTime(), _State, Status);
   
    produceLuaError(Details);
}

void LuaDebugger::setPackagePath(const std::string& Pattern)
{
    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaDebugger::getPackagePath(): package is not a table" << std::endl;
        return;
    }
    lua_pushlstring(_State, Pattern.c_str(), Pattern.size());
    lua_setfield(_State, 1, "path");
    lua_pop(_State, 1);
}

std::string LuaDebugger::getPackagePath(void) const
{
    std::string Result("");

    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaDebugger::getPackagePath(): package is not a table" << std::endl;
        return Result;
    }
    lua_getfield(_State, 1, "path");
    if (LUA_TSTRING != lua_type(_State, 2)) 
    {
        SWARNING << "LuaDebugger::getPackagePath(): package.path is not a string" << std::endl;
        lua_pop(_State, 1);
        return Result;
    }
    Result = lua_tostring(_State, 2);
    lua_pop(_State, 1);

    return Result;
}

void LuaDebugger::setPackageCPath(const std::string& Pattern)
{
    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaDebugger::getPackageCPath(): package is not a table" << std::endl;
        return;
    }
    lua_pushlstring(_State, Pattern.c_str(), Pattern.size());
    lua_setfield(_State, 1, "cpath");
    lua_pop(_State, 1);
}

std::string LuaDebugger::getPackageCPath(void) const
{
    std::string Result("");

    //Get the package table
    lua_getglobal(_State, "package");
    if (LUA_TTABLE != lua_type(_State, 1))
    {
        SWARNING << "LuaDebugger::getPackageCPath(): package is not a table" << std::endl;
        return Result;
    }
    lua_getfield(_State, 1, "cpath");
    if (LUA_TSTRING != lua_type(_State, 2)) 
    {
        SWARNING << "LuaDebugger::getPackageCPath(): package.cpath is not a string" << std::endl;
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

LuaDebugger::LuaDebugger(void) 
{	
    L = 0;
    //thread_ = 0;
    break_flag_ = abort_flag_ = false;
    func_call_level_ = 0;
    stop_at_level_ = 0;
    run_mode_ = StepInto;
    is_running_ = false;
    status_ready_ = false;

    //L = lua_open();
    //if (L == 0)
        //throw lua_exception("not enough memory for Lua state");
}

LuaDebugger::LuaDebugger(const LuaDebugger &source) 
{
    assert(false && "Sould NOT CALL LuaDebugger copy constructor");
}

LuaDebugger::~LuaDebugger(void)
{
}

void LuaDebugger::setCallback(const boost::function<void (LuaRunEvent, int)>& fn)
{
    callback_ = fn;
}

void LuaDebugger::dump(ProgBuf& program, bool debug)
{
	program.clear();

	//lua_TValue* t= L->top - 1;

	//if (!ttisfunction(t))
		//return;

	//const Proto* f= clvalue(t)->l.p; //toproto(L, -1);
	//{
		//LuaLocker lock(L);
        ////export this fn:
		////luaU_dump(L, f, writer, &program, !debug);
        //assert(false && "Not Implemented");
	//}
}

Int32 LuaDebugger::call(void)
{
	int narg   = 0;
	//int base = lua_gettop(L) - narg;  // function index
	int err_fn = 0;
	int status = lua_pcall(L, narg, LUA_MULTRET, err_fn);

	return status;
}

void LuaDebugger::stepInto(void)
{
	go(StepInto);
}

void LuaDebugger::stepOver(void)
{
	go(StepOver);
}

void LuaDebugger::run(void)
{
	go(Run);
}

void LuaDebugger::stepOut(void)
{
	go(StepOut);
}

std::string LuaDebugger::status(void) const
{
	if (is_execution_finished() || status_ready_)
		return status_msg_;

    return is_running_ ? "Running" : "Stopped";
}

bool LuaDebugger::isRunning(void) const
{
    if (is_execution_finished())
        return false;

	return is_running_;
}

bool LuaDebugger::isFinished(void) const
{
	return is_execution_finished();
}

bool LuaDebugger::isStopped(void) const
{
	return is_data_available();
}

bool LuaDebugger::toggleBreakpoint(Int32 line)
{
	return toggle_breakpoint(line);
}

bool LuaDebugger::toggleBreakpoint(const std::string& filename, Int32 line)
{
	return toggle_breakpoint(filename, line);
}

void LuaDebugger::breakProg(void)
{
	break_flag_ = true;
}

std::string LuaDebugger::getCallStack(void) const
{
	//if (!is_data_available())
		//return std::string();

	std::ostringstream callstack;

	// local info= debug.getinfo(1)
//LUA_API int lua_getstack (lua_State *L, int level, lua_Debug *ar);

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	while (lua_getstack(L, level++, &dbg))
	{
		if (lua_getinfo(L, "Snl", &dbg) == 0)
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


bool LuaDebugger::getLocalVars(std::vector<lua_details::Var>& out, Int32 level) const
{
	out.clear();

	if (!is_data_available())
		return false;

	lua_Debug dbg;
	memset(&dbg, 0, sizeof(dbg));

	if (!lua_getstack(L, level, &dbg))
		return false;

	if (lua_getinfo(L, "Snl", &dbg))
	{
		const int SAFETY_COUNTER= 10000;

		for (int i= 1; i < SAFETY_COUNTER; ++i)
		{
			const char* name= lua_getlocal(L, &dbg, i);

			if (name == 0)
				break;

			lua_details::popStackElements pop(L, 1);	// pop variable value eventually

			lua_details::Value val(L, lua_gettop(L));

			lua_details::Var var(name, val);

			out.push_back(var);
		}
	}

	return true;
}

bool LuaDebugger::getGlobalVars(lua_details::TableInfo& out, bool deep) const
{
	if (!is_data_available())
		return false;

	return lua_details::listTable(L, LUA_GLOBALSINDEX, out, deep ? 1 : 0);
}

bool LuaDebugger::getValueStack(lua_details::ValueStack& stack) const
{
	if (!is_data_available())
		return false;

	const size_t limit_table_elements_to= 10;

	return lua_details::listVirtualStack(L, stack, limit_table_elements_to);
}

bool LuaDebugger::getCallStack(lua_details::CallStack& stack) const
{
	if (!is_data_available())
		return false;

	stack.clear();
	stack.reserve(8);

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	while (lua_getstack(L, level++, &dbg))
	{
		lua_details::StackFrame frame;

		if (lua_getinfo(L, "Snl", &dbg) == 0)
		{
			stack.push_back(frame);	// error encountered
			break;
		}

		frame.fill(dbg);

		stack.push_back(frame);
	}

	return true;
}

bool LuaDebugger::getCurrentSource(lua_details::StackFrame& top) const
{
	if (!is_data_available())
		return false;

	int level= 0;
	lua_Debug dbg;
	memset(&dbg, 0, sizeof dbg);

	if (!lua_getstack(L, level, &dbg) || !lua_getinfo(L, "Snl", &dbg))
		return false;

	top.fill(dbg);

	return true;
}

OSG_END_NAMESPACE
