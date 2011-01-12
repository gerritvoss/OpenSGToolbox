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

#include "OSGOctree.h"
#include "OSGOctreeAStarAlgorithm.h"

OSG_BEGIN_NAMESPACE

OctreeAStarAlgorithm::OctreeAStarAlgorithm(void)
{
}

std::vector<Pnt3f> OctreeAStarAlgorithm::search(OctreePtr Tree,
                                                const Pnt3f& Start,
                                                const Pnt3f& Goal)
{
    return search(Tree, Start, Goal,
                  boost::bind(&OctreeAStarAlgorithm::euclideanDistanceCost, _2, _3,
                              1.0f));
}

std::vector<Pnt3f> OctreeAStarAlgorithm::search(OctreePtr Tree,
                                                const Pnt3f& Start,
                                                const Pnt3f& Goal,
                                                PathCostHeuristicFunc CostHeuristicFunc)
{
    _Tree = Tree; 
    _StartNode = _Tree->getNodeThatContains(Start);
    _GoalNode = _Tree->getNodeThatContains(Goal);
    _CostHeuristicFunc = CostHeuristicFunc;

    if(!_StartNode ||
       !_GoalNode)
    {
        return _SolutionPath;
    }

	//clear lists
    _SolutionPath.clear();
	_OpenNodes.clear();
	_ClosedNodes.clear();

	//initialize start node
	ASNodePtr startNode = ASNodePtr(new ASNode);
	startNode->_OctreeNode = _StartNode;
	startNode->_CostFromStart = 0;
    Pnt3f Center;
    _StartNode->getVolume().getCenter(Center);
	startNode->_CostToGoal = _CostHeuristicFunc(_Tree, _StartNode, Center);
	startNode->_Parent.reset();
	_OpenNodes.push_back(startNode);

	while(!_OpenNodes.empty())
    {
		ASNodePtr Node = _OpenNodes.front();
		_OpenNodes.erase(_OpenNodes.begin());

		if(Node->_OctreeNode == _GoalNode)
        {
			constructPath(Node);
			return _SolutionPath;//success
		}
        else
        {
			for(Int8 i = 0; i < Node->_OctreeNode->getNeighbors().size(); ++i)
            {
				if(!Node->_OctreeNode->getNeighbor(i)->getContainsObstacles())
                {//Node->_OctreeNode->getNeighbor(i)->children.size() == 0
                    Node->_OctreeNode->getNeighbor(i)->getVolume().getCenter(Center);
					Real32 NewCost = Node->_CostFromStart + _CostHeuristicFunc(_Tree, _StartNode, Center);
					Int32 locInOpen = inOpen(Node->_OctreeNode->getNeighbor(i));
					Int32 locInClosed = inClosed(Node->_OctreeNode->getNeighbor(i));
					if((locInOpen >= 0 && _OpenNodes[locInOpen]->_CostFromStart <= NewCost) || (locInClosed >= 0 && _ClosedNodes[locInClosed]->_CostFromStart <= NewCost))
                    {
						continue;
					}
                    else
                    {
						//initialize a new node
						ASNodePtr NewNode = ASNodePtr(new ASNode());
						NewNode->_OctreeNode = Node->_OctreeNode->getNeighbor(i);
                        NewNode->_OctreeNode->getVolume().getCenter(Center);
						NewNode->_CostFromStart = _CostHeuristicFunc(_Tree, _StartNode, Center);
						NewNode->_CostToGoal = _CostHeuristicFunc(_Tree, _GoalNode, Center);
						NewNode->_Parent = Node;

						if(locInClosed >= 0)
                        {
							_ClosedNodes.erase(_ClosedNodes.begin() + locInClosed);
						}
						/*if(locInOpen >= 0)
                         * {
							_OpenNodes.erase(_OpenNodes.begin() + locInOpen);
						}else{
							pushOnOpen(NewNode);
						}*/
						if(locInOpen >= 0)
                        {
							_OpenNodes.erase(_OpenNodes.begin() + locInOpen);
						}
						pushOnOpen(NewNode);

					}//endif
				}//endif...
			}//end for loop...dont with Node
		}//endif

		_ClosedNodes.push_back(Node);
	}//end while loop

	return _SolutionPath;
}

Real32 OctreeAStarAlgorithm::euclideanDistanceCost(Octree::OTNodePtr node,
                                                   const Pnt3f& Location,
                                                   Real32 CostPerUnit)
{
    Pnt3f Target;
    node->getVolume().getCenter(Target);
	return CostPerUnit * Location.dist(Target);
}

Real32 OctreeAStarAlgorithm::manhattanDistanceCost(Octree::OTNodePtr node,
                                                   const Pnt3f& Location,
                                                   Real32 CostPerUnit)
{
    Pnt3f Target;
    node->getVolume().getCenter(Target);
	return CostPerUnit * (osgAbs(Location.x() - Target.x())
                        + osgAbs(Location.y() - Target.y())
                        + osgAbs(Location.z() - Target.z()));
}

//protected functions

void OctreeAStarAlgorithm::constructPath(ASNodePtr node)
{
	ASNodePtr temp = node;

    std::deque<Pnt3f> ThePath;
    Pnt3f Center;
	while(temp)
    {
        temp->_OctreeNode->getVolume().getCenter(Center);
		ThePath.push_front(Center);
        if(!temp->_Parent.expired())
        {
            temp = ASNodePtr(temp->_Parent);
        }
        else
        {
            temp.reset();
        }
	}
    _SolutionPath.insert(_SolutionPath.end(), ThePath.begin(), ThePath.end());

}

Int32 OctreeAStarAlgorithm::inOpen(const Octree::OTNodePtr node)
{
	for(Int32 i = 0; i < _OpenNodes.size(); ++i)
    {
		if(_OpenNodes[i]->_OctreeNode == node)
        {
			return i;
        }
	}

	return -1;
}

Int32 OctreeAStarAlgorithm::inClosed(const Octree::OTNodePtr node)
{
	for(Int32 i = 0; i < _ClosedNodes.size(); ++i)
    {
		if(_ClosedNodes[i]->_OctreeNode == node)
        {
			return i;
        }
	}

	return -1;
}

void OctreeAStarAlgorithm::pushOnOpen(ASNodePtr node)
{
	for(Int32 i = 0; i < _OpenNodes.size(); ++i)
    {
		//either cfs or total cost
		if(node->_CostFromStart <= _OpenNodes[i]->_CostFromStart)
        {
			_OpenNodes.insert(_OpenNodes.begin() + i, node);
			return;
		}
	}
	_OpenNodes.push_back(node);
}

OSG_END_NAMESPACE

