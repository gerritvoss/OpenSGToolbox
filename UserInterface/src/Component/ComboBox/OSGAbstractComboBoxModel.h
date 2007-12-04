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

#ifndef _OSGABSTRACTCOMBOBOXMODEL_H_
#define _OSGABSTRACTCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComboBoxModel.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractComboBoxModel class. See \ref 
           PageUserInterfaceAbstractComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractComboBoxModel : public ComboBoxModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	virtual void addListDataListener(ListDataListenerPtr l);
	virtual void removeListDataListener(ListDataListenerPtr l);
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
	typedef std::set<ListDataListenerPtr> ListDataListenerSet;
	typedef ListDataListenerSet::iterator ListDataListenerSetIter;
	typedef ListDataListenerSet::const_iterator ListDataListenerSetConstIter;
	ListDataListenerSet _DataListeners;

	void produceListDataContentsChanged(void);
	void produceListDataIntervalAdded(UInt32 index0, UInt32 index1);
	void produceListDataIntervalRemoved(UInt32 index0, UInt32 index1);
};

typedef AbstractComboBoxModel *AbstractComboBoxModelPtr;

OSG_END_NAMESPACE

#define OSGABSTRACTCOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTCOMBOBOXMODEL_H_ */
