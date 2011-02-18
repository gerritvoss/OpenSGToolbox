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

#ifndef _OSGLUADETAILSSTACKFRAME_H_
#define _OSGLUADETAILSSTACKFRAME_H_
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
#include "OSGBoostPathFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief LuaDebugger class. See \ref 
  PageSoundLuaDebugger for a description.
  */

namespace lua_details
{

    class StackFrame
    {
      public:
        enum Entry
        { 
            Err       = 0,
            LuaFun    = 1,
            MainChunk = 2,
            CFun      = 3,
            TailCall  = 4
        };


        // fill stack frame variable with info from Lua debug class
        void fill(const lua_Debug& dbg);

        void clear(void);

        BoostPath sourcePath(void) const;

        StackFrame(void);

        StackFrame(const lua_Debug& dbg);

             Entry        getType           (void) const;
       const std::string& getSource         (void) const;
       const std::string& getNameWhat       (void) const;
             UInt32       getCurrentLine    (void) const;
             UInt32       getLineDefined    (void) const;
             UInt32       getLastLineDefined(void) const;
      private:

        Entry       _Type;
        std::string _Source;
        std::string _NameWhat;
        UInt32      _CurrentLine;	// 1..N or 0 if not available

        // where it is defined (Lua fn)
        UInt32 _LineDefined;
        UInt32 _LastLineDefined;
    };
     
    typedef std::vector<StackFrame> CallStack;
}

OSG_END_NAMESPACE

#include "OSGLuaDetailsStackFrame.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADETAILSSTACKFRAME_H_ */

