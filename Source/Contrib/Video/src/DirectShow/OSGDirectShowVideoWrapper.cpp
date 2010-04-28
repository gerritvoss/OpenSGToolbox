/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDirectShowVideoWrapper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDirectShowVideoWrapperBase.cpp file.
// To modify it, please change the .fcd file (OSGDirectShowVideoWrapper.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DirectShowVideoWrapper::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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

bool DirectShowVideoWrapper::open(const std::string& ThePath, WindowUnrecPtr TheWindow)
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

    std::wstring WideFileName;
    WideFileName.assign(ThePath.begin(), ThePath.end());

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

	videoInitialized = true;
	produceOpened();
    return true;
}

bool DirectShowVideoWrapper::setRate(Real32 Rate)
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		if (SUCCEEDED(mediaSeeking->SetRate(Rate)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

Real32 DirectShowVideoWrapper::getRate(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		double Rate;
		if (SUCCEEDED(mediaSeeking->GetRate(&Rate)))
		{
			return static_cast<Real32>(Rate);
		}
	}
	return 0.0;
}

bool DirectShowVideoWrapper::jump(Int64 Amount)
{
    return seek(osgClamp<Int64>(0,getPosition()+Amount,getDuration()));
    /*if(isInitialized())
    {
		REFERENCE_TIME Position = (getDuration() *100) / 95;
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		if (SUCCEEDED(mediaSeeking->SetPositions(&Amount, AM_SEEKING_RelativePositioning, NULL, AM_SEEKING_NoPositioning))) {
            reachEndOnce = false;
			produceSeeked();
			return true;
		} else {
			return false;
		}
	}
	return false;*/
}

bool DirectShowVideoWrapper::seek(Int64 SeekPos)
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaSeeking* mediaSeeking;
		hr = filterGraph->QueryInterface(IID_IMediaSeeking,(void**)&mediaSeeking);

		if (SUCCEEDED(mediaSeeking->SetPositions(&SeekPos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning))) {
            reachEndOnce = false;
			produceSeeked();
			return true;
		} else {
			return false;
		}
	}
	return false;
}

bool DirectShowVideoWrapper::play(void)
{
    if(isInitialized())
    {
		bool wasPaused(isPaused());
		// Tell the whole graph to start sending video
		// Apart from making sure the source filter can load
		// This is the only failure point we care about unless
		// You need to do more extensive development and debugging.
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		if (SUCCEEDED(mediaControl->Run())) {
			if(wasPaused)
			{
				produceUnpaused();
			}
			produceStarted();
			return true;
		} else {
			uninitVideo();
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool DirectShowVideoWrapper::pause(void)
{
    if(isInitialized())
    {
        HRESULT hr;

        IMediaControl* mediaControl;
        hr = filterGraph->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

        if (SUCCEEDED(mediaControl->Pause())) {
			producePaused();
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
			produceStopped();
            reachEndOnce = false;
            return true;
        }
    }
    return false;
}

bool DirectShowVideoWrapper::close(void)
{
    uninitVideo();
	produceClosed();
    reachEndOnce = false;
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
            HRESULT result;
            result = sampleGrabber->GetCurrentBuffer(&bufferSize, NULL);
            if(bufferSize<=0)
            {
                std::cout << "bufferSize<=0" << std::endl;
                return false;
            }
            if(bufferSize>10000000)
            {
                std::cout << "bufferSize>10000000" << std::endl;
                return false;
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
            try
            {
			    _VideoImage->set(Image::OSG_BGR_PF,videoWidth,videoHeight,1,1,1,0.0,reinterpret_cast<const UInt8*>(frameBuffer),Image::OSG_UINT8_IMAGEDATA);
            }
            catch(...)
            {
			    subRefCP(_VideoImage);
                _VideoImage= NullFC;
                return false;
            }
		}
		else
		{
            _VideoImage->setData(reinterpret_cast<const UInt8*>(frameBuffer));		
		}
        if(!reachEndOnce && getPosition() == getDuration())
        {
            reachEndOnce = true;
            produceEnded();
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

    if(frameBuffer != NULL)
    {
        delete[] frameBuffer;
    }
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DirectShowVideoWrapper::DirectShowVideoWrapper(void) :
    Inherited(),
        videoInitialized(false),
        frameBuffer(NULL),
        reachEndOnce(false)
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }
}

DirectShowVideoWrapper::DirectShowVideoWrapper(const DirectShowVideoWrapper &source) :
    Inherited(source),
        videoInitialized(false),
        frameBuffer(NULL),
        reachEndOnce(false)
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }

}

DirectShowVideoWrapper::~DirectShowVideoWrapper(void)
{
    uninitVideo();
    CoUninitialize();
}

/*----------------------------- class specific ----------------------------*/

void DirectShowVideoWrapper::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DirectShowVideoWrapper::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DirectShowVideoWrapper NI" << std::endl;
}

OSG_END_NAMESPACE
