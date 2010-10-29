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

#ifndef _OSGINSERTCHARACTER_COMMAND_H_
#define _OSGINSERTCHARACTER_COMMAND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"


#include "OSGUndoableCommand.h"

#include "OSGTextDomLayoutManagerFields.h"
#include "OSGPlainDocumentFields.h"


OSG_BEGIN_NAMESPACE

class InsertCharacterCommand;
typedef boost::shared_ptr<InsertCharacterCommand> InsertCharacterCommandPtr;

class OSG_CONTRIBTEXTDOM_DLLMAPPING InsertCharacterCommand: public UndoableCommand
{
protected:

	enum 
    {
        LEFT           = 0,
        RIGHT          = 1,
        UP             = 2,
        DOWN           = 3,
        HOME           = 4,
        END            = 5,
        HOMEOFNEXTLINE = 6,
        PAGEUP         = 7,
        PAGEDOWN       = 8
    };

	typedef UndoableCommand Inherited;
	typedef InsertCharacterCommand Self;
	typedef InsertCharacterCommandPtr RefPtr;

    InsertCharacterCommand(TextDomLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel,char theCharacter,UInt32 line,UInt32 index);// here
	InsertCharacterCommand(const InsertCharacterCommand& source);

	void operator =(const InsertCharacterCommand& source);

	static CommandType _Type;
	
	virtual void execute(void);
	virtual std::string getPresentationName(void) const;
	virtual void redo(void);
	virtual void undo(void);

	TextDomLayoutManagerRefPtr _Manager;
	PlainDocumentRefPtr _TheDocumentModel;
	char _TheCharacter;
	UInt32 _theOriginalCaretIndex;
	UInt32 _theOriginalCaretLine;
	UInt32 numberOfLeadingSpaces;
	

public:

	virtual std::string getCommandDescription(void) const;

    virtual const CommandType &getType(void) const;
	
    static const CommandType &getClassType(void);

	virtual ~InsertCharacterCommand(void);
	
    static InsertCharacterCommandPtr create(TextDomLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel,char theCharacter,UInt32 line,UInt32 index);// here
};

OSG_END_NAMESPACE

#include "OSGInsertCharacterCommand.inl"

#endif /* _OSGINSERTCHARACTER_COMMAND_H_ */
