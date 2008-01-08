/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Aaron Cronk                                      *
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

#ifndef _OSGDEFAULTTREESELECTIONMODEL_H_
#define _OSGDEFAULTTREESELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractTreeSelectionModel.h"
#include "Component/Tree/OSGTreeRowMapper.h"
#include <vector>
#include <list>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeSelectionModel class. See \ref 
           PageUserInterfaceDefaultTreeSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultTreeSelectionModel : public AbstractTreeSelectionModel
{
    /*==========================  PUBLIC  =================================*/
  public:
    DefaultTreeSelectionModel(void);

	//Adds path to the current selection.
	virtual void addSelectionPath(TreePath path);

	//Adds paths to the current selection.
	virtual void addSelectionPaths(std::vector<TreePath> paths);

	//Changes the values of _AnchorSelectionIndex, _LeadSelectionIndex, _MaxSelectionIndex, and _MinSelectionIndex to current values of selection.
	virtual void changeValues(std::vector<TreePath> paths);

	//Empties the current selection.
	virtual void clearSelection(void);

	//Returns the last path that was added.
	virtual TreePath getLeadSelectionPath(void) const;

	//Returns the lead selection index.
	virtual UInt32 getLeadSelectionRow(void) const;

	//Returns the largest value obtained from the TreeRowMapper for the current set of selected TreePaths.
	virtual UInt32 getMaxSelectionRow(void) const;

	//Returns the smallest value obtained from the TreeRowMapper for the current set of selected TreePaths.
	virtual UInt32 getMinSelectionRow(void) const;

	//Returns the TreeRowMapper instance that is able to map a TreePath to a row.
	virtual TreeRowMapperPtr getRowMapper(void) const;

	//Returns the number of paths that are selected.
	virtual UInt32 getSelectionCount(void) const;

	//Returns the current selection mode, one of SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
	virtual UInt32 getSelectionMode(void) const;

	//Returns the first path in the selection.
	virtual TreePath getSelectionPath(void) const;

	//Returns the paths in the selection.
	virtual std::vector<TreePath> getSelectionPaths(void) const;

	//Returns all of the currently selected rows.
	virtual std::vector<UInt32> getSelectionRows(void) const;

	//Returns true if the path, path, is in the current selection.
	virtual bool isPathSelected(std::vector<TreePath> path) const;

	//Returns true if paths is Contiguous
	virtual bool arePathsContiguous(const std::vector<TreePath>& paths) const;

	//Returns true if paths1 is Contiguous with paths2
	virtual bool arePathsContiguous(const std::vector<TreePath>& paths1, const std::vector<TreePath>& paths2) const;

	//Returns true if the row identified by row is selected.
	virtual bool isRowSelected(const UInt32& row) const;

	//Returns true if the selection is currently empty.
	virtual bool isSelectionEmpty(void) const;

	//Removes path from the selection.
	virtual void removeSelectionPath(TreePath path);

	//Removes paths from the selection.
	virtual void removeSelectionPaths(std::vector<TreePath> paths);

	//Updates this object's mapping from TreePaths to rows.
	//virtual void resetRowSelection(void);

	//Sets the TreeRowMapper instance.
	virtual void setRowMapper(TreeRowMapperPtr newMapper);

	//Sets the selection model, which must be one of SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
	virtual void setSelectionMode(const UInt32& mode);

	//Sets the selection to path.
	virtual void setSelectionPath(TreePath path);

	//Sets the selection to path.
	virtual void setSelectionPaths(std::vector<TreePath> paths);

  protected:
	  typedef std::vector<TreePath> SelectionVector;
	  typedef SelectionVector::const_iterator SelectionVectorConstItor;
	  
	  SelectionVector _Selection;

	  UInt32	_SelectionMode;
	  UInt32 	_LeadSelectionIndex;
	  UInt32 	_MaxSelectionIndex;
	  UInt32 	_MinSelectionIndex;

	  TreeRowMapperPtr _TreeRowMapper;
	  TreePathPtr _TreePath;

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultTreeSelectionModel *DefaultTreeSelectionModelPtr;

OSG_END_NAMESPACE

#define OSGDEFAULTTREESELECTIONMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTTREESELECTIONMODEL_H_ */
