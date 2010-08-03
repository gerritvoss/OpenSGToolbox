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
OSG_BEGIN_NAMESPACE

inline
SetFieldValueCommand::SetFieldValueCommand(FieldContainer* FC, UInt32 FieldId, const std::string& Value, UInt32 Index) : Inherited(FC, FieldId),
_Index(Index),
_Value(Value),
_PrevValue("")
{
}

inline
SetFieldValueCommand::SetFieldValueCommand(FieldContainer* FC, UInt32 FieldId, const std::string& Value, const std::string& PrevValue, UInt32 Index) : Inherited(FC, FieldId),
_Index(Index),
_Value(Value),
_PrevValue(PrevValue)
{
}

inline
SetFieldValueCommand::SetFieldValueCommand(const SetFieldValueCommand& source) : Inherited(source),
_Index(source._Index),
_Value(source._Value)
{
}

inline 
const CommandType &SetFieldValueCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
