###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/CoreGL:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/X:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/QT4:$(srcdir)/Event:$(srcdir)/Utils:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGEventDispatchThread.o \
	OSGWindowEventProducer.o \
	OSGWindowEventProducerBase.o \
	OSGWindowUtils.o \
	OSGWindowEventProducerFactory.o \
	OSGGLUTWindowEventProducer.o \
	OSGGLUTWindowEventProducerBase.o \
	OSGWin32WindowEventProducer.o \
	OSGWin32WindowEventProducerBase.o \
	OSGXWindowEventProducer.o \
	OSGXWindowEventProducerBase.o \
	OSGMouseWheelEventProducer.o \
	OSGMouseMotionEventProducer.o \
	OSGMouseEventProducer.o \
	OSGKeyEvent.o \
	OSGKeyEventProducer.o \
	OSGStringUtils.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
