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

#include "OSGRandomMovementParticleAffector.h"
#include "OSGParticleSystem.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"
#include "OSGPerlinNoiseDistribution1D.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRandomMovementParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGRandomMovementParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RandomMovementParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RandomMovementParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
    //System->setUpdateSecAttribs(false);
    Real32 x,
           y,
           z,
           age(System->getAge(ParticleIndex));

    if(getAttributeAffected() == VELOCITY_ATTRIBUTE)
    {
        Vec3f vel = System->getSecVelocity(ParticleIndex);
        // grab each value independently , and adjust the phase for each
        // axis, since we have a 3D phase and the 1D distribution only takes
        // one value
        Real32 velSum = vel.x() + vel.y() + vel.z();

        getPerlinDistribution()->setPhase(getPhase().x() + velSum);
        x = getPerlinDistribution()->generate(vel.x() + age);
        getPerlinDistribution()->setPhase(getPhase().y() + velSum);
        y = getPerlinDistribution()->generate(vel.y() + age);
        getPerlinDistribution()->setPhase(getPhase().z() + velSum);
        z = getPerlinDistribution()->generate(vel.z() + age);


        System->setVelocity(Vec3f(x,y,z) + vel,ParticleIndex);

    }else // affecting position	
    {
        Pnt3f pos = System->getSecPosition(ParticleIndex);
        Real32 posSum = pos.x() + pos.y() + pos.z();

        getPerlinDistribution()->setPhase(getPhase().x() + posSum);
        x = getPerlinDistribution()->generate(pos.x() + age);
        getPerlinDistribution()->setPhase(getPhase().y() + posSum);
        y = getPerlinDistribution()->generate(pos.y() + age);
        getPerlinDistribution()->setPhase(getPhase().z() + posSum);
        z = getPerlinDistribution()->generate(pos.z() + age);


        System->setPosition(Pnt3f(x,y,z) + pos.subZero(),ParticleIndex);
    }

    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void RandomMovementParticleAffector::onCreate(const RandomMovementParticleAffector *source)
{
    if(source != NULL)
    {
        //Shader Chunk
        PerlinNoiseDistribution1DRefPtr TheNoiseDist = PerlinNoiseDistribution1D::create();
        TheNoiseDist->setFrequency(getFrequency());
        TheNoiseDist->setPersistance(getPersistance());
        TheNoiseDist->setOctaves(getOctaves());
        TheNoiseDist->setAmplitude(getAmplitude());
        TheNoiseDist->setInterpolationType(getInterpolationType());
        TheNoiseDist->setPhase(getPhase().x());
        TheNoiseDist->setUseSmoothing(true);

        setPerlinDistribution(TheNoiseDist);
    }
}

void RandomMovementParticleAffector::onDestroy(void)
{
    if(getPerlinDistribution() != NULL)
    {
        setPerlinDistribution(NULL);
    }
}

/*----------------------- constructors & destructors ----------------------*/

RandomMovementParticleAffector::RandomMovementParticleAffector(void) :
    Inherited()
{
}

RandomMovementParticleAffector::RandomMovementParticleAffector(const RandomMovementParticleAffector &source) :
    Inherited(source)
{
}

RandomMovementParticleAffector::~RandomMovementParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RandomMovementParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & PersistanceFieldMask)
    {
        getPerlinDistribution()->setPersistance(getPersistance());
    } 
    else if (whichField & FrequencyFieldMask)
    {
        getPerlinDistribution()->setFrequency(getFrequency());
    } 
    else if (whichField & InterpolationTypeFieldMask)
    {
        getPerlinDistribution()->setInterpolationType(getInterpolationType());
    } 
    else if (whichField & OctavesFieldMask)
    {
        getPerlinDistribution()->setOctaves(getOctaves());
    } 
    else if (whichField & AmplitudeFieldMask )
    {
        getPerlinDistribution()->setAmplitude(getAmplitude());
    }
    else if (whichField & PhaseFieldMask )
    {
        getPerlinDistribution()->setPhase(getPhase()[0]);
    }
}

void RandomMovementParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump RandomMovementParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
