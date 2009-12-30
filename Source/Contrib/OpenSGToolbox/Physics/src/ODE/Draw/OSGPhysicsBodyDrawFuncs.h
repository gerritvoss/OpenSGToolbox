
#ifndef _OSGPHYSICSBODYDRAWFUNCS_H_
#define _OSGPHYSICSBODYDRAWFUNCS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"


#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGMaterial.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGNode.h>

#include "ODE/OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsBodyCoordinateSystem(const PhysicsBodyPtr body, Real32 Length);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsBodyLinearVelocity(const PhysicsBodyPtr body, Real32 Length);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsBodyAngularVelocity(const PhysicsBodyPtr body, Real32 Length);


void OSG_PHYSICSLIB_DLLMAPPING dropPhysicsBody(DrawActionBase* action,const NodePtr node, MaterialPtr mat = NullFC);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSBODYDRAWFUNCS_H_ */
