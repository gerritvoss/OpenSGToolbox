###

LIB_NAME = OSGSound
LIB_INCLUDE_DIR_NAME = Sound

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/FMod:$(srcdir)/Sound:$(srcdir)/Sound/Events:$(srcdir)/Stub:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -fPIC -I$(FMOD_BASE_DIR)/inc -I$(srcdir) -I../../../../Builds/Linux/include
EXTRA_LDFLAGS = -L$(FMOD_BASE_DIR)/lib -lfmodex64 -L$(BOOST_BASE_DIR)/lib -lboost_filesystem-gcc41-mt-1_38 -lboost_system-gcc41-mt-1_38 

OBJECTS = OSGFModSoundChannel.o \
	OSGFModSoundManager.o \
	OSGFModSoundBase.o \
	OSGFModSound.o \
	OSGSound.o \
	OSGSoundGroupBase.o \
	OSGSoundGroup.o \
	OSGSoundEmitter.o \
	OSGSoundBase.o \
	OSGSoundManager.o \
	OSGSoundEmitterBase.o \
	OSGSoundEvent.o \
	OSGStubSound.o \
	OSGStubSoundManager.o \
	OSGStubSoundBase.o
        
        
include $(commondir)/CommonMake.mk
