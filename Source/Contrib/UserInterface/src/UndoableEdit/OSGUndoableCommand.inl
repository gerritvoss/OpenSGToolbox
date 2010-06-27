/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const CommandType &UndoableCommand::getClassType(void)
{
    return _Type;
}

inline
const Time& UndoableCommand::getTime(void) const
{
    return _ExecuteTime;
}

inline
const Time& UndoableCommand::getMaxReplaceTime(void)
{
    return _MaxReplaceTime;
}

inline
void UndoableCommand::setMaxReplaceTime(const Time& t)
{
    _MaxReplaceTime = t;
}

OSG_END_NAMESPACE
