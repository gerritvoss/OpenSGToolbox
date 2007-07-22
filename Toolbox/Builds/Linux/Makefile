###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Cameras:$(srcdir)/Util:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGMatrixBeaconCamera.o \
	OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o \
	OSGMatrixBeaconCameraBase.o
        
        
include $(commondir)/CommonMake.mk
