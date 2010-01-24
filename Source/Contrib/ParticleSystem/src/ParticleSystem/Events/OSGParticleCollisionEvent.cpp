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

#include "OSGParticleCollisionEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleCollisionEventBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleCollisionEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleCollisionEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleCollisionEventTransitPtr ParticleCollisionEvent::create(FieldContainerRefPtr Source,
                                                                Time TimeStamp,
                                                                ParticleSystemRefPtr PrimarySystem,
                                                                UInt32 PrimaryIndex,
                                                                ParticleSystemRefPtr SecondarySystem,
                                                                UInt32 SecondaryIndex)
{
    ParticleCollisionEvent* TheEvent = ParticleCollisionEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setPrimarySystem(PrimarySystem);
    TheEvent->setPrimaryParticleIndex(PrimaryIndex);
    TheEvent->setSecondarySystem(SecondarySystem);
    TheEvent->setSecondaryParticleIndex(SecondaryIndex);

    return ParticleCollisionEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleCollisionEvent::ParticleCollisionEvent(void) :
    Inherited()
{
}

ParticleCollisionEvent::ParticleCollisionEvent(const ParticleCollisionEvent &source) :
    Inherited(source)
{
}

ParticleCollisionEvent::~ParticleCollisionEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleCollisionEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleCollisionEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleCollisionEvent NI" << std::endl;
}

OSG_END_NAMESPACE
