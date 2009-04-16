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
#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGCommandManager.h"
#include "OSGUndoableCommand.h"

#include <boost/bind.hpp>

OSG_USING_NAMESPACE

void CommandManager::produceCommandExecuted(CommandPtr TheCommand)
{
	CommandEvent e(NullFC, getSystemTime(), TheCommand);
	CommandListenerSet Listeners(_CommandListeners);
	for(CommandListenerSet::const_iterator SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->commandExecuted(e);
    }
	if(_UndoManager != NULL && 
		TheCommand->getType().isDerivedFrom(UndoableCommand::getClassType()))
	{
        UndoableEditEvent Event(e.getSource(), e.getTimeStamp(), UndoableCommand::dcast(TheCommand));
		_UndoManager->undoableEditHappened(Event);
	}
}

EventConnection CommandManager::addCommandListener(CommandListenerPtr Listener)
{
   _CommandListeners.insert(Listener);
   return EventConnection(
       boost::bind(&CommandManager::isCommandListenerAttached, this, Listener),
       boost::bind(&CommandManager::removeCommandListener, this, Listener));
}


bool CommandManager::isCommandListenerAttached(CommandListenerPtr Listener) const
{
    return _CommandListeners.find(Listener) != _CommandListeners.end();
}

void CommandManager::removeCommandListener(CommandListenerPtr Listener)
{
	CommandListenerSet::iterator EraseIter(_CommandListeners.find(Listener));
   if(EraseIter != _CommandListeners.end())
   {
      _CommandListeners.erase(EraseIter);
   }
}

void CommandManager::executeCommand(CommandPtr TheCommand)
{
	TheCommand->execute();
	produceCommandExecuted(TheCommand);

}

CommandManagerPtr CommandManager::create(UndoManagerPtr UndoManager)
{
	return CommandManagerPtr(new CommandManager(UndoManager));
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CommandManager::CommandManager(UndoManagerPtr UndoManager) : Inherited(),
								_UndoManager(UndoManager)
{
}
    

CommandManager::CommandManager(const CommandManager& source) : Inherited(source),
								_UndoManager(source._UndoManager)
{
}

void CommandManager::operator =(const CommandManager& source)
{
	Inherited::operator =(source);
	_UndoManager = source._UndoManager;
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CommandManager::~CommandManager(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

