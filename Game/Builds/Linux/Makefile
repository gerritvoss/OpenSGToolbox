###

LIB_NAME = OSGGame
LIB_INCLUDE_DIR_NAME = Game

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/MiniMap:$(srcdir)/MiniMap/Indicators:$(srcdir)/MiniMap/Events:$(srcdir)/Cameras:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include
EXTRA_LDFLAGS = -lboost_filesystem

OBJECTS = OSGMiniMapBase.o \
	OSGMiniMapOverlayBase.o \
	OSGLayeredImageMiniMap.o \
	OSGMiniMap.o \
	OSGMiniMapMatrixTransformation.o \
	OSGMiniMapTransformation.o \
	OSGMiniMapOverlay.o \
	OSGLayeredImageMiniMapBase.o \
	OSGMiniMapMatrixTransformationBase.o \
	OSGMiniMapTransformationBase.o \
	OSGMiniMapIndicatorComponentGenerator.o \
	OSGDefaultMiniMapIndicatorComponentGenerator.o \
	OSGMiniMapIndicator.o \
	OSGDefaultMiniMapIndicatorComponentGeneratorBase.o \
	OSGMiniMapIndicatorComponentGeneratorBase.o \
	OSGMiniMapIndicatorBase.o \
	OSGMiniMapEvent.o \
	OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o
        
        
include $(commondir)/CommonMake.mk
