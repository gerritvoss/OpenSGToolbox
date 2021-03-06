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

#ifndef _OSGDIALOGLISTENER_H_
#define _OSGDIALOGLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include <OpenSG/Toolbox/OSGEventListener.h>
#include "OSGDialogEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_GAMELIB_DLLMAPPING DialogListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void started(const DialogEventPtr e) = 0;
    virtual void ended(const DialogEventPtr e) = 0;
    virtual void responseSelected(const DialogEventPtr e) = 0;
    virtual void responsesReady(const DialogEventPtr e) = 0;
    virtual void terminated(const DialogEventPtr e) = 0;
};

typedef DialogListener* DialogListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGDIALOGLISTENER_H_ */
