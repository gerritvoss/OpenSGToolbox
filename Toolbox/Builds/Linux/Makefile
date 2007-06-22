###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir):$(srcdir)/Cameras


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGMatrixBeaconCameraBase.o \
	OSGMatrixBeaconCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o
        
        
include $(commondir)/CommonMake.mk
