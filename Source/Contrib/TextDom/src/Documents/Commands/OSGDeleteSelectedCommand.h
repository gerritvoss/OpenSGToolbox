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

#ifndef _OSGDELETESELECTED_COMMAND_H_
#define _OSGDELETESELECTED_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"


#include "OSGUndoableCommand.h"

#include "OSGFixedHeightLayoutManager.h"
#include "OSGPlainDocument.h"
#include "OSGTextDomArea.h"

OSG_BEGIN_NAMESPACE

class DeleteSelectedCommand;
typedef boost::shared_ptr<DeleteSelectedCommand> DeleteSelectedCommandPtr;

class OSG_CONTRIBTEXTDOM_DLLMAPPING DeleteSelectedCommand: public UndoableCommand
{
protected:

	enum {LEFT,RIGHT,UP,DOWN,HOME,END,HOMEOFNEXTLINE,PAGEUP,PAGEDOWN};

	typedef UndoableCommand Inherited;
	typedef DeleteSelectedCommand Self;
	typedef DeleteSelectedCommandPtr RefPtr;

    DeleteSelectedCommand(FixedHeightLayoutManagerRefPtr Manager,TextDomAreaRefPtr TheTextDomArea);// here
	DeleteSelectedCommand(const DeleteSelectedCommand& source);

	void operator =(const DeleteSelectedCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	FixedHeightLayoutManagerRefPtr Manager;
	UInt32 old_HSI;
	UInt32 old_HSL;
	UInt32 old_HEI;
	UInt32 old_HEL;
	TextDomAreaRefPtr _TextDomArea;
	std::string deletedString;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~DeleteSelectedCommand(void);
	
    static DeleteSelectedCommandPtr create(FixedHeightLayoutManagerRefPtr Manager,TextDomAreaRefPtr TheTextDomArea);// here
};

OSG_END_NAMESPACE

#include "OSGDeleteSelectedCommand.inl"

#endif /* _OSGINSERTCHARACTER_COMMAND_H_ */
