
#ifndef _OSGPHYSICSGEOMDRAWFUNCS_H_
#define _OSGPHYSICSGEOMDRAWFUNCS_H_
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

#include "ODE/Geom/OSGPhysicsGeom.h"
#include "ODE/Geom/OSGPhysicsBoxGeom.h"
#include "ODE/Geom/OSGPhysicsCapsuleGeom.h"
#include "ODE/Geom/OSGPhysicsPlaneGeom.h"
#include "ODE/Geom/OSGPhysicsRayGeom.h"
#include "ODE/Geom/OSGPhysicsSphereGeom.h"
#include "ODE/Geom/OSGPhysicsTriMeshGeom.h"

OSG_BEGIN_NAMESPACE

void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsBoxGeomPtr geom);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsCapsuleGeomPtr geom);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsPlaneGeomPtr geom);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsRayGeomPtr geom);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsSphereGeomPtr geom);
void OSG_PHYSICSLIB_DLLMAPPING drawPhysicsGeom(const PhysicsTriMeshGeomPtr geom);


void OSG_PHYSICSLIB_DLLMAPPING dropPhysicsGeom(DrawActionBase* action,const NodePtr node, const Color4f& col, MaterialPtr mat = NullFC);
void OSG_PHYSICSLIB_DLLMAPPING dropPhysicsGeom(DrawActionBase* action,const PhysicsGeomPtr geom, const Color4f& col, MaterialPtr mat = NullFC);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSGEOMDRAWFUNCS_H_ */
