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

#ifndef _OSGABSTRACTUNDOABLEEDIT_H_
#define _OSGABSTRACTUNDOABLEEDIT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGUndoableEdit.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractUndoableEdit class. See \ref 
           PageUserInterfaceAbstractUndoableEdit for a description.
*/

class AbstractUndoableEdit;
typedef boost::shared_ptr<AbstractUndoableEdit> AbstractUndoableEditPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractUndoableEdit : public UndoableEdit
{
    /*==========================  PUBLIC  =================================*/
  public:
	  typedef UndoableEdit Inherited;
    typedef AbstractUndoableEditPtr  Ptr;
    typedef AbstractUndoableEdit  Self;

	//This UndoableEdit should absorb anEdit if it can.
	virtual bool addEdit(const UndoableEditPtr anEdit);

	//True if it is still possible to redo this operation.
	virtual bool canRedo(void) const;

	//True if it is still possible to undo this operation.
	virtual bool canUndo(void) const;

	//May be sent to inform an edit that it should no longer be used.
	virtual void die(void);

	//Provides a localized, human readable description of this edit suitable for use in, say, a change log.
	virtual std::string getPresentationName(void) const;

	//Provides a localized, human readable description of the redoable form of this edit, e.g.
	virtual std::string getRedoPresentationName(void) const;

	//Provides a localized, human readable description of the undoable form of this edit, e.g.
	virtual std::string getUndoPresentationName(void) const;

	//Returns false if this edit is insignificant--for example one that maintains the user's selection, but does not change any model state.
	virtual bool isSignificant(void) const;

	//Re-apply the edit, assuming that it has been undone.
	virtual void redo(void);

	//Returns true if this UndoableEdit should replace anEdit.
	virtual bool replaceEdit(const UndoableEditPtr anEdit) const;

	//Undo the edit that was made.
	virtual void undo(void);
	
	virtual ~AbstractUndoableEdit(void);

	template <class InTypeT> inline
	static Ptr dcast(InTypeT oIn)
	{
		return Ptr(dynamic_cast<Self *>(oIn.get()));
	}
  protected:
	bool _Alive;
	bool _HasBeenDone;

	AbstractUndoableEdit(void);

	AbstractUndoableEdit(const AbstractUndoableEdit& source);

    void operator =(const AbstractUndoableEdit& source);
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGAbstractUndoableEdit.inl"

#endif /* _OSGABSTRACTUNDOABLEEDIT_H_ */
