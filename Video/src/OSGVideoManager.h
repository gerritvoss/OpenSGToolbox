#ifndef _OPENSG_VIDEO_MANAGER_H_
#define _OPENSG_VIDEO_MANAGER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"
#include "OSGVideoWrapper.h"

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING VideoManager
{
public:
    virtual void init(int   argc, char *argv[]) = 0;
    virtual void exit(void) = 0;

    virtual VideoWrapperPtr createVideoWrapper(void) const = 0;

private:
protected:
};

typedef VideoManager* VideoManagerPtr;

VideoManagerPtr OSG_VIDEOLIB_DLLMAPPING getDefaultVideoManager(void);

OSG_END_NAMESPACE

#endif
