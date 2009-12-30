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

#ifndef _OSGUNDOMANAGER_H_
#define _OSGUNDOMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include "OSGCompoundUndoableEdit.h"
#include "OSGUndoableEditListener.h"
#include "Event/OSGChangeListener.h"
#include <set>
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief UndoManager class. See \ref 
           PageUserInterfaceUndoManager for a description.
*/

class UndoManager;
typedef boost::intrusive_ptr<UndoManager> UndoManagerPtr;

class OSG_USERINTERFACELIB_DLLMAPPING UndoManager : public CompoundUndoableEdit, public UndoableEditListener
{
    /*==========================  PUBLIC  =================================*/
  public:
	typedef CompoundUndoableEdit Inherited;
    typedef UndoManagerPtr  Ptr;
    typedef UndoManager  Self;

    //Adds a ChangeListener to the model's listener list.
    virtual EventConnection addChangeListener(ChangeListenerPtr l);
	virtual bool isChangeListenerAttached(ChangeListenerPtr l) const;
    
    //Removes a ChangeListener from the model's listener list.
    virtual void removeChangeListener(ChangeListenerPtr l);

	//If inProgress, inserts anEdit at indexOfNextAdd, and removes any old edits that were at indexOfNextAdd or later.
	virtual bool addEdit(const UndoableEditPtr anEdit);

	//Overridden to preserve usual semantics: returns true if a redo operation would be successful now, false otherwise
	virtual bool canRedo(void) const;

	//Overridden to preserve usual semantics: returns true if an undo operation would be successful now, false otherwise
	virtual bool canUndo(void) const;

	//Return true if calling undoOrRedo will undo or redo.
	bool canUndoOrRedo(void) const;

	//Empty the undo manager, sending each edit a die message in the process.
	void discardAllEdits(void);

	//Sending end() to an UndoManager turns it into a plain old (ended) CompoundEdit.
	void end(void);

	//Returns the maximum number of edits this UndoManager will hold.
	Int32 getLimit(void) const;
          
	//Return the appropriate name for a command that toggles between undo and redo.
	virtual std::string getUndoOrRedoPresentationName(void) const;

	//If inProgress, returns getRedoPresentationName of the significant edit that will be redone when redo() is invoked.
	virtual std::string getRedoPresentationName(void) const;

	//If inProgress, returns getUndoPresentationName of the significant edit that will be undone when undo() is invoked.
	virtual std::string getUndoPresentationName(void) const;

	//If this UndoManager is inProgress, redoes the last significant UndoableEdit at indexOfNextAdd or after, and all insignificant edits up to it.
	virtual void redo(void);

	//If this UndoManager is inProgress, counts the number of significant, redoable, UndoableEdit after indexOfNextAdd.
	UInt32 numberOfRedos(void) const;

	//If this UndoManager is inProgress, counts the number of significant, undoable, UndoableEdit before indexOfNextAdd.
	UInt32 numberOfUndos(void) const;

	//Returns the the significant edit to be redone offset edits after indexOfNextAdd.
	UndoableEditPtr editToBeRedone(const UInt32& offset) const;

	//Returns the the significant edit to be undone offset edits before indexOfNextAdd.
	UndoableEditPtr editToBeUndone(const UInt32& offset) const;

	//Set the maximum number of edits this UndoManager will hold.
	void setLimit(const Int32& limit);
	
	//If this UndoManager is inProgress, undo the last significant UndoableEdit before indexOfNextAdd, and all insignificant edits back to it.
	virtual void undo(void);

	//Called by the UndoabledEdit sources this UndoManager listens to.
	void undoableEditHappened(UndoableEditEventPtr e);

	//Undo or redo as appropriate.
	void undoOrRedo(void);

	
	void undoOrRedoTo(const UInt32& index);

	//Redoes all changes from indexOfNextAdd to edit.
	void redoTo(UndoableEditPtr edit);

	//Undoes all changes from indexOfNextAdd to edit.
	void undoTo(UndoableEditPtr edit);

	virtual ~UndoManager(void);

	static UndoManagerPtr create(void);

	template <class InTypeT> inline
	static Ptr dcast(InTypeT oIn)
	{
		return Ptr(dynamic_cast<Self *>(oIn.get()));
	}
  protected:
	Int32 _IndexOfNextAdd;
	Int32 _Limit;

	UndoManager(void);

	UndoManager(const UndoManager& source);

    void operator =(const UndoManager& source);

	//Returns the the next significant edit to be redone if redo is called.
	UndoableEditPtr editToBeRedone(void) const;

	//Returns the the next significant edit to be undone if undo is called.
	UndoableEditPtr editToBeUndone(void) const;

	//Tell the edits in the given range (inclusive) to die, and remove them from edits.
	void trimEdits(Int32 from, Int32 to);

	//Reduce the number of queued edits to a range of size limit, centered on indexOfNextAdd.
	void trimForLimit(void);

	typedef std::set<ChangeListenerPtr> ChangeListenerSet;

	ChangeListenerSet _ChangeListeners;

	void produceStateChanged(void);
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGUndoManager.inl"

#define OSGUNDOMANAGER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGUNDOMANAGER_H_ */
