/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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
#include "OSGWindowUtils.h"

#ifdef __APPLE__
#include "OSGCarbonWindow.h"
#endif

#ifdef WIN32
#include "OSGWIN32Window.h"
#endif

#ifdef __linux
#include "OSGXWindow.h"
#endif

OSG_BEGIN_NAMESPACE

WindowEventProducerTransitPtr createNativeWindow(void)
{
#if defined(__APPLE__)
    return WindowEventProducerTransitPtr(CarbonWindow::create());
#elif defined(WIN32)
    return WindowEventProducerTransitPtr(WIN32Window::create());
#elif defined(__linux)
    return WindowEventProducerTransitPtr(XWindow::create());
#endif
}

OSG_END_NAMESPACE


