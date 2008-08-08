#include "OSGDirectShowVideoWrapper.h"

#include <boost/archive/iterators/wchar_from_mb.hpp> 

OSG_BEGIN_NAMESPACE

Int64 DirectShowVideoWrapper::getPosition(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		Int64 Result;
		if (SUCCEEDED(mediaSeeking->GetCurrentPosition(&Result))) {
			return Result;
		} else {
			return -1;
		}
	}
	return -1;
}

Int64 DirectShowVideoWrapper::getDuration(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		Int64 Result;
		if (SUCCEEDED(mediaSeeking->GetDuration(&Result))) {
			return Result;
		} else {
			return -1;
		}
	}
	return -1;
}

bool DirectShowVideoWrapper::isPlaying(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState))) {
			return GraphState == State_Running;
		} else {
			return false;
		}
    }
    return false;
}
bool DirectShowVideoWrapper::isStopped(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState))) {
			return GraphState == State_Stopped;
		} else {
			return false;
		}
    }
    return false;
}

bool DirectShowVideoWrapper::isPaused(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState))) {
			return GraphState == State_Paused;
		} else {
			return false;
		}
    }
    return false;
}

bool DirectShowVideoWrapper::isInitialized(void) const
{
    return videoInitialized;
}

bool DirectShowVideoWrapper::open(Path ThePath)
{
    if (videoInitialized) {
        uninitVideo();
    }

    HRESULT hr;
    
    hr = CoCreateInstance(CLSID_FilterGraph, NULL,
    CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&filterGraph);

    if(SUCCEEDED(hr))
    {
        // Create the main object that runs the graph
        hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
            CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2,
            (void **)&graphBuilder);

        if (SUCCEEDED(hr))
        {
            graphBuilder->SetFiltergraph(filterGraph);
        }
    }
    else
    {
        return false;
    }

    IBaseFilter* sourceFilter;

    typedef boost::archive::iterators::wchar_from_mb<const char *> translator;

    std::wstring WideFileName;
    WideFileName.assign(ThePath.string().begin(), ThePath.string().end());

    // This takes the absolute filename path and
    // Loads the appropriate file reader and splitter
    // Depending in the file type.
    filterGraph->AddSourceFilter(WideFileName.c_str(),
                                 L"Video Source",
                                 &sourceFilter);
    
    // Create the Sample Grabber which we will use
    // To take each frame for texture generation
    IBaseFilter* grabberFilter;
    hr = ::CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
                        IID_IBaseFilter, (LPVOID *)&grabberFilter);

    grabberFilter->QueryInterface(IID_ISampleGrabber, reinterpret_cast<void**>(&sampleGrabber));

    filterGraph->AddFilter(grabberFilter, L"Sample Grabber");

    // We have to set the 24-bit RGB desire here
    // So that the proper conversion filters
    // Are added automatically.
    AM_MEDIA_TYPE desiredType;
    memset(&desiredType, 0, sizeof(desiredType));
    desiredType.majortype = MEDIATYPE_Video;
    desiredType.subtype = MEDIASUBTYPE_RGB24;
    desiredType.formattype = FORMAT_VideoInfo;

    sampleGrabber->SetMediaType(&desiredType);
    sampleGrabber->SetBufferSamples(TRUE);

    // Use pin connection methods instead of 
    // ICaptureGraphBuilder::RenderStream because of
    // the SampleGrabber setting we're using.
    if (!ConnectPins(sourceFilter, 0, grabberFilter, 0)) {
        uninitVideo();
        return false;        
    }

    // A Null Renderer does not display the video
    // But it allows the Sample Grabber to run
    // And it will keep proper playback timing
    // Unless specified otherwise.
    IBaseFilter* nullRenderer;
    CoCreateInstance(CLSID_NullRenderer,   NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&nullRenderer);

    filterGraph->AddFilter(nullRenderer, L"Null Renderer");

    if (!ConnectPins(grabberFilter, 0, nullRenderer, 0)) {
        uninitVideo();
        return false;
    }

    // Just a little trick so that we don't have to know
    // The video resolution when calling this method.
    bool mediaConnected = false;
    AM_MEDIA_TYPE connectedType;
    if (SUCCEEDED(sampleGrabber->GetConnectedMediaType(&connectedType))) {
        if (connectedType.formattype == FORMAT_VideoInfo) {
            VIDEOINFOHEADER* infoHeader = (VIDEOINFOHEADER*)connectedType.pbFormat;
            videoWidth = infoHeader->bmiHeader.biWidth;
            videoHeight = infoHeader->bmiHeader.biHeight;
            mediaConnected = true;
        }
        CoTaskMemFree(connectedType.pbFormat);
    }

    if (!mediaConnected) {
        uninitVideo();
        return false;
    }

    return true;
}

bool DirectShowVideoWrapper::seek(Int64 SeekPos)
{
    //TODO: Implement
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		if (SUCCEEDED(mediaSeeking->SetPositions(&SeekPos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning))) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

bool DirectShowVideoWrapper::play(void)
{
    //if(isInitialized())
    //{
		// Tell the whole graph to start sending video
		// Apart from making sure the source filter can load
		// This is the only failure point we care about unless
		// You need to do more extensive development and debugging.
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		if (SUCCEEDED(mediaControl->Run())) {
			videoInitialized = true;
			return true;
		} else {
			uninitVideo();
			return false;
		}
	//}
}

bool DirectShowVideoWrapper::pause(void)
{
    if(isInitialized())
    {
        HRESULT hr;

        IMediaControl* mediaControl;
        hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

        if (SUCCEEDED(mediaControl->Pause())) {
            return true;
        }
    }
    return false;
}

bool DirectShowVideoWrapper::unpause(void)
{
    return play();
}

bool DirectShowVideoWrapper::pauseToggle(void)
{
    if(isInitialized())
    {
		if(isPaused())
		{
			return unpause();
		}
		else
		{
			return pause();
		}
	}
    return false;
}

bool DirectShowVideoWrapper::stop(void)
{
    if(isInitialized())
    {
        HRESULT hr;

        IMediaControl* mediaControl;
        hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

        if (SUCCEEDED(mediaControl->Stop())) {
            return true;
        }
    }
    return false;
}

bool DirectShowVideoWrapper::close(void)
{
    uninitVideo();
    return true;
}

bool DirectShowVideoWrapper::updateImage(void)
{
    if (videoInitialized) {
        // Only need to do this once
        if (!frameBuffer) {
            // The Sample Grabber requires an arbitrary buffer
            // That we only know at runtime.
            // (width * height * 3) bytes will not work.
            sampleGrabber->GetCurrentBuffer(&bufferSize, NULL);
            if(bufferSize<=0)
            {
                return NullFC;
            }
            frameBuffer = new long[bufferSize];
        }
        
        sampleGrabber->GetCurrentBuffer(&bufferSize, (long*)frameBuffer);
    
		if(_VideoImage == NullFC ||
		_VideoImage->getWidth() != videoWidth ||
		_VideoImage->getHeight() != videoHeight)
		{
			_VideoImage = Image::create();
			addRefCP(_VideoImage);
			_VideoImage->set(Image::OSG_BGR_PF,videoWidth,videoHeight,1,1,1,0.0,reinterpret_cast<const UInt8*>(frameBuffer),Image::OSG_UINT8_IMAGEDATA);
		}
		else
		{
			_VideoImage->setData(reinterpret_cast<const UInt8*>(frameBuffer));		
		}

        return true;
    }

    return false;
}

ImagePtr DirectShowVideoWrapper::getCurrentFrame(void)
{
    if (videoInitialized) {
        // Only need to do this once
        if (!frameBuffer) {
            // The Sample Grabber requires an arbitrary buffer
            // That we only know at runtime.
            // (width * height * 3) bytes will not work.
            sampleGrabber->GetCurrentBuffer(&bufferSize, NULL);
            if(bufferSize<=0)
            {
                return NullFC;
            }
            frameBuffer = new long[bufferSize];
        }
        
        sampleGrabber->GetCurrentBuffer(&bufferSize, (long*)frameBuffer);
    
        ImagePtr TheImage = Image::create();
        TheImage->set(Image::OSG_BGR_PF,videoWidth,videoHeight,1,1,1,0.0,reinterpret_cast<const UInt8*>(frameBuffer),Image::OSG_UINT8_IMAGEDATA);

        return TheImage;
    }

    return NullFC;
}

void DirectShowVideoWrapper::uninitVideo() {
    videoInitialized = false;

    HRESULT hr;
    if (videoInitialized) {
        sampleGrabber->Release();
        IMediaControl* mediaControl;
        hr = filterGraph->QueryInterface(IID_IMediaControl,
    (void**)&mediaControl);
        mediaControl->Stop();
        filterGraph->Release();
        graphBuilder->Release();
    }

    delete[] frameBuffer;
    frameBuffer = NULL;
}

bool DirectShowVideoWrapper::ConnectPins(IBaseFilter* outputFilter,
                       unsigned int outputNum,
                       IBaseFilter* inputFilter,
                       unsigned int inputNum) {

    IPin* inputPin;
    IPin* outputPin;

    if (!outputFilter || !inputFilter) {
        return false;
    }

    FindPin(outputFilter, PINDIR_OUTPUT, outputNum, &outputPin);
    FindPin(inputFilter, PINDIR_INPUT, inputNum, &inputPin);

    if (inputPin && outputPin) {
        return SUCCEEDED(filterGraph->Connect(outputPin, inputPin));
    } else {
        return false;
    }
}

void DirectShowVideoWrapper::FindPin(IBaseFilter* baseFilter,
                   PIN_DIRECTION direction,
                   int pinNumber,
                   IPin** destPin) {

    IEnumPins* enumPins;

    *destPin = NULL;

    if (SUCCEEDED(baseFilter->EnumPins(&enumPins))) {
        ULONG numFound;
        IPin* tmpPin;

        while (SUCCEEDED(enumPins->Next(1, &tmpPin, &numFound))) {
            PIN_DIRECTION pinDirection;

            tmpPin->QueryDirection(&pinDirection);
            if (pinDirection == direction) {
                if (pinNumber == 0) {
                    // Return the pin's interface
                    *destPin = tmpPin;
                    break;
                }
                pinNumber--;
            }
            tmpPin->Release();
        }
    }
}

OSG_END_NAMESPACE
