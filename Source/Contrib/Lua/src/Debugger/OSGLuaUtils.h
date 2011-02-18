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

#ifndef _OSGLUAUTILS_H_
#define _OSGLUAUTILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#include "OSGBaseTypes.h"
#include "OSGLuaDetailsLuaField.h"
#include "lua.hpp"
#include <boost/function.hpp>
#include <vector>
#include <map>

#ifdef OSG_WITH_LUA_DEBUGGER

OSG_BEGIN_NAMESPACE

namespace lua_details
{
    /**********************************************************************//**
     * Class for automating poping off lua stack elements.
     *
     * Instances of this class are constructed with a lua state and a number of
     * stack elements.  When the instance is destroyed, the number of stack 
     * elements is popped off of the stack of the given lua state.
     *
     *************************************************************************/
    class OSG_CONTRIBLUA_DLLMAPPING popStackElements
    {
      public:
        popStackElements(lua_State* L, int num);

        void dec(void);

        ~popStackElements(void);

      private:
        popStackElements(void);
        popStackElements(const popStackElements&);

        lua_State* L_;
        int num_;
    };

    /**********************************************************************//**
     *  Fills a TableInfo object with the fields of a lua table that is 
     *  on the lua stack.
     *
     * @param L A Lua state
     * @param idx Index of the lua table on the lua stack
     * @param out The TableInfo object to fill with the result
     * @param recursive Amount of recursive steps to take for fields that are 
     *        tables
     *************************************************************************/
    bool OSG_CONTRIBLUA_DLLMAPPING listTable(lua_State* L, int idx, TableInfo& out, int recursive= 0);

    /**********************************************************************//**
     * Get the number of fields in a lua table
     *
     * @param L A Lua state
     * @param idx The index of the lua table
     *
     * @return The number of fields present in the table
     *
     *************************************************************************/
    UInt32 OSG_CONTRIBLUA_DLLMAPPING getNumFields(lua_State* L, int idx);

    /**********************************************************************//**
     * Formats a string with the contents of a TableInfo object representing
     * a lua table
     *
     * @param table A TableInfo object representing a lua table
     * @param limit Maximum number of fields in the table to print
     *
     *************************************************************************/
    std::string OSG_CONTRIBLUA_DLLMAPPING tableAsString(const TableInfo& table, size_t limit);

    /**********************************************************************//**
     * Fills a ValueStack with the contents of the lua stack
     *
     * @param L A lua state
     * @param stack The object to fill with the result
     * @param table_size_limit The maximum number of elements of the lua stack
     * to grab
     *
     * @return True if successful
     *
     *************************************************************************/
    bool OSG_CONTRIBLUA_DLLMAPPING listVirtualStack(lua_State* L, ValueStack& stack, size_t table_size_limit);
    
    /**********************************************************************//**
     * Push a table onto the top of the lua stack
     *
     * @param L A lua state
     * @param PathToField Path from the global table to the field. If empty, the
     * global table is pushed onto the stack
     *
     * @return True if successful
     *
     *************************************************************************/
    bool OSG_CONTRIBLUA_DLLMAPPING pushFieldOntoStack(lua_State* L,
                                                      const FieldStack& PathToField);


}

OSG_END_NAMESPACE

#include "OSGLuaUtils.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUAUTILS_H_ */

