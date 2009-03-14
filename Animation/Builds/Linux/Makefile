###

LIB_NAME = OSGAnimation
LIB_INCLUDE_DIR_NAME = Animation

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Animations:$(srcdir)/Animations/Advancers:$(srcdir)/Interpolation:$(srcdir)/GeometryAnimation:$(srcdir)/KeyframeSequence:$(srcdir)/KeyframeSequence/GeometryKeyframeSequences:$(srcdir)/Animators:$(srcdir)/Util:$(srcdir)/SkeletalAnimation:$(srcdir)/Events:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I$(installdir)/include -fPIC

OBJECTS = OSGShaderAnimation.o \
	OSGAnimationBase.o \
	OSGFieldAnimation.o \
	OSGShaderAnimationBase.o \
	OSGFieldAnimationBase.o \
	OSGAnimation.o \
	OSGFieldAnimationAdvancer.o \
	OSGElapsedTimeAnimationAdvancerBase.o \
	OSGConstantAnimationAdvancer.o \
	OSGFieldAnimationAdvancerBase.o \
	OSGAnimationAdvancer.o \
	OSGConstantAnimationAdvancerBase.o \
	OSGElapsedTimeAnimationAdvancer.o \
	OSGAnimationAdvancerBase.o \
	OSGGeometryInterpolations.o \
	OSGMFieldInterpolations.o \
	OSGKeyframeInterpolations.o \
	OSGInterpolationFactory.o \
	OSGGeoPositionDifferenceSet.o \
	OSGGeoColorDifferenceSetBase.o \
	OSGBlendGeometryBase.o \
	OSGGeoDifferenceSet.o \
	OSGGeoNormalDifferenceSetBase.o \
	OSGGeoTexCoordDifferenceSet.o \
	OSGGeoPositionDifferenceSetBase.o \
	OSGGeoDifferenceSetBase.o \
	OSGBlendGeometry.o \
	OSGGeoColorDifferenceSet.o \
	OSGGeoTexCoordDifferenceSetBase.o \
	OSGGeoNormalDifferenceSet.o \
	OSGKeyframeRotationsSequence.o \
	OSGKeyframePositionsSequence.o \
	OSGKeyframeTransformationsSequence.o \
	OSGKeyframeColorsSequence.o \
	OSGKeyframeSequenceTmplFields.o \
	OSGKeyframeNumbersSequence.o \
	OSGKeyframeSequenceBase.o \
	OSGKeyframeVectorsSequence.o \
	OSGKeyframeFCPtrsSequence.o \
	OSGKeyframeDiscreetSequence.o \
	OSGKeyframeSequenceTmplBase.o \
	OSGKeyframeSequence.o \
	OSGKeyframeSequenceGeoColorsPtrBase.o \
	OSGKeyframeSequenceGeoTexCoordsPtr.o \
	OSGKeyframeSequenceGeoNormalsPtr.o \
	OSGKeyframeSequenceGeoPositionsPtr.o \
	OSGKeyframeSequenceGeoColorsPtr.o \
	OSGKeyframeSequenceGeoTexCoordsPtrBase.o \
	OSGKeyframeSequenceGeoNormalsPtrBase.o \
	OSGKeyframeSequenceGeoPositionsPtrBase.o \
	OSGKeyframeAnimatorBase.o \
	OSGKeyframeAnimator.o \
	OSGAnimatorBase.o \
	OSGAnimator.o \
	OSGGeoPropertyOperations.o \
	OSGSkeletonDrawable.o \
	OSGBoneBase.o \
	OSGSkeletonBase.o \
	OSGSkeletonDrawableBase.o \
	OSGBone.o \
	OSGSkeleton.o \
	OSGHingedBoneBase.o \
	OSGSkeletonBlendedGeometryBase.o \
	OSGSkeletonAnimation.o \
	OSGHingedBone.o \
	OSGSkeletonBlendedGeometry.o \
	OSGSkeletonAnimationBase.o \
	OSGAnimationEvent.o
        
        
include $(commondir)/CommonMake.mk
