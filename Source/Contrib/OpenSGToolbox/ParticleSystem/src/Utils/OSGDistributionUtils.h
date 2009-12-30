/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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
#ifndef _OPENSG_PARTICLESYSTEM_UTILS_H_
#define _OPENSG_PARTICLESYSTEM_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"
#include <OpenSG/OSGBaseTypes.h>
#include <vector>

OSG_BEGIN_NAMESPACE


UInt32 OSG_PARTICLESYSTEMLIB_DLLMAPPING stlBinarySearch(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value);
UInt32 OSG_PARTICLESYSTEMLIB_DLLMAPPING stlLowerBound(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value);

OSG_END_NAMESPACE

#endif
