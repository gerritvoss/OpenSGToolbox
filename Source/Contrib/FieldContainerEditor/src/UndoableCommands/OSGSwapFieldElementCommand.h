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
#ifndef _OSGSWAPFIELDELEMENTCOMMAND_H_
#define _OSGSWAPFIELDELEMENTCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditCommand.h"

OSG_BEGIN_NAMESPACE

class SwapFieldElementCommand;
typedef boost::shared_ptr<SwapFieldElementCommand> SwapFieldElementCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING SwapFieldElementCommand: public FieldEditCommand
{
protected:
	typedef FieldEditCommand Inherited;
	typedef SwapFieldElementCommandPtr RefPtr;

    SwapFieldElementCommand(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex);

	SwapFieldElementCommand(const SwapFieldElementCommand& source);

	void operator =(const SwapFieldElementCommand& source);

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

	virtual ~SwapFieldElementCommand(void);
	
	static SwapFieldElementCommandPtr create(FieldContainer* FC, UInt32 FieldId, UInt32 FromIndex, UInt32 ToIndex);
};

OSG_END_NAMESPACE

#include "OSGSwapFieldElementCommand.inl"

#endif /* _OSGSWAPFIELDELEMENTCOMMAND_H_ */
