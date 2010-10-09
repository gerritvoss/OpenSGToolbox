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

#ifndef _OSGDELETECHARACTER_COMMAND_H_
#define _OSGDELETECHARACTER_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"


#include "OSGUndoableCommand.h"

#include "OSGFixedHeightLayoutManager.h"
#include "OSGPlainDocument.h"


OSG_BEGIN_NAMESPACE

class DeleteCharacterCommand;
typedef boost::shared_ptr<DeleteCharacterCommand> DeleteCharacterCommandPtr;

class OSG_CONTRIBTEXTDOM_DLLMAPPING DeleteCharacterCommand: public UndoableCommand
{
protected:

	enum {LEFT,RIGHT,UP,DOWN,HOME,END,HOMEOFNEXTLINE,PAGEUP,PAGEDOWN};

	typedef UndoableCommand Inherited;
	typedef DeleteCharacterCommand Self;
	typedef DeleteCharacterCommandPtr RefPtr;

    DeleteCharacterCommand(FixedHeightLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel);// here
	DeleteCharacterCommand(const DeleteCharacterCommand& source);

	void operator =(const DeleteCharacterCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	FixedHeightLayoutManagerRefPtr _Manager;
	PlainDocumentRefPtr _TheDocumentModel;
	char _TheCharacter;
	UInt32 _theOriginalCaretIndex;
	UInt32 _theOriginalCaretLine;
	bool _isLastCharacter;

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~DeleteCharacterCommand(void);
	
    static DeleteCharacterCommandPtr create(FixedHeightLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel);// here
};

OSG_END_NAMESPACE

#include "OSGDeleteCharacterCommand.inl"

#endif /* _OSGDELETECHARACTER_COMMAND_H_ */
