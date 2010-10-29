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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILETEXTDOMLIB

#include "OSGConfig.h"

#include "OSGInsertCharacterCommand.h"

#include "OSGElement.h"
#include "OSGGlyphView.h"
#include "OSGTextDomArea.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGPlainDocument.h"


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::InsertCharacterCommand
A InsertCharacterCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType InsertCharacterCommand::_Type("InsertCharacterCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

InsertCharacterCommandPtr InsertCharacterCommand::create(TextDomLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel,char theCharacter,UInt32 line,UInt32 index)
{
	return RefPtr(new InsertCharacterCommand(Manager,DocumentModel,theCharacter,line,index));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void InsertCharacterCommand::execute(void)
{
	DocumentElementAttribute temp;
	if(_theOriginalCaretLine == -1 || _theOriginalCaretIndex == -1)
	{
		_theOriginalCaretIndex = _Manager->getCaretIndex();
		_theOriginalCaretLine = _Manager->getCaretLine();
	}

	if(_TheCharacter == '\n')
	{
		numberOfLeadingSpaces = _Manager->getNumberOfLeadingSpaces(_theOriginalCaretLine);
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,'\r',temp);
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex+1,_theOriginalCaretLine ,'\n',temp);

		Int32 i,count;
		for(i = _theOriginalCaretIndex+2,count=0;count<numberOfLeadingSpaces;count++,i++)
			_TheDocumentModel->insertCharacter(count,_theOriginalCaretLine+1,' ',temp);

		_Manager->moveTheCaret(HOMEOFNEXTLINE,false,false);

		for(count=0;count<numberOfLeadingSpaces;count++)
			_Manager->moveTheCaret(RIGHT,false,false);
	}
	else
	{
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,_TheCharacter,temp);
		_Manager->moveTheCaret(RIGHT,false,false);
		_Manager->DoIfLineLongerThanPreferredSize();
	}

	_HasBeenDone = true;
}

std::string InsertCharacterCommand::getCommandDescription(void) const
{
	return std::string("Insert Character ");
}

std::string InsertCharacterCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void InsertCharacterCommand::redo(void)
{
	DocumentElementAttribute temp;
	_Manager->setCaretIndexAndLine(_theOriginalCaretIndex,_theOriginalCaretLine);

    if(_TheCharacter == '\n')
	{
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,'\r',temp);
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex+1,_theOriginalCaretLine ,'\n',temp);

		Int32 i,count;
		for(count=0;count<numberOfLeadingSpaces;count++)
			_TheDocumentModel->insertCharacter(count,_theOriginalCaretLine+1,' ',temp);

		_Manager->moveTheCaret(HOMEOFNEXTLINE,false,false);

		for(count=0;count<numberOfLeadingSpaces;count++)
			_Manager->moveTheCaret(RIGHT,false,false);
	}
	else
	{
		_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,_TheCharacter,temp);
		_Manager->moveTheCaret(RIGHT,false,false);
		_Manager->DoIfLineLongerThanPreferredSize();
	}

	Inherited::redo();
}

void InsertCharacterCommand::undo(void)
{
	_Manager->setCaretIndexAndLine(_theOriginalCaretIndex,_theOriginalCaretLine);

	if(_TheCharacter == '\n')
	{
		for(UInt32 i=0;i<numberOfLeadingSpaces+1;i++)	
		{
			//_Manager->moveTheCaret(LEFT,false,false);
			_TheDocumentModel->deleteCharacter(_Manager->getCaretLine(),_Manager->getCaretIndex());
		}
	}
	else
	{
		_TheDocumentModel->deleteCharacter(_theOriginalCaretLine,_theOriginalCaretIndex);
	}

	Inherited::undo();
}

const CommandType &InsertCharacterCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InsertCharacterCommand::~InsertCharacterCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InsertCharacterCommand::operator =(const InsertCharacterCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
    }
}

