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

#include "OSGCollectiveGravityParticleSystemAffector.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCollectiveGravityParticleSystemAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGCollectiveGravityParticleSystemAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollectiveGravityParticleSystemAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CollectiveGravityParticleSystemAffector::affect(ParticleSystemRefPtr System, const Time& elps)
{
	Vec3f Force,Ftotal,LineSegment;
	Real32 DistanceSquared;
	Pnt3f CenterMass, TempCenterMass;

	//calculate Center Mass of all particles
	for(UInt32 i(0); i < System->getNumParticles(); ++i)
	{
		CenterMass = CenterMass + System->getPosition(i).subZero();
	}

	CenterMass*=1.0f/System->getNumParticles();
    Real32 MinDistSqr(getMinDistance()*getMinDistance()),
           MaxDistSqr(getMaxDistance()*getMaxDistance());
	
	for(UInt32 i(0); i < System->getNumParticles(); ++i)
	{
		TempCenterMass = CenterMass - Vec3f(System->getPosition(i) * (1.0/System->getNumParticles()));
		DistanceSquared = System->getPosition(i).dist2(TempCenterMass);
		if(DistanceSquared > 0 &&
           (getMinDistance() < 0.0f || DistanceSquared >= MinDistSqr) &&
           (getMaxDistance() < 0.0f || DistanceSquared <= MaxDistSqr))
		{
			Force = (getGravitationalConstant() * getParticleMass()* getParticleMass() * (System->getNumParticles()-1)* (TempCenterMass - System->getPosition(i)))* (1.0/DistanceSquared);
            if(getParticleMass() != 0.0f)
            {
		        System->setAcceleration(System->getAcceleration(i) + Force/getParticleMass(),i);
            }
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollectiveGravityParticleSystemAffector::CollectiveGravityParticleSystemAffector(void) :
    Inherited()
{
}

CollectiveGravityParticleSystemAffector::CollectiveGravityParticleSystemAffector(const CollectiveGravityParticleSystemAffector &source) :
    Inherited(source)
{
}

CollectiveGravityParticleSystemAffector::~CollectiveGravityParticleSystemAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollectiveGravityParticleSystemAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CollectiveGravityParticleSystemAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CollectiveGravityParticleSystemAffector NI" << std::endl;
}

OSG_END_NAMESPACE
