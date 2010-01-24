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

#include "OSGAttributeAttractRepelParticleAffector.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAttributeAttractRepelParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGAttributeAttractRepelParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AttributeAttractRepelParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AttributeAttractRepelParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
    if(System != NULL)
    {
        Vec3f Displacement(System->getSecPosition(ParticleIndex) - System->getPosition(ParticleIndex) );

        Real32 Distance(Displacement.squareLength());

        if((Distance > getMinDistance()*getMinDistance()) &&
           (Distance < getMaxDistance()*getMaxDistance()))
        {
            Distance = osgSqrt(Distance);
            Displacement.normalize();

            Real32 t((getQuadratic() * (Distance*Distance) + getLinear() * Distance + getConstant())*elps);
            if(t > Distance)
            {
                t=Distance;
            }

            System->setPosition(System->getPosition(ParticleIndex) + (Displacement * t),ParticleIndex) ;
        }
    }
    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AttributeAttractRepelParticleAffector::AttributeAttractRepelParticleAffector(void) :
    Inherited()
{
}

AttributeAttractRepelParticleAffector::AttributeAttractRepelParticleAffector(const AttributeAttractRepelParticleAffector &source) :
    Inherited(source)
{
}

AttributeAttractRepelParticleAffector::~AttributeAttractRepelParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AttributeAttractRepelParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AttributeAttractRepelParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AttributeAttractRepelParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
