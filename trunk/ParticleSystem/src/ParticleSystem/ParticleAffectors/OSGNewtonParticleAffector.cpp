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

#include "OSGNewtonParticleAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NewtonParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NewtonParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool NewtonParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
		// getting affector's translation.  No affect is applied if the beacon cannot be found
	if(getBeacon() != NullFC)
	{
		Matrix BeaconToWorld(getBeacon()->getToWorld());
		Vec3f translation, tmp;
		Quaternion tmp2;
		BeaconToWorld.getTransform(translation,tmp2,tmp,tmp2);

		//distance from affector to particle
		Pnt3f particlePos = System->getPosition(ParticleIndex);
		Real32 distanceFromAffector = particlePos.dist(Pnt3f(translation.x(),translation.y(),translation.z())); 

		if((getMaxDistance() < 0.0) || (distanceFromAffector <= getMaxDistance())) //only affect the particle if it is in range
		{	
			// get direction from particle to the affector
			Vec3f newtonianForce(particlePos.x() - translation.x(), particlePos.y() - translation.y(), particlePos.z() - translation.z());
			newtonianForce.normalize();
			// computing velocity change due to field
			newtonianForce *= ((getMagnitude()/getParticleMass()) * elps)/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());
			// set new particle velocity
			System->setVelocity(newtonianForce + System->getVelocity(ParticleIndex),ParticleIndex);
		}
	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NewtonParticleAffector::NewtonParticleAffector(void) :
    Inherited()
{
}

NewtonParticleAffector::NewtonParticleAffector(const NewtonParticleAffector &source) :
    Inherited(source)
{
}

NewtonParticleAffector::~NewtonParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NewtonParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void NewtonParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump NewtonParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGNEWTONPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGNEWTONPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGNEWTONPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

