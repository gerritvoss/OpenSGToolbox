/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Aaron Cronk                                      *
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

#ifndef _OSGABSTRACTTREESELECTIONMODEL_H_
#define _OSGABSTRACTTREESELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTreeSelectionModel.h"
#include <set>

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeSelectionModel class. See \ref 
           PageUserInterfaceAbstractTreeSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTreeSelectionModel : public TreeSelectionModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	//Adds a listener for the TreeSelectionModelEvent posted after the tree changes.
	virtual EventConnection addTreeSelectionListener(TreeSelectionListenerPtr l);
	virtual bool isTreeSelectionListenerAttached(TreeSelectionListenerPtr l) const;

	//Removes a listener previously added with addTreeSelectionListener.
	virtual void removeTreeSelectionListener(TreeSelectionListenerPtr l);
	
	//Adds a ChangeListener to the listener list.
	virtual EventConnection addChangeListener(ChangeListenerPtr listener);
	virtual bool isChangeListenerAttached(ChangeListenerPtr listener) const;
	
	//Removes a ChangeListener from the listener list.
	virtual void removeChangeListener(ChangeListenerPtr listener);
  protected:
	typedef std::set<TreeSelectionListenerPtr> TreeSelectionListenerSet;
	typedef TreeSelectionListenerSet::iterator TreeSelectionListenerSetIter;
	typedef TreeSelectionListenerSet::const_iterator TreeSelectionListenerSetConstIter;
	TreeSelectionListenerSet _SelectionListeners;

	void produceSelectionAdded(const std::vector<NumberRange>& ElementsAdded, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath);
	void produceSelectionRemoved(const std::vector<NumberRange>& ElementsRemoved, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath);
	
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
	typedef ChangeListenerSet::iterator ChangeListenerSetIter;
	typedef ChangeListenerSet::const_iterator ChangeListenerSetConstIter;
	ChangeListenerSet _ChangeListeners;
	
	//void produceStateChanged(void);

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef AbstractTreeSelectionModel *AbstractTreeSelectionModelPtr;

OSG_END_NAMESPACE

#define OSGABSTRACTTREESELECTIONMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTREESELECTIONMODEL_H_ */
