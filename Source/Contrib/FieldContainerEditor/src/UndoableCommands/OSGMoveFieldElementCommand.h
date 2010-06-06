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
#ifndef _OSGMOVEFIELDELEMENTCOMMAND_H_
#define _OSGMOVEFIELDELEMENTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditCommand.h"

OSG_BEGIN_NAMESPACE

class MoveFieldElementCommand;
typedef boost::shared_ptr<MoveFieldElementCommand> MoveFieldElementCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MoveFieldElementCommand: public FieldEditCommand
{
protected:
	typedef FieldEditCommand Inherited;
	typedef MoveFieldElementCommandPtr RefPtr;

    MoveFieldElementCommand(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex);

	MoveFieldElementCommand(const MoveFieldElementCommand& source);

	void operator =(const MoveFieldElementCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

    UInt32 _FromIndex;
    UInt32 _ToIndex;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~MoveFieldElementCommand(void);
	
	static MoveFieldElementCommandPtr create(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex);
};

OSG_END_NAMESPACE

#include "OSGMoveFieldElementCommand.inl"

#endif /* _OSGMOVEFIELDELEMENTCOMMAND_H_ */
