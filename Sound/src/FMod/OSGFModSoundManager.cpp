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
#include "OSGFModSound.h"

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

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FModSoundManager::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/



void FModSoundManager::init(const char* arg, ...){
	va_list listPointer;
	va_start(listPointer, arg);
	const char* mediaPath = arg;
	const char* mediaFile = va_arg(listPointer, const char*);
	const int maxChannel = va_arg(listPointer, const int);
	
	va_end(listPointer);
	result = FMOD::EventSystem_Create(&this->eventSystem);
	result = eventSystem->init(maxChannel, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL);
	
	result = eventSystem->setMediaPath(mediaPath);
	result = eventSystem->load(mediaFile, 0, 0);
	result = eventSystem->set3DNumListeners(1);
}

void FModSoundManager::uninit(void)
{	
	if (eventSystem)
		eventSystem->release();
	eventSystem = NULL;
}

FMOD_RESULT FModSoundManager::getFmodResult(){
	return result;
}

FMOD::EventSystem* FModSoundManager::getFMODEventSystem()
{
	return eventSystem;
}



SoundPtr FModSoundManager::getSound(const char* path){
	if (!eventSystem)
		return (FModSoundPtr)NULL;
	FModSoundPtr s = FModSound::create();
	FMOD::Event* e;
	result = eventSystem->getEvent(path, FMOD_EVENT_DEFAULT, &e);
	s->setFModEvent(e);
	return s;
}

SoundPtr FModSoundManager::getSound(const int id){
	if (!eventSystem)
		return (FModSoundPtr)NULL;
	FModSoundPtr s = FModSound::create();
	FMOD::Event* e;
	result = eventSystem->getEventBySystemID(id, FMOD_EVENT_DEFAULT, &e);
	s->setFModEvent(e);
	return s;
}

void FModSoundManager::update(const Real32& elps){
	//setup listener's position and orientation as camera's
	Matrix camW2S;
	CameraPtr cam = this->getCamera();
	cam->getViewing(camW2S, 0, 0);
	Pnt3f org(0, 0, 0);
	camW2S.mult(org);
	//printf("position: %8f, %8f, %8f\r\n", org[0], org[1], org[2]);

	Vec3f up(0, 1, 0);
	camW2S.mult(up);
	//printf("up: %8f, %8f, %8f\r\n", up[0], up[1], up[2]);

	Vec3f forward(0, 0, -1);
	camW2S.mult(forward);
	//printf("forward: %8f, %8f, %8f\r\n", forward[0], forward[1], forward[2]);
	FMOD_VECTOR f_pos, f_vel, f_up, f_forward;
	f_pos.x = org[0]; f_pos.y = org[1]; f_pos.z = org[2];
	f_vel.x = 0; f_vel.y = 0; f_vel.z = 0;
	f_up.x = up[0]; f_up.y = up[1]; f_up.z = up[2];
	f_forward.x = forward[0]; f_forward.y = forward[1]; f_forward.z = forward[2];

	eventSystem->set3DListenerAttributes(0, &f_pos, &f_vel, &f_forward, &f_up);
	//call FMOD's update
	eventSystem->update();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FModSoundManager::FModSoundManager(void) :
    Inherited()
{	
	eventSystem = NULL;
}

FModSoundManager::FModSoundManager(const FModSoundManager &source) :
    Inherited(source)
{
}

FModSoundManager::~FModSoundManager(void)
{
	uninit();
}
void FModSoundManager::setListenerProperties(const Pnt3f &lstnrPos, const Vec3f &velocity, const Vec3f &forward, const Vec3f &up){	
	FMOD_VECTOR pos, vel, forwardDir, upDir;
	pos.x = lstnrPos[0]; pos.y = lstnrPos[1]; pos.z = lstnrPos[2];
	vel.x = velocity[0]; vel.y = velocity[1]; vel.z = velocity[2];
	forwardDir.x = forward[0]; forwardDir.y = forward[1]; forwardDir.z = forward[2];
	upDir.x = up[0]; upDir.y = up[1]; upDir.z = up[2];

	this->eventSystem->set3DListenerAttributes(0, &pos, &vel, &forwardDir, &upDir);
}
/*----------------------------- class specific ----------------------------*/

void FModSoundManager::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FModSoundManager::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FModSoundManager NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFMODSOUNDMANAGERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFMODSOUNDMANAGERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFMODSOUNDMANAGERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

