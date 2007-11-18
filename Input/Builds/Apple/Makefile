###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Apple
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Event:$(srcdir)/Utils:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/CoreGL:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/QT4:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/X:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGEventFactory.o \
	OSGEventType.o \
	OSGFieldChangeEvent.o \
	OSGFieldChangeListener.o \
	OSGKeyAdapter.o \
	OSGKeyEvent.o \
	OSGKeyEventProducer.o \
	OSGMouseAdapter.o \
	OSGMouseEvent.o \
	OSGMouseEventProducer.o \
	OSGMouseMotionAdapter.o \
	OSGMouseMotionEventProducer.o \
	OSGMouseWheelEvent.o \
	OSGMouseWheelEventProducer.o \
	OSGUpdateEvent.o \
	OSGWindowAdapter.o \
	OSGWindowEvent.o \
	OSGStringUtils.o \
	OSGWindowEventProducer.o \
	OSGWindowEventProducerBase.o \
	OSGWindowEventProducerFactory.o \
	OSGWindowUtils.o \
	OSGCarbonWindowEventProducer.o \
	OSGCarbonWindowEventProducerBase.o \
	OSGGLUTWindowEventProducer.o \
	OSGGLUTWindowEventProducerBase.o \
	OSGWin32WindowEventProducer.o \
	OSGWin32WindowEventProducerBase.o \
	OSGXWindowEventProducer.o \
	OSGXWindowEventProducerBase.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
