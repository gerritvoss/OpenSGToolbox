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

#include "OSGDragParticleAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DragParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DragParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DragParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
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
			if(getUseDirection()) // field 'direction' affects the amount of drag exerted on particle
			{
				Vec3f particleVelocity = System->getVelocity(ParticleIndex);
				Vec3f projection(particleVelocity);
				projection.projectTo(getDirection());
				if(particleVelocity.length() < getSpeedAttenuation() && getSpeedAttenuation() > 0.0f)
				{
					/*particleVelocity -= projection * osgSgn(particleVelocity.dot(getDirection())) * (elps * getMagnitude() 
										* std::pow(particleVelocity.length()/getSpeedAttenuation(), 2)
										/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));*/

					double scaleDragEffect = (elps * getMagnitude() * std::pow(particleVelocity.length()/getSpeedAttenuation(), 2))
											/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());

					for(int i(0); i < 3; i++)
					{
						double tmp3 = getDirection()[i] * scaleDragEffect * particleVelocity[i];
						particleVelocity[i] -= getDirection()[i] * scaleDragEffect * particleVelocity[i];
					}

				}
				else
				{
			/*		particleVelocity -= projection * osgSgn(particleVelocity.dot(getDirection())) * (elps * getMagnitude()
										osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));*/

					double scaleDragEffect = (elps * getMagnitude())
											/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());

					for(int i(0); i < 3; i++)
					{
						double tmp3 = getDirection()[i] * scaleDragEffect * particleVelocity[i];
						particleVelocity[i] -= getDirection()[i] * scaleDragEffect * particleVelocity[i];
					}

				}
				System->setVelocity(particleVelocity,ParticleIndex);
			} 
			else  //particle velocity is affected regardless of direction
			{
				Vec3f particleVelocity = System->getVelocity(ParticleIndex);
				if(particleVelocity.length() < getSpeedAttenuation() && getSpeedAttenuation() > 0.0f)
				{
					particleVelocity -= particleVelocity * (elps * getMagnitude() * std::pow(particleVelocity.length()/getSpeedAttenuation(), 2)
										/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));
				}
				else
				{
					particleVelocity -= particleVelocity * (elps * getMagnitude()
										/osg::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));
				}
				System->setVelocity(particleVelocity,ParticleIndex);
			}
		}
	}

	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DragParticleAffector::DragParticleAffector(void) :
    Inherited()
{
}

DragParticleAffector::DragParticleAffector(const DragParticleAffector &source) :
    Inherited(source)
{
}

DragParticleAffector::~DragParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DragParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DragParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DragParticleAffector NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDRAGPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDRAGPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDRAGPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

