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
#include "OSGMaterialFields.h"
#include "OSGLineChunkFields.h"

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBOCTREE_DLLMAPPING OctreeVisualization
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef boost::function<NodeTransitPtr (OctreePtr, const Octree::OTNodePtr, Material*)> OTNodeGeometryCreateFunc;
    typedef boost::function<MaterialTransitPtr (OctreePtr, const Octree::OTNodePtr)> OTNodeMaterialCreateFunc;
    typedef boost::function<bool           (OctreePtr, const Octree::OTNodePtr)> OTNodeIsVisibleFunc;

    //Methods for visualizing octrees
    //
    //Methods for drawing nodes
    //Render each node as a box
    //Render each node as a the bounding box lines
    //
    //Methods for choosing which nodes to draw
    //Render only the leaf nodes
    //Render only the nodes of depth i...j
    //Use LOD Nodes to draw only nodes a specific distance from the view
    //
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */
    static NodeTransitPtr createOctreeVisualization(OctreePtr tree,
                                                    Int32 MaxDepth,
                                                    //Render as Filled box or lined box
                                                    bool filledGeometry = true,
                                                    //Which nodes to draw: OnlyLeaf, NodeDepthRange, LOD
                                                    bool onlyLeaf = true);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Create Node Queries                         */
    /*! \{                                                                 */
    static bool isNodeLeaf  (OctreePtr,
                             const Octree::OTNodePtr,
                             bool EmptyLeavesVisible);

    static bool isNodeDepthRange  (OctreePtr,
                                   const Octree::OTNodePtr,
                                   Int32 MinDepth,
                                   Int32 MaxDepth);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Node Creation                              */
    /*! \{                                                                 */
    static NodeTransitPtr createNodeGeo(OctreePtr,
                                        const Octree::OTNodePtr,
                                        Material*,
                                        const Node* BaseGeo);

    static NodeTransitPtr createNodeDistanceLOD(OctreePtr,
                                                const Octree::OTNodePtr,
                                                Material*,
                                                const Node* BaseGeo,
                                                Real32 Range
                                               );
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Material Creation                         */
    /*! \{                                                                 */
    static MaterialTransitPtr createMatFilled(OctreePtr,
                                              const Octree::OTNodePtr,
                                              const Color3f& CoolColor,
                                              const Color3f& HotColor,
                                              Real32 Alpha,
                                              BlendChunk* BaseBlendChunk,
                                              PolygonChunk* BasePolygonChunk
                                             );

    static MaterialTransitPtr createMatLine(OctreePtr,
                                            const Octree::OTNodePtr,
                                            const Color3f& CoolColor,
                                            const Color3f& HotColor,
                                            Real32 Alpha,
                                            BlendChunk* BaseBlendChunk,
                                            LineChunk* BaseLineChunk
                                           );
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*=========================  PRIVATE  =================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                  Recursive Func                              */
    /*! \{                                                                 */
    static void createOctreeVisualizationRec(OctreePtr tree,
                                             const Octree::OTNodePtr node,
                                             Node* const VisNode,
                                             Int32 MaxDepth,
                                             OTNodeGeometryCreateFunc GeoCreateFunc,
                                             OTNodeMaterialCreateFunc MatCreateFunc,
                                             OTNodeIsVisibleFunc IsVisibleFunc);
    /*! \}                                                                 */
};
OSG_END_NAMESPACE

#endif /* _OSGOCTREEUTILS_H_ */
