
#ifndef _OSGTOOLBOX_LUA_WRAP_H_
#define _OSGTOOLBOX_LUA_WRAP_H_

#include "OSGConfig.h"
#include "OSGContribLuaToolboxDef.h"

#include <lua.hpp>
#include "OSGLuaManager.h"

OSG::LuaManager::OpenBoundLuaLibFunctor  OSG_CONTRIBLUATOOLBOX_DLLMAPPING getOSGToolboxLuaBindingsLibFunctor(void);

#endif
