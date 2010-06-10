/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGWINDOWLISTENER_H_
#define _OSGWINDOWLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGEventListener.h"
#include "OSGWindowEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING WindowListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEventUnrecPtr e) = 0;
    virtual void windowClosing(const WindowEventUnrecPtr e) = 0;
    virtual void windowClosed(const WindowEventUnrecPtr e) = 0;
    virtual void windowIconified(const WindowEventUnrecPtr e) = 0;
    virtual void windowDeiconified(const WindowEventUnrecPtr e) = 0;
    virtual void windowActivated(const WindowEventUnrecPtr e) = 0;
    virtual void windowDeactivated(const WindowEventUnrecPtr e) = 0;
    virtual void windowEntered(const WindowEventUnrecPtr e) = 0;
    virtual void windowExited(const WindowEventUnrecPtr e) = 0;
};

typedef WindowListener* WindowListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGWINDOWLISTENER_H_ */


