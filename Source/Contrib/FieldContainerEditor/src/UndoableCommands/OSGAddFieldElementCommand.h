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
#ifndef _OSGADDFIELDELEMENTCOMMAND_H_
#define _OSGADDFIELDELEMENTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditCommand.h"

OSG_BEGIN_NAMESPACE

class AddFieldElementCommand;
typedef boost::shared_ptr<AddFieldElementCommand> AddFieldElementCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING AddFieldElementCommand: public FieldEditCommand
{
protected:
	typedef FieldEditCommand Inherited;
	typedef AddFieldElementCommandPtr RefPtr;

    AddFieldElementCommand(FieldContainer* FC, UInt32 FieldId, const std::string& Value);

	AddFieldElementCommand(const AddFieldElementCommand& source);

	void operator =(const AddFieldElementCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    std::string _Value;
    FieldContainerUnrecPtr _AddedPtr;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~AddFieldElementCommand(void);
	
	static AddFieldElementCommandPtr create(FieldContainer* FC, UInt32 FieldId, const std::string& Value);
};

OSG_END_NAMESPACE

#include "OSGAddFieldElementCommand.inl"

#endif /* _OSGADDFIELDELEMENTCOMMAND_H_ */
