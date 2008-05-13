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
#ifndef _OSG_UI_SELECTION_EVENT_H_
#define _OSG_UI_SELECTION_EVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING SelectionEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
   //Returns the index of the first row whose selection may have changed.
   const std::vector<Int32>& getSelectedIndicies(void) const;

   //Returns the index of the last row whose selection may have changed.
   const std::vector<Int32>& getPreviouslySelectedIndicies(void) const;

    //Returns true if this is one of multiple change events
    bool 	getValueIsAdjusting() const;
    
    SelectionEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<Int32>& Selected, std::vector<Int32>& PreviouslySelected, bool ValueIsAdjusting);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  protected:
     std::vector<Int32> _Selected;
     std::vector<Int32> _PreviouslySelected;
     bool _ValueIsAdjusting;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGSelectionEvent.inl"

#endif /* _OSG_UI_SELECTION_EVENT_H_ */
