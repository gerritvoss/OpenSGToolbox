###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/CoreGL:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/X:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/QT4:$(srcdir)/Event:$(srcdir)/Utils:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGWindowEventProducer.o \
	OSGWindowEventProducerBase.o \
	OSGWindowUtils.o \
	OSGWindowEventProducerFactory.o \
	OSGGLUTWindowEventProducer.o \
	OSGGLUTWindowEventProducerBase.o \
	OSGWin32WindowEventProducer.o \
	OSGWin32WindowEventProducerBase.o \
	OSGXWindowEventProducer.o \
	OSGXWindowEventProducerBase.o \
	OSGCarbonWindowEventProducerBase.o \
	OSGCarbonWindowEventProducer.o \
	OSGWindowEvent.o \
	OSGMouseWheelEventProducer.o \
	OSGMouseMotionEventProducer.o \
	OSGWindowAdapter.o \
	OSGFieldChangeEvent.o \
	OSGMouseEvent.o \
	OSGMouseEventProducer.o \
	OSGEventFactory.o \
	OSGKeyAdapter.o \
	OSGMouseMotionAdapter.o \
	OSGUpdateEvent.o \
	OSGFieldChangeListener.o \
	OSGMouseAdapter.o \
	OSGKeyEvent.o \
	OSGKeyEventProducer.o \
	OSGMouseWheelEvent.o \
	OSGEventType.o \
	OSGStringUtils.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
