/*---------------------------------------------------------------------------*\
 *                     OpenSG UserInterface UserInterface                    *
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

#ifndef _OSGTREEMODELLAYOUT_H_
#define _OSGTREEMODELLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTreeModelLayoutBase.h"
#include "Component/Tree/OSGTreePath.h"
#include "Component/Tree/Model/OSGTreeModel.h"
#include "Component/Tree/Model/OSGTreeModelListener.h"
#include "Component/Tree/Selection/OSGTreeSelectionModel.h"
#include "OSGTreeModelLayoutListener.h"
#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelLayout class. See \ref 
           PageUserInterfaceTreeModelLayout for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TreeModelLayout : public TreeModelLayoutBase
{
  private:

    typedef TreeModelLayoutBase Inherited;

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

    virtual void addTreeModelLayoutListener(TreeModelLayoutListenerPtr Listener) = 0;

    virtual void removeTreeModelLayoutListener(TreeModelLayoutListenerPtr Listener) = 0;

	//Returns a rectangle giving the bounds needed to draw path.
	virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const = 0;

	//Returns true if every node in the path is expanded
	virtual bool isVisible(const TreePath& path) const = 0;

	//Returns the TreeModel that is providing the data.
	virtual TreeModelPtr getModel(void) const = 0;

	//Returns the object that renders nodes in the tree, and which is responsible for calculating the dimensions of individual nodes.
	//virtual AbstractLayoutCache.NodeDimensions getNodeDimensions(void) const = 0;

	//Returns the path to the node that is closest to x,y.
	virtual TreePath getPathClosestTo(const UInt32& x, const UInt32& y) const = 0;

	//Returns the path for passed in row.
	virtual TreePath getPathForRow(const UInt32& row) const = 0;

	//Returns the preferred height.
	virtual UInt32 getPreferredHeight(void) const = 0;

	//Returns the preferred width for the passed in region.
	virtual UInt32 getPreferredWidth(Pnt2f& TopLeft, Pnt2f& BottomRight) const = 0;

	//Number of rows being displayed.
	virtual UInt32 getRowCount(void) const = 0;

	//Returns the row that the last item identified in path is visible at.
	virtual Int32 getRowForPath(const TreePath& path) const = 0;

	//Returns the height of each row.
	virtual UInt32 getRowHeight(void) const = 0;

	//Returns the model used to maintain the selection.
	virtual TreeSelectionModelPtr getSelectionModel(void) const = 0;

	//Returns the number of visible children for row.
	virtual UInt32 getVisibleChildCount(const TreePath& path) const = 0;
    
	//Returns the Visible Paths
    virtual std::vector<TreePath> getVisiblePaths(void) const = 0;

	//Returns the Expanded Paths
    virtual std::vector<TreePath> getExpandedPaths(void) const = 0;

	//Returns an Enumerator that increments over the visible paths starting at the passed in location.
	//virtual Enumeration getVisiblePathsFrom(const TreePath& path) const = 0;

	//Instructs the LayoutCache that the bounds for path are invalid, and need to be updated.
	virtual void invalidatePathBounds(const TreePath& path) = 0;

	//Informs the TreeState that it needs to recalculate all the sizes it is referencing.
	virtual void invalidateSizes(void) = 0;

	//Returns true if the last node in this path is expanded
	virtual bool isExpanded(const TreePath& path) const = 0;

	//Returns true if the root node of the tree is displayed.
	virtual bool isRootVisible(void) const = 0;

	//Marks the path path expanded state to isExpanded.
	virtual void setExpanded(const TreePath& path, bool Expand) = 0;

	//Makes sure that all the nodes in path are expanded making the last node in the
    //path visible
	virtual void setVisible(const TreePath& path) = 0;

	//Sets the TreeModel that will provide the data.
	virtual void setModel(TreeModelPtr newModel) = 0;

	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd) = 0;

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible) = 0;

	//Sets the height of each cell.
	virtual void setRowHeight(const UInt32& rowHeight) = 0;

	//Sets the TreeSelectionModel used to manage the selection to new LSM.
	virtual void setSelectionModel(TreeSelectionModelPtr newLSM) = 0;

	//Returns true if the height of each row is a fixed size.
	virtual bool isFixedRowHeight(void) const = 0;

	//Tells the ModelLayout to veto the expantion of the given TreePath
	virtual void vetoPathExpantion(const TreePath& Path) = 0;

	//Tells the ModelLayout to veto the collapse of the given TreePath
	virtual void vetoPathCollapse(const TreePath& Path) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TreeModelLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModelLayout(void);
    TreeModelLayout(const TreeModelLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModelLayout(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TreeModelLayoutBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TreeModelLayout &source);
};

typedef TreeModelLayout *TreeModelLayoutP;

OSG_END_NAMESPACE

#include "OSGTreeModelLayoutBase.inl"
#include "OSGTreeModelLayout.inl"

#define OSGTREEMODELLAYOUT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTREEMODELLAYOUT_H_ */
