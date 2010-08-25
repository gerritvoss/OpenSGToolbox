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

#include <iostream>

#include "OSGCommandManager.h"
#include "OSGUndoableCommand.h"
#include "OSGCommandEventDetails.h"
#include "OSGUndoableEditEventDetails.h"

#include <boost/bind.hpp>

OSG_USING_NAMESPACE

EventDescription *CommandManager::_eventDesc[] =
{
    new EventDescription("CommandExecuted", 
                          "CommandExecuted",
                          CommandExecutedEventId, 
                          FieldTraits<CommandExecutedEventDetailsType *>::getType(),
                          true,
                          NULL),
};

EventProducerType CommandManager::_producerType(
                                            "CommandManagerProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

const EventProducerType &CommandManager::getProducerType(void) const
{
    return _producerType;
}

void CommandManager::executeCommand(CommandPtr TheCommand)
{
	TheCommand->execute();
	CommandEventDetailsUnrecPtr Details = CommandEventDetails::create(NULL, getSystemTime(), TheCommand);

    produceCommandExecuted(Details);

	if(_UndoManager != NULL && 
		TheCommand->getType().isDerivedFrom(UndoableCommand::getClassType()))
	{
	    UndoableEditEventDetailsUnrecPtr UndoableDetails = UndoableEditEventDetails::create(NULL, Details->getTimeStamp(), boost::dynamic_pointer_cast<UndoableCommand>(TheCommand));
		_UndoManager->handleUndoableEditHappened(UndoableDetails);
	}

}

CommandManagerPtr CommandManager::create(UndoManagerPtr UndoManager)
{
	return CommandManagerPtr(new CommandManager(UndoManager));
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CommandManager::CommandManager(UndoManagerPtr UndoManager) :
								_UndoManager(UndoManager)
{
}
    

CommandManager::CommandManager(const CommandManager& source) :
								_UndoManager(source._UndoManager)
{
}

void CommandManager::operator =(const CommandManager& source)
{
	_UndoManager = source._UndoManager;
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CommandManager::~CommandManager(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

