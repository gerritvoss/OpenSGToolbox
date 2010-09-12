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
#include "OSGStubVideoManager.h"
#include "OSGStubVideoWrapper.h"

OSG_BEGIN_NAMESPACE

StubVideoManager *StubVideoManager::_the = NULL;

VideoManager *StubVideoManager::the(void)
{
    if(_the == NULL)
        _the = new StubVideoManager;

    return _the;
}

VideoWrapperTransitPtr StubVideoManager::createVideoWrapper(void) const
{
    VideoWrapperUnrecPtr Video(StubVideoWrapper::create());
	return VideoWrapperTransitPtr(Video.get());
}

bool StubVideoManager::init(int   argc, char *argv[])
{
    SLOG << "Video Stub Manager Initialized" << std::endl;
    return true;
}

bool StubVideoManager::exit(void)
{
    SLOG << "Video Stub Manager Exited" << std::endl;
    return true;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

StubVideoManager::StubVideoManager(void)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

StubVideoManager::~StubVideoManager(void)
{
}

OSG_END_NAMESPACE


