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

	//Returns the rows that the TreePath instances in path are being displayed at.
	virtual std::vector<UInt32> getRowsForPaths(std::vector<TreePath> paths) const;

	//Returns the TreeModel that is providing the data.
	virtual TreeModelPtr getModel(void) const;

	//Returns the object that renders nodes in the tree, and which is responsible for calculating the dimensions of individual nodes.
	//virtual AbstractLayoutCache.NodeDimensions getNodeDimensions(void) const;

	//Returns the preferred height.
	virtual UInt32 getPreferredHeight(void) const;

	//Returns the preferred width for the passed in region.
	virtual UInt32 getPreferredWidth(Pnt2s& TopLeft, Pnt2s& BottomRight) const;

	//Returns the height of each row.
	virtual UInt32 getRowHeight(void) const;

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
	virtual void setRowHeight(const UInt32& rowHeight);

	//Sets the TreeSelectionModel used to manage the selection to new LSM.
	virtual void setSelectionModel(TreeSelectionModelPtr newLSM);

	//Returns true if the height of each row is a fixed size.
	virtual bool isFixedRowHeight(void) const;
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
	virtual void getNodeDimensions(Pnt2s& TopLeft, Pnt2s& BottomRight, SharedFieldPtr value, const UInt32& row, const UInt32& depth, bool expanded, Pnt2s TopLeftPlaceIn, Pnt2s BottomRightPlaceIn);


    //Object responsible for getting the size of a node.
    //AbstractLayoutCache.NodeDimensions nodeDimensions;

    //Model providing information.
    TreeModelPtr _TreeModel;

    //Selection model.
    TreeSelectionModelPtr _TreeSelectionModel;


    struct TreePathPreorderLessThan
    {
    protected:
        TreeModelPtr _TreeModel;

        TreePathPreorderLessThan(void);
    public:
        TreePathPreorderLessThan(TreeModelPtr Model);

        bool operator()(const TreePath& LeftPath,
                        const TreePath& RightPath) const;
    };
    
    typedef std::set<TreePath, TreePathPreorderLessThan> TreePathSet;
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
        virtual void treeNodesRemoved(TreeModelEvent e);
        virtual void treeStructureChanged(TreeModelEvent e);
	protected :
		AbstractTreeModelLayoutPtr _AbstractTreeModelLayout;
	};

	friend class ModelListener;

	ModelListener _ModelListener;

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
