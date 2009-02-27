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
TreePath::NodePairType TreePath::getLastPathComponent(void) const
{
	return _Path.back();
}

inline
TreePath TreePath::getParentPath(void) const
{
	return TreePath(_Path, _Path.size() - 1);
}

inline
TreePath::PathVectorType TreePath::getPath(void) const
{
	return _Path;
}

inline
TreePath::NodePairType TreePath::getPathComponent(const UInt32& Index) const
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
bool TreePath::operator!=(const TreePath& Right) const
{
    return !(operator==(Right));
}

inline
bool TreePath::operator<=(const TreePath& RightPath) const
{
    return (operator==(RightPath) || operator<(RightPath));
}

inline
bool TreePath::operator>(const TreePath& RightPath) const
{
    return !operator<=(RightPath);
}

inline
bool TreePath::operator>=(const TreePath& RightPath) const
{
    return (operator==(RightPath) || operator>(RightPath));
}

inline
TreePath::NodePairType::NodePairType(const boost::any& Value, UInt32 Index)
: _NodeValue(Value), _NodeIndex(Index)
{
}

inline
TreePath::NodePairType::NodePairType(const NodePairType& Value)
: _NodeValue(Value._NodeValue), _NodeIndex(Value._NodeIndex)
{
}

inline
TreePath::NodePairType::NodePairType(void)
: _NodeValue(), _NodeIndex(0)
{
}

OSG_END_NAMESPACE

#define OSGTREEPATH_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

