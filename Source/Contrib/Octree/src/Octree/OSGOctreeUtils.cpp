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

#include "OSGOctreeUtils.h"
#include "OSGSimpleGeometry.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGBlendChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGPhysicsWorld.h"
#include "OSGPhysicsSpace.h"

OSG_BEGIN_NAMESPACE

NodeTransitPtr createOctreeVisualization(const Octree& tree,
                                         Int32 MaxDepth,
                                         const Color3f& CoolColor,
                                         const Color3f& HotColor)
{
    NodeRecPtr VisRootNode = makeCoredNode<Group>();

    NodeRecPtr BaseBox = makeBox(1,1,1, 1,1,1);

    BlendChunkRecPtr DefaultBlendChunk = BlendChunk::create();
    DefaultBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    DefaultBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    PolygonChunkRecPtr    DefaultPolygonChunk = PolygonChunk::create();
    DefaultPolygonChunk->setCullFace(GL_BACK);

    createOctreeVisualizationRec(tree.getRoot(),
                                 VisRootNode,
                                 MaxDepth,
                                 CoolColor,
                                 HotColor,
                                 BaseBox,
                                 DefaultBlendChunk,
                                 DefaultPolygonChunk);

    return NodeTransitPtr(VisRootNode);
}

void createOctreeVisualizationRec(const Octree::OTNodePtr node,
                                  Node* const VisNode,
                                  Int32 MaxDepth,
                                  const Color3f& CoolColor,
                                  const Color3f& HotColor,
                                  const Node* BaseBox,
                                  BlendChunk* BaseBlendChunk,
                                  PolygonChunk* BasePolygonChunk)
{
    if(node->depth <= MaxDepth)
    {
        NodeRecPtr NewVisNode =createOctreeNodeVisualization(node->vol,
                                                             node->depth,
                                                             MaxDepth,
                                                             CoolColor,
                                                             HotColor,
                                                             BaseBox,
                                                             BaseBlendChunk,
                                                             BasePolygonChunk);
        VisNode->addChild(NewVisNode);

        for(UInt32 i(0) ; i<node->children.size() ; ++i)
        {
            createOctreeVisualizationRec(node->children[i],
                                         VisNode,
                                         MaxDepth,
                                         CoolColor,
                                         HotColor,
                                         BaseBox,
                                         BaseBlendChunk,
                                         BasePolygonChunk);
        }
    }
}

NodeTransitPtr createOctreeNodeVisualization(Octree::OTNodeVolume &vol,
                                             UInt32 Depth,
                                             UInt32 MaxDepth,
                                             const Color3f& CoolColor,
                                             const Color3f& HotColor,
                                             const Node* BaseBox,
                                             BlendChunk* BaseBlendChunk,
                                             PolygonChunk* BasePolygonChunk
                                            )
{
    NodeRecPtr box = cloneTree(BaseBox);

    Real32 t = static_cast<Real32>(Depth)/static_cast<Real32>(MaxDepth);
    Color3f NodeColor(t*HotColor + (1.0f-t)*CoolColor);
    Color4f NodeColorWithAlpha(NodeColor.red(),NodeColor.green(),NodeColor.blue(),0.05f);


    MaterialChunkRecPtr    DefaultMatChunk = MaterialChunk::create();
    DefaultMatChunk->setAmbient(NodeColorWithAlpha);
    DefaultMatChunk->setDiffuse(NodeColorWithAlpha);

    ChunkMaterialRecPtr box_mat = ChunkMaterial::create();
    box_mat->addChunk(BaseBlendChunk);
    box_mat->addChunk(BasePolygonChunk);
    box_mat->addChunk(DefaultMatChunk);

    dynamic_cast<Geometry*>(box->getCore())->setMaterial(box_mat);

    Matrix m;
    TransformRecPtr box_trans;
    NodeRecPtr trans_node = makeCoredNode<Transform>(&box_trans);
    m.setTranslate(vol.position.x(), vol.position.y(), vol.position.z());

    const Real32 Offset(0.01f);
    m.setScale(vol.lengths.x()-(vol.lengths.x()*Offset), vol.lengths.y()-(vol.lengths.y()*Offset), vol.lengths.z()-(vol.lengths.z()*Offset));
    box_trans->setMatrix(m);
    trans_node->addChild(box);

    return NodeTransitPtr(trans_node);
}

OSG_END_NAMESPACE
