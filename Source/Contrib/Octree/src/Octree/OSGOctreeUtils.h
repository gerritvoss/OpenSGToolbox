/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  PJ Campbell(pjcamp@iastate.edu),                              *
 *             David Kabala (djkabala@gmail.com)                             *
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
#ifndef _OSGOCTREEUTILS_H_
#define _OSGOCTREEUTILS_H_
#ifdef __sgi
#pragma once
#endif

// Headers
#include "OSGConfig.h"
#include "OSGContribOctreeDef.h"

#include "OSGOctree.h"
#include "OSGBlendChunkFields.h"
#include "OSGPolygonChunkFields.h"
#include "OSGGeometryFields.h"

OSG_BEGIN_NAMESPACE

NodeTransitPtr OSG_CONTRIBOCTREE_DLLMAPPING createOctreeVisualization(const Octree& tree,
                                                                      Int32 MaxDepth,
                                                                      const Color3f& CoolColor = Color3f(0.0f,0.0f,1.0f),
                                                                      const Color3f& HotColor = Color3f(1.0f,0.0f,0.0f));

void OSG_CONTRIBOCTREE_DLLMAPPING createOctreeVisualizationRec(const Octree::OTNodePtr node,
                                                               Node* const VisNode,
                                                               Int32 MaxDepth,
                                                               const Color3f& CoolColor,
                                                               const Color3f& HotColor,
                                                               const Node* BaseBox,
                                                               BlendChunk* BaseBlendChunk,
                                                               PolygonChunk* BasePolygonChunk);

NodeTransitPtr OSG_CONTRIBOCTREE_DLLMAPPING
createOctreeNodeVisualization(Octree::OTNodeVolume &vol,
                              UInt32 Depth,
                              UInt32 MaxDepth,
                              const Color3f& CoolColor,
                              const Color3f& HotColor,
                              const Node* BaseBox,
                              BlendChunk* BaseBlendChunk,
                              PolygonChunk* BasePolygonChunk
                             );

OSG_END_NAMESPACE

#endif /* _OSGOCTREEUTILS_H_ */
