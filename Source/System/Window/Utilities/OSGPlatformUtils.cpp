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
#include <CoreServices/CoreServices.h>
#endif

#ifdef WIN32
#endif

#ifdef __linux
#endif

OSG_BEGIN_NAMESPACE

/********************** OS X **************************/
#ifdef __APPLE__

std::string FSRef2String(const FSRef& foundRef)
{
    std::string Result("");

    CFURLRef tURL;
    tURL = CFURLCreateFromFSRef(kCFAllocatorDefault, &foundRef);

    CFStringRef tCFString = CFURLCopyFileSystemPath(tURL,
                                                    kCFURLPOSIXPathStyle);

    CFIndex buf_len = 1 + CFStringGetMaximumSizeForEncoding(CFStringGetLength(tCFString), 
                                                            kCFStringEncodingUTF8);
    char *buffer  = new char[buf_len];
    CFStringGetCString(tCFString, buffer, buf_len,
                       kCFStringEncodingUTF8);

    Result = std::string(buffer);

    delete[] buffer;
    CFRelease(tCFString);
    CFRelease(tURL);

    return Result;
}

BoostPath getPlatformUserAppDataDir(void)
{
    BoostPath Result("");

    //Carbon
    FSRef foundRef;
    OSErr err = FSFindFolder(kUserDomain, kApplicationSupportFolderType,
                             kDontCreateFolder, &foundRef);
    if (err == noErr)
    {
        Result = BoostPath(FSRef2String(foundRef));
    }
    return Result;
}

BoostPath getPlatformTempDataDir(void)
{
    BoostPath Result("");

    //Carbon
    FSRef foundRef;
    OSErr err = FSFindFolder(kUserDomain, kTemporaryFolderType,
                             kDontCreateFolder, &foundRef);
    if (err == noErr)
    {
        Result = BoostPath(FSRef2String(foundRef));
    }
    return Result;
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

