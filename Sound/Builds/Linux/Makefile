###

LIB_NAME = OSGSound
LIB_INCLUDE_DIR_NAME = Sound

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Sound:$(srcdir)/Sound/Events:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir)
EXTRA_LDFLAGS = 

OBJECTS = OSGSound.o \
	OSGSoundEmitterBase.o \
	OSGSoundEmitter.o \
	OSGSoundBase.o \
	OSGSoundEvent.o
        
        
include $(commondir)/CommonMake.mk
