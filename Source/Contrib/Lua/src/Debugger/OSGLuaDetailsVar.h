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

#ifndef _OSGLUADETAILSVAR_H_
#define _OSGLUADETAILSVAR_H_
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

OSG_BEGIN_NAMESPACE

namespace lua_details
{
    /*! \brief LuaDebugger class. See \ref 
      PageSoundLuaDebugger for a description.
      */

    class Var
    {
      public:
        const std::string& getName (void) const;
        const Value&       getValue(void) const;

        Var(const std::string& Name,
            const Value&       Value);

      private:
        std::string _Name;	// variable's identifier
        Value       _Value;
    };

}

OSG_END_NAMESPACE

#include "OSGLuaDetailsVar.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADETAILSVAR_H_ */

