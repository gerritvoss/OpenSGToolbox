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

#ifndef _OSGLIST_H_
#define _OSGLIST_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGListBase.h"
#include "Event/OSGFocusListener.h"
#include "OSGListDataListener.h"
#include "OSGListSelectionListener.h"
#include "Util/OSGUIDefines.h"
#include "OSGListSelectionModel.h"
#include "OSGListModel.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING List : public ListBase, public ListSelectionListener, public ListDataListener, public FocusListener
{
  private:

    typedef ListBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	//Focus Events
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

    //Selection Event
	virtual void selectionChanged(const ListSelectionEvent& e);

	//List Data Events
	virtual void contentsChanged(ListDataEvent e);
	virtual void intervalAdded(ListDataEvent e);
	virtual void intervalRemoved(ListDataEvent e);
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
   
    virtual void updateLayout(void);

    void setModel(ListModelPtr Model);
    void setSelectionModel(ListSelectionModelPtr SelectionModel);

    ListModelPtr getModel(void) const;
    ListSelectionModelPtr getSelectionModel(void) const;
	
    virtual void mousePressed(const MouseEvent& e);
	virtual void keyTyped(const KeyEvent& e);

    ComponentPtr getComponentAtPoint(const MouseEvent& e);
    SharedFieldPtr getValueAtPoint(const MouseEvent& e);

    //Returns the row for the specified location.
	//The Location should be in Component space
    Int32 getIndexForLocation(const Pnt2s& Location) const;

	
    Int32 getIndexClosestToLocation(const Pnt2s& Location) const;

    ComponentPtr getComponentAtIndex(const UInt32& Index);
    SharedFieldPtr getValueAtIndex(const UInt32& Index);
    
	
	//Scrollable Interface
    //Returns the preferred size of the viewport for a view component.
    virtual Vec2s getPreferredScrollableViewportSize(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
	void scrollToIndex(const UInt32& Index);

	void scrollToFocused(void);

	void scrollToSelection(void);
	/*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ListBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    List(void);
    List(const List &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~List(void); 

    /*! \}                                                                 */

    ListModelPtr _Model;
    ListSelectionModelPtr _SelectionModel;


	void updateIndiciesDrawnFromModel(void);

	//Updates the drawn Indices.  Called when the ClipBounds of the List
	//changes
    void updateIndicesDrawn(void);

	//Determines the indicies of the Indices that will be seen
	//taking the clip bounds into account
    void getDrawnIndices(Int32& Beginning, Int32& End) const;

	Int32 getListIndexFromDrawnIndex(const Int32& Index) const;

	Int32 getDrawnIndexFromListIndex(const Int32& Index) const;
	
    void updatePreferredSize(void);

	void focusIndex(const Int32& Index);
	
	//Creates the component for the given Index
    ComponentPtr createIndexComponent(const UInt32& Index);

	
	void updateItem(const UInt32& Index);

	void cleanItem(const UInt32& Index);

	void initItem(const UInt32& Index);
	
    Int32 _TopDrawnIndex,
          _BottomDrawnIndex;
	Int32 _FocusedIndex;

    std::deque<ComponentPtr> _DrawnIndices;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ListBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const List &source);
};

typedef List *ListP;

OSG_END_NAMESPACE

#include "OSGListBase.inl"
#include "OSGList.inl"

#define OSGLIST_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLIST_H_ */
