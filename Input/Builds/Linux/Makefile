###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Event:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/X:$(srcdir)/WindowSystem/QT4:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/CoreGL:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGKeyEventProducer.o \
	OSGMouseEventProducer.o \
	OSGKeyEvent.o \
	OSGMouseWheelEventProducer.o \
	OSGMouseMotionEventProducer.o \
	OSGWindowUtils.o \
	OSGEventDispatchThread.o \
	OSGWindowEventProducerFactory.o \
	OSGWindowEventProducerBase.o \
	OSGWindowEventProducer.o \
	OSGWin32WindowEventProducerBase.o \
	OSGWin32WindowEventProducer.o \
	OSGGLUTWindowEventProducer.o \
	OSGGLUTWindowEventProducerBase.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
