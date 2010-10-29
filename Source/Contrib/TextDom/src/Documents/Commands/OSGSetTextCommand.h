/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

#ifndef _OSGSETTEXT_COMMAND_H_
#define _OSGSETTEXT_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"


#include "OSGUndoableCommand.h"

#include "OSGTextDomLayoutManagerFields.h"
#include "OSGPlainDocumentFields.h"


OSG_BEGIN_NAMESPACE

class SetTextCommand;
typedef boost::shared_ptr<SetTextCommand> SetTextCommandPtr;

class OSG_CONTRIBTEXTDOM_DLLMAPPING SetTextCommand: public UndoableCommand
{
protected:

	typedef UndoableCommand Inherited;
	typedef SetTextCommand Self;
	typedef SetTextCommandPtr RefPtr;

	SetTextCommand(ElementRefPtr element,std::string newString);// here
	SetTextCommand(const SetTextCommand& source);

	void operator =(const SetTextCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	ElementRefPtr _TheElement;
	std::string _TheOriginalString;
	std::string _TheNewString;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~SetTextCommand(void);
	
    static SetTextCommandPtr create(ElementRefPtr element,std::string newString);// here
};

OSG_END_NAMESPACE

#include "OSGSetTextCommand.inl"

#endif /* _OSGSETTEXT_COMMAND_H_ */
