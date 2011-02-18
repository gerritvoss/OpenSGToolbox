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

#ifndef _OSGLUADETAILSVALUE_H_
#define _OSGLUADETAILSVALUE_H_
#ifdef __sgi
#pragma once
#endif


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#ifdef OSG_WITH_LUA_DEBUGGER

#include "lua.hpp"
#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief LuaDebugger class. See \ref 
  PageSoundLuaDebugger for a description.
  */
namespace lua_details
{
    class OSG_CONTRIBLUA_DLLMAPPING Value	// value on a virtual stack or elsewhere
    {
      public:

        enum ValType
        {
            None          = -1,
            Nil           =  0,
            Bool          =  1,
            LightUserData =  2,
            Number        =  3,
            String        =  4,
            Table         =  5,
            Function      =  6,
            UserData      =  7,
            Thread        =  8
        };
        
        Value(      ValType      Type,
              const std::string& Typename,
              const std::string& Value);

        Value(lua_State* L, int index, int recursive= 0, size_t table_size_limit= 10);

        /**********************************************************************//**
         * Push the value 
         *
         *************************************************************************/
        bool push(lua_State* L) const;

        // store information about Lua value present at the 'index'
        void capture(lua_State* L, int index, int recursive= 0, size_t table_size_limit= 10);

        bool operator==(const Value& Right) const;

              ValType      getType    (void) const;
        const std::string& getTypeName(void) const;
        const std::string& getValue   (void) const;// simplified string representation of value

      private:
        ValType     _Type;
        std::string _TypeName;
        std::string _Value;
    };

    typedef std::vector<Value> ValueStack;
}

OSG_END_NAMESPACE

#include "OSGLuaDetailsValue.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADETAILSVALUE_H_ */

