###

LIB_NAME = OSGGame
LIB_INCLUDE_DIR_NAME = Game

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/MiniMap:$(srcdir)/MiniMap/Indicators:$(srcdir)/MiniMap/Overlays:$(srcdir)/MiniMap/Events:$(srcdir)/Cameras:$(srcdir)/Caption:$(srcdir)/Caption/Event:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -fPIC -I$(FMOD_BASE_DIR)/inc -I$(srcdir) -I$(BOOST_BASE_DIR)/include -I../../../../Builds/Linux/include -D_OSG_TOOLBOX_USE_FMOD_

OBJECTS = OSGMiniMapBase.o \
	OSGLayeredImageMiniMap.o \
	OSGMiniMap.o \
	OSGMiniMapMatrixTransformation.o \
	OSGMiniMapTransformation.o \
	OSGLayeredImageMiniMapBase.o \
	OSGMiniMapMatrixTransformationBase.o \
	OSGMiniMapTransformationBase.o \
	OSGMiniMapIndicatorComponentGenerator.o \
	OSGDefaultMiniMapIndicatorComponentGenerator.o \
	OSGMiniMapIndicator.o \
	OSGDefaultMiniMapIndicatorComponentGeneratorBase.o \
	OSGMiniMapIndicatorComponentGeneratorBase.o \
	OSGMiniMapIndicatorBase.o \
	OSGDirectionalIndicatorMiniMapOverlayBase.o \
	OSGMiniMapOverlayBase.o \
	OSGDirectionalIndicatorMiniMapOverlay.o \
	OSGDirectionalIndicatorComponentGeneratorBase.o \
	OSGMiniMapOverlay.o \
	OSGDefaultDirectionalIndicatorComponentGenerator.o \
	OSGDirectionalIndicatorComponentGenerator.o \
	OSGDefaultDirectionalIndicatorComponentGeneratorBase.o \
	OSGMiniMapEvent.o \
	OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o \
	OSGDefaultCaptionComponentGeneratorBase.o \
	OSGCaptionComponentGenerator.o \
	OSGCaptionBase.o \
	OSGDefaultCaptionComponentGenerator.o \
	OSGCaption.o \
	OSGCaptionComponentGeneratorBase.o \
	OSGCaptionEvent.o
        
        
include $(commondir)/CommonMake.mk
