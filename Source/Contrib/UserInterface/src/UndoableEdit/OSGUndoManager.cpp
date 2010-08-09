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

#include "OSGUndoManager.h"
#include "OSGUndoableEditEventDetails.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::UndoManager
A UndoManager. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


EventDescription *UndoManager::_eventDesc[] =
{
    new EventDescription("StateChanged", 
                          "StateChanged",
                          StateChangedEventId, 
                          FieldTraits<StateChangedEventDetailsType *>::getType(),
                          true,
                          NULL),
};

EventProducerType UndoManager::_producerType(
                                            "UndoManagerProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

const EventProducerType &UndoManager::getProducerType(void) const
{
    return _producerType;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UndoManager::produceStateChanged(void)
{
    ChangeEventDetailsUnrecPtr Details = ChangeEventDetails::create(NULL, getSystemTime());

    produceStateChanged(Details);
}

bool UndoManager::addEdit(const UndoableEditPtr anEdit)
{
	if(_IsInProgress)
	{
		trimEdits(_IndexOfNextAdd, _Edits.size()-1);
		Inherited::addEdit(anEdit);
		_IndexOfNextAdd = _Edits.size();

		trimForLimit();
		produceStateChanged();

		return true;
	}
	else
	{
		return Inherited::addEdit(anEdit);
	}
}

bool UndoManager::canRedo(void) const
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeRedone();
		return edit != NULL && edit->canRedo();
	}
	else
	{
		return Inherited::canRedo();
	}
}

bool UndoManager::canUndo(void) const
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeUndone();
		return edit != NULL && edit->canUndo();
	}
	else
	{
		return Inherited::canUndo();
	}
}

bool UndoManager::canUndoOrRedo(void) const
{
	if(_IndexOfNextAdd == _Edits.size())
	{
		return canUndo();
	}
	else
	{
		return canRedo();
	}
}

void UndoManager::discardAllEdits(void)
{
	trimEdits(0,_Edits.size());
}

void UndoManager::end(void)
{
	Inherited::end();

	trimEdits(_IndexOfNextAdd, _Edits.size()-1);
}
      
std::string UndoManager::getUndoOrRedoPresentationName(void) const
{
	if(_IndexOfNextAdd == _Edits.size())
	{
		return getUndoPresentationName();
	}
	else
	{
		return getRedoPresentationName();
	}
}

std::string UndoManager::getRedoPresentationName(void) const
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeRedone();
		if(edit != NULL && edit->canRedo())
		{
			return edit->getRedoPresentationName();
		}
		else
		{
			return AbstractUndoableEdit::getRedoPresentationName();
		}
	}
	else
	{
		return Inherited::getRedoPresentationName();
	}
}

std::string UndoManager::getUndoPresentationName(void) const
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeUndone();
		if(edit != NULL && edit->canUndo())
		{
			return edit->getUndoPresentationName();
		}
		else
		{
			return AbstractUndoableEdit::getUndoPresentationName();
		}
	}
	else
	{
		return Inherited::getUndoPresentationName();
	}
}

void UndoManager::redo(void)
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeRedone();
		if(edit == NULL)
		{
			throw CannotRedoException();
		}

		redoTo(edit);
	}
	else
	{
		return Inherited::redo();
	}
}

void UndoManager::undo(void)
{
	if(_IsInProgress)
	{
		UndoableEditPtr edit = editToBeUndone();
		if(edit == NULL)
		{
			throw CannotUndoException();
		}

		undoTo(edit);
	}
	else
	{
		return Inherited::undo();
	}
}

void UndoManager::handleUndoableEditHappened(UndoableEditEventDetails* const e)
{
	addEdit(e->getUndoableEdit());
}

void UndoManager::undoOrRedo(void)
{
	if(_IndexOfNextAdd == _Edits.size())
	{
		return undo();
	}
	else
	{
		return redo();
	}
}

UndoableEditPtr UndoManager::editToBeRedone(void) const
{
	Int32 i = _IndexOfNextAdd;
    while (i < _Edits.size())
	{
        UndoableEditPtr edit = _Edits[i++];
        if (edit->isSignificant())
		{
            return edit;
        }
    }

	return UndoableEditPtr();
}

UndoableEditPtr UndoManager::editToBeUndone(void) const
{
	Int32 i = _IndexOfNextAdd;
    while (i > 0)
	{
        UndoableEditPtr edit = _Edits[--i];
        if (edit->isSignificant())
		{
            return edit;
        }
    }

	return UndoableEditPtr();
}

void UndoManager::undoOrRedoTo(const UInt32& index)
{
	if(index <= _Edits.size())
	{
		bool done = false;
		while(_IndexOfNextAdd != index)
		{
			if(_IndexOfNextAdd >= index)
			{
				undo();
			}
			else
			{
				redo();
			}
		}
	}
}

void UndoManager::redoTo(UndoableEditPtr edit)
{
	bool done = false;
    while (!done)
	{
        UndoableEditPtr next = _Edits[_IndexOfNextAdd++];
        next->redo();
        done = (next == edit);
    }
	produceStateChanged();
}

void UndoManager::trimEdits(Int32 from, Int32 to)
{
	if (from >= 0 && from <= to)
	{
        for (Int32 i = to-1; from <= i; --i)
		{
            UndoableEditPtr e = _Edits[i];
            e->die();
        }

		EditVector::iterator FromItor(_Edits.begin());
		for(Int32 i(0) ; i<from && i<_Edits.size(); ++i) {++FromItor;}

		EditVector::iterator ToItor(_Edits.begin());
		for(Int32 i(0) ; i<to+1 && i<_Edits.size() ; ++i) {++ToItor;}

		_Edits.erase(FromItor,ToItor);

        if (_IndexOfNextAdd > to)
		{
            _IndexOfNextAdd -= to-from+1;
        }
		else if (_IndexOfNextAdd >= from)
		{
            _IndexOfNextAdd = from;
        }

		produceStateChanged();
    }
}

void UndoManager::trimForLimit(void)
{
	if (_Limit >= 0)
	{
        Int32 size = _Edits.size();

		if (size > _Limit)
		{
            Int32 halfLimit = _Limit/2;
            Int32 keepFrom = _IndexOfNextAdd - 1 - halfLimit;
            Int32 keepTo   = _IndexOfNextAdd - 1 + halfLimit;

            if (keepTo - keepFrom + 1 > _Limit)
			{
                keepFrom++;
            }

            if (keepFrom < 0) {
                keepTo -= keepFrom;
                keepFrom = 0;
            }
            if (keepTo >= size) {
                Int32 delta = size - keepTo - 1;
                keepTo += delta;
                keepFrom += delta;
            }

            trimEdits(keepTo+1, size-1);
            trimEdits(0, keepFrom-1);
        }
    }
}

void UndoManager::undoTo(UndoableEditPtr edit)
{
	bool done = false;
    while (!done)
	{
        UndoableEditPtr next = _Edits[--_IndexOfNextAdd];
        next->undo();
        done = (next == edit);
    }
	produceStateChanged();
}

UInt32 UndoManager::numberOfRedos(void) const
{
	UInt32 RedoCount(0);
    for (Int32 i(_IndexOfNextAdd) ; i < _Edits.size() ; ++i)
	{
        if (_Edits[i]->isSignificant())
		{
            ++RedoCount;
        }
    }

	return RedoCount;
}

UInt32 UndoManager::numberOfUndos(void) const
{
	UInt32 UndoCount(0);
    for (Int32 i(_IndexOfNextAdd-1) ; i >= 0 ; --i)
	{
        if (_Edits[i]->isSignificant())
		{
            ++UndoCount;
        }
    }

	return UndoCount;
}

UndoableEditPtr UndoManager::editToBeRedone(const UInt32& offset) const
{
	Int32 i = _IndexOfNextAdd;
	UInt32 RedoCount(0);
    while (i < _Edits.size())
	{
        UndoableEditPtr edit = _Edits[i++];
        if (edit->isSignificant())
		{
			if(RedoCount == offset)
			{
				return edit;
			}
			else
			{
				++RedoCount;
			}
        }
    }

	return UndoableEditPtr();
}

UndoableEditPtr UndoManager::editToBeUndone(const UInt32& offset) const
{
	Int32 i = _IndexOfNextAdd;
	UInt32 UndoCount(0);
    while (i > 0)
	{
        UndoableEditPtr edit = _Edits[--i];
        if (edit->isSignificant())
		{
			if(UndoCount == offset)
			{
				return edit;
			}
			else
			{
				++UndoCount;
			}
        }
    }

	return UndoableEditPtr();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UndoManager::UndoManager(void) : Inherited(),
								_IndexOfNextAdd(0),
								_Limit(100)
{
}

UndoManager::UndoManager(const UndoManager& source) : Inherited(source),
								_IndexOfNextAdd(source._IndexOfNextAdd),
								_Limit(source._Limit)
{
}

void UndoManager::operator=(const UndoManager& source)
{
	Inherited::operator=(source);
	_IndexOfNextAdd = source._IndexOfNextAdd;
	_Limit = source._Limit;
}

UndoManager::~UndoManager(void)
{
}

UndoManagerPtr UndoManager::create(void)
{
	return UndoManagerPtr(new UndoManager());
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

