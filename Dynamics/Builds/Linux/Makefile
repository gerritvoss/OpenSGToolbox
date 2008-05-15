###

LIB_NAME = OSGDynamics
LIB_INCLUDE_DIR_NAME = Dynamics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Distributions:$(srcdir)/Distributions/2D:$(srcdir)/Distributions/3D:$(srcdir)/Distributions/1D:$(srcdir)/Function:$(srcdir)/Function/Conversion:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include -I../../../../External/Boost

OBJECTS = OSGTriDistribution2D.o \
	OSGQuadDistribution2DBase.o \
	OSGTriDistribution2DBase.o \
	OSGGaussianNormalDistribution2DBase.o \
	OSGGaussianNormalDistribution2D.o \
	OSGLineDistribution2DBase.o \
	OSGLineDistribution2D.o \
	OSGDiscDistribution2D.o \
	OSGDiscDistribution2DBase.o \
	OSGQuadDistribution2D.o \
	OSGBoxDistribution3DBase.o \
	OSGGeoVolumeDistribution3DBase.o \
	OSGDiscDistribution3DBase.o \
	OSGCylinderDistribution3DBase.o \
	OSGGeoVolumeDistribution3D.o \
	OSGCylinderDistribution3D.o \
	OSGLineDistribution3D.o \
	OSGSphereDistribution3D.o \
	OSGSphereDistribution3DBase.o \
	OSGGaussianNormalDistribution3DBase.o \
	OSGTriDistribution3D.o \
	OSGGaussianNormalDistribution3D.o \
	OSGLineDistribution3DBase.o \
	OSGDiscDistribution3D.o \
	OSGGeoSurfaceDistribution3D.o \
	OSGBoxDistribution3D.o \
	OSGTriDistribution3DBase.o \
	OSGGeoSurfaceDistribution3DBase.o \
	OSGGaussianNormalDistribution1DBase.o \
	OSGSegmentDistribution1D.o \
	OSGSegmentSetDistribution1D.o \
	OSGSegmentSetDistribution1DBase.o \
	OSGSegmentDistribution1DBase.o \
	OSGGaussianNormalDistribution1D.o \
	OSGCompoundFunction.o \
	OSGFunction.o \
	OSGFunctionFactory.o \
	OSGFunctionBase.o \
	OSGCompoundFunctionBase.o \
	OSGDataConverterBase.o \
	OSGDataCombiner.o \
	OSGDataCombinerBase.o \
	OSGDataSplitterBase.o \
	OSGDataConverter.o \
	OSGDataSplitter.o
        
        
include $(commondir)/CommonMake.mk
