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
#include "OSGDirectShowManager.h"
#include "OSGdshowutil.h"
#include <algorithm>
#include <cctype>
#include <boost/filesystem/operations.hpp>

#include "OSGBaseInitFunctions.h"

#ifdef OSG_WITH_DIRECT_SHOW

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

    if(ePhase == TypeObject::Static)
    {
        char *c[] = {""};
        addPreFactoryInitFunction(boost::bind(&DirectShowManager::init, DirectShowManager::the(), 0, c));
        addPostFactoryExitFunction(boost::bind(&DirectShowManager::exit, DirectShowManager::the()));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real64 DirectShowVideoWrapper::getPosition(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return -1.0;
		}

		Real64 Result;
		hr = mediaPosition->get_CurrentPosition(&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get current position, error: " << szErr << std::endl;
			return -1.0;
		}

		return Result;
	}
	return -1.0;
}

Real64 DirectShowVideoWrapper::getDuration(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return -1.0;
		}

		Real64 Result;
		hr = mediaPosition->get_Duration(&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get duration, error: " << szErr << std::endl;
			return -1.0;
		}

		return Result;
	}
	return -1.0;
}

bool DirectShowVideoWrapper::isPlaying(void) const
{
    if(isInitialized())
    {
		HRESULT hr;

		IMediaControl* mediaControl;
		hr = _pGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState)))
        {
			return GraphState == State_Running;
		}
        else
        {
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
		hr = _pGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState)))
        {
			return GraphState == State_Stopped;
		}
        else
        {
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
		hr = _pGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&mediaControl);

		OAFilterState GraphState;
		if (SUCCEEDED(mediaControl->GetState(0.1f, &GraphState)))
        {
			return GraphState == State_Paused;
		}
        else
        {
			return false;
		}
    }
    return false;
}

bool DirectShowVideoWrapper::isInitialized(void) const
{
    return _VideoInitialized;
}

bool DirectShowVideoWrapper::canSeekForward(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return false;
		}

		LONG Result;
		hr = mediaPosition->CanSeekForward (&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get canSeekForward, error: " << szErr << std::endl;
			return false;
		}

		return Result == OATRUE;
	}
	return false;
}

bool DirectShowVideoWrapper::canSeekBackward(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return false;
		}

		LONG Result;
		hr = mediaPosition->CanSeekBackward(&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get canSeekForward, error: " << szErr << std::endl;
			return false;
		}

		return Result == OATRUE;
	}
	return false;
}

bool DirectShowVideoWrapper::setRate(Real64 Rate)
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return false;
		}

		hr = mediaPosition->put_Rate(Rate);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to set rate to value: " << Rate << ", error: " << szErr << std::endl;
			return false;
		}

		return true;
	}
	return false;
}

Real64 DirectShowVideoWrapper::getRate(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return -1.0;
		}

		Real64 Result;
		hr = mediaPosition->get_Rate(&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get rate, error: " << szErr << std::endl;
			return -1.0;
		}

		return Result;
	}
	return -1.0;
}

bool DirectShowVideoWrapper::jump(Real64 Amount)
{
    return seek(osgClamp<Real64>(0.0,getPosition()+Amount,getDuration()));
}

bool DirectShowVideoWrapper::seek(Real64 SeekPos)
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

        Real64 CurPos(getPosition());
        if((SeekPos < CurPos) &&
            (!canSeekBackward()))
        {
            SWARNING << "Unable to seek backwards on this type of media." << std::endl;
			return false;
        }
        if((SeekPos > CurPos) &&
            (!canSeekForward()))
        {
            SWARNING << "Unable to seek forwards on this type of media." << std::endl;
			return false;
        }

		CComPtr<IMediaPosition> mediaPosition;
		hr = _pGraphBuilder->QueryInterface(&mediaPosition);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IMediaPosition, error: " << szErr << std::endl;
			return false;
		}

		hr = mediaPosition->put_CurrentPosition(SeekPos);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to set position to value: " << SeekPos << ", error: " << szErr << std::endl;
			return false;
		}

		return true;
	}
	return false;
}

bool DirectShowVideoWrapper::play(void)
{
    if(isInitialized())
    {
		bool wasPaused(isPaused());

		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaControl> mediaControl;
		hr = _pGraphBuilder->QueryInterface(&mediaControl);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get media control, error: " << szErr << std::endl;
            return false;
        }

		hr = mediaControl->Run();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to run filter graph, error: " << szErr << std::endl;
            return false;
        }

		if(wasPaused)
		{
			produceUnpaused();
		}
		produceStarted();
		return true;
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
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaControl> mediaControl;
		hr = _pGraphBuilder->QueryInterface(&mediaControl);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get media control, error: " << szErr << std::endl;
            return false;
        }

		hr = mediaControl->Pause();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to pause, error: " << szErr << std::endl;
            return false;
        }

		producePaused();
        return true;
    }
    return false;
}

bool DirectShowVideoWrapper::unpause(void)
{
    if(isInitialized() && isPaused())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaControl> mediaControl;
		hr = _pGraphBuilder->QueryInterface(&mediaControl);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get media control, error: " << szErr << std::endl;
            return false;
        }

		hr = mediaControl->Run();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to run filter graph, error: " << szErr << std::endl;
            return false;
        }

	    produceUnpaused();
		return true;
	}
	else
	{
		return false;
	}
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
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IMediaControl> mediaControl;
		hr = _pGraphBuilder->QueryInterface(&mediaControl);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get media control, error: " << szErr << std::endl;
            return false;
        }

		hr = mediaControl->Stop();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to stop, error: " << szErr << std::endl;
            return false;
        }

		produceStopped();
        _ReachEndOnce = false;
        return true;
    }
    return false;
}

 bool DirectShowVideoWrapper::hasAudio(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

        IBaseFilter* pAudioRenderer = NULL;
        hr = FindAudioRenderer(_pGraphBuilder,&pAudioRenderer);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Failed to find audio renderer, error: " << szErr << std::endl;
            return false;
        }

        return pAudioRenderer != NULL;
	}
	return false;
}

void DirectShowVideoWrapper::enableAudio(void)
{
    if(isInitialized() && hasAudio())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

        IBaseFilter* pAudioRenderer = NULL;
        _pGraphBuilder->FindFilterByName(L"NULL Audio Renderer",&pAudioRenderer);

        if(pAudioRenderer != NULL)
        {
            stop();

            //Remove the Null Renderer
		    IPin* ipin;
            GetPin(pAudioRenderer, PINDIR_INPUT, 0, &ipin);
		    IPin* opin = NULL;
		    //find out who the renderer is connected to and disconnect from them
		    hr = ipin->ConnectedTo(&opin);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
		    hr = ipin->Disconnect();
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
		    hr = opin->Disconnect();
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

            //Remove the Null Renderer		
		    hr = _pGraphBuilder->RemoveFilter(pAudioRenderer);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

            
            //Connect an Audio renderer
		    hr = _pGraphBuilder->AddFilter(_pAudioRenderer, L"Audio Renderer");
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

		    //get the input pin of the Color Space Converter
		    GetPin(_pAudioRenderer, PINDIR_INPUT, 0, &ipin);

            //Connect an Audio renderer
		    hr = _pGraphBuilder->Connect(opin, ipin);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
        }
    }
}

 void DirectShowVideoWrapper::disableAudio(void)
{
    if(isInitialized() && hasAudio())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

        IBaseFilter* pAudioRenderer = NULL;
        hr = FindAudioRenderer(_pGraphBuilder,&pAudioRenderer);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Failed to find audio renderer, error: " << szErr << std::endl;
            return;
        }

        if(pAudioRenderer != NULL)
        {
            stop();
            //Remove the Renderer
		    IPin* ipin;
            GetPin(pAudioRenderer, PINDIR_INPUT, 0, &ipin);
		    IPin* opin = NULL;
		    //find out who the renderer is connected to and disconnect from them
		    hr = ipin->ConnectedTo(&opin);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
		    hr = ipin->Disconnect();
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
		    hr = opin->Disconnect();
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

            //Remove the Renderer		
		    hr = _pGraphBuilder->RemoveFilter(pAudioRenderer);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

            
            //Connect an NULL Audio renderer
		    hr = _pGraphBuilder->AddFilter(_pNullAudioFilter, L"NULL Audio Renderer");
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }

		    //get the input pin of the Color Space Converter
		    GetPin(_pNullAudioFilter, PINDIR_INPUT, 0, &ipin);

            //Connect an Audio renderer
		    hr = _pGraphBuilder->Connect(opin, ipin);
            if (FAILED(hr))
            {
                AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
                SWARNING << "error: " << szErr << std::endl;
                return;
            }
        }
    }
}

bool DirectShowVideoWrapper::isAudioEnabled(void) const
{
    if(isInitialized() && hasAudio())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

        IBaseFilter* pAudioRenderer = NULL;
        _pGraphBuilder->FindFilterByName(L"NULL Audio Renderer",&pAudioRenderer);

        return (pAudioRenderer == NULL);
    }

    return false;
}

Real32 DirectShowVideoWrapper::getAudioVolume(void) const
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IBasicAudio> basicAudio;
		hr = _pGraphBuilder->QueryInterface(&basicAudio);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IBasicAudio, error: " << szErr << std::endl;
			return 0.0;
		}

		long Result;
		hr = basicAudio->get_Volume(&Result);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get audio volume, error: " << szErr << std::endl;
			return 0.0;
		}

		return 1.0f - (osgabs(static_cast<Real32>(Result))/10000.0f);
	}
	return 0.0;
}

 void DirectShowVideoWrapper::setAudioVolume(Real32 volume)
{
    if(isInitialized())
    {
		HRESULT hr;
        TCHAR szErr[MAX_ERROR_TEXT_LEN];

		CComPtr<IBasicAudio> basicAudio;
		hr = _pGraphBuilder->QueryInterface(&basicAudio);
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to get IBasicAudio, error: " << szErr << std::endl;
			return;
		}

		hr = basicAudio->put_Volume(static_cast<long>((volume - 1.0f) * -10000.0f));
		if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to set volume to value: " << volume << ", error: " << szErr << std::endl;
			return;
		}
	}
}

bool DirectShowVideoWrapper::close(void)
{
    uninitVideo();
	produceClosed();
    _ReachEndOnce = false;
    return true;
}

bool DirectShowVideoWrapper::updateImage(void)
{
    if (_VideoInitialized)
    {
        // Only need to do this once
        if (!_FrameBuffer)
        {
            // The Sample Grabber requires an arbitrary buffer
            // That we only know at runtime.
            // (width * height * 3) bytes will not work.
            HRESULT result;
            result = _pSampleGrabber->GetCurrentBuffer(&_BufferSize, NULL);
            if(FAILED(result))
            {
                return false;
            }

            if(_BufferSize<=0)
            {
                SWARNING << "_BufferSize<=0" << std::endl;
                return false;
            }
            if(_BufferSize>10000000)
            {
                SWARNING << "_BufferSize>10000000" << std::endl;
                return false;
            }
            _FrameBuffer = new long[_BufferSize];
        }
        
        _pSampleGrabber->GetCurrentBuffer(&_BufferSize, (long*)_FrameBuffer);
    
		if(getImage() == NULL ||
		getImage()->getWidth() != _VideoWidth ||
		getImage()->getHeight() != _VideoHeight)
		{
            ImageUnrecPtr NewImage(Image::create());
			setImage(NewImage);
            try
            {
			    getImage()->set(Image::OSG_BGR_PF,_VideoWidth,_VideoHeight,1,1,1,0.0,reinterpret_cast<const UInt8*>(_FrameBuffer),Image::OSG_UINT8_IMAGEDATA);
            }
            catch(...)
            {
			    setImage(NULL);
                return false;
            }
		}
		else
		{
            getImage()->setData(reinterpret_cast<const UInt8*>(_FrameBuffer));		
		}
        if(!_ReachEndOnce && getPosition() == getDuration())
        {
            _ReachEndOnce = true;
            produceEnded();
        }

        return true;
    }

    return false;
}

void DirectShowVideoWrapper::uninitVideo()
{
    _VideoInitialized = false;


    //Stop the video if need be
    HRESULT hr;
    if (_VideoInitialized &&
        _pGraphBuilder)
    {
        //_pSampleGrabberFilter->Release();
        IMediaControl* mediaControl;
        hr = _pGraphBuilder->QueryInterface(IID_IMediaControl,
                                            (void**)&mediaControl);
        mediaControl->Stop();
    }

    //Clear all reference counted pointers
    if(_pGraphBuilder)
    {
        _pGraphBuilder.Release();
        _pGraphBuilder.Detach();
    }
    if(_pGraphCaptureBuilder)
    {
        _pGraphCaptureBuilder.Release();
        _pGraphCaptureBuilder.Detach();
    }
    if(_pMediaControl)
    {
        _pMediaControl.Release();
        _pMediaControl.Detach();
    }
    if(_pMediaPosition)
    {
        _pMediaPosition.Release();
        _pMediaPosition.Detach();
    }
    if(_pMediaEvent)
    {
        _pMediaEvent.Release();
        _pMediaEvent.Detach();
    }
    if(g_IFileSource)
    {
        g_IFileSource.Release();
        g_IFileSource.Detach();
    }
    if(_pSourceFilter)
    {
        _pSourceFilter.Release();
        _pSourceFilter.Detach();
    }
    if(_pSourceAudioPin)
    {
        _pSourceAudioPin.Release();
        _pSourceAudioPin.Detach();
    }
    if(_pSourceVideoPin)
    {
        _pSourceVideoPin.Release();
        _pSourceVideoPin.Detach();
    }
    if(_pDecoderFilter)
    {
        _pDecoderFilter.Release();
        _pDecoderFilter.Detach();
    }
    if(_pVideoRenderer)
    {
        _pVideoRenderer.Release();
        _pVideoRenderer.Detach();
    }
    if(_DecoderOutputPin)
    {
        _DecoderOutputPin.Release();
        _DecoderOutputPin.Detach();
    }
    if(_pNullAudioFilter)
    {
        _pNullAudioFilter.Release();
        _pNullAudioFilter.Detach();
    }
    if(_pAudioRenderer)
    {
        _pAudioRenderer.Release();
        _pAudioRenderer.Detach();
    }
    if(_pSampleGrabberFilter)
    {
        _pSampleGrabberFilter.Release();
        _pSampleGrabberFilter.Detach();
    }
    if(_pCSCFilter)
    {
        _pCSCFilter.Release();
        _pCSCFilter.Detach();
    }
    if(_SampleGrabberIntputPin)
    {
        _SampleGrabberIntputPin.Release();
        _SampleGrabberIntputPin.Detach();
    }
    if(_SampleGrabberOutputPin)
    {
        _SampleGrabberOutputPin.Release();
        _SampleGrabberOutputPin.Detach();
    }

    //deallocate framebuffer
    if(_FrameBuffer != NULL)
    {
        delete[] _FrameBuffer;
        _FrameBuffer = NULL;
    }

    //Set image to NULL
    setImage(NULL);
}

HRESULT DirectShowVideoWrapper::ConnectWMVFile(const std::string& ThePath)
{
    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];

    std::wstring WideFileName;
    WideFileName.assign(ThePath.begin(), ThePath.end());
    
    SLOG << "Attempting to Load WMV File" << ThePath << std::endl;

    hr = _pGraphBuilder->RenderFile(WideFileName.c_str(),L"");
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable connect filter graph, error: " << szErr << std::endl;
        return hr;
    }

    SLOG << "Loaded WMV File into filter graph." << std::endl;

    return hr;
}

HRESULT DirectShowVideoWrapper::ConnectMPGFile(const std::string& ThePath)
{
    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];

    std::wstring WideFileName;
    WideFileName.assign(ThePath.begin(), ThePath.end());

    SLOG << "Attempting to Load MPG File" << ThePath << std::endl;
    
    hr = _pGraphBuilder->RenderFile(WideFileName.c_str(),L"");
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable connect filter graph, error: " << szErr << std::endl;
        return hr;
    }

    SLOG << "Loaded MPG File into filter graph." << std::endl;

    return hr;
}

HRESULT DirectShowVideoWrapper::ConnectAVCHDFile(const std::string& ThePath)
{
    //IMPORTANT: CoreAVC or some other codec like that is needed to create these filters
    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];

    std::wstring WideFileName;
    WideFileName.assign(ThePath.begin(), ThePath.end());

    SLOG << "Attempting to Load AVCHD File" << ThePath << std::endl;
    
    hr = _pGraphBuilder->RenderFile(WideFileName.c_str(),L"");
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable connect filter graph, error: " << szErr << std::endl;
        return hr;
    }

    SLOG << "Loaded AVCHD File into filter graph." << std::endl;

    return hr;
}

HRESULT DirectShowVideoWrapper::ConnectAVIFile(const std::string& ThePath)
{
    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];

    std::wstring WideFileName;
    WideFileName.assign(ThePath.begin(), ThePath.end());

    SLOG << "Attempting to Load File" << ThePath << std::endl;
    
    hr = _pGraphBuilder->RenderFile(WideFileName.c_str(),L"");
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable connect filter graph, error: " << szErr << std::endl;
        return hr;
    }

    SLOG << "Loaded File into filter graph." << std::endl;

    return hr;
}

HRESULT DirectShowVideoWrapper::ConnectSampleGrabber(void)
{
    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];
    
    // Register the graph in the Running Object Table (for debug purposes)
    //AddGraphToROT(_pGraphBuilder, &dwROT);

    // Create the Sample Grabber which we will use
    // To take each frame for texture generation
    if(_pCSCFilter == NULL)
    {
        hr = _pCSCFilter.CoCreateInstance(CLSID_Colour, NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Could not create Color Space Converter Filter, error: " << szErr << std::endl;
            return hr;
        }
    }

    // Create the Sample Grabber which we will use
    // To take each frame for texture generation
    if(_pSampleGrabberFilter == NULL)
    {
        hr = _pSampleGrabberFilter.CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Could not create SampleGrabberFilter, error: " << szErr << std::endl;
            return hr;
        }
    }

    _pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, reinterpret_cast<void**>(&_pSampleGrabber));

    // We have to set the 24-bit RGB desire here
    // So that the proper conversion filters
    // Are added automatically.
    AM_MEDIA_TYPE desiredType;
    memset(&desiredType, 0, sizeof(desiredType));
    desiredType.majortype = MEDIATYPE_Video;
    //desiredType.subtype = MEDIASUBTYPE_RGB565;
    desiredType.subtype = MEDIASUBTYPE_RGB24;
    //desiredType.subtype = GUID_NULL;
    desiredType.formattype = GUID();
    //desiredType.formattype = FORMAT_VideoInfo;

    _pSampleGrabber->SetMediaType(&desiredType);
    _pSampleGrabber->SetBufferSamples(TRUE);


    // A Null Renderer does not display the video
    // But it allows the Sample Grabber to run
    // And it will keep proper playback timing
    // Unless specified otherwise.
    if(_pVideoRenderer == NULL)
    {
        hr = _pVideoRenderer.CoCreateInstance(CLSID_NullRenderer,   NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to create Null Renderer, error: " << szErr << std::endl;
            return hr;
        }
    }
    
    //Get Input pins to VideoRenderer
    IPin* _VideoRendererIntputPin;
    if (FAILED(hr = _pVideoRenderer->FindPin(L"In", &_VideoRendererIntputPin)))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Could not find VideoRenderer Intput Pin, error: " << szErr << std::endl;
        return hr;
    }

    IBaseFilter* pVidRenderer = NULL;
	hr = FindVideoRenderer(_pGraphBuilder,&pVidRenderer);
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "error: " << szErr << std::endl;
        return hr;
    }
	if(pVidRenderer)
	{
        SLOG << "Removing default video renderer" << std::endl;
		//get input pin of video renderer
		IPin* ipin;
        GetPin(pVidRenderer, PINDIR_INPUT, 0, &ipin);
		IPin* opin = NULL;
		//find out who the renderer is connected to and disconnect from them
		hr = ipin->ConnectedTo(&opin);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }
		hr = ipin->Disconnect();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }
		hr = opin->Disconnect();
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }

		//SAFE_RELEASE(ipin);

		//remove the default renderer from the graph		
		hr = _pGraphBuilder->RemoveFilter(pVidRenderer);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }
		//SAFE_RELEASE(pVidRenderer);

		//see if the video renderer was originally connected to 
		//a color space converter
		//IBaseFilter* pColorConverter = NULL;
		//m_pGraph->FindFilterByName(L"Color Space Converter", &pColorConverter);
		//if(pColorConverter)
		//{
		//	SAFE_RELEASE(opin);

		//	//remove the converter from the graph as well
		//	ipin = GetPin(pColorConverter, PINDIR_INPUT);

		//	ipin->ConnectedTo(&opin);
		//	ipin->Disconnect();
		//	opin->Disconnect();

		//	SAFE_RELEASE(ipin);
		//	
		//	m_pGraph->RemoveFilter(pColorConverter);
		//	SAFE_RELEASE(pColorConverter);
		//}

  //      if (FAILED(hr =_pGraphBuilder->AddFilter(_pSampleGrabberFilter, L"Sample Grabber")))
  //      {
  //          AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
  //          SWARNING << "Could not add SampleGrabberFilter, error: " << szErr << std::endl;
  //          return hr;
  //      }
        hr = _pGraphBuilder->AddFilter(_pCSCFilter, L"Color Space Converter");
		//get the input pin of the Color Space Converter
		GetPin(_pCSCFilter, PINDIR_INPUT, 0, &ipin);

		//connect the filter that was originally connected to the default renderer
		//to the Color Space Converter
        SLOG << "Attaching Color Space Converter Filter." << std::endl;
		hr = _pGraphBuilder->Connect(opin, ipin);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }
        hr = _pGraphBuilder->AddFilter(_pSampleGrabberFilter, L"Video Sample Grabber");
        
		//get the input pin of the Sample Grabber
		GetPin(_pSampleGrabberFilter, PINDIR_INPUT, 0, &ipin);

		//get the output pin of the Color Space Converter
		GetPin(_pCSCFilter, PINDIR_OUTPUT, 0, &opin);

        SLOG << "Attaching video sample grabber filter." << std::endl;
		hr = _pGraphBuilder->Connect(opin, ipin);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "error: " << szErr << std::endl;
            return hr;
        }



		//SAFE_RELEASE(ipin);
		//SAFE_RELEASE(opin);

		//get output pin of sample grabber
		GetPin(_pSampleGrabberFilter, PINDIR_OUTPUT, 0, &opin);
        

        hr = _pGraphBuilder->AddFilter(_pVideoRenderer, L"Video Null Renderer");
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to add Renderer to filter graph, error: " << szErr << std::endl;
            return hr;
        }

		//get input pin of null renderer
		GetPin(_pVideoRenderer, PINDIR_INPUT, 0, &ipin);

		//connect them
        SLOG << "Attaching null video renderer." << std::endl;
		hr = _pGraphBuilder->Connect(opin, ipin);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to connect Renderer to sample grabber, error: " << szErr << std::endl;
            return hr;
        }
		//SAFE_RELEASE(ipin);
		//SAFE_RELEASE(opin);
	}

    

    // Just a little trick so that we don't have to know
    // The video resolution when calling this method.
    bool mediaConnected = false;
    AM_MEDIA_TYPE connectedType;
    if (SUCCEEDED(hr = _pSampleGrabber->GetConnectedMediaType(&connectedType)))
    {
        if (connectedType.formattype == FORMAT_VideoInfo)
        {
            VIDEOINFOHEADER* infoHeader = (VIDEOINFOHEADER*)connectedType.pbFormat;
            _VideoWidth = infoHeader->bmiHeader.biWidth;
            _VideoHeight = infoHeader->bmiHeader.biHeight;

            mediaConnected = true;
        }
        else if (connectedType.formattype == FORMAT_VideoInfo2)
        {
            VIDEOINFOHEADER* infoHeader = (VIDEOINFOHEADER*)connectedType.pbFormat;
            _VideoWidth = infoHeader->bmiHeader.biWidth;
            _VideoHeight = infoHeader->bmiHeader.biHeight;

            mediaConnected = true;
        }
        else
        {
            SWARNING << "Unable to get the media type connected to the sample grabber." << std::endl;
        }
        SLOG << "Video Dimensions: " << _VideoWidth << " x " << _VideoHeight << std::endl;
        CoTaskMemFree(connectedType.pbFormat);
    }
    else
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable to get connected media type, error: " << szErr << std::endl;
        return hr;
    }

    /*if (!mediaConnected)
    {
        uninitVideo();
        return false;
    }*/
    return hr;
}


//-----------------------------------------------------------------------------
// open: Depending on what type of media files we want to load, we 
//                will initialize the appropriate graph.  WMV (Requires a 
//                different source filter to operate properly)
//-----------------------------------------------------------------------------
bool DirectShowVideoWrapper::open(const std::string& ThePath, Window* const window)
{
    //Check that the file exists
    if(!boost::filesystem::exists(BoostPath(ThePath)))
    {
        SWARNING << "Could not open file: " << ThePath << ", because no such file exists." << std::endl;
        return false;
    }

    // Determine the file to load based on DirectX Media path (from SDK)
    // Use a helper function included in DXUtils.cpp
    std::vector<std::string> wmv_ext;
    wmv_ext.push_back("wmv");
    wmv_ext.push_back("wma");
    wmv_ext.push_back("asf");

    std::vector<std::string> mpg_ext;
    mpg_ext.push_back("mpg");
    mpg_ext.push_back("mpeg");
    mpg_ext.push_back("m2v");

    std::vector<std::string> avchd_ext;
    avchd_ext.push_back("mts");
    avchd_ext.push_back("m2ts");

    //Get the file extension
    std::string ext;
    std::string::size_type dot_pos(ThePath.find_last_of("."));
    if(dot_pos == std::string::npos)
    {
        SWARNING << "Could not determine extension of file: " << ThePath << std::endl;
        return false;
    }
    ext = ThePath.substr(dot_pos+1);
    std::transform(ext.begin(), ext.end(), ext.begin(), (int(*)(int)) std::tolower);// explicit cast needed to resolve ambiguity

    //Determine if the file is a WMV
    bool isWMV(false);
    for(UInt32 i(0) ; i<wmv_ext.size() ; ++i)
    {
        if(ext.compare(wmv_ext[i]) == 0)
        {
            isWMV = true;
            break;
        }
    }
    //Determine if the file is a MPG
    bool isMPG(false);
    for(UInt32 i(0) ; i<mpg_ext.size() ; ++i)
    {
        if(ext.compare(mpg_ext[i]) == 0)
        {
            isMPG = true;
            break;
        }
    }
    
    //Determine if the file is a AVCHD
    bool isAVCHD(false);
    for(UInt32 i(0) ; i<avchd_ext.size() ; ++i)
    {
        if(ext.compare(avchd_ext[i]) == 0)
        {
            isAVCHD = true;
            break;
        }
    }

    HRESULT hr = S_OK;
    TCHAR szErr[MAX_ERROR_TEXT_LEN];

    // Create the filter graph
    if(_pGraphBuilder == NULL)
    {
        hr = _pGraphBuilder.CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to Create FilterGraph object, error: " << szErr << std::endl;
            return hr;
        }
    }

    // Create the capture filter graph
    if(_pGraphCaptureBuilder == NULL)
    {
        hr = _pGraphCaptureBuilder.CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to Create CaptureFilterGraph object, error: " << szErr << std::endl;
            return hr;
        }
    }

    hr = _pGraphCaptureBuilder->SetFiltergraph(_pGraphBuilder);
    if (FAILED(hr))
    {
        AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
        SWARNING << "Unable to attach FilterGraph object, error: " << szErr << std::endl;
        return hr;
    }

    

    //Create the Source Filter
    if (isWMV) 
    {
        hr = ConnectWMVFile(ThePath);
        if (FAILED(hr))
        {
            SWARNING << "Could not connect wmv file: " << ThePath << std::endl;
            return false;
        }
    }
    else if(isMPG) 
    {
        hr = ConnectMPGFile(ThePath);
        if (FAILED(hr))
        {
            SWARNING << "Could not connect mpg file: " << ThePath << std::endl;
            return false;
        }
    }
    else if(isAVCHD) 
    {
        hr = ConnectAVCHDFile(ThePath);
        if (FAILED(hr))
        {
            SWARNING << "Could not connect AVCHD file: " << ThePath << std::endl;
            return false;
        }
    }
    else
    {
        // This is all other standard media types that do not use the 
        // Microsoft DirectX Media Objects
        hr = ConnectAVIFile(ThePath);
        if (FAILED(hr))
        {
            SWARNING << "Could not connect avi file: " << ThePath << std::endl;
            return false;
        }
    }

    // A Null Audio Renderer
    if(_pNullAudioFilter == NULL)
    {
        hr = _pNullAudioFilter.CoCreateInstance(CLSID_NullRenderer,   NULL, CLSCTX_INPROC_SERVER);
        if (FAILED(hr))
        {
            AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
            SWARNING << "Unable to create Null Audio Renderer, error: " << szErr << std::endl;
            return hr;
        }
    }

    //The Audio Renderer
    hr = FindAudioRenderer(_pGraphBuilder,&_pAudioRenderer);
    if (_pAudioRenderer == NULL)
    {
        SLOG << "Video has no Audio renderer." << std::endl;
    }


    if(FAILED(ConnectSampleGrabber()))
    {
        /*std::wstring WideFileName;
        WideFileName.assign(ThePath.begin(), ThePath.end());
        std::wstring WideFileNameGrf = WideFileName + L".grf";
        SaveGraphFile(_pGraphBuilder, const_cast<WCHAR*>(WideFileNameGrf.c_str()));*/
        return false;
    }


	_VideoInitialized = true;

    SLOG << "Successfully created filter graph for file: " << ThePath << std::endl;
	produceOpened();

    // Register the graph in the Running Object Table (for debug purposes)
    //AddGraphToROT(_pGraphBuilder, &dwROT);

    return true;
}

//void DirectShowVideoWrapper::CheckMovieStatus(void)
//{
//    long lEventCode;
//    LONG_PTR lParam1, lParam2;
//    HRESULT hr;
//
//    if (!_pMediaEvent)
//        return;
//        
//    // Check for completion events
//    hr = _pMediaEvent->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
//    if (SUCCEEDED(hr))
//    {
//        // If we have reached the end of the media file, reset to beginning
//        if (EC_COMPLETE == lEventCode) 
//        {
//            hr = _pMediaPosition->put_CurrentPosition(0);
//        }
//
//        // Free any memory associated with this event
//        hr = _pMediaEvent->FreeEventParams(lEventCode, lParam1, lParam2);
//    }
//}

//void DirectShowVideoWrapper::CleanupDShow(void)
//{
//#ifdef REGISTER_FILTERGRAPH
//    // Pull graph from Running Object Table (Debug)
//    RemoveGraphFromROT(dwROT);
//#endif
//
//    if (g_IFileSource)  g_IFileSource->Release();
//    if (_pSourceAudioPin)   _pSourceAudioPin.Release();
//    if (_pSourceVideoPin)   _pSourceVideoPin.Release();
//    if (_pSourceFilter)          _pSourceFilter.Release();
//    if (_pDecoderFilter)      _pDecoderFilter.Release();
//    if (_pVideoRenderer)     _pVideoRenderer.Release();
//    if (_DecoderOutputPin)    _DecoderOutputPin.Release();
//    if (g_pRenderer)    g_pRenderer.Release();
//
//    // Shut down the graph
//    if (_pMediaControl) _pMediaControl->Stop();
//
//    if (_pMediaControl) _pMediaControl.Release();
//    if (_pMediaEvent) _pMediaEvent.Release();
//    if (_pMediaPosition) _pMediaPosition.Release();
//    if (_pGraphBuilder) _pGraphBuilder.Release();
//
////    if (mpVMRAlloc) delete mpVMRAlloc;
//}

UInt32 DirectShowVideoWrapper::getWidth(void) const
{
    //TODO: Implement
    return _VideoWidth;
}

UInt32 DirectShowVideoWrapper::getHeight(void) const
{
    //TODO: Implement
    return _VideoHeight;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DirectShowVideoWrapper::DirectShowVideoWrapper(void) :
    Inherited(),
        _VideoInitialized(false),
        _FrameBuffer(NULL),
        _ReachEndOnce(false)
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
        _VideoInitialized(false),
        _FrameBuffer(NULL),
        _ReachEndOnce(false)
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

#endif /* OSG_WITH_DIRECT_SHOW */
