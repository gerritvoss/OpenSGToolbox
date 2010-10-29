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

#include "OSGDeleteCharacterCommand.h"

#include "OSGElement.h"
#include "OSGGlyphView.h"
#include "OSGTextDomArea.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGPlainDocument.h"


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DeleteCharacterCommand
A DeleteCharacterCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType DeleteCharacterCommand::_Type("DeleteCharacterCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

DeleteCharacterCommandPtr DeleteCharacterCommand::create(TextDomLayoutManagerRefPtr Manager,PlainDocumentRefPtr DocumentModel)
{
	return RefPtr(new DeleteCharacterCommand(Manager,DocumentModel));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DeleteCharacterCommand::execute(void)
{
	DocumentElementAttribute temp;
	_theOriginalCaretIndex = _Manager->getCaretIndex();
	_theOriginalCaretLine = _Manager->getCaretLine();

	if(_theOriginalCaretLine+1 < _Manager->getRootElement()->getElementCount() || (_theOriginalCaretLine+1 == _Manager->getRootElement()->getElementCount() && !_Manager->isLastCharacterOfLine(_theOriginalCaretIndex,_theOriginalCaretLine)))
	{
		_TheCharacter = _Manager->getNextCharacter(_theOriginalCaretIndex,_theOriginalCaretLine);
		if(_Manager->isLastCharacterOfLine(_theOriginalCaretIndex,_theOriginalCaretLine))
		{
			_isLastCharacter = true;
		}

		_TheDocumentModel->deleteCharacter(_theOriginalCaretLine,_theOriginalCaretIndex);
	}
		
	_HasBeenDone = true;
}

std::string DeleteCharacterCommand::getCommandDescription(void) const
{
	return std::string("Delete Character ");
}

std::string DeleteCharacterCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void DeleteCharacterCommand::redo(void)
{

	_TheDocumentModel->deleteCharacter(_theOriginalCaretLine,_theOriginalCaretIndex);

	Inherited::redo();
}

void DeleteCharacterCommand::undo(void)
{
	if(_theOriginalCaretLine+1 < _Manager->getRootElement()->getElementCount() || (_theOriginalCaretLine+1 == _Manager->getRootElement()->getElementCount() && !_Manager->isLastCharacterOfLine(_theOriginalCaretIndex,_theOriginalCaretLine)))
	{
		DocumentElementAttribute temp;
		_Manager->setCaretIndexAndLine(_theOriginalCaretIndex,_theOriginalCaretLine);
	    
		if(_isLastCharacter)
		{
			_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,'\r',temp);
			_TheDocumentModel->insertCharacter(_theOriginalCaretIndex+1,_theOriginalCaretLine,'\n',temp);
			_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,_TheCharacter,temp);

			/*Manager->moveTheCaret(HOMEOFNEXTLINE,false,false);
			Manager->moveTheCaret(RIGHT,false,false);*/
		}
		else
		{
			_TheDocumentModel->insertCharacter(_theOriginalCaretIndex,_theOriginalCaretLine,_TheCharacter,temp);
		}

		_Manager->DoIfLineLongerThanPreferredSize();
	}
	Inherited::undo();
}

const CommandType &DeleteCharacterCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeleteCharacterCommand::~DeleteCharacterCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeleteCharacterCommand::operator =(const DeleteCharacterCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
    }
}

