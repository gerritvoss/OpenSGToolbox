#ifndef _OPENSG_DIRECT_SHOW_VIDEO_WRAPPER_H_
#define _OPENSG_DIRECT_SHOW_VIDEO_WRAPPER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#ifdef WIN32

#include "OSGVideoWrapper.h"
#include <windows.h>
#include <dshow.h>
#include <qedit.h>
#include <string>

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING DirectShowVideoWrapper : public VideoWrapper
{
public:
    virtual bool open(Path ThePath);

    virtual bool seek(Real32 SeekPos);
    virtual bool play(void);
    virtual bool pause(void);
    virtual bool unpause(void);
    virtual bool pauseToggle(void);
    virtual bool stop(void);
    virtual bool close(void);

    virtual ImagePtr getCurrentFrame(void);
private:
    friend class DirectShowManager;

    ICaptureGraphBuilder2* graphBuilder;
    IFilterGraph2* filterGraph;
    ISampleGrabber* sampleGrabber;
    
    bool videoInitialized;
    int videoWidth;
    int videoHeight;
    long* frameBuffer;
    long bufferSize;

    DirectShowVideoWrapper() {
        // This must be callled before 
        // interfaces can be accessed
        CoInitialize(NULL);
        videoInitialized = false;
        frameBuffer = NULL;
    }

    ~DirectShowVideoWrapper() {
        // Technically, uninit ever init
        CoUninitialize();
    }

    bool loadVideoFile(const std::wstring& filename);

    bool loadVideoCamera();

    void uninitVideo();

    bool ConnectPins(IBaseFilter* outputFilter, 
                     unsigned int outputNum,
                     IBaseFilter* inputFilter,
                     unsigned int inputNum);

    void FindPin(IBaseFilter* baseFilter,
                 PIN_DIRECTION direction,
                 int pinNumber,
                 IPin** destPin);
};

OSG_END_NAMESPACE

#endif

#endif
