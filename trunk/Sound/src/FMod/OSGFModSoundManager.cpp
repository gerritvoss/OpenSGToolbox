/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFModSoundManager.h"

#ifdef _OSG_TOOLBOX_USE_FMOD_
#include "OSGFModSound.h"

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

void FMOD_ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        SWARNING << "FModSoundManager:: FMod Error: " << FMOD_ErrorString(result) << std::endl;
    }
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

SoundPtr FModSoundManager::createSound(void) const
{
    return FModSound::create();
}

void FModSoundManager::init(void)
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
    result = FMOD::System_Create(&_FModSystem);
    FMOD_ERRCHECK(result);
    
    result = _FModSystem->getVersion(&version);
    FMOD_ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        SWARNING << "FModSoundManager::init: Error!  You are using an old version of FMOD " << version << ".  This program requires " << FMOD_VERSION << std::endl;
        return;
    }
    
    result = _FModSystem->getNumDrivers(&numdrivers);
    FMOD_ERRCHECK(result);

    if (numdrivers == 0)
    {
        result = _FModSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        FMOD_ERRCHECK(result);
    }
    else
    {
        result = _FModSystem->getDriverCaps(0, &caps, 0, 0, &speakermode);
        FMOD_ERRCHECK(result);

        result = _FModSystem->setSpeakerMode(speakermode);       /* Set the user selected speaker mode. */
        FMOD_ERRCHECK(result);

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)             /* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
        {                                                   /* You might want to warn the user about this. */
            result = _FModSystem->setDSPBufferSize(1024, 10);
            FMOD_ERRCHECK(result);
        }

        result = _FModSystem->getDriverInfo(0, name, 256, 0);
        FMOD_ERRCHECK(result);

        if (strstr(name, "SigmaTel"))   /* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
        {
            result = _FModSystem->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
            FMOD_ERRCHECK(result);
        }
    }

    result = _FModSystem->init(100, FMOD_INIT_NORMAL, 0);
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
    {
        result = _FModSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        FMOD_ERRCHECK(result);
            
        result = _FModSystem->init(100, FMOD_INIT_NORMAL, 0);/* ... and re-init. */
        FMOD_ERRCHECK(result);
    }

    SLOG << "FModSoundManager Successfully Initialized." << std::endl;
}

void FModSoundManager::uninit(void)
{
    SLOG << "FModSoundManager Uninitializing." << std::endl;
    FMOD_RESULT      result;

    result = _FModSystem->release();
    FMOD_ERRCHECK(result);
    
    SLOG << "FModSoundManager Successfully Uninitialized." << std::endl;
}

void FModSoundManager::update(const UpdateEvent& e)
{
    FMOD_RESULT result;

    //setup listener's position and orientation as camera's
	Matrix camW2S;
	CameraPtr cam = getCamera();
    if(cam != NullFC)
    {
	    cam->getViewing(camW2S, 1, 1);
	    Pnt3f org(0, 0, 0);
	    camW2S.multMatrixPnt(org);

	    Vec3f up(0, 1, 0);
	    camW2S.multMatrixVec(up);

	    Vec3f forward(0, 0, -1);
	    camW2S.multMatrixVec(forward);
	    FMOD_VECTOR f_pos, f_vel, f_up, f_forward;
	    f_pos.x = org.x(); f_pos.y = org.y(); f_pos.z = org.z();
	    f_vel.x = 0; f_vel.y = 0; f_vel.z = 0;
	    f_up.x = up.x(); f_up.y = up.y(); f_up.z = up.z();
	    f_forward.x = forward.x(); f_forward.y = forward.y(); f_forward.z = forward.z();

        
        std::cout << "Camera Position: " << org << std::endl;
        
	    result = _FModSystem->set3DListenerAttributes(0, &f_pos, &f_vel, &f_forward, &f_up);
        FMOD_ERRCHECK(result);
    }
    else
    {
        SWARNING << "FModSoundManager: The Camera is not attached to the sound manager.  This is required to update the listeners position and velocity." << std::endl;
    }

	//call FMOD's update
	result = _FModSystem->update();
    FMOD_ERRCHECK(result);
}

void FModSoundManager::setListenerProperties(const Pnt3f &lstnrPos, const Vec3f &velocity, const Vec3f &forward, const Vec3f &up)
{	
	/*FMOD_VECTOR pos, vel, forwardDir, upDir;
	pos.x = lstnrPos[0]; pos.y = lstnrPos[1]; pos.z = lstnrPos[2];
	vel.x = velocity[0]; vel.y = velocity[1]; vel.z = velocity[2];
	forwardDir.x = forward[0]; forwardDir.y = forward[1]; forwardDir.z = forward[2];
	upDir.x = up[0]; upDir.y = up[1]; upDir.z = up[2];

	this->eventSystem->set3DListenerAttributes(0, &pos, &vel, &forwardDir, &upDir);*/
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
	uninit();
}

OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_USE_FMOD_ */
