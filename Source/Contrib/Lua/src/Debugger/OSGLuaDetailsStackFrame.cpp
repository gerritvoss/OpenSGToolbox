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
#include "OSGLuaDetailsStackFrame.h"

#ifdef OSG_WITH_LUA_DEBUGGER

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

// fill stack frame variable with info from Lua debug struct
void lua_details::StackFrame::fill(const lua_Debug& dbg)
{
	clear();

	_Source = dbg.source ? dbg.source : dbg.short_src;

	if (dbg.currentline > 0)
		_CurrentLine = dbg.currentline;

	if (dbg.what)
	{
		if (strcmp(dbg.what, "C") == 0)
			_Type = StackFrame::CFun;
		else if (strcmp(dbg.what, "Lua") == 0)
			_Type = StackFrame::LuaFun;
		else if (strcmp(dbg.what, "main") == 0)
			_Type = StackFrame::MainChunk;
		else if (strcmp(dbg.what, "tail") == 0)
			_Type = StackFrame::TailCall;
		else
			_Type = StackFrame::Err;
	}

	if (dbg.namewhat != 0 && *dbg.namewhat != '\0')	// is there a name?
		_NameWhat = dbg.name;

	_LastLineDefined = dbg.lastlinedefined;
	_LineDefined = dbg.linedefined;
}

lua_details::StackFrame::StackFrame(void)
{
    clear();
}

void lua_details::StackFrame::clear(void)
{
    _CurrentLine = 0;
    _Type = Err;
    _LineDefined = _LastLineDefined = 0;
}

BoostPath lua_details::StackFrame::sourcePath(void) const
{
    if (_Source.size() > 1 && _Source[0] == '@')
        return BoostPath(_Source.substr(1));

    return BoostPath();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
lua_details::StackFrame::StackFrame(const lua_Debug& dbg)
{
    fill(dbg);
}

OSG_END_NAMESPACE

#endif /* OSG_WITH_LUA_DEBUGGER */

