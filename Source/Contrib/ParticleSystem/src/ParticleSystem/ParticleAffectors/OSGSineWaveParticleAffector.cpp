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

#include "OSGSineWaveParticleAffector.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSineWaveParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGSineWaveParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SineWaveParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool SineWaveParticleAffector::affect(ParticleSystemRecPtr System, Int32 ParticleIndex, const Time& elps)
{
    // turn off secondary attribute updates.  This affector needs both position and secondary position in order
    // to properly function.  Only needs to be done
    if(ParticleIndex == 0) System->setUpdateSecAttribs(false);
    // calculate displacement from current position.
    Real32 displacement = getAmplitude() * osgSin(getFrequency() * System->getAge(ParticleIndex));
    // get the direction to displace the particle
    Vec3f displacementDir;
    switch(getUpDirSource())
    {
        case X_AXIS :
            displacementDir = Vec3f(1.0f,0.0f,0.0f);
            break;
        case Y_AXIS :
            displacementDir = Vec3f(0.0f,1.0f,0.0f);
            break;
        case Z_AXIS :
            displacementDir = Vec3f(0.0f,0.0f,1.0f);
            break;
        case NORMAL :
            displacementDir = System->getNormal(ParticleIndex);
        case CROSS_PRODUCT:
            displacementDir = System->getNormal(ParticleIndex).cross(System->getVelocity(ParticleIndex));
            displacementDir.normalize();
            if(displacementDir.length() == 0.0f)
            {	if(System->getVelocity(ParticleIndex) != Vec3f(1.0f,0.0f,0.0f))
                {
                    displacementDir = Vec3f(1.0f,0.0f,0.0f);
                }
                else
                {
                    displacementDir = Vec3f(0.0f,1.0f,0.0f);
                }
            }
            break;
        default: // default to y-axis displacement
            displacementDir = Vec3f(0.0f,1.0f,0.0f);
    }

    Pnt3f oldPos = System->getSecPosition(ParticleIndex);
    Pnt3f curPos = System->getPosition(ParticleIndex);
    // manually adjust sec pos
    System->setSecPosition(System->getSecPosition(ParticleIndex) + 
                           System->getVelocity(ParticleIndex)*elps + 
                           System->getAcceleration(ParticleIndex)*elps*elps, ParticleIndex);
    System->setPosition(oldPos + displacement*displacementDir,ParticleIndex);
    Vec3f newAcc = displacement*displacementDir;

    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SineWaveParticleAffector::SineWaveParticleAffector(void) :
    Inherited()
{
}

SineWaveParticleAffector::SineWaveParticleAffector(const SineWaveParticleAffector &source) :
    Inherited(source)
{
}

SineWaveParticleAffector::~SineWaveParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SineWaveParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SineWaveParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SineWaveParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
