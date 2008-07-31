#include <windows.h>
#include <comip.h>
#include <dshow.h>
#define __IDxtCompositor_INTERFACE_DEFINED__

#define __IDxtAlphaSetter_INTERFACE_DEFINED__

#define __IDxtJpeg_INTERFACE_DEFINED__

#define __IDxtKey_INTERFACE_DEFINED__
#include <qedit.h>
#include <string>

class VideoWrapper {
    _com_ptr_t<ICaptureGraphBuilder2> graphBuilder;
    _com_ptr_t<IFilterGraph2> filterGraph;
    _com_ptr_t<ISampleGrabber> sampleGrabber;
    
    bool videoInitialized;
    int videoWidth;
    int videoHeight;
    long* frameBuffer;
    long bufferSize;

    /** G3D Texture object */
    TextureRef videoTexture;

    VideoWrapper {
        // This must be callled before 
        // interfaces can be accessed
        CoInitialize(NULL);
        videoInitialized = false;
        frameBuffer = NULL;
    }

    ~VideoWrapper (
        // Technically, uninit ever init
        CoUninitialize();
    }

    bool loadVideoFile(const std::wstring& filename);

    bool loadVideoCamera();

    TextureRef grabFrameTexture();

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