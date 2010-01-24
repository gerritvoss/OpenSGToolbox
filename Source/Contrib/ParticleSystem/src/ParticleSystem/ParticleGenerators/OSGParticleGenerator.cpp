/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGParticleGenerator.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleGenerator::generate(ParticleSystemRefPtr System,
                                 Pnt3f& PositionReturnValue, 
                                 Pnt3f& SecPositionReturnValue, 
                                 Vec3f& NormalReturnValue,
                                 Color4f& ColorReturnValue,
                                 Vec3f& SizeReturnValue,
                                 Time& LifespanReturnValue,
                                 Time& AgeReturnValue,
                                 Vec3f& VelocityReturnValue,
                                 Vec3f& SecVelocityReturnValue,
                                 Vec3f& AccelerationReturnValue,
                                 StringToUInt32Map& AttributeReturnValue) const
{
    if(System != NULL)
    {
        if(getBeacon() == NULL || !getGenerateInWorldSpace())
        {
            System->addParticle(PositionReturnValue,
                                SecPositionReturnValue,
                                NormalReturnValue,
                                ColorReturnValue,
                                SizeReturnValue,
                                LifespanReturnValue,
                                AgeReturnValue,
                                VelocityReturnValue,
                                SecVelocityReturnValue,
                                AccelerationReturnValue,
                                AttributeReturnValue);
        }
        else
        {
            Matrix BeaconToWorld(getBeacon()->getToWorld());

            BeaconToWorld.mult(PositionReturnValue, PositionReturnValue);
            BeaconToWorld.mult(SecPositionReturnValue, SecPositionReturnValue);
            BeaconToWorld.mult(NormalReturnValue, NormalReturnValue);
            //SBeaconToWorld.mult(SizeReturnValue, SizeReturnValue);
            BeaconToWorld.mult(VelocityReturnValue, VelocityReturnValue);
            BeaconToWorld.mult(SecVelocityReturnValue, SecVelocityReturnValue);
            BeaconToWorld.mult(AccelerationReturnValue, AccelerationReturnValue);

            System->addWorldSpaceParticle(PositionReturnValue,
                                          SecPositionReturnValue,
                                          NormalReturnValue,
                                          ColorReturnValue,
                                          SizeReturnValue,
                                          LifespanReturnValue,
                                          AgeReturnValue,
                                          VelocityReturnValue,
                                          SecVelocityReturnValue,
                                          AccelerationReturnValue,
                                          AttributeReturnValue);

        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleGenerator::ParticleGenerator(void) :
    Inherited()
{
}

ParticleGenerator::ParticleGenerator(const ParticleGenerator &source) :
    Inherited(source)
{
}

ParticleGenerator::~ParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
