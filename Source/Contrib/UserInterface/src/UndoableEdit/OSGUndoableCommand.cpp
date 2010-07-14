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

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGUndoableCommand.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::UndoableCommand
A UndoableCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType UndoableCommand::_Type          ("UndoableCommand", "Command");
Time        UndoableCommand::_MaxReplaceTime(5.0                         );

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const CommandType &UndoableCommand::getType(void) const
{
    return _Type;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UndoableCommand::execute(void)
{
    _ExecuteTime = getSystemTime();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UndoableCommand::UndoableCommand(void) : Inherited1(), Inherited2()
{
}

UndoableCommand::UndoableCommand(const UndoableCommand& source) : Inherited1(source), Inherited2(source)
{
}

void UndoableCommand::operator =(const UndoableCommand& source)
{
	Inherited1::operator=(source);
	Inherited2::operator=(source);
}

UndoableCommand::~UndoableCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

