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

#ifndef _OSGLUAMANAGER_H_
#define _OSGLUAMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

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

#ifdef OSG_WITH_LUA_DEBUGGER
#include <boost/scoped_ptr.hpp>
#include "OSGLuaUtils.h"
//#include <exception>
#endif

OSG_BEGIN_NAMESPACE

/*! \brief LuaManager class. See \ref 
  PageSoundLuaManager for a description.
  */


#ifdef OSG_WITH_LUA_DEBUGGER

//struct lua_exception : public std::exception
//{
	//lua_exception(const char* msg) : exception(msg)
	//{}
//};

#endif

class OSG_CONTRIBLUA_DLLMAPPING LuaManager
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

    static LuaManager* the(void);

    int runScript(const std::string& Script);
    int runScript(const BoostPath& ScriptPath);
    int runPushedFunction(UInt32 NumArgs, UInt32 NumReturns);

    static void report_errors(lua_State *L, int status);

    static bool init(void);
    bool recreateLuaState(void);
    bool openLuaBindingLib(OpenBoundLuaLibFunctor OpenFunc);
    static bool uninit(void);

    void setPackagePath(const std::string& Pattern);
    std::string getPackagePath(void) const;

    void setPackageCPath(const std::string& Pattern);
    std::string getPackageCPath(void) const;

    static void FunctionHook(lua_State *l, lua_Debug *ar);

    void setEnableStackTrace(bool Enable);

    bool getEnableStackTrace(void) const;

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

#ifdef OSG_WITH_LUA_DEBUGGER

	void setCallback(const boost::function<void (lua_details::LuaRunEvent, Int32)>& fn);

    typedef std::vector<unsigned char> ProgBuf;
	void dump(ProgBuf& program, bool debug);

	// execute
	Int32 call(void);

	// execute single line (current one) following calls, if any
	void stepInto(void);

	// execute current line, without entering any functions
	void stepOver(void);

	// start execution (it runs in a thread)
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
#endif
    /*==========================  PRIVATE  ================================*/
  private:

    static LuaManager* _the;

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    LuaErrorEventType _LuaErrorEvent;

    // Variables should all be in StubSoundManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaManager(void);
    LuaManager(const LuaManager &source);
    LuaManager& operator=(const LuaManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaManager(void); 

    /*! \}                                                                 */

    void printStackTrace(void) const;


    static lua_State *_State;
    std::list<std::string> _LuaStack;
    bool _EnableStackTrace;

    void produceLuaError(int Status);
    
    void produceLuaError(LuaErrorEventDetailsType* const e);

#ifdef OSG_WITH_LUA_DEBUGGER

    friend class lua_details::State;
	boost::scoped_ptr<lua_details::State> _DebState;

#endif
};

typedef LuaManager *LuaManagerP;

OSG_END_NAMESPACE

#include "OSGLuaManager.inl"

#endif /* _OSGLUAMANAGER_H_ */

