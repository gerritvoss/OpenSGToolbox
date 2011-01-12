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
    /*==========================  PUBLIC  =================================*/
  public:

    typedef boost::function<Real32 (OctreePtr,
                                    Octree::OTNodePtr,
                                    const Pnt3f& Goal)> PathCostHeuristicFunc;

    /*---------------------------------------------------------------------*/
    /*! \name Search                                                       */
    /*! \{                                                                 */
    std::vector<Pnt3f> search(OctreePtr Tree,
                              const Pnt3f& Start,
                              const Pnt3f& Goal);

    std::vector<Pnt3f> search(OctreePtr Tree,
                              const Pnt3f& Start,
                              const Pnt3f& Goal,
                              PathCostHeuristicFunc CostHeuristicFunc);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    OctreeAStarAlgorithm(void);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name Cost Heuristic Methods                                       */
    /*! \{                                                                 */
    static Real32 euclideanDistanceCost(Octree::OTNodePtr, const Pnt3f&, Real32 CostPerUnit);
    static Real32 manhattanDistanceCost(Octree::OTNodePtr, const Pnt3f&, Real32 CostPerUnit);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    struct ASNode;

    typedef boost::shared_ptr<ASNode> ASNodePtr;
    typedef boost::weak_ptr<ASNode> ASNodeWeakPtr;

    struct ASNode
    {
        Real32 _CostFromStart;
        Real32 _CostToGoal;
        ASNodeWeakPtr _Parent;
        Octree::OTNodePtr _OctreeNode;
    };


    /*---------------------------------------------------------------------*/
    /*! \name Algorithm helpers                                            */
    /*! \{                                                                 */
    void constructPath(ASNodePtr);
    Int32 inOpen(const Octree::OTNodePtr);
    Int32 inClosed(const Octree::OTNodePtr);
    void pushOnOpen(ASNodePtr);
    /*! \}                                                                 */


    std::vector<ASNodePtr> _OpenNodes;
    std::vector<ASNodePtr> _ClosedNodes;

    std::vector<Pnt3f>     _SolutionPath;
    Octree::OTNodePtr      _StartNode;
    Octree::OTNodePtr      _GoalNode;
    OctreePtr              _Tree;

    PathCostHeuristicFunc  _CostHeuristicFunc;
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#endif // _OSGOCTREEASTARALGORITHM_H_
