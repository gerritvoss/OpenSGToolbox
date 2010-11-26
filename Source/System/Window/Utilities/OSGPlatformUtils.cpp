/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
#include "OSGPlatformUtils.h"

#ifdef __APPLE__
//#include "Folders.h"
#endif

#ifdef WIN32
#endif

#ifdef __linux
#endif

OSG_BEGIN_NAMESPACE

/********************** OS X **************************/
#ifdef __APPLE__

BoostPath getPlatformUserAppDataDir(void)
{
    return BoostPath(getenv("HOME")) / "/Library/Application Support";
}

BoostPath getPlatformTempDataDir(void)
{
    //Carbon
    //FSFindFolder();
    return BoostPath("/tmp");
}

#endif

/********************* Linux **************************/
#ifdef __linux

BoostPath getPlatformUserAppDataDir(void)
{
    return BoostPath("~/");
}

BoostPath getPlatformTempDataDir(void)
{
    return BoostPath("/tmp");
}

#endif

/******************** Windows *************************/
#ifdef WIN32

BoostPath getPlatformUserAppDataDir(void)
{
    //APPDATA
    return BoostPath(getenv("APPDATA"));
}

BoostPath getPlatformTempDataDir(void)
{
    //TEMP
    return BoostPath(getenv("TEMP"));
}

#endif

OSG_END_NAMESPACE

