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

#ifndef _OSGCOMMAND_H_
#define _OSGCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include <boost/shared_ptr.hpp>
#include "OSGCommandType.h"
#include "OSGCommandManagerFields.h"
#include <string>

OSG_BEGIN_NAMESPACE
 

class Command;
typedef boost::shared_ptr<Command> CommandPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Command
{
   /*=========================  PUBLIC  ===============================*/
protected:
	friend class CommandManager;

    typedef CommandPtr  Ptr;
    typedef Command  Self;

	Command(void);

	Command(const Command& source);
	
    void operator =(const Command& source);

	//This command should be overriden by sub-classes
	virtual void execute(void) = 0;

    static CommandType _Type;
public:

	//A human readable string that describes the command
	virtual std::string getCommandDescription(void) const = 0;
	
    virtual const CommandType &getType(void) const = 0;
	
    static const CommandType &getClassType(void);
	
	virtual ~Command(void);
};


OSG_END_NAMESPACE

#include "OSGCommand.inl"

#endif /* _OSGCOMMAND_H_ */
