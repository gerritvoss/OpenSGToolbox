###

LIB_NAME = OSGPhysics
LIB_INCLUDE_DIR_NAME = Physics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Events:$(srcdir)/ODE:$(srcdir)/ODE/Geom:$(srcdir)/ODE/Utils:$(srcdir)/ODE/Joints:$(srcdir)/ODE/Spaces:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -fPIC `$(ODE_BASE_DIR)/bin/ode-config --cflags` -I$(srcdir) -I$(BOOST_BASE_DIR)/include -I../../../../Builds/Linux/include 
EXTRA_LDFLAGS = `$(ODE_BASE_DIR)/bin/ode-config --libs`

OBJECTS = OSGCollisionEvent.o \
	OSGPhysicsWorldBase.o \
	OSGPhysicsWorld.o \
	OSGPhysicsBodyBase.o \
	OSGPhysicsBody.o \
	OSGPhysicsHandlerBase.o \
	OSGPhysicsHandler.o \
	OSGPhysicsTriMeshGeom.o \
	OSGPhysicsCCylinderGeom.o \
	OSGPhysicsGeom.o \
	OSGPhysicsSphereGeom.o \
	OSGPhysicsBoxGeom.o \
	OSGPhysicsPlaneGeomBase.o \
	OSGPhysicsRayGeom.o \
	OSGPhysicsTriMeshGeomBase.o \
	OSGPhysicsCCylinderGeomBase.o \
	OSGPhysicsGeomBase.o \
	OSGPhysicsSphereGeomBase.o \
	OSGPhysicsBoxGeomBase.o \
	OSGPhysicsRayGeomBase.o \
	OSGPhysicsPlaneGeom.o \
	OSGPhysicsUtils.o \
	OSGPhysicsPRJoint.o \
	OSGPhysicsHingeJointBase.o \
	OSGPhysicsPistonJointBase.o \
	OSGPhysicsLMotorJoint.o \
	OSGPhysicsSliderJointBase.o \
	OSGPhysicsJoint.o \
	OSGPhysicsHingeJoint.o \
	OSGPhysicsAMotorJointBase.o \
	OSGPhysicsUniversalJointBase.o \
	OSGPhysicsPistonJoint.o \
	OSGPhysicsPUJointBase.o \
	OSGPhysicsSliderJoint.o \
	OSGPhysicsAMotorJoint.o \
	OSGPhysicsBallJointBase.o \
	OSGPhysicsHinge2JointBase.o \
	OSGPhysicsUniversalJoint.o \
	OSGPhysicsPRJointBase.o \
	OSGPhysicsPUJoint.o \
	OSGPhysicsLMotorJointBase.o \
	OSGPhysicsBallJoint.o \
	OSGPhysicsJointBase.o \
	OSGPhysicsHinge2Joint.o \
	OSGPhysicsSweepAndPruneSpaceBase.o \
	OSGCollisionContactParameters.o \
	OSGPhysicsHashSpaceBase.o \
	OSGPhysicsSpace.o \
	OSGPhysicsSimpleSpaceBase.o \
	OSGCollisionContactParametersBase.o \
	OSGPhysicsSpaceBase.o \
	OSGPhysicsQuadTreeSpace.o \
	OSGPhysicsSweepAndPruneSpace.o \
	OSGPhysicsHashSpace.o \
	OSGPhysicsSimpleSpace.o \
	OSGPhysicsQuadTreeSpaceBase.o
        
        
include $(commondir)/CommonMake.mk
