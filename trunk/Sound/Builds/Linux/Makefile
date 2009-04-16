###

LIB_NAME = OSGSound
LIB_INCLUDE_DIR_NAME = Sound

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/FMod:$(srcdir)/Sound:$(srcdir)/Sound/Events:$(srcdir)/Stub:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -fPIC -I$(FMOD_INC_DIR) -I$(FMOD_DESIGNER_INC_DIR) -I$(srcdir) -I../../../../Builds/Linux/include
EXTRA_LDFLAGS = $(FMOD_LD_FLAGS) $(BOOST_LD_FLAGS)

OBJECTS = OSGFModSoundChannel.o \
	OSGFModSoundManager.o \
	OSGFModSoundBase.o \
	OSGFModSound.o \
	OSGFModSoundChannelBase.o \
	OSGFModSoundManagerBase.o \
	OSGSound.o \
	OSGDialogCoordinatorBase.o \
	OSGSoundChannel.o \
	OSGSoundEmitter.o \
	OSGSoundBase.o \
	OSGSoundManager.o \
	OSGDialogCoordinator.o \
	OSGSoundChannelBase.o \
	OSGSoundEmitterBase.o \
	OSGSoundManagerBase.o \
	OSGSoundEvent.o \
	OSGStubSound.o \
	OSGStubSoundChannelBase.o \
	OSGStubSoundManagerBase.o \
	OSGStubSoundChannel.o \
	OSGStubSoundManager.o \
	OSGStubSoundBase.o
        
        
include $(commondir)/CommonMake.mk
