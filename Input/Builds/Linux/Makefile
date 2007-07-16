###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Event:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/CoreGL:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/QT4:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/X:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGKeyEvent.o \
	OSGEventDispatchThread.o \
	OSGWindowEventProducer.o \
	OSGWindowEventProducerBase.o \
	OSGWindowEventProducerFactory.o \
	OSGWindowUtils.o \
	OSGGLUTWindowEventProducer.o \
	OSGGLUTWindowEventProducerBase.o \
	OSGWin32WindowEventProducer.o \
	OSGWin32WindowEventProducerBase.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
