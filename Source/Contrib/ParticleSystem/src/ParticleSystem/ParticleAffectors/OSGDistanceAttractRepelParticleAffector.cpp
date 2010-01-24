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

#include "OSGDistanceAttractRepelParticleAffector.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDistanceAttractRepelParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGDistanceAttractRepelParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceAttractRepelParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DistanceAttractRepelParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement)
{
	Real32 age     = System->getAge(ParticleIndex);
	Real32 d       = Displacement.length();
	Vec3f  dnormal = Displacement*(1.0/d);
	if( d > getMinDistance()  && d < getMaxDistance())
	{
		Real32 t((getQuadratic() * (1.0/(d*d)) + getLinear() * (1.0/d) + getConstant())*elps);
		if(t > d)
		{
			t=d;
		}

		Pnt3f pos = System->getPosition(ParticleIndex) + (dnormal * t);
		System->setPosition(pos,ParticleIndex) ;
	}
	return false;
	
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceAttractRepelParticleAffector::DistanceAttractRepelParticleAffector(void) :
    Inherited()
{
}

DistanceAttractRepelParticleAffector::DistanceAttractRepelParticleAffector(const DistanceAttractRepelParticleAffector &source) :
    Inherited(source)
{
}

DistanceAttractRepelParticleAffector::~DistanceAttractRepelParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceAttractRepelParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DistanceAttractRepelParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DistanceAttractRepelParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
