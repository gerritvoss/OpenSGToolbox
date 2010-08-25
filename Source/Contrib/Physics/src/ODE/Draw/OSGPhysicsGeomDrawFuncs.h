
#ifndef _OSGPHYSICSGEOMDRAWFUNCS_H_
#define _OSGPHYSICSGEOMDRAWFUNCS_H_
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

#include "OSGPhysicsGeom.h"
#include "OSGPhysicsBoxGeom.h"
#include "OSGPhysicsCapsuleGeom.h"
#include "OSGPhysicsPlaneGeom.h"
#include "OSGPhysicsRayGeom.h"
#include "OSGPhysicsSphereGeom.h"
#include "OSGPhysicsTriMeshGeom.h"

OSG_BEGIN_NAMESPACE

void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsBoxGeomUnrecPtr geom);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsCapsuleGeomUnrecPtr geom);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsPlaneGeomUnrecPtr geom);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsRayGeomUnrecPtr geom);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsSphereGeomUnrecPtr geom);
void OSG_CONTRIBPHYSICS_DLLMAPPING drawPhysicsGeom(const PhysicsTriMeshGeomUnrecPtr geom);


void OSG_CONTRIBPHYSICS_DLLMAPPING dropPhysicsGeom(RenderAction* action,const NodeUnrecPtr node, const Color4f& col, MaterialUnrecPtr mat = NULL);
void OSG_CONTRIBPHYSICS_DLLMAPPING dropPhysicsGeom(RenderAction* action,const PhysicsGeomUnrecPtr geom, const Color4f& col, MaterialUnrecPtr mat = NULL);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSGEOMDRAWFUNCS_H_ */
