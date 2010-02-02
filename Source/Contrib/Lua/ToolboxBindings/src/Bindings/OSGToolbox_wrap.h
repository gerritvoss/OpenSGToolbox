
#ifndef _OSGTOOLBOX_LUA_WRAP_H_
#define _OSGTOOLBOX_LUA_WRAP_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxLuaBindingsDef.h"

#include <lua.hpp>
#include <OpenSG/Lua/OSGLuaManager.h>

osg::LuaManager::OpenBoundLuaLibFunctor  OSG_TOOLBOXLUABINDINGSLIB_DLLMAPPING getOSGToolboxLuaBindingsLibFunctor(void);

#endif
