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
//#include "Component/Tree/Model/OSGDefaultTreeModel.h"

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
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(i));
    }

    addSelectionPaths(Paths);
}

void Tree::addSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(*Itor));
    }

    addSelectionPaths(Paths);
}




void Tree::cancelEditing(void)
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
    return _TreeModelLayout->getPathClosestTo(x,y);
}

Int32 Tree::getClosestRowForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return _TreeModelLayout->getRowForPath(getClosestPathForLocation(x,y));
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



TreePath Tree::getPathForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return TreePath(SharedFieldPtr());
}

Int32 Tree::getRowForLocation(const UInt32& x, const UInt32& y) const
{
    //TODO:Implement
    return 0;
}

Int32 Tree::getVisibleRowCount(void) const
{
    //TODO:Implement
    return 0;
}

bool Tree::isEditing(void) const
{
    //TODO:Implement
    return false;
}

bool Tree::isPathEditable(const TreePath& path) const
{
    //TODO:Implement
    return false;
}

void Tree::removeSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(i));
    }

    removeSelectionPaths(Paths);
}

void Tree::removeSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(*Itor));
    }

    removeSelectionPaths(Paths);
}




void Tree::scrollRowToVisible(const UInt32& row)
{
    //TODO:Implement
}

void Tree::setAnchorSelectionPath(const TreePath& newPath)
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

void Tree::setLeadSelectionPath(const TreePath& newPath)
{
    //TODO:Implement
}

void Tree::setModel(TreeModelPtr newModel)
{
    if(_Model != NULL)
    {
        _Model->removeTreeModelListener(&_ModelListener);
    }
    _Model = newModel;
    if(_Model != NULL)
    {
        _Model->addTreeModelListener(&_ModelListener);
    }
}

void Tree::setSelectionInterval(const UInt32& index0, const UInt32& index1)
{
    //Get all of the Paths coresponding to this row interval
    std::vector<TreePath> Paths;
    UInt32 MinIndex(osgMin(index0,index1)), MaxIndex(osgMax(index0,index1));
    for(UInt32 i(MinIndex) ; i<=MaxIndex ; ++i)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(i));
    }

    setSelectionPaths(Paths);
}

void Tree::setSelectionModel(TreeSelectionModelPtr selectionModel)
{
    if(_SelectionModel != NULL)
    {
        _SelectionModel->removeTreeSelectionListener(&_SelectionListener);
    }
    _SelectionModel = selectionModel;
    if(_SelectionModel != NULL)
    {
        _SelectionModel->addTreeSelectionListener(&_SelectionListener);
    }
}

void Tree::setSelectionRows(const std::vector<UInt32>& rows)
{
    //Get all of the Paths coresponding to this rows
    std::vector<TreePath> Paths;
    for(std::vector<UInt32>::const_iterator Itor(rows.begin()) ; Itor!=rows.end() ; ++Itor)
    {
        Paths.push_back(_TreeModelLayout->getPathForRow(*Itor));
    }

    setSelectionPaths(Paths);
}

void Tree::setVisibleRowCount(const UInt32& newCount)
{
    //TODO:Implement
}

void Tree::startEditingAtPath(const TreePath& path)
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
    return false;
}

bool Tree::getScrollableTracksViewportWidth(void)
{
    return true;
}

Int32 Tree::getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    //TODO:Implement
    return 0;
}

void Tree::clearToggledPaths(void)
{
    std::vector<TreePath> ExpandedPaths = _TreeModelLayout->getExpandedPaths();
    for(std::vector<TreePath>::iterator Itor(ExpandedPaths.begin()) ; Itor != ExpandedPaths.end() ; ++Itor)
    {
        _TreeModelLayout->setExpanded((*Itor), false);
    }
}




TreeModelPtr Tree::getDefaultTreeModel(void)
{
    //TODO:Implement
    return NULL;
}

std::vector<TreePath> Tree::getDescendantToggledPaths(const TreePath& parent)
{
    std::vector<TreePath> ExpandedPaths = _TreeModelLayout->getExpandedPaths();
    std::vector<TreePath> Result;
    
    for(std::vector<TreePath>::iterator Itor(ExpandedPaths.begin()) ; Itor != ExpandedPaths.end() ; ++Itor)
    {
        if(parent.isDescendant(*Itor))
        {
            Result.push_back(*Itor);
        }
    }

    return Result;
}

std::vector<TreePath> Tree::getPathBetweenRows(const UInt32& index0, const UInt32& index1)
{
    //TODO:Implement
    return std::vector<TreePath>();
}

bool Tree::removeDescendantSelectedPaths(const TreePath& path, bool includePath)
{
    bool WasPathSelected(_SelectionModel->isPathSelected(path));

    std::vector<TreePath> SelectedPaths = _SelectionModel->getSelectionPaths();
    std::vector<TreePath> PathsToRemove;
    
    for(std::vector<TreePath>::iterator Itor(SelectedPaths.begin()) ; Itor != SelectedPaths.end() ; ++Itor)
    {
        if(path.isDescendant(*Itor))
        {
            PathsToRemove.push_back(*Itor);
        }
    }

    if(includePath && WasPathSelected)
    {
        PathsToRemove.push_back(path);
    }

    _SelectionModel->removeSelectionPaths(PathsToRemove);

    return WasPathSelected;
}

void Tree::removeDescendantToggledPaths(const std::vector<TreePath>& toRemove)
{
    std::vector<TreePath> ExpandedPaths = _TreeModelLayout->getExpandedPaths();
    
    for(std::vector<TreePath>::const_iterator ToRemoveItor(toRemove.begin()) ; ToRemoveItor != toRemove.end() ; ++ToRemoveItor)
    {
        for(std::vector<TreePath>::iterator ExpandedPathsItor(ExpandedPaths.begin()) ; ExpandedPathsItor != ExpandedPaths.end() ; ++ExpandedPathsItor)
        {
            if(ToRemoveItor->isDescendant(*ExpandedPathsItor))
            {
                _TreeModelLayout->setExpanded(*ExpandedPathsItor, false);
            }
        }
    }
}

void Tree::setExpandedState(const TreePath& path, bool state)
{
    _TreeModelLayout->setVisible(path);
    _TreeModelLayout->setExpanded(path, state);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Tree::Tree(void) :
    Inherited(),
        _Model(NULL),
        _SelectionModel(NULL),
        _TreeModelLayout(NULL),
        _ModelListener(TreePtr(this)),
        _SelectionListener(TreePtr(this))
{
}

Tree::Tree(const Tree &source) :
    Inherited(source),
        _Model(source._Model),
        _SelectionModel(source._SelectionModel),
        _TreeModelLayout(NULL),
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

