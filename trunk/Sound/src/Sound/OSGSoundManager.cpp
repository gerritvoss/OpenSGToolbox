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

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGSoundManager.h"

#include "OSGSound.h"
#include "Stub/OSGStubSoundManager.h"

#ifdef _OSG_TOOLBOX_USE_FMOD_
#include "FMod/OSGFModSoundManager.h"
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SoundManager
A SoundManager Interface. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

SoundManager *SoundManager::_the = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

SoundManager *SoundManager::the(void)
{
    if(_the == NULL)
    {
        _the = getDefaultSoundManager();
    }

    if(_the == NULL)
    {
        SWARNING << "SoundManager: The Sound Manager is NULL.  Need to set the Sound Manager." << std::endl;
    }

    return _the;
}

void SoundManager::setSoundManager(SoundManager *manager)
{
    _the = manager;
}

SoundManager* SoundManager::getDefaultSoundManager(void)
{
#ifdef _OSG_TOOLBOX_USE_FMOD_
    return FModSoundManager::the();
#else
    return StubSoundManager::the();
#endif
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SoundManager::SoundManager(void)
{
}

SoundManager::SoundManager(const SoundManager &source)
{
}

SoundManager::~SoundManager(void)
{
}

OSG_END_NAMESPACE

