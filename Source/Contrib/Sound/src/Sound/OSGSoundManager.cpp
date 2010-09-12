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

#include "OSGConfig.h"

#include "OSGSoundManager.h"

#include "OSGSound.h"
#include "OSGUpdateEventDetails.h"
#include "OSGStubSoundManager.h"

#ifdef OSG_WITH_FMOD
#include "OSGFModSoundManager.h"
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

StatElemDesc<StatIntElem> SoundManager::statNChannels("NChannels", 
                                                      "number of sound channels");

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
#ifdef OSG_WITH_FMOD
    return FModSoundManager::the();
#else
    return StubSoundManager::the();
#endif
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundManager::attachUpdateProducer(ReflexiveContainer* const producer)
{
    if(_UpdateEventConnection.connected())
    {
        _UpdateEventConnection.disconnect();
    }
    //Get the Id of the UpdateEvent
    const EventDescription* Desc(producer->getProducerType().findEventDescription("Update"));
    if(Desc == NULL)
    {
        SWARNING << "There is no Update event defined on " << producer->getType().getName() << " types." << std::endl;
    }
    else
    {
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&SoundManager::attachedUpdate, this, _1));
    }
}

void SoundManager::attachedUpdate(EventDetails* const details)
{
    update(dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime());
}

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

