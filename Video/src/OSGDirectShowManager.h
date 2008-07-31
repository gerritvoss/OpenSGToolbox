#ifndef _OPENSG_VIDEO_MANAGER_H_
#define _OPENSG_VIDEO_MANAGER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include <string>
#include <Dshow.h>

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING DirectShowManager
{
public:
    static DirectShowManager *the(void);

    void init(int   argc, char *argv[]);
    void exit(void);

    void openVideo(std::string Path);

private:
    DirectShowManager(void);
    virtual ~DirectShowManager(void);
    
    static DirectShowManager   *_the;
    DirectShowManager(const DirectShowManager &source);
    void operator =(const DirectShowManager &source);
protected:
	IGraphBuilder *pGraph;
    IMediaControl *pControl;
    IMediaEvent   *pEvent;

    // Initialize the COM library.
    HRESULT hr;
};

OSG_END_NAMESPACE


#include "OSGDirectShowManager.inl"
#endif
