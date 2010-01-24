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

#include "OSGSurfaceParticleGenerator.h"
#include "OSGDistribution1D.h"
#include "OSGDistribution3D.h"
#include "OSGGeoSurfaceDistribution3D.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSurfaceParticleGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGSurfaceParticleGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SurfaceParticleGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool SurfaceParticleGenerator::generate(ParticleSystemRefPtr System, const Time& elps)
{
    Pnt3f PositionReturnValue     (0.0f,0.0f,0.0f);
    Pnt3f SecPositionReturnValue  (0.0f,0.0f,0.0f);
    Vec3f NormalReturnValue       (0.0f,0.0f,1.0f);
    Vec3f ColorReturnValue        (1.0,1.0f,1.0f);
    Vec3f SizeReturnValue         (1.0,1.0f,1.0f);
    Vec3f VelocityReturnValue     (0.0f,0.0f,0.0f);
    Vec3f SecVelocityReturnValue  (0.0f,0.0f,0.0f);
    Vec3f TangentReturnValue      (0.0f,0.0f,1.0f);
    Vec3f AccelerationReturnValue (0.0f,0.0f,0.0f);
    Real32 TransparencyReturnValue(1.0f);
    Time LifespanReturnValue      (-1);
    Time AgeReturnValue           (0);
    Real32 SpeedReturnValue       (0.0);
    StringToUInt32Map              AttributesReturnValue;

    Vec3f Tangent;

    if(getPositionVelocityDistribution() != NULL)
    {
        getPositionVelocityDistribution()->generate(PositionReturnValue, NormalReturnValue, Tangent);
        SecPositionReturnValue = PositionReturnValue;
    }

    if(getColorDistribution() != NULL)
    {
        ColorReturnValue = getColorDistribution()->generate();
    }

    if(getTransparencyDistribution() != NULL)
    {
        TransparencyReturnValue = getTransparencyDistribution()->generate();
    }
    Color4f FinalColorValue(ColorReturnValue[0],ColorReturnValue[1],ColorReturnValue[2],TransparencyReturnValue);

    if(getSizeDistribution() != NULL)
    {
        SizeReturnValue = getSizeDistribution()->generate();
    }

    if(getLifespanDistribution() != NULL)
    {
        LifespanReturnValue = getLifespanDistribution()->generate();
    }
    if(getAgeDistribution() != NULL)
    {
        AgeReturnValue = getAgeDistribution()->generate();
    }
    AgeReturnValue += elps;
    if(getSpeedDistribution() != NULL)
    {
        SpeedReturnValue = getSpeedDistribution()->generate();
    }

    if(getPositionVelocityDistribution() != NULL)
    {
        VelocityReturnValue = SpeedReturnValue * NormalReturnValue;
    }
    SecVelocityReturnValue = VelocityReturnValue;
    if(getAccelerationDistribution() != NULL)
    {
        AccelerationReturnValue = getAccelerationDistribution()->generate();
    }

    ParticleGenerator::generate(System,
                                PositionReturnValue, 
                                SecPositionReturnValue, 
                                NormalReturnValue,
                                FinalColorValue,
                                SizeReturnValue,
                                LifespanReturnValue,
                                AgeReturnValue,
                                VelocityReturnValue,
                                SecVelocityReturnValue,
                                AccelerationReturnValue,
                                AttributesReturnValue);



    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SurfaceParticleGenerator::SurfaceParticleGenerator(void) :
    Inherited()
{
}

SurfaceParticleGenerator::SurfaceParticleGenerator(const SurfaceParticleGenerator &source) :
    Inherited(source)
{
}

SurfaceParticleGenerator::~SurfaceParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SurfaceParticleGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SurfaceParticleGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SurfaceParticleGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
