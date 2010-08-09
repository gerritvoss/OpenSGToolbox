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

#include "OSGParticleCollisionEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleCollisionEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleCollisionEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleCollisionEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ParticleCollisionEventDetailsTransitPtr ParticleCollisionEventDetails::create(FieldContainer* const Source,
                                                                Time TimeStamp,
                                                                ParticleSystem* const PrimarySystem,
                                                                UInt32 PrimaryIndex,
                                                                ParticleSystem* const SecondarySystem,
                                                                UInt32 SecondaryIndex)
{
    ParticleCollisionEventDetails* TheEventDetails = ParticleCollisionEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setPrimarySystem(PrimarySystem);
    TheEventDetails->setPrimaryParticleIndex(PrimaryIndex);
    TheEventDetails->setSecondarySystem(SecondarySystem);
    TheEventDetails->setSecondaryParticleIndex(SecondaryIndex);

    return ParticleCollisionEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleCollisionEventDetails::ParticleCollisionEventDetails(void) :
    Inherited()
{
}

ParticleCollisionEventDetails::ParticleCollisionEventDetails(const ParticleCollisionEventDetails &source) :
    Inherited(source)
{
}

ParticleCollisionEventDetails::~ParticleCollisionEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleCollisionEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleCollisionEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleCollisionEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
