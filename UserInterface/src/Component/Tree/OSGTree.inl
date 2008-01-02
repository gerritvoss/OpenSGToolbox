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
void Tree::addSelectionPath(const TreePath& path)
{
    _SelectionModel->addSelectionPath(path);
}

inline
void Tree::addSelectionPaths(const std::vector<TreePath>& paths)
{
    _SelectionModel->addSelectionPaths(paths);
}

inline
void Tree::addSelectionRow(const UInt32& row)
{
    addSelectionPath(_TreeModelLayout->getPathForRow(row));
}

inline
void Tree::clearSelection(void)
{
    _SelectionModel->clearSelection();
}

inline
void Tree::collapsePath(const TreePath& path)
{
    _TreeModelLayout->setExpanded(path, false);
}

inline
void Tree::collapseRow(const UInt32& row)
{
    _TreeModelLayout->setExpanded(_TreeModelLayout->getPathForRow(row), false);
}

inline
void Tree::expandPath(const TreePath& path)
{
    _TreeModelLayout->setExpanded(path, true);
}

inline
void Tree::expandRow(const UInt32& row)
{
    _TreeModelLayout->setExpanded(_TreeModelLayout->getPathForRow(row), true);
}

inline
SharedFieldPtr Tree::getLastSelectedPathComponent(void) const
{
    return _TreeModelLayout->getPathForRow(_SelectionModel->getMaxSelectionRow()).getLastPathComponent();
}

inline
TreePath Tree::getLeadSelectionPath(void) const
{
    return _SelectionModel->getLeadSelectionPath();
}

inline
Int32 Tree::getLeadSelectionRow(void) const
{
    return _SelectionModel->getLeadSelectionRow();
}

inline
Int32 Tree::getMaxSelectionRow(void) const
{
    return _SelectionModel->getMaxSelectionRow();
}

inline
Int32 Tree::getMinSelectionRow(void) const
{
    return _SelectionModel->getMinSelectionRow();
}

inline
TreeModelPtr Tree::getModel(void) const
{
    return _Model;
}

inline
TreePath Tree::getPathForRow(const UInt32& row) const
{
    return _TreeModelLayout->getPathForRow(row);
}

inline
Int32 Tree::getRowCount(void) const
{
    return _TreeModelLayout->getRowCount();
}

inline
Int32 Tree::getRowForPath(const TreePath& path) const
{
    return _TreeModelLayout->getRowForPath(path);
}

inline
UInt32 Tree::getSelectionCount(void) const
{
    return _SelectionModel->getSelectionCount();
}

inline
TreeSelectionModelPtr Tree::getSelectionModel(void) const
{
    return _SelectionModel;
}

inline
TreePath Tree::getSelectionPath(void) const
{
    return _SelectionModel->getSelectionPath();
}

inline
std::vector<TreePath> Tree::getSelectionPaths(void) const
{
    return _SelectionModel->getSelectionPaths();
}

inline
std::vector<UInt32> Tree::getSelectionRows(void) const
{
    return _SelectionModel->getSelectionRows();
}

inline
bool Tree::hasBeenExpanded(const TreePath& path) const
{
    return _TreeModelLayout->isExpanded(path);
}

inline
bool Tree::isCollapsed(const UInt32& row) const
{
    return !_TreeModelLayout->isExpanded(_TreeModelLayout->getPathForRow(row));
}

inline
bool Tree::isCollapsed(const TreePath& path) const
{
    return !_TreeModelLayout->isExpanded(path);
}

inline
bool Tree::isExpanded(const UInt32& row) const
{
    return _TreeModelLayout->isExpanded(_TreeModelLayout->getPathForRow(row));
}

inline
bool Tree::isExpanded(const TreePath& path) const
{
    return _TreeModelLayout->isExpanded(path);
}

inline
bool Tree::isFixedRowHeight(void) const
{
    return _TreeModelLayout->isFixedRowHeight();
}

inline
bool Tree::isPathSelected(const TreePath& path) const
{
    return _SelectionModel->isPathSelected(path);
}

inline
bool Tree::isRowSelected(const UInt32& row) const
{
    return _SelectionModel->isRowSelected(row);
}

inline
bool Tree::isSelectionEmpty(void) const
{
    return _SelectionModel->isSelectionEmpty();
}

inline
bool Tree::isVisible(const TreePath& path) const
{
    return _TreeModelLayout->isVisible(path);
}

inline
void Tree::makeVisible(const TreePath& path)
{
    _TreeModelLayout->setVisible(path);
}

inline
void Tree::removeSelectionPath(const TreePath& path)
{
    _SelectionModel->removeSelectionPath(path);
}

inline
void Tree::removeSelectionPaths(const std::vector<TreePath>& paths)
{
    _SelectionModel->removeSelectionPaths(paths);
}

inline
void Tree::removeSelectionRow(const UInt32& row)
{
    _SelectionModel->removeSelectionPath(_TreeModelLayout->getPathForRow(row));
}

inline
void Tree::scrollPathToVisible(const TreePath& path)
{
    scrollRowToVisible(_TreeModelLayout->getRowForPath(path));
}

inline
void Tree::setSelectionPath(const TreePath& path)
{
    _SelectionModel->setSelectionPath(path);
}

inline
void Tree::setSelectionPaths(const std::vector<TreePath>& paths)
{
    _SelectionModel->setSelectionPaths(paths);
}

inline
void Tree::setSelectionRow(const UInt32& row)
{
    _SelectionModel->setSelectionPath(_TreeModelLayout->getPathForRow(row));
}

inline
Tree::ModelListener::ModelListener(TreePtr TheTree) :
_Tree(TheTree)
{
}

inline
Tree::SelectionListener::SelectionListener(TreePtr TheTree) :
_Tree(TheTree)
{
}

OSG_END_NAMESPACE

#define OSGTREE_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

