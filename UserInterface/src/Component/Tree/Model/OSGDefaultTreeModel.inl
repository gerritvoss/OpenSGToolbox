/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void DefaultTreeModel::setAsksAllowsChildren(bool newValue)
{
    _AskAllowsChilren = newValue;
}


inline
void DefaultTreeModel::reload(void)
{
    nodeChanged(_Root);
}

inline
void DefaultTreeModel::reload(TreeNodePtr node)
{
    nodeChanged(node);
}

inline
void DefaultTreeModel::nodesWereRemoved(TreeNodePtr node, std::vector<UInt32> childIndices, std::vector<SharedFieldPtr> removedChildren)
{
    produceTreeNodesRemoved(node->getPath(), childIndices, removedChildren);
}

inline
bool DefaultTreeModel::asksAllowsChildren(void)
{
    return _AskAllowsChilren;
}

inline
std::vector<MutableTreeNodePtr> DefaultTreeModel::getPathToRoot(TreeNodePtr aNode)
{
    return std::vector<MutableTreeNodePtr>();
}

OSG_END_NAMESPACE


