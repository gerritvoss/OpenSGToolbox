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

#include "OSGDragParticleAffector.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"

#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDragParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGDragParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DragParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DragParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
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
            if(getUseDirection()) // field 'direction' affects the amount of drag exerted on particle
            {
                Vec3f particleVelocity = System->getVelocity(ParticleIndex);
                Vec3f projection(particleVelocity);
                projection.projectTo(getDirection());
                if(particleVelocity.length() < getSpeedAttenuation() && getSpeedAttenuation() > 0.0f)
                {
                    double scaleDragEffect = (elps * getMagnitude() * std::pow(particleVelocity.length()/getSpeedAttenuation(), 2))
                        /osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());

                    for(int i(0); i < 3; i++)
                    {
                        particleVelocity[i] -= getDirection()[i] * scaleDragEffect * particleVelocity[i];
                    }

                }
                else
                {
                    double scaleDragEffect = (elps * getMagnitude())
                        /osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax());

                    for(int i(0); i < 3; i++)
                    {
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
                                                            /osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));
                }
                else
                {
                    particleVelocity -= particleVelocity * (elps * getMagnitude()
                                                            /osgClamp<Real32>(1.0f,std::pow(distanceFromAffector,getAttenuation()),TypeTraits<Real32>::getMax()));
                }
                System->setVelocity(particleVelocity,ParticleIndex);
            } // use direction cond.
        }	// particle within maxDistance cond.
    }// Null Beacon cond.

    return false;
} // end affect()

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

void DragParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DragParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DragParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
