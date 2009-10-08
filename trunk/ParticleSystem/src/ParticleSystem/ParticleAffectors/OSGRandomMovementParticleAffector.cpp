/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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
	System->setUpdateSecAttribs(false);
	Real32 x,y,z,age(System->getAge(ParticleIndex));
	if(getAttributeAffected() == VELOCITY_ATTRIBUTE)
	{
			Vec3f vel = System->getSecVelocity(ParticleIndex);
			// grab each value independently , and adjust the phase for each
			// axis, since we have a 3D phase and the 1D distribution only takes
			// one value
			Real32 velSum = vel.x() + vel.y() + vel.z();

			beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
				getPerlinDistribution()->setPhase(getPhase().x() + velSum);
				x = getPerlinDistribution()->generate(vel.x() + age);
				getPerlinDistribution()->setPhase(getPhase().y() + velSum);
				y = getPerlinDistribution()->generate(vel.y() + age);
				getPerlinDistribution()->setPhase(getPhase().z() + velSum);
				z = getPerlinDistribution()->generate(vel.z() + age);
			endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
			

			System->setVelocity(Vec3f(x,y,z) + vel,ParticleIndex);

	}else // affecting position	
	{
			Pnt3f pos = System->getSecPosition(ParticleIndex);
			Real32 posSum = pos.x() + pos.y() + pos.z();

			beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
				getPerlinDistribution()->setPhase(getPhase().x() + posSum);
				x = getPerlinDistribution()->generate(pos.x() + age);
				getPerlinDistribution()->setPhase(getPhase().y() + posSum);
				y = getPerlinDistribution()->generate(pos.y() + age);
				getPerlinDistribution()->setPhase(getPhase().z() + posSum);
				z = getPerlinDistribution()->generate(pos.z() + age);
			endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
			

			System->setPosition(Pnt3f(x,y,z) + pos,ParticleIndex);
	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void RandomMovementParticleAffector::randomize(Real32 &x, Real32&y, Real32&z, Int32 Index)
{
	Real32 swap(0.0f);
	switch(Index%6)
	{
	case 0:
		// no swapping
		break;
	case 1:
		swap = x;
		x = y;
		y = z;
		z = swap;
		break;

	case 2:
		swap = y;
		y = x;
		x = swap;
		break;

	case 3:
		swap = y;
		y = z;
		z = swap;
		break;

	case 4:
		swap = y;
		x = z;
		y = x;
		z = swap;
		break;

	case 5:
		swap = x;
		x = z;
		z = swap;
		break;

	default: // if this gets hit, there are big problems with math
		break;
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

void RandomMovementParticleAffector::onCreate(const RandomMovementParticleAffector *source)
{
    //Shader Chunk
    PerlinNoiseDistribution1DPtr TheNoiseDist = PerlinNoiseDistribution1D::create();
    beginEditCP(TheNoiseDist);
        TheNoiseDist->setFrequency(getFrequency());
        TheNoiseDist->setPersistance(getPersistance());
        TheNoiseDist->setOctaves(getOctaves());
        TheNoiseDist->setAmplitude(getAmplitude());
        TheNoiseDist->setInterpolationType(getInterpolationType());
        TheNoiseDist->setPhase(getPhase().x());
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
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PersistanceFieldMask);
			getPerlinDistribution()->setPersistance(getPersistance());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PersistanceFieldMask);
	} 
	else if (whichField & FrequencyFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::FrequencyFieldMask);
			getPerlinDistribution()->setFrequency(getFrequency());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::FrequencyFieldMask);
	} 
	else if (whichField & InterpolationTypeFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::InterpolationTypeFieldMask);
			getPerlinDistribution()->setInterpolationType(getInterpolationType());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::InterpolationTypeFieldMask);
	} 
	else if (whichField & OctavesFieldMask)
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::OctavesFieldMask);
			getPerlinDistribution()->setOctaves(getOctaves());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::OctavesFieldMask);
	} 
	else if (whichField & AmplitudeFieldMask )
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::AmplitudeFieldMask);
			getPerlinDistribution()->setAmplitude(getAmplitude());
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::AmplitudeFieldMask);
	}
	else if (whichField & PhaseFieldMask )
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
			getPerlinDistribution()->setPhase(getPhase()[0]);
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
	}
}

void RandomMovementParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RandomMovementParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE

