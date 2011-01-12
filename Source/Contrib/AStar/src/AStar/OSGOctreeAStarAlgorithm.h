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
#ifndef _OSGOCTREEASTARALGORITHM_H_
#define _OSGOCTREEASTARALGORITHM_H_

#include "OSGConfig.h"
#include "OSGContribAStarDef.h"
#include "OSGBaseTypes.h"

#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBASTAR_DLLMAPPING OctreeAStarAlgorithm
{
  public:
    OctreeAStarAlgorithm(void);

    typedef boost::function<Real32 (OctreePtr,
                                    const Octree::OTNodePtr,
                                    const Pnt3f& Goal)> PathCostHeuristicFunc;

    void setCostHeuristic(PathCostHeuristicFunc CostHeuristicFunc);

    std::vector<Pnt3f> search(OctreePtr Tree,const Pnt3f& Start,const Pnt3f& Goal);

    const std::vector<Pnt3f>& getPath(void) const;

  protected:

    struct ASNode;

    typedef boost::shared_ptr<ASNode> ASNodePtr;
    typedef boost::weak_ptr<ASNode> ASNodeWeakPtr;

    struct ASNode
    {
        Real32 costFromStart;
        Real32 costToGoal;
        Real32 totalCost;
        ASNodeWeakPtr parent;
        Octree::OTNodePtr OT_Node;
    };

    void setAgent(Octree::OTNodePtr);
    void setGoal(Octree::OTNodePtr);

    void setTree(OctreePtr Tree);

    void setAgent(const Pnt3f& Location);
    void setGoal(const Pnt3f& Location);

    Real32 findCostToGoal(const Pnt3f&);
    Real32 findCostFromStart(const Pnt3f&);
    void constructPath(ASNodePtr);
    Int32 inOpen(const Octree::OTNodePtr);
    Int32 inClosed(const Octree::OTNodePtr);
    void pushOnOpen(ASNodePtr);


    //instance variables
    std::vector<ASNodePtr> open, closed;//, path;
    std::vector<Pnt3f> path;
    Octree::OTNodePtr agent, goal;
    OctreePtr _Tree;

    PathCostHeuristicFunc _CostHeuristicFunc;
  private:
};

OSG_END_NAMESPACE

#endif // _OSGOCTREEASTARALGORITHM_H_
