/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Video                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
                           Authors: David Kabala                            
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEVIDEOLIB

#include <OpenSG/OSGConfig.h>

#include "OSGVideoWrapper.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VideoWrapper

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VideoWrapper::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->paused(TheEvent);
    }
    _Producer.produceEvent(VideoPausedMethodId,TheEvent);
}

void VideoWrapper::produceUnpaused(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->unpaused(TheEvent);
    }
    _Producer.produceEvent(VideoUnpausedMethodId,TheEvent);
}

void VideoWrapper::produceStarted(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->started(TheEvent);
    }
    _Producer.produceEvent(VideoStartedMethodId,TheEvent);
}

void VideoWrapper::produceStopped(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->stopped(TheEvent);
    }
    _Producer.produceEvent(VideoStoppedMethodId,TheEvent);
}

void VideoWrapper::produceOpened(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->opened(TheEvent);
    }
    _Producer.produceEvent(VideoOpenedMethodId,TheEvent);
}

void VideoWrapper::produceClosed(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->closed(TheEvent);
    }
    _Producer.produceEvent(VideoClosedMethodId,TheEvent);
}

void VideoWrapper::produceEnded(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->ended(TheEvent);
    }
    _Producer.produceEvent(VideoEndedMethodId,TheEvent);
}

void VideoWrapper::produceSeeked(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->seeked(TheEvent);
    }
    _Producer.produceEvent(VideoSeekedMethodId,TheEvent);
}

void VideoWrapper::produceCycled(void)
{
    VideoEventPtr TheEvent = VideoEvent::create(VideoWrapperPtr(this), getSystemTime());
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

void VideoWrapper::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void VideoWrapper::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump VideoWrapper NI" << std::endl;
}

OSG_END_NAMESPACE

