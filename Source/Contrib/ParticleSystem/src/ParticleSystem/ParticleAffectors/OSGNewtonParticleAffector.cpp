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

#include "OSGNewtonParticleAffector.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"

#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNewtonParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGNewtonParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NewtonParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool NewtonParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
    Vec3f translation(0.0f,0.0f,0.0f);

    // getting affector's translation.
    if(getBeacon() != NULL)
    {
        Vec3f tmp;
        Quaternion tmp2;
        Matrix BeaconToWorld(getBeacon()->getToWorld());
        BeaconToWorld.getTransform(translation,tmp2,tmp,tmp2);
    }

    //distance from affector to particle
    Pnt3f particlePos = System->getPosition(ParticleIndex);
    Real32 distanceFromAffector = particlePos.dist(Pnt3f(translation.x(),translation.y(),translation.z())); 

    //only affect the particle if it is in range
    if((getMaxDistance() < 0.0 && distanceFromAffector >= getMinDistance()) 
       || (distanceFromAffector <= getMaxDistance() && distanceFromAffector >= getMinDistance())) 
    {	
        // get direction from particle to the affector
        Vec3f newtonianForce(particlePos.x() - translation.x(), particlePos.y() - translation.y(), particlePos.z() - translation.z());
        newtonianForce.normalize();
        // computing velocity change due to field
        newtonianForce = newtonianForce *
            ((-getMagnitude() * elps)/OSG::osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));

        //add acceleration
        if(getParticleMass() != 0.0f)
        {
		    System->setAcceleration(System->getAcceleration(ParticleIndex) + newtonianForce/getParticleMass(),ParticleIndex);
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

void NewtonParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void NewtonParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump NewtonParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
