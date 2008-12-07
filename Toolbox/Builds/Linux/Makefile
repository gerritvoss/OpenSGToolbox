###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Types:$(srcdir)/Util:$(srcdir)/FileIO:$(srcdir)/Attachments:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -I$(srcdir) -I$(BOOST_BASE_DIR)/include
EXTRA_LDFLAGS = -L$(BOOST_BASE_DIR) -lboost_filesystem -lboost_system

OBJECTS = OSGFieldContainerMapType.o \
	OSGStringMapType.o \
	OSGPathType.o \
	OSGRandomPoolManager.o \
	OSGGLenumUtils.o \
	OSGIntrusivePtrImplBase.o \
	OSGCameraUtils.o \
	OSGStringUtils.o \
	OSGMathUtils.o \
	OSGTextureUtils.o \
	OSGFCFileHandler.o \
	OSGFCFileType.o \
	OSGXMLFCFileType.o \
	OSGBinFCFileType.o \
	OSGFilePathAttachment.o \
	OSGFilePathAttachmentBase.o
        
        
include $(commondir)/CommonMake.mk
