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
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>

#include "OSGTurbulenceParticleAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TurbulenceParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TurbulenceParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool TurbulenceParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	if(getBeacon() != NullFC)
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
			fieldAffect *= getAmplitude()* (elps/(osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax())));

			System->setVelocity(System->getVelocity(ParticleIndex) + fieldAffect, ParticleIndex);

		} // end distance conditional
	} // end null beacon conditional

	return false;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

bool TurbulenceParticleAffector::distributionIsNotInitialized()
{
	PerlinNoiseDistribution1DPtr dist(getPerlinDistribution());
	
	if(1.0f != getAmplitude() ||
		dist->getPersistance() != getPersistance() ||
		dist->getOctaves() != getOctaves() ||
		dist->getInterpolationType() != getInterpolationType() ||
		dist->getFrequency() != getFrequency()) return true;

	return false;
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

void TurbulenceParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(getPerlinDistribution() == NullFC || distributionIsNotInitialized())
	{
		setPerlinDistribution(osg::PerlinNoiseDistribution1D::create());
		beginEditCP(getPerlinDistribution());
			getPerlinDistribution()->setFrequency(getFrequency());
			getPerlinDistribution()->setPersistance(getPersistance());
			getPerlinDistribution()->setOctaves(getOctaves());
			getPerlinDistribution()->setAmplitude(1.0f);
			getPerlinDistribution()->setInterpolationType(getInterpolationType());
			getPerlinDistribution()->setPhase(getPhase()[0]);
			getPerlinDistribution()->setUseSmoothing(true);
		endEditCP(getPerlinDistribution());
	}
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
			getPerlinDistribution()->setAmplitude(1.0f);
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::AmplitudeFieldMask);
	}
	else if (whichField & PhaseFieldMask )
	{
		beginEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
			getPerlinDistribution()->setPhase(getPhase()[0]);
		endEditCP(getPerlinDistribution(), PerlinNoiseDistribution1D::PhaseFieldMask);
	}
}

void TurbulenceParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TurbulenceParticleAffector NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGTURBULENCEPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTURBULENCEPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTURBULENCEPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

