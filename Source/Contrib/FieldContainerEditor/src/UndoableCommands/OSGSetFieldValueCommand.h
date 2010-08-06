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
#ifndef _OSGSETFIELDVALUECOMMAND_H_
#define _OSGSETFIELDVALUECOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditCommand.h"

OSG_BEGIN_NAMESPACE

class SetFieldValueCommand;
typedef boost::shared_ptr<SetFieldValueCommand> SetFieldValueCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING SetFieldValueCommand: public FieldEditCommand
{
protected:
	typedef FieldEditCommand Inherited;
	typedef SetFieldValueCommandPtr RefPtr;

    SetFieldValueCommand(FieldContainer* FC,
                         UInt32 FieldId,
                         const std::string& Value,
                         UInt32 Index = 0);

    SetFieldValueCommand(FieldContainer* FC,
                         UInt32 FieldId,
                         const std::string& Value,
                         const std::string& PrevValue,
                         UInt32 Index = 0);

	SetFieldValueCommand(const SetFieldValueCommand& source);

	void operator =(const SetFieldValueCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    UInt32 _Index;
    std::string _Value;
    std::string _PrevValue;
    FieldContainerUnrecPtr _PrevPtrValue;
    FieldContainerUnrecPtr _PtrValue;

public:
	virtual bool addEdit(const UndoableEditPtr anEdit);

	virtual bool replaceEdit(const UndoableEditPtr anEdit) const;
    
	virtual bool isSignificant(void) const;

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~SetFieldValueCommand(void);
	
	static SetFieldValueCommandPtr create(FieldContainer* FC,
                                          UInt32 FieldId,
                                          const std::string& Value,
                                          UInt32 Index = 0);

	static SetFieldValueCommandPtr create(FieldContainer* FC,
                                          UInt32 FieldId,
                                          const std::string& Value,
                                          const std::string& PrevValue,
                                          UInt32 Index = 0);
};

OSG_END_NAMESPACE

#include "OSGSetFieldValueCommand.inl"

#endif /* _OSGSETFIELDVALUECOMMAND_H_ */
