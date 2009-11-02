/************************************************************************/
/* add includes                                                         */
/************************************************************************/
#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "ODE/OSGPhysicsHandler.h"
#include "ODE/OSGPhysicsWorld.h"
#include "ODE/OSGPhysicsBody.h"

#include "ODE/Geom/OSGPhysicsBoxGeom.h"
#include "ODE/Geom/OSGPhysicsPlaneGeom.h"
#include "ODE/Geom/OSGPhysicsSphereGeom.h"
#include "ODE/Geom/OSGPhysicsCapsuleGeom.h"
#include "ODE/Geom/OSGPhysicsTriMeshGeom.h"
#include "ODE/Geom/OSGPhysicsRayGeom.h"

#include "ODE/Spaces/OSGPhysicsSimpleSpace.h"
#include "ODE/Spaces/OSGPhysicsHashSpace.h"
#include "ODE/Spaces/OSGPhysicsSweepAndPruneSpace.h"
#include "ODE/Spaces/OSGPhysicsQuadTreeSpace.h"
#include "ODE/Spaces/OSGCollisionContactParameters.h"

#include "ODE/Joints/OSGPhysicsAMotorJoint.h"
#include "ODE/Joints/OSGPhysicsLMotorJoint.h"
#include "ODE/Joints/OSGPhysicsHinge2Joint.h"
#include "ODE/Joints/OSGPhysicsBallJoint.h"
#include "ODE/Joints/OSGPhysicsHingeJoint.h"
#include "ODE/Joints/OSGPhysicsSliderJoint.h"
#include "ODE/Joints/OSGPhysicsUniversalJoint.h"
#include "ODE/Joints/OSGPhysicsPistonJoint.h"
#include "ODE/Joints/OSGPhysicsPRJoint.h"
#include "ODE/Joints/OSGPhysicsPUJoint.h"
#include "ODE/Joints/OSGPhysicsPlane2DJoint.h"

#include "ODE/Utils/OSGPhysicsUtils.h"
