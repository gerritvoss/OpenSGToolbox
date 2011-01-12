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
#ifndef _OSGOCTREE_H_
#define _OSGOCTREE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribOctreeDef.h"
#include "OSGBaseTypes.h"

#include "OSGPhysicsSpaceFields.h"
#include "OSGPhysicsWorldFields.h"
#include "OSGPhysicsGeomFields.h"
#include "OSGPhysicsBoxGeomFields.h"
#include "OSGCollisionEventDetailsFields.h"

#include "OSGNodeFields.h"
#include "OSGGraphOp.h"

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

class Octree;

typedef boost::shared_ptr<Octree> OctreePtr;

class OSG_CONTRIBOCTREE_DLLMAPPING Octree
{
  public:

    enum Octant
    {
        OCT_000 = 0, //lower left front octant
        OCT_100 = 1, //lower right front octant
        OCT_010 = 2, //top left front
        OCT_110 = 3, //top right front
        OCT_001 = 4, //lower left back
        OCT_101 = 5, //lower right back
        OCT_011 = 6, //top left back
        OCT_111 = 7  //top right back
    };

    enum SideNeighbor
    {
        LEFT   = 0,
        RIGHT  = 1,
        BOTTOM = 2,
        TOP    = 3,
        BACK   = 4,
        FRONT  = 5
    };

    struct OTNode;

    typedef boost::shared_ptr<OTNode> OTNodePtr;
    typedef boost::weak_ptr<OTNode> OTNodeWeakPtr;

    struct OTNode
    {
      public:
        friend class Octree;

        const BoxVolume& getVolume(void) const;
        const std::vector<OTNodePtr>& getChildren(void) const;
        OTNodePtr getChildren(UInt32 Index);
        std::vector<OTNodePtr> getNeighbors(void) const;
        OTNodePtr getNeighbor(UInt32 Index);
        std::vector<bool> getNeighborsToSide(void) const;
        OTNodePtr getParent(void) const;
        const Octant& getOctant(void) const;
        Int32 getDepth(void) const;

        UInt32 getNodeCount(void) const;
        UInt32 getLeafNodeCount(void) const;
        UInt32 getBranchNodeCount(void) const;
        UInt32 getIntersectingNodeCount(void) const;
        UInt32 getIntersectingLeafNodeCount(void) const;

        bool getContainsObstacles(void) const;

        void setVolume(const BoxVolume& Volume);
        void setChildren(const std::vector<OTNodePtr>& Children);
        void setNeighbors(const std::vector<OTNodePtr>& Neighbors);
        void setNeighborsToSide(const std::vector<bool>& NeighborsToSide);
        void setParent(OTNodePtr Parent);
        void setOctant(Octant TheOctant);
        void setDepth(Int32 Depth);
        void setContainsObstacles(bool ContainsObs);

        bool isLeaf(void) const;
        bool isBranch(void) const;
        bool isEmpty(void) const;

      private:
        BoxVolume& editVolume(void);
        void addChild(OTNodePtr Child);
        void addNeighbor(OTNodePtr Neighbor);

        BoxVolume _Volume;
        std::vector<OTNodePtr> _Children;
        std::vector<OTNodeWeakPtr> _Neighbors;
        bool _NeighborsToSide[6];
        OTNodeWeakPtr _Parent;
        Octant _Octant;
        Int32 _Depth;
        bool _ContainsObstacles;
    };


    static OctreePtr buildTree(Node* const RootNode,
                                   UInt32 TravMask,
                                   UInt32 MaxDepth,
                                   Real32 MinSideLength = 0.0f,
                                   bool uniformSideLengths = true);

    OTNodePtr getRoot(void) const;

    OTNodePtr getNodeThatContains(const Pnt3f Location) const;

    UInt32 getDepth(void) const;

    UInt32 getNodeCount(void) const;
    UInt32 getLeafNodeCount(void) const;
    UInt32 getBranchNodeCount(void) const;

    UInt32 getIntersectingNodeCount(void) const;
    UInt32 getIntersectingLeafNodeCount(void) const;

    class AddCollisionGeomGraphOp : public GraphOp
    {
        /*==========================  PUBLIC  =================================*/
      public:
        /*---------------------------------------------------------------------*/
        /*! \name Types                                                        */
        /*! \{                                                                 */

        typedef GraphOp                                 Inherited;
        typedef AddCollisionGeomGraphOp                 Self;

        OSG_GEN_INTERNAL_MEMOBJPTR(AddCollisionGeomGraphOp);

        /*! \}                                                                 */
        /*---------------------------------------------------------------------*/
        /*! \name Classname                                                    */
        /*! \{                                                                 */

        static const char *getClassname(void) { return "AddCollisionGeomGraphOp"; };

        /*! \}                                                                 */
        /*---------------------------------------------------------------------*/
        /*! \name Constructors                                                 */
        /*! \{                                                                 */

        static ObjTransitPtr      create(UInt32 travMask,
                                         UInt32 catMask,
                                         UInt32 colMask);

        virtual GraphOpTransitPtr clone (void                             );

        /*! \}                                                                 */
        /*---------------------------------------------------------------------*/
        /*! \name Parameters                                                   */
        /*! \{                                                                 */

        void        setParams(const std::string params);
        std::string usage    (void                    );

        /*! \}                                                                 */
        virtual bool traverse(Node *root);
        void           destroyObjs(void);
        PhysicsSpace*  getSpace(void) const;
        PhysicsWorld*  getWorld(void) const;
        /*=========================  PROTECTED  ===============================*/
      protected:
        /*---------------------------------------------------------------------*/
        /*! \name Constructors/Destructor                                      */
        /*! \{                                                                 */

        AddCollisionGeomGraphOp(UInt32 travMask,
                                UInt32 catMask,
                                UInt32 colMask);
        virtual ~AddCollisionGeomGraphOp(void                                    );

        /*! \}                                                                 */
        /*==========================  PRIVATE  ================================*/
      private:
        Action::ResultE traverseEnter(Node * const node);
        Action::ResultE traverseLeave(Node * const node, Action::ResultE res);

        UInt32 _TravMask;
        UInt32 _CategoryMask;
        UInt32 _CollisionMask;
        std::vector<PhysicsGeomUnrecPtr> _CreatedGeoms;
        PhysicsSpaceRecPtr _PhysSpace;
        PhysicsWorldRecPtr _PhysWorld;
    };
    OSG_GEN_MEMOBJPTR(AddCollisionGeomGraphOp);

  private:
    //construct the octree
    Octree(void);
    Octree(Node* const, PhysicsSpace* const, PhysicsWorld* const);

    void build(OTNodePtr,
               PhysicsBoxGeom* const VolumeBoxGeom,
               PhysicsSpace* const Space,
               PhysicsWorld* const World,
               UInt32 MaxDepth,
               Real32 MinSideLength);

    void buildNewNodes(OTNodePtr);

    Pnt3f getVolMin(Octant, const BoxVolume&, const Vec3f&) const;
    Pnt3f getVolMax(Octant, const BoxVolume&, const Vec3f&) const;
    void beginSearchForNeighbors(OTNode*);
    void findNeighbors(OTNode*, OTNode*, Int8); //TODO:  void traverse();
    bool areNeighbors(OTNode*, OTNode*) const;
    void handleCollision(CollisionEventDetails *const e);

    bool _CollisionOccured;

    //octree
    OTNodePtr _Root;
    UInt32 _Depth;
};

OSG_END_NAMESPACE

#include "OSGOctree.inl"

#endif
