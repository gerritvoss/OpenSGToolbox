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

#include "OSGSoundEmitter.h"
#include "OSGUpdateEventDetails.h"
#include "OSGNode.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundEmitterBase.cpp file.
// To modify it, please change the .fcd file (OSGSoundEmitter.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundEmitter::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SoundEmitter::emitSound(void)
{
    if(getSound() != NULL)
    {
        _EmittedSoundChannels.insert(getSound()->play());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SoundEmitter::update(EventDetails* const details)
{
	OSG_ASSERT(getParents().size() == 1 && "A Sound Emitter NodeCore MUST have 1 and only 1 parent.");

    Matrix wm;
    dynamic_cast<Node*>(_mfParents[0])->getToWorld(wm);
    Pnt3f Position(0, 0, 0);
    wm.mult(Pnt3f(0.0f,0.0f,0.0f),Position);

    if(getSound() != NULL)
    {
        //Remove all invalid
        for(std::set<UInt32>::iterator Itor(_EmittedSoundChannels.begin()) ; Itor != _EmittedSoundChannels.end() ;)
        {
            if(!getSound()->isValid(*Itor))
            {
                std::set<UInt32>::iterator EraseItor(Itor);
                ++Itor;
                _EmittedSoundChannels.erase(EraseItor);
            }
            else
            {

                //getSound()->setChannelVelocity(_PreviousPosition - Position * (1.0f/dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime()), *Itor);
                

                getSound()->setChannelPosition(Position, *Itor);
                ++Itor;
            }
        }
    }

    _PreviousPosition = Position;
}

void SoundEmitter::attachUpdateProducer(ReflexiveContainer* const producer)
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
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&SoundEmitter::update, this, _1));
    }
    if(getParents().size() > 0)
    {
        Matrix wm;
        dynamic_cast<Node*>(_mfParents[0])->getToWorld(wm);
        wm.mult(Pnt3f(0.0f,0.0f,0.0f),_PreviousPosition);
    }
}

/*----------------------- constructors & destructors ----------------------*/

SoundEmitter::SoundEmitter(void) :
    Inherited()
{
}

SoundEmitter::SoundEmitter(const SoundEmitter &source) :
    Inherited(source)
{
}

SoundEmitter::~SoundEmitter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundEmitter::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ParentsFieldMask && getParents().size() > 0)
    {
        Matrix wm;
        dynamic_cast<Node*>(_mfParents[0])->getToWorld(wm);
        wm.multFull(Pnt3f(0.0f,0.0f,0.0f),_PreviousPosition);
    }
}

void SoundEmitter::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SoundEmitter NI" << std::endl;
}

OSG_END_NAMESPACE

