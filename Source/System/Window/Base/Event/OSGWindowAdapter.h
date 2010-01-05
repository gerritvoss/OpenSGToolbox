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

#ifndef _OSGWINDOWADAPTER_H_
#define _OSGWINDOWADAPTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGWindowListener.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING WindowAdapter : public WindowListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEventUnrecPtr e);
    virtual void windowClosing(const WindowEventUnrecPtr e);
    virtual void windowClosed(const WindowEventUnrecPtr e);
    virtual void windowIconified(const WindowEventUnrecPtr e);
    virtual void windowDeiconified(const WindowEventUnrecPtr e);
    virtual void windowActivated(const WindowEventUnrecPtr e);
    virtual void windowDeactivated(const WindowEventUnrecPtr e);
    virtual void windowEntered(const WindowEventUnrecPtr e);
    virtual void windowExited(const WindowEventUnrecPtr e);
};

typedef WindowAdapter* WindowAdapterPtr;

OSG_END_NAMESPACE

#endif /* _OSGWINDOWADAPTER_H_ */


