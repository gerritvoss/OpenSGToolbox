/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#ifndef _OSGABSTRACTTREEMODELLAYOUT_H_
#define _OSGABSTRACTTREEMODELLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractTreeModelLayoutBase.h"
#include "OSGTreeModelEventDetailsFields.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeModelLayout class. See \ref
           PageContribUserInterfaceAbstractTreeModelLayout for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractTreeModelLayout : public AbstractTreeModelLayoutBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractTreeModelLayoutBase Inherited;
    typedef AbstractTreeModelLayout     Self;

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

	//Returns the rows that the TreePath instances in path are being displayed at.
	virtual std::vector<Int32> getRowsForPaths(const std::vector<TreePath>& paths) const;
    
    //Returns true if the children of the path are visible
	virtual bool areChildrenVisible(const TreePath& path) const;

	//Returns the TreeModel that is providing the data.
	virtual TreeModel* getModel(void) const;

	//Returns the object that renders nodes in the tree, and which is responsible for calculating the dimensions of individual nodes.
	//virtual AbstractLayoutCache.NodeDimensions getNodeDimensions(void) const;

	//Returns the preferred height.
	virtual Real32 getPreferredHeight(void) const;

	//Returns the preferred width for the passed in region.
	virtual Real32 getPreferredWidth(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

	//Returns the height of each row.
	virtual Real32 getRowHeight(void) const;

	virtual Real32 getDepthOffset(void) const;

	//Returns the model used to maintain the selection.
	virtual TreeSelectionModel* getSelectionModel(void) const;
    
	//Returns the Visible Paths
    virtual std::vector<TreePath> getVisiblePaths(void) const;

	//Returns the Expanded Paths
    virtual std::vector<TreePath> getExpandedPaths(void) const;

	//Returns true if the root node of the tree is displayed.
	virtual bool isRootVisible(void) const;

	//Makes sure that all the nodes in path are expanded making the last node in the
    //path visible
	virtual void setVisible(const TreePath& path);

	//Sets the TreeModel that will provide the data.
	virtual void setModel(TreeModel* const newModel);

	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const Real32& rowHeight);

	//Sets the offset of each depth.
	virtual void setDepthOffset(const Real32& depthOffset);

	//Sets the TreeSelectionModel used to manage the selection to new LSM.
	virtual void setSelectionModel(TreeSelectionModel* const newLSM);

	//Returns true if the height of each row is a fixed size.
	virtual bool isFixedRowHeight(void) const;
	
	//Tells the ModelLayout to veto the expantion of the given TreePath
	virtual void vetoPathExpantion(const TreePath& Path);

	//Tells the ModelLayout to veto the collapse of the given TreePath
	virtual void vetoPathCollapse(const TreePath& Path);
    
    //Fills VisibleDecendents will all of the TreePaths to nodes that are visible decendents of Path
    virtual void getVisibleDecendants(const TreePath& Path, std::vector<TreePath>& VisibleDecendants) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractTreeModelLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractTreeModelLayout(void);
    AbstractTreeModelLayout(const AbstractTreeModelLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractTreeModelLayout(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    //Returns, by reference in placeIn, the size needed to represent value.
	virtual void getNodeDimensions(Pnt2f& TopLeft,
                                   Pnt2f& BottomRight,
                                   const boost::any& value,
                                   const UInt32& row,
                                   const UInt32& depth,
                                   bool expanded,
                                   Pnt2f TopLeftPlaceIn,
                                   Pnt2f BottomRightPlaceIn);

    //Object responsible for getting the size of a node.
    //AbstractLayoutCache.NodeDimensions nodeDimensions;

    //Model providing information.
    TreeModelRefPtr _TreeModel;

    //Selection model.
    TreeSelectionModelRecPtr _TreeSelectionModel;

    typedef std::set<TreePath, TreePath::BreadthFirstFunctional> TreePathSet;
    typedef TreePathSet::iterator TreePathSetItor;
    typedef TreePathSet::const_iterator TreePathSetConstItor;

    TreePathSet _ExpandedPathSet;
    TreePathSet _VisiblePathSet;

    void handleTreeNodesChanged(TreeModelEventDetails* const e);
    void handleTreeNodesInserted(TreeModelEventDetails* const e);
    void handleTreeNodesWillBeRemoved(TreeModelEventDetails* const e);
    void handleTreeNodesRemoved(TreeModelEventDetails* const e);
    void handleTreeStructureChanged(TreeModelEventDetails* const e);
    boost::signals2::connection _TreeNodesChangedConnection,
                                _TreeNodesInsertedConnection,
                                _TreeNodesWillBeRemovedConnection,
                                _TreeNodesRemovedConnection,
                                _TreeStructureChangedConnection;

    void produceTreeCollapsed(const TreePath& Path);
    void produceTreeExpanded(const TreePath& Path);
    void produceTreeWillCollapse(const TreePath& Path);
    void produceTreeWillExpand(const TreePath& Path);

    bool _VetoPathExpantion;
    bool _VetoPathCollapse;

    void insertVisiblePath(const TreePath& Path);
    void removeVisiblePath(const TreePath& Path);
    void removeExpandedPath(const TreePath& Path);

    void produceTreeNodesChanged(TreeModelEventDetails* const e);
    void produceTreeNodesInserted(TreeModelEventDetails* const e);
    void produceTreeNodesWillBeRemoved(TreeModelEventDetails* const e);
    void produceTreeNodesRemoved(TreeModelEventDetails* const e);
	void produceTreeStructureChanged(TreeModelEventDetails* const e);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractTreeModelLayoutBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractTreeModelLayout &source);
};

typedef AbstractTreeModelLayout *AbstractTreeModelLayoutP;

OSG_END_NAMESPACE

#include "OSGAbstractTreeModelLayoutBase.inl"
#include "OSGAbstractTreeModelLayout.inl"

#endif /* _OSGABSTRACTTREEMODELLAYOUT_H_ */
