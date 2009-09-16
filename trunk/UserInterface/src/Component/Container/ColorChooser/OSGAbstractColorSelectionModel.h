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

#ifndef _OSG_ABSTRACT_COLOR_SELECTION_MODEL_H_
#define _OSG_ABSTRACT_COLOR_SELECTION_MODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGColorSelectionModel.h"
#include <set>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractColorSelectionModel class. See \ref 
           PageUserInterfaceAbstractColorSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractColorSelectionModel : public ColorSelectionModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	virtual EventConnection addChangeListener(ChangeListenerPtr Listener);
	virtual bool isChangeListenerAttached(ChangeListenerPtr Listener) const;

	virtual void removeChangeListener(ChangeListenerPtr Listener);
  protected:
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
	
    ChangeListenerSet       _ChangeListeners;
    void produceStateChanged(const ChangeEvent& e);
    /*==========================  PRIVATE  ================================*/
  private:
};

typedef AbstractColorSelectionModel *AbstractColorSelectionModelPtr;

OSG_END_NAMESPACE

#define OSGABSTRACTCOLOR_SELECTIONMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSG_ABSTRACT_COLOR_SELECTION_MODEL_H_ */
