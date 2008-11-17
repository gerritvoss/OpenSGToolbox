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

#ifndef _OSGWINDOWLISTENER_H_
#define _OSGWINDOWLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "OSGEventListener.h"
#include "OSGWindowEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING WindowListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEvent& e) = 0;
    virtual void windowClosing(const WindowEvent& e) = 0;
    virtual void windowClosed(const WindowEvent& e) = 0;
    virtual void windowIconified(const WindowEvent& e) = 0;
    virtual void windowDeiconified(const WindowEvent& e) = 0;
    virtual void windowActivated(const WindowEvent& e) = 0;
    virtual void windowDeactivated(const WindowEvent& e) = 0;
    virtual void windowEntered(const WindowEvent& e) = 0;
    virtual void windowExited(const WindowEvent& e) = 0;
};

typedef WindowListener* WindowListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGWINDOWLISTENER_H_ */
