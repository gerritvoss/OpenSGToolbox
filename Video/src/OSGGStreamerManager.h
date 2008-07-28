#ifndef _OPENSG_VIDEO_MANAGER_H_
#define _OPENSG_VIDEO_MANAGER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include <string>

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING GStreamerManager
{
public:
    static GStreamerManager *the(void);

    void init(int   argc, char *argv[]);
    void exit(void);

    void doSomething(void);

    void openVideo(std::string Path);

private:
    GStreamerManager(void);
    virtual ~GStreamerManager(void);
    
    static GStreamerManager   *_the;
    GStreamerManager(const GStreamerManager &source);
    void operator =(const GStreamerManager &source);
protected:
};

OSG_END_NAMESPACE


#include "OSGGStreamerManager.inl"
#endif
