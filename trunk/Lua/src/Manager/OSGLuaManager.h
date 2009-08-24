/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
 *   This class is a wrapper for FMOD::EventSystem class, it provides basic  *
 *   Operation such as loading an an FMod event data base, and loading evnets*
 *   in the database provided.                                               *
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

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

}

OSG_BEGIN_NAMESPACE

/*! \brief LuaManager class. See \ref 
           PageSoundLuaManager for a description.
*/

class OSG_LUALIB_DLLMAPPING LuaManager
{
  private:

    /*==========================  PUBLIC  =================================*/
  public:
      
    static LuaManager* the(void);

	static bool init(void);
	static bool uninit(void);

    void runScript(const std::string& Script);

    static void LuaManager::report_errors(lua_State *L, int status);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    static LuaManager* _the;

    // Variables should all be in StubSoundManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LuaManager(void);
    LuaManager(const LuaManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LuaManager(void); 

    /*! \}                                                                 */
    

    /*==========================  PRIVATE  ================================*/
  private:

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LuaManager &source);

    static lua_State *_State;
    
};

typedef LuaManager *LuaManagerP;

OSG_END_NAMESPACE

#include "OSGLuaManager.inl"

#endif /* _OSGLUAMANAGER_H_ */
