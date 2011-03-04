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

#include "OSGTurbulenceParticleAffector.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"
#include "OSGPerlinNoiseDistribution1D.h"

#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTurbulenceParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGTurbulenceParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TurbulenceParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool TurbulenceParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
	if(getBeacon() != NULL)
	{	
		Matrix BeaconToWorld(getBeacon()->getToWorld());
		Vec3f translation, tmp;
		Quaternion tmp2;
		BeaconToWorld.getTransform(translation,tmp2,tmp,tmp2);

		Pnt3f particlePos = System->getPosition(ParticleIndex);
		Real32 distanceFromAffector = particlePos.dist(Pnt3f(translation.x(),translation.y(),translation.z())); 

		if((getMaxDistance() < 0.0) || (distanceFromAffector <= getMaxDistance())) //only affect the particle if it is in range
		{	
			Real32 Xparam, Yparam, Zparam;

			Pnt3f pos(System->getPosition(ParticleIndex));
			getPerlinDistribution()->setPhase(getPhase()[0]);
			Xparam = getPerlinDistribution()->generate(pos[0]);
			getPerlinDistribution()->setPhase(getPhase()[1]);
			Yparam = getPerlinDistribution()->generate(pos[1]);
			getPerlinDistribution()->setPhase(getPhase()[2]);
			Zparam = getPerlinDistribution()->generate(pos[2]);

			Vec3f fieldAffect(Vec3f(Xparam, Yparam, Zparam));
			fieldAffect = fieldAffect * (getAmplitude()*
                                          (elps/(OSG::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()))));

			System->setVelocity(System->getVelocity(ParticleIndex) + fieldAffect, ParticleIndex);

		} // end distance conditional
	} // end null beacon conditional

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

bool TurbulenceParticleAffector::distributionIsNotInitialized(void)
{
    PerlinNoiseDistribution1DRefPtr dist(getPerlinDistribution());

    return (1.0f != getAmplitude() ||
            dist->getPersistance() != getPersistance() ||
            dist->getOctaves() != getOctaves() ||
            dist->getInterpolationType() != getInterpolationType() ||
            dist->getFrequency() != getFrequency());
}

/*----------------------- constructors & destructors ----------------------*/

TurbulenceParticleAffector::TurbulenceParticleAffector(void) :
    Inherited()
{
}

TurbulenceParticleAffector::TurbulenceParticleAffector(const TurbulenceParticleAffector &source) :
    Inherited(source)
{
}

TurbulenceParticleAffector::~TurbulenceParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TurbulenceParticleAffector::onCreate(const TurbulenceParticleAffector *Id)
{
    PerlinNoiseDistribution1DRefPtr Dist = PerlinNoiseDistribution1D::create();
    this->setPerlinDistribution(Dist);
}

void TurbulenceParticleAffector::onDestroy()
{
}

void TurbulenceParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(distributionIsNotInitialized())
    {
        getPerlinDistribution()->setFrequency(getFrequency());
        getPerlinDistribution()->setPersistance(getPersistance());
        getPerlinDistribution()->setOctaves(getOctaves());
        getPerlinDistribution()->setAmplitude(1.0f);
        getPerlinDistribution()->setInterpolationType(getInterpolationType());
        getPerlinDistribution()->setPhase(getPhase()[0]);
        getPerlinDistribution()->setUseSmoothing(true);
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
        getPerlinDistribution()->setAmplitude(1.0f);
    }
    else if (whichField & PhaseFieldMask )
    {
        getPerlinDistribution()->setPhase(getPhase()[0]);
    }
}

void TurbulenceParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TurbulenceParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
