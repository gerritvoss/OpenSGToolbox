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

OSG_BEGIN_NAMESPACE

inline
UInt32 Octree::getDepth(void) const
{
    return _Depth;
}

inline
Octree::OTNodePtr Octree::getRoot(void) const
{
    return _Root;
}

inline
const BoxVolume& Octree::OTNode::getVolume(void) const
{
    return _Volume;
}

inline
const std::vector<Octree::OTNodePtr>& Octree::OTNode::getChildren(void) const
{
    return _Children;
}

inline
Octree::OTNodePtr Octree::OTNode::getChildren(UInt32 Index)
{
    OTNodePtr Result();
    return _Children[Index];
}

inline
std::vector<Octree::OTNodePtr> Octree::OTNode::getNeighbors(void) const
{
    std::vector<Octree::OTNodePtr> Result;
    for(UInt32 i(0) ; i<_Neighbors.size() ; ++i)
    {
        Result.push_back(OTNodePtr(_Neighbors[i]));
    }

    return Result;
}

inline
Octree::OTNodePtr Octree::OTNode::getNeighbor(UInt32 Index)
{
    return OTNodePtr(_Neighbors[Index]);
}

inline
std::vector<bool> Octree::OTNode::getNeighborsToSide(void) const
{
    std::vector<bool> Result;
    for(UInt32 i(0) ; i<6 ; ++i)
    {
        Result.push_back(_NeighborsToSide[i]);
    }

    return Result;
}

inline
Octree::OTNodePtr Octree::OTNode::getParent(void) const
{
    return OTNodePtr(_Parent);
}

inline
const Octree::Octant& Octree::OTNode::getOctant(void) const
{
    return _Octant;
}

inline
Int32 Octree::OTNode::getDepth(void) const
{
    return _Depth;
}

inline
bool Octree::OTNode::getContainsObstacles(void) const
{
    return _ContainsObstacles;
}

inline
void Octree::OTNode::setVolume(const BoxVolume& Volume)
{
    _Volume = Volume;
}

inline
void Octree::OTNode::setChildren(const std::vector<OTNodePtr>& Children)
{
    _Children = Children;
}

inline
void Octree::OTNode::setNeighbors(const std::vector<OTNodePtr>& Neighbors)
{
    _Neighbors.clear();
    for(UInt32 i(0) ; i<Neighbors.size() ; ++i)
    {
        _Neighbors.push_back(Neighbors[i]);
    }
}

inline
void Octree::OTNode::setNeighborsToSide(const std::vector<bool>& NeighborsToSide)
{
    assert(NeighborsToSide.size() == 6);

    for(UInt32 i(0) ; i<NeighborsToSide.size() ; ++i)
    {
        _NeighborsToSide[i] = NeighborsToSide[i];
    }
}

inline
void Octree::OTNode::setParent(OTNodePtr Parent)
{
    _Parent = Parent;
}

inline
void Octree::OTNode::setOctant(Octant TheOctant)
{
    _Octant = TheOctant;
}

inline
void Octree::OTNode::setDepth(Int32 Depth)
{
    _Depth = Depth;
}

inline
void Octree::OTNode::setContainsObstacles(bool ContainsObs)
{
    _ContainsObstacles = ContainsObs;
}

inline
BoxVolume& Octree::OTNode::editVolume(void)
{
    return _Volume;
}

inline
void Octree::OTNode::addChild(OTNodePtr Child)
{
    _Children.push_back(Child);
}

inline
void Octree::OTNode::addNeighbor(OTNodePtr Neighbor)
{
    _Neighbors.push_back(Neighbor);
}

inline
bool Octree::OTNode::isLeaf(void) const
{
    return _Children.size() == 0;
}

inline
bool Octree::OTNode::isBranch(void) const
{
    return !isLeaf();
}

inline
bool Octree::OTNode::isEmpty(void) const
{
    return !getContainsObstacles();
}

OSG_END_NAMESPACE

