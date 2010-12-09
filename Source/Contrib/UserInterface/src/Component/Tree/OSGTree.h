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

#ifndef _OSGTREE_H_
#define _OSGTREE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeBase.h"
#include "OSGUIViewportFields.h"
#include "OSGComponentGenerator.h"
#include "OSGTreeModelLayoutEventDetailsFields.h"
#include "OSGTreeModelEventDetailsFields.h"
#include "OSGTreeSelectionEventDetailsFields.h"
#include "OSGTreePath.h"

#include <deque>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief Tree class. See \ref
           PageContribUserInterfaceTree for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Tree : public TreeBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeBase Inherited;
    typedef Tree     Self;

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
    
    virtual void mousePressed(MouseEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);
	virtual void focusLost(FocusEventDetails* const e);

	virtual Vec2f getContentRequestedSize(void) const;

    //Adds the paths between index0 and index1, inclusive, to the selection.
    void addSelectionInterval(UInt32 index0, UInt32 index1);

    //Adds the node identified by the specified TreePath to the current selection.
    void addSelectionPath(const TreePath& path);

    //Adds each path in the array of paths to the current selection.
    void addSelectionPaths(const std::vector<TreePath>& paths);

    //Adds the path at the specified row to the current selection.
    void addSelectionRow(UInt32 row);

    //Adds the paths at each of the specified rows to the current selection.
    void addSelectionRows(const std::vector<UInt32>& rows);

    //Cancels the current editing session.
    void cancelEditing(void);

    //Clears the selection.
    void clearSelection(void);

    //Ensures that the node identified by the specified path is collapsed and viewable.
    void collapsePath(const TreePath& path);

    //Ensures that the node in the specified row is collapsed.
    void collapseRow(UInt32 row);

    //Called by the renderers to convert the specified value to text.
    //String convertValueToText(Object value, bool selected, bool expanded, bool leaf, UInt32 row, bool hasFocus);

    //Ensures that the node identified by the specified path is expanded and viewable.
    void expandPath(const TreePath& path);

    //Ensures that the node in the specified row is expanded and viewable.
    void expandRow(UInt32 row);

    //Returns the path identified as the anchor.
    TreePath getAnchorSelectionPath(void) const;

    //Returns the path to the node that is closest to x,y.
    TreePath getClosestPathForLocation(const Pnt2f& Loc) const;

    //Returns the row to the node that is closest to x,y.
    Int32 getClosestRowForLocation(const Pnt2f& Loc) const;

    //Returns the path to the element that is currently being edited.
    TreePath getEditingPath(void) const;

    //Returns an Enumeration of the descendants of the path parent that are currently expanded.
    //Enumeration getExpandedDescendants(TreePath parent) const;

    //Returns the last path component in the first node of the current selection.
    boost::any getLastSelectedPathComponent(void) const;

    //Returns the path identified as the lead.
    TreePath getLeadSelectionPath(void) const;

    //Returns the row index corresponding to the lead path.
    Int32 getLeadSelectionRow(void) const;

    //Returns the last selected row.
    Int32 getMaxSelectionRow(void) const;

    //Gets the first selected row.
    Int32 getMinSelectionRow(void) const;

    //Returns the TreePath to the next tree element that begins with a prefix.
    //TreePath getNextMatch(String prefix, UInt32 startingRow, Position.Bias bias) const;

    //Returns the Rectangle that the specified node will be drawn into.
    //Rectangle getPathBounds(TreePath path) const;

    //Returns the path for the node at the specified location.
    TreePath getPathForLocation(const Pnt2f& Loc) const;

    //Returns the path for the specified row.
    TreePath getPathForRow(UInt32 row) const;

    //Returns the Rectangle that the node at the specified row is drawn in.
    //Rectangle getRowBounds(UInt32 row) const;

    //Returns the number of rows that are currently being displayed.
    Int32 getRowCount(void) const;

    //Returns the row for the specified location.
    Int32 getRowForLocation(const Pnt2f& Loc) const;

    //Returns the row that displays the node identified by the specified path.
    Int32 getRowForPath(const TreePath& path) const;

    //Returns the number of nodes selected.
    UInt32 getSelectionCount(void) const;

    //Returns the path to the first selected node.
    TreePath getSelectionPath(void) const;

    //Returns the paths of all selected values.
    std::vector<TreePath> getSelectionPaths(void) const;

    //Returns all of the currently selected rows.
    std::vector<Int32> getSelectionRows(void) const;

    //Returns the number of rows that are displayed in the display area.
    Int32 getVisibleRowCount(void) const;
    
    bool getRootVisible(void) const;

    //Returns true if the node identified by the path has ever been expanded.
    bool hasBeenExpanded(const TreePath& path) const;

    //Returns true if the node at the specified display row is collapsed.
    bool isCollapsed(UInt32 row) const;

    //Returns true if the value identified by path is currently collapsed, this will return false if any of the values in path are currently not being displayed.
    bool isCollapsed(const TreePath& path) const;

    //Returns true if the tree is being edited.
    bool isEditing(void) const;

    //Returns true if the node at the specified display row is currently expanded.
    bool isExpanded(UInt32 row) const;

    //Returns true if the node identified by the path is currently expanded,
    bool isExpanded(const TreePath& path) const;

    //Returns true if the height of each display row is a fixed size.
    bool isFixedRowHeight(void) const;

    //Returns isEditable.
    bool isPathEditable(const TreePath& path) const;

    //Returns true if the item identified by the path is currently selected.
    bool isPathSelected(const TreePath& path) const;

    //Returns true if the node identified by row is selected.
    bool isRowSelected(UInt32 row) const;

    //Returns true if the selection is currently empty.
    bool isSelectionEmpty(void) const;

    //Returns true if the value identified by path is currently viewable, which means it is either the root or all of its parents are expanded.
    bool isVisible(const TreePath& path) const;

    //Ensures that the node identified by path is currently viewable.
    void makeVisible(const TreePath& path);

    //Removes the nodes between index0 and index1, inclusive, from the selection.
    void removeSelectionInterval(UInt32 index0, UInt32 index1);

    //Removes the node identified by the specified path from the current selection.
    void removeSelectionPath(const TreePath& path);

    //Removes the nodes identified by the specified paths from the current selection.
    void removeSelectionPaths(const std::vector<TreePath>& paths);

    //Removes the row at the index row from the current selection.
    void removeSelectionRow(UInt32 row);

    //Removes the rows that are selected at each of the specified rows.
    void removeSelectionRows(const std::vector<UInt32>& rows);

    //Makes sure all the path components in path are expanded (except for the last path component) and scrolls so that the node identified by the path is displayed.
    void scrollPathToVisible(const TreePath& path);

    //Scrolls the item identified by row until it is displayed.
    void scrollRowToVisible(UInt32 row);

    //Sets the path identified as the anchor.
    void setAnchorSelectionPath(const TreePath& newPath);

    //Sets the dragEnabled property, which must be true to enable automatic drag handling (the first part of drag and drop) on this component.
    void setDragEnabled(bool b);

    //Sets the path identifies as the lead.
    void setLeadSelectionPath(const TreePath& newPath);

    //Selects the nodes between index0 and index1, inclusive.
    void setSelectionInterval(const Int32& index0, const Int32& index1);

    //Selects the node identified by the specified path.
    void setSelectionPath(const TreePath& path);

    //Selects the nodes identified by the specified array of paths.
    void setSelectionPaths(const std::vector<TreePath>& paths);

    //Selects the node at the specified row in the display.
    void setSelectionRow(UInt32 row);

    //Selects the nodes corresponding to each of the specified rows in the display.
    void setSelectionRows(const std::vector<UInt32>& rows);

    //Sets the number of rows that are to be displayed.
    void setVisibleRowCount(UInt32 newCount);

    //Selects the node identified by the specified path and initiates editing.
    void startEditingAtPath(const TreePath& path);

    void setRootVisible(bool Visible);

    //Ends the current editing session.
    bool stopEditing(void);

    //Sent when the tree has changed enough that we need to resize the bounds, but not enough that we need to remove the expanded node set (e->g nodes were expanded or collapsed, or nodes were inserted into the tree).
    void treeDidChange(void);

    //Scrollable Interface
    //Returns the preferred size of the viewport for a view component.
    virtual Vec2f getPreferredScrollableViewportSize(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
    virtual void updateLayout(void);

    void setModel          (TreeModel * const value);
    void setModelLayout    (TreeModelLayout * const value);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Tree(void);
    Tree(const Tree &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Tree(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Tree *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    virtual bool useBoundsForClipping(void) const;

    void handleModelTreeNodesChanged(TreeModelEventDetails* const e);
    void handleModelTreeNodesInserted(TreeModelEventDetails* const e);
    void handleModelTreeNodesWillBeRemoved(TreeModelEventDetails* const e);
    void handleModelTreeNodesRemoved(TreeModelEventDetails* const e);
    void handleModelTreeStructureChanged(TreeModelEventDetails* const e);

    boost::signals2::connection _ModelTreeNodesChangedConnection,
                                _ModelTreeNodesInsertedConnection,
                                _ModelTreeNodesWillBeRemovedConnection,
                                _ModelTreeNodesRemovedConnection,
                                _ModelTreeStructureChangedConnection;
    std::set<Int32> _RomovedNodeRows;

    //Called whenever elements are added to the selection
    void handleSelectionAdded(TreeSelectionEventDetails* const e);
    //Called whenever elements are removed to the selection
    void handleSelectionRemoved(TreeSelectionEventDetails* const e);
    boost::signals2::connection _SelectionAddedConnection,
                                _SelectionRemovedConnection;

    //Called whenever an item in the tree has been collapsed.
    void handleModelLayoutTreeCollapsed(TreeModelLayoutEventDetails* const e);
    //Called whenever an item in the tree has been expanded.
    void handleModelLayoutTreeExpanded(TreeModelLayoutEventDetails* const e);
    boost::signals2::connection _ModelLayoutTreeCollapsedConnection,
                                _ModelLayoutTreeExpandedConnection;

    //Clears the cache of toggled tree paths.
    void clearToggledPaths(void);

    //Returns a TreeModel wrapping the specified object.
    //static TreeModel* createTreeModel(Object value);

    //Creates and returns a sample TreeModel.
    static TreeModel* getDefaultTreeModel(void);

    //Returns an Enumeration of TreePaths that have been expanded that are descendants of parent.
    std::vector<TreePath> getDescendantToggledPaths(const TreePath& parent);

    //Returns TreePath instances representing the path between index0 and index1 (including index1).
    std::vector<TreePath> getPathBetweenRows(UInt32 index0, UInt32 index1);

    //Removes any paths in the selection that are descendants of path.
    bool removeDescendantSelectedPaths(const TreePath& path, bool includePath);

    //Removes any descendants of the TreePaths in toRemove that have been expanded.
    void removeDescendantToggledPaths(const std::vector<TreePath>& toRemove);

    //Sets the expanded state of this JTree.
    void setExpandedState(const TreePath& path, bool state);

    bool isParentAViewport(void) const;

    UIViewport* getParentViewport(void) const;

    //Some non-structural properties of a path has changed.  So update
    //how the row for this path is drawn
    void updateChangedPath(const TreePath& Path);

    //The structure of the tree and it's layout has changed so significantly
    //that the entire drawn representation of the tree should be updated
    void updateEntireTree(void);

    //Updates the drawn representation of the tree in response to inserted rows
    //These new rows may have been inserted through an Insertion event from the model
    //or an expantion event from the ModelLayout
    void updateInsertedRows(UInt32 Begining, UInt32 NumInsertedRows);

    //Updates the drawn representation of the tree in response to removed rows
    //These rows may have been removed through a Removal event from the model
    //or a collapse event from the ModelLayout
    void updateRemovedRows(UInt32 Begining, UInt32 NumRemovedRows);

    void updateRows(UInt32 Begining, UInt32 NumRows);

    
    void updateRowLayout(UInt32 Row);


    void updateExpandedPath (const TreePath& Path);
    void updateCollapsedPath(const TreePath& Path);
    void updateChangedNode  (const TreePath& Path);
    
    void updateChildren (void);
    void clearRowsDrawn (void);

    void updateRowsDrawn(void);

    struct TreeRowComponents
    {
        TreeRowComponents(void);
        TreeRowComponents(Component* const ExpandedComponent, Component* const ValueComponent, Int32 Row);
        ComponentUnrecPtr _ExpandedComponent, _ValueComponent;
        Int32 _Row;
    };

    TreeRowComponents createRowComponent(UInt32 Row);

    void updateDrawnRow(UInt32 Row);
    void updatePreferredSize(void);

    void getDrawnRows(Int32& Beginning, Int32& End) const;

    Int32 _TopDrawnRow,
          _BottomDrawnRow;


    std::deque<TreeRowComponents> _DrawnRows;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Tree &source);
};

typedef Tree *TreeP;

OSG_END_NAMESPACE

#include "OSGTreeModelLayout.h"
#include "OSGCellEditor.h"
#include "OSGTreeBase.inl"
#include "OSGTree.inl"

#endif /* _OSGTREE_H_ */
