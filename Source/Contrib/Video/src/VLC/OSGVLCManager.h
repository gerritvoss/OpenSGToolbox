/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Video                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala, David Naylor                       *
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
#ifndef _OPENSG_VLC_MANAGER_H_
#define _OPENSG_VLC_MANAGER_H_

#include "OSGConfig.h"
#include "OSGContribVideoDef.h"

#ifdef OSG_WITH_VLC

#include "OSGVideoManager.h"
#include <string>


OSG_BEGIN_NAMESPACE

class OSG_CONTRIBVIDEO_DLLMAPPING VLCManager : public VideoManager
{
public:
    static VideoManager *the(void);

    virtual void init(int   argc, char *argv[]);
    virtual void exit(void);

    virtual VideoWrapperTransitPtr createVideoWrapper(void) const;

private:
    VLCManager(void);
    virtual ~VLCManager(void);
    
    static VLCManager   *_the;
    VLCManager(const VLCManager &source);
    void operator =(const VLCManager &source);
protected:
};

OSG_END_NAMESPACE


#include "OSGVLCManager.inl"
#endif

#endif
