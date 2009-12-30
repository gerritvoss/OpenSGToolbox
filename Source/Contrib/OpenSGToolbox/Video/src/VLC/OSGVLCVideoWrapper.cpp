/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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

#ifdef _OSGTOOLBOX_VIDEO_USE_VLC

#include <Windowsx.h>


#if __STDC_VERSION__ >= 199901L

	#include <stdint.h>

#else

	#include <boost/cstdint.hpp>
	using namespace boost;

#endif

#include <vlc/vlc.h>
#include <vlc/libvlc_media_player.h>

#include "OSGVLCVideoWrapper.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VLCVideoWrapper

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VLCVideoWrapper::initMethod (void)
{
}

// Method for checking VLC exceptions
bool VLCVideoWrapper::VLC_Execption_catch (libvlc_exception_t ex, std::string message)
{
	bool error(false);
	// check if the passed exception is a problem
    if (libvlc_exception_raised (&ex))
    {
		// printing out what/where the exception happend (message should contain this info!)
		fprintf(stderr, "\nA VLC exception occured: %s \n", message);
        error = true;
    }

    libvlc_exception_clear (&ex);

	return error;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VLCVideoWrapper::open(Path ThePath)
{
	bool errorOpening(false);

	libvlc_exception_t ex; 

	// libvlc settings 
    const char* const args[] = {
        "-I", "dummy",                      /* no interface */
        "--vout", "dummy",                  /* we want video (output)? */
        "--no-audio",                       /* we don't want audio */
        "--verbose=0",                      /* show only errors */
        "--no-media-library",               /* don't want */
        "--services-discovery", "",         /* nor that */
        "--no-video-title-show",            /* nor the filename displayed */
        "--no-stats",                       /* no stats */
        "--ignore-config",					/* don't use/overwrite the config */
        "--no-sub-autodetect",              /* don't want subtitles */
        "--control", "",                    /* don't want interface (again) */
        "--no-inhibit",                     /* no interface ! */
        "--no-disable-screensaver",         /* no screensaver popping up  */
        "--extraintf", ""                   /* ok, it will be a piece of cake */
    };

	int nargs = sizeof(args) / sizeof(args[0]);
	libvlc_instance_t *libvlc = libvlc_new( nargs, args, &ex );
    errorOpening = VLC_Execption_catch(ex, "Error creating libvlc_instance_t.");

    // creates vlc struct holding data to the video file
	libvlc_media_t * TheMedia = libvlc_media_new( libvlc, ThePath.string().c_str(), &ex );
    errorOpening = VLC_Execption_catch(ex, "Error initializing media file.");
   
	// initialize the media player
    mTheMediaPlayer = libvlc_media_player_new_from_media( TheMedia, &ex );
	errorOpening =  VLC_Execption_catch(ex, "Error initializing media player.");

	// release media file
    libvlc_media_release( TheMedia );

    // set position to the beginning of the file
    libvlc_media_player_set_position( mTheMediaPlayer, 0.0f, &ex );
    errorOpening = VLC_Execption_catch(ex, "Error setting position during player initialization.");



	// setting the video output?  How to? need a drawable window? 
	// trying to open a windows window for now.
	WNDCLASS  wndClass;
    HWND hwnd;

	    // Win32 Init
    memset(&wndClass, 0, sizeof(wndClass));
    
    std::string ClassName("VLC Window");
    wndClass.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	//wndClass.lpfnWndProc		= (WNDPROC) Win32WindowEventProducer::staticWndProc;				// WndProc Handles Messages
	wndClass.cbClsExtra		= 0;						// No Extra Window Data
	wndClass.cbWndExtra		= 0;						// No Extra Window Data
	wndClass.hInstance		= GetModuleHandle(NULL);					// Set The Instance
	wndClass.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	//wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wndClass.hbrBackground	= NULL;						// No Background Required For GL
	wndClass.lpszMenuName		= NULL;						// We Don't Want A Menu
	wndClass.lpszClassName	= ClassName.c_str();

    if (!RegisterClass(&wndClass)) 
    {
        MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
    }


    RECT WindowRect;							// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=0;							// Set Left Value To 0
	WindowRect.right=100;						// Set Right Value To Requested Width
	WindowRect.top=0;							// Set Top Value To 0
	WindowRect.bottom=200;						// Set Bottom Value To Requested Height

    //Fullscreen
    //bool fullscreen(_IsFullscreen);
    bool fullscreen(false);


    DWORD		dwExStyle;									// Window Extended Style
	DWORD		dwStyle;									// Window Style

    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	
    
    //ShowCursor(true);						// Show/Hide Mouse Pointer

    // Create a Window
    hwnd = CreateWindowEx(	dwExStyle,				// Extended Style For The Window
				ClassName.c_str(),				// Class Name
				"Temp",					// Window Title
				WS_CLIPSIBLINGS |			// Required Window Style
				WS_CLIPCHILDREN |			// Required Window Style
				dwStyle,				// Selected Window Style
				WindowRect.left, WindowRect.top,					// Window Position
				WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
				WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
				NULL,					// No Parent Window
				NULL,					// No Menu
				wndClass.hInstance,				// Instance
				NULL);					// Don't Pass Anything To WM_CREATE

    if(!hwnd)
    {
        DWORD LastError = GetLastError();
        MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
    }

	libvlc_media_player_set_hwnd(mTheMediaPlayer, hwnd, &ex );
	errorOpening = VLC_Execption_catch(ex, "Error setting hwnd in VLCVideoWrapper::open()");
	
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


bool VLCVideoWrapper::seek(Int64 SeekPos)
{
	SeekPos = osgClamp<Int64>(0,SeekPos,getDuration());
	libvlc_exception_t ex; 
	// jump the vid to SeekPos ms into the video
	libvlc_media_player_set_time(mTheMediaPlayer, SeekPos, &ex);
	bool error = VLC_Execption_catch(ex, "Error seeking in VLCVideoWrapper::seek()");
	// will return true if no errors occured
	return !error;
}

bool VLCVideoWrapper::jump(Int64 Amount)
{
	Amount = osgClamp<Int64>(0,getPosition()+Amount,getDuration());

	libvlc_exception_t ex; 
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
	// set the playback rate
	libvlc_media_player_set_rate(mTheMediaPlayer, Rate, &ex);
	bool error = VLC_Execption_catch(ex, "Error setting player rate.");
	// will return true if no errors occured
	return !error;
}


Real32 VLCVideoWrapper::getRate(void) const
{
	libvlc_exception_t ex; 
	
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

	// play the video
	libvlc_media_player_play( mTheMediaPlayer, &ex );
	bool error = VLC_Execption_catch(ex, "Error starting media playback in VLCVideoWrapper::play().");
	// will return true if no errors occured
	return !error;
}

bool VLCVideoWrapper::pause(void)
{
	libvlc_exception_t ex; 

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

	return mPaused;
}

bool VLCVideoWrapper::unpause(void)
{
	libvlc_exception_t ex; 

	if(mPaused) // don't need to unpause if it's not paused
	{
		libvlc_media_player_play(mTheMediaPlayer, &ex);
		// error checking
		bool error = VLC_Execption_catch(ex, "Error unpausing media in VLCVideoWrapper::unpause()");
		if(!error)
			mPaused = false;

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
	} else 
	{
		pause();
		mPaused = true;
	}
	return true;
}

bool VLCVideoWrapper::stop(void)
{
	libvlc_exception_t ex; 
	// vlc call to stop playing
	libvlc_media_player_stop(mTheMediaPlayer, &ex);
	// checking for error
	bool error = VLC_Execption_catch(ex, "Error stopping player in VLCVideoWrapper::stop()");
	// Probs??!?
	if(!error) mStopped = true;
	// will return true if no errors occured
	return !error;
}

bool VLCVideoWrapper::close(void)
{
	libvlc_media_player_release(mTheMediaPlayer);// releases media currently in use

	libvlc_media_player_release(mTheMediaPlayer);// releases the media player itself

	// player is no longer initialized
	mInitialized = false;
	// should always return true
	return true;
}

bool VLCVideoWrapper::isPlaying(void) const
{
	libvlc_exception_t ex; 

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
	// just ask VLC for the vid length
	libvlc_time_t totalTime = libvlc_media_player_get_length(mTheMediaPlayer,&ex);
	// libvlc_time_t is just a typedef for a 64 bit integer
	return totalTime;
}


ImagePtr VLCVideoWrapper::getCurrentFrame(void)
{
	
	// creating image ptr to return
	ImagePtr currentFrame = Image::create();
	// ran into a wall, ouch
	// not sure about this whole vld_drawable_t deal going on
	beginEditCP(currentFrame);
		//currentFrame->set
	endEditCP(currentFrame);

	return currentFrame;
		
		
}

bool VLCVideoWrapper::updateImage(void)
{	
	// image stored somewhere? what's going on in this function?
	// _VideoImage ! use it!
	return false;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VLCVideoWrapper::VLCVideoWrapper(void) :
    Inherited()
{
}

VLCVideoWrapper::VLCVideoWrapper(const VLCVideoWrapper &source) :
    Inherited(source)
{
}

VLCVideoWrapper::~VLCVideoWrapper(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VLCVideoWrapper::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void VLCVideoWrapper::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump VLCVideoWrapper NI" << std::endl;
}


OSG_END_NAMESPACE

#endif

