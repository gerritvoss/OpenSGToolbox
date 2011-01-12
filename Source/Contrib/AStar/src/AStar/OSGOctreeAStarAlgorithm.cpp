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

void OctreeAStarAlgorithm::setAgent(Octree::OTNodePtr node)
{
	agent = node;
}

void OctreeAStarAlgorithm::setGoal(Octree::OTNodePtr node)
{
	goal = node;
}

void OctreeAStarAlgorithm::setAgent(const Pnt3f& Location)
{
    setAgent(_Tree->getNodeThatContains(Location));
}

void OctreeAStarAlgorithm::setGoal(const Pnt3f& Location)
{
    setGoal(_Tree->getNodeThatContains(Location));
}

void OctreeAStarAlgorithm::setTree(OctreePtr Tree)
{
    _Tree = Tree; 
}

void OctreeAStarAlgorithm::setCostHeuristic(PathCostHeuristicFunc CostHeuristicFunc)
{
    _CostHeuristicFunc = CostHeuristicFunc;
}

std::vector<Pnt3f> OctreeAStarAlgorithm::search(OctreePtr Tree,const Pnt3f& Start,const Pnt3f& Goal)
{
    setTree(Tree);
    setAgent(Start);
    setGoal(Goal);

    if(!agent ||
       !goal)
    {
        return path;
    }

	//clear lists
    path.clear();
	open.clear();
	closed.clear();

	//initialize start node
	ASNodePtr startNode = ASNodePtr(new ASNode);
	startNode->OT_Node = agent;
	startNode->costFromStart = 0;
    Pnt3f Center;
    agent->getVolume().getCenter(Center);
	startNode->costToGoal = findCostToGoal(Center);
	startNode->parent.reset();
	startNode->totalCost = startNode->costToGoal + startNode->costToGoal;
	open.push_back(startNode);

	while(!open.empty())
    {
		ASNodePtr Node = open.front();
		open.erase(open.begin());

		if(Node->OT_Node == goal)
        {
			constructPath(Node);
			return path;//success
		}
        else
        {
			for(Int8 i = 0; i < Node->OT_Node->getNeighbors().size(); ++i)
            {
				if(!Node->OT_Node->getNeighbor(i)->getContainsObstacles())
                {//Node->OT_Node->getNeighbor(i)->children.size() == 0
                    Node->OT_Node->getNeighbor(i)->getVolume().getCenter(Center);
					Real32 NewCost = Node->costFromStart + findCostFromStart(Center);
					Int32 locInOpen = inOpen(Node->OT_Node->getNeighbor(i));
					Int32 locInClosed = inClosed(Node->OT_Node->getNeighbor(i));
					if((locInOpen >= 0 && open[locInOpen]->costFromStart <= NewCost) || (locInClosed >= 0 && closed[locInClosed]->costFromStart <= NewCost))
                    {
						continue;
					}
                    else
                    {
						//initialize a new node
						ASNodePtr NewNode = ASNodePtr(new ASNode);
						NewNode->OT_Node = Node->OT_Node->getNeighbor(i);
                        NewNode->OT_Node->getVolume().getCenter(Center);
						NewNode->costFromStart = findCostFromStart(Center);
						NewNode->costToGoal = findCostToGoal(Center);
						NewNode->parent = Node;
						NewNode->totalCost = NewNode->costFromStart + NewNode->costToGoal;

						if(locInClosed >= 0)
                        {
							closed.erase(closed.begin() + locInClosed);
						}
						/*if(locInOpen >= 0)
                         * {
							open.erase(open.begin() + locInOpen);
						}else{
							pushOnOpen(NewNode);
						}*/
						if(locInOpen >= 0)
                        {
							open.erase(open.begin() + locInOpen);
						}
						pushOnOpen(NewNode);

					}//endif
				}//endif...
			}//end for loop...dont with Node
		}//endif

		closed.push_back(Node);
	}//end while loop

	return path;
}

const std::vector<Pnt3f>& OctreeAStarAlgorithm::getPath(void) const 
{
	return path;
}

//protected functions
Real32 OctreeAStarAlgorithm::findCostToGoal(const Pnt3f& pos)
{
	Real32 tCost = 1;
    Pnt3f Center;
    goal->getVolume().getCenter(Center);
	return tCost * pos.dist(Center);
}

Real32 OctreeAStarAlgorithm::findCostFromStart(const Pnt3f& pos)
{
	Real32 tCost = 1;
    Pnt3f Center;
    agent->getVolume().getCenter(Center);
	return tCost * pos.dist(Center);
}

void OctreeAStarAlgorithm::constructPath(ASNodePtr node)
{
	ASNodePtr temp = node;

    std::deque<Pnt3f> ThePath;
    Pnt3f Center;
	while(temp)
    {
        temp->OT_Node->getVolume().getCenter(Center);
		ThePath.push_front(Center);
        if(!temp->parent.expired())
        {
            temp = ASNodePtr(temp->parent);
        }
        else
        {
            temp.reset();
        }
	}
    path.insert(path.end(), ThePath.begin(), ThePath.end());

}

Int32 OctreeAStarAlgorithm::inOpen(const Octree::OTNodePtr node)
{
	for(Int32 i = 0; i < open.size(); ++i)
    {
		if(open[i]->OT_Node == node)
        {
			return i;
        }
	}

	return -1;
}

Int32 OctreeAStarAlgorithm::inClosed(const Octree::OTNodePtr node)
{
	for(Int32 i = 0; i < closed.size(); ++i)
    {
		if(closed[i]->OT_Node == node)
        {
			return i;
        }
	}

	return -1;
}

void OctreeAStarAlgorithm::pushOnOpen(ASNodePtr node)
{
	for(Int32 i = 0; i < open.size(); ++i)
    {
		//either cfs or total cost
		if(node->costFromStart <= open[i]->costFromStart)
        {
			open.insert(open.begin() + i, node);
			return;
		}
	}
	open.push_back(node);
}

OSG_END_NAMESPACE

