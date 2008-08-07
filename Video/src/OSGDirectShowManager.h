#ifndef _OPENSG_DIRECT_SHOW_MANAGER_H_
#define _OPENSG_DIRECT_SHOW_MANAGER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#ifdef WIN32

#include "OSGVideoManager.h"
#include <string>
#include <Dshow.h>

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING DirectShowManager : public VideoManager
{
public:
    static VideoManager *the(void);

    virtual void init(int   argc, char *argv[]);
    virtual void exit(void);

    virtual VideoWrapperPtr createVideoWrapper(void) const;

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
#endif

#endif
