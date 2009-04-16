/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSGPARTICLEEVENT_H_
#define _OSGPARTICLEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include <OpenSG/Input/OSGEvent.h>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

#include "ParticleSystem/OSGParticleSystemFields.h"

OSG_BEGIN_NAMESPACE

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleEvent : public Event
{
  /*=========================  PUBLIC  ===============================*/
  public:

   ParticleEvent(FieldContainerPtr Source, Time TimeStamp,
	 Int32 Index,
	 ParticleSystemPtr System,
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
	 UInt64 Properties);

    virtual const EventType &getType(void) const;

    const Int32 &getIndex(void) const;
    const ParticleSystemPtr &getSystem(void) const;
    const Pnt3f &getPosition(void) const;
    const Pnt3f &getSecPosition(void) const;
    const Vec3f &getNormal(void) const;
    const Color4f &getColor(void) const;
    const Vec3f &getSize(void) const;
    const Real32 &getLifespan(void) const;
    const Real32 &getAge(void) const;
    const Vec3f &getVelocity(void) const;
    const Vec3f &getSecVelocity(void) const;
    const Vec3f &getAcceleration(void) const;
    const UInt64 &getProperties(void) const;
    
    static const EventType &getClassType(void);
  private:
     static EventType _Type;
	 
	 Int32 _ParticleIndex;
	 ParticleSystemPtr _System;

	 Pnt3f _ParticlePosition;
     Pnt3f _ParticleSecPosition;
	 Vec3f _ParticleNormal;
	 Color4f _ParticleColor;
	 Vec3f _ParticleSize;
	 Real32 _ParticleLifespan;
	 Real32 _ParticleAge;
	 Vec3f _ParticleVelocity;
	 Vec3f _ParticleSecVelocity;
	 Vec3f _ParticleAcceleration;
	 UInt64 _ParticleProperties;
};

OSG_END_NAMESPACE

#include "OSGParticleEvent.inl"

#endif /* _OSGPARTICLEEVENT_H_ */
