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

OSG_BEGIN_NAMESPACE

inline
boost::any TreePath::getLastPathComponent(void) const
{
	return _Path.back();
}

inline
TreePath TreePath::getParentPath(void) const
{
	return TreePath(*this, _Path.size() - 1);
}

inline
boost::any TreePath::getPathComponent(const UInt32& Index) const
{
	return _Path[Index];
}

inline
UInt32 TreePath::getPathCount(void) const
{
	return _Path.size();
}

inline
UInt32 TreePath::getDepth(void) const
{
    return _Path.size();
}


inline
bool TreePath::isAncestor(const TreePath& aTreePath) const
{
    return aTreePath.isDescendant(*this);
}

inline
bool TreePath::isSibling(const TreePath& aTreePath) const
{
    return (getParentPath() == aTreePath.getParentPath());
}

inline
bool TreePath::operator<(const TreePath& Right) const
{
    return breadthFirstLessThan(Right);
}

inline
bool TreePath::operator!=(const TreePath& Right) const
{
    return !(operator==(Right));
}

inline
bool TreePath::BreadthFirstFunctional::operator()(const TreePath& LeftPath,
                const TreePath& RightPath) const
{
    return LeftPath.breadthFirstLessThan(RightPath);
}

inline
bool TreePath::DepthFirstFunctional::operator()(const TreePath& LeftPath,
                const TreePath& RightPath) const
{
    return LeftPath.depthFirstLessThan(RightPath);
}

inline
TreePath TreePath::getChildPath(boost::any child) const
{
    return TreePath(*this, child);
}

OSG_END_NAMESPACE

