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

#include "OSGGeometryCollisionParticleSystemAffector.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGeometryCollisionParticleSystemAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGGeometryCollisionParticleSystemAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeometryCollisionParticleSystemAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GeometryCollisionParticleSystemAffector::produceParticleCollision(ParticleSystem* const System, Int32 ParticleIndex, IntersectAction* Action)
{
    ParticleGeometryCollisionEventDetailsUnrecPtr Details =
        ParticleGeometryCollisionEventDetails::create(this,
                                               getSystemTime(),Action->getHitT(),
                                               Action->getHitObject(),
                                               Action->getHitTriangle(),
                                               Action->getHitNormal(),
                                               Action->getHitPoint(),
                                               System,
                                               ParticleIndex );
       
    Inherited::produceParticleCollision(Details);
}

void GeometryCollisionParticleSystemAffector::affect(ParticleSystemRefPtr System, const Time& elps)
{
	UInt32 NumParticles(System->getNumParticles());
	
	Line ray;
    IntersectAction *iAct = IntersectAction::create();
	Pnt3f ParticlePos, ParticleSecPos;
    

	Real32 HitT(0.0f);
	for(UInt32 i(0) ; i<NumParticles ; ++i)
	{
		ParticlePos = System->getPosition(i);
		ParticleSecPos = System->getSecPosition(i);
		ray.setValue(ParticleSecPos, ParticlePos);
		iAct->setLine(ray);
		iAct->apply(getCollisionNode());
	    
		if (iAct->didHit())
		{
			HitT = iAct->getHitT();
			if(HitT > 0.0f && HitT*HitT<ParticlePos.dist2(ParticleSecPos))
			{
				produceParticleCollision(System, i, iAct);
                for(UInt32 j(0) ; j<getMFCollisionAffectors()->size(); ++j)
                {
                    getCollisionAffectors(i)->affect(System,i,elps);
                }
			}
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeometryCollisionParticleSystemAffector::GeometryCollisionParticleSystemAffector(void) :
    Inherited()
{
}

GeometryCollisionParticleSystemAffector::GeometryCollisionParticleSystemAffector(const GeometryCollisionParticleSystemAffector &source) :
    Inherited(source)
{
}

GeometryCollisionParticleSystemAffector::~GeometryCollisionParticleSystemAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeometryCollisionParticleSystemAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GeometryCollisionParticleSystemAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GeometryCollisionParticleSystemAffector NI" << std::endl;
}

OSG_END_NAMESPACE
