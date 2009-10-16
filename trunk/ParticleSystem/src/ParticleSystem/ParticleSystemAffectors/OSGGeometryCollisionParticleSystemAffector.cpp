/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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

#include "OSGGeometryCollisionParticleSystemAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"
#include "ParticleSystem/ParticleAffectors/OSGParticleAffector.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeometryCollisionParticleSystemAffector
s 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeometryCollisionParticleSystemAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/



void GeometryCollisionParticleSystemAffector::removeParticleGeometryCollisionListener(ParticleGeometryCollisionListenerPtr Listener)
{
   ParticleGeometryCollisionListenerSetItor EraseIter(_ParticleGeometryCollisionListeners.find(Listener));
   if(EraseIter != _ParticleGeometryCollisionListeners.end())
   {
      _ParticleGeometryCollisionListeners.erase(EraseIter);
   }
}

void GeometryCollisionParticleSystemAffector::produceCollision(ParticleSystemPtr System, Int32 ParticleIndex, IntersectAction* Action)
{
   const ParticleGeometryCollisionEventPtr TheCollisionEvent = ParticleGeometryCollisionEvent::create( GeometryCollisionParticleSystemAffectorPtr(this),
           getSystemTime(),Action->getHitT(),
           Action->getHitObject(),
           Action->getHitTriangle(),
           Action->getHitNormal(),
           Action->getHitPoint(),
           System,
           ParticleIndex );
   ParticleGeometryCollisionListenerSetItor NextItor;
   for(ParticleGeometryCollisionListenerSetItor SetItor(_ParticleGeometryCollisionListeners.begin()) ; SetItor != _ParticleGeometryCollisionListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleCollision(TheCollisionEvent);
      SetItor = NextItor;
   }
   _Producer.produceEvent(ParticleCollisionMethodId,TheCollisionEvent);
}

void GeometryCollisionParticleSystemAffector::affect(ParticleSystemPtr System, const Time& elps)
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
				produceCollision(System, i, iAct);
                for(UInt32 j(0) ; j<getCollisionAffectors().size(); ++j)
                {
                    getCollisionAffectors()[i]->affect(System,i,elps);
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

void GeometryCollisionParticleSystemAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeometryCollisionParticleSystemAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeometryCollisionParticleSystemAffector NI" << std::endl;
}

OSG_END_NAMESPACE

