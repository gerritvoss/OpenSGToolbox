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
#ifndef _OSGCREATEFIELDCONTAINERCOMMAND_H_
#define _OSGCREATEFIELDCONTAINERCOMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGCommand.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

class CreateFieldContainerCommand;
typedef boost::shared_ptr<CreateFieldContainerCommand> CreateFieldContainerCommandPtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING CreateFieldContainerCommand: public Command
{
protected:
	typedef Command Inherited;
	typedef CreateFieldContainerCommandPtr RefPtr;

    CreateFieldContainerCommand(const FieldContainerType* type);

	CreateFieldContainerCommand(const CreateFieldContainerCommand& source);

	void operator =(const CreateFieldContainerCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);

    FieldContainerUnrecPtr _CreatedFC;
    const FieldContainerType* _TypeToCreate;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~CreateFieldContainerCommand(void);

    FieldContainer* getContainer(void) const;
	
    static CreateFieldContainerCommandPtr create(const std::string& typeName);
    static CreateFieldContainerCommandPtr create(const FieldContainerType* type);
};

OSG_END_NAMESPACE

#include "OSGCreateFieldContainerCommand.inl"

#endif /* _OSGCREATEFIELDCONTAINERCOMMAND_H_ */
