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

#include "OSGDeleteSelectedCommand.h"

#include "OSGNameAttachment.h"


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DeleteSelectedCommand
A DeleteSelectedCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType DeleteSelectedCommand::_Type("DeleteSelectedCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

DeleteSelectedCommandPtr DeleteSelectedCommand::create(FixedHeightLayoutManagerRefPtr Manager,TextDomAreaRefPtr TheTextDomArea)
{
	return RefPtr(new DeleteSelectedCommand(Manager,TheTextDomArea));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DeleteSelectedCommand::execute(void)
{
	if(Manager->isStartLocationBeforeEndLocation())
	{
		old_HSI = Manager->getHSI();
		old_HSL = Manager->getHSL();
		old_HEI = Manager->getHEI();
		old_HEL = Manager->getHEL();
	}
	else 
	{
		old_HEI = Manager->getHSI();
		old_HEL = Manager->getHSL();
		old_HSI = Manager->getHEI();
		old_HSL = Manager->getHEL();
	}
	

	deletedString = _TextDomArea->getHighlightedString();
	Manager->deleteSelected();

	_HasBeenDone = true;
}

std::string DeleteSelectedCommand::getCommandDescription(void) const
{
	return std::string("Insert Character ");
}

std::string DeleteSelectedCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void DeleteSelectedCommand::redo(void)
{
	Manager->deleteSelected();
	Inherited::redo();
}

void DeleteSelectedCommand::undo(void)
{
	TextWithProps temp;

	Manager->setHSI(old_HSI);
	Manager->setHSL(old_HSL);
	Manager->setHEI(old_HEI);
	Manager->setHEL(old_HEL);
	
	_TextDomArea->getDocumentModel()->insertString(Manager->CaretLineAndIndexToCaretOffsetInDOM(old_HSL,old_HSI),deletedString,temp);

	Inherited::undo();
}

const CommandType &DeleteSelectedCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeleteSelectedCommand::~DeleteSelectedCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeleteSelectedCommand::operator =(const DeleteSelectedCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
    }
}

