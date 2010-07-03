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

#ifndef _OSGVARIABLEHEIGHTTREEMODELLAYOUT_H_
#define _OSGVARIABLEHEIGHTTREEMODELLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVariableHeightTreeModelLayoutBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VariableHeightTreeModelLayout class. See \ref
           PageContribUserInterfaceVariableHeightTreeModelLayout for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING VariableHeightTreeModelLayout : public VariableHeightTreeModelLayoutBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VariableHeightTreeModelLayoutBase Inherited;
    typedef VariableHeightTreeModelLayout     Self;

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

	//Returns a rectangle giving the bounds needed to draw path.
	virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const;

	//Returns true if every node in the path is expanded
	virtual bool isVisible(const TreePath& path) const;

	//Returns the path to the node that is closest to x,y.
	virtual TreePath getPathClosestTo(const Pnt2f& Loc) const;

	//Returns the path for passed in row.
	virtual TreePath getPathForRow(const UInt32& row) const;

	//Returns the preferred height.
	virtual Real32 getPreferredHeight(void) const;

	//Returns the preferred width for the passed in region.
	virtual Real32 getPreferredWidth(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

	//Number of rows being displayed.
	virtual UInt32 getRowCount(void) const;

	//Returns the row that the last item identified in path is visible at.
	virtual Int32 getRowForPath(const TreePath& path) const;

	//Returns the number of visible children for row.
	virtual UInt32 getVisibleChildCount(const TreePath& path) const;

	//Returns an Enumerator that increments over the visible paths starting at the passed in location.
	//virtual Enumeration getVisiblePathsFrom(const TreePath& path) const;

	//Instructs the LayoutCache that the bounds for path are invalid, and need to be updated.
	virtual void invalidatePathBounds(const TreePath& path);

	//Informs the TreeState that it needs to recalculate all the sizes it is referencing.
	virtual void invalidateSizes(void);

	//Returns true if the last node in this path is expanded
	virtual bool isExpanded(const TreePath& path) const;

	//Marks the path path expanded state to isExpanded.
	virtual void setExpanded(const TreePath& path, bool Expand);

	//Sets the TreeModel that will provide the data.
	virtual void setModel(TreeModel* const newModel);
	
	//Sets the renderer that is responsible for drawing nodes in the tree and which is threfore responsible for calculating the dimensions of individual nodes.
	//virtual void setNodeDimensions(AbstractLayoutCache.NodeDimensions nd);

	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const Real32& rowHeight);

    //Returns the height of the Layout.
    virtual Real32 getHeight(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VariableHeightTreeModelLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VariableHeightTreeModelLayout(void);
    VariableHeightTreeModelLayout(const VariableHeightTreeModelLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VariableHeightTreeModelLayout(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VariableHeightTreeModelLayoutBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VariableHeightTreeModelLayout &source);
};

typedef VariableHeightTreeModelLayout *VariableHeightTreeModelLayoutP;

OSG_END_NAMESPACE

#include "OSGVariableHeightTreeModelLayoutBase.inl"
#include "OSGVariableHeightTreeModelLayout.inl"

#endif /* _OSGVARIABLEHEIGHTTREEMODELLAYOUT_H_ */
