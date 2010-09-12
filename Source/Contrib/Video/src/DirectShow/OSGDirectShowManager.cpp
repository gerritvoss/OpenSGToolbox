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
#include "OSGDirectShowManager.h"
#include "OSGDirectShowVideoWrapper.h"

#ifdef OSG_WITH_DIRECT_SHOW

#include <Dshow.h>

OSG_BEGIN_NAMESPACE

DirectShowManager *DirectShowManager::_the = NULL;

DirectShowManager *DirectShowManager::the(void)
{
    if(_the == NULL)
    {
        _the = new DirectShowManager;
    }

    return _the;
}

VideoWrapperTransitPtr DirectShowManager::createVideoWrapper(void) const
{
    VideoWrapperUnrecPtr Video(DirectShowVideoWrapper::create());
	return VideoWrapperTransitPtr(Video.get());
}

bool DirectShowManager::init(int   argc, char *argv[])
{
    HRESULT hr;
    SLOG << "Initializing COM library." << std::endl;
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        SWARNING << "Could not initialize COM library." << std::endl;
        return false;
    }
    return true;
}

bool DirectShowManager::exit(void)
{
    SLOG << "Uninitializing COM library." << std::endl;
    CoUninitialize();
    return true;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DirectShowManager::DirectShowManager(void)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DirectShowManager::~DirectShowManager(void)
{
}

OSG_END_NAMESPACE

#endif  //OSG_WITH_DIRECT_SHOW

