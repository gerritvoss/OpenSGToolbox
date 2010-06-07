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

#include "OSGCompoundUndoableCommand.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CompoundUndoableCommand
A CompoundUndoableCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CompoundUndoableCommand::_Type("CompoundUndoableCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const CommandType &CompoundUndoableCommand::getType(void) const
{
    return _Type;
}

CompoundUndoableCommandPtr CompoundUndoableCommand::create(const std::vector <UndoableCommandPtr>& commands)
{
    return CompoundUndoableCommandPtr(new CompoundUndoableCommand(commands));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

	
void CompoundUndoableCommand::execute(void)
{
    for(UInt32 i(0) ; i<_Commands.size() ; ++i)
    {
        _Commands[i]->execute();
    }
    
	_HasBeenDone = true;
}

std::string CompoundUndoableCommand::getCommandDescription(void) const
{
	return "Compound Command";
}

std::string CompoundUndoableCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void CompoundUndoableCommand::redo(void)
{
    Inherited::redo();

    for(UInt32 i(0) ; i<_Commands.size() ; ++i)
    {
        _Commands[i]->redo();
    }
}

void CompoundUndoableCommand::undo(void)
{
    Inherited::undo();
    for(Int32 i(_Commands.size()-1) ; i>=0 ; --i)
    {
        _Commands[i]->undo();
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CompoundUndoableCommand::CompoundUndoableCommand(const std::vector <UndoableCommandPtr>& commands) : Inherited(),
_Commands(commands)
{
}

CompoundUndoableCommand::CompoundUndoableCommand(const CompoundUndoableCommand& source) : Inherited(source)
{
}

void CompoundUndoableCommand::operator =(const CompoundUndoableCommand& source)
{
	Inherited::operator=(source);
}

CompoundUndoableCommand::~CompoundUndoableCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

