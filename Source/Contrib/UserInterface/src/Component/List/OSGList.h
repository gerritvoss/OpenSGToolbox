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
#include "OSGListSelectionModel.h"
#include "OSGComponentGenerator.h"
#include "OSGListSelectionEventDetailsFields.h"
#include "OSGListDataEventDetailsFields.h"
#include <boost/any.hpp>

#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief List class. See \ref
           PageContribUserInterfaceList for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING List : public ListBase
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

   
    virtual void updateLayout(void);

    void setSelectedIndex(UInt32 index);

    Int32 getSelectedIndex(void) const;

    Int32 getMinSelectedIndex(void) const;

    Int32 getMaxSelectedIndex(void) const;

    boost::any getSelectedItem(void) const;

	virtual Vec2f getContentRequestedSize(void) const;
	
    virtual void mousePressed(MouseEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);

    Component* getComponentAtPoint(MouseEventDetails* const e);
    boost::any getValueAtPoint(MouseEventDetails* const e);

    //Returns the row for the specified location.
	//The Location should be in Component space
    Int32 getIndexForLocation(const Pnt2f& Location) const;

	//The Location should be in Component space
    Int32 getIndexClosestToLocation(const Pnt2f& Location) const;

	//The Location should be in DrawingSurface space
    Int32 getIndexForDrawingSurfaceLocation(const Pnt2f& Location) const;

	//The Location should be in DrawingSurface space
    Int32 getIndexClosestToDrawingSurfaceLocation(const Pnt2f& Location) const;

    Component* getComponentAtIndex(const UInt32& Index);
    boost::any getValueAtIndex(const UInt32& Index) const;
    
	
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
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const List *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    virtual bool useBoundsForClipping(void) const;
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
    ComponentTransitPtr createIndexComponent(const UInt32& Index);

	
	void updateItem(const UInt32& Index);

	void cleanItem(const UInt32& Index);

	void initItem(const UInt32& Index);
	
    Int32 _TopDrawnIndex,
          _BottomDrawnIndex;
	Int32 _FocusedIndex;

    std::deque<ComponentRefPtr> _DrawnIndices;

	//Focus Events
	void handleItemFocusGained(FocusEventDetails* const e);
	void handleItemFocusLost(FocusEventDetails* const e);
    std::map<Component*, boost::signals2::connection> _ItemFocusGainedConnections,
                                             _ItemFocusLostConnections;

    //Selection Event
	void handleSelectionChanged(ListSelectionEventDetails* const e);
    boost::signals2::connection _SelectionChangedConnection;

	//List Data Events
	void handleContentsChanged(ListDataEventDetails* const e);
	void handleIntervalAdded(ListDataEventDetails* const e);
	void handleIntervalRemoved(ListDataEventDetails* const e);
    boost::signals2::connection _ContentsChangedConnection,
                                _IntervalAddedConnection,
                                _IntervalRemovedConnection;

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
