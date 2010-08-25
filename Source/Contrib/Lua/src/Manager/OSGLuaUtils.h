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

#ifndef _OSGLUAUTILS_H_
#define _OSGLUAUTILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#include "OSGBaseTypes.h"
#include "lua.hpp"
#include <boost/function.hpp>
#include <vector>
#include <map>

#define OSG_WITH_LUA_DEBUGGER
#ifdef OSG_WITH_LUA_DEBUGGER

OSG_BEGIN_NAMESPACE

namespace lua_details
{

    enum LuaRunEvent
    { 
        Start    = 0,
        Running  = 1,
        NewLine  = 2,
        Finished = 3
    };

    enum ValType
    {
        None          = -1,
        Nil           =  0,
        Bool          =  1,
        LightUserData =  2,
        Number        =  3,
        String        =  4,
        Table         =  5,
        Function      =  6,
        UserData      =  7,
        Thread        =  8
    };

    struct OSG_CONTRIBLUA_DLLMAPPING Value	// value on a virtual stack or elsewhere
    {
        Value(void);

        ValType type;
        const Char8* type_name;
        std::string value;	// simplified string representation of value

        bool push(lua_State* L) const;
        bool operator==(const Value& Right) const;
    };

    typedef std::vector<Value> ValueStack;

    struct Var
    {
        std::string name;	// variable's identifier
        Value v;
    };

    struct OSG_CONTRIBLUA_DLLMAPPING LuaField	// table entry
    {
        Value key;
        Value val;

        bool operator==(const LuaField& Right) const;
    };

    typedef std::vector<LuaField> TableInfo;
    typedef std::vector<LuaField> FieldStack;

    struct StackFrame
    {
        StackFrame(void);

        void clear(void);

        const Char8* sourcePath(void) const;

        enum Entry
        { 
            Err       = 0,
            LuaFun    = 1,
            MainChunk = 2,
            CFun      = 3,
            TailCall  = 4
        } type;

        std::string source;
        std::string name_what;
        UInt32 current_line;	// 1..N or 0 if not available
        // where it is defined (Lua fn)
        UInt32 line_defined;
        UInt32 last_line_defined;
    };
    // 
    typedef std::vector<StackFrame> CallStack;

    enum Breakpoint
    {
        BPT_NONE	= 0x00,		// nie ma przerwania
        BPT_EXECUTE	= 0x01,		// przerwanie przy wykonaniu
        BPT_READ	= 0x02,		// przerwanie przy odczycie
        BPT_WRITE	= 0x04,		// przerwanie przy zapisie
        BPT_MASK	= 0x07,
        BPT_NO_CODE	= 0x08,		// wiersz nie zawiera kodu - przerwanie nie mo¿e byæ ustawione
        BPT_TEMP_EXEC=0x10,		// przerwanie tymczasowe do zatrzymania programu
        BPT_DISABLED= 0x80		// przerwanie wy³¹czone
    };

    struct OSG_CONTRIBLUA_DLLMAPPING  State
    {
        State(void);

        ~State(void);

        enum RunMode
        {
            StepInto = 0,
            StepOver = 1,
            StepOut  = 2,
            Run      = 3
        };

        void go(RunMode mode);

        //static UINT AFX_CDECL exec_thread(LPVOID param);
        static void exec_hook_function(lua_State* L, lua_Debug* ar);
        void exec_hook(lua_State* L, lua_Debug* dbg);
        void line_hook(lua_State* L, lua_Debug* dbg);
        void count_hook(lua_State* L, lua_Debug* dbg);
        void call_hook(lua_State* L, lua_Debug* dbg);
        void ret_hook(lua_State* L, lua_Debug* dbg);
        void suspend_exec(lua_Debug* dbg, bool forced);

        void notify(LuaRunEvent ev, lua_Debug* dbg);

        bool is_execution_finished(void) const;

        bool is_data_available(void) const;

        bool breakpoint_at_line(UInt32 line) const;

        bool toggle_breakpoint(UInt32 line);

        lua_State* L;
        //CWinThread* thread_;
        //CEvent step_event_;
        //CEvent start_event_;
        bool abort_flag_;
        bool break_flag_;
        boost::function<void (LuaRunEvent, Int32)> callback_;
        std::string status_msg_;
        bool status_ready_;
        typedef std::map<UInt32, Breakpoint> BreakpointMap;
        BreakpointMap breakpoints_;
        //mutable CCriticalSection breakpoints_lock_;
        Int32 func_call_level_;
        Int32 stop_at_level_;
        bool is_running_;

      private:
        void run();
        RunMode run_mode_;
    };

    class OSG_CONTRIBLUA_DLLMAPPING LuaLocker
    {
      private:
        lua_State* L_;

      public:
        LuaLocker(lua_State* L);

        ~LuaLocker(void);
    };

    class OSG_CONTRIBLUA_DLLMAPPING pop_stack_elements
    {
      public:
        pop_stack_elements(lua_State* L, int num);

        void dec(void);

        ~pop_stack_elements(void);

      private:
        lua_State* L_;
        int num_;
    };

    char OSG_CONTRIBLUA_DLLMAPPING *to_pointer(char* buffer, const void* ptr);

    std::string OSG_CONTRIBLUA_DLLMAPPING to_table(lua_State* L, int index);

    bool OSG_CONTRIBLUA_DLLMAPPING list_table(lua_State* L, int idx, TableInfo& out, int recursive= 0);

    UInt32 OSG_CONTRIBLUA_DLLMAPPING get_num_fields(lua_State* L, int idx);

    std::string OSG_CONTRIBLUA_DLLMAPPING table_as_string(const TableInfo& table, size_t limit);

    // store information about Lua value present at the 'index' inside 'v' struct
    void OSG_CONTRIBLUA_DLLMAPPING capture_value(lua_State* L, Value& v, int index, int recursive= 0, size_t table_size_limit= 10);

    bool OSG_CONTRIBLUA_DLLMAPPING list_virtual_stack(lua_State* L, ValueStack& stack, size_t table_size_limit);

    // fill stack frame variable with info from Lua debug struct
    void OSG_CONTRIBLUA_DLLMAPPING fill_frame(const lua_Debug& dbg, StackFrame& frame);
    

    bool OSG_CONTRIBLUA_DLLMAPPING pushFieldOntoStack(lua_State* L, const FieldStack& theNode);


}

OSG_END_NAMESPACE

#include "OSGLuaUtils.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUAUTILS_H_ */

