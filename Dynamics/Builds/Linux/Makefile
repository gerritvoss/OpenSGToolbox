###

LIB_NAME = OSGDynamics
LIB_INCLUDE_DIR_NAME = Dynamics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir):$(srcdir)/Function:$(srcdir)/Distributions


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGFunction.o \
	OSGFunctionBase.o
        
        
include $(commondir)/CommonMake.mk
