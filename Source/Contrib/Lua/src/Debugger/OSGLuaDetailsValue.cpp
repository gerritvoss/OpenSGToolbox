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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "OSGConfig.h"

#ifdef OSG_WITH_LUA_DEBUGGER
#include "OSGLuaDetailsValue.h"
#include "OSGLuaDetailsLuaField.h"
#include "OSGLuaUtils.h"
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

// store information about Lua value present at the 'index' inside 'v' struct
void lua_details::Value::capture(lua_State* L, int index, int recursive, size_t table_size_limit)
{
	int i= index;

	int t= lua_type(L, i);

	switch (t)
	{
	case LUA_TSTRING:
		_Type = String;
		_Value = lua_tostring(L, i);
		break;

	case LUA_TBOOLEAN:
		_Type = Bool;
		_Value = lua_toboolean(L, i) ? "true" : "false";
		break;

	case LUA_TNUMBER:
		_Type = Number;
        _Value = boost::lexical_cast<std::string>(lua_tonumber(L, i));
		break;

	case LUA_TLIGHTUSERDATA:
		_Type = LightUserData;
        _Value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TUSERDATA:
		_Type = UserData;
		_Value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TTABLE:
		_Type = Table;
		if (recursive > 0)
		{
			TableInfo t;
			listTable(L, i, t, recursive - 1);
			_Value = tableAsString(t, table_size_limit);
		}
		else
			_Value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TFUNCTION:
		_Type = Function;
		_Value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TTHREAD:
		_Type = Thread;
		_Value = "0x" + boost::lexical_cast<std::string>(lua_topointer(L, i));
		break;

	case LUA_TNIL:
		_Type = Nil;
		_Value.clear();
		break;

	default:
		_Type = None;
		_Value.clear();
		break;
	}

	_TypeName = lua_typename(L, t);
}

bool lua_details::Value::push(lua_State* L) const
{
	switch (_Type)
	{
	case Nil:
        lua_pushnil(L);
        return true;
		break;
	case Bool:
        lua_pushboolean(L, boost::lexical_cast<bool>(_Value));
        return true;
		break;
	case LightUserData:
        lua_pushlightuserdata(L, boost::lexical_cast<void*>(_Value));
        return true;
		break;
	case Number:
        lua_pushnumber(L, boost::lexical_cast<lua_Number>(_Value));
        return true;
		break;
	case String:
        lua_pushstring(L, _Value.c_str());
        return true;
		break;
	case Table:
        assert(false && "NYI");
        return false;
		break;
	case Function:
        assert(false && "NYI");
        //lua_pushcfunction(L, boost::lexical_cast<void*>(_Value));
        return false;
		break;
	case UserData:
        assert(false && "NYI");
        //lua_pushuserdata(L, boost::lexical_cast<void*>(_Value));
        return false;
		break;
	case Thread:
        assert(false && "NYI");
        //lua_pushthread(L, boost::lexical_cast<void*>(_Value));
        return false;
		break;

	case None:
	default:
        assert(false && "Can't push UNKNOWN type");
        return false;
		break;
	}
    return true;
}

bool lua_details::Value::operator==(const Value& Right) const
{
    return (_Type == Right._Type && _Value.compare(Right._Value) == 0);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

lua_details::Value::Value(      ValType      Type,
                          const std::string& Typename,
                          const std::string& Value) :
    _Type(Type),
    _TypeName(Typename),
    _Value(Value)
{
}

lua_details::Value::Value(lua_State* L,
                          int        index,
                          int        recursive,
                          size_t     table_size_limit)
{
    capture(L, index, recursive, table_size_limit);
}

OSG_END_NAMESPACE

#endif /* OSG_WITH_LUA_DEBUGGER */

