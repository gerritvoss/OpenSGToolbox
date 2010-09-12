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
#ifndef _OPENSG_DIRECT_SHOW_MANAGER_H_
#define _OPENSG_DIRECT_SHOW_MANAGER_H_

#include "OSGConfig.h"
#include "OSGContribVideoDef.h"

#ifdef OSG_WITH_DIRECT_SHOW

#include "OSGVideoManager.h"
#include <string>


OSG_BEGIN_NAMESPACE

class OSG_CONTRIBVIDEO_DLLMAPPING DirectShowManager : public VideoManager
{
public:
    static DirectShowManager *the(void);

    virtual bool init(int   argc, char *argv[]);
    virtual bool exit(void);

    virtual VideoWrapperTransitPtr createVideoWrapper(void) const;

private:
    DirectShowManager(void);
    virtual ~DirectShowManager(void);
    
    static DirectShowManager   *_the;
    DirectShowManager(const DirectShowManager &source);
    void operator =(const DirectShowManager &source);
protected:
};

OSG_END_NAMESPACE


#include "OSGDirectShowManager.inl"
#endif    //OSG_WITH_DIRECT_SHOW

#endif
