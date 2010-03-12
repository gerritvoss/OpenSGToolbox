/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSGUNDOABLE_EDIT_H_
#define _OSGUNDOABLE_EDIT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include <boost/shared_ptr.hpp>
#include <exception>
#include <string>

OSG_BEGIN_NAMESPACE
  
class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CannotUndoException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "CannotUndoException";
    }
};

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CannotRedoException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "CannotRedoException";
    }
};

class UndoableEdit;
typedef boost::shared_ptr<UndoableEdit> UndoableEditPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UndoableEdit
{
   /*=========================  PUBLIC  ===============================*/
protected:
    typedef UndoableEditPtr  Ptr;
    typedef UndoableEdit  Self;

	UndoableEdit(void);

	UndoableEdit(const UndoableEdit& source);

    void operator =(const UndoableEdit& source);
public:

	//This UndoableEdit should absorb anEdit if it can.
	virtual bool addEdit(const UndoableEditPtr anEdit) = 0;

	//True if it is still possible to redo this operation.
	virtual bool canRedo(void) const = 0;

	//True if it is still possible to undo this operation.
	virtual bool canUndo(void) const = 0;

	//May be sent to inform an edit that it should no longer be used.
	virtual void die(void) = 0;

	//Provides a localized, human readable description of this edit suitable for use in, say, a change log.
	virtual std::string getPresentationName(void) const = 0;

	//Provides a localized, human readable description of the redoable form of this edit, e.g.
	virtual std::string getRedoPresentationName(void) const = 0;

	//Provides a localized, human readable description of the undoable form of this edit, e.g.
	virtual std::string getUndoPresentationName(void) const = 0;

	//Returns false if this edit is insignificant--for example one that maintains the user's selection, but does not change any model state.
	virtual bool isSignificant(void) const = 0;

	//Re-apply the edit, assuming that it has been undone.
	virtual void redo(void) = 0;

	//Returns true if this UndoableEdit should replace anEdit.
	virtual bool replaceEdit(const UndoableEditPtr anEdit) const = 0;

	//Undo the edit that was made.
	virtual void undo(void) = 0;
	
	virtual ~UndoableEdit(void);
};


OSG_END_NAMESPACE

#include "OSGUndoableEdit.inl"

#endif /* _OSGUNDOABLE_EDIT_H_ */
