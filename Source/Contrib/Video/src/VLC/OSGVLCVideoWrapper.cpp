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
#include <OpenSG/OSGWIN32Window.h>
#endif


//#if __STDC_VERSION__ >= 199901L
//
//	#include <stdint.h>
//
//#else
//
//	#include <boost/cstdint.hpp>
//	using namespace boost;
//
//#endif

#include <vlc/vlc.h>
#include <vlc/libvlc_media_player.h>

#include "OSGVLCVideoWrapper.h"

#ifdef __APPLE__
#include <OpenSG/OSGCarbonWindow.h>
#include <AGL/agl.h>
#endif

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
    }
}

// Method for checking VLC exceptions
bool VLCVideoWrapper::VLC_Execption_catch (libvlc_exception_t ex, std::string message)
{
	bool error(false);
	// check if the passed exception is a problem
    if (libvlc_exception_raised (&ex))
    {
		// printing out what/where the exception happend (message should contain this info!)
		SWARNING << "A VLC exception occured: " << message << std::endl;
		SWARNING << libvlc_exception_get_message(&ex) << std::endl;
        error = true;
    }

    libvlc_exception_clear (&ex);

	return error;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VLCVideoWrapper::open(const std::string& ThePath, Window* const TheWindow)
{
	bool errorOpening(false);

	libvlc_exception_t ex; 
	libvlc_exception_init( &ex );
	
	// Creating some char[] to store the media options
	char clock[64], cunlock[64], cdata[64];
	char width[32], height[32], chroma[32], pitch[32];

    _VideoWidth = 1280;
    _VideoHeight = 1024;
	
	
	// We now need a struct for storing the video buffer
	// and a mutex to protect it.
	// The structure will be given as an arguments for the
	// lock/unlock callbacks.
	//struct ctx* _VideoMemContext;
	// Allocating the video buffer
	_VideoMemContext.pixels = ( UInt8* )malloc( ( sizeof( *( _VideoMemContext.pixels ) ) * _VideoWidth * _VideoHeight ) * 4 );
	// Allocating the mutex
	_VideoMemContext.lock = Lock::create();
	//_VideoMemContext.mainWindow = this;
	
	// Preparing the options for the media
	// The clock and cunlock contain a pointer to the associated
	// static method (note the use of %lld).
	//
	// In that specific case we can't use Qt:
	// The sprintf method of the QString does not support
	// length modifiers (like %lld).    
    /*
     *  Initialise libVLC
     */
    sprintf(clock, "%lld", (long long int)(intptr_t)lock);
    sprintf(cunlock, "%lld", (long long int)(intptr_t)unlock);
    sprintf(cdata, "%lld", (long long int)(intptr_t)&_VideoMemContext);
    sprintf(width, "%i", _VideoWidth);
    sprintf(height, "%i", _VideoHeight);
    sprintf(pitch, "%i", _VideoWidth * 3);

	// libvlc settings 
	const char* args[] = { 
        "-I", "dummy",                      /* no interface */
        "--vout=vmem",
        "--vmem-width", width,
        "--vmem-height", height,
        "--vmem-pitch", pitch,
        "--vmem-chroma", "RV24",
        "--vmem-lock", clock,
        "--vmem-unlock", cunlock,
        "--vmem-data", cdata,                  /* we don't want video (output) */
        //"--plugin-path=/Applications/VLC.app/Contents/MacOS/modules",                  /* we don't want video (output) */
        "--plugin-path=C:\\Users\\David\\Documents\\Work\\vlc-1.0.6-git\\plugins",                  /* we don't want video (output) */
        "--no-audio",                       /* we don't want audio */
        "--verbose=0",                      /* show only errors */
        "--no-media-library",               /* don't want that */
        "--services-discovery=",         /* nor that */
        "--no-video-title-show",            /* nor the filename displayed */
        "--no-stats",                       /* no stats */
        "--ignore-config",            /* don't use/overwrite the config */
        "--no-sub-autodetect",              /* don't want subtitles */
        "--control=",                    /* don't want interface (again) */
        /*"--no-inhibit=",                     [> i say no interface ! <]*/
        //"--extraintf=logger",                   /* ok, it will be a piece of cake */
		//"--verbose=3",
        "--no-disable-screensaver"         /* wanna fight ? */
    };
   // const char* const args[] = {
     //   "-I","dummy",                      /* no interface */
      //  "--ignore-config",									/* don't use/overwrite the config */
        //"--intf=dummy",                      /* no interface */
        //"--vout", "dummy",                  /* we want video (output)? */
        //"--vout=dummy",                  /* we want video (output)? */
      //  "--no-audio",                       /* we don't want audio */
      //  "--verbose=0",                      /* show only errors */
      //  "--no-media-library",               /* don't want */
      //  "--services-discovery=",         /* nor that */
      //  "--no-video-title-show",            /* nor the filename displayed */
      //  "--no-stats",                       /* no stats */
      //  "--no-sub-autodetect",              /* don't want subtitles */
      //  "--control=",                    /* don't want interface (again) */
        //"--no-inhibit",                     /* no interface ! */
      //  "--no-disable-screensaver",         /* no screensaver popping up  */
      //  "--extraintf=",	                /* ok, it will be a piece of cake */
		//		"--vout=minimal_macosx",
	//			"--opengl-provider=minimal_macosx",
	//			"--plugin-path=/Users/dtnaylor/Documents/Work/opensgtoolbox/VLC/modules"
    //};


	int nargs = sizeof(args) / sizeof(args[0]);
	libvlc_instance_t *libvlc = libvlc_new( nargs, args, &ex );
    errorOpening = VLC_Execption_catch(ex, "Error creating libvlc_instance_t.");
	

		// creates vlc struct holding data to the video file
	libvlc_media_t *TheMedia = libvlc_media_new( libvlc, ThePath.c_str(), &ex );
    errorOpening = VLC_Execption_catch(ex, "Error initializing media file.");
	
		// initialize a temporary media player so we can get height and width before
		// adding the vmem options to TheMedia
    libvlc_media_player_t * tempMediaPlayer = libvlc_media_player_new_from_media( TheMedia, &ex );
	  errorOpening =  VLC_Execption_catch(ex, "Error initializing temporary media player.");

		// get height and width of video
		/*_VideoWidth = libvlc_video_get_width (tempMediaPlayer, &ex);
		errorOpening = VLC_Execption_catch(ex, "Error getting width of the video.");
		_VideoHeight = libvlc_video_get_height (tempMediaPlayer, &ex);
		errorOpening = VLC_Execption_catch(ex, "Error getting heigh of the video.");
	
SLOG << "Width: " << _VideoWidth << std::endl;
SLOG << "Height: " << _VideoHeight << std::endl;	*/


	
	
	

	//sprintf( clock,   ":vmem-lock=%lld",   (long long int)(intptr_t)lock    );
	//sprintf( cunlock, ":vmem-unlock=%lld", (long long int)(intptr_t)unlock  );
	//sprintf( cdata,   ":vmem-data=%lld",   (long long int)(intptr_t)_VideoMemContext );
	//sprintf( width,   ":vmem-width=%i",    _VideoWidth           );
	//sprintf( height,  ":vmem-height=%i",   _VideoHeight          );
	////sprintf( chroma,  ":vmem-chroma=%s",   "RV24"                           );  
	//sprintf( pitch,   ":vmem-pitch=%i",    _VideoWidth*3       );		
	// List of options
	// This part can be easily replaced by a QStringList
	// instead of a C array.
	//char const* media_options[] =
	//{
	//	":vout=vmem",
	//	width, height,
	//	chroma, pitch,
	//	clock, cunlock,
	//	cdata
	//};
	//int media_options_size = sizeof( media_options )
	//						/ sizeof( *media_options );
	//// Adding each option from the array to the media
	//for ( int i = 0; i < media_options_size; ++i )
	//{
	//	libvlc_media_add_option( TheMedia, media_options[i], &ex );
	//	errorOpening = VLC_Execption_catch(ex, "Error adding options to TheMedia.");
	//}
	
	
	
	
	
   
	// initialize the media player
    mTheMediaPlayer = libvlc_media_player_new_from_media( TheMedia, &ex );
	errorOpening =  VLC_Execption_catch(ex, "Error initializing media player.");
	
	
	//set agl handle (if window is pointing to a carbon window)
#ifdef __APPLE__
	if (window->getType().isDerivedFrom(CarbonWindow::getClassType()))
	{
		HIWindowRef windowRef = aglGetWindowRef(CarbonWindowPtr::dcast(window)->getContext());
		
		HIViewRef contentView = 0;
		GetRootControl(windowRef, &contentView);
		
		
		//uint32_t aglHandler = CarbonWindowPtr::dcast(window)->winId();
		libvlc_media_player_set_agl (mTheMediaPlayer, reinterpret_cast<uint32_t>(contentView), &ex );
		errorOpening = VLC_Execption_catch(ex, "Error attaching media player to carbon window.");
	}
#else
#ifdef WIN32
	if (window->getType().isDerivedFrom(WIN32Window::getClassType()))
	{
		libvlc_media_player_set_hwnd (mTheMediaPlayer, WIN32WindowPtr::dcast(window)->getHwnd(), &ex );
		errorOpening = VLC_Execption_catch(ex, "Error attaching media player to WIN32 window.");
	}
#endif
#endif

		// release media file
    libvlc_media_release( TheMedia );
    

		// set position to the beginning of the file
	

    libvlc_media_player_play( mTheMediaPlayer, &ex );
    bool error = VLC_Execption_catch(ex, "Error playing the media.");

	// check if the player can be paused
	if(libvlc_media_player_can_pause(mTheMediaPlayer, &ex))
	{	// can pause it?  do it
		libvlc_media_player_pause(mTheMediaPlayer, &ex);
		// error checking of course
		errorOpening = VLC_Execption_catch(ex, "Error pausing media player.");
        
        libvlc_media_player_set_position( mTheMediaPlayer, 0.0f, &ex );
        errorOpening = VLC_Execption_catch(ex, "Error setting position during player initialization.");
	}

	


	// since we keep track of whether the vid is initialized...
	if(!errorOpening)
	{
		mInitialized = true;
	} else
	{
		mInitialized = false;
	}
	
	return errorOpening;
}

void VLCVideoWrapper::lock( struct ctx* ctx, void** pp_ret )	
{
    // Lock the buffer (to avoid concurrent access and data corruption)
    ctx->lock->acquire();

    // Tell libvlc to write the next frame into our pre-allocated buffer
    *pp_ret = ctx->pixels;	
}

void VLCVideoWrapper::unlock( struct ctx* ctx )	
{
    ctx->lock->release();
}

void VLCVideoWrapper::processNewFrame( struct ctx* ctx )	
{
    // Not sure why this needs to be here, but if it's not, we get errors
}

bool VLCVideoWrapper::open(BoostPath ThePath, Window* const TheWindow)
{
    return open(ThePath.string(), TheWindow);
}


bool VLCVideoWrapper::seek(Int64 SeekPos)
{
    SeekPos = osgClamp<Int64>(0,SeekPos,getDuration());
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );
    // jump the vid to SeekPos ms into the video
    libvlc_media_player_set_time(mTheMediaPlayer, SeekPos, &ex);
    bool error = VLC_Execption_catch(ex, "Error seeking in VLCVideoWrapper::seek()");

    if (!error) reachEndOnce = false;

    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::jump(Int64 Amount)
{
    Amount = osgClamp<Int64>(0,getPosition()+Amount,getDuration());

    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );
    // getting the current time in the movie and adding it to the desired time to jump
    Amount += libvlc_media_player_get_time(mTheMediaPlayer, &ex);
    // checking if there was an error gettin the time
    bool error = VLC_Execption_catch(ex, "Error jumping to point in VLCVideoWrapper::jump()");
    // no error? excellent, then jump fwd/bkwd Amount ms
    if(!error)
    {
        // GO to 'amount' time in the video
        libvlc_media_player_set_time(mTheMediaPlayer, Amount, &ex);
        // more error checking
        error = VLC_Execption_catch(ex, "Error jumping to point in VLCVideoWrapper::jump()");

    }
    // will return true if no errors occured
    return !error;
}


bool VLCVideoWrapper::setRate(Real32 Rate)
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );
    // set the playback rate
    libvlc_media_player_set_rate(mTheMediaPlayer, Rate, &ex);
    bool error = VLC_Execption_catch(ex, "Error setting player rate.");
    // will return true if no errors occured
    return !error;
}


Real32 VLCVideoWrapper::getRate(void) const
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    float playRate = libvlc_media_player_get_rate( mTheMediaPlayer, &ex );
    bool error = VLC_Execption_catch(ex, "Error getting player rate.");

    if(error)
    { // there was a problem, return 0.
        return 0.0f;
    } 
    else return playRate;
}

bool VLCVideoWrapper::play(void)
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    // play the video

    // start playing the video
    libvlc_media_player_play( mTheMediaPlayer, &ex );
    bool error = VLC_Execption_catch(ex, "Error playing the media.");

    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::pause(void)
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    // check if the player can be paused
    if(libvlc_media_player_can_pause(mTheMediaPlayer, &ex))
    {	// can pause it?  do it
        libvlc_media_player_pause(mTheMediaPlayer, &ex);
        // error checking of course
        bool error = VLC_Execption_catch(ex, "Error pausing media player in VLCVideoWrapper::pause()");
        if(!error) // 
            mPaused = true;
        else mPaused = false;
    }
    if(mPaused)
    {
        producePaused();
    }

    return mPaused;
}

bool VLCVideoWrapper::unpause(void)
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    if(mPaused) // don't need to unpause if it's not paused
    {
        libvlc_media_player_play(mTheMediaPlayer, &ex);
        // error checking
        bool error = VLC_Execption_catch(ex, "Error unpausing media in VLCVideoWrapper::unpause()");
        if(!error)
            mPaused = false;

    }
    if(!mPaused)
    {
        produceUnpaused();
    }
    // returns true is the player is unpaused!
    return !mPaused;
}

bool VLCVideoWrapper::pauseToggle(void)
{
    // pause if it's playing, unpause if it's not
    if(mPaused)
    {
        unpause();
        mPaused = false;
    } 
    else 
    {
        pause();
        mPaused = true;
    }
    return true;
}

bool VLCVideoWrapper::stop(void)
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );
    // vlc call to stop playing
    libvlc_media_player_stop(mTheMediaPlayer, &ex);
    // checking for error
    bool error = VLC_Execption_catch(ex, "Error stopping player in VLCVideoWrapper::stop()");
    // Probs??!?
    if(!error)
    {	
        mStopped = true;
        reachEndOnce = false;
    }
    // will return true if no errors occured
    return !error;
}

bool VLCVideoWrapper::close(void)
{
    libvlc_media_player_release(mTheMediaPlayer);// releases media currently in use

    libvlc_media_player_release(mTheMediaPlayer);// releases the media player itself

    // player is no longer initialized
    mInitialized = false;

    reachEndOnce = false;	

    // should always return true
    return true;
}

bool VLCVideoWrapper::isPlaying(void) const
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    bool error(false);
    // check if media player is playing 
    int playing = libvlc_media_player_is_playing(mTheMediaPlayer, &ex);
    // check for errors
    error = VLC_Execption_catch(ex, "Error checking play state in VLCVideoWrapper::isPlaying().");
    if(!error)
    {	// returns true if the media is playing
        return ((playing > 0)?(true):(false));
    } 
    else return false;
}

bool VLCVideoWrapper::isPaused(void) const
{	// we keep track of whether it's paused or not, no need to call vlc function
    return mPaused;
}

bool VLCVideoWrapper::isInitialized(void) const
{
    return mInitialized;
}

bool VLCVideoWrapper::isStopped(void) const
{	// we keep track of this, no need to call VLC function
    return mStopped;
}


Int64 VLCVideoWrapper::getPosition(void) const
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );

    // grabbing the time in ms
    libvlc_time_t currentTime = libvlc_media_player_get_time(mTheMediaPlayer,&ex);
    // extra vigilance
    VLC_Execption_catch(ex, "Error getting position in VLCVideoWrapper::getPosition().");
    // remember that this time is in ms
    return currentTime;
}

Int64 VLCVideoWrapper::getDuration(void) const
{
    libvlc_exception_t ex; 
    libvlc_exception_init( &ex );
    // just ask VLC for the vid length
    libvlc_time_t totalTime = libvlc_media_player_get_length(mTheMediaPlayer,&ex);
    VLC_Execption_catch(ex, "Error getting duratio: in VLCVideoWrapper::getDuration().");
    // libvlc_time_t is just a typedef for a 64 bit integer
    return totalTime;
}

UInt32 VLCVideoWrapper::getWidth(void) const
{
	libvlc_exception_t ex; 
	libvlc_exception_init( &ex );
	// just ask VLC for the vid length
	int width = libvlc_video_get_width(mTheMediaPlayer,&ex);
	VLC_Execption_catch(ex, "Error getting width: in VLCVideoWrapper::getWidth().");
	// libvlc_time_t is just a typedef for a 64 bit integer
	return width;
}

UInt32 VLCVideoWrapper::getHeight(void) const
{
	libvlc_exception_t ex; 
	libvlc_exception_init( &ex );
	// just ask VLC for the vid length
	int height = libvlc_video_get_height(mTheMediaPlayer,&ex);
	VLC_Execption_catch(ex, "Error getting height: in VLCVideoWrapper::getHeight().");
	// libvlc_time_t is just a typedef for a 64 bit integer
	return height;
}


Image* VLCVideoWrapper::getCurrentFrame(void)
{
    updateImage();

    return _VideoImage;
}

bool VLCVideoWrapper::updateImage(void)
{	
    if(_VideoImage == NULL ||
       _VideoImage->getWidth() != videoWidth ||
       _VideoImage->getHeight() != videoHeight)
    {
        _VideoImage = Image::create();
        try
        {
            _VideoImage->set(
#if BYTE_ORDER == LITTLE_ENDIAN
                             Image::OSG_BGR_PF,
#else
                             Image::OSG_RGB_PF,
#endif
                             videoWidth,
                             videoHeight,
                             1,1,1,0.0,
                             reinterpret_cast<const UInt8*>(context->pixels),
                             Image::OSG_UINT8_IMAGEDATA);
        }
        catch(...)
        {
            SWARNING << "VLCVideoWrapper::updateImage(): Error updateing Image object." << std::endl;
            _VideoImage= NULL;
            return false;
        }
    }
    else
    {
        _VideoImage->setData(reinterpret_cast<const UInt8*>(context->pixels));		
    }
    if(!reachEndOnce &&
       (getPosition() >= 0 &&
        getDuration() >= 0 &&
        getPosition() >= getDuration()))
    {
        reachEndOnce = true;
        produceEnded();
    }

    //libvlc_exception_t ex; 
    //libvlc_exception_init( &ex );


    // get height and width of video
    //videoWidth = libvlc_video_get_width (mTheMediaPlayer, &ex);
    //VLC_Execption_catch(ex, "Error getting width of the video.");
    //videoHeight = libvlc_video_get_height (mTheMediaPlayer, &ex);
    //VLC_Execption_catch(ex, "Error getting heigh of the video.");

    //SLOG << "Width: " << videoWidth << std::endl;
    //SLOG << "Height: " << videoHeight << std::endl;	


    return true;
    //}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VLCVideoWrapper::VLCVideoWrapper(void) :
    Inherited(),
		reachEndOnce(false)
{
}

#if 0
VLCVideoWrapper::VLCVideoWrapper(void *carbonWindow) :
    Inherited(),
		reachEndOnce(false)
{
		theCarbonWindow = carbonWindow;
}

VLCVideoWrapper::VLCVideoWrapper(const VLCVideoWrapper &source, void *carbonWindow) :
    Inherited(source),
		reachEndOnce(false)
{
    theCarbonWindow = carbonWindow;
}
#endif

VLCVideoWrapper::VLCVideoWrapper(const VLCVideoWrapper &source) :
    Inherited(source),
		reachEndOnce(false)
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
