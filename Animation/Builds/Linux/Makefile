###

#SHELL = /bin/tcsh
LIBTYPE ?= opt

# try to guess the OSGCONFIG path

OSGCONFIG := notset

# use OSGPOOL if set

OSGPOOL ?= ..

# try to get configured information first, will not work if more
# than one system is configured from one dir. Just for the 1.0

OSGINSTALLPREFIX := notset

#PREFIXSUFFIX := $(shell $(OSGPOOL)/CommonConf/config.guess)
#-include .prefix.$(PREFIXSUFFIX)

ifneq ($(OSGINSTALLPREFIX),notset)
    OSGCONFIG := $(OSGINSTALLPREFIX)/bin/osg-config
endif

ifneq ($(OPENSG_BASE_DIR),notset)
	OSGCONF := $(wildcard $(OPENSG_BASE_DIR)/bin/osg-config)

    ifneq ($(OSGCONF),)
		OSGCONFIG := $(OSGCONF)
	endif

endif

# if configure info wasn't found, maybe a Builds/* install?
ifeq ($(OSGCONFIG),notset)
    INSTALLROOT := $(wildcard ../Builds/$(shell ../CommonConf/config.guess)-*)
    OSGCONF := $(wildcard $(INSTALLROOT)/bin/osg-config)
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# maybe we can find it in the path?
ifeq ($(OSGCONFIG),notset)
    OSGCONF := \
       $(shell if which osg-config >/dev/null 2>&1; then which osg-config; fi )  
    OSGCONF := $(strip $(OSGCONF))
    ifneq ($(OSGCONF),)
        OSGCONFIG := $(OSGCONF)
    endif
endif

# ok, give up
ifeq ($(OSGCONFIG),notset)
    $(error Can't find osg-config, please configure the Makefile or \
            add it to your PATH)
endif

# Set the system we're running on
SYSTEM := $(shell uname)

# which extension to be used for executables
EXEEXT :=

# be very careful with these lines. There needs to be a space after the Unix
# lines and nothing after the win lines!!

ifeq ($(SYSTEM),IRIX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(SYSTEM),IRIX64)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(SYSTEM),Linux)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(findstring WIN,$(SYSTEM)),WIN)
        OS := WIN32
        CCOUT := -Fo
        LDOUT := /out:
	LINK   := -link
	EXEEXT :=.exe
endif
ifeq ($(SYSTEM),HP-UX)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif
ifeq ($(SYSTEM),Darwin)
        CCOUT := -o 
        LDOUT := -o 
	LINK  := 
endif

# Var settings

CC = `$(OSGCONFIG) --compiler`

CCFLAGS = `$(OSGCONFIG) --cflags --$(LIBTYPE) Base System`

LDFLAGS = $(LINK) `$(OSGCONFIG) --libs --$(LIBTYPE) Base System`

LIB_NAME = OSGAnimation

srcdir = ../../../src
VPATH = ../../../src:../../../src/Animations:../../../src/Animators:../../../src/KeyframeSequence:../../../src/Interpolation:../../../src/Cameras:../../../src/Animations/Advancers:../../../src/GeometryAnimation:../../../src/KeyframeSequence/GeometryKeyframeSequences:../../../src/Util
#.SUFFIX = .cpp .o

INCLUDES = -I$(srcdir)

OBJECTS = OSGFieldAnimation.o \
	OSGFieldAnimationBase.o \
	OSGShaderAnimation.o \
	OSGGeoPropertyOperations.o \
	OSGShaderAnimationBase.o \
	OSGGeometryAnimation.o \
	OSGGeometryAnimationBase.o \
	OSGAnimation.o \
	OSGAnimationBase.o \
	OSGGeoDifferenceSetBase.o \
	OSGGeoDifferenceSet.o \
	OSGGeoPositionDifferenceSetBase.o \
	OSGGeoPositionDifferenceSet.o \
	OSGAnimationAdvancerBase.o \
	OSGAnimationAdvancer.o \
	OSGConstantAnimationAdvancerBase.o \
	OSGConstantAnimationAdvancer.o \
	OSGElapsedTimeAnimationAdvancerBase.o \
	OSGElapsedTimeAnimationAdvancer.o \
	OSGFieldAnimationAdvancerBase.o \
	OSGFieldAnimationAdvancer.o \
	OSGAnimator.o \
	OSGKeyframeAnimatorBase.o \
	OSGAnimatorBase.o \
	OSGKeyframeAnimator.o \
	OSGInterpolationFactory.o \
	OSGMFInterpolations.o \
	OSGGeometryInterpolations.o \
	OSGAirplaneCameraBase.o \
	OSGAirplaneCamera.o \
	OSGRubberBandCameraBase.o \
	OSGRubberBandCamera.o \
	OSGMatrixBeaconCameraBase.o \
	OSGMatrixBeaconCamera.o \
	OSGKeyframeSequenceGeoPositionsPtr.o \
	OSGKeyframeSequenceGeoPositionsPtrBase.o \
	OSGKeyframeSequenceOSGNodePtr.o \
	OSGKeyframeSequenceOSGNodePtrBase.o \
	OSGKeyframeSequenceNodeCorePtr.o \
	OSGKeyframeSequenceNodeCorePtrBase.o \
	OSGKeyframeSequenceMaterialPtr.o \
	OSGKeyframeSequenceMaterialPtrBase.o \
	OSGKeyframeSequenceStateChunkPtr.o \
	OSGKeyframeSequenceStateChunkPtrBase.o \
	OSGKeyframeSequenceTextureChunkPtr.o \
	OSGKeyframeSequenceTextureChunkPtrBase.o \
	OSGKeyframeSequenceImagePtr.o \
	OSGKeyframeSequenceImagePtrBase.o \
	OSGKeyframeSequence.o \
	OSGKeyframeSequenceReal32.o \
	OSGKeyframeSequenceInt32.o \
	OSGKeyframeSequencePnt3fBase.o \
	OSGKeyframeSequenceColor4f.o \
	OSGKeyframeSequenceVec2f.o \
	OSGKeyframeSequenceStringBase.o \
	OSGKeyframeSequenceMatrix.o \
	OSGKeyframeSequenceColor3f.o \
	OSGKeyframeSequenceGLenum.o \
	OSGKeyframeSequenceVec2fBase.o \
	OSGKeyframeSequenceUInt8Base.o \
	OSGKeyframeSequenceTimeBase.o \
	OSGKeyframeSequenceGLenumBase.o \
	OSGKeyframeSequenceUInt16Base.o \
	OSGKeyframeSequenceUInt8.o \
	OSGKeyframeSequenceTime.o \
	OSGKeyframeSequenceBool.o \
	OSGKeyframeSequenceBase.o \
	OSGKeyframeSequenceQuaternion.o \
	OSGKeyframeSequenceColor3fBase.o \
	OSGKeyframeSequenceVec3fBase.o \
	OSGKeyframeSequenceUInt16.o \
	OSGKeyframeSequenceQuaternionBase.o \
	OSGKeyframeSequenceUInt32Base.o \
	OSGKeyframeSequencePnt3f.o \
	OSGKeyframeSequenceVec3f.o \
	OSGKeyframeSequenceUInt32.o \
	OSGKeyframeSequenceColor4fBase.o \
	OSGKeyframeSequenceMatrixBase.o \
	OSGKeyframeSequenceInt32Base.o \
	OSGKeyframeSequenceReal32Base.o \
	OSGKeyframeSequencePnt2f.o \
	OSGKeyframeSequencePnt2fBase.o \
	OSGKeyframeSequenceBoolBase.o \
	OSGKeyframeSequenceString.o

ifeq ($(LIBTYPE),dbg)
	DGB_OPT_EXT := D
endif
SHARED_LIB_NAME=lib$(LIB_NAME)$(DGB_OPT_EXT).so

STATIC_LIB_NAME=lib$(LIB_NAME)$(DGB_OPT_EXT).a

default:	$(SHARED_LIB_NAME) \
	$(STATIC_LIB_NAME)

$(SHARED_LIB_NAME): $(OBJECTS)
	$(CC) -shared $(LDOUT) $(SHARED_LIB_NAME) $(OBJECTS) $(LDFLAGS)
	cp $(SHARED_LIB_NAME) ../../../../../../Linux.Build/$(LIBTYPE)/
        
$(STATIC_LIB_NAME): $(OBJECTS)
	ar -ruv $(STATIC_LIB_NAME) $(OBJECTS)
	cp $(STATIC_LIB_NAME) ../../../../../../Linux.Build/$(LIBTYPE)/

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(INCLUDES) $<

%: %.o
	$(CC) $(LDOUT)$@ $< $(LDFLAGS)
                                                                                                                                                             
# -----------------------------------------------------------------------------
# Clean-up.
# -----------------------------------------------------------------------------
clean:
	rm -f $(SHARED_LIB_NAME) $(STATIC_LIB_NAME) $(OBJECTS) *core     \
          so_locations *.?db
