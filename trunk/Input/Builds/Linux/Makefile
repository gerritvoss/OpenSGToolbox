###

LIB_NAME = OSGInput
LIB_INCLUDE_DIR_NAME = Input

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Utils:$(srcdir)/Event:$(srcdir)/WindowSystem:$(srcdir)/WindowSystem/QT:$(srcdir)/WindowSystem/Cocoa:$(srcdir)/WindowSystem/Win32:$(srcdir)/WindowSystem/Carbon:$(srcdir)/WindowSystem/X:$(srcdir)/WindowSystem/QT4:$(srcdir)/WindowSystem/GLUT:$(srcdir)/WindowSystem/CoreGL:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -fPIC -I$(srcdir)  -I../../../../Builds/Linux/include -I$(BOOST_BASE_DIR)/include

OBJECTS = OSGStringUtils.o \
	OSGMouseAdapter.o \
	OSGKeyAdapter.o \
	OSGMouseEventProducer.o \
	OSGKeyEventProducer.o \
	OSGEventConnection.o \
	OSGWindowEvent.o \
	OSGMouseWheelEvent.o \
	OSGKeyEvent.o \
	OSGFieldChangeEvent.o \
	OSGMouseEvent.o \
	OSGFieldChangeListener.o \
	OSGInputEvent.o \
	OSGMouseMotionAdapter.o \
	OSGWindowAdapter.o \
	OSGEventFactory.o \
	OSGEventType.o \
	OSGMouseWheelEventProducer.o \
	OSGMouseMotionEventProducer.o \
	OSGUpdateEvent.o \
	OSGWindowUtils.o \
	OSGWindowEventProducerFactory.o \
	OSGWindowEventProducerBase.o \
	OSGWindowEventProducer.o \
	OSGXWindowEventProducer.o \
	OSGXWindowEventProducerBase.o \
	OSGInputSettings.o
        
        
include $(commondir)/CommonMake.mk
