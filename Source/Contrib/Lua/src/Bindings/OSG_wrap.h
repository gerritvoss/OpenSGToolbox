
#ifndef _OSG_LUA_WRAP_H_
#define _OSG_LUA_WRAP_H_

#include "OSGConfig.h"
#include "OSGFieldContainer.h"

#include "lua.hpp"

void OSG_CONTRIBLUA_DLLMAPPING push_FieldContainer_on_lua(lua_State* L, OSG::FieldContainerRefPtr value);

#endif
