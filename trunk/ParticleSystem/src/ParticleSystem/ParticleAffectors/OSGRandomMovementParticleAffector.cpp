/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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

#include "OSGRandomMovementParticleAffector.h"

#include "ParticleSystem/OSGParticleSystem.h"
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RandomMovementParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RandomMovementParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RandomMovementParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	switch(getAttributeAffected())
	{
	case ACCELERATION_ATTRIBUTE:
		break;
	case VELOCITY_ATTRIBUTE:
		break;
	case POSITION_ATTRIBUTE:
	default:
		break;
	}
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void RandomMovementParticleAffector::onCreate(const RandomMovementParticleAffector *source)
{
    //Shader Chunk
    PerlinNoiseDistribution3DPtr TheNoiseDist = PerlinNoiseDistribution3D::create();
    beginEditCP(TheNoiseDist);
        TheNoiseDist->setFrequency(getFrequency());
        TheNoiseDist->setPersistance(getPersistance());
        TheNoiseDist->setOctaves(getOctaves());
        TheNoiseDist->setAmplitude(getAmplitude());
        TheNoiseDist->setInterpolationType(getInterpolationType());
        TheNoiseDist->setPhase(getPhase());
        TheNoiseDist->setUseSmoothing(true);
    endEditCP(TheNoiseDist);

    addRefCP(TheNoiseDist);
    setPerlinDistribution(TheNoiseDist);
}

void RandomMovementParticleAffector::onDestroy(void)
{
    subRefCP(getPerlinDistribution());
    setPerlinDistribution(NullFC);
}

void RandomMovementParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	if(whichField & PersistanceFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::PersistanceFieldMask);
			getPerlinDistribution()->setPersistance(getPersistance());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::PersistanceFieldMask);
	} 
	else if (whichField & FrequencyFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::FrequencyFieldMask);
			getPerlinDistribution()->setFrequency(getFrequency());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::FrequencyFieldMask);
	} 
	else if (whichField & InterpolationTypeFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::InterpolationTypeFieldMask);
			getPerlinDistribution()->setInterpolationType(getInterpolationType());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::InterpolationTypeFieldMask);
	} 
	else if (whichField & OctavesFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::OctavesFieldMask);
			getPerlinDistribution()->setOctaves(getOctaves());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::OctavesFieldMask);
	} 
	else if (whichField & AmplitudeFieldMask )
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::AmplitudeFieldMask);
			getPerlinDistribution()->setAmplitude(getAmplitude());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::AmplitudeFieldMask);
	}
	else if (whichField & PhaseFieldMask )
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::PhaseFieldMask);
			getPerlinDistribution()->setPhase(getPhase()[0]);
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution3D::PhaseFieldMask);
	}
}

void RandomMovementParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RandomMovementParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE

