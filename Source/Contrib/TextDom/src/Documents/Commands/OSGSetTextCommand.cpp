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

#include "OSGSetTextCommand.h"

#include "OSGNameAttachment.h"


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::SetTextCommand
A SetTextCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType SetTextCommand::_Type("SetTextCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SetTextCommandPtr SetTextCommand::create(PlainDocumentLeafElementRefPtr element,std::string newString)
{
	return RefPtr(new SetTextCommand(element,newString));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SetTextCommand::execute(void)
{
	if(_TheElement)
	{
		_TheOriginalString = _TheElement->getText();
		_TheElement->setText(_TheNewString);
	}
	_HasBeenDone = true;
}

std::string SetTextCommand::getCommandDescription(void) const
{
	return std::string("Set Text");
}

std::string SetTextCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void SetTextCommand::redo(void)
{
	if(_TheElement)
	{
		_TheElement->setText(_TheNewString);
	}
	Inherited::redo();
}

void SetTextCommand::undo(void)
{
	if(_TheElement)
	{
		_TheElement->setText(_TheOriginalString);
	}
	Inherited::undo();
}

const CommandType &SetTextCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SetTextCommand::~SetTextCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SetTextCommand::operator =(const SetTextCommand& source)
{
    if(this != &source)
    {
	    Inherited::operator=(source);
    }
}

