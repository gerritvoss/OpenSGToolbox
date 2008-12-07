###

LIB_NAME = OSGParticleSystem
LIB_INCLUDE_DIR_NAME = ParticleSystem

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/ParticleSystem:$(srcdir)/ParticleSystem/MultiParticleSystemAffectors:$(srcdir)/ParticleSystem/ParticleGenerators:$(srcdir)/ParticleSystem/ParticleSystemDrawers:$(srcdir)/ParticleSystem/Events:$(srcdir)/ParticleSystem/ParticleAffectors:$(srcdir)/ParticleSystem/ParticleSystemAffectors:$(srcdir)/ParticleSystem/Dynamics:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include

OBJECTS = OSGParticleSystemBase.o \
	OSGParticleSystem.o \
	OSGParticleSystemCoreBase.o \
	OSGParticleSystemCore.o \
	OSGNodeParticleSystemCore.o \
	OSGNodeParticleSystemCoreBase.o \
	OSGMultiParticleSystemAffectorBase.o \
	OSGMultiParticleSystemAffector.o \
	OSGParticleGeneratorBase.o \
	OSGParticleGenerator.o \
	OSGBurstParticleGenerator.o \
	OSGDynamicsParticleGenerator.o \
	OSGBurstParticleGeneratorBase.o \
	OSGRateParticleGenerator.o \
	OSGDynamicsParticleGeneratorBase.o \
	OSGRateParticleGeneratorBase.o \
	OSGShaderQuadParticleSystemDrawer.o \
	OSGPointParticleSystemDrawer.o \
	OSGQuadParticleSystemDrawer.o \
	OSGParticleSystemDrawerBase.o \
	OSGLineParticleSystemDrawerBase.o \
	OSGParticleSystemDrawer.o \
	OSGLineParticleSystemDrawer.o \
	OSGShaderQuadParticleSystemDrawerBase.o \
	OSGPointParticleSystemDrawerBase.o \
	OSGQuadParticleSystemDrawerBase.o \
	OSGParticleEvent.o \
	OSGParticleSystemEvent.o \
	OSGCollisionEvent.o \
	OSGAgeFadeParticleAffectorBase.o \
	OSGParticleAffectorBase.o \
	OSGAgeFadeParticleAffector.o \
	OSGParticleAffector.o \
	OSGDistanceAttractRepelParticleAffectorBase.o \
	OSGDistanceKillParticleAffector.o \
	OSGDistanceFadeParticleAffector.o \
	OSGAgeSizeParticleAffector.o \
	OSGDistanceParticleAffector.o \
	OSGDistanceKillParticleAffectorBase.o \
	OSGDistanceFadeParticleAffectorBase.o \
	OSGDistanceAttractRepelParticleAffector.o \
	OSGAgeSizeParticleAffectorBase.o \
	OSGDistanceParticleAffectorBase.o \
	OSGParticleSystemAffectorBase.o \
	OSGParticleSystemAffector.o \
	OSGCollectiveGravityParticleSystemAffectorBase.o \
	OSGCollectiveGravityParticleSystemAffector.o \
	OSGGeometryCollisionParticleSystemAffectorBase.o \
	OSGGeometryCollisionParticleSystemAffector.o \
	OSGParticleDistribution3DBase.o \
	OSGParticleDistribution3D.o
        
        
include $(commondir)/CommonMake.mk
