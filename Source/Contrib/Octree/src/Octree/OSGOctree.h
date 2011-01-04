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
#include "OSGPhysicsBoxGeomFields.h"
#include "OSGCollisionEventDetailsFields.h"

#include "OSGNodeFields.h"

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

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

    struct OTNodeVolume
    {
        Vec3f lengths;
        Pnt3f position,
              min,
              max;
    };


    struct OTNode;

    typedef boost::shared_ptr<OTNode> OTNodePtr;
    typedef boost::weak_ptr<OTNode> OTNodeWeakPtr;

    struct OTNode
    {
        OTNodeVolume vol;
        std::vector<OTNodePtr> children;
        std::vector<OTNodeWeakPtr> neighbors;
        bool neighborsToSide[6];
        OTNodeWeakPtr parent;
        Octant octant;
        Int32 depth;
        bool containsObstacles;
    };

    Octree(void);
    Octree(Node* const, PhysicsSpace* const, PhysicsWorld* const);
    void buildTree(void);

    void setRootNode(Node* const);
    void setSpace(PhysicsSpace* const);
    void setWorld(PhysicsWorld* const);
    OTNodePtr getRoot(void) const;

    void setMinNodeVolume(const Vec3f& min);
    const Vec3f& getMinNodeVolume(void) const;

    UInt32 getDepth(void) const;

  private:
    //construct the octree
    void build(OTNodePtr, PhysicsBoxGeom* const VolumeBoxGeom);
    void buildNewNodes(OTNodePtr);

    Pnt3f getVolMin(Octant, OTNodeVolume&, Vec3f&) const;
    Pnt3f getVolMax(Octant, OTNodeVolume&, Vec3f&) const;
    void beginSearchForNeighbors(OTNode*);
    void findNeighbors(OTNode*, OTNode*, Int8); //TODO:  void traverse();
    bool areNeighbors(OTNode*, OTNode*) const;
    void handleCollision(CollisionEventDetails *const e);

    bool _CollisionOccured;

    //scene info
    NodeRecPtr _SceneRoot;
    UInt32     _CollidableMask;
    PhysicsSpaceRecPtr _PhysSpace;
    PhysicsWorldRecPtr _PhysWorld;

    //octree
    OTNodePtr _Root;
    Vec3f _MinNodeVolume;
    UInt32 _Depth;
};

OSG_END_NAMESPACE

#include "OSGOctree.inl"

#endif
