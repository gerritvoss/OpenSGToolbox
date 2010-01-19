
#ifndef _OSGPHYSICSUTILS_H_
#define _OSGPHYSICSUTILS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include "OSGConfig.h"
#include "OSGContribPhysicsDef.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeometry.h"
#include "OSGBaseFunctions.h"
#include "OSGTransform.h"
#include "OSGAction.h"

#include <vector>

#include "OSGPhysicsHandler.h"
#include "OSGPhysicsWorld.h"
#include "OSGPhysicsBody.h"
#include "OSGPhysicsSpace.h"
#include "OSGPhysicsGeom.h"
#include "OSGPhysicsJoint.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsHandlerFinder
{
public:

    PhysicsHandlerFinder(void);

    PhysicsHandlerUnrecPtr operator() (NodeUnrecPtr root);

    static PhysicsHandlerUnrecPtr find(NodeUnrecPtr root);

private:

    Action::ResultE check(Node*& node);

    PhysicsHandlerUnrecPtr  _found;
};

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsGeometryFinder
{
public:

    PhysicsGeometryFinder(void);

    NodeUnrecPtr operator() (NodeUnrecPtr root);

    static NodeUnrecPtr find(NodeUnrecPtr root);

private:

    Action::ResultE check(Node*& node);

    NodeUnrecPtr  _found;
};

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsAttachmentsFinder
{
public:

    PhysicsAttachmentsFinder(void);

    void traverse(NodeUnrecPtr root);

    const std::vector<const PhysicsHandler*>&  getFoundHandlers(void) const;
    const std::vector<const PhysicsWorld*>&    getFoundWorlds(void) const;
    const std::vector<const PhysicsGeom*>&     getFoundGeoms(void) const;
    const std::vector<const PhysicsSpace*>&    getFoundSpaces(void) const;
    const std::vector<const PhysicsBody*>&     getFoundBodies(void) const;
    const std::vector<const PhysicsJoint*>&    getFoundJoints(void) const;

private:

    Action::ResultE check(Node*& node);

    std::vector<const PhysicsHandler*>  _FoundHandlers;
    std::vector<const PhysicsWorld*>  _FoundWorlds;
    std::vector<const PhysicsGeom*>  _FoundGeoms;
    std::vector<const PhysicsSpace*>  _FoundSpaces;
    std::vector<const PhysicsBody*>  _FoundBodies;
    std::vector<const PhysicsJoint*>  _FoundJoints;
};

Vec3f OSG_CONTRIBPHYSICS_DLLMAPPING calcMinGeometryBounds(GeometryUnrecPtr geo);
Pnt3f OSG_CONTRIBPHYSICS_DLLMAPPING calcGeometryCenter(GeometryUnrecPtr geo);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSUTILS_H_ */
