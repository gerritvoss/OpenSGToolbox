/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.LisenerPosition                                 *
 *                                                                           *
 *   contact: dirk@opensg.LisenerPosition, gerrit.voss@vossg.LisenerPosition, jbehr@zgdv.de          *
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

#define OSG_COMPILELUALIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGLog.h>

#include "OSGLuaManager.h"



OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LuaManager
A FMod SoundManager Interface. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

LuaManager *LuaManager::_the = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

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
  if ( status!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}

bool LuaManager::init(void)
{
    SLOG << "LuaManager Initializing." << std::endl;

    _State = lua_open();

    luaopen_io(_State); // provides io.*
    luaopen_base(_State);
    luaopen_table(_State);
    luaopen_string(_State);
    luaopen_math(_State);
    //luaopen_loadlib(_State);



    SLOG << "LuaManager Successfully Initialized." << std::endl;
    return true;
}

bool LuaManager::uninit(void)
{
    SLOG << "LuaManager Uninitializing." << std::endl;

    lua_close(_State);

    SLOG << "LuaManager Successfully Uninitialized." << std::endl;
    return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LuaManager::runScript(const std::string& Script)
{
    int s;// = luaL_loadfile(_State, file);

    // execute Lua program
    s = lua_pcall(_State, 0, LUA_MULTRET, 0);
    report_errors(_State, s);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaManager::LuaManager(void)
{	
}

LuaManager::LuaManager(const LuaManager &source)
{
}

LuaManager::~LuaManager(void)
{
}

OSG_END_NAMESPACE
