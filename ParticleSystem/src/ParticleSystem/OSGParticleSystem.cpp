/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
    (TypeTraits<BitVector>::One << ParticleSystem::InternalPropertiesFieldId);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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
	else if(getInternalColors().size())
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

void ParticleSystem::addAndExpandProperties(UInt64 Properties)
{
	if(getInternalProperties().size() == 0)
	{
		getInternalProperties().push_back(Properties);
	}
	else if(getInternalProperties().size() == 1)
	{
		if(getInternalProperties()[0] != Properties)
		{
			//Expand to Positions size-1
			for(UInt32 i(0) ; i<getInternalPositions().size()-1 ; ++i)
			{
				getInternalProperties().push_back(getInternalProperties()[0]);
			}

			getInternalProperties().push_back(Properties);
		}
	}
	else
	{
		getInternalProperties().push_back(Properties);
	}
}

bool ParticleSystem::killParticle(UInt32 Index)
{
    if(Index >= getNumParticles())
    {
        return false;
    }

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
    removeProperty(Index);

    produceParticleKilled();

    return true;
}

void ParticleSystem::removePosition(UInt32 Index)
{
    getInternalPositions()[Index] = getInternalPositions().back();
    getInternalPositions().resize(getInternalPositions().size()-1);
}

void ParticleSystem::removeSecPosition(UInt32 Index)
{
    if(getNumSecPositions() > 1)
    {
        getInternalSecPositions()[Index] = getInternalSecPositions().back();
        getInternalSecPositions().resize(getInternalSecPositions().size()-1);
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
        getInternalNormals().resize(getInternalNormals().size()-1);
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
        getInternalColors().resize(getInternalColors().size()-1);
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
        getInternalSizes().resize(getInternalSizes().size()-1);
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
        getInternalLifespans().resize(getInternalLifespans().size()-1);
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
        getInternalAges().resize(getInternalAges().size()-1);
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
        getInternalVelocities().resize(getInternalVelocities().size()-1);
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
        getInternalSecVelocities().resize(getInternalSecVelocities().size()-1);
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
        getInternalAccelerations().resize(getInternalAccelerations().size()-1);
    }
    else if(getNumParticles() == 0)
    {
        getInternalAccelerations().clear();
    }
}

void ParticleSystem::removeProperty(UInt32 Index)
{
    if(getNumProperties() > 1)
    {
        getInternalProperties()[Index] = getInternalProperties().back();
        getInternalProperties().resize(getInternalProperties().size()-1);
    }
    else if(getNumParticles() == 0)
    {
        getInternalProperties().clear();
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
					 UInt64 Properties)
{
	if(getNumParticles() >= getMaxParticles())
	{
		return false;
	}

	beginEditCP(ParticleSystemPtr(this), ParticleSystem::InternalParticlesFieldMask);
		getInternalPositions().push_back(Position);

		addAndExpandSecPositions(SecPosition);
		addAndExpandNormals(Normal);
		addAndExpandColors(Color);
		addAndExpandSizes(Size);
		addAndExpandLifespans(Lifespan);
		addAndExpandAges(Age);
		addAndExpandVelocities(Velocity);
		addAndExpandSecVelocities(SecVelocity);
		addAndExpandAccelerations(Acceleration);
		addAndExpandProperties(Properties);
	endEditCP(ParticleSystemPtr(this), ParticleSystem::InternalParticlesFieldMask);

    produceParticleGenerated();

	return true;
}

bool ParticleSystem::addParticle(const Pnt3f& Position,
					 const Vec3f& Normal,
					 const Color4f& Color,
					 const Vec3f& Size,
					 Real32 Lifespan,
					 const Vec3f& Velocity,
					 const Vec3f& Acceleration,
					 UInt64 Properties)
{
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
				 Properties);
}

const Vec3f& ParticleSystem::getPositionChange(const UInt32& Index) const
{
	return getPosition(Index) - getSecPosition(Index);
}

const Vec3f& ParticleSystem::getVelocityChange(const UInt32& Index) const
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
		getInternalSecPositions()[0];
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
		getInternalNormals()[0];
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
		getInternalColors()[0];
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
		getInternalSizes()[0];
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
		getInternalLifespans()[0];
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
		getInternalAges()[0];
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
		getInternalVelocities()[0];
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
		getInternalSecVelocities()[0];
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
		getInternalAccelerations()[0];
	}
}

UInt64 ParticleSystem::getProperty(const UInt32& Index) const
{
	if(Index < getInternalProperties().getSize())
	{
		return getInternalProperties()[Index];
	}
	else
	{
		getInternalProperties()[0];
	}
}

void ParticleSystem::setVelocity(const Vec3f& V, const UInt32& Index)
{
	if(getNumVelocities() > 1)
	{
		getInternalVelocities()[Index] = V;
	}
	else if(getNumVelocities() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalVelocities()[0] != V)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalVelocities().push_back(getInternalVelocities()[0]);
				}
				getInternalVelocities()[Index] = V;
			}
		}
		else
		{
			getInternalVelocities()[Index] = V;
		}
	}
}
void ParticleSystem::setAge(const Time& T, const UInt32& Index)
{
	if(getNumAges() > 1)
	{
		getInternalAges()[Index] = T;
	}
	else if(getNumAges() == 1)
	{
		if(getNumParticles() > 1)
		{
			if(getInternalAges()[0] != T)
			{
				//Expand to Positions size-1
				for(UInt32 i(0) ; i<getNumParticles()-1 ; ++i)
				{
					getInternalAges().push_back(getInternalAges()[0]);
				}
				getInternalAges()[Index] = T;
			}
		}
		else
		{
			getInternalAges()[Index] = T;
		}
	}
}

void ParticleSystem::update(const Time& elps)
{
    //TODO: Implement
	//Remember the Old Postions and velocities

	//Generate Particles with Generators

	//Effect Particles with Effectors

	//Effect Particle Systems

    //Loop through all of the particles
    bool VolumeChanged(false);
    UInt32 NumParticles(getNumParticles());
	bool AdvanceIterator(true);
    for(UInt32 i(0) ; i<NumParticles;)
    {
        VolumeChanged = true;

		//Apply Acceleration and Velocity
        setPosition(getPosition(i) + getVelocity(i)*elps + getAcceleration(i)*elps*elps, i);

		setVelocity(getVelocity(i) + getAcceleration(i)*elps,i);

		//Kill Particles that have ages > lifespans
		setAge(getAge(i) + elps,i);
		if(getAge(i)>getLifespan(i))
		{
			if(killParticle(i))
			{
				AdvanceIterator = false;
				--NumParticles;
			}
		}

		if(AdvanceIterator)
		{
			 ++i;
		}
		AdvanceIterator = true;
    }


    //Fire a Update Event
    produceSystemUpdated(VolumeChanged);
}

void ParticleSystem::produceParticleGenerated(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleGenerated(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceParticleKilled(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleKilled(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceParticleStolen(void)
{
   ParticleEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->particleStolen(TheEvent);
      SetItor = NextItor;
   }
}

void ParticleSystem::produceSystemUpdated(bool VolumeChanged)
{
   ParticleSystemEvent TheEvent( ParticleSystemPtr(this), getSystemTime(), VolumeChanged );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->systemUpdated(TheEvent);
      SetItor = NextItor;
   }
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
}

void ParticleSystem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystem NI" << std::endl;
}

/*----------------------------- internal classes ----------------------------*/
void ParticleSystem::SystemUpdateListener::update(const UpdateEvent& e)
{
    _System->update(e.getElapsedTime());
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPARTICLESYSTEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLESYSTEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLESYSTEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

