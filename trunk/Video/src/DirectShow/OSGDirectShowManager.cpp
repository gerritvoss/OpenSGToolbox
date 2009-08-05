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

#ifdef WIN32

#include <Dshow.h>

OSG_BEGIN_NAMESPACE

DirectShowManager *DirectShowManager::_the = NULL;

VideoManager *DirectShowManager::the(void)
{
    if(_the == NULL)
        _the = new DirectShowManager;

    return _the;
}

VideoWrapperPtr DirectShowManager::createVideoWrapper(void) const
{
	return DirectShowVideoWrapper::create();
}

void DirectShowManager::init(int   argc, char *argv[])
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }
}

void DirectShowManager::exit(void)
{
    CoUninitialize();
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

#endif

