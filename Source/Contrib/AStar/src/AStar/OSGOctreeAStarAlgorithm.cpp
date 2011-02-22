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

/*!\class OSG::OctreeAStarAlgorithm
 *
 * \brief Class for constructing paths using the A* path planning algorithm
 *
 * From <a href="http://en.wikipedia.org/wiki/A*">Wikipedia</a>:
 *
 * A* uses a best-first search and finds the least-cost path from a given
 * initial node to one goal node (out of one or more possible goals).
 *
 * It uses a distance-plus-cost heuristic function (usually denoted f(x))
 * to determine the order in which the search visits nodes in the tree.
 * The distance-plus-cost heuristic is a sum of two functions:
 *  - the path-cost function, which is the cost from the starting node to the current node (usually denoted g(x))
 *  - and an admissible "heuristic estimate" of the distance to the goal (usually denoted h(x)).
 *
 * The h(x) part of the f(x) function must be an admissible heuristic; that
 * is, it must not overestimate the distance to the goal. Thus, for an application
 * like routing, h(x) might represent the straight-line distance to the goal
 * , since that is physically the smallest possible distance between any two
 * points or nodes.
 *
 * If the heuristic h satisfies the additional condition h(x) \le d(x,y) + h(y)
 * for every edge x, y of the graph (where d denotes the length of that edge),
 * then h is called monotone, or consistent. In such a case, A* can be implemented
 * more efficiently—roughly speaking, no node needs to be processed more than once
 * (see closed set below)—and A* is equivalent to running Dijkstra's algorithm
 * with the reduced cost d'(x,y): = d(x,y) − h(x) + h(y).
 *
 * \b Examples:
 *
 *  - \example_link{01AStarPathing, Simple pathing example}
 *  - \example_link{02AnimatedPathing, Animated pathing example}
 *  - \example_link{03MultiplePaths, Multiple paths example}
 *  - \example_link{04AStarHeuristics, Heuristic example} showing the use of multiple heuristics
 *
 */

/*!\fn std::vector<Pnt3f> OctreeAStarAlgorithm::search(OctreePtr Tree,
 *                        const Pnt3f& Start,
 *                        const Pnt3f& Goal)
 * \brief Compute the A* Path between a Start and End goal, given an Octree
 * subdivition of the space.
 *
 * By default this uses a euclidean distance metric(#euclideanDistanceCost)
 * for the heuristic used by the A* algorithm. 
 *
 * \param[in] Tree The Octree subdivition of the space
 * \param[in] Start The start position
 * \param[in] Goal The goal position
 *
 * \returns A vector of points that lead from the start to the goal as
 * determined by the path planning algorithm
 */

/*!\fn std::vector<Pnt3f> OctreeAStarAlgorithm::search(OctreePtr Tree,
 *                        const Pnt3f& Start,
 *                        const Pnt3f& Goal,
 *                        PathCostHeuristicFunc CostHeuristicFunc)
 * \brief Compute the A* Path between a Start and End goal, given an Octree
 * subdivition of the space and a const heuristic functor.
 *
 * \param[in] Tree The Octree subdivition of the space
 * \param[in] Start The start position
 * \param[in] Goal The goal position
 * \param[in] CostHeuristicFunc A Functor to a method for use as the cost
 * heuristic
 *
 * \returns A vector of points that lead from the start to the goal as
 * determined by the path planning algorithm
 */

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

