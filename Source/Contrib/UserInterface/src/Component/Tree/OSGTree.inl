/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
void Tree::addSelectionPath(const TreePath& path)
{
    getSelectionModel()->addSelectionPath(path);
}

inline
void Tree::addSelectionPaths(const std::vector<TreePath>& paths)
{
    getSelectionModel()->addSelectionPaths(paths);
}

inline
void Tree::addSelectionRow(const UInt32& row)
{
    addSelectionPath(getModelLayout()->getPathForRow(row));
}

inline
void Tree::clearSelection(void)
{
    getSelectionModel()->clearSelection();
}

inline
void Tree::collapsePath(const TreePath& path)
{
    getModelLayout()->setExpanded(path, false);
}

inline
void Tree::collapseRow(const UInt32& row)
{
    getModelLayout()->setExpanded(getModelLayout()->getPathForRow(row), false);
}

inline
void Tree::expandRow(const UInt32& row)
{
    getModelLayout()->setExpanded(getModelLayout()->getPathForRow(row), true);
}

inline
boost::any Tree::getLastSelectedPathComponent(void) const
{
    return getModelLayout()->getPathForRow(getSelectionModel()->getMaxSelectionRow()).getLastPathComponent();
}

inline
TreePath Tree::getLeadSelectionPath(void) const
{
    return getSelectionModel()->getLeadSelectionPath();
}

inline
Int32 Tree::getLeadSelectionRow(void) const
{
    return getSelectionModel()->getLeadSelectionRow();
}

inline
Int32 Tree::getMaxSelectionRow(void) const
{
    return getSelectionModel()->getMaxSelectionRow();
}

inline
Int32 Tree::getMinSelectionRow(void) const
{
    return getSelectionModel()->getMinSelectionRow();
}

inline
TreePath Tree::getPathForRow(const UInt32& row) const
{
    return getModelLayout()->getPathForRow(row);
}

inline
Int32 Tree::getRowCount(void) const
{
    return getModelLayout()->getRowCount();
}

inline
Int32 Tree::getRowForPath(const TreePath& path) const
{
    return getModelLayout()->getRowForPath(path);
}

inline
UInt32 Tree::getSelectionCount(void) const
{
    return getSelectionModel()->getSelectionCount();
}

inline
TreePath Tree::getSelectionPath(void) const
{
    return getSelectionModel()->getSelectionPath();
}

inline
std::vector<TreePath> Tree::getSelectionPaths(void) const
{
    return getSelectionModel()->getSelectionPaths();
}

inline
std::vector<Int32> Tree::getSelectionRows(void) const
{
    return getSelectionModel()->getSelectionRows();
}

inline
bool Tree::hasBeenExpanded(const TreePath& path) const
{
    return getModelLayout()->isExpanded(path);
}

inline
bool Tree::isCollapsed(const UInt32& row) const
{
    return !getModelLayout()->isExpanded(getModelLayout()->getPathForRow(row));
}

inline
bool Tree::isCollapsed(const TreePath& path) const
{
    return !getModelLayout()->isExpanded(path);
}

inline
bool Tree::isExpanded(const UInt32& row) const
{
    return getModelLayout()->isExpanded(getModelLayout()->getPathForRow(row));
}

inline
bool Tree::isExpanded(const TreePath& path) const
{
    return getModelLayout()->isExpanded(path);
}

inline
bool Tree::isFixedRowHeight(void) const
{
    return getModelLayout()->isFixedRowHeight();
}

inline
bool Tree::isPathSelected(const TreePath& path) const
{
    return getSelectionModel()->isPathSelected(path);
}

inline
bool Tree::isRowSelected(const UInt32& row) const
{
    return getSelectionModel()->isRowSelected(row);
}

inline
bool Tree::isSelectionEmpty(void) const
{
    return getSelectionModel()->isSelectionEmpty();
}

inline
bool Tree::isVisible(const TreePath& path) const
{
    return getModelLayout()->isVisible(path);
}

inline
void Tree::makeVisible(const TreePath& path)
{
    getModelLayout()->setVisible(path);
}

inline
void Tree::removeSelectionPath(const TreePath& path)
{
    getSelectionModel()->removeSelectionPath(path);
}

inline
void Tree::removeSelectionPaths(const std::vector<TreePath>& paths)
{
    getSelectionModel()->removeSelectionPaths(paths);
}

inline
void Tree::removeSelectionRow(const UInt32& row)
{
    getSelectionModel()->removeSelectionPath(getModelLayout()->getPathForRow(row));
}

inline
void Tree::scrollPathToVisible(const TreePath& path)
{
    scrollRowToVisible(getModelLayout()->getRowForPath(path));
}

inline
void Tree::setSelectionPath(const TreePath& path)
{
    getSelectionModel()->setSelectionPath(path);
}

inline
void Tree::setSelectionPaths(const std::vector<TreePath>& paths)
{
    getSelectionModel()->setSelectionPaths(paths);
}

inline
void Tree::setSelectionRow(const UInt32& row)
{
    getSelectionModel()->setSelectionPath(getModelLayout()->getPathForRow(row));
}

inline
bool Tree::getRootVisible(void) const
{
    return getModelLayout()->isRootVisible();
}

inline
void Tree::setRootVisible(bool Visible)
{
    getModelLayout()->setRootVisible(Visible);
}

OSG_END_NAMESPACE
