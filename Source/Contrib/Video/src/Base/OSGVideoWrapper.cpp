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

#include "OSGVideoWrapper.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVideoWrapperBase.cpp file.
// To modify it, please change the .fcd file (OSGVideoWrapper.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VideoWrapper::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VideoWrapper::open(const BoostPath& ThePath, WindowUnrecPtr TheWindow)
{
    //Check if the file exists
    if(boost::filesystem::exists(ThePath))
    {
        return open(ThePath.file_string(), TheWindow);
    }
    else
    {
        SWARNING << "VideoWrapper::open(): File " << ThePath.file_string() << " could not be opened, because no file by that path exists" << std::endl;
        return false;
    }
}

bool VideoWrapper::updateTexture(TextureObjChunkRefPtr TheTexture)
{
    bool Result(updateImage());

    if(_VideoImage != NULL)
    {
	    //if(!hasNPOT)
	    //{
		//    TheImage->scaleNextPower2(TheImage);
	    //}
	    if(TheTexture->getImage() != _VideoImage)
	    {
			    TheTexture->setImage(_VideoImage);
	    }
	    else
	    {
		    //tex->imageContentChanged();
	    }
    }
    return Result;
}

void VideoWrapper::addVideoListener(VideoListenerPtr Listener)
{
   _VideoListeners.insert(Listener);
}

void VideoWrapper::removeVideoListener(VideoListenerPtr Listener)
{
   VideoListenerSetItor EraseIter(_VideoListeners.find(Listener));
   if(EraseIter != _VideoListeners.end())
   {
      _VideoListeners.erase(EraseIter);
   }
}

void VideoWrapper::producePaused(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->paused(TheEvent);
    }
    _Producer.produceEvent(VideoPausedMethodId,TheEvent);
}

void VideoWrapper::produceUnpaused(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->unpaused(TheEvent);
    }
    _Producer.produceEvent(VideoUnpausedMethodId,TheEvent);
}

void VideoWrapper::produceStarted(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->started(TheEvent);
    }
    _Producer.produceEvent(VideoStartedMethodId,TheEvent);
}

void VideoWrapper::produceStopped(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->stopped(TheEvent);
    }
    _Producer.produceEvent(VideoStoppedMethodId,TheEvent);
}

void VideoWrapper::produceOpened(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->opened(TheEvent);
    }
    _Producer.produceEvent(VideoOpenedMethodId,TheEvent);
}

void VideoWrapper::produceClosed(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->closed(TheEvent);
    }
    _Producer.produceEvent(VideoClosedMethodId,TheEvent);
}

void VideoWrapper::produceEnded(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->ended(TheEvent);
    }
    _Producer.produceEvent(VideoEndedMethodId,TheEvent);
}

void VideoWrapper::produceSeeked(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->seeked(TheEvent);
    }
    _Producer.produceEvent(VideoSeekedMethodId,TheEvent);
}

void VideoWrapper::produceCycled(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->cycled(TheEvent);
    }
    _Producer.produceEvent(VideoCycledMethodId,TheEvent);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VideoWrapper::VideoWrapper(void) :
    Inherited()
{
}

VideoWrapper::VideoWrapper(const VideoWrapper &source) :
    Inherited(source)
{
}

VideoWrapper::~VideoWrapper(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VideoWrapper::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VideoWrapper::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VideoWrapper NI" << std::endl;
}

OSG_END_NAMESPACE
