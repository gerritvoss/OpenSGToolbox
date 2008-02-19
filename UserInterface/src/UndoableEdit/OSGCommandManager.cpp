#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGCommandManager.h"
#include "OSGUndoableCommand.h"

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
		_UndoManager->undoableEditHappened(UndoableEditEvent(e.getSource(), e.getTimeStamp(), UndoableCommand::dcast(TheCommand)));
	}
}

void CommandManager::addCommandListener(CommandListenerPtr Listener)
{
   _CommandListeners.insert(Listener);
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

