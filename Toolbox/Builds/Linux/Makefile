###

LIB_NAME = OSGToolbox
LIB_INCLUDE_DIR_NAME = Toolbox

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Types:$(srcdir)/FileIO:$(srcdir)/Attachments:$(srcdir)/Util:


#.SUFFIX = .cpp .o

EXTRA_CCFLAGS = -fPIC -I$(srcdir) -I$(BOOST_BASE_DIR)/include
EXTRA_LDFLAGS = 

OBJECTS = OSGFieldContainerMapType.o \
	OSGStringMapType.o \
	OSGPathType.o \
	OSGFCFileHandler.o \
	OSGFCFileType.o \
	OSGXMLFCFileType.o \
	OSGBinFCFileType.o \
	OSGFilePathAttachmentBase.o \
	OSGFilePathAttachment.o \
	OSGStringUtils.o \
	OSGIntrusivePtrImplBase.o \
	OSGRandomPoolManager.o \
	OSGFieldContainerUtils.o \
	OSGGLenumUtils.o \
	OSGCameraUtils.o \
	OSGMathUtils.o \
	OSGTextureUtils.o
        
        
include $(commondir)/CommonMake.mk
