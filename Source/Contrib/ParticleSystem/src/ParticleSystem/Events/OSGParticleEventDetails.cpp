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

#include "OSGParticleEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleEventDetailsTransitPtr ParticleEventDetails::create( FieldContainer* const Source,
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
    ParticleEventDetails* TheEventDetails = ParticleEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setParticleIndex(Index);
    TheEventDetails->setParticleID(ID);
    TheEventDetails->setParticlePosition(Position);
    TheEventDetails->setParticleSecPosition(SecPosition);
    TheEventDetails->setParticleNormal(Normal);
    TheEventDetails->setParticleColor(Color);
    TheEventDetails->setParticleSize(Size);
    TheEventDetails->setParticleLifespan(Lifespan);
    TheEventDetails->setParticleAge(Age);
    TheEventDetails->setParticleVelocity(Velocity);
    TheEventDetails->setParticleSecVelocity(SecVelocity);
    TheEventDetails->setParticleAcceleration(Acceleration);
    TheEventDetails->setParticleAttributes(Attributes);

    return ParticleEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleEventDetails::ParticleEventDetails(void) :
    Inherited()
{
}

ParticleEventDetails::ParticleEventDetails(const ParticleEventDetails &source) :
    Inherited(source)
{
}

ParticleEventDetails::~ParticleEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
