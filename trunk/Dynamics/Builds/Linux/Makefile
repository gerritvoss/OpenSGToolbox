###

LIB_NAME = OSGDynamics
LIB_INCLUDE_DIR_NAME = Dynamics

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Utils:$(srcdir)/Distributions:$(srcdir)/Distributions/1D:$(srcdir)/Distributions/2D:$(srcdir)/Distributions/3D:$(srcdir)/BooleanOperations:$(srcdir)/Function:$(srcdir)/Function/Conversion:$(srcdir)/Constants:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I../../../../Builds/Linux/include -I$(BOOST_BASE_DIR)/include

OBJECTS = OSGDynamicsUtils.o \
	OSGSegmentDistribution1D.o \
	OSGGaussianNormalDistribution1DBase.o \
	OSGSegmentSetDistribution1DBase.o \
	OSGSegmentSetDistribution1D.o \
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
	OSGBoxDistribution3DBase.o \
	OSGCylinderDistribution3D.o \
	OSGGaussianNormalDistribution3D.o \
	OSGGeoVolumeDistribution3DBase.o \
	OSGLineDistribution3D.o \
	OSGTriDistribution3D.o \
	OSGSphereDistribution3DBase.o \
	OSGBoxDistribution3D.o \
	OSGGeoVolumeDistribution3D.o \
	OSGDiscDistribution3DBase.o \
	OSGGeoSurfaceDistribution3DBase.o \
	OSGSphereDistribution3D.o \
	OSGCylinderDistribution3DBase.o \
	OSGGaussianNormalDistribution3DBase.o \
	OSGDiscDistribution3D.o \
	OSGLineDistribution3DBase.o \
	OSGGeoSurfaceDistribution3D.o \
	OSGTriDistribution3DBase.o \
	OSGConeDistribution3DBase.o \
	OSGConeDistribution3D.o \
	OSGBooleanFunctionBase.o \
	OSGBooleanFunction.o \
	OSGFunctionConnectionsBase.o \
	OSGCompoundFunctionBase.o \
	OSGFunction.o \
	OSGFunctionConnections.o \
	OSGCompoundFunction.o \
	OSGFunctionFactory.o \
	OSGFunctionBase.o \
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
	OSGPnt3fConstantFunction.o
        
        
include $(commondir)/CommonMake.mk
