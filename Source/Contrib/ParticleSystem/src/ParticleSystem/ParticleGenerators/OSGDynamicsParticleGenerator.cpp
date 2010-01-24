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

#include "OSGDynamicsParticleGenerator.h"
#include "OSGDistribution3D.h"
#include "OSGDistribution2D.h"
#include "OSGDistribution1D.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDynamicsParticleGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGDynamicsParticleGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DynamicsParticleGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DynamicsParticleGenerator::generateDynamic(ParticleSystemRefPtr System, Real32 AdditionalAging) const
{
    Pnt3f PositionReturnValue      (0.0,0.0f,0.0f);
    Pnt3f SecPositionReturnValue   (0.0,0.0f,0.0f);
    Vec3f NormalReturnValue        (0.0,0.0f,1.0f);
    Vec3f ColorReturnValue         (1.0,1.0f,1.0f);
    Vec3f SizeReturnValue          (1.0,1.0f,1.0f);
    Vec3f VelocityReturnValue      (0.0,0.0f,0.0f);
    Vec3f SecVelocityReturnValue   (0.0,0.0f,0.0f);
    Vec3f AccelerationReturnValue  (0.0,0.0f,0.0f);
    Real32 TransparencyReturnValue (1.0f);
    Time LifespanReturnValue       (1);
    Time AgeReturnValue            (0);
    StringToUInt32Map               AttributesReturnValue;


    if(getPositionDistribution() != NULL)
    {
        PositionReturnValue.setValue(getPositionDistribution()->generate().getValues());
    }
    if(getSecPositionDistribution() != NULL)
    {
        SecPositionReturnValue.setValue(getSecPositionDistribution()->generate().getValues());
    } else if(getPositionDistribution() != NULL)
    { // if the secondary position function is null and the primary position function isn't,
        // then we assign the secondary position to be the same as the primary position.  
        SecPositionReturnValue = PositionReturnValue;
    }

    if(getNormalDistribution() != NULL)
    {
        NormalReturnValue = getNormalDistribution()->generate();
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
    AgeReturnValue += AdditionalAging;
    if(getVelocityDistribution() != NULL)
    {
        VelocityReturnValue = getVelocityDistribution()->generate();
    }
    if(getSecVelocityDistribution() != NULL)
    {
        SecVelocityReturnValue = getSecVelocityDistribution()->generate();
    }
    if(getAccelerationDistribution() != NULL)
    {
        AccelerationReturnValue = getAccelerationDistribution()->generate();
    }

    generate(System,
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
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DynamicsParticleGenerator::DynamicsParticleGenerator(void) :
    Inherited()
{
}

DynamicsParticleGenerator::DynamicsParticleGenerator(const DynamicsParticleGenerator &source) :
    Inherited(source)
{
}

DynamicsParticleGenerator::~DynamicsParticleGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DynamicsParticleGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DynamicsParticleGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DynamicsParticleGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
