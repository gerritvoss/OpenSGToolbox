###

LIB_NAME = OSGDynamics
LIB_INCLUDE_DIR_NAME = Dynamics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Distributions:$(srcdir)/Distributions/1D:$(srcdir)/Distributions/2D:$(srcdir)/Distributions/3D:$(srcdir)/Function:$(srcdir)/Function/Conversion:$(srcdir)/Constants:$(srcdir)/Utils:$(srcdir)/BooleanOperations:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include -I$(BOOST_BASE_DIR)/include

OBJECTS = OSGSegmentDistribution1D.o \
	OSGSegmentSetDistribution1DBase.o \
	OSGSegmentSetDistribution1D.o \
	OSGGaussianNormalDistribution1DBase.o \
	OSGGaussianNormalDistribution1D.o \
	OSGSegmentDistribution1DBase.o \
	OSGGaussianNormalDistribution2DBase.o \
	OSGLineDistribution2DBase.o \
	OSGDiscDistribution2D.o \
	OSGQuadDistribution2DBase.o \
	OSGTriDistribution2DBase.o \
	OSGDiscDistribution2DBase.o \
	OSGGaussianNormalDistribution2D.o \
	OSGLineDistribution2D.o \
	OSGQuadDistribution2D.o \
	OSGTriDistribution2D.o \
	OSGCylinderDistribution3D.o \
	OSGBoxDistribution3DBase.o \
	OSGGaussianNormalDistribution3D.o \
	OSGLineDistribution3D.o \
	OSGGeoVolumeDistribution3DBase.o \
	OSGTriDistribution3D.o \
	OSGSphereDistribution3DBase.o \
	OSGBoxDistribution3D.o \
	OSGGeoVolumeDistribution3D.o \
	OSGDiscDistribution3DBase.o \
	OSGGeoSurfaceDistribution3DBase.o \
	OSGSphereDistribution3D.o \
	OSGCylinderDistribution3DBase.o \
	OSGGaussianNormalDistribution3DBase.o \
	OSGLineDistribution3DBase.o \
	OSGDiscDistribution3D.o \
	OSGGeoSurfaceDistribution3D.o \
	OSGTriDistribution3DBase.o \
	OSGFunction.o \
	OSGCompoundFunctionBase.o \
	OSGCompoundFunction.o \
	OSGFunctionFactory.o \
	OSGFunctionBase.o \
	OSGFunctionConnections.o \
	OSGFunctionConnectionsBase.o \
	OSGDataCombiner.o \
	OSGDataSplitterBase.o \
	OSGDataConverterBase.o \
	OSGDataSplitter.o \
	OSGDataConverter.o \
	OSGDataCombinerBase.o \
	OSGReal32ConstantFunctionBase.o \
	OSGPnt2fConstantFunctionBase.o \
	OSGPnt3fConstantFunctionBase.o \
	OSGReal32ConstantFunction.o \
	OSGPnt2fConstantFunction.o \
	OSGPnt3fConstantFunction.o \
	OSGDynamicsUtils.o \
	OSGBooleanFunction.o \
	OSGBooleanFunctionBase.o
        
        
include $(commondir)/CommonMake.mk
