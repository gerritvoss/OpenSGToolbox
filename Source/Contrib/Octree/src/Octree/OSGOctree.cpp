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

//Physics
#include "OSGPhysicsSpace.h"
#include "OSGPhysicsWorld.h"
#include "OSGPhysicsBoxGeom.h"
#include "OSGCollisionEventDetails.h"


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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Octree::buildTree(bool uniformSideLengths)
{
    Real32 x, y, z;
    Pnt3f center, max, min;
    BoxVolume vol;
    _SceneRoot->getWorldVolume(vol);
    vol.getSize(x,y,z);
    vol.getCenter(center);
    if(uniformSideLengths)
    {
        x = y = z = osgMax(x,osgMax(y,z));

        min = center - 0.5f * Vec3f(x); 
        max = center + 0.5f * Vec3f(x); 
    }
    else
    {
        vol.getBounds(min, max);
    }

    //set _Root
    _Root->vol.lengths = Vec3f(x, y, z);
    _Root->vol.max = max;
    _Root->vol.min = min;
    _Root->vol.position = center;
    _Root->depth = 0;
    //_Root->parent = NULL;
    _Root->containsObstacles = false;

    PhysicsBoxGeomUnrecPtr VolumeBoxGeom = PhysicsBoxGeom::create();
    VolumeBoxGeom->setSpace(_PhysSpace);

    //Traverse the root node of the scene
    //For each geometry decendent, create a physics TriMeshGeom

    //Add a collision callback to the physics _PhysSpace
    boost::signals2::connection CollisionConnection =
        _PhysSpace->connectCollision(boost::bind(&Octree::handleCollision, this, _1),0.0,1.0);

    build(_Root,VolumeBoxGeom);

    //Disconnect the collision callback
    CollisionConnection.disconnect();

    _PhysSpace->RemoveGeom(VolumeBoxGeom->getGeomID());

    beginSearchForNeighbors(_Root.get());

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Octree::handleCollision(CollisionEventDetails *const e)
{
    _CollisionOccured = true;
}

Pnt3f Octree::getVolMin(Octant octant, OTNodeVolume& vol, Vec3f& newLengths) const
{
    switch(octant)
    {
        case(OCT_000)://lower left front
            return Pnt3f(vol.min[0], vol.min[1], vol.min[2]+newLengths.z());
        case(OCT_100)://lower right front
            return Pnt3f(vol.min[0] + newLengths.x(), vol.min[1], vol.min[2]+newLengths.z());
        case(OCT_010)://top left front
            return Pnt3f(vol.min[0], vol.min[1] + newLengths.y(), vol.min[2]+newLengths.z());
        case(OCT_110)://top right front
            return Pnt3f(vol.min[0] + newLengths.x(), vol.min[1] + newLengths.y(), vol.min[2]+newLengths.z());
        case(OCT_001)://lower left back
            return Pnt3f(vol.min[0], vol.min[1], vol.min[2]);
        case(OCT_101)://lower right back
            return Pnt3f(vol.min[0] + newLengths.x(), vol.min[1], vol.min[2]);
        case(OCT_011)://top left back
            return Pnt3f(vol.min[0], vol.min[1] + newLengths.y(), vol.min[2]);
        case(OCT_111)://top right back
            return Pnt3f(vol.min[0] + newLengths.x(), vol.min[1] + newLengths.y(), vol.min[2]);
    };	
}

Pnt3f Octree::getVolMax(Octant octant, OTNodeVolume& vol, Vec3f& newLengths) const
{
    switch(octant)
    {
        case(OCT_000)://lower left front
            return Pnt3f(vol.max[0] - newLengths.x(), vol.max[1] - newLengths.y(), vol.max[2]);
        case(OCT_100)://lower right front
            return Pnt3f(vol.max[0], vol.max[1] - newLengths.y(), vol.max[2]);
        case(OCT_010)://top left front
            return Pnt3f(vol.max[0] - newLengths.x(), vol.max[1], vol.max[2]);
        case(OCT_110)://top right front
            return Pnt3f(vol.max[0], vol.max[1], vol.max[2]);
        case(OCT_001)://lower left back
            return Pnt3f(vol.max[0] - newLengths.x(), vol.max[1]-newLengths.y(), vol.max[2] - newLengths.z());
        case(OCT_101)://lower right back
            return Pnt3f(vol.max[0], vol.max[1]-newLengths.y(), vol.max[2] - newLengths.z());
        case(OCT_011)://top left back
            return Pnt3f(vol.max[0] - newLengths.x(), vol.max[1], vol.max[2] - newLengths.z());
        case(OCT_111)://top right back
            return Pnt3f(vol.max[0], vol.max[1], vol.max[2] - newLengths.z());
    };
}

void Octree::beginSearchForNeighbors(OTNode* node)
{
    //const Int8 maxChildren = 8;
    //const Int8 maxNeighbors = 6;


    /*if(node->children.size() == 0)
      {
      return;
      }*/

    //node->depth < _Depth
    if(node->depth >= _Depth)
    {
        return;
    }

    if(node->children.size() != 0)
    {
        for(Int8 i = 0; i < node->children.size(); i++)
        {
            findNeighbors(node->children[i].get(), _Root.get(), 0);
            beginSearchForNeighbors(node->children[i].get());
        }
    }
}

void Octree::findNeighbors(OTNode* node, OTNode* target, Int8 numNeighbors)
{
    ////const Int8 maxChildren = 8;
    //const Int8 maxNeighbors = 6;

    //node->depth > target->depth && numNeighbors <= maxNeighbors  /// || node->neighbors.size() > maxNeighbors
    /*if(node->depth < target->depth)
      {	
      return;
      }*/

    /*if(node->neighbors.size() >= maxNeighbors)
      {
      return;
      }*/

    if(target->children.size() != 0)
    {
        for(Int8 i = 0; i < target->children.size(); i++)
        {
            //findNeighbors(node, target->children[i], numNeighbors);

            if(areNeighbors(node, target->children[i].get()))
            {
                node->neighbors.push_back(target->children[i]);
                //numNeighbors++;
            }
            //areNeighbors(node, target->children[i]);
            findNeighbors(node, target->children[i].get(), numNeighbors);
        }
    }

}

bool Octree::areNeighbors(OTNode* node, OTNode* target) const
{

    if(node == target)//if they are the same node
        return false;

    //if(node->depth < target->depth)//target is too small to be a neighbor
    //	return false;

    Pnt3f min1 = node->vol.min;
    Pnt3f max1 = node->vol.max;
    Pnt3f min2 = target->vol.min;
    Pnt3f max2 = target->vol.max;

    //left
    //if(!node->neighborsToSide[LEFT])
    //{
    if( (min1.x() == max2.x()) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[LEFT] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[LEFT] = true;
          return true;*/
    }
    //}

    //right
    //if(!node->neighborsToSide[RIGHT])
    //{
    if( (max1.x() == min2.x()) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[RIGHT] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[RIGHT] = true;
          return true;*/
    }
    //}


    //bottom
    //if(!node->neighborsToSide[BOTTOM])
    //{
    if( (min1.y() == max2.y()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[BOTTOM] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[BOTTOM] = true;
          return true;*/
    }
    //}

    //top
    //if(!node->neighborsToSide[TOP])
    //{
    if( (max1.y() == min2.y()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.z() >= min2.z() && max1.z() <= max2.z()) || (min2.z() >= min1.z() && max2.z() <= max1.z())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[TOP] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[TOP] = true;
          return true;*/
    }
    //}

    //front
    //if(!node->neighborsToSide[FRONT])
    //{
    if( (max1.z() == min2.z()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[FRONT] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[FRONT] = true;
          return true;*/
    }
    //}


    //back
    //if(!node->neighborsToSide[BACK]))
    //{
    if( (max2.z() == min1.z()) && 
        ((min1.x() >= min2.x() && max1.x() <= max2.x()) || (min2.x() >= min1.x() && max2.x() <= max1.x())) && 
        ((min1.y() >= min2.y() && max1.y() <= max2.y()) || (min2.y() >= min1.y() && max2.y() <= max1.y())) )
    {
        //if(target->children.size() !=0)
        //{
        //	for(Int8 i = 0; i < target->children.size(); i++)
        //		areNeighbors(node, target->children[i]);
        //}else{
        //	node->neighbors.push_back(target);
        //	node->neighborsToSide[BACK] = true;
        //	//return true;
        //}

        return true;
        /*node->neighborsToSide[BACK] = true;
          return true;*/
    }
    //}

    return false;
}

void Octree::buildNewNodes(OTNodePtr node)
{
    const Int8 numChildren = 8;
    const Int8 maxNeighbors = 6;

    OTNodeVolume vol = node->vol;
    Vec3f newLengths = Vec3f( vol.lengths.x()*0.5, vol.lengths.y()*0.5, vol.lengths.z()*0.5 );
    Pnt3f newPos, newMin, newMax;

    for(Int8 i = 0; i < numChildren; i++)
    {
        OTNodePtr newNode = OTNodePtr(new OTNode);
        newNode->parent = node;
        newNode->depth = node->depth+1;
        newNode->octant = Octant(i);
        for(Int8 n = 0; n < maxNeighbors; n++)
            newNode->neighborsToSide[n] = false;

        newMin = getVolMin(Octant(i), vol, newLengths);
        newMax = getVolMax(Octant(i), vol, newLengths);
        newPos = newMin + (newMax-newMin) * 0.5;

        newNode->vol.lengths = newLengths;
        newNode->vol.position = newPos;
        newNode->vol.min = newMin;
        newNode->vol.max = newMax;
        newNode->containsObstacles = false;

        node->children.push_back(newNode);
    }

    //update my _Depth
    if(_Depth < node->depth + 1)
        _Depth = node->depth+1;
}

void Octree::build(OTNodePtr node, PhysicsBoxGeom* const VolumeBoxGeom)
{
    VolumeBoxGeom->setLengths(node->vol.lengths);
    VolumeBoxGeom->setPosition(Vec3f(node->vol.position.x(),
                               node->vol.position.y(),
                               node->vol.position.z()));

    commitChanges();

    _CollisionOccured = false;
    _PhysSpace->Collide(_PhysWorld);

    if(_CollisionOccured)
    {
        node->containsObstacles = true;
    }

    if(_CollisionOccured  && (node->vol.lengths.x() > _MinNodeVolume.x() && node->vol.lengths.y() > _MinNodeVolume.y() && node->vol.lengths.z() > _MinNodeVolume.z()))
    {//ToDo: better way to check minVolume
        /*node->containsObstacles = true;*/

        buildNewNodes(node);
        //Int8 numChildren = 8;
        for(Int8 i = 0; i < node->children.size(); i++)
        {
            build(node->children[i], VolumeBoxGeom);
        }
    }
}

/*----------------------- constructors & destructors ----------------------*/

Octree::Octree(void) : _CollisionOccured(false),
                       _CollidableMask(TypeTraits<UInt32>::getMax()),
                       _MinNodeVolume(0.2f, 0.2f, 0.2f),
                       _Depth(0)
{
    _Root = OTNodePtr(new OTNode);
}

Octree::Octree(Node* const n, PhysicsSpace* const s, PhysicsWorld* const w) :
    _CollisionOccured(false),
    _CollidableMask(TypeTraits<UInt32>::getMax()),
    _PhysSpace(s),
    _SceneRoot(n),
    _PhysWorld(w),
    _MinNodeVolume(0.2f, 0.2f, 0.2f),
    _Depth(0)

{
    _Root = OTNodePtr(new OTNode);
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE
