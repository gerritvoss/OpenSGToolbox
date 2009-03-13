###

LIB_NAME = OSGParticleSystem
LIB_INCLUDE_DIR_NAME = ParticleSystem

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/ParticleSystem:$(srcdir)/ParticleSystem/MultiParticleSystemAffectors:$(srcdir)/ParticleSystem/ParticleGenerators:$(srcdir)/ParticleSystem/ParticleSystemDrawers:$(srcdir)/ParticleSystem/ParticleAffectors:$(srcdir)/ParticleSystem/Events:$(srcdir)/ParticleSystem/ParticleSystemAffectors:$(srcdir)/ParticleSystem/Dynamics:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include

OBJECTS = OSGNodeParticleSystemCore.o \
	OSGParticleSystemBase.o \
	OSGParticleSystem.o \
	OSGParticleSystemCoreBase.o \
	OSGParticleSystemCore.o \
	OSGNodeParticleSystemCoreBase.o \
	OSGMultiParticleSystemAffectorBase.o \
	OSGMultiParticleSystemAffector.o \
	OSGBurstParticleGenerator.o \
	OSGDynamicsParticleGenerator.o \
	OSGParticleGenerator.o \
	OSGRateParticleGenerator.o \
	OSGBurstParticleGeneratorBase.o \
	OSGDynamicsParticleGeneratorBase.o \
	OSGParticleGeneratorBase.o \
	OSGRateParticleGeneratorBase.o \
	OSGParticleSystemDrawer.o \
	OSGShaderQuadParticleSystemDrawer.o \
	OSGLineParticleSystemDrawer.o \
	OSGPointParticleSystemDrawer.o \
	OSGQuadParticleSystemDrawer.o \
	OSGParticleSystemDrawerBase.o \
	OSGShaderQuadParticleSystemDrawerBase.o \
	OSGLineParticleSystemDrawerBase.o \
	OSGPointParticleSystemDrawerBase.o \
	OSGQuadParticleSystemDrawerBase.o \
	OSGDistanceAttractRepelParticleAffectorBase.o \
	OSGDistanceKillParticleAffector.o \
	OSGDistanceFadeParticleAffector.o \
	OSGAgeFadeParticleAffector.o \
	OSGParticleAffector.o \
	OSGAgeSizeParticleAffector.o \
	OSGAgeFadeParticleAffectorBase.o \
	OSGDistanceParticleAffector.o \
	OSGDistanceKillParticleAffectorBase.o \
	OSGDistanceFadeParticleAffectorBase.o \
	OSGDistanceAttractRepelParticleAffector.o \
	OSGParticleAffectorBase.o \
	OSGAgeSizeParticleAffectorBase.o \
	OSGDistanceParticleAffectorBase.o \
	OSGCollisionEvent.o \
	OSGParticleEvent.o \
	OSGParticleSystemEvent.o \
	OSGParticleSystemAffector.o \
	OSGCollectiveGravityParticleSystemAffectorBase.o \
	OSGCollectiveGravityParticleSystemAffector.o \
	OSGGeometryCollisionParticleSystemAffectorBase.o \
	OSGGeometryCollisionParticleSystemAffector.o \
	OSGParticleSystemAffectorBase.o \
	OSGParticleDistribution3DBase.o \
	OSGParticleDistribution3D.o
        
        
include $(commondir)/CommonMake.mk
