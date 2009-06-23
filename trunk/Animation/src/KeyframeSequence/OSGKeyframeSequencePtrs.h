/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#ifndef _OSGKEYFRAMEPTRS_H_
#define _OSGKEYFRAMEPTRS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeSequenceBase.h"
#include "OSGKeyframePositionsSequence.h"
#include "OSGKeyframeVectorsSequence.h"
#include "OSGKeyframeRotationsSequence.h"
#include "OSGKeyframeTransformationsSequence.h"
#include "OSGKeyframeColorsSequence.h"
#include "OSGKeyframeNumbersSequence.h"
#include "OSGKeyframeDiscreetSequence.h"
#include "OSGKeyframeFCPtrsSequence.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
typedef KeyframePositionsSequence2s::PtrType  KeyframePositionsSequence2sPtr;
typedef KeyframePositionsSequence2f::PtrType  KeyframePositionsSequence2fPtr;
typedef KeyframePositionsSequence2d::PtrType  KeyframePositionsSequence2dPtr;

typedef KeyframePositionsSequence3s::PtrType  KeyframePositionsSequence3sPtr;
typedef KeyframePositionsSequence3f::PtrType  KeyframePositionsSequence3fPtr;
typedef KeyframePositionsSequence3d::PtrType  KeyframePositionsSequence3dPtr;

typedef KeyframePositionsSequence4s::PtrType  KeyframePositionsSequence4sPtr;
typedef KeyframePositionsSequence4f::PtrType  KeyframePositionsSequence4fPtr;
typedef KeyframePositionsSequence4d::PtrType  KeyframePositionsSequence4dPtr;

//Vectors
typedef KeyframeVectorsSequence2s::PtrType  KeyframeVectorsSequence2sPtr;
typedef KeyframeVectorsSequence2f::PtrType  KeyframeVectorsSequence2fPtr;
typedef KeyframeVectorsSequence2d::PtrType  KeyframeVectorsSequence2dPtr;

typedef KeyframeVectorsSequence3s::PtrType  KeyframeVectorsSequence3sPtr;
typedef KeyframeVectorsSequence3f::PtrType  KeyframeVectorsSequence3fPtr;
typedef KeyframeVectorsSequence3d::PtrType  KeyframeVectorsSequence3dPtr;

typedef KeyframeVectorsSequence4s::PtrType  KeyframeVectorsSequence4sPtr;
typedef KeyframeVectorsSequence4f::PtrType  KeyframeVectorsSequence4fPtr;
typedef KeyframeVectorsSequence4d::PtrType  KeyframeVectorsSequence4dPtr;

//Rotations
typedef KeyframeRotationsSequenceQuat::PtrType  KeyframeRotationsSequenceQuatPtr;

//Transformations
typedef KeyframeTransformationsSequence44f::PtrType  KeyframeTransformationsSequence44fPtr;

//Colors
typedef KeyframeColorsSequence3ub::PtrType  KeyframeTransformationsSequence3ubPtr;
typedef KeyframeColorsSequence3f::PtrType  KeyframeTransformationsSequence3fPtr;
typedef KeyframeColorsSequence4ub::PtrType  KeyframeTransformationsSequence4ubPtr;
typedef KeyframeColorsSequence4f::PtrType  KeyframeTransformationsSequence4fPtr;

//Numbers
//typedef KeyframeNumbersSequenceBool::PtrType  KeyframeNumbersSequenceBoolPtr;
typedef KeyframeNumbersSequenceUInt8::PtrType  KeyframeNumbersSequenceUInt8Ptr;
typedef KeyframeNumbersSequenceUInt16::PtrType  KeyframeNumbersSequenceUInt16Ptr;
typedef KeyframeNumbersSequenceUInt32::PtrType  KeyframeNumbersSequenceUInt32Ptr;
typedef KeyframeNumbersSequenceUInt64::PtrType  KeyframeNumbersSequenceUInt64Ptr;
typedef KeyframeNumbersSequenceInt8::PtrType  KeyframeNumbersSequenceInt8Ptr;
typedef KeyframeNumbersSequenceInt16::PtrType  KeyframeNumbersSequenceInt16Ptr;
typedef KeyframeNumbersSequenceInt32::PtrType  KeyframeNumbersSequenceInt32Ptr;
typedef KeyframeNumbersSequenceInt64::PtrType  KeyframeNumbersSequenceInt64Ptr;
typedef KeyframeNumbersSequenceReal32::PtrType  KeyframeNumbersSequenceReal32Ptr;
typedef KeyframeNumbersSequenceReal64::PtrType  KeyframeNumbersSequenceReal64Ptr;

//Discreet
typedef KeyframeDiscreetSequenceString::PtrType  KeyframeDiscreetSequenceStringPtr;
typedef KeyframeDiscreetSequenceGLenum::PtrType  KeyframeDiscreetSequenceGLenumPtr;

//FCPtrs
typedef KeyframeFCPtrsSequenceTextureChunk::PtrType  KeyframeFCPtrsSequenceTextureChunkPtr;
OSG_END_NAMESPACE

#endif /* _OSGKEYFRAMEPTRS_H_ */
