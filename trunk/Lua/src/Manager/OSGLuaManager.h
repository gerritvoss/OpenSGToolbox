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

#include <OpenSG/OSGConfig.h>
#include "OSGLuaDef.h"

#include "lua.hpp"
#include <set>
#include <list>
#include "Events/OSGLuaListener.h"

#include <OpenSG/Toolbox/OSGEventConnection.h>
#include <OpenSG/Toolbox/OSGEventProducer.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
#include <OpenSG/Toolbox/OSGMethodDescription.h>

OSG_BEGIN_NAMESPACE

/*! \brief LuaManager class. See \ref 
           PageSoundLuaManager for a description.
*/

class OSG_LUALIB_DLLMAPPING LuaManager : public EventProducer
{
  private:
      typedef EventProducer ProducerInherited;

    /*==========================  PUBLIC  =================================*/
  public:
    enum
    {
        LuaErrorMethodId      = ProducerInherited::NextMethodId,
        NextMethodId              = LuaErrorMethodId            + 1
    };
      
    static LuaManager* the(void);


    void runScript(const std::string& Script);

    static void report_errors(lua_State *L, int status);

	static bool init(void);
	static bool uninit(void);

    EventConnection addLuaListener(LuaListenerPtr Listener);
    bool isLuaListenerAttached(LuaListenerPtr Listener) const;
    void removeLuaListener(LuaListenerPtr Listener);
    
    static void FunctionHook(lua_State *l, lua_Debug *ar);

    void setEnableStackTrace(bool Enable);

    bool getEnableStackTrace(void) const;

    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 
    virtual const EventProducerType &getProducerType(void) const; 
    /*==========================  PRIVATE  ================================*/
  private:

    static LuaManager* _the;

    static MethodDescription   *_methodDesc[];
    static EventProducerType _producerType;

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
    
	typedef std::set<LuaListenerPtr> LuaListenerSet;
    typedef LuaListenerSet::iterator LuaListenerSetItor;
    typedef LuaListenerSet::const_iterator LuaListenerSetConstItor;
    LuaListenerSet       _LuaListeners;
    std::list<std::string> _LuaStack;
    bool _EnableStackTrace;
        
    void checkError(int Status);
    void produceError(int Status);
};

typedef LuaManager *LuaManagerP;

OSG_END_NAMESPACE

#include "OSGLuaManager.inl"

#endif /* _OSGLUAMANAGER_H_ */
