/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGTree.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Tree
A UI Tree. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Tree::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Tree::addSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
}

void Tree::addSelectionPath(TreePath path)
{
    //TODO:Implement
}

void Tree::addSelectionPaths(std::vector<TreePath> paths)
{
    //TODO:Implement
}

void Tree::addSelectionRow(const UInt32& row)
{
    //TODO:Implement
}

void Tree::addSelectionRows(std::vector<UInt32> rows)
{
    //TODO:Implement
}




void Tree::cancelEditing(void)
{
    //TODO:Implement
}

void Tree::clearSelection(void)
{
    //TODO:Implement
}

void Tree::collapsePath(TreePath path)
{
    //TODO:Implement
}

void Tree::collapseRow(const UInt32& row)
{
    //TODO:Implement
}


void Tree::expandPath(TreePath path)
{
    //TODO:Implement
}

void Tree::expandRow(const UInt32& row)
{
    //TODO:Implement
}





TreePath Tree::getAnchorSelectionPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

TreePath Tree::getClosestPathForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

Int32 Tree::getClosestRowForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return 0;
}

TreePath Tree::getEditingPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}


bool Tree::getExpandsSelectedPaths(void) const
{
    //TODO:Implement
    return false;
}

SharedFieldPtr Tree::getLastSelectedPathComponent(void) const
{
    //TODO:Implement
    return SharedFieldPtr();
}

TreePath Tree::getLeadSelectionPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

Int32 Tree::getLeadSelectionRow(void) const
{
    //TODO:Implement
    return 0;
}

Int32 Tree::getMaxSelectionRow(void) const
{
    //TODO:Implement
    return 0;
}

Int32 Tree::getMinSelectionRow(void) const
{
    //TODO:Implement
    return 0;
}

TreeModelPtr Tree::getModel(void) const
{
    //TODO:Implement
    return NULL;
}



TreePath Tree::getPathForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

TreePath Tree::getPathForRow(const UInt32& row) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}


Int32 Tree::getRowCount(void) const
{
    //TODO:Implement
    return 0;
}

Int32 Tree::getRowForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return 0;
}

Int32 Tree::getRowForPath(TreePath path) const
{
    //TODO:Implement
    return 0;
}

UInt32 Tree::getSelectionCount(void) const
{
    //TODO:Implement
    return 0;
}

TreeSelectionModelPtr Tree::getSelectionModel(void) const
{
    //TODO:Implement
    return NULL;
}

TreePath Tree::getSelectionPath(void) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

std::vector<TreePath> Tree::getSelectionPaths(void) const
{
    //TODO:Implement
    return std::vector<TreePath>();
}

std::vector<UInt32> Tree::getSelectionRows(void) const
{
    //TODO:Implement
    return std::vector<UInt32>();
}

Int32 Tree::getVisibleRowCount(void) const
{
    //TODO:Implement
    return 0;
}

bool Tree::hasBeenExpanded(TreePath path) const
{
    //TODO:Implement
    return false;
}

bool Tree::isCollapsed(const UInt32& row) const
{
    //TODO:Implement
    return false;
}

bool Tree::isCollapsed(TreePath path) const
{
    //TODO:Implement
    return false;
}

bool Tree::isEditing(void) const
{
    //TODO:Implement
    return false;
}

bool Tree::isExpanded(const UInt32& row) const
{
    //TODO:Implement
    return false;
}

bool Tree::isExpanded(TreePath path) const
{
    //TODO:Implement
    return false;
}

bool Tree::isFixedRowHeight(void) const
{
    //TODO:Implement
    return false;
}

bool Tree::isPathEditable(TreePath path) const
{
    //TODO:Implement
    return false;
}

bool Tree::isPathSelected(TreePath path) const
{
    //TODO:Implement
    return false;
}

bool Tree::isRowSelected(const UInt32& row) const
{
    //TODO:Implement
    return false;
}

bool Tree::isSelectionEmpty(void) const
{
    //TODO:Implement
    return false;
}

bool Tree::isVisible(TreePath path) const
{
    //TODO:Implement
    return false;
}

void Tree::makeVisible(TreePath path)
{
    //TODO:Implement
}

void Tree::removeSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
}

void Tree::removeSelectionPath(TreePath path)
{
    //TODO:Implement
}

void Tree::removeSelectionPaths(std::vector<TreePath> paths)
{
    //TODO:Implement
}

void Tree::removeSelectionRow(const UInt32& row)
{
    //TODO:Implement
}

void Tree::removeSelectionRows(std::vector<UInt32> rows)
{
    //TODO:Implement
}




void Tree::scrollPathToVisible(TreePath path)
{
    //TODO:Implement
}

void Tree::scrollRowToVisible(const UInt32& row)
{
    //TODO:Implement
}

void Tree::setAnchorSelectionPath(TreePath newPath)
{
    //TODO:Implement
}

void Tree::setDragEnabled(bool b)
{
    //TODO:Implement
}

void Tree::setExpandsSelectedPaths(bool newValue)
{
    //TODO:Implement
}

void Tree::setLeadSelectionPath(TreePath newPath)
{
    //TODO:Implement
}

void Tree::setModel(TreeModelPtr newModel)
{
    //TODO:Implement
}

void Tree::setSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
}

void Tree::setSelectionModel(TreeSelectionModelPtr selectionModel)
{
    //TODO:Implement
}

void Tree::setSelectionPath(TreePath path)
{
    //TODO:Implement
}

void Tree::setSelectionPaths(std::vector<TreePath> paths)
{
    //TODO:Implement
}

void Tree::setSelectionRow(const UInt32& row)
{
    //TODO:Implement
}

void Tree::setSelectionRows(std::vector<UInt32> rows)
{
    //TODO:Implement
}

void Tree::setVisibleRowCount(const UInt32& newCount)
{
    //TODO:Implement
}

void Tree::startEditingAtPath(TreePath path)
{
    //TODO:Implement
}

bool Tree::stopEditing(void)
{
    //TODO:Implement
    return false;
}

void Tree::treeDidChange(void)
{
    //TODO:Implement
}

Vec2s Tree::getPreferredScrollableViewportSize(void)
{
    //TODO:Implement
    return Vec2s();
}

Int32 Tree::getScrollableBlockIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    //TODO:Implement
    return 0;
}

bool Tree::getScrollableTracksViewportHeight(void)
{
    //TODO:Implement
    return false;
}

bool Tree::getScrollableTracksViewportWidth(void)
{
    //TODO:Implement
    return false;
}

Int32 Tree::getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    //TODO:Implement
    return 0;
}

void Tree::clearToggledPaths(void)
{
    //TODO:Implement
}




TreeModelPtr Tree::getDefaultTreeModel(void)
{
    //TODO:Implement
    return NULL;
}

std::vector<TreePath> Tree::getDescendantToggledPaths(TreePath parent)
{
    //TODO:Implement
    return std::vector<TreePath>();
}

std::vector<TreePath> Tree::getPathBetweenRows(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
    return std::vector<TreePath>();
}

bool Tree::removeDescendantSelectedPaths(TreePath path, bool includePath)
{
    //TODO:Implement
    return false;
}

void Tree::removeDescendantToggledPaths(std::vector<TreePath> toRemove)
{
    //TODO:Implement
}

void Tree::setExpandedState(TreePath path, bool state)
{
    //TODO:Implement
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Tree::Tree(void) :
    Inherited(),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this))
{
}

Tree::Tree(const Tree &source) :
    Inherited(source),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this))
{
}

Tree::~Tree(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Tree::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Tree::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Tree NI" << std::endl;
}

void Tree::ModelListener::treeNodesChanged(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeNodesInserted(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeNodesRemoved(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::ModelListener::treeStructureChanged(TreeModelEvent e)
{
    //TODO: Implement
}

void Tree::SelectionListener::valueChanged(TreeSelectionEvent e)
{
    //TODO: Implement
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGTREEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTREEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTREEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

