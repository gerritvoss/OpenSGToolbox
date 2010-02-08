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

#ifndef _OSGFIXEDHEIGHTTREEMODELLAYOUT_H_
#define _OSGFIXEDHEIGHTTREEMODELLAYOUT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGFixedHeightTreeModelLayoutBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FixedHeightTreeModelLayout class. See \ref 
           PageUserInterfaceFixedHeightTreeModelLayout for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING FixedHeightTreeModelLayout : public FixedHeightTreeModelLayoutBase
{
  private:

    typedef FixedHeightTreeModelLayoutBase Inherited;

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
	//Returns a rectangle giving the bounds needed to draw path.
	virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight, TreePath path, Pnt2f TopLeftPlaceIn, Pnt2f BottomRightPlaceIn) const;

	//Returns true if every node in the path is expanded
	virtual bool isVisible(const TreePath& path) const;

	//Returns the path to the node that is closest to x,y.
	virtual TreePath getPathClosestTo(const Pnt2f& Loc) const;

	//Returns the path for passed in row.
	virtual TreePath getPathForRow(const UInt32& row) const;

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
	virtual void setModel(TreeModelPtr newModel);
	
	//Determines whether or not the root node from the TreeModel is visible.
	virtual void setRootVisible(bool rootVisible);

	//Sets the height of each cell.
	virtual void setRowHeight(const UInt32& rowHeight);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FixedHeightTreeModelLayoutBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FixedHeightTreeModelLayout(void);
    FixedHeightTreeModelLayout(const FixedHeightTreeModelLayout &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FixedHeightTreeModelLayout(void); 

    /*! \}                                                                 */
      
    UInt32 getRowCount(const TreePath& Path) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FixedHeightTreeModelLayoutBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FixedHeightTreeModelLayout &source);
};

typedef FixedHeightTreeModelLayout *FixedHeightTreeModelLayoutP;

OSG_END_NAMESPACE

#include "OSGFixedHeightTreeModelLayoutBase.inl"
#include "OSGFixedHeightTreeModelLayout.inl"

#define OSGFIXEDHEIGHTTREEMODELLAYOUT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGFIXEDHEIGHTTREEMODELLAYOUT_H_ */
