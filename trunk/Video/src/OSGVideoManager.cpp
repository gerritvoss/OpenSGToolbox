/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Video                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
                           Authors: David Kabala                            
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
#include "OSGVideoManager.h"

#ifdef __APPLE__
//#include "WindowSystem/Carbon/OSGCarbonWindowEventProducer.h"
#endif

#ifdef WIN32
#ifdef _USE_DIRECT_SHOW
#include "DirectShow/OSGDirectShowManager.h"
#endif
#endif

#ifdef __linux
//#include <OpenSG/OSGXWindow.h>
//#include "WindowSystem/X/OSGXWindowEventProducer.h"
//#include <GL/glx.h>
#endif

OSG_BEGIN_NAMESPACE

VideoManagerPtr getDefaultVideoManager(void)
{
#ifdef __APPLE__
    return NULL;
#elif defined(WIN32)
#ifdef _USE_DIRECT_SHOW
    return DirectShowManager::the();
#else
    return NULL;
#endif
#elif defined(__linux)
    return NULL;
#endif
}

OSG_END_NAMESPACE
