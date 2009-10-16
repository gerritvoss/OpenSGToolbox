/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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
#include <boost/bind.hpp>

#include "OSGCollisionParticleSystemAffector.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CollisionParticleSystemAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionParticleSystemAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CollisionParticleSystemAffector::affect(ParticleSystemPtr System, const Time& elps)
{
    UInt32 PrimaryNumParticles(System->getNumParticles());
    Real32 MinDistSqr(getCollisionDistance() * getCollisionDistance());
    for(UInt32 i(0) ; i<getSecondaryCollisionSystems().size() ; ++i)
    {
        //Check their volumes for intersection
        if(System->getVolume().intersect(getSecondaryCollisionSystems(i)->getVolume()))
        {
            UInt32 SecondaryNumParticles(getSecondaryCollisionSystems(i)->getNumParticles());
            //If the Volumes intersect then check for collisions
            for(UInt32 PrimaryIndex(0) ; PrimaryIndex<PrimaryNumParticles ; ++PrimaryIndex)
            {
                for(UInt32 SecondaryIndex(0) ; SecondaryIndex<SecondaryNumParticles ; ++SecondaryIndex)
                {
                    if(MinDistSqr >= System->getPosition(PrimaryIndex).dist2(getSecondaryCollisionSystems(i)->getPosition(SecondaryIndex)))
                    {
                        produceCollision(ParticleCollisionEvent::create(CollisionParticleSystemAffectorPtr(this),
                                    getTimeStamp(),
                                    System,
                                    PrimaryIndex,
                                    getSecondaryCollisionSystems(i),
                                    SecondaryIndex));
                    }
                }
            }
        }
    }
}

EventConnection CollisionParticleSystemAffector::addParticleCollisionListener(ParticleCollisionListenerPtr Listener)
{
   _ParticleCollisionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&CollisionParticleSystemAffector::isParticleCollisionListenerAttached, this, Listener),
       boost::bind(&CollisionParticleSystemAffector::removeParticleCollisionListener, this, Listener));
}
    
bool CollisionParticleSystemAffector::isParticleCollisionListenerAttached(ParticleCollisionListenerPtr Listener) const
{
    return _ParticleCollisionListeners.find(Listener) != _ParticleCollisionListeners.end();
}

void CollisionParticleSystemAffector::removeParticleCollisionListener(ParticleCollisionListenerPtr Listener)
{
   ParticleCollisionListenerSetItor EraseIter(_ParticleCollisionListeners.find(Listener));
   if(EraseIter != _ParticleCollisionListeners.end())
   {
      _ParticleCollisionListeners.erase(EraseIter);
   }
}

void CollisionParticleSystemAffector::produceCollision(const ParticleCollisionEventPtr Event)
{
    for(ParticleCollisionListenerSetItor SetItor(_ParticleCollisionListeners.begin()) ; SetItor != _ParticleCollisionListeners.end() ; ++SetItor)
    {
        (*SetItor)->particleCollision(Event);
    }
    _Producer.produceEvent(ParticleCollisionMethodId,Event);
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

void CollisionParticleSystemAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CollisionParticleSystemAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CollisionParticleSystemAffector NI" << std::endl;
}


OSG_END_NAMESPACE

