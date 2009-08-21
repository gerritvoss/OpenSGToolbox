/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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
#ifndef _OPENSG_TOOLBOX_MATERIALS_H_
#define _OPENSG_TOOLBOX_MATERIALS_H_

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGCubeTextureChunk.h>
#include <OpenSG/OSGMaterial.h>
#include "OSGMaterialLibrary.h"

OSG_BEGIN_NAMESPACE

CubeTextureChunkPtr createCubeTextureChunk(void);

// Gooch shader material
MaterialPtr OSG_TOOLBOXLIB_DLLMAPPING createGoochMaterial(Vec4f WarmColor = Vec3f(0.6f,0.6f,0.0f,1.0f), 
														  Vec4f CoolColor = Vec3f(0.0f,0.0f,0.6f,1.0f), 
														  Vec4f SurfaceColor = Vec4f(0.75f,0.75f,0.75f,1.0f), 
														  Real32 DiffuseWarm = 0.45f, 
													      Real32 DiffuseCool = 0.45f, 
														  Real32 OutlineWidth = 3.5f);

std::string createSHLVertexProgGooch(void);
std::string createSHLFragProgGooch(void);

// Black outlining material
MaterialPtr OSG_TOOLBOXLIB_DLLMAPPING createBlackOutlineMaterial(Real32 OutlineWidth = 3.5f);
std::string createSHLVertexProgBlack(void); 
std::string createSHKFragProgBlack(void);

// Simple Glass material (No refraction, only reflection)
MaterialPtr OSG_TOOLBOXLIB_DLLMAPPING createSimpleGlassMaterial(Real32 Rainbowiness = 0.5f, 
																CubeTextureChunkPtr Environment = createCubeTextureChunk());
std::string createSimpleGlassVertexProg(void);
std::string createSimpleGlassFragProg(void);

// Complex Glass material (Reflection, refraction, and chromatic abberation)
MaterialPtr OSG_TOOLBOXLIB_DLLMAPPING createComplexGlassMaterial(Real32 IndexOfRefractionRatio = 0.65, 
															     Vec3f IORDisplacements = Vec3f(-0.02f,0.0f,0.02f), 
															     Real32 FresnelPower = 5.0f, 
															     bool ChromaticAbberation = true,
															     CubeTextureChunkPtr Environment = createCubeTextureChunk());

std::string createComplexGlassVertexProg(void);
std::string createComplexGlassFragProg(void);

OSG_END_NAMESPACE

#endif