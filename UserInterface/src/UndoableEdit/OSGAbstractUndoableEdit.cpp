/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractUndoableEdit.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractUndoableEdit
A AbstractUndoableEdit. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AbstractUndoableEdit::addEdit(const UndoableEditPtr anEdit)
{
	return false;
}

bool AbstractUndoableEdit::canRedo(void) const
{
	return _Alive && !_HasBeenDone;
}

bool AbstractUndoableEdit::canUndo(void) const
{
	return _Alive && _HasBeenDone;
}

void AbstractUndoableEdit::die(void)
{
	_Alive = false;
}

std::string AbstractUndoableEdit::getPresentationName(void) const
{
	return std::string("");
}

std::string AbstractUndoableEdit::getRedoPresentationName(void) const
{
	return std::string("Redo ") + getPresentationName();
}

std::string AbstractUndoableEdit::getUndoPresentationName(void) const
{
	return std::string("Undo ") + getPresentationName();
}

bool AbstractUndoableEdit::isSignificant(void) const
{
	return true;
}

void AbstractUndoableEdit::redo(void)
{
	if(canRedo())
	{
		_HasBeenDone = true;
	}
	else
	{
		throw CannotRedoException();
	}
}

bool AbstractUndoableEdit::replaceEdit(const UndoableEditPtr anEdit) const
{
	return false;
}

void AbstractUndoableEdit::undo(void)
{
	if(canUndo())
	{
		_HasBeenDone = false;
	}
	else
	{
		throw CannotUndoException();
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractUndoableEdit::AbstractUndoableEdit(void) : Inherited(),
				_Alive(true),
				_HasBeenDone(false)
{
}

AbstractUndoableEdit::AbstractUndoableEdit(const AbstractUndoableEdit& source) : Inherited(source),
				_Alive(source._Alive),
				_HasBeenDone(source._HasBeenDone)
{
}

void AbstractUndoableEdit::operator=(const AbstractUndoableEdit& source)
{
	Inherited::operator=(source);
	_Alive = source._Alive;
	_HasBeenDone = source._HasBeenDone;
}

AbstractUndoableEdit::~AbstractUndoableEdit(void)
{
}
/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

