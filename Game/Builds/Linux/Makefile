###

LIB_NAME = OSGGame
LIB_INCLUDE_DIR_NAME = Game

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/MiniMap:$(srcdir)/Cameras:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include
EXTRA_LDFLAGS = -lboost_filesystem

OBJECTS = OSGMiniMapBase.o \
	OSGMiniMapOverlayBase.o \
	OSGLayeredImageMiniMap.o \
	OSGMiniMapTransformation.o \
	OSGMiniMapIndicator.o \
	OSGMiniMap.o \
	OSGMiniMapOverlay.o \
	OSGLayeredImageMiniMapBase.o \
	OSGMiniMapTransformationBase.o \
	OSGMiniMapIndicatorBase.o \
	OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o
        
        
include $(commondir)/CommonMake.mk
