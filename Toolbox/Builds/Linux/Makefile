###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Util:$(srcdir)/Cameras:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGAirplaneCamera.o \
	OSGMatrixBeaconCameraBase.o \
	OSGMatrixBeaconCamera.o \
	OSGRubberBandCamera.o \
	OSGRubberBandCameraBase.o \
	OSGAirplaneCameraBase.o
        
        
include $(commondir)/CommonMake.mk
