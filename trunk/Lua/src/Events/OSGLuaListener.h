/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Physics                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGCOLLISIONLISTENER_H_
#define _OSGCOLLISIONLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include <OpenSG/Input/OSGEventListener.h>
#include "OSGCollisionEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_PHYSICSLIB_DLLMAPPING CollisionListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void collision(const CollisionEvent& e) = 0;
};

typedef CollisionListener* CollisionListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGCOLLISIONLISTENER_H_ */
