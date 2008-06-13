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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystem

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


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

void ParticleSystem::update(const Time& elps)
{
    //TODO: Implement
    //Fire a Update Event
    produceSystemUpdated();
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

void ParticleSystem::produceSystemUpdated(void)
{
   ParticleSystemEvent TheEvent( ParticleSystemPtr(this), getSystemTime() );
   ParticleSystemListenerSetItor NextItor;
   for(ParticleSystemListenerSetItor SetItor(_ParticleSystemListeners.begin()) ; SetItor != _ParticleSystemListeners.end() ;)
   {
      NextItor = SetItor;
      ++NextItor;
      (*SetItor)->systemUpdated(TheEvent);
      SetItor = NextItor;
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

