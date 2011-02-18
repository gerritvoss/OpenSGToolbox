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

#ifndef _OSGLUADETAILSBREAKPOINT_H_
#define _OSGLUADETAILSBREAKPOINT_H_
#ifdef __sgi
#pragma once
#endif


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include "OSGConfig.h"
#include "OSGContribLuaDef.h"

#ifdef OSG_WITH_LUA_DEBUGGER

#include "OSGBaseTypes.h"
#include <map>

OSG_BEGIN_NAMESPACE

namespace lua_details
{

    enum Breakpoint
    {
        BPT_NONE	= 0x00,		// nie ma przerwania
        BPT_EXECUTE	= 0x01,		// przerwanie przy wykonaniu
        BPT_READ	= 0x02,		// przerwanie przy odczycie
        BPT_WRITE	= 0x04,		// przerwanie przy zapisie
        BPT_MASK	= 0x07,
        BPT_NO_CODE	= 0x08,		// wiersz nie zawiera kodu - przerwanie nie mo¿e byæ ustawione
        BPT_TEMP_EXEC=0x10,		// przerwanie tymczasowe do zatrzymania programu
        BPT_DISABLED= 0x80		// przerwanie wy³¹czone
    };

    typedef std::map<UInt32, Breakpoint> BreakpointMap;
    typedef std::map<std::string, BreakpointMap> FileBreakpointMap;

}

OSG_END_NAMESPACE

#include "OSGLuaDetailsBreakpoint.inl"

#endif /* OSG_WITH_LUA_DEBUGGER */

#endif /* _OSGLUADETAILSBREAKPOINT_H_ */

