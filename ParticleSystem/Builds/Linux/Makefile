###

LIB_NAME = OSGParticleSystem
LIB_INCLUDE_DIR_NAME = ParticleSystem

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGParticleSystemBase.o \
	OSGParticleSystem.o \
	OSGListTypeInst.o \
	OSGParticleSystemIterator.o
        
        
include $(commondir)/CommonMake.mk
