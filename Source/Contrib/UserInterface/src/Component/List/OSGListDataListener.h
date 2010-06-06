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

#ifndef _OSG_UI_LIST_DATA_LISTENER_H_
#define _OSG_UI_LIST_DATA_LISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGListDataEvent.h"

#include "OSGEventListener.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ListDataListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
	//Sent when the contents of the list has changed in a way that's too complex to characterize with the previous methods.
	virtual void 	contentsChanged(const ListDataEventUnrecPtr e) = 0;

	//Sent after the indices in the index0,index1 interval have been inserted in the data model.
	virtual void 	intervalAdded(const ListDataEventUnrecPtr e) = 0;

	//Sent after the indices in the index0,index1 interval have been removed from the data model.
	virtual void 	intervalRemoved(const ListDataEventUnrecPtr e) = 0;
};

typedef ListDataListener* ListDataListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_LIST_DATA_LISTENER_H_ */
