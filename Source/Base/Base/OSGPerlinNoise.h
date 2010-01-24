/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#ifndef _OPENSG_TOOLBOX_PERLIN_NOISE_H_
#define _OPENSG_TOOLBOX_PERLIN_NOISE_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"
#include <OpenSG/OSGVector.h>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGImage.h>

OSG_BEGIN_NAMESPACE

enum PerlinNoiseInterpolation{PERLIN_INTERPOLATE_LINEAR = 0, PERLIN_INTERPOLATE_QUADRATIC = 2, PERLIN_INTERPOLATE_COSINE = 1};

Real32 OSG_TOOLBOXLIB_DLLMAPPING calcPerlinNoise(Real32 t, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType = PERLIN_INTERPOLATE_COSINE, bool Smoothing = true);

Real32 OSG_TOOLBOXLIB_DLLMAPPING interpolateCosine(Real32 a, Real32 b, Real32 t);

Real32 OSG_TOOLBOXLIB_DLLMAPPING interpolateLinear(Real32 a, Real32 b, Real32 t);

Real32 OSG_TOOLBOXLIB_DLLMAPPING interpolatedNoise(Real32 t, UInt32 octave, UInt32 InterpolationType, bool Smoothing);

Real32 OSG_TOOLBOXLIB_DLLMAPPING getNoise(Int32 t, UInt32 octave);

Real32 OSG_TOOLBOXLIB_DLLMAPPING calcPerlinNoise(const Pnt2f& t, Real32 Amplitude, Real32 Frequency, const Vec2f& Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType = PERLIN_INTERPOLATE_COSINE, bool Smoothing = true);

Real32 OSG_TOOLBOXLIB_DLLMAPPING interpolatedNoise(const Pnt2f& t, UInt32 & octave, UInt32 InterpolationType, bool Smoothing);

Real32 OSG_TOOLBOXLIB_DLLMAPPING smoothNoise(Real32 x, Real32 y, UInt32 & octave);

Real32 OSG_TOOLBOXLIB_DLLMAPPING getNoise(Int32 t1, Int32 t2, UInt32 & octave);

Real32 OSG_TOOLBOXLIB_DLLMAPPING calcPerlinNoise(const Pnt3f& t, Real32 Amplitude, Real32 Frequency, const Vec3f& Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType = PERLIN_INTERPOLATE_COSINE, bool Smoothing = true);

ImagePtr OSG_TOOLBOXLIB_DLLMAPPING createPerlinImage(const Vec2s& Size, const Vec2f& Range, Real32 Amplitude, Real32 Frequency, const Vec2f& Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType = PERLIN_INTERPOLATE_COSINE, bool Smoothing = true, Image::PixelFormat pixelformat = Image::OSG_I_PF, Image::Type  type = Image::OSG_FLOAT32_IMAGEDATA);

Real32 OSG_TOOLBOXLIB_DLLMAPPING interpolatedNoise(const Pnt3f& t, UInt32 & octave, UInt32 InterpolationType, bool Smoothing);

Real32 OSG_TOOLBOXLIB_DLLMAPPING smoothNoise(Real32 x, Real32 y, Real32 z, UInt32 octave);

Real32 OSG_TOOLBOXLIB_DLLMAPPING getNoise(Int32 t1, Int32 t2, Int32 t3, UInt32 octave);

OSG_END_NAMESPACE

#endif


