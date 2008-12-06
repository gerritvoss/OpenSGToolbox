###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Types:$(srcdir)/Util:$(srcdir)/Cameras:$(srcdir)/FileIO:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)
EXTRA_LDFLAGS = -lboost_filesystem

OBJECTS = OSGStringMapType.o \
	OSGPathType.o \
	OSGFieldContainerMapType.o \
	OSGIntrusivePtrImplBase.o \
	OSGRandomPoolManager.o \
	OSGCameraUtils.o \
	OSGGLenumUtils.o \
	OSGAirplaneCamera.o \
	OSGMatrixBeaconCameraBase.o \
	OSGMatrixBeaconCamera.o \
	OSGRubberBandCamera.o \
	OSGRubberBandCameraBase.o \
	OSGAirplaneCameraBase.o \
	OSGBinFCFileType.o \
	OSGFCFileHandler.o \
	OSGFCFileType.o \
	OSGXMLFCFileType.o
        
        
include $(commondir)/CommonMake.mk
