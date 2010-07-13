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

#ifndef _OSGLIST_H_
#define _OSGLIST_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGListBase.h"
#include "OSGFocusListener.h"
#include "OSGListDataListener.h"
#include "OSGListSelectionListener.h"
#include "OSGListSelectionModel.h"
#include "OSGComponentGenerator.h"
#include <boost/any.hpp>

#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief List class. See \ref
           PageContribUserInterfaceList for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING List : public ListBase, public ListSelectionListener, public ListDataListener, public FocusListener
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef ListBase Inherited;
    typedef List     Self;

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

	//Focus Events
	virtual void focusGained(const FocusEventUnrecPtr e);
	virtual void focusLost(const FocusEventUnrecPtr e);

    //Selection Event
	virtual void selectionChanged(const ListSelectionEventUnrecPtr e);

	//List Data Events
	virtual void contentsChanged(const ListDataEventUnrecPtr e);
	virtual void intervalAdded(const ListDataEventUnrecPtr e);
	virtual void intervalRemoved(const ListDataEventUnrecPtr e);
   
    virtual void updateLayout(void);

    void setSelectionModel(ListSelectionModelPtr SelectionModel);

    ListSelectionModelPtr getSelectionModel(void) const;

	virtual Vec2f getContentRequestedSize(void) const;
	
    virtual void mousePressed(const MouseEventUnrecPtr e);
	virtual void keyTyped(const KeyEventUnrecPtr e);

    ComponentRefPtr getComponentAtPoint(const MouseEventUnrecPtr e);
    boost::any getValueAtPoint(const MouseEventUnrecPtr e);

    //Returns the row for the specified location.
	//The Location should be in Component space
    Int32 getIndexForLocation(const Pnt2f& Location) const;

	
    Int32 getIndexClosestToLocation(const Pnt2f& Location) const;

    ComponentRefPtr getComponentAtIndex(const UInt32& Index);
    boost::any getValueAtIndex(const UInt32& Index);
    
	
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

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
    ComponentRefPtr createIndexComponent(const UInt32& Index);

	
	void updateItem(const UInt32& Index);

	void cleanItem(const UInt32& Index);

	void initItem(const UInt32& Index);
	
    Int32 _TopDrawnIndex,
          _BottomDrawnIndex;
	Int32 _FocusedIndex;

    std::deque<ComponentRefPtr> _DrawnIndices;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ListBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const List &source);
};

typedef List *ListP;

OSG_END_NAMESPACE

#include "OSGListModel.h"

#include "OSGListBase.inl"
#include "OSGList.inl"

#endif /* _OSGLIST_H_ */
