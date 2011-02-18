/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGLUADEBUGGER_H_
#define _OSGLUADEBUGGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#ifdef OSG_WITH_LUA_DEBUGGER

#include "lua.hpp"
#include <list>

#include "OSGEventProducerType.h"
#include "OSGLuaErrorEventDetails.h"
#include "OSGConsumableEventCombiner.h"
#include "OSGEventDescription.h"
#include "OSGActivity.h"
#include "OSGPathType.h"
#include "OSGStatElemTypes.h"

#include <boost/function.hpp>

#include <boost/scoped_ptr.hpp>
#include "OSGLuaUtils.h"
#include "OSGLuaDetailsVar.h"
#include "OSGLuaDetailsStackFrame.h"
#include "OSGLuaDetailsLuaField.h"
#include "OSGLuaDetailsBreakpoint.h"
//#include <exception>

OSG_BEGIN_NAMESPACE

/*! \brief LuaDebugger class. See \ref 
  PageSoundLuaDebugger for a description.
  */

//struct lua_exception : public std::exception
//{
	//lua_exception(const char* msg) : exception(msg)
	//{}
//};

class OSG_CONTRIBLUA_DLLMAPPING LuaDebugger
{
    friend class LuaActivity;

  private:

    /*==========================  PUBLIC  =================================*/
  public:
    typedef LuaErrorEventDetails LuaErrorEventDetailsType;
    typedef boost::signals2::signal<void (LuaErrorEventDetails* const, UInt32), ConsumableEventCombiner> LuaErrorEventType;
    typedef boost::function<int ( lua_State* )> OpenBoundLuaLibFunctor;

    enum
    {
        LuaErrorEventId = 1,
        NextEventId     = LuaErrorEventId            + 1
    };

    enum LuaRunEvent
    { 
        Start    = 0,
        Running  = 1,
        NewLine  = 2,
        Finished = 3
    };

    enum RunMode
    {
        StepInto = 0,
        StepOver = 1,
        StepOut  = 2,
        Run      = 3
    };

    static LuaDebugger* the(void);

    int runScript(const std::string& Script);
    int runScript(const BoostPath& ScriptPath);
    int runPushedFunction(UInt32 NumArgs, UInt32 NumReturns);

    static bool init(void);
    bool recreateLuaState(void);
    bool openLuaBindingLib(OpenBoundLuaLibFunctor OpenFunc);
    static bool uninit(void);

    void setPackagePath(const std::string& Pattern);
    std::string getPackagePath(void) const;

    void setPackageCPath(const std::string& Pattern);
    std::string getPackageCPath(void) const;

    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 
    virtual const EventProducerType &getProducerType(void) const; 

    boost::signals2::connection          attachActivity(UInt32 eventId,
                                                       Activity* TheActivity);
    UInt32                   getNumProducedEvents(void)          const;
    const EventDescription *getProducedEventDescription(const   Char8 *ProducedEventName) const;
    const EventDescription *getProducedEventDescription(UInt32  ProducedEventId) const;
    UInt32                   getProducedEventId(const            Char8 *ProducedEventName) const;

    boost::signals2::connection connectLuaError(const LuaErrorEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    boost::signals2::connection connectLuaError(const LuaErrorEventType::group_type &group,
                                                       const LuaErrorEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    void   disconnectLuaError       (const LuaErrorEventType::group_type &group);
    void   disconnectAllSlotsLuaError(void);
    bool   isEmptyLuaError          (void) const;
    UInt32 numSlotsLuaError         (void) const;

    lua_State *getLuaState(void);
    void checkError(int Status);

    static StatElemDesc<StatTimeElem   > statScriptsRunTime;

	void setCallback(const boost::function<void (LuaRunEvent, Int32)>& fn);

    typedef std::vector<UChar8> ProgBuf;
	void dump(ProgBuf& program, bool debug);

	// execute
	Int32 call(void);

	// execute single line (current one) following calls, if any
	void stepInto(void);

	// execute current line, without entering any functions
	void stepOver(void);

	// start execution
	void run(void);

	// run till return from the current function
	void stepOut(void);

	std::string status(void) const;

    // is Lua program running now? (if not, maybe it stopped at the breakpoint)
    bool isRunning(void) const;

    // has Lua program finished execution?
    bool isFinished(void) const;

    // if stopped, it can be resumed (if not stopped, it's either running or done)
	bool isStopped(void) const;	

	// toggle breakpoint in given line
	bool toggleBreakpoint(Int32 line);

	// toggle breakpoint in given line of the given file
	bool toggleBreakpoint(const std::string& filename, Int32 line);

	// stop running program
	void breakProg(void);

	// get current call stack
	std::string getCallStack(void) const;

	// get local vars of function at given 'level'
	bool getLocalVars(std::vector<lua_details::Var>& out, Int32 level= 0) const;

	// get global vars
	bool getGlobalVars(lua_details::TableInfo& out, bool deep) const;

	// read all values off virtual value stack
	bool getValueStack(lua_details::ValueStack& stack) const;

	// get function call stack
	bool getCallStack(lua_details::CallStack& stack) const;

	// info about current function and source file (at the top of the stack)
    bool getCurrentSource(lua_details::StackFrame& top) const;

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

    bool breakpoint_at_line(const std::string& filename, UInt32 line) const;

    bool toggle_breakpoint(UInt32 line);

    bool toggle_breakpoint(const std::string& filename, UInt32 line);

    /*==========================  PRIVATE  ================================*/
  private:

    static LuaDebugger* _the;

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    LuaErrorEventType _LuaErrorEvent;

    static int handleLuaError(lua_State *L);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaDebugger(void);
    LuaDebugger(const LuaDebugger &source);
    LuaDebugger& operator=(const LuaDebugger &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaDebugger(void); 

    /*! \}                                                                 */
    RunMode run_mode_;

    lua_State* L;
    bool abort_flag_;
    bool break_flag_;
    boost::function<void (LuaRunEvent, Int32)> callback_;
    std::string status_msg_;
    bool status_ready_;

    lua_details::BreakpointMap breakpoints_;

    lua_details::FileBreakpointMap file_breakpoints_;

    //mutable CCriticalSection breakpoints_lock_;
    Int32 func_call_level_;
    Int32 stop_at_level_;
    bool is_running_;

    void printStackTrace(void) const;


    static lua_State *_State;

    void produceLuaError(int Status);
    
    void produceLuaError(LuaErrorEventDetailsType* const e);
};

typedef LuaDebugger *LuaDebuggerP;

OSG_END_NAMESPACE

#include "OSGLuaDebugger.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADEBUGGER_H_ */

