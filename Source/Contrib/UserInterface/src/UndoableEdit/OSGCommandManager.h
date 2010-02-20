/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSGCOMMANDMANAGER_H_
#define _OSGCOMMANDMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGCommand.h"
#include "OSGCommandListener.h"
#include "OSGEventConnection.h"
#include <set>
#include "OSGCommandManagerFields.h"
#include "OSGUndoManager.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CommandManager
{
    /*==========================  PUBLIC  =================================*/

  public :
	void executeCommand(CommandPtr TheCommand);
    
	EventConnection addCommandListener(CommandListenerPtr Listener);
	bool isCommandListenerAttached(CommandListenerPtr Listener) const;

    void removeCommandListener(CommandListenerPtr Listener);
	
	static CommandManagerPtr create(UndoManagerPtr UndoManager);
    /*=========================  PROTECTED  ===============================*/
    virtual ~CommandManager(void);
    

  protected:
	friend class Command;
  
    CommandManager(UndoManagerPtr UndoManager);

	CommandManager(const CommandManager& source);
	
    void operator =(const CommandManager& source);
    
    /*---------------------------------------------------------------------*/
	typedef std::set<CommandListenerPtr> CommandListenerSet;
	
    CommandListenerSet       _CommandListeners;
	UndoManagerPtr           _UndoManager;

    void produceCommandExecuted(CommandPtr TheCommand);
};

OSG_END_NAMESPACE

#endif /* _OSGCOMMANDMANAGER_H_ */
