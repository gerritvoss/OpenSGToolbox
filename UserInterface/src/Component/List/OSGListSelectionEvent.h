/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSG_UI_LIST_SELECTION_EVENT_H_
#define _OSG_UI_LIST_SELECTION_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUserInterfaceConfig.h"

#include <OpenSG/Input/OSGEvent.h>

OSG_BEGIN_NAMESPACE

class OSG_USER_INTERFACE_CLASS_API ListSelectionEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
   //Returns the index of the first row whose selection may have changed.
   UInt32 	getFirstIndex() const;
   //Returns the index of the last row whose selection may have changed.
   UInt32 	getLastIndex() const;
   //Returns true if this is one of multiple change events
   bool 	getValueIsAdjusting() const;
    
    ListSelectionEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FirstIndex, UInt32 LastIndex, bool ValueIsAdjusting);
  private:
     UInt32 _FirstIndex;
     UInt32 _LastIndex;
     bool _ValueIsAdjusting;
    
};

OSG_END_NAMESPACE

#include "OSGListSelectionEvent.inl"

#endif /* _OSG_UI_LIST_SELECTION_EVENT_H_ */