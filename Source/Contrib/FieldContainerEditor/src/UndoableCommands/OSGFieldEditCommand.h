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

#ifndef _OSGFIELDEDITCOMMAND_H_
#define _OSGFIELDEDITCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGUndoableCommand.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

class FieldEditCommand;
typedef boost::shared_ptr<FieldEditCommand> FieldEditCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FieldEditCommand: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;
	typedef FieldEditCommandPtr RefPtr;

	FieldEditCommand(FieldContainer* FC, UInt32 FieldId);

	FieldEditCommand(const FieldEditCommand& source);

	void operator =(const FieldEditCommand& source);

	static CommandType _Type;

    FieldContainerRefPtr _FC;
    UInt32 _FieldId;

public:
	
    static const CommandType &getClassType(void);

	virtual ~FieldEditCommand(void);
};

OSG_END_NAMESPACE

#include "OSGFieldEditCommand.inl"

#endif /* _OSGFIELDEDITCOMMAND_H_ */
