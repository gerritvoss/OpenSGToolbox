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

#ifdef OSG_WITH_LUA_DEBUGGER

OSG_BEGIN_NAMESPACE

inline
lua_details::StackFrame::Entry lua_details::StackFrame::getType(void) const
{
    return _Type;
}

inline
const std::string& lua_details::StackFrame::getSource(void) const
{
    return _Source;
}

inline
const std::string& lua_details::StackFrame::getNameWhat(void) const
{
    return _NameWhat;
}

inline
UInt32 lua_details::StackFrame::getCurrentLine(void) const
{
    return _CurrentLine;
}

inline
UInt32 lua_details::StackFrame::getLineDefined(void) const
{
    return _LineDefined;
}

inline
UInt32 lua_details::StackFrame::getLastLineDefined(void) const
{
    return _LastLineDefined;
}

OSG_END_NAMESPACE

#endif /* OSG_WITH_LUA_DEBUGGER */

