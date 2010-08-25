/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Aaron Cronk                *
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

#include "OSGDefaultTreeSelectionModelBase.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeSelectionModel class. See \ref
           PageContribUserInterfaceDefaultTreeSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTreeSelectionModel : public DefaultTreeSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTreeSelectionModelBase Inherited;
    typedef DefaultTreeSelectionModel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	//Adds path to the current selection.
	virtual void addSelectionPath(TreePath path);
	virtual void addSelectionRow(Int32 Row);

	//Adds paths to the current selection.
	virtual void addSelectionPaths(std::vector<TreePath> paths);
	virtual void addSelectionRows(std::vector<Int32> Rows);

	//Empties the current selection.
	virtual void clearSelection(void);

	//Sets the Lead Selection Path
	virtual void setLeadSelectionPath(const TreePath& path);

	//Sets the Lead Selection Row
	virtual void setLeadSelectionRow(Int32 Row);

	//Sets the Anchor Selection Path
	virtual void setAnchorSelectionPath(const TreePath& path);

	//Sets the Anchor Selection Row
	virtual void setAnchorSelectionRow(Int32 Row);

	//Returns the last path that was added.
	virtual TreePath getLeadSelectionPath(void) const;

	//Returns the lead selection index.
	virtual Int32 getLeadSelectionRow(void) const;

	//Returns the Anchor Path
	virtual TreePath getAnchorSelectionPath(void) const;

	//Returns the anchor selection index.
	virtual Int32 getAnchorSelectionRow(void) const;

	//Returns the largest value obtained from the TreeRowMapper for the current set of selected TreePaths.
	virtual Int32 getMaxSelectionRow(void) const;

	//Returns the smallest value obtained from the TreeRowMapper for the current set of selected TreePaths.
	virtual Int32 getMinSelectionRow(void) const;

	//Returns the TreeRowMapper instance that is able to map a TreePath to a row.
	virtual TreeRowMapper* getRowMapper(void) const;

	//Returns the number of paths that are selected.
	virtual UInt32 getSelectionCount(void) const;

	//Returns the current selection mode, one of SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
	virtual UInt32 getSelectionMode(void) const;

	//Returns the first path in the selection.
	virtual TreePath getSelectionPath(void) const;
	virtual Int32 getSelectionRow(void) const;

	//Returns the paths in the selection.
	virtual std::vector<TreePath> getSelectionPaths(void) const;

	//Returns all of the currently selected rows.
	virtual std::vector<Int32> getSelectionRows(void) const;

	//Returns true if the path, path, is in the current selection.
	virtual bool isPathSelected(std::vector<TreePath> path) const;
	virtual bool isPathSelected(TreePath path) const;

	//Returns true if the row identified by row is selected.
	virtual bool isRowSelected(const Int32& row) const;

	//Returns true if the selection is currently empty.
	virtual bool isSelectionEmpty(void) const;

	//Removes path from the selection.
	virtual void removeSelectionPath(TreePath path);
	virtual void removeSelectionRow(Int32 Row);

	//Removes paths from the selection.
	virtual void removeSelectionPaths(std::vector<TreePath> paths);
	virtual void removeSelectionRows(std::vector<Int32> Rows);

	//Updates this object's mapping from TreePaths to rows.
	//virtual void resetRowSelection(void);

	//Sets the TreeRowMapper instance.
	virtual void setRowMapper(TreeRowMapper* const newMapper);

	//Sets the selection model, which must be one of SINGLE_TREE_SELECTION, CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
	virtual void setSelectionMode(const UInt32& mode);

	//Sets the selection to path.
	virtual void setSelectionPath(TreePath path);
	virtual void setSelectionRow(Int32 Row);

	//Sets the selection to path.
	virtual void setSelectionPaths(std::vector<TreePath> paths);
	virtual void setSelectionRows(std::vector<Int32> Rows);

    //Sets the selection to the Interval from StartRow to EndRow
    virtual void setSelectionInterval(const Int32& index0, const Int32& index1);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultTreeSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTreeSelectionModel(void);
    DefaultTreeSelectionModel(const DefaultTreeSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTreeSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    typedef std::set<TreePath, TreePath::BreadthFirstFunctional> TreePathSet;
    void toRowNumberSet(NumberSet& Result, const TreePathSet& PathSet) const;
    
    void updateMinMax(void);
    Int32 getMinRow(const TreePathSet& PathSet) const;
    Int32 getMaxRow(const TreePathSet& PathSet) const;
    TreePathSet getMinimumContiguousSelection(const TreePathSet& PathSet) const;

    void produceEvents(const TreePathSet& PreSelectedSet, const TreePathSet& PostSelectedSet, Int32 OldLeadSelectionIndex);
    TreePathSet _SelectionSet;

    TreeSelectionMode _SelectionMode;
    Int32 	_AnchorSelectionIndex;
    Int32 	_LeadSelectionIndex;
    Int32 	_MaxSelectionIndex;
    Int32 	_MinSelectionIndex;
    bool 	_ValueIsAdjusting;

    TreeRowMapperRefPtr _TreeRowMapper;
    TreePathPtr _TreePath;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTreeSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTreeSelectionModel &source);
};

typedef DefaultTreeSelectionModel *DefaultTreeSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultTreeSelectionModelBase.inl"
#include "OSGDefaultTreeSelectionModel.inl"

#endif /* _OSGDEFAULTTREESELECTIONMODEL_H_ */
