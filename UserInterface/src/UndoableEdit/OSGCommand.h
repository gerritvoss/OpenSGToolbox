/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>
#include "OSGCommandType.h"
#include "OSGCommandManagerFields.h"
#include <string>

OSG_BEGIN_NAMESPACE
 

class Command;
typedef boost::intrusive_ptr<Command> CommandPtr;

class OSG_USERINTERFACELIB_DLLMAPPING Command : public virtual IntrusivePtrImplBase
{
   /*=========================  PUBLIC  ===============================*/
protected:
	friend class CommandManager;

	typedef IntrusivePtrImplBase Inherited;
    typedef CommandPtr  Ptr;
    typedef Command  Self;

	Command(void);

	Command(const Command& source);
	
    void operator =(const Command& source);

	//This command should be overriden by sub-classes
	virtual void execute(void) = 0;
public:

	//A human readable string that describes the command
	virtual std::string getCommandDescription(void) const = 0;
	
    virtual const CommandType &getType(void) const = 0;
	
	virtual ~Command(void);

	template <class InTypeT> inline
	static Ptr dcast(InTypeT oIn)
	{
		return Ptr(dynamic_cast<typename Self *>(oIn.get()));
	}
};


OSG_END_NAMESPACE

#include "OSGCommand.inl"

#endif /* _OSGCOMMAND_H_ */
