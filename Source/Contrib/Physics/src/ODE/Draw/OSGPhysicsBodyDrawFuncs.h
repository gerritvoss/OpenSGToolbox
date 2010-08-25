
#ifndef _OSGPHYSICSBODYDRAWFUNCS_H_
#define _OSGPHYSICSBODYDRAWFUNCS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include "OSGConfig.h"
#include "OSGContribPhysicsDef.h"


#include "OSGRenderAction.h"
#include "OSGMaterial.h"
#include "OSGColor.h"
#include "OSGNode.h"

#include "OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsBodyCoordinateSystem(const PhysicsBodyUnrecPtr body, Real32 Length);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsBodyLinearVelocity(const PhysicsBodyUnrecPtr body, Real32 Length);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsBodyAngularVelocity(const PhysicsBodyUnrecPtr body, Real32 Length);


void OSG_CONTRIBPHYSICS_DLLMAPPING dropPhysicsBody(RenderAction* action,const NodeUnrecPtr node, MaterialUnrecPtr mat = NULL);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSBODYDRAWFUNCS_H_ */
