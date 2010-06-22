/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
#ifndef _OSGREMOVEFIELDELEMENTCOMMAND_H_
#define _OSGREMOVEFIELDELEMENTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditCommand.h"

OSG_BEGIN_NAMESPACE

class RemoveFieldElementCommand;
typedef boost::shared_ptr<RemoveFieldElementCommand> RemoveFieldElementCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING RemoveFieldElementCommand: public FieldEditCommand
{
protected:
	typedef FieldEditCommand Inherited;
	typedef RemoveFieldElementCommandPtr RefPtr;

    RemoveFieldElementCommand(FieldContainer* FC, UInt32 FieldId, UInt32 Index);

	RemoveFieldElementCommand(const RemoveFieldElementCommand& source);

	void operator =(const RemoveFieldElementCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    UInt32 _Index;
    std::string _RemovedValue;
    FieldContainerUnrecPtr _RemovedPtr;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~RemoveFieldElementCommand(void);
	
	static RemoveFieldElementCommandPtr create(FieldContainer* FC, UInt32 FieldId, UInt32 Index);
};

OSG_END_NAMESPACE

#include "OSGRemoveFieldElementCommand.inl"

#endif /* _OSGREMOVEFIELDELEMENTCOMMAND_H_ */
