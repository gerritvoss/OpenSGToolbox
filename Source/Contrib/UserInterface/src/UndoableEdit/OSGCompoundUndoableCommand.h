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

#ifndef _OSGCOMPOUNDUNDOABLECOMMAND_H_
#define _OSGCOMPOUNDUNDOABLECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGUndoableCommand.h"

OSG_BEGIN_NAMESPACE

class CompoundUndoableCommand;
typedef boost::shared_ptr<CompoundUndoableCommand> CompoundUndoableCommandPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CompoundUndoableCommand : public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
    typedef UndoableCommandPtr  Ptr;
    typedef CompoundUndoableCommand  Self;

	CompoundUndoableCommand(const std::vector <UndoableCommandPtr>& commands);

	CompoundUndoableCommand(const CompoundUndoableCommand& source);
	
    void operator =(const CompoundUndoableCommand& source);
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
    virtual std::string getCommandDescription(void) const;
	virtual void redo(void);
	virtual void undo(void);

    static CommandType _Type;

    std::vector <UndoableCommandPtr> _Commands;
public:
	static CompoundUndoableCommandPtr create(const std::vector <UndoableCommandPtr>& commands);
	
    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CompoundUndoableCommand(void);
};


OSG_END_NAMESPACE

#include "OSGCompoundUndoableCommand.inl"

#endif /* _OSGCOMPOUNDUNDOABLECOMMAND_H_ */
