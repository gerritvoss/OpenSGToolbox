/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
 *                   Authors: David Kabala, Eric Langkamp                    *
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
#ifndef _OSGDIALOGHIERARCHYEVENT_H_
#define _OSGDIALOGHIERARCHYEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include <OpenSG/Toolbox/OSGEvent.h>

#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

class OSG_GAMELIB_DLLMAPPING DialogHierarchyEvent : public Event
{
  /*=========================  PUBLIC  ===============================*/
  public:

   DialogHierarchyEvent(FieldContainerPtr Source, Time TimeStamp);

    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
  private:
     static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGDialogHierarchyEvent.inl"

#endif /* _OSGDIALOGHIERARCHYEVENT_H_ */
