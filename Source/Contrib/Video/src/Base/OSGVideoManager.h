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
#ifndef _OPENSG_VIDEO_MANAGER_H_
#define _OPENSG_VIDEO_MANAGER_H_

#include "OSGConfig.h"
#include "OSGContribVideoDef.h"
#include "OSGVideoWrapper.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBVIDEO_DLLMAPPING VideoManager
{
public:
    virtual bool init(int   argc, char *argv[]) = 0;
    virtual bool init(void);
    virtual bool exit(void) = 0;

    virtual VideoWrapperTransitPtr createVideoWrapper(void) const = 0;

private:
protected:
};

typedef VideoManager* VideoManagerPtr;

VideoManagerPtr OSG_CONTRIBVIDEO_DLLMAPPING getDefaultVideoManager(void);

OSG_END_NAMESPACE

#endif
