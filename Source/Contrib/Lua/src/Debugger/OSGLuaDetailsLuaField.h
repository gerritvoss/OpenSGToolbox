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

#ifndef _OSGLUADETAILSLUAFIELD_H_
#define _OSGLUADETAILSLUAFIELD_H_
#ifdef __sgi
#pragma once
#endif


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#ifdef OSG_WITH_LUA_DEBUGGER

#include "OSGLuaDetailsValue.h"
#include <vector>

OSG_BEGIN_NAMESPACE

namespace lua_details
{

    /*! \brief LuaDebugger class. See \ref 
      PageSoundLuaDebugger for a description.
      */
    class OSG_CONTRIBLUA_DLLMAPPING LuaField	// table entry
    {
      public:
        const Value& getKey  (void) const;
        const Value& getValue(void) const;

        LuaField(const Value& Key,
                 const Value& Value);

        bool operator==(const LuaField& Right) const;

      private:
        Value _Key;
        Value _Value;
    };

    typedef std::vector<LuaField> TableInfo;
    typedef std::vector<LuaField> FieldStack;
}


OSG_END_NAMESPACE

#include "OSGLuaDetailsLuaField.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADETAILSLUAFIELD_H_ */

