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

#include "OSGAirParticleAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AirParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AirParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AirParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
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
			Vec3f particleDirFromField(particlePos.x() - translation.x(), particlePos.y() - translation.y(), particlePos.z() - translation.z()),
				  fieldDirection(getDirection()), newVelocity;
			particleDirFromField.normalize();
			fieldDirection.normalize();
			Real32 dotProduct = particleDirFromField.dot(fieldDirection);

			if(getUseSpread() && (dotProduct >= 1.0 - getSpread())) // particles only affected if within field 'spread'
			{
				// calculating effect of field
				particleDirFromField *= (elps * getSpeed() * getMagnitude())
										/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());
				
				// ensuring the particle is not moving faster than the field magnitude
				newVelocity = System->getVelocity(ParticleIndex);
				if(newVelocity.length() < std::abs(getMagnitude())) 
				{
					newVelocity += particleDirFromField;
					if(newVelocity.length() > std::abs(getMagnitude())) newVelocity *= getMagnitude()/newVelocity.length();
				}

				System->setVelocity(newVelocity,ParticleIndex);
				
			} 
			else if(!getUseSpread()) //particle velocity affected regardless of field spread
			{	
				fieldDirection *= (elps * getSpeed() * getMagnitude())
										/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());
				
				// ensuring the particle is not moving faster than the field magnitude
				newVelocity = System->getVelocity(ParticleIndex);
				if(newVelocity.length() < std::abs(getMagnitude()))
				{
					newVelocity += fieldDirection;
					if(newVelocity.length() > std::abs(getMagnitude())) newVelocity *= getMagnitude()/newVelocity.length();
				}

				System->setVelocity(newVelocity,ParticleIndex);

			}//end spread conditional
		} // end distance conditional
	} // end null beacon conditional

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AirParticleAffector::AirParticleAffector(void) :
    Inherited()
{
}

AirParticleAffector::AirParticleAffector(const AirParticleAffector &source) :
    Inherited(source)
{
}

AirParticleAffector::~AirParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AirParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AirParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AirParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGAIRPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGAIRPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGAIRPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

