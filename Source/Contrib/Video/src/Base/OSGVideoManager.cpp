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

#ifdef OSG_WITH_DIRECT_SHOW
#include "OSGDirectShowManager.h"
#endif

#if defined(OSG_WITH_VLC)
#include "OSGVLCManager.h"
#endif

#include "OSGStubVideoManager.h"

OSG_BEGIN_NAMESPACE

VideoManagerPtr getDefaultVideoManager(void)
{
#ifdef OSG_WITH_DIRECT_SHOW
    return DirectShowManager::the();
#elif defined(OSG_WITH_VLC)
    return VLCManager::the();
#else
    return StubVideoManager::the();
#endif
}

bool VideoManager::init(void)
{
    return init(0, NULL);
}

OSG_END_NAMESPACE
