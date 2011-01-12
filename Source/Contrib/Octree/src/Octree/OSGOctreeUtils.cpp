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
#include "OSGLineChunk.h"
#include "OSGGroup.h"
#include "OSGTransform.h"
#include "OSGDistanceLOD.h"
#include "OSGPhysicsWorld.h"
#include "OSGPhysicsSpace.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

NodeTransitPtr OctreeVisualization::createOctreeVisualization(OctreePtr tree,
                                                              Int32 MaxDepth,
                                                              bool filledGeometry,
                                                              bool onlyLeaf)
{
    OTNodeGeometryCreateFunc GeoCreateFunc;
    OTNodeMaterialCreateFunc MatCreateFunc;    
    OTNodeIsVisibleFunc IsVisibleFunc;

    IsVisibleFunc = boost::bind(&OctreeVisualization::isNodeLeaf,_1, _2,
                                false);

    NodeRecPtr VisRootNode = makeCoredNode<Group>();

    if(filledGeometry)
    {
        NodeRecPtr BaseBox = makeBox(1.0f,1.0f,1.0f,
                                     1,   1,   1);

        GeoCreateFunc = boost::bind(&OctreeVisualization::createNodeDistanceLOD,_1, _2, _3, BaseBox.get(), 10.0f);

        BlendChunkRecPtr DefaultBlendChunk = BlendChunk::create();
        DefaultBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        DefaultBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        PolygonChunkRecPtr    DefaultPolygonChunk = PolygonChunk::create();
        DefaultPolygonChunk->setCullFace(GL_BACK);
        
        MatCreateFunc = boost::bind(&OctreeVisualization::createMatFilled,_1, _2,
                                    Color3f(0.0f,1.0f,0.0f),
                                    Color3f(1.0f,0.0f,0.0f),
                                    0.15f,
                                    DefaultBlendChunk.get(),
                                    DefaultPolygonChunk.get());

        createOctreeVisualizationRec(tree,
                                     tree->getRoot(),
                                     VisRootNode,
                                     osgMin<UInt32>(tree->getDepth(),MaxDepth),
                                     GeoCreateFunc,
                                     MatCreateFunc,
                                     IsVisibleFunc);
    }
    else
    {
        //*******************Create the Geometry for the box
        GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
        //Volume bound box
        type->push_back(GL_LINE_STRIP);
        type->push_back(GL_LINES);

        GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
        //Volume bound box
        lens->push_back(10);
        lens->push_back(6);

        GeoUInt32PropertyRefPtr index = GeoUInt32Property::create();

        //Volume bound box
        index->push_back(0);
        index->push_back(1);
        index->push_back(3);
        index->push_back(2);
        index->push_back(0);
        index->push_back(4);
        index->push_back(5);
        index->push_back(7);
        index->push_back(6);
        index->push_back(4);

        index->push_back(1);
        index->push_back(5);
        index->push_back(2);
        index->push_back(6);
        index->push_back(3);
        index->push_back(7);

        GeoPnt3fPropertyRefPtr highlightPoints = GeoPnt3fProperty::create();
        //Volume bound box
        highlightPoints->push_back(Pnt3f(-1, -1, -1));
        highlightPoints->push_back(Pnt3f( 1, -1, -1));
        highlightPoints->push_back(Pnt3f(-1,  1, -1));
        highlightPoints->push_back(Pnt3f( 1,  1, -1));
        highlightPoints->push_back(Pnt3f(-1, -1,  1));
        highlightPoints->push_back(Pnt3f( 1, -1,  1));
        highlightPoints->push_back(Pnt3f(-1,  1,  1));
        highlightPoints->push_back(Pnt3f( 1,  1,  1));

        //Colors
        Color4f BoundBoxColor(1.0f,1.0f,1.0,1.00f);

        GeoVec4fPropertyRefPtr highlightColors = GeoVec4fProperty::create();
        //Volume bound box
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);
        highlightColors->push_back(BoundBoxColor);

        GeometryRecPtr BoxGeo =Geometry::create();
        BoxGeo->setTypes     (type);
        BoxGeo->setLengths   (lens);
        BoxGeo->setIndices   (index);
        BoxGeo->setPositions (highlightPoints);
        BoxGeo->setColors    (highlightColors);

        //Highlight Bound Box Node
        NodeRecPtr BaseBox = makeNodeFor(BoxGeo);
        GeoCreateFunc =
            boost::bind(&OctreeVisualization::createNodeDistanceLOD,_1, _2, _3,
                        BaseBox.get(), 10.0f);

        //*******************Create the Geometry for the highlight


        BlendChunkRecPtr DefaultBlendChunk = BlendChunk::create();
        DefaultBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        DefaultBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        LineChunkRecPtr    DefaultLineChunk = LineChunk::create();
        DefaultLineChunk->setSmooth(true);

        MatCreateFunc = boost::bind(&OctreeVisualization::createMatLine,_1, _2,
                                    Color3f(1.0f,0.0f,0.0f),
                                    Color3f(0.0f,0.0f,1.0f),
                                    0.55f,
                                    DefaultBlendChunk.get(),
                                    DefaultLineChunk.get());

        createOctreeVisualizationRec(tree,
                                     tree->getRoot(),
                                     VisRootNode,
                                     osgMin<UInt32>(tree->getDepth(),MaxDepth),
                                     GeoCreateFunc,
                                     MatCreateFunc,
                                     IsVisibleFunc);
    }


    return NodeTransitPtr(VisRootNode);
}

void OctreeVisualization::createOctreeVisualizationRec(OctreePtr tree,
                                                       const Octree::OTNodePtr node,
                                                       Node* const VisNode,
                                                       Int32 MaxDepth,
                                                       OTNodeGeometryCreateFunc GeoCreateFunc,
                                                       OTNodeMaterialCreateFunc MatCreateFunc,
                                                       OTNodeIsVisibleFunc IsVisibleFunc)
{
    if(node->getDepth() <= MaxDepth)
    {
        if(IsVisibleFunc(tree, node))
        {
            MaterialRecPtr NodeMat = MatCreateFunc(tree, node);
            NodeRecPtr NewVisNode = GeoCreateFunc(tree, node, NodeMat);
            VisNode->addChild(NewVisNode);
        }

        for(UInt32 i(0) ; i<node->getChildren().size() ; ++i)
        {
            createOctreeVisualizationRec(tree,
                                         node->getChildren(i),
                                         VisNode,
                                         MaxDepth,
                                         GeoCreateFunc,
                                         MatCreateFunc,
                                         IsVisibleFunc);
        }
    }
}

bool OctreeVisualization::isNodeLeaf  (OctreePtr tree,
                                       const Octree::OTNodePtr node,
                                       bool EmptyLeafsVisible)
{
    return node->getChildren().size() == 0 && 
           (EmptyLeafsVisible || node->getContainsObstacles());
}

bool OctreeVisualization::isNodeDepthRange  (OctreePtr tree,
                                             const Octree::OTNodePtr node,
                                             Int32 MinDepth,
                                             Int32 MaxDepth)
{
    return (MinDepth < 0 || node->getDepth() >= MinDepth) &&
           (MaxDepth < 0 || node->getDepth() <= MaxDepth);
}

NodeTransitPtr OctreeVisualization::createNodeGeo(OctreePtr,
                                                  const Octree::OTNodePtr node,
                                                  Material* GeoMaterial,
                                                  const Node* BaseGeo)
{
    //Make the Geoemtry
    NodeRecPtr box = deepCloneTree(BaseGeo);

    dynamic_cast<Geometry*>(box->getCore())->setMaterial(GeoMaterial);

    Matrix m;
    TransformRecPtr box_trans;
    NodeRecPtr trans_node = makeCoredNode<Transform>(&box_trans);
    Pnt3f Center;
    node->getVolume().getCenter(Center);
    m.setTranslate( Center.x(), Center.y(), Center.z());

    const Real32 Offset(0.0f);
    Vec3f Size;
    node->getVolume().getSize(Size);
    m.setScale(Size.x()-(Size.x()*Offset), Size.y()-(Size.y()*Offset), Size.z()-(Size.z()*Offset));
    box_trans->setMatrix(m);
    trans_node->addChild(box);

    return NodeTransitPtr(trans_node);
}

NodeTransitPtr OctreeVisualization::createNodeDistanceLOD(OctreePtr,
                                                          const Octree::OTNodePtr node,
                                                          Material* GeoMaterial,
                                                          const Node* BaseGeo,
                                                          Real32 Range
                                                         )
{
    NodeRecPtr box = deepCloneTree(BaseGeo);
    dynamic_cast<Geometry*>(box->getCore())->setMaterial(GeoMaterial);

    //DistanceLOD node
    DistanceLODRecPtr LOD = DistanceLOD::create();
    LOD->editMFRange()->push_back(10.0);

    NodeRecPtr LODNode = makeNodeFor(LOD);
    LODNode->addChild(box);
    LODNode->addChild(makeCoredNode<Group>());

    Matrix m;
    TransformRecPtr box_trans;
    NodeRecPtr trans_node = makeCoredNode<Transform>(&box_trans);
    Pnt3f Center;
    node->getVolume().getCenter(Center);
    m.setTranslate(Center.x(),
                   Center.y(),
                   Center.z());

    const Real32 Offset(0.0f);
    Vec3f Size;
    node->getVolume().getSize(Size);
    m.setScale(Size.x()-(Size.x()*Offset),
               Size.y()-(Size.y()*Offset),
               Size.z()-(Size.z()*Offset));
    box_trans->setMatrix(m);
    trans_node->addChild(LODNode);

    return NodeTransitPtr(trans_node);
}

MaterialTransitPtr OctreeVisualization::createMatFilled(OctreePtr tree,
                                                        const Octree::OTNodePtr node,
                                                        const Color3f& CoolColor,
                                                        const Color3f& HotColor,
                                                        Real32 Alpha,
                                                        BlendChunk* BaseBlendChunk,
                                                        PolygonChunk* BasePolygonChunk
                                                       )
{
    //Calculate the Color
    //Real32 t = static_cast<Real32>(node->getDepth())/static_cast<Real32>(tree->getDepth());
    //Color3f NodeColor(t*HotColor + (1.0f-t)*CoolColor);
    Color3f NodeColor;
    Color4f NodeColorWithAlpha;
    if(node->getContainsObstacles())
    {
        NodeColor = HotColor;
        NodeColorWithAlpha.setValuesRGBA(NodeColor.red(),NodeColor.green(),NodeColor.blue(),0.55);
    }
    else
    {
        NodeColor = CoolColor;
        NodeColorWithAlpha.setValuesRGBA(NodeColor.red(),NodeColor.green(),NodeColor.blue(),0.05);
    }

    MaterialChunkRecPtr    DefaultMatChunk = MaterialChunk::create();
    DefaultMatChunk->setAmbient(NodeColorWithAlpha);
    DefaultMatChunk->setDiffuse(NodeColorWithAlpha);

    ChunkMaterialRecPtr NodeMat = ChunkMaterial::create();
    NodeMat->setSortKey(1);
    NodeMat->addChunk(BaseBlendChunk);
    NodeMat->addChunk(BasePolygonChunk);
    NodeMat->addChunk(DefaultMatChunk);

    return MaterialTransitPtr(NodeMat);
}

MaterialTransitPtr OctreeVisualization::createMatLine(OctreePtr tree,
                                                      const Octree::OTNodePtr node,
                                                      const Color3f& CoolColor,
                                                      const Color3f& HotColor,
                                                      Real32 Alpha,
                                                      BlendChunk* BaseBlendChunk,
                                                      LineChunk* BaseLineChunk
                                                     )
{
    //Calculate the Color
    Real32 t = static_cast<Real32>(node->getDepth())/static_cast<Real32>(tree->getDepth());
    Color3f NodeColor(t*HotColor + (1.0f-t)*CoolColor);
    Color4f NodeColorWithAlpha(NodeColor.red(),NodeColor.green(),NodeColor.blue(),Alpha);

    MaterialChunkRecPtr    DefaultMatChunk = MaterialChunk::create();
    DefaultMatChunk->setAmbient(NodeColorWithAlpha);
    DefaultMatChunk->setDiffuse(NodeColorWithAlpha);

    ChunkMaterialRecPtr NodeMat = ChunkMaterial::create();
    NodeMat->setSortKey(1);
    NodeMat->addChunk(BaseBlendChunk);
    NodeMat->addChunk(DefaultMatChunk);
    NodeMat->addChunk(BaseLineChunk);

    return MaterialTransitPtr(NodeMat);
}

OSG_END_NAMESPACE
