/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGConfig.h"

#include "OSGFModSoundManager.h"

#ifdef OSG_WITH_FMOD
#include "OSGFModSound.h"

#include "OSGStatCollector.h"

//fmod include files
#include "fmod_errors.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FModSoundManager
A FMod SoundManager Interface. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

FModSoundManager *FModSoundManager::_the = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

FModSoundManager *FModSoundManager::the(void)
{
    if(_the == NULL)
    {
        _the = new FModSoundManager();
    }

    return _the;
}

void FMOD_ERRCHECK(FMOD_RESULT result, std::string Location)
{
    if (result != FMOD_OK)
    {
        SWARNING << Location << ": FMod Error: " << FMOD_ErrorString(result) << std::endl;
    }
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

SoundTransitPtr FModSoundManager::createSound(void) const
{
    return SoundTransitPtr(FModSound::create());
}

bool FModSoundManager::init(void)
{
    SLOG << "FModSoundManager Initializing." << std::endl;

    FMOD_RESULT      result;
    unsigned int     version;
    int              numdrivers;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS        caps;
    char             name[256];

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&the()->_FModSystem);
    FMOD_ERRCHECK(result,"FModSoundManager: System_Create()");
    
    result = the()->_FModSystem->getVersion(&version);
    FMOD_ERRCHECK(result,"FModSoundManager: getVersion()");

    if (version < FMOD_VERSION)
    {
        SWARNING << "FModSoundManager: init: Error!  You are using an old version of FMOD " << version << ".  This program requires " << FMOD_VERSION << std::endl;
        return false;
    }
    
    result = the()->_FModSystem->getNumDrivers(&numdrivers);
    FMOD_ERRCHECK(result,"FModSoundManager: getNumDrivers()");

    if (numdrivers == 0)
    {
        result = the()->_FModSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        FMOD_ERRCHECK(result,"FModSoundManager: setOutput()");
    }
    else
    {
        result = the()->_FModSystem->getDriverCaps(0, &caps, 0, 0, &speakermode);
        FMOD_ERRCHECK(result,"FModSoundManager: getDriverCaps()");

        result = the()->_FModSystem->setSpeakerMode(speakermode);       /* Set the user selected speaker mode. */
        FMOD_ERRCHECK(result,"FModSoundManager: setSpeakerMode()");

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)             /* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
        {                                                   /* You might want to warn the user about this. */
            result = the()->_FModSystem->setDSPBufferSize(1024, 10);
            FMOD_ERRCHECK(result,"FModSoundManager: setDSPBufferSize()");
        }

        result = the()->_FModSystem->getDriverInfo(0, name, 256, 0);
        FMOD_ERRCHECK(result,"FModSoundManager: getDriverInfo()");

        if (strstr(name, "SigmaTel"))   /* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
        {
            result = the()->_FModSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
            FMOD_ERRCHECK(result,"FModSoundManager: setSoftwareFormat()");
        }
    }

    result = the()->_FModSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
    {
        result = the()->_FModSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        FMOD_ERRCHECK(result,"FModSoundManager: setSpeakerMode()");
            
        result = the()->_FModSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);/* ... and re-init. */
        FMOD_ERRCHECK(result,"FModSoundManager: init()");
    }

    SLOG << "FModSoundManager Successfully Initialized.  Using FMod version: " << version << std::endl;
    return true;
}

bool FModSoundManager::uninit(void)
{
    SLOG << "FModSoundManager Uninitializing." << std::endl;
    FMOD_RESULT      result;

    result = the()->_FModSystem->release();
    FMOD_ERRCHECK(result,"FModSoundManager: release()");
    
    SLOG << "FModSoundManager Successfully Uninitialized." << std::endl;
    return true;
}

void FModSoundManager::update(const Time& ElapsedTime)
{
    FMOD_RESULT result;

    //setup listener's position and orientation as camera's
    if(getCamera() != NULL)
    {
	    Matrix camW2S;
	    getCamera()->getViewing(camW2S, 1, 1);
	    Pnt3f LisenerPosition(0, 0, 0);
	    camW2S.mult(LisenerPosition,LisenerPosition);

	    Vec3f up(0, 1, 0);
	    camW2S.mult(up,up);

	    Vec3f forward(0, 0, -1);
	    camW2S.mult(forward,forward);
	    FMOD_VECTOR f_pos, f_vel, f_up, f_forward;
	    f_pos.x = LisenerPosition.x(); f_pos.y = LisenerPosition.y(); f_pos.z = LisenerPosition.z();
	    f_up.x = up.x(); f_up.y = up.y(); f_up.z = up.z();
	    f_forward.x = forward.x(); f_forward.y = forward.y(); f_forward.z = forward.z();

        //Calculate Velocity
	    f_vel.x = 0; f_vel.y = 0; f_vel.z = 0;
	    /*f_vel.x = ( _PreviousLisenerPosition.x() - LisenerPosition.x() ) / e.getElapsedTime();
        f_vel.y = ( _PreviousLisenerPosition.y() - LisenerPosition.y() ) / e.getElapsedTime();
        f_vel.z = ( _PreviousLisenerPosition.z() - LisenerPosition.z() ) / e.getElapsedTime();*/
        _PreviousLisenerPosition = LisenerPosition;
        
	    result = _FModSystem->set3DListenerAttributes(0, &f_pos, &f_vel, &f_forward, &f_up);
        FMOD_ERRCHECK(result,"FModSoundManager: set3DListenerAttributes()");
    }
    //else
    //{
    //    SWARNING << "FModSoundManager: The Camera is not attached to the sound manager.  This is required to update the listeners position and velocity." << std::endl;
    //}

	//call FMOD's update
	result = _FModSystem->update();
    FMOD_ERRCHECK(result,"FModSoundManager: update()");

    //Update the number of channels statistic
    StatIntElem *NChannelsStatElem = StatCollector::getGlobalElem(SoundManager::statNChannels);
    if(NChannelsStatElem)
    {
        int channels;
        _FModSystem->getChannelsPlaying(&channels);
        FMOD_ERRCHECK(result,"FModSoundManager: getChannelsPlaying()");
        NChannelsStatElem->set(channels);
    }

}

void FModSoundManager::setCamera(CameraUnrecPtr TheCamera)
{
    Inherited::setCamera(TheCamera);
    if(TheCamera != NULL)
    {
	    Matrix camW2S;
        TheCamera->getViewing(camW2S, 1, 1);
        _PreviousLisenerPosition.setValues(0.0,0.0,0.0);
        camW2S.mult(_PreviousLisenerPosition,_PreviousLisenerPosition);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FModSoundManager::FModSoundManager(void) :
    Inherited()
{	
}

FModSoundManager::FModSoundManager(const FModSoundManager &source) :
    Inherited(source)
{
}

FModSoundManager::~FModSoundManager(void)
{
}

OSG_END_NAMESPACE

#endif /* OSG_WITH_FMOD */
