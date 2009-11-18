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

#ifdef _OSGTOOLBOX_VIDEO_USE_DIRECT_SHOW
#include "DirectShow/OSGDirectShowManager.h"
#endif

#include "Stub/OSGStubVideoManager.h"

OSG_BEGIN_NAMESPACE

VideoManagerPtr getDefaultVideoManager(void)
{
#ifdef _OSGTOOLBOX_VIDEO_USE_DIRECT_SHOW
    return DirectShowManager::the();
#elif defined(_OSGTOOLBOX_VIDEO_USE_VLC)
    return StubVideoManager::the();
#else
    return StubVideoManager::the();
#endif
}

void VideoManager::init(void)
{
    init(0, NULL);
}

OSG_END_NAMESPACE
