###

LIB_NAME = OSGDynamics
LIB_INCLUDE_DIR_NAME = Dynamics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Distributions:$(srcdir)/Distributions/1D:$(srcdir)/Distributions/2D:$(srcdir)/Distributions/3D:$(srcdir)/Function:$(srcdir)/Function/Conversion:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir)

OBJECTS = OSGGaussianNormalDistribution1D.o \
	OSGGaussianNormalDistribution1DBase.o \
	OSGSegmentDistribution1D.o \
	OSGSegmentDistribution1DBase.o \
	OSGSegmentSetDistribution1D.o \
	OSGSegmentSetDistribution1DBase.o \
	OSGDiscDistribution2D.o \
	OSGDiscDistribution2DBase.o \
	OSGGaussianNormalDistribution2D.o \
	OSGGaussianNormalDistribution2DBase.o \
	OSGLineDistribution2D.o \
	OSGLineDistribution2DBase.o \
	OSGQuadDistribution2D.o \
	OSGQuadDistribution2DBase.o \
	OSGTriDistribution2D.o \
	OSGTriDistribution2DBase.o \
	OSGBoxDistribution3D.o \
	OSGBoxDistribution3DBase.o \
	OSGCylinderDistribution3D.o \
	OSGCylinderDistribution3DBase.o \
	OSGDiscDistribution3D.o \
	OSGDiscDistribution3DBase.o \
	OSGGaussianNormalDistribution3D.o \
	OSGGaussianNormalDistribution3DBase.o \
	OSGGeoSurfaceDistribution3D.o \
	OSGGeoSurfaceDistribution3DBase.o \
	OSGGeoVolumeDistribution3D.o \
	OSGGeoVolumeDistribution3DBase.o \
	OSGLineDistribution3D.o \
	OSGLineDistribution3DBase.o \
	OSGSphereDistribution3D.o \
	OSGSphereDistribution3DBase.o \
	OSGTriDistribution3D.o \
	OSGTriDistribution3DBase.o \
	OSGFunction.o \
	OSGFunctionBase.o \
	OSGFunctionFactory.o \
	OSGDataCombiner.o \
	OSGDataCombinerBase.o \
	OSGDataSplitter.o \
	OSGDataSplitterBase.o
        
        
include $(commondir)/CommonMake.mk
