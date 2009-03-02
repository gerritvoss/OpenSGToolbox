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

#ifndef _OSGABSTRACTTREEMODELLAYOUT_H_
#define _OSGABSTRACTTREEMODELLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractTreeModelLayoutBase.h"

#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeModelLayout class. See \ref 
           PageUserInterfaceAbstractTreeModelLayout for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTreeModelLayout : public AbstractTreeModelLayoutBase
{
  private:

    typedef AbstractTreeModelLayoutBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    virtual void addTreeModelLayoutListener(TreeModelLayoutListenerPtr Listener);

    virtual void removeTreeModelLayoutListener(TreeModelLayoutListenerPtr Listener);

	//Adds a listener for the TreeModelEvent posted after the tree changes.
	virtual void addTreeModelListener(TreeModelListenerPtr l);

	//Removes a listener previously added with addTreeModelListener.
	virtual void removeTreeModelListener(TreeModelListenerPtr l);

	//Returns the rows that the TreePath instances in path are being displayed at.
	virtual std::vector<Int32> getRowsForPaths(const std::vector<TreePath>& paths) const;
    
    //Returns true if the children of the path are visible
	virtual bool areChildrenVisible(const TreePath& path) const;

	//Returns the TreeModel that is providing the data.
	virtual TreeModelPtr getModel(void) const;

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
	virtual TreeSelectionModelPtr getSelectionModel(void) const;
    
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
	virtual void setModel(TreeModelPtr newModel);

	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const Real32& rowHeight);

	//Sets the offset of each depth.
	virtual void setDepthOffset(const Real32& depthOffset);

	//Sets the TreeSelectionModel used to manage the selection to new LSM.
	virtual void setSelectionModel(TreeSelectionModelPtr newLSM);

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
    //Returns, by reference in placeIn, the size needed to represent value.
	virtual void getNodeDimensions(Pnt2f& TopLeft, Pnt2f& BottomRight, const boost::any& value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn);


    //Object responsible for getting the size of a node.
    //AbstractLayoutCache.NodeDimensions nodeDimensions;

    //Model providing information.
    TreeModelPtr _TreeModel;

    //Selection model.
    TreeSelectionModelPtr _TreeSelectionModel;
    
    typedef std::set<TreePath, TreePath::BreadthFirstFunctional> TreePathSet;
    typedef TreePathSet::iterator TreePathSetItor;
    typedef TreePathSet::const_iterator TreePathSetConstItor;

    TreePathSet _ExpandedPathSet;
    TreePathSet _VisiblePathSet;
    
	class ModelListener : public TreeModelListener
	{
	public :
		ModelListener(AbstractTreeModelLayoutPtr TheAbstractTreeModelLayout);
		
        virtual void treeNodesChanged(TreeModelEvent e);
        virtual void treeNodesInserted(TreeModelEvent e);
        virtual void treeNodesWillBeRemoved(TreeModelEvent e);
        virtual void treeNodesRemoved(TreeModelEvent e);
        virtual void treeStructureChanged(TreeModelEvent e);
	protected :
		AbstractTreeModelLayoutPtr _AbstractTreeModelLayout;
	};

	friend class ModelListener;

	ModelListener _ModelListener;

	typedef std::set<TreeModelLayoutListenerPtr> TreeModelLayoutListenerSet;
    typedef TreeModelLayoutListenerSet::iterator TreeModelLayoutListenerSetItor;
    typedef TreeModelLayoutListenerSet::const_iterator TreeModelLayoutListenerSetConstItor;
	
    TreeModelLayoutListenerSet       _TreeModelLayoutListeners;

    void produceTreeCollapsed(const TreePath& Path);
    void produceTreeExpanded(const TreePath& Path);
    void produceTreeWillCollapse(const TreePath& Path);
    void produceTreeWillExpand(const TreePath& Path);

	bool _VetoPathExpantion;
	bool _VetoPathCollapse;

    void insertVisiblePath(const TreePath& Path);
    void removeVisiblePath(const TreePath& Path);
    void removeExpandedPath(const TreePath& Path);
    
    typedef std::set<TreeModelListenerPtr> TreeModelListenerSet;
	typedef TreeModelListenerSet::iterator TreeModelListenerSetIter;
	typedef TreeModelListenerSet::const_iterator TreeModelListenerSetConstIter;
	TreeModelListenerSet _ModelListeners;

	void produceTreeNodesChanged(const TreeModelEvent& e);
	void produceTreeNodesInserted(const TreeModelEvent& e);
	void produceTreeNodesWillBeRemoved(const TreeModelEvent& e);
	void produceTreeNodesRemoved(const TreeModelEvent& e);
	void produceTreeStructureChanged(const TreeModelEvent& e);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractTreeModelLayoutBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractTreeModelLayout &source);
};

typedef AbstractTreeModelLayout *AbstractTreeModelLayoutP;

OSG_END_NAMESPACE

#include "OSGAbstractTreeModelLayoutBase.inl"
#include "OSGAbstractTreeModelLayout.inl"

#define OSGABSTRACTTREEMODELLAYOUT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTREEMODELLAYOUT_H_ */
