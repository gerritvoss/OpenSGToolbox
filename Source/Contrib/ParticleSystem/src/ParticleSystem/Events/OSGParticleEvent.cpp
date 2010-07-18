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

#include "OSGParticleEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleEventBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleEventTransitPtr ParticleEvent::create( FieldContainerRefPtr Source,
                                             Time TimeStamp,
                                             Int32 Index,
                                             const Pnt3f& Position,
                                             const Pnt3f& SecPosition,
                                             const Vec3f& Normal,
                                             const Color4f& Color,
                                             const Vec3f& Size,
                                             Real32 Lifespan,
                                             Real32 Age,
                                             const Vec3f& Velocity,
                                             const Vec3f& SecVelocity,
                                             const Vec3f& Acceleration,
                                             const StringToUInt32Map& Attributes,
                                             UInt32 ID)
{
    ParticleEvent* TheEvent = ParticleEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setParticleIndex(Index);
    TheEvent->setParticleID(ID);
    TheEvent->setParticlePosition(Position);
    TheEvent->setParticleSecPosition(SecPosition);
    TheEvent->setParticleNormal(Normal);
    TheEvent->setParticleColor(Color);
    TheEvent->setParticleSize(Size);
    TheEvent->setParticleLifespan(Lifespan);
    TheEvent->setParticleAge(Age);
    TheEvent->setParticleVelocity(Velocity);
    TheEvent->setParticleSecVelocity(SecVelocity);
    TheEvent->setParticleAcceleration(Acceleration);
    TheEvent->setParticleAttributes(Attributes);

    return ParticleEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleEvent::ParticleEvent(void) :
    Inherited()
{
}

ParticleEvent::ParticleEvent(const ParticleEvent &source) :
    Inherited(source)
{
}

ParticleEvent::~ParticleEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleEvent NI" << std::endl;
}

OSG_END_NAMESPACE
