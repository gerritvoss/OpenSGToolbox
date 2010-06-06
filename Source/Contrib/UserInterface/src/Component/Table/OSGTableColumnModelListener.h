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

#ifndef _OSG_UI_TABLE_COLUMN_MODEL_LISTENER_H_
#define _OSG_UI_TABLE_COLUMN_MODEL_LISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGChangeEvent.h"
#include "OSGListSelectionEvent.h"
#include "OSGTableColumnModelEventFields.h"

#include "OSGEventListener.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableColumnModelListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:

    //Tells listeners that a column was added to the model.
    virtual void columnAdded(const TableColumnModelEventUnrecPtr e) = 0;

    //Tells listeners that a column was moved due to a margin change.
    virtual void columnMarginChanged(const ChangeEventUnrecPtr e) = 0;

    //Tells listeners that a column was repositioned.
    virtual void columnMoved(const TableColumnModelEventUnrecPtr e) = 0;

    //Tells listeners that a column was removed from the model.
    virtual void columnRemoved(const TableColumnModelEventUnrecPtr e) = 0;

    //Tells listeners that the selection model of the TableColumnModel changed.
    virtual void columnSelectionChanged(const ListSelectionEventUnrecPtr e) = 0;
};

typedef TableColumnModelListener* TableColumnModelListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_TABLE_COLUMN_MODEL_LISTENER_H_ */
