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
#ifndef _OSGFIELDCHANGEEVENT_H_
#define _OSGFIELDCHANGEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "Event/OSGEvent.h"

#include <OpenSG/OSGField.h>
#include <OpenSG/OSGFieldDescription.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING FieldChangeEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    Field* getField(void) const;
    FieldDescription* getFieldDescription(void) const;
    
    FieldChangeEvent(FieldContainerPtr Source, Time TimeStamp, Field* TheField, FieldDescription* TheDescription);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
    
  protected:
     Field* _Field;
     FieldDescription* _FieldDescription;
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGFieldChangeEvent.inl"

#endif /* _OSGFIELDCHANGEEVENT_H_ */


