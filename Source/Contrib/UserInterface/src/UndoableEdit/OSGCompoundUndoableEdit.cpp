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

#include "OSGConfig.h"
#include <assert.h>

#include "OSGCompoundUndoableEdit.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CompoundUndoableEdit
A CompoundUndoableEdit. 
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

bool CompoundUndoableEdit::addEdit(const UndoableEditPtr anEdit)
{
	if(_IsInProgress)
	{
		if(_Edits.size() != 0)
		{
			if(anEdit->isSignificant() &&
               !_Edits.back()->addEdit(anEdit))
			{
				if(anEdit->replaceEdit(_Edits.back()))
				{
					_Edits.pop_back();
				}
				_Edits.push_back(anEdit);
                return true;
			}
		}
		else
		{
			_Edits.push_back(anEdit);
            return true;
		}
	}
    return false;
}

bool CompoundUndoableEdit::canRedo(void) const
{
	return Inherited::canRedo() && !_IsInProgress;
}

bool CompoundUndoableEdit::canUndo(void) const
{
	return Inherited::canUndo() && !_IsInProgress;
}

void CompoundUndoableEdit::die(void)
{
	for(EditVector::reverse_iterator Itor(_Edits.rbegin()) ; Itor != _Edits.rend() ; ++Itor)
	{
		(*Itor)->die();
	}
}

std::string CompoundUndoableEdit::getPresentationName(void) const
{
	if(_Edits.size() != 0)
	{
		return _Edits.back()->getPresentationName();
	}
	else
	{
		return Inherited::getPresentationName();
	}
}

std::string CompoundUndoableEdit::getRedoPresentationName(void) const
{
	if(_Edits.size() != 0)
	{
		return _Edits.back()->getRedoPresentationName();
	}
	else
	{
		return Inherited::getPresentationName();
	}
}

std::string CompoundUndoableEdit::getUndoPresentationName(void) const
{
	if(_Edits.size() != 0)
	{
		return _Edits.back()->getUndoPresentationName();
	}
	else
	{
		return Inherited::getPresentationName();
	}
}

bool CompoundUndoableEdit::isSignificant(void) const
{
	for(EditVector::const_iterator Itor(_Edits.begin()) ; Itor != _Edits.end() ; ++Itor)
	{
		if((*Itor)->isSignificant())
		{
			return true;
		}
	}
	return false;
}

void CompoundUndoableEdit::redo(void)
{
	for(EditVector::reverse_iterator Itor(_Edits.rbegin()) ; Itor != _Edits.rend() ; ++Itor)
	{
		(*Itor)->redo();
	}
}

void CompoundUndoableEdit::undo(void)
{
	for(EditVector::reverse_iterator Itor(_Edits.rbegin()) ; Itor != _Edits.rend() ; ++Itor)
	{
		(*Itor)->undo();
	}
}

bool CompoundUndoableEdit::isInProgress(void) const
{
	return _IsInProgress;
}

void CompoundUndoableEdit::end(void)
{
	_IsInProgress = false;
}

UndoableEditPtr CompoundUndoableEdit::lastEdit(void)
{
	return _Edits.back();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CompoundUndoableEdit::CompoundUndoableEdit(void) : Inherited(),
				_IsInProgress(true)
{
}

CompoundUndoableEdit::CompoundUndoableEdit(const CompoundUndoableEdit& source) : Inherited(source),
												_IsInProgress(source._IsInProgress),
												_Edits(source._Edits)
{
}

void CompoundUndoableEdit::operator=(const CompoundUndoableEdit& source)
{
	Inherited::operator=(source);
	_IsInProgress = source._IsInProgress;
	_Edits = source._Edits;
}

CompoundUndoableEdit::~CompoundUndoableEdit(void)
{
}

CompoundUndoableEditPtr CompoundUndoableEdit::create(void)
{
	return CompoundUndoableEditPtr(new CompoundUndoableEdit());
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

