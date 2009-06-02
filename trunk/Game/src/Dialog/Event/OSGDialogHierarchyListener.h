/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Game                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Eric Langkamp                                    *
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

#ifndef _OSGDIALOGHIERARCHYLISTENER_H_
#define _OSGDIALOGHIERARCHYLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include <OpenSG/Input/OSGEventListener.h>
#include "OSGDialogHierarchyEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_GAMELIB_DLLMAPPING DialogHierarchyListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void newDialogStarted(const DialogHierarchyEvent& e) = 0;
    virtual void dialogEnded(const DialogHierarchyEvent& e) = 0;
    virtual void dialogResponseSelected(const DialogHierarchyEvent& e) = 0;
    virtual void dialogResponsesReady(const DialogHierarchyEvent& e) = 0;
    virtual void terminated(const DialogHierarchyEvent& e) = 0;
};

typedef DialogHierarchyListener* DialogHierarchyListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGDIALOGHIERARCHYLISTENER_H_ */
