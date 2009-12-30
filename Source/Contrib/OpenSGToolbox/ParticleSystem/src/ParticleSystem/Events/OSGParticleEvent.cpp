/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>

#include "OSGParticleEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleEvent::initMethod (void)
{
}

ParticleEventPtr ParticleEvent::create( FieldContainerPtr Source,
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
                                             const StringToUInt32Map& Attributes)
{
    ParticleEventPtr TheEvent = ParticleEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setParticleIndex(Index);
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

    return TheEvent;
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

void ParticleEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleEvent NI" << std::endl;
}


OSG_END_NAMESPACE

