/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGCollisionParticleSystemAffector.h"
#include "OSGParticleSystem.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCollisionParticleSystemAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGCollisionParticleSystemAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionParticleSystemAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CollisionParticleSystemAffector::affect(ParticleSystemRefPtr System, const Time& elps)
{
    UInt32 PrimaryNumParticles(System->getNumParticles());
    Real32 MinDistSqr(getCollisionDistance() * getCollisionDistance());
    BoxVolume PrimaryVolume,SecondaryVolume;
    Matrix PrimaryMat(System->getBeacon()->getToWorld()),SecondaryMat;

    //Get the World Volume of the primary particle System
    PrimaryVolume = System->getBeacon()->getVolume();
    PrimaryVolume.transform(PrimaryMat);

    Pnt3f PrimaryPos,SecondaryPos;

    //Loop through all of the Collidable Systems
    for(UInt32 i(0) ; i<getMFSecondaryCollisionSystems()->size() ; ++i)
    {
        //Get the Volume of the Secondary System in world space
        SecondaryMat = System->getBeacon()->getToWorld();
        SecondaryVolume = getSecondaryCollisionSystems(i)->getBeacon()->getVolume();
        SecondaryVolume.transform(SecondaryMat);

        if(PrimaryVolume.intersect(SecondaryVolume))
        {
			getSecondaryCollisionSystems(i)->_isUpdating = true;
            //If the Volumes intersect then check for collisions
            UInt32 SecondaryNumParticles(getSecondaryCollisionSystems(i)->getNumParticles());
            for(UInt32 PrimaryIndex(0) ; PrimaryIndex<PrimaryNumParticles ; ++PrimaryIndex)
            {
                //Get the position of the Primary Particle in World Space
                PrimaryPos = PrimaryMat * System->getPosition(PrimaryIndex);
                for(UInt32 SecondaryIndex(0) ; SecondaryIndex<SecondaryNumParticles ; ++SecondaryIndex)
                {
                    //Get the position of the Secondary Particle in World Space
                    SecondaryPos = SecondaryMat * getSecondaryCollisionSystems(i)->getPosition(SecondaryIndex);

                    //Check if the points are close enough
                    if(MinDistSqr >= PrimaryPos.dist2(SecondaryPos))
                    {
                        produceParticleCollision(System,
                                                 PrimaryIndex,
                                                 getSecondaryCollisionSystems(i),
                                                 SecondaryIndex);
                    }
                }
            }
			getSecondaryCollisionSystems(i)->_isUpdating = false;
			getSecondaryCollisionSystems(i)->internalKillParticles();
        }
    }
}

void CollisionParticleSystemAffector::produceParticleCollision(ParticleSystem* const System,
                                                               UInt32 PrimaryIndex,
                                                               ParticleSystem* const SecondarySystem,
                                                               UInt32 SecondaryIndex)
{
    ParticleCollisionEventDetailsUnrecPtr Details = ParticleCollisionEventDetails::create(this,
                                                                            getSystemTime(),
                                                                            System,
                                                                            PrimaryIndex,
                                                                            SecondarySystem,
                                                                            SecondaryIndex);
    Inherited::produceParticleCollision(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollisionParticleSystemAffector::CollisionParticleSystemAffector(void) :
    Inherited()
{
}

CollisionParticleSystemAffector::CollisionParticleSystemAffector(const CollisionParticleSystemAffector &source) :
    Inherited(source)
{
}

CollisionParticleSystemAffector::~CollisionParticleSystemAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollisionParticleSystemAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CollisionParticleSystemAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CollisionParticleSystemAffector NI" << std::endl;
}

OSG_END_NAMESPACE
