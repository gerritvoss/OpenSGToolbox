
#ifndef _OSGPHYSICSUTILS_H_
#define _OSGPHYSICSUTILS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGAction.h>

#include <vector>

#include "ODE/OSGPhysicsHandler.h"
#include "ODE/OSGPhysicsWorld.h"
#include "ODE/OSGPhysicsBody.h"
#include "ODE/Spaces/OSGPhysicsSpace.h"
#include "ODE/Geom/OSGPhysicsGeom.h"
#include "ODE/Joints/OSGPhysicsJoint.h"

OSG_BEGIN_NAMESPACE

class OSG_PHYSICSLIB_DLLMAPPING PhysicsHandlerFinder
{
public:

    PhysicsHandlerFinder(void);

    PhysicsHandlerPtr operator() (NodePtr root);

    static PhysicsHandlerPtr find(NodePtr root);

private:

    Action::ResultE check(NodePtr& node);

    PhysicsHandlerPtr  _found;
};

class OSG_PHYSICSLIB_DLLMAPPING PhysicsGeometryFinder
{
public:

    PhysicsGeometryFinder(void);

    NodePtr operator() (NodePtr root);

    static NodePtr find(NodePtr root);

private:

    Action::ResultE check(NodePtr& node);

    NodePtr  _found;
};

class OSG_PHYSICSLIB_DLLMAPPING PhysicsAttachmentsFinder
{
public:

    PhysicsAttachmentsFinder(void);

    void traverse(NodePtr root);

    const std::vector<PhysicsHandlerPtr>&  getFoundHandlers(void) const;
    const std::vector<PhysicsWorldPtr>&    getFoundWorlds(void) const;
    const std::vector<PhysicsGeomPtr>&     getFoundGeoms(void) const;
    const std::vector<PhysicsSpacePtr>&    getFoundSpaces(void) const;
    const std::vector<PhysicsBodyPtr>&     getFoundBodies(void) const;
    const std::vector<PhysicsJointPtr>&    getFoundJoints(void) const;

private:

    Action::ResultE check(NodePtr& node);

    std::vector<PhysicsHandlerPtr>  _FoundHandlers;
    std::vector<PhysicsWorldPtr>  _FoundWorlds;
    std::vector<PhysicsGeomPtr>  _FoundGeoms;
    std::vector<PhysicsSpacePtr>  _FoundSpaces;
    std::vector<PhysicsBodyPtr>  _FoundBodies;
    std::vector<PhysicsJointPtr>  _FoundJoints;
};

Vec3f OSG_PHYSICSLIB_DLLMAPPING calcMinGeometryBounds(GeometryPtr geo);
Pnt3f OSG_PHYSICSLIB_DLLMAPPING calcGeometryCenter(GeometryPtr geo);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSUTILS_H_ */
