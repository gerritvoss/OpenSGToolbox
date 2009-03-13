###

LIB_NAME = OSGAnimation
LIB_INCLUDE_DIR_NAME = Animation

srcdir = ../../../src
installdir = ../../../../Builds/Linux
commondir = ../../../../Builds/Common
VPATH = $(srcdir)/:$(srcdir)/Animations:$(srcdir)/Animations/Advancers:$(srcdir)/Events:$(srcdir)/SkeletalAnimation:$(srcdir)/Interpolation:$(srcdir)/GeometryAnimation:$(srcdir)/KeyframeSequence:$(srcdir)/KeyframeSequence/GeometryKeyframeSequences:$(srcdir)/Animators:$(srcdir)/Util:


#.SUFFIX = .o .o

EXTRA_CCFLAGS = -I$(srcdir) -I$(installdir)/include

OBJECTS = OSGGeometryAnimationBase.o \
	OSGShaderAnimation.o \
	OSGAnimationBase.o \
	OSGFieldAnimation.o \
	OSGGeometryAnimation.o \
	OSGShaderAnimationBase.o \
	OSGFieldAnimationBase.o \
	OSGAnimation.o \
	OSGFieldAnimationAdvancer.o \
	OSGConstantAnimationAdvancer.o \
	OSGElapsedTimeAnimationAdvancerBase.o \
	OSGFieldAnimationAdvancerBase.o \
	OSGAnimationAdvancer.o \
	OSGConstantAnimationAdvancerBase.o \
	OSGElapsedTimeAnimationAdvancer.o \
	OSGAnimationAdvancerBase.o \
	OSGAnimationEvent.o \
	OSGHingedBoneBase.o \
	OSGBoneBase.o \
	OSGSkeletonBlendedGeometryBase.o \
	OSGSkeletonAnimation.o \
	OSGSkeletonBase.o \
	OSGSkeletonDrawable.o \
	OSGHingedBone.o \
	OSGBone.o \
	OSGSkeletonBlendedGeometry.o \
	OSGSkeletonAnimationBase.o \
	OSGSkeletonDrawableBase.o \
	OSGSkeleton.o \
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
	OSGKeyframeSequence.o \
	OSGKeyframeRotationsSequence.o \
	OSGKeyframePositionsSequence.o \
	OSGKeyframeTransformationsSequence.o \
	OSGKeyframeColorsSequence.o \
	OSGKeyframeSequenceTmplFields.o \
	OSGKeyframeSequenceBase.o \
	OSGKeyframeNumbersSequence.o \
	OSGKeyframeVectorsSequence.o \
	OSGKeyframeFCPtrsSequence.o \
	OSGKeyframeDiscreetSequence.o \
	OSGKeyframeSequenceTmplBase.o \
	OSGKeyframeSequenceGeoColorsPtrBase.o \
	OSGKeyframeSequenceGeoTexCoordsPtrBase.o \
	OSGKeyframeSequenceGeoTexCoordsPtr.o \
	OSGKeyframeSequenceGeoNormalsPtr.o \
	OSGKeyframeSequenceGeoPositionsPtr.o \
	OSGKeyframeSequenceGeoColorsPtr.o \
	OSGKeyframeSequenceGeoNormalsPtrBase.o \
	OSGKeyframeSequenceGeoPositionsPtrBase.o \
	OSGKeyframeAnimatorBase.o \
	OSGKeyframeAnimator.o \
	OSGAnimatorBase.o \
	OSGAnimator.o \
	OSGGeoPropertyOperations.o
        
        
include $(commondir)/CommonMake.mk
