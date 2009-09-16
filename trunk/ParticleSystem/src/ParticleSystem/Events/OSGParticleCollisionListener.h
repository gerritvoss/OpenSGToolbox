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

#ifndef _OSGPARTICLECOLLISIONLISTENER_H_
#define _OSGPARTICLECOLLISIONLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include <OpenSG/Toolbox/OSGEventListener.h>
#include "OSGParticleEvent.h"
#include "OSGCollisionEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleCollisionListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void particleCollision(const ParticleEvent& ParE, const CollisionEvent& ColE) = 0;
};

typedef ParticleCollisionListener* ParticleCollisionListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGPARTICLECOLLISIONLISTENER_H_ */
