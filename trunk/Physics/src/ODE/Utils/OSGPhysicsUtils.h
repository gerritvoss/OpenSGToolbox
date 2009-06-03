
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
#include "ODE/OSGPhysicsHandler.h"

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

Vec3f OSG_PHYSICSLIB_DLLMAPPING calcMinGeometryBounds(GeometryPtr geo);
Pnt3f OSG_PHYSICSLIB_DLLMAPPING calcGeometryCenter(GeometryPtr geo);

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSUTILS_H_ */
