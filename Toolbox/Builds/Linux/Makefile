###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Cameras:$(srcdir)/Util:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGAirplaneCamera.o \
	OSGAirplaneCameraBase.o \
	OSGMatrixBeaconCamera.o \
	OSGMatrixBeaconCameraBase.o \
	OSGRubberBandCamera.o \
	OSGRubberBandCameraBase.o \
	OSGGLenumUtils.o \
	OSGIntrusivePtrImplBase.o
        
        
include $(commondir)/CommonMake.mk
