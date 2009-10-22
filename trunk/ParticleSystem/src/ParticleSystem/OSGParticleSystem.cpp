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

#include "OSGParticleSystem.h"
#include "ParticleSystem/Events/OSGParticleEvent.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "ParticleSystem/ParticleAffectors/OSGParticleAffector.h"
#include "ParticleSystem/ParticleSystemAffectors/OSGParticleSystemAffector.h"
#include "ParticleSystem/ParticleGenerators/OSGParticleGenerator.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystem

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  ParticleSystem::InternalParticlesFieldMask = 
    (TypeTraits<BitVector>::One << ParticleSystem::InternalPositionsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSecPositionsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalNormalsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalColorsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSizesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalLifespansFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAgesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalVelocitiesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSecVelocitiesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAccelerationsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAttributesFieldId);

StatElemDesc<StatIntElem> ParticleSystem::statNParticles("NParticles", 
                                                      "number of particles");
StatElemDesc<StatTimeElem> ParticleSystem::statParticleSystemUpdate("ParticleUpdateTime", 
                                                      "time for particle system updates");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


EventConnection ParticleSystem::addParticleSystemListener(ParticleSystemListenerPtr Listener)
{
   _ParticleSystemListeners.insert(Listener);
   return EventConnection(
       boost::bind(&ParticleSystem::isParticleSystemListenerAttached, this, Listener),
       boost::bind(&ParticleSystem::removeParticleSystemListener, this, Listener));
}
    
bool ParticleSystem::isParticleSystemListenerAttached(ParticleSystemListenerPtr Listener) const
{
    return _ParticleSystemListeners.find(Listener) != _ParticleSystemListeners.end();
}

void ParticleSystem::removeParticleSystemListener(ParticleSystemListenerPtr Listener)
{
   ParticleSystemListenerSetItor EraseIter(_ParticleSystemListeners.find(Listener));
   if(EraseIter != _ParticleSystemListeners.end())
   {
      _ParticleSystemListeners.erase(EraseIter);
   }
}

std::vector<UInt32> ParticleSystem::intersect(const Line& Ray, Real32 IntersectionDistance, NodePtr Beacon) const
{
    std::vector<UInt32> Result;

    DynamicVolume BeaconWorldVol;
    Matrix BeaconToWorld;

    
    //If the Beacon node given to this function is Null
    if(Beacon == NullFC)
    {
        //If the Beacon node attached to this particle system is Null
        if(getBeacon() == NullFC)
        {
            BeaconToWorld.setIdentity();
            BeaconWorldVol.setInfinite(true);
        }
        else
        {
            BeaconToWorld = getBeacon()->getToWorld();
            getBeacon()->getWorldVolume(BeaconWorldVol);
        }
    }
    else
    {
        BeaconToWorld = Beacon->getToWorld();
        Beacon->getWorldVolume(BeaconWorldVol);
    }

    Pnt3f ClosestPoint;
    Pnt3f ParticleWorldPosition;
    Real32 MinDist2(IntersectionDistance * IntersectionDistance);

    Real32 EnterVol,ExitVol;
    //Check if this ray intersects with the Beacons volume

    //The volume needs to be extended so that there is an intersection
    //When the bound volume is not intersecting with the line but is intersecting
    //with the IntersectionDistance from the line
    BeaconWorldVol.extendBy(BeaconWorldVol.getMin() - Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    BeaconWorldVol.extendBy(BeaconWorldVol.getMax() + Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    if(
        (BeaconWorldVol.getType() == DynamicVolume::BOX_VOLUME && Ray.intersect(static_cast<const BoxVolume&>(BeaconWorldVol.getInstance()),EnterVol,ExitVol)) ||
        (BeaconWorldVol.getType() == DynamicVolume::SPHERE_VOLUME && Ray.intersect(static_cast<const SphereVolume&>(BeaconWorldVol.getInstance()),EnterVol,ExitVol))
        )
    {
        //For each particle
        for(UInt32 i(0) ; i< getNumParticles(); ++i)
        {
            ParticleWorldPosition = BeaconToWorld*getPosition(i);
            ClosestPoint = Ray.getClosestPoint(ParticleWorldPosition);
            if(ClosestPoint.dist2(ParticleWorldPosition) < MinDist2)
            {
                Result.push_back(i);
            }
        }
    }

    return Result;
}

void ParticleSystem::addAndExpandSecPositions(const Pnt3f& SecPosition)
{
	if(getInternalSecPositions().size() == 0)
	{
		getInternalSecPositions().push_back(SecPosition);
	}
	else if(getInternalSecPositions().size() == 1)
	{
		if(getInternalSecPositions()[0] != SecPosition)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalSecPositions().push_back(getInternalSecPositions()[0]);
			}

			getInternalSecPositions().push_back(SecPosition);
		}
	}
	else
	{
		getInternalSecPositions().push_back(SecPosition);
	}
}

void ParticleSystem::addAndExpandNormals(const Vec3f& Normal)
{
	if(getInternalNormals().size() == 0)
	{
		getInternalNormals().push_back(Normal);
	}
	else if(getInternalNormals().size() == 1)
	{
		if(getInternalNormals()[0] != Normal)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalNormals().push_back(getInternalNormals()[0]);
			}

			getInternalNormals().push_back(Normal);
		}
	}
	else
	{
		getInternalNormals().push_back(Normal);
	}
}

void ParticleSystem::addAndExpandColors(const Color4f& Color)
{
	if(getInternalColors().size() == 0)
	{
		getInternalColors().push_back(Color);
	}
	else if(getInternalColors().size() == 1)
	{
		if(getInternalColors()[0] != Color)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalColors().push_back(getInternalColors()[0]);
			}

			getInternalColors().push_back(Color);
		}
	}
	else
	{
		getInternalColors().push_back(Color);
	}
}

void ParticleSystem::addAndExpandSizes(const Vec3f& Size)
{
	if(getInternalSizes().size() == 0)
	{
		getInternalSizes().push_back(Size);
	}
	else if(getInternalSizes().size() == 1)
	{
		if(getInternalSizes()[0] != Size)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalSizes().push_back(getInternalSizes()[0]);
			}

			getInternalSizes().push_back(Size);
		}
	}
	else
	{
		getInternalSizes().push_back(Size);
	}
}

void ParticleSystem::addAndExpandLifespans(Real32 Lifespan)
{
	if(getInternalLifespans().size() == 0)
	{
		getInternalLifespans().push_back(Lifespan);
	}
	else if(getInternalLifespans().size() == 1)
	{
		if(getInternalLifespans()[0] != Lifespan)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalLifespans().push_back(getInternalLifespans()[0]);
			}

			getInternalLifespans().push_back(Lifespan);
		}
	}
	else
	{
		getInternalLifespans().push_back(Lifespan);
	}
}

void ParticleSystem::addAndExpandAges(Real32 Age)
{
	if(getInternalAges().size() == 0)
	{
		getInternalAges().push_back(Age);
	}
	else if(getInternalAges().size() == 1)
	{
		if(getInternalAges()[0] != Age)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalAges().push_back(getInternalAges()[0]);
			}

			getInternalAges().push_back(Age);
		}
	}
	else
	{
		getInternalAges().push_back(Age);
	}
}

void ParticleSystem::addAndExpandVelocities(const Vec3f& Velocity)
{
	if(getInternalVelocities().size() == 0)
	{
		getInternalVelocities().push_back(Velocity);
	}
	else if(getInternalVelocities().size() == 1)
	{
		if(getInternalVelocities()[0] != Velocity)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalVelocities().push_back(getInternalVelocities()[0]);
			}

			getInternalVelocities().push_back(Velocity);
		}
	}
	else
	{
		getInternalVelocities().push_back(Velocity);
	}
}

void ParticleSystem::addAndExpandSecVelocities(const Vec3f& SecVelocity)
{
	if(getInternalSecVelocities().size() == 0)
	{
		getInternalSecVelocities().push_back(SecVelocity);
	}
	else if(getInternalSecVelocities().size() == 1)
	{
		if(getInternalSecVelocities()[0] != SecVelocity)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalSecVelocities().push_back(getInternalSecVelocities()[0]);
			}

			getInternalSecVelocities().push_back(SecVelocity);
		}
	}
	else
	{
		getInternalSecVelocities().push_back(SecVelocity);
	}
}

void ParticleSystem::addAndExpandAccelerations(const Vec3f& Acceleration)
{
	if(getInternalAccelerations().size() == 0)
	{
		getInternalAccelerations().push_back(Acceleration);
	}
	else if(getInternalAccelerations().size() == 1)
	{
		if(getInternalAccelerations()[0] != Acceleration)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalAccelerations().push_back(getInternalAccelerations()[0]);
			}

			getInternalAccelerations().push_back(Acceleration);
		}
	}
	else
	{
		getInternalAccelerations().push_back(Acceleration);
	}
}

void ParticleSystem::addAndExpandAttributes(const StringToUInt32Map& AttributeMap)
{
	if(getInternalAttributes().size() == 0)
	{
		getInternalAttributes().push_back(AttributeMap);
	}
	else if(getInternalAttributes().size() == 1)
	{
		if(getInternalAttributes()[0] != AttributeMap)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalAttributes().push_back(getInternalAttributes()[0]);
			}

			getInternalAttributes().push_back(AttributeMap);
		}
	}
	else
	{
		getInternalAttributes().push_back(AttributeMap);
	}
}

bool ParticleSystem::internalKillParticle(UInt32 Index)
{
    if(Index >= getNumParticles())
    {
        return false;
    }

	Pnt3f Position(getPosition(Index));
	Pnt3f SecPosition(getSecPosition(Index));
	Vec3f Normal(getNormal(Index));
	Color4f Color(getColor(Index));
	Vec3f Size(getSize(Index));
	Real32 Lifespan(getLifespan(Index));
	Real32 Age(getAge(Index));
	Vec3f Velocity(getVelocity(Index));
	Vec3f SecVelocity(getSecVelocity(Index));
	Vec3f Acceleration(getAcceleration(Index));
	StringToUInt32Map Attributes;
	// only attempting to retrieve attributes if there are any present
	if(getNumAttributes() > 0) Attributes = getAttributes(Index);
	
    removePosition(Index);
    removeSecPosition(Index);
    removeNormal(Index);
    removeColor(Index);
    removeSize(Index);
    removeLifespan(Index);
    removeAge(Index);
    removeVelocity(Index);
    removeSecVelocity(Index);
    removeAcceleration(Index);
    removeAttributes(Index);

    produceParticleKilled(Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes);

    return true;
}

bool ParticleSystem::killParticle(UInt32 Index)
{
	if(_isUpdating)
	{
		_ParticlesToKill.insert(Index);
		return false;
	}
	else
	{
		return internalKillParticle(Index);
	}
}

void ParticleSystem::removePosition(UInt32 Index)
{
    getInternalPositions()[Index] = getInternalPositions().back();
    getInternalPositions().erase(--getInternalPositions().end());
}

void ParticleSystem::removeSecPosition(UInt32 Index)
{
    if(getNumSecPositions() > 1)
    {
        getInternalSecPositions()[Index] = getInternalSecPositions().back();
        getInternalSecPositions().erase(--getInternalSecPositions().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalSecPositions().clear();
    }
}

void ParticleSystem::removeNormal(UInt32 Index)
{
    if(getNumNormals() > 1)
    {
        getInternalNormals()[Index] = getInternalNormals().back();
        getInternalNormals().erase(--getInternalNormals().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalNormals().clear();
    }
}

void ParticleSystem::removeColor(UInt32 Index)
{
    if(getNumColors() > 1)
    {
        getInternalColors()[Index] = getInternalColors().back();
        getInternalColors().erase(--getInternalColors().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalColors().clear();
    }
}

void ParticleSystem::removeSize(UInt32 Index)
{
    if(getNumSizes() > 1)
    {
        getInternalSizes()[Index] = getInternalSizes().back();
        getInternalSizes().erase(--getInternalSizes().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalSizes().clear();
    }
}

void ParticleSystem::removeLifespan(UInt32 Index)
{
    if(getNumLifespans() > 1)
    {
        getInternalLifespans()[Index] = getInternalLifespans().back();
        getInternalLifespans().erase(--getInternalLifespans().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalLifespans().clear();
    }
}

void ParticleSystem::removeAge(UInt32 Index)
{
    if(getNumAges() > 1)
    {
        getInternalAges()[Index] = getInternalAges().back();
        getInternalAges().erase(--getInternalAges().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalAges().clear();
    }
}

void ParticleSystem::removeVelocity(UInt32 Index)
{
    if(getNumVelocities() > 1)
    {
        getInternalVelocities()[Index] = getInternalVelocities().back();
        getInternalVelocities().erase(--getInternalVelocities().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalVelocities().clear();
    }
}

void ParticleSystem::removeSecVelocity(UInt32 Index)
{
    if(getNumSecVelocities() > 1)
    {
        getInternalSecVelocities()[Index] = getInternalSecVelocities().back();
        getInternalSecVelocities().erase(--getInternalSecVelocities().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalSecVelocities().clear();
    }
}

void ParticleSystem::removeAcceleration(UInt32 Index)
{
    if(getNumAccelerations() > 1)
    {
        getInternalAccelerations()[Index] = getInternalAccelerations().back();
        getInternalAccelerations().erase(--getInternalAccelerations().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalAccelerations().clear();
    }
}

void ParticleSystem::removeAttributes(UInt32 Index)
{
    if(getNumAttributes() > 1)
    {
        getInternalAttributes()[Index] = getInternalAttributes().back();
        getInternalAttributes().erase(--getInternalAttributes().end());
    }
    else if(getNumParticles() == 0)
    {
        getInternalAttributes().clear();
    }
}


bool ParticleSystem::addParticle(const Pnt3f& Position,
		             const Pnt3f& SecPosition,
					 const Vec3f& Normal,
					 const Color4f& Color,
					 const Vec3f& Size,
					 Real32 Lifespan,
					 Real32 Age,
					 const Vec3f& Velocity,
					 const Vec3f& SecVelocity,
					 const Vec3f& Acceleration,
                     const StringToUInt32Map& Attributes)
{
	if(getNumParticles() >= getMaxParticles())
	{
		return false;
	}

	beginEditCP(ParticleSystemPtr(this), ParticleSystem::InternalParticlesFieldMask);

		addAndExpandSecPositions(SecPosition);
		addAndExpandNormals(Normal);
		addAndExpandColors(Color);
		addAndExpandSizes(Size);
		addAndExpandLifespans(Lifespan);
		addAndExpandAges(Age);
        //Apply the accumulated acceleration onto the velocity
		addAndExpandVelocities(Velocity + Acceleration*Age);
		addAndExpandSecVelocities(SecVelocity + Acceleration*Age);
		addAndExpandAccelerations(Acceleration);
		addAndExpandAttributes(Attributes);

        //Apply the accumulated velocity and acceleration onto the position
		getInternalPositions().push_back(Position + Velocity*Age + Acceleration*Age*Age);
	endEditCP(ParticleSystemPtr(this), ParticleSystem::InternalParticlesFieldMask);

    //Affect Particles with Affectors
    for(UInt32 j(0) ; j<getAffectors().size(); ++j)
    {
        getAffectors(j)->affect(ParticleSystemPtr(this), getInternalPositions().size()-1, Age);
        
    }

    produceParticleGenerated(getInternalPositions().size()-1);

	return true;
}

bool ParticleSystem::addParticle(const Pnt3f& Position,
					 const Vec3f& Normal,
					 const Color4f& Color,
					 const Vec3f& Size,
					 Real32 Lifespan,
					 const Vec3f& Velocity,
					 const Vec3f& Acceleration)
{
    StringToUInt32Map EmptyAttributes;

	return addParticle(Position,
	             Position,
				 Normal,
				 Color,
				 Size,
				 Lifespan,
				 0.0f,
				 Velocity,
				 Velocity,
				 Acceleration,
				 EmptyAttributes);
}

bool ParticleSystem::addWorldSpaceParticle(const Pnt3f& Position,
					 const Vec3f& Normal,
					 const Color4f& Color,
					 const Vec3f& Size,
					 Real32 Lifespan,
					 const Vec3f& Velocity,
					 const Vec3f& Acceleration)
{
	StringToUInt32Map EmptyAttributes;

	return addWorldSpaceParticle(Position,
						 Position,
						 Normal,
						 Color,
						 Size,
						 Lifespan,
						 0.0f,
						 Velocity,
						 Velocity,
						 Acceleration,
						 EmptyAttributes);
}


bool ParticleSystem::addWorldSpaceParticle(const Pnt3f& Position,
		             const Pnt3f& SecPosition,
					 const Vec3f& Normal,
					 const Color4f& Color,
					 const Vec3f& Size,
					 Real32 Lifespan,
					 Real32 Age,
					 const Vec3f& Velocity,
					 const Vec3f& SecVelocity,
					 const Vec3f& Acceleration,
                     const StringToUInt32Map& Attributes)
{
	// behavior for this method is undefined if the beacon is not present
	if(getBeacon() == NullFC)
	{	// no beacon, so we can't do anything to convert the particle
		// to local particle system space
		return false;
	}

	Matrix PSBeaconMatrix(getBeacon()->getToWorld());
	
	if(PSBeaconMatrix.invert())
	{
		Pnt3f NewPosition(PSBeaconMatrix * Position);
		Pnt3f NewSecPosition(PSBeaconMatrix * SecPosition);
		Vec3f NewNormal(PSBeaconMatrix * Normal);
		Vec3f NewVelocity(PSBeaconMatrix * Velocity);
		Vec3f NewSecVelocity(PSBeaconMatrix * SecVelocity);
		Vec3f NewAcceleration(PSBeaconMatrix * Acceleration);
		
		// tranformation to local particle system space complete
		// so add it to the particle system
		return addParticle(NewPosition,
             NewSecPosition,
			 NewNormal,
			 Color,
			 Size,
			 Lifespan,
			 Age,
			 NewVelocity,
			 NewSecVelocity,
			 NewAcceleration,
			 Attributes);
	}


	// if this is reached, the inversion of the matrix was unsucessful
	return false;
}


const Vec3f ParticleSystem::getPositionChange(const UInt32& Index) const
{
	return getPosition(Index) - getSecPosition(Index);
}

const Vec3f ParticleSystem::getVelocityChange(const UInt32& Index) const
{
	return getVelocity(Index) - getSecVelocity(Index);
}

const Pnt3f& ParticleSystem::getSecPosition(const UInt32& Index) const
{
	if(Index < getInternalSecPositions().getSize())
	{
		return getInternalSecPositions()[Index];
	}
	else
	{
		return getInternalSecPositions()[0];
	}
}

const Vec3f& ParticleSystem::getNormal(const UInt32& Index) const
{
	if(Index < getInternalNormals().getSize())
	{
		return getInternalNormals()[Index];
	}
	else
	{
		return getInternalNormals()[0];
	}
}

const Color4f& ParticleSystem::getColor(const UInt32& Index) const
{
	if(Index < getInternalColors().getSize())
	{
		return getInternalColors()[Index];
	}
	else
	{
		return getInternalColors()[0];
	}
}

const Vec3f& ParticleSystem::getSize(const UInt32& Index) const
{
	if(Index < getInternalSizes().getSize())
	{
		return getInternalSizes()[Index];
	}
	else
	{
		return getInternalSizes()[0];
	}
}

Real32 ParticleSystem::getLifespan(const UInt32& Index) const
{
	if(Index < getInternalLifespans().getSize())
	{
		return getInternalLifespans()[Index];
	}
	else
	{
		return getInternalLifespans()[0];
	}
}

Real32 ParticleSystem::getAge(const UInt32& Index) const
{
	if(Index < getInternalAges().getSize())
	{
		return getInternalAges()[Index];
	}
	else
	{
		return getInternalAges()[0];
	}
}

const Vec3f& ParticleSystem::getVelocity(const UInt32& Index) const
{
	if(Index < getInternalVelocities().getSize())
	{
		return getInternalVelocities()[Index];
	}
	else
	{
		return getInternalVelocities()[0];
	}
}

const Vec3f& ParticleSystem::getSecVelocity(const UInt32& Index) const
{
	if(Index < getInternalSecVelocities().getSize())
	{
		return getInternalSecVelocities()[Index];
	}
	else
	{
		return getInternalSecVelocities()[0];
	}
}

const Vec3f& ParticleSystem::getAcceleration(const UInt32& Index) const
{
	if(Index < getInternalAccelerations().getSize())
	{
		return getInternalAccelerations()[Index];
	}
	else
	{
		return getInternalAccelerations()[0];
	}
}

const StringToUInt32Map& ParticleSystem::getAttributes(const UInt32& Index) const
{
	if(Index < getInternalAttributes().getSize())
	{
		return getInternalAttributes()[Index];
	}
	else 
	{
		return getInternalAttributes()[0];
	}
}

UInt32 ParticleSystem::getAttribute(const UInt32& Index, const std::string& AttributeKey) const
{
	if(Index < getInternalAttributes().getSize())
	{
		return getInternalAttributes()[Index].find(AttributeKey)->second;
	}
	else
	{
		return getInternalAttributes()[0].find(AttributeKey)->second;
	}
}

void ParticleSystem::setSecPosition(const Pnt3f& SecPosition, const UInt32& Index)
{
	if(getNumSecPositions() > 1)
	{
		getInternalSecPositions()[Index] = SecPosition;
	}
	else if(getNumSecPositions() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalSecPositions()[0] != SecPosition)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalSecPositions().push_back(getInternalSecPositions()[0]);
				}
				getInternalSecPositions()[Index] = SecPosition;
			}
		}
		else
		{
			getInternalSecPositions()[Index] = SecPosition;
		}
	}
}

void ParticleSystem::setNormal(const Vec3f& Normal, const UInt32& Index)
{
	if(getNumNormals() > 1)
	{
		getInternalNormals()[Index] = Normal;
	}
	else if(getNumNormals() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalNormals()[0] != Normal)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalNormals().push_back(getInternalNormals()[0]);
				}
				getInternalNormals()[Index] = Normal;
			}
		}
		else
		{
			getInternalNormals()[Index] = Normal;
		}
	}
}
void ParticleSystem::setColor(const Color4f& Color, const UInt32& Index)
{
	if(getNumColors() > 1)
	{
		getInternalColors()[Index] = Color;
	}
	else if(getNumColors() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalColors()[0] != Color)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalColors().push_back(getInternalColors()[0]);
				}
				getInternalColors()[Index] = Color;
			}
		}
		else
		{
			getInternalColors()[Index] = Color;
		}
	}
}


void ParticleSystem::setSize(const Vec3f& Size, const UInt32& Index)
{
	if(getNumSizes() > 1)
	{
		getInternalSizes()[Index] = Size;
	}
	else if(getNumSizes() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalSizes()[0] != Size)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalSizes().push_back(getInternalSizes()[0]);
				}
				getInternalSizes()[Index] = Size;
			}
		}
		else
		{
			getInternalSizes()[Index] = Size;
		}
	}
}
void ParticleSystem::setLifespan(const Time& Lifespan, const UInt32& Index)
{
	if(getNumLifespans() > 1)
	{
		getInternalLifespans()[Index] = Lifespan;
	}
	else if(getNumLifespans() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalLifespans()[0] != Lifespan)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalLifespans().push_back(getInternalLifespans()[0]);
				}
				getInternalLifespans()[Index] = Lifespan;
			}
		}
		else
		{
			getInternalLifespans()[Index] = Lifespan;
		}
	}
}

void ParticleSystem::setAge(const Time& Age, const UInt32& Index)
{
	if(getNumAges() > 1)
	{
		getInternalAges()[Index] = Age;
	}
	else if(getNumAges() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalAges()[0] != Age)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalAges().push_back(getInternalAges()[0]);
				}
				getInternalAges()[Index] = Age;
			}
		}
		else
		{
			getInternalAges()[Index] = Age;
		}
	}
}

void ParticleSystem::setVelocity(const Vec3f& Velocity, const UInt32& Index)
{
	if(getNumVelocities() > 1)
	{
		getInternalVelocities()[Index] = Velocity;
	}
	else if(getNumVelocities() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalVelocities()[0] != Velocity)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalVelocities().push_back(getInternalVelocities()[0]);
				}
				getInternalVelocities()[Index] = Velocity;
			}
		}
		else
		{
			getInternalVelocities()[Index] = Velocity;
		}
	}
}

void ParticleSystem::setSecVelocity(const Vec3f& SecVelocity, const UInt32& Index)
{
	if(getNumSecVelocities() > 1)
	{
		getInternalSecVelocities()[Index] = SecVelocity;
	}
	else if(getNumSecVelocities() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalSecVelocities()[0] != SecVelocity)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalSecVelocities().push_back(getInternalSecVelocities()[0]);
				}
				getInternalSecVelocities()[Index] = SecVelocity;
			}
		}
		else
		{
			getInternalSecVelocities()[Index] = SecVelocity;
		}
	}
}

void ParticleSystem::setAcceleration(const Vec3f& Acceleration, const UInt32& Index)
{
	if(getNumAccelerations() > 1)
	{
		getInternalAccelerations()[Index] = Acceleration;
	}
	else if(getNumAccelerations() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalAccelerations()[0] != Acceleration)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalAccelerations().push_back(getInternalAccelerations()[0]);
				}
				getInternalAccelerations()[Index] = Acceleration;
			}
		}
		else
		{
			getInternalAccelerations()[Index] = Acceleration;
		}
	}
}

void ParticleSystem::setAttributes(const StringToUInt32Map& Attributes, const UInt32& Index)
{
	if(getNumAttributes() > 1)
	{
		getInternalAttributes()[Index] = Attributes;
	}
	else if(getNumAttributes() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalAttributes()[0] != Attributes)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalAttributes().push_back(getInternalAttributes()[0]);
				}
				getInternalAttributes()[Index] = Attributes;
			}
		}
		else
		{
			getInternalAttributes()[Index] = Attributes;
		}
	}
}

void ParticleSystem::setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index)
{
	if(getNumAttributes() > 1)
	{
		getInternalAttributes()[Index][AttributeKey] = AttributeValue;
	}
	else if(getNumAttributes() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalAttributes()[0][AttributeKey] != AttributeValue)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalAttributes().push_back(getInternalAttributes()[0]);
				}
				getInternalAttributes()[Index][AttributeKey] = AttributeValue;
			}
		}
		else
		{
			getInternalAttributes()[Index][AttributeKey] = AttributeValue;
		}
	}
}

void ParticleSystem::internalKillParticles()
{
	if(!_isUpdating)
	{
		//Kill Particles
		for(std::set<UInt32, GreaterThanUInt32>::iterator Itor(_ParticlesToKill.begin()) ; Itor != _ParticlesToKill.end() ; ++Itor)
		{
			killParticle(*Itor);
		}
		_ParticlesToKill.clear();
	}
}

void ParticleSystem::update(const Time& elps)
{

    //Loop through all of the particles
    DynamicVolume PrevVolume(getVolume());

	_isUpdating = true;

	//Generate Particles with Generators
	UInt32 NumGenerators(getGenerators().size());
	for(UInt32 j(0) ; j<NumGenerators; )
	{
		if(getGenerators()[j]->generate(ParticleSystemPtr(this), elps))
		{
			beginEditCP(ParticleSystemPtr(this), GeneratorsFieldMask);
				getGenerators().erase(std::find(getGenerators().begin(), getGenerators().end(), getGenerators()[j])); 
			endEditCP(ParticleSystemPtr(this), GeneratorsFieldMask);
			--NumGenerators;
		}
		else
		{
			++j;
		}
	}

    UInt32 NumParticles(getNumParticles());
    if(NumParticles > 0)
    {
        beginEditCP(ParticleSystemPtr(this), VolumeFieldMask | MaxParticleSizeFieldMask);
            setVolume(DynamicVolume());
            setMaxParticleSize(Vec3f(0.0f,0.0f,0.0f));
    }

	bool AdvanceIterator(true);
    for(UInt32 i(0) ; i<NumParticles; ++i)
    {
		//Kill Particles that have ages > lifespans
		setAge(getAge(i) + elps,i);
		if(getLifespan(i) > 0.0f && getAge(i)>getLifespan(i))
		{
			killParticle(i);
			continue;
		}


		if(getUpdateSecAttribs())
		{
			//Remember the Old Postions and velocities
			setSecPosition(getPosition(i),i);
			setSecVelocity(getVelocity(i),i);
		}


		//Apply Acceleration and Velocity
        setPosition(getPosition(i) + getVelocity(i)*elps + getAcceleration(i)*elps*elps, i);

		setVelocity(getVelocity(i) + getAcceleration(i)*elps,i);

		//Affect Particles with Affectors
		for(UInt32 j(0) ; j<getAffectors().size(); ++j)
		{
			if(getAffectors(j)->affect(ParticleSystemPtr(this), i, elps))
			{
				killParticle(i);
				continue;
			}
			
		}

        editVolume().extendBy(getPosition(i));
        editMaxParticleSize().setValues(osgMax(getMaxParticleSize().x(),getSize(i).x()),
                                        osgMax(getMaxParticleSize().y(),getSize(i).y()),
                                        osgMax(getMaxParticleSize().z(),getSize(i).z())
                                        );
    }
    
	//Affect Particles with System Affectors
	for(UInt32 j(0) ; j<getSystemAffectors().size(); ++j)
	{
		getSystemAffectors(j)->affect(ParticleSystemPtr(this), elps);
	}

	_isUpdating = false;
	internalKillParticles();

    if(NumParticles > 0)
    {
        if(PrevVolume != getVolume() || !getMaxParticleSize().isZero())
        {
            endEditCP(ParticleSystemPtr(this), VolumeFieldMask | MaxParticleSizeFieldMask);
        }
        else
        {
            endEditNotChangedCP(ParticleSystemPtr(this), VolumeFieldMask | MaxParticleSizeFieldMask);
        }
    }

    produceSystemUpdated();
}

void ParticleSystem::produceParticleGenerated(Int32 Index)
{
    if(_ParticleSystemListeners.size() > 0 || getNumActivitiesAttached(ParticleGeneratedMethodId)>0)
    {
        const ParticleEventPtr TheEvent = ParticleEvent::create( ParticleSystemPtr(this), getSystemTime(),
                Index,
                getPosition(Index),
                getSecPosition(Index),
                getNormal(Index),
                getColor(Index),
                getSize(Index),
                getLifespan(Index),
                getAge(Index),
                getVelocity(Index),
                getSecVelocity(Index),
                getAcceleration(Index),
                getAttributes(Index) );
        ParticleSystemListenerSetItor NextItor;
        for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
        {
            NextItor = SetItor;
            ++NextItor;
            (*SetItor)->particleGenerated(TheEvent);
            SetItor = NextItor;
        }
        _Producer.produceEvent(ParticleGeneratedMethodId,TheEvent);
    }
}

void ParticleSystem::produceParticleKilled(Int32 Index,
										 const Pnt3f& Position,
										 const Pnt3f& SecPosition,
										 const Vec3f& Normal,
										 const Color4f& Color,
										 const Vec3f& Size,
										 Real32 Lifespan,
										 Real32 Age,
										 const Vec3f& Velocity,
										 const Vec3f& SecVelocity,
										 const Vec3f& Acceleration,
                                         const StringToUInt32Map& Attributes)
{
   const ParticleEventPtr TheEvent = ParticleEvent::create( ParticleSystemPtr(this), getSystemTime(), Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleKilled(TheEvent);
      SetItor = NextItor;
   }
   _Producer.produceEvent(ParticleKilledMethodId,TheEvent);
}

void ParticleSystem::produceParticleStolen(Int32 Index,
										 const Pnt3f& Position,
										 const Pnt3f& SecPosition,
										 const Vec3f& Normal,
										 const Color4f& Color,
										 const Vec3f& Size,
										 Real32 Lifespan,
										 Real32 Age,
										 const Vec3f& Velocity,
										 const Vec3f& SecVelocity,
										 const Vec3f& Acceleration,
                                         const StringToUInt32Map& Attributes)
{
   const ParticleEventPtr TheEvent = ParticleEvent::create( ParticleSystemPtr(this), getSystemTime(), Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes );

   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleStolen(TheEvent);
      SetItor = NextItor;
   }
   _Producer.produceEvent(ParticleStolenMethodId,TheEvent);
}

void ParticleSystem::produceSystemUpdated()
{
   const ParticleSystemEventPtr TheEvent = ParticleSystemEvent::create( ParticleSystemPtr(this), getSystemTime());
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->systemUpdated(TheEvent);
      SetItor = NextItor;
   }
   _Producer.produceEvent(SystemUpdatedMethodId,TheEvent);
}

void ParticleSystem::produceVolumeChanged()
{
   const ParticleSystemEventPtr TheEvent = ParticleSystemEvent::create( ParticleSystemPtr(this), getSystemTime());
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->volumeChanged(TheEvent);
      SetItor = NextItor;
   }
   _Producer.produceEvent(VolumeChangedMethodId,TheEvent);
}

bool ParticleSystem::attachUpdateListener(WindowEventProducerPtr UpdateProducer)
{
    if(UpdateProducer == NullFC)
    {
        return false;
    }

    UpdateProducer->addUpdateListener(&_SystemUpdateListener);

    return true;
}

void ParticleSystem::dettachUpdateListener(WindowEventProducerPtr UpdateProducer)
{
    if(UpdateProducer != NullFC)
    {
        UpdateProducer->removeUpdateListener(&_SystemUpdateListener);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystem::ParticleSystem(void) :
    Inherited(),
    _SystemUpdateListener(this)
{
}

ParticleSystem::ParticleSystem(const ParticleSystem &source) :
    Inherited(source),
    _SystemUpdateListener(this)
{
}

ParticleSystem::~ParticleSystem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & VolumeFieldMask)
    {
        //Fire a Volume Change Event
        produceVolumeChanged();
    }
}

void ParticleSystem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystem NI" << std::endl;
}

/*----------------------------- internal classes ----------------------------*/
void ParticleSystem::SystemUpdateListener::update(const UpdateEventPtr e)
{
    _System->update(e->getElapsedTime());
}

OSG_END_NAMESPACE

