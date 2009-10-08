
#ifndef _OSG_LUA_WRAP_H_
#define _OSG_LUA_WRAP_H_

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFieldContainerPtr.h>

#include "lua.hpp"

void push_FieldContainer_on_lua(lua_State* L, osg::FieldContainerPtr value);

#endif
