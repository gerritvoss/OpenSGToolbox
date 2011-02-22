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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGOctree.h"
#include "OSGGraphOpFactory.h"
#include "OSGGeometry.h"

//Physics
#include "OSGPhysicsHashSpace.h"
#include "OSGPhysicsWorld.h"
#include "OSGPhysicsBoxGeom.h"
#include "OSGPhysicsTriMeshGeom.h"
#include "OSGCollisionEventDetails.h"

/*!\class OSG::Octree
 *
 * \brief Class for constructing a subdivision of a geometric space in an Octree
 * hierarchy.
 *
 * From <a href="http://en.wikipedia.org/wiki/Octree">Wikipedia</a>:
 *
 * An octree is a tree data structure in which each internal node has exactly
 * eight children. Octrees are most often used to partition a three dimensional
 * space by recursively subdividing it into eight octants. Octrees are the
 * three-dimensional analog of quadtrees.
 *
 * \b Examples:
 *
 *  - \example_link{01OctreeConstruction, Octree construction and visualization}
 *
 */
/*!\fn OctreePtr Octree::buildTree(Node* const RootNode,
                    UInt32 TravMask,
                    UInt32 MaxDepth,
                    Real32 MinSideLength = 0.0f,
                    bool uniformSideLengths = true)
 * \brief Construct an octree using the given geometry.
 *
 * Depending on the complexity of the scene-graph node given, traversal mask,
 * and the max depth, this function may take a considerable amount of time to
 * complete.
 *
 * \param[in] RootNode The scene graph node containing the geometry to subdivide
 * \param[in] TravMask The traversal mask to use when determining if nodes are
 * intersectable
 * \param[in] MaxDepth The maximum depth of the tree
 * \param[in] MinSideLength The minimum length of the root Octree node
 * \param[in] uniformSideLengths If true, all of the 3-sides of octree nodes
 * will be the same length.
 *
 * \returns A pointer to the newly created octree
 */

/*!\fn OTNodePtr Octree::getRoot(void) const
 * \brief Get the root node of this Octree
 */

/*!\fn OTNodePtr Octree::getNodeThatContains(const Pnt3f Location) const
 * \brief Get the octree node that contains the given location
 *
 * \param[in] Location The location to look for
 *
 * \returns The Octree node that contains the given location.  Returns NULL if
 * the location is not contained
 */

/*!\fn UInt32 Octree::getDepth(void) const
 * \brief Get the maximum depth of the Octree
 */

/*!\fn UInt32 Octree::getNodeCount(void) const
 * \brief Get the number of nodes in the Octree
 */

/*!\fn UInt32 Octree::getLeafNodeCount(void) const
 * \brief Get the number of leaf nodes.
 *
 * Leaf nodes are nodes that do not contain any children nodes.
 */

/*!\fn UInt32 Octree::getBranchNodeCount(void) const
 * \brief Geth the number of branch nodes.
 *
 * Branch nodes are nodes that contain children nodes.
 */

/*!\fn UInt32 Octree::getIntersectingNodeCount(void) const
 * \brief Get the number of nodes that intersect with the geometry.
 */

/*!\fn UInt32 Octree::getIntersectingLeafNodeCount(void) const
 * \brief Get the number of leaf nodes that intersect with the geometry
 *
 * Leaf nodes are nodes that do not contain any children nodes.
 */


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundBase.cpp file.
// To modify it, please change the .fcd file (OSGSound.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

OctreePtr Octree::buildTree(Node* const RootNode,
                                   UInt32 TravMask,
                                   UInt32 MaxDepth,
                                   Real32 MinSideLength,
                                   bool uniformSideLengths)
{
    OctreePtr TheTree = OctreePtr(new Octree());
    Pnt3f max, min;
    BoxVolume vol;
    RootNode->getWorldVolume(vol);
    if(uniformSideLengths)
    {
        Real32 x, y, z;
        vol.getSize(x,y,z);
        Pnt3f center;
        vol.getCenter(center);

        Real32 MaxSide = osgMax(x,osgMax(y,z));

        min = center - 0.5f * Vec3f(MaxSide,MaxSide,MaxSide); 
        max = center + 0.5f * Vec3f(MaxSide,MaxSide,MaxSide); 
    }
    else
    {
        vol.getBounds(min, max);
    }

    //set _Root
    TheTree->_Root->editVolume().setBounds(min,max);
    TheTree->_Root->setDepth(0);
    TheTree->_Root->setContainsObstacles(false);

    //Add collision geometry to the geometry nodes
    Octree::AddCollisionGeomGraphOpRefPtr AddCollisionOp =
        AddCollisionGeomGraphOp::create(TravMask,1,0);
    AddCollisionOp->traverse(RootNode);

    commitChanges();

    PhysicsBoxGeomUnrecPtr VolumeBoxGeom = PhysicsBoxGeom::create();
    VolumeBoxGeom->setSpace(AddCollisionOp->getSpace());
    VolumeBoxGeom->setCategoryBits(0);
    VolumeBoxGeom->setCollideBits(1);

    //Add a collision callback to the physics Space
    boost::signals2::connection CollisionConnection =
        AddCollisionOp->getSpace()->connectCollision(boost::bind(&Octree::handleCollision,
                                                                 TheTree.get(), _1),0.0,1.0);

    TheTree->build(TheTree->_Root,
                   VolumeBoxGeom,
                   AddCollisionOp->getSpace(),
                   AddCollisionOp->getWorld(),
                   MaxDepth,
                   MinSideLength);

    //Disconnect the collision callback
    CollisionConnection.disconnect();

    AddCollisionOp->getSpace()->RemoveGeom(VolumeBoxGeom->getGeomID());

    TheTree->beginSearchForNeighbors(TheTree->_Root.get());

    return TheTree;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Octree::OTNodePtr Octree::getNodeThatContains(const Pnt3f Location) const
{
    OTNodePtr TestNode(_Root);
    bool Intersected;
    while(TestNode &&
          TestNode->isBranch())
    {
        Intersected = false;
        //Find the node that the location is in
        for(UInt32 i(0) ; i<TestNode->getChildren().size() ; ++i)
        {
            if(TestNode->getChildren(i)->getVolume().intersect(Location))
            {
                TestNode = TestNode->getChildren(i);
                Intersected = true;
                break;
            }
        }
        if(!Intersected)
        {
            TestNode.reset();
        }
    }

    return TestNode;
}

UInt32 Octree::getNodeCount(void) const
{
    return (_Root ? _Root->getNodeCount(): 0);
}

UInt32 Octree::getLeafNodeCount(void) const
{
    return (_Root ? _Root->getLeafNodeCount(): 0);
}

UInt32 Octree::getBranchNodeCount(void) const
{
    return (_Root ? _Root->getBranchNodeCount(): 0);
}

UInt32 Octree::getIntersectingNodeCount(void) const
{
    return (_Root ? _Root->getIntersectingNodeCount(): 0);
}

UInt32 Octree::getIntersectingLeafNodeCount(void) const
{
    return (_Root ? _Root->getIntersectingLeafNodeCount(): 0);
}

UInt32 Octree::OTNode::getNodeCount(void) const
{
    UInt32 Result(1);
    for(UInt32 i(0) ; i<_Children.size() ; ++i)
    {
        Result += _Children[i]->getNodeCount();
    }
    return Result;
}

UInt32 Octree::OTNode::getLeafNodeCount(void) const
{
    UInt32 Result(_Children.size() == 0 ? 1 : 0);
    for(UInt32 i(0) ; i<_Children.size() ; ++i)
    {
        Result += _Children[i]->getLeafNodeCount();
    }
    return Result;
}

UInt32 Octree::OTNode::getBranchNodeCount(void) const
{
    UInt32 Result(_Children.size() == 0 ? 0 : 1);
    for(UInt32 i(0) ; i<_Children.size() ; ++i)
    {
        Result += _Children[i]->getBranchNodeCount();
    }
    return Result;
}

UInt32 Octree::OTNode::getIntersectingNodeCount(void) const
{
    UInt32 Result(_ContainsObstacles ? 1 : 0);
    for(UInt32 i(0) ; i<_Children.size() ; ++i)
    {
        Result += _Children[i]->getIntersectingNodeCount();
    }
    return Result;
}

UInt32 Octree::OTNode::getIntersectingLeafNodeCount(void) const
{
    UInt32 Result(_Children.size() == 0 && _ContainsObstacles ? 1 : 0);
    for(UInt32 i(0) ; i<_Children.size() ; ++i)
    {
        Result += _Children[i]->getIntersectingLeafNodeCount();
    }
    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Octree::handleCollision(CollisionEventDetails *const e)
{
    _CollisionOccured = true;
}

Pnt3f Octree::getVolMin(Octant octant, const BoxVolume& vol, const Vec3f& newLengths) const
{
    switch(octant)
    {
        case(OCT_000)://lower left front
            return Pnt3f(vol.getMin()[0], vol.getMin()[1], vol.getMin()[2]+newLengths.z());
        case(OCT_100)://lower right front
            return Pnt3f(vol.getMin()[0] + newLengths.x(), vol.getMin()[1], vol.getMin()[2]+newLengths.z());
        case(OCT_010)://top left front
            return Pnt3f(vol.getMin()[0], vol.getMin()[1] + newLengths.y(), vol.getMin()[2]+newLengths.z());
        case(OCT_110)://top right front
            return Pnt3f(vol.getMin()[0] + newLengths.x(), vol.getMin()[1] + newLengths.y(), vol.getMin()[2]+newLengths.z());
        case(OCT_001)://lower left back
            return Pnt3f(vol.getMin()[0], vol.getMin()[1], vol.getMin()[2]);
        case(OCT_101)://lower right back
            return Pnt3f(vol.getMin()[0] + newLengths.x(), vol.getMin()[1], vol.getMin()[2]);
        case(OCT_011)://top left back
            return Pnt3f(vol.getMin()[0], vol.getMin()[1] + newLengths.y(), vol.getMin()[2]);
        case(OCT_111)://top right back
            return Pnt3f(vol.getMin()[0] + newLengths.x(), vol.getMin()[1] + newLengths.y(), vol.getMin()[2]);
    };	
}

Pnt3f Octree::getVolMax(Octant octant, const BoxVolume& vol, const Vec3f& newLengths) const
{
    switch(octant)
    {
        case(OCT_000)://lower left front
            return Pnt3f(vol.getMax()[0] - newLengths.x(), vol.getMax()[1] - newLengths.y(), vol.getMax()[2]);
        case(OCT_100)://lower right front
            return Pnt3f(vol.getMax()[0], vol.getMax()[1] - newLengths.y(), vol.getMax()[2]);
        case(OCT_010)://top left front
            return Pnt3f(vol.getMax()[0] - newLengths.x(), vol.getMax()[1], vol.getMax()[2]);
        case(OCT_110)://top right front
            return Pnt3f(vol.getMax()[0], vol.getMax()[1], vol.getMax()[2]);
        case(OCT_001)://lower left back
            return Pnt3f(vol.getMax()[0] - newLengths.x(), vol.getMax()[1]-newLengths.y(), vol.getMax()[2] - newLengths.z());
        case(OCT_101)://lower right back
            return Pnt3f(vol.getMax()[0], vol.getMax()[1]-newLengths.y(), vol.getMax()[2] - newLengths.z());
        case(OCT_011)://top left back
            return Pnt3f(vol.getMax()[0] - newLengths.x(), vol.getMax()[1], vol.getMax()[2] - newLengths.z());
        case(OCT_111)://top right back
            return Pnt3f(vol.getMax()[0], vol.getMax()[1], vol.getMax()[2] - newLengths.z());
    };
}

void Octree::beginSearchForNeighbors(OTNode* node)
{
    //const Int8 maxChildren = 8;
    //const Int8 maxNeighbors = 6;


    /*if(node->getChildren().size() == 0)
      {
      return;
      }*/

    //node->getDepth() < _Depth
    if(node->getDepth() >= _Depth)
    {
        return;
    }

    if(node->getChildren().size() != 0)
    {
        for(Int8 i = 0; i < node->getChildren().size(); i++)
        {
            findNeighbors(node->getChildren()[i].get(), _Root.get(), 0);
            beginSearchForNeighbors(node->getChildren()[i].get());
        }
    }
}

void Octree::findNeighbors(OTNode* node, OTNode* target, Int8 numNeighbors)
{
    if(target->getChildren().size() != 0)
    {
        for(Int8 i = 0; i < target->getChildren().size(); i++)
        {
            if(areNeighbors(node, target->getChildren(i).get()))
            {
                node->addNeighbor(target->getChildren(i));
            }
            findNeighbors(node, target->getChildren(i).get(), numNeighbors);
        }
    }

}

bool Octree::areNeighbors(OTNode* node, OTNode* target) const
{

    if(node == target)//if they are the same node
    {
        return false;
    }

    Pnt3f min1 = node->getVolume().getMin();
    Pnt3f max1 = node->getVolume().getMax();
    Pnt3f min2 = target->getVolume().getMin();
    Pnt3f max2 = target->getVolume().getMax();

    //left
    if( (min1.x() == max2.x()) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        return true;
    }

    //right
    if( (max1.x() == min2.x()) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        return true;
    }


    //bottom
    if( (min1.y() == max2.y()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        return true;
    }

    //top
    if( (max1.y() == min2.y()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        return true;
    }
    if( (max1.z() == min2.z()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) )
    {

        return true;
    }


    //back
    if( (max2.z() == min1.z()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) )
    {

        return true;
    }

    return false;
}

void Octree::buildNewNodes(OTNodePtr node)
{
    const Int8 numChildren = 8;
    const Int8 maxNeighbors = 6;

    BoxVolume vol = node->getVolume();
    Vec3f Size;
    vol.getSize(Size);
    Vec3f newLengths = Vec3f( Size.x()*0.5, Size.y()*0.5, Size.z()*0.5 );
    Pnt3f newPos, newMin, newMax;

    for(Int8 i = 0; i < numChildren; i++)
    {
        OTNodePtr newNode = OTNodePtr(new OTNode);
        newNode->setParent(node);
        newNode->setDepth(node->getDepth()+1);
        newNode->setOctant(Octant(i));
        for(Int8 n = 0; n < maxNeighbors; n++)
        {
            newNode->getNeighborsToSide()[n] = false;
        }

        newMin = getVolMin(Octant(i), vol, newLengths);
        newMax = getVolMax(Octant(i), vol, newLengths);

        newNode->editVolume().setBounds(newMin,newMax);
        newNode->setContainsObstacles(false);

        node->addChild(newNode);
    }

    //update my _Depth
    if(_Depth < node->getDepth() + 1)
        _Depth = node->getDepth()+1;
}

void Octree::build(OTNodePtr node,
                   PhysicsBoxGeom* const VolumeBoxGeom,
                   PhysicsSpace* const Space,
                   PhysicsWorld* const World,
                   UInt32 MaxDepth,
                   Real32 MinSideLength)
{
    if(node->getDepth() > MaxDepth)
    {
        return;
    }

    Vec3f Size;
    node->getVolume().getSize(Size);
    VolumeBoxGeom->setLengths(Size);

    Pnt3f Center;
    node->getVolume().getCenter(Center);

    VolumeBoxGeom->setPosition(Vec3f(Center));

    commitChanges();

    _CollisionOccured = false;
    Space->Collide(World);

    if(_CollisionOccured)
    {
        node->setContainsObstacles(true);
    }

    if(_CollisionOccured  && (
       (Size.x() > MinSideLength &&
        Size.y() > MinSideLength &&
        Size.z() > MinSideLength) ||
       MinSideLength == 0.0f))
    {//ToDo: better way to check minVolume
        /*node->containsObstacles = true;*/

        buildNewNodes(node);
        for(Int8 i = 0; i < node->getChildren().size(); i++)
        {
            build(node->getChildren(i),
                  VolumeBoxGeom,
                  Space,
                  World,
                  MaxDepth,
                  MinSideLength);
        }
    }
}

/*----------------------- constructors & destructors ----------------------*/

Octree::Octree(void) : _CollisionOccured(false),
                       _Depth(0)
{
    _Root = OTNodePtr(new OTNode);
}

Octree::Octree(Node* const n, PhysicsSpace* const s, PhysicsWorld* const w) :
    _CollisionOccured(false),
    _Depth(0)

{
    _Root = OTNodePtr(new OTNode);
}

/*----------------------------- class specific ----------------------------*/
namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp =
            Octree::AddCollisionGeomGraphOp::create(TypeTraits<UInt32>::getMax(),TypeTraits<UInt32>::getMax(),TypeTraits<UInt32>::getMax());

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace


Octree::AddCollisionGeomGraphOp::AddCollisionGeomGraphOp(UInt32 travMask,
                                                         UInt32 catMask,
                                                         UInt32 colMask)
    : GraphOp("AddCollisionGeomGraphOp")
    , _TravMask  (travMask)
    , _CategoryMask  (catMask)
    , _CollisionMask  (colMask)
{
}

Octree::AddCollisionGeomGraphOp::~AddCollisionGeomGraphOp(void)
{
}

Octree::AddCollisionGeomGraphOpTransitPtr
Octree::AddCollisionGeomGraphOp::create(UInt32 travMask,
                                        UInt32 catMask,
                                        UInt32 colMask)
{
    return AddCollisionGeomGraphOpTransitPtr(new AddCollisionGeomGraphOp(travMask,catMask,colMask));
}

GraphOpTransitPtr Octree::AddCollisionGeomGraphOp::clone(void)
{
    return GraphOpTransitPtr(new AddCollisionGeomGraphOp(_TravMask,_CategoryMask,_CollisionMask));
}

void Octree::AddCollisionGeomGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    
    ps("travMask",  _TravMask);
    ps("categoryMask",  _CategoryMask);
    ps("collisionMask",  _CollisionMask);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("AddCollisionGeomGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string Octree::AddCollisionGeomGraphOp::usage(void)
{
    return 
    "AddCollisionGeom: Adds Collision geometry\n"
    "  Adds Collision geometry as attachments to nodes\n"
    "Params: name (type, default)\n"
    "  travMask   (UInt32, 4294967295): \n"
    "                    traversal mask\n"
    "  categoryMask   (UInt32, 4294967295): \n"
    "                    category mask to assign geoms\n"
    "  collisionMask   (UInt32, 4294967295): \n"
    "                    collision mask to assign geoms\n";
}

bool Octree::AddCollisionGeomGraphOp::traverse(Node *root)
{
    _PhysWorld = PhysicsWorld::create();
    _PhysSpace = PhysicsHashSpace::create();
    return Inherited::traverse(root);
}

Action::ResultE Octree::AddCollisionGeomGraphOp::traverseEnter(Node * const node)
{
    if(node->getTravMask() & _TravMask)
    {
        if(node->getCore() != NULL &&
           node->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
        {
            PhysicsTriMeshGeomRecPtr TriGeom = PhysicsTriMeshGeom::create();
            TriGeom->setCategoryBits(_CategoryMask);
            TriGeom->setCollideBits(_CollisionMask);

            //add geom to space for collision
            TriGeom->setSpace(_PhysSpace);

            //set the geometryNode to fill the ode-triMesh
            TriGeom->setGeometryNode(node);

            _CreatedGeoms.push_back(TriGeom);
        }

        return Action::Continue;
    }
    else
    {
        return Action::Skip;
    }
}

Action::ResultE Octree::AddCollisionGeomGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
    if(node->getTravMask() & _TravMask)
    {
        return res;
    }
    else
    {
        return Action::Skip;
    }
}

void Octree::AddCollisionGeomGraphOp::destroyObjs(void)
{
    //for(UInt32 i(0) ; i<_CreatedGeoms.size() ; ++i)
    //{
        //_CreatedGeoms[i];
    //}
    _PhysSpace = NULL;
    _PhysWorld = NULL;
    _CreatedGeoms.clear();
}

PhysicsSpace*  Octree::AddCollisionGeomGraphOp::getSpace(void) const
{
    return _PhysSpace;
}

PhysicsWorld*  Octree::AddCollisionGeomGraphOp::getWorld(void) const
{
    return _PhysWorld;
}


OSG_END_NAMESPACE
