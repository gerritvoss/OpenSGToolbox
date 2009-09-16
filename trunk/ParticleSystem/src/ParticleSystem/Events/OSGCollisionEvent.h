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
#ifndef _OSGCOLLISIONEVENT_H_
#define _OSGCOLLISIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGVector.h>

#include <OpenSG/Toolbox/OSGEvent.h>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

class OSG_PARTICLESYSTEMLIB_DLLMAPPING CollisionEvent : public Event
{
  /*=========================  PUBLIC  ===============================*/
  public:

   CollisionEvent(FieldContainerPtr Source, Time TimeStamp,
	   Real32 HitT,
	   NodePtr HitNode,
	   Int32 HitPoly,
	   Vec3f HitNormal,
	   Pnt3f HitPoint);

    virtual const EventType &getType(void) const;
    const Real32 &getHitT(void) const;
    const NodePtr &getHitNode(void) const;
    const Int32 &getHitPoly(void) const;
    const Vec3f &getHitNormal(void) const;
    const Pnt3f &getHitPoint(void) const;
    
    static const EventType &getClassType(void);
  private:
     static EventType _Type;

	 Real32 _HitT;
	 NodePtr _HitNode;
	 Int32 _HitPoly;
	 Vec3f _HitNormal;
	 Pnt3f _HitPoint;
};

OSG_END_NAMESPACE

#include "OSGCollisionEvent.inl"

#endif /* _OSGCOLLISIONEVENT_H_ */
