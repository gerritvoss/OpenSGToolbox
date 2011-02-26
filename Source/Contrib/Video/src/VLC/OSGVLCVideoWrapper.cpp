/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#include "OSGConfig.h"

#ifdef OSG_WITH_VLC

#ifdef WIN32
#include <Windowsx.h>
#include "OSGWIN32Window.h"
#endif

#include <vlc/vlc.h>
#include <vlc/libvlc_media_player.h>

#include "OSGVLCVideoWrapper.h"

#ifdef __APPLE__
#include "OSGCarbonWindow.h"
#include <AGL/agl.h>
#endif

#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVLCVideoWrapperBase.cpp file.
// To modify it, please change the .fcd file (OSGVLCVideoWrapper.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VLCVideoWrapper::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        SLOG << "VLC version: " << libvlc_get_version() << std::endl;
    }
}

// Method for checking VLC exceptions
bool VLCVideoWrapper::checkVLCError (const std::string& message)
{
    bool error(false);

    // check if there was an error
    if (libvlc_errmsg() != NULL)
    {
        // printing out what/where the exception happend (message should contain this info!)
        SWARNING << "VLC error occured while : " << message
                 << ". Error: " << libvlc_errmsg() << std::endl;
        error = true;
    }

    libvlc_clearerr();

    return error;
}

void* VLCVideoWrapper::lock( void* userData, void** plane )	
{
    //VLC wants to decode the video

    // Lock the buffer (to avoid concurrent access and data corruption)
    reinterpret_cast<struct ctx*>(userData)->_lock->acquire();

    // Tell libvlc to write the next frame into our pre-allocated buffer
    *plane = reinterpret_cast<struct ctx*>(userData)->_pixels;	

    return NULL;/* picture identifier, not needed here */
}

void VLCVideoWrapper::unlock( void* userData, void* picture, void* const* plane )	
{
    //VLC just decoded the video
    reinterpret_cast<struct ctx*>(userData)->_lock->release();
}

void VLCVideoWrapper::display(void* userData, void* picture)
{
    reinterpret_cast<struct ctx*>(userData)->_VideoWrapper->_NextFrameReady = true;
}

void VLCVideoWrapper::handleVLCEvents(const libvlc_event_t *pEvent, void *param)
{
   printf("receive event %s\n", libvlc_event_type_name(pEvent->type));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VLCVideoWrapper::open(const std::string& ThePath, Window* const TheWindow)
{
    bool errorOpening(false);

    //BoostPath PluginsDirPath("/Applications/VLC.app/Contents/MacOS/modules");
    BoostPath PluginsDirPath("/Applications/VLC-1.1.7.app/Contents/MacOS/modules");

    std::vector<std::string> VLCArguments;

    VLCArguments.push_back("-I");
    VLCArguments.push_back("dummy"); /* no interface */

    VLCArguments.push_back(std::string("--plugin-path=") + PluginsDirPath.string());

    //VLCArguments.push_back("--no-audio"); [> we don't want audio <]
    VLCArguments.push_back("--verbose=0"); /* show only errors */
    VLCArguments.push_back("--no-media-library");/* don't want that */
    VLCArguments.push_back("--services-discovery=");/* don't want that */
    VLCArguments.push_back("--no-video-title-show");/* don't want that */
    VLCArguments.push_back("--no-stats");/* don't want that */
    VLCArguments.push_back("--ignore-config"); /* don't use/overwrite the config */
    VLCArguments.push_back("--no-sub-autodetect");/* don't want subtitles */
    VLCArguments.push_back("--control=");/* don't want interface (again) */
    VLCArguments.push_back("--no-disable-screensaver");/* don't want that */

    // libvlc settings 
    const char** args = new const char*[VLCArguments.size()];
    for(UInt32 i(0) ; i<VLCArguments.size() ; ++i)
    {
        args[i] = VLCArguments[i].c_str();
    }

    /*
     *  Initialise libVLC
     */
    UInt32 nargs = VLCArguments.size();
    _VLCInstance = libvlc_new( nargs, args );
    if(_VLCInstance == NULL)
    {
        checkVLCError("creating new vlc instance");
        return false;
    }

    delete [] args;


    // creates vlc struct holding data to the video file
    libvlc_media_t *TheMedia = libvlc_media_new_path( _VLCInstance, ThePath.c_str() );
    checkVLCError("initializing media file");

    // initialize a temporary media player so we can get height and width before
    // adding the vmem options to TheMedia
    libvlc_media_player_t * tempMediaPlayer = libvlc_media_player_new_from_media( TheMedia );

    unsigned Width(200), Height(200);
    libvlc_video_set_callbacks(tempMediaPlayer,
                               lock,
                               unlock,
                               display,
                               &_VideoMemContext);

    _VideoMemContext._pixels = ( UInt8* )malloc( ( sizeof( *( _VideoMemContext._pixels ) )
                                                   * Width
                                                   * Height ) * 4 );

    libvlc_video_set_format(tempMediaPlayer,
                            "RV24",
                            Width,
                            Height,
                            Width * 3);

    //Release the media file
    libvlc_media_release( TheMedia );

    libvlc_media_player_play( tempMediaPlayer );
    checkVLCError("playing the media");

    libvlc_state_t currentState;
    do
    {
        currentState = libvlc_media_player_get_state(tempMediaPlayer);
        checkVLCError("getting state");
    } while(currentState != libvlc_Playing);

    int VLCResult;
    do
    {
        VLCResult = libvlc_video_get_size(tempMediaPlayer, 0, &Width, &Height);
    } while(VLCResult != 0);
    checkVLCError("getting size");
    libvlc_media_player_stop( tempMediaPlayer );
    libvlc_media_player_release(tempMediaPlayer);// releases media currently in use


    //Now that we have the size initialize the media again
    TheMedia = libvlc_media_new_path( _VLCInstance, ThePath.c_str() );
    checkVLCError("initializing media file");

    // initialize the media player
    _MediaPlayer = libvlc_media_player_new_from_media( TheMedia );
    checkVLCError("initializing media player");

    //Release the media file
    libvlc_media_release( TheMedia );

#ifdef __APPLE__
    //set agl handle (if TheWindow is pointing to a carbon window)
    if (TheWindow->getType().isDerivedFrom(CarbonWindow::getClassType()))
    {
        HIWindowRef windowRef = aglGetWindowRef(dynamic_cast<CarbonWindow* const>(TheWindow)->getContext());

        HIViewRef contentView = 0;
        GetRootControl(windowRef, &contentView);


        //uint32_t aglHandler = CarbonWindowPtr::dcast(TheWindow)->winId();
        libvlc_media_player_set_agl (_MediaPlayer, reinterpret_cast<uint32_t>(contentView) );
        checkVLCError("attaching media player to carbon window");
    }
#endif
#ifdef WIN32
    if (TheWindow->getType().isDerivedFrom(WIN32Window::getClassType()))
    {
        libvlc_media_player_set_hwnd (_MediaPlayer, dynamic_cast<WIN32Window* const>(TheWindow)->getHwnd() );
        checkVLCError("attaching media player to WIN32 window");
    }
#endif
#ifdef __linux
    if (TheWindow->getType().isDerivedFrom(XWindow::getClassType()))
    {
        libvlc_media_player_set_xwindow (_MediaPlayer, dynamic_cast<XWindow* const>(TheWindow)->getDisplay() );
        checkVLCError("attaching media player to Xwindow");
    }
#endif

    libvlc_video_set_callbacks(_MediaPlayer,
                               lock,
                               unlock,
                               display,
                               &_VideoMemContext);

    _VideoMemContext._pixels = ( UInt8* )malloc( ( sizeof( *( _VideoMemContext._pixels ) )
                                                   * Width
                                                   * Height ) * 4 );

    libvlc_video_set_format(_MediaPlayer,
                            "RV24",
                            Width,
                            Height,
                            Width * 3);

    //Start playing the video
    libvlc_media_player_play( _MediaPlayer );
    checkVLCError("playing the media");

    do
    {
        currentState = libvlc_media_player_get_state(_MediaPlayer);
        checkVLCError("getting state");
    } while(currentState != libvlc_Playing);

    clock_t endwait;
    endwait = clock () + 2 * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}



    _Initialized = true;

    // check if the player can be paused
    if(libvlc_media_player_can_pause(_MediaPlayer))
    {	// can pause it?  do it
        libvlc_media_player_pause(_MediaPlayer);
        // error checking of course
        checkVLCError("pausing media player");

        libvlc_media_player_set_position( _MediaPlayer, 0.0f );
        checkVLCError("setting position during player initialization");
    }

    return errorOpening;
}

bool VLCVideoWrapper::open(BoostPath ThePath, Window* const TheWindow)
{
    return open(ThePath.string(), TheWindow);
}

bool VLCVideoWrapper::seek(Real64 SeekPos)
{
    SeekPos = osgClamp<Real64>(0,SeekPos,getDuration());
    Real64 SeekInMS(SeekPos*1000.0);
    // jump the vid to SeekPos ms into the video
    libvlc_media_player_set_time(_MediaPlayer, SeekInMS);
    bool error = checkVLCError("seeking");

    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::jump(Real64 Amount)
{
    Amount = osgClamp<Real64>(0,getPosition()+Amount,getDuration());
    Real64 AmountInMS(Amount*1000.0);

    // getting the current time in the movie and adding it to the desired time to jump
    // checking if there was an error gettin the time
    bool error = checkVLCError("jumping");
    // no error? excellent, then jump fwd/bkwd Amount ms
    if(!error)
    {
        // GO to 'amount' time in the video
        libvlc_media_player_set_time(_MediaPlayer, AmountInMS);
        // more error checking
        error = checkVLCError("jumping");

    }
    // will return true if no errors occured
    return !error;
}


bool VLCVideoWrapper::setRate(Real64 Rate)
{
    // set the playback rate
    libvlc_media_player_set_rate(_MediaPlayer, Rate);
    bool error = checkVLCError("setting player rate");
    // will return true if no errors occured
    return !error;
}


Real64 VLCVideoWrapper::getRate(void) const
{

    float playRate = libvlc_media_player_get_rate( _MediaPlayer );
    bool error = checkVLCError("getting player rate");

    if(error)
    { // there was a problem, return 0.
        return 0.0f;
    } 
    else return playRate;
}

bool VLCVideoWrapper::play(void)
{
    // play the video
    // start playing the video
    libvlc_media_player_play( _MediaPlayer );
    bool error = checkVLCError("playing");

    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::pause(void)
{
    // check if the player can be paused
    if(libvlc_media_player_can_pause(_MediaPlayer))
    {	// can pause it?  do it
        libvlc_media_player_pause(_MediaPlayer);
        // error checking of course
        checkVLCError("pausing");
    }
    if(isPaused())
    {
        producePaused();
        return true;
    }
    else
    {
        return false;
    }

}

bool VLCVideoWrapper::unpause(void)
{

    if(isPaused()) // don't need to unpause if it's not paused
    {
        libvlc_media_player_play(_MediaPlayer);
        // error checking
        checkVLCError("unpausing");
    }
    if(!isPaused())
    {
        produceUnpaused();
        return true;
    }
    else
    {
        return false;
    }
}

bool VLCVideoWrapper::pauseToggle(void)
{
    // pause if it's playing, unpause if it's not
    if(isPaused())
    {
        unpause();
    } 
    else 
    {
        pause();
    }
    return true;
}

bool VLCVideoWrapper::stop(void)
{
    // vlc call to stop playing
    libvlc_media_player_stop(_MediaPlayer);
    // checking for error
    bool error = checkVLCError("stopping");

    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::close(void)
{
    if(_MediaPlayer != NULL)
    {
        libvlc_media_player_release(_MediaPlayer);// releases the media player itself
        _MediaPlayer = NULL;
    }

    if(_VLCInstance != NULL)
    {
        libvlc_release(_VLCInstance);
        _VLCInstance = NULL;
    }

    // player is no longer initialized
    _Initialized = false;

    // should always return true
    return true;
}

bool VLCVideoWrapper::isPlaying(void) const
{

    bool error(false);
    // check if media player is playing 
    int playing = libvlc_media_player_is_playing(_MediaPlayer);
    // check for errors
    error = checkVLCError("checking play state");
    if(!error)
    {	// returns true if the media is playing
        return ((playing > 0)?(true):(false));
    } 
    else
    {
        return false;
    }
}

bool VLCVideoWrapper::isPaused(void) const
{
    //Get the state of the medial player
    libvlc_state_t currentState = libvlc_media_player_get_state(_MediaPlayer);
    bool error = checkVLCError("getting pause state");

    return currentState == libvlc_Paused;
}

bool VLCVideoWrapper::isInitialized(void) const
{
    return _Initialized;
}

bool VLCVideoWrapper::isStopped(void) const
{
    //Get the state of the medial player
    libvlc_state_t currentState = libvlc_media_player_get_state(_MediaPlayer);
    bool error = checkVLCError("getting pause state");

    return currentState == libvlc_Stopped;
}


Real64 VLCVideoWrapper::getPosition(void) const
{
    // grabbing the time in ms
    // libvlc_time_t is just a typedef for a 64 bit integer
    libvlc_time_t currentTime = libvlc_media_player_get_time(_MediaPlayer);
    bool error = checkVLCError("getting position");

    //Convert into seconds
    return static_cast<Real64>(currentTime) / 1000.0;
}

Real64 VLCVideoWrapper::getDuration(void) const
{
    // just ask VLC for the vid length
    // libvlc_time_t is just a typedef for a 64 bit integer
    libvlc_time_t totalTime = libvlc_media_player_get_length(_MediaPlayer);
    bool error = checkVLCError("getting duration");

    return static_cast<Real64>(totalTime) / 1000.0;
}

UInt32 VLCVideoWrapper::getWidth(void) const
{
    unsigned width, height;
    libvlc_video_get_size(_MediaPlayer, 0, &width, &height);
    bool error = checkVLCError("getting width");

    return width;
}

UInt32 VLCVideoWrapper::getHeight(void) const
{
    unsigned width, height;
    libvlc_video_get_size(_MediaPlayer, 0, &width, &height);
    bool error = checkVLCError("getting height");

    return height;
}

bool VLCVideoWrapper::updateImage(void)
{
    //VLC wants the current frame to be displayed
    if(_NextFrameReady)
    {
        if(getImage() == NULL)
        {
            _NextFrameReady = false;
            ImageUnrecPtr NewImage(Image::create());
            setImage(NewImage);
            try
            {
                UInt32 Width(getWidth()),
                       Height(getHeight());

                _VideoMemContext._lock->acquire();
                getImage()->set(
#if BYTE_ORDER == LITTLE_ENDIAN
                                Image::OSG_BGR_PF,
#else
                                Image::OSG_RGB_PF,
#endif
                                Width,
                                Height,
                                1,1,1,0.0,
                                reinterpret_cast<const UInt8*>(_VideoMemContext._pixels),
                                Image::OSG_UINT8_IMAGEDATA);
                _VideoMemContext._lock->release();
            }
            catch(...)
            {
                SWARNING << "VLCVideoWrapper::updateImage(): Error updateing Image object." << std::endl;
                setImage(NULL);
                return false;
            }
        }
        else
        {
            getImage()->setData(reinterpret_cast<const UInt8*>(_VideoMemContext._pixels));		
        }
        libvlc_state_t currentState = libvlc_media_player_get_state(_MediaPlayer);
        checkVLCError("Getting player state");
        if(currentState == libvlc_Ended)
        {
            produceEnded();
        }
        getImage()->mirror(false,true);		
    }

    return true;
}

bool VLCVideoWrapper::hasAudio(void) const
{
    int Result = libvlc_audio_get_track_count(_MediaPlayer);
    checkVLCError("Checking if video has audio");
    return (Result > 0);
}

void VLCVideoWrapper::enableAudio(void)
{
    /*! \todo Find better way to do this */
    setMute(true);
}

void VLCVideoWrapper::disableAudio(void)
{
    /*! \todo Find better way to do this */
    setMute(false);
}

bool VLCVideoWrapper::isAudioEnabled(void) const
{
    /*! \todo Find better way to do this */
    return isMuted();
}


Real32 VLCVideoWrapper::getAudioVolume(void) const
{
    int AudioVol(libvlc_audio_get_volume(_MediaPlayer));
    checkVLCError("getting audio volume");

    /*! \warning This is a hack, because vlc does not currently
     * provide the symbols AOUT_VOLUME_MAX, and AOUT_VOLUME_MIN  in their user
     * SDK.
     */
    const int VLC_MAX_AUDIO(200);
    const int VLC_MIN_AUDIO(0);

    return static_cast<Real32>(AudioVol - VLC_MIN_AUDIO)/static_cast<Real32>(VLC_MAX_AUDIO - VLC_MIN_AUDIO);
}

void VLCVideoWrapper::setAudioVolume(Real32 volume)
{
    /*! \warning This is a hack, because vlc does not currently
     * provide the symbols AOUT_VOLUME_MAX, and AOUT_VOLUME_MIN  in their user
     * SDK.
     */
    const int VLC_MAX_AUDIO(200);
    const int VLC_MIN_AUDIO(0);

    int VLCVolume((volume * (VLC_MAX_AUDIO - VLC_MIN_AUDIO - 1)) +VLC_MIN_AUDIO);
    libvlc_audio_set_volume(_MediaPlayer, VLCVolume);
    checkVLCError("setting audio volume");
}

void VLCVideoWrapper::setMute(bool Mute)
{
    libvlc_audio_set_mute(_MediaPlayer, (Mute ? 1 : 0));
    checkVLCError("muting volume");
}

bool VLCVideoWrapper::isMuted(void) const
{
    int MuteStatus(libvlc_audio_get_mute(_MediaPlayer));
    checkVLCError("getting mute volume");

    return (MuteStatus != 0);
}

bool VLCVideoWrapper::canSeekForward(void) const
{
    /*! \todo implement
    */
    return false;
}

bool VLCVideoWrapper::canSeekBackward(void) const
{
    /*! \todo implement
    */
    return false;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void VLCVideoWrapper::onCreate(const VLCVideoWrapper * Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        // Allocating the Lock
        _VideoMemContext._lock = Lock::get("VLCVideoWrapperLock", true);
        _VideoMemContext._VideoWrapper = this;
    }
}

void VLCVideoWrapper::onDestroy()
{
}

void VLCVideoWrapper::resolveLinks(void)
{
    Inherited::resolveLinks();

    close();
}

/*----------------------- constructors & destructors ----------------------*/

VLCVideoWrapper::VLCVideoWrapper(void) :
    Inherited(),
    _NextFrameReady(false),
    _Initialized(false)
{
}

VLCVideoWrapper::VLCVideoWrapper(const VLCVideoWrapper &source) :
    Inherited(source),
    _NextFrameReady(false),
    _Initialized(false)
{
}

VLCVideoWrapper::~VLCVideoWrapper(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VLCVideoWrapper::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VLCVideoWrapper::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VLCVideoWrapper NI" << std::endl;
}

OSG_END_NAMESPACE

#endif
