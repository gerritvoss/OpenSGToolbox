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
#include "OSGCommandManagerFields.h"
#include "OSGUndoManager.h"
#include "OSGCommandEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CommandManager
{
    /*==========================  PUBLIC  =================================*/

  public :
    typedef CommandEventDetails CommandExecutedEventDetailsType;
    typedef boost::signals2::signal<void (CommandExecutedEventDetailsType* const, UInt32), ConsumableEventCombiner> CommandExecutedEventType;

    enum
    {
        CommandExecutedEventId = 1,
        NextEventId     = CommandExecutedEventId            + 1
    };
    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 
    virtual const EventProducerType &getProducerType(void) const; 

    boost::signals2::connection          attachActivity(UInt32 eventId,
                                                       Activity* TheActivity);
    UInt32                   getNumProducedEvents(void)          const;
    const EventDescription *getProducedEventDescription(const   Char8 *ProducedEventName) const;
    const EventDescription *getProducedEventDescription(UInt32  ProducedEventId) const;
    UInt32                   getProducedEventId(const            Char8 *ProducedEventName) const;

    boost::signals2::connection connectCommandExecuted(const CommandExecutedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    boost::signals2::connection connectCommandExecuted(const CommandExecutedEventType::group_type &group,
                                                       const CommandExecutedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    void   disconnectCommandExecuted       (const CommandExecutedEventType::group_type &group);
    void   disconnectAllSlotsCommandExecuted(void);
    bool   isEmptyCommandExecuted          (void) const;
    UInt32 numSlotsCommandExecuted         (void) const;

	void executeCommand(CommandPtr TheCommand);
	
	static CommandManagerPtr create(UndoManagerPtr UndoManager);
    /*=========================  PROTECTED  ===============================*/
    virtual ~CommandManager(void);
    

  protected:
	friend class Command;
  
    CommandManager(UndoManagerPtr UndoManager);

	CommandManager(const CommandManager& source);
	
    void operator =(const CommandManager& source);
    
    /*---------------------------------------------------------------------*/
	UndoManagerPtr           _UndoManager;

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    CommandExecutedEventType _CommandExecutedEvent;
    
    void produceCommandExecuted(CommandExecutedEventDetailsType* const e);
};

OSG_END_NAMESPACE

#include "OSGCommandManager.inl"

#endif /* _OSGCOMMANDMANAGER_H_ */
