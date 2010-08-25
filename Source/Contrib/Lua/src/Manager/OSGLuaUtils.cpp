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
//#define OSG_WITH_LUA_DEBUGGER


#include "OSGConfig.h"

#include "OSGLuaUtils.h"
#include "OSGLuaManager.h"
#include <boost/lexical_cast.hpp>

#ifdef OSG_WITH_LUA_DEBUGGER

OSG_BEGIN_NAMESPACE

bool lua_details::Value::push(lua_State* L) const
{
	switch (type)
	{
	case Nil:
        lua_pushnil(L);
        return true;
		break;
	case Bool:
        lua_pushboolean(L, boost::lexical_cast<bool>(value));
        return true;
		break;
	case LightUserData:
        lua_pushlightuserdata(L, boost::lexical_cast<void*>(value));
        return true;
		break;
	case Number:
        lua_pushnumber(L, boost::lexical_cast<lua_Number>(value));
        return true;
		break;
	case String:
        lua_pushstring(L, value.c_str());
        return true;
		break;
	case Table:
        //lua_pushboolean(L, boost::lexical_cast<bool>(v.value));
        return false;
		break;
	case Function:
        //lua_pushcfunction(L, boost::lexical_cast<void*>(value));
        return false;
		break;
	case UserData:
        //lua_pushuserdata(L, boost::lexical_cast<void*>(value));
        return false;
		break;
	case Thread:
        //lua_pushthread(L, boost::lexical_cast<void*>(value));
        return false;
		break;

	case None:
	default:
        assert(false && "Can't push UNKNOWN type");
        return false;
		break;
	}
    return true;
}

bool lua_details::Value::operator==(const Value& Right) const
{
    return (type == Right.type && value.compare(Right.value) == 0);
}

bool lua_details::LuaField::operator==(const LuaField& Right) const
{
    return (key == Right.key && val == Right.val);
}

lua_details::State::State(void) //: step_event_(false, true), start_event_(false, true)
{
    L = 0;
    //thread_ = 0;
    break_flag_ = abort_flag_ = false;
    func_call_level_ = 0;
    stop_at_level_ = 0;
    run_mode_ = StepInto;
    is_running_ = false;
    status_ready_ = false;

    L = lua_open();
    //if (L == 0)
        //throw lua_exception("not enough memory for Lua state");
}

lua_details::State::~State(void)
{
    //if (thread_)
    //{
        //abort_flag_ = true;
        ////step_event_.SetEvent();
        ////start_event_.SetEvent();
        ////::WaitForSingleObject(*thread_, -1);
        ////delete thread_;
    //}

    lua_close(L);
}

bool lua_details::State::is_execution_finished(void) const
{
    //TODO: Implement
    return true;
    
    //return ::WaitForSingleObject(*thread_, 0) != WAIT_TIMEOUT; }
}

void lua_details::State::go(RunMode mode)
{
	if (is_execution_finished())
		return;

	run_mode_ = mode;
	break_flag_ = false;
	stop_at_level_ = func_call_level_;

	//if (::WaitForSingleObject(start_event_, 0) == WAIT_OBJECT_0)
		//step_event_.SetEvent();
	//else
	//{
		//start_event_.SetEvent();
		//if (mode == Run)
			//step_event_.SetEvent();
	//}

	//if (mode == Run)	//TODO: improve
		//notify(Running, 0);
}

// internal Lua data is only available when VM stopped at a breakpoint
bool lua_details::State::is_data_available() const
{
	if (is_execution_finished())
		return false;

	return !is_running_;
}

bool lua_details::State::breakpoint_at_line(UInt32 line) const
{
	//CSingleLock lock(&breakpoints_lock_, true);

	BreakpointMap::const_iterator it= breakpoints_.find(line);

	if (it == breakpoints_.end())
		return false;

	return (it->second & BPT_MASK) == BPT_EXECUTE;
}


bool lua_details::State::toggle_breakpoint(UInt32 line)
{
	//CSingleLock lock(&breakpoints_lock_, true);

	if (breakpoint_at_line(line))
	{
		breakpoints_.erase(line);
		return false;
	}
	else
	{
		breakpoints_[line] = BPT_EXECUTE;
		return true;
	}
}

void lua_details::State::notify(LuaRunEvent ev, lua_Debug* dbg)
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


void lua_details::State::exec_hook_function(lua_State* L, lua_Debug* dbg)
{
	State* state= LuaManager::the()->_DebState.get();

    if (state->abort_flag_)
    {
        lua_error(state->L);		// abort now
        return;
    }

    switch (dbg->event)
    {
    case LUA_HOOKCOUNT:
        state->count_hook(L, dbg);
        break;

    case LUA_HOOKCALL:
        state->call_hook(L, dbg);
        break;

    case LUA_HOOKRET:
    case LUA_HOOKTAILRET:	//verify
        state->ret_hook(L, dbg);
        break;

    case LUA_HOOKLINE:
        state->line_hook(L, dbg);
        break;
    }
}


void lua_details::State::count_hook(lua_State* L, lua_Debug*)
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


void lua_details::State::call_hook(lua_State* L, lua_Debug* dbg)
{
	func_call_level_++;
}


void lua_details::State::ret_hook(lua_State* L, lua_Debug* dbg)
{
	func_call_level_--;
}


void lua_details::State::line_hook(lua_State* L, lua_Debug* dbg)
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
		if (breakpoint_at_line(dbg->currentline))
			suspend_exec(dbg, true);	// stop now; there's a breakpoint at the current line
	}
	else
		suspend_exec(dbg, false);	// line-by-line execution, so stop
}


void lua_details::State::suspend_exec(lua_Debug* dbg, bool forced)
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

lua_details::pop_stack_elements::pop_stack_elements(lua_State* L, int num) : L_(L), num_(num)
{
}

void lua_details::pop_stack_elements::dec(void)
{
    --num_;
}

lua_details::pop_stack_elements::~pop_stack_elements(void)
{
    try
    {
        if (num_ > 0)
            lua_pop(L_, num_);
    }
    catch (...)
    {}
}

char* lua_details::to_pointer(char* buffer, const void* ptr)
{
	sprintf(buffer, "0x%p", ptr);
	return buffer;
}

std::string lua_details::to_table(lua_State* L, int index)
{
//	lua_gettable
        return "";
}

UInt32 lua_details::get_num_fields(lua_State* L, int idx)
{
    UInt32 count(0);
    if(lua_istable(L, idx))
    {
        /* table is in the stack at index 'idx' */
        lua_pushnil(L);  /* first key */
	    int table= lua_gettop(L) - 1;
        while (lua_next(L, table) != 0)
        {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
            ++count;
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
    }
    
    return count;
}

bool lua_details::list_table(lua_State* L, int idx, TableInfo& out, int recursive)
{
	out.clear();

	if (lua_type(L, idx) != LUA_TTABLE)
		return false;

	UInt32 size= get_num_fields(L, idx);

	out.reserve(size);

	// table to traverse
	lua_pushvalue(L, idx);

	// push a key
	lua_pushnil(L);

	pop_stack_elements pop(L, 2);	// remove key & table off the stack at the end of this fn
//	pop_stack_elements pop(L, 1);	// remove table off the stack at the end of this fn

	int table= lua_gettop(L) - 1;

	// traverse a table
	while (lua_next(L, table))
	{
		pop_stack_elements pop(L, 1);

		LuaField field;
		capture_value(L, field.key, -2);
		capture_value(L, field.val, -1, recursive);

		out.push_back(field);
	}

	pop.dec();	// final lua_next call removed key

	return true;
}


std::string lua_details::table_as_string(const TableInfo& table, size_t limit)
{
	std::ostringstream ost;

	ost << "{ ";

	const size_t count= table.size();

	for (size_t i= 0; i < count; ++i)
	{
		const LuaField& f= table[i];

		if (i > 0)
			ost << ", ";

		ost << f.key.value << " = " << f.val.value;

		if (i + 1 == limit)
		{
			ost << ", ... ";
			break;
		}
	}

	if (count > 0)
		ost << ' ';

	ost << "}";

	return ost.str();
}

// store information about Lua value present at the 'index' inside 'v' struct
void lua_details::capture_value(lua_State* L, Value& v, int index, int recursive, size_t table_size_limit)
{
	int i= index;

	int t= lua_type(L, i);

	switch (t)
	{
	case LUA_TSTRING:
		v.type = String;
		v.value = lua_tostring(L, i);
		break;

	case LUA_TBOOLEAN:
		v.type = Bool;
		v.value = lua_toboolean(L, i) ? "true" : "false";
		break;

	case LUA_TNUMBER:
		v.type = Number;
        v.value = boost::lexical_cast<std::string>(lua_tonumber(L, i));
		break;

	case LUA_TLIGHTUSERDATA:
		v.type = LightUserData;
        v.value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TUSERDATA:
		v.type = UserData;
		v.value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TTABLE:
		v.type = Table;
		if (recursive > 0)
		{
			TableInfo t;
			list_table(L, i, t, recursive - 1);
			v.value = table_as_string(t, table_size_limit);
		}
		else
			v.value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TFUNCTION:
		v.type = Function;
		v.value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TTHREAD:
		v.type = Thread;
		v.value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TNIL:
		v.type = Nil;
		v.value.clear();
		break;

	default:
		v.type = None;
		v.value.clear();
		break;
	}

	v.type_name = lua_typename(L, t);
}

bool lua_details::list_virtual_stack(lua_State* L, ValueStack& stack, size_t table_size_limit)
{
	int size= lua_gettop(L);

	stack.clear();
	stack.reserve(size);

	for (int idx= size - 1; idx > 0; --idx)
	{
		Value v;
		capture_value(L, v, idx, 1, table_size_limit);

		stack.push_back(v);
	}

	return true;
}

// fill stack frame variable with info from Lua debug struct
void lua_details::fill_frame(const lua_Debug& dbg, StackFrame& frame)
{
	frame.clear();

	frame.source = dbg.source ? dbg.source : dbg.short_src;

	if (dbg.currentline > 0)
		frame.current_line = dbg.currentline;

	if (dbg.what)
	{
		if (strcmp(dbg.what, "C") == 0)
			frame.type = StackFrame::CFun;
		else if (strcmp(dbg.what, "Lua") == 0)
			frame.type = StackFrame::LuaFun;
		else if (strcmp(dbg.what, "main") == 0)
			frame.type = StackFrame::MainChunk;
		else if (strcmp(dbg.what, "tail") == 0)
			frame.type = StackFrame::TailCall;
		else
			frame.type = StackFrame::Err;
	}

	if (dbg.namewhat != 0 && *dbg.namewhat != '\0')	// is there a name?
		frame.name_what = dbg.name;

	frame.last_line_defined = dbg.lastlinedefined;
	frame.line_defined = dbg.linedefined;
}

lua_details::StackFrame::StackFrame(void)
{
    clear();
}

void lua_details::StackFrame::clear(void)
{
    current_line = 0;
    type = Err;
    line_defined = last_line_defined = 0;
}

const Char8* lua_details::StackFrame::sourcePath(void) const
{
    if (source.size() > 1 && source[0] == '@')
        return source.c_str() + 1;

    return 0;
}

bool lua_details::pushFieldOntoStack(lua_State* L, const FieldStack& theFieldStack)
{

    if(theFieldStack.size() == 0)
    {
        lua_pushstring(L,"_G");
        lua_gettable(L, LUA_GLOBALSINDEX);  //Push The global table onto the stack
    }
    else
    {
        //Get the Lua value
        for(UInt32 i(0) ; i<theFieldStack.size() ; ++i)
        {
            if(i == 0)
            {
                if(!theFieldStack[i].key.push(L))//push the key of the table on the stack
                {
                    return false;
                }
                lua_gettable(L, LUA_GLOBALSINDEX);  //Push The table onto the stack
            }
            else
            {
                //Check if the the value given is a table
                if(!lua_istable(L, -1))
                {
                    //Pop the value, and the original table from the stack
                    lua_pop(L, 2);

                    return false;
                }
            
                
                if(!theFieldStack[i].key.push(L))//push the key of the table on the stack
                {
                    return false;
                }
                lua_gettable(L, -2);  //Push The table onto the stack

                //Remove the original table from the stack
                lua_remove(L, -2);
            }
        }
    }
    return true;
}


OSG_END_NAMESPACE
#endif /* OSG_WITH_LUA_DEBUGGER */

