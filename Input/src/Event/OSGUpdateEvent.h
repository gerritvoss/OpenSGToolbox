/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGUPDATEEVENT_H_
#define _OSGUPDATEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "Event/OSGEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING UpdateEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    Time getElapsedTime(void) const;
    
    UpdateEvent(FieldContainerPtr Source, Time TimeStamp, Time Elps);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
    
  protected:
    Time _Elps;
  
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGUpdateEvent.inl"

#endif /* _OSGUPDATEEVENT_H_ */
