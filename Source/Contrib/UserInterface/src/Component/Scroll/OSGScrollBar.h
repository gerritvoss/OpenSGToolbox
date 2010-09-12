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

#ifndef _OSGSCROLLBAR_H_
#define _OSGSCROLLBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGScrollBarBase.h"
#include "OSGBoundedRangeModel.h"
#include "OSGActionEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScrollBar class. See \ref
           PageContribUserInterfaceScrollBar for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ScrollBar : public ScrollBarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef ScrollBarBase Inherited;
    typedef ScrollBar     Self;

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

    UInt32 getExtent(void) const;
    
    Int32 getMaximum(void) const;
    
    Int32 getMinimum(void) const;
    
    Int32 getValue(void) const;
    
    bool getValueIsAdjusting(void) const;
    
    void setExtent(UInt32 newExtent);
    
    void setMaximum(Int32 newMaximum);
    
    void setMinimum(Int32 newMinimum);
    
    void setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting);
    
    void setValue(Int32 newValue);
    
    void setValueIsAdjusting(bool Value);

    void scrollUnit(const Int32 Units);
    void scrollBlock(const Int32 Blocks);
    
	//Mouse Wheel Events
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

    Button* getMinButton(void) const;
    Button* getMaxButton(void) const;
    Button* getScrollField(void) const;
    Button* getScrollBar(void) const;

    virtual void detachFromEventProducer(void);
    
    void setRangeModel     (BoundedRangeModel * const value);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ScrollBarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScrollBar(void);
    ScrollBar(const ScrollBar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScrollBar(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ScrollBar *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    Pnt2f calculateScrollBarPosition(void) const;
    Vec2f calculateScrollBarSize(void) const;

    Int32 calculateValueFromPosition(const Pnt2f Position) const;

    void produceAdjustmentValueChanged(AdjustmentEventDetails* const e);

    void updateScrollBarLayout(void);
    

    void handleRangeModelStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _RangeModelConnection;


    //Min Button Action
    void handleMinButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _MinActionConnection;

    //Max Button Action
    void handleMaxButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _MaxActionConnection;
    
    //ScrollBar mouse pressed
	void handleScrollBarMousePressed(MouseEventDetails* const e);
    boost::signals2::connection _ScrollBarMousePressedConnection;

    //ScrollBar Dragging
	void handleScrollBarDragMouseReleased(MouseEventDetails* const e);
    
	void handleScrollBarDragMouseDragged(MouseEventDetails* const e);

    boost::signals2::connection _ScrollBarDragMouseReleasedConnection,
                                _ScrollBarDragMouseDraggedConnection;

    Pnt2f _ScrollBarInitialMousePosition;
    Pnt2f _ScrollBarInitialScrollBarPosition;
    
    //ScrollField Mouse
    void handleScrollFieldAction(ActionEventDetails* const e);
    boost::signals2::connection _ScrollFieldActionConnection;

    void setMajorAxisScrollBarPosition(const Pnt2f& Pos);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ScrollBarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScrollBar &source);
};

typedef ScrollBar *ScrollBarP;

OSG_END_NAMESPACE

#include "OSGButton.h"
#include "OSGScrollBarBase.inl"
#include "OSGScrollBar.inl"

#endif /* _OSGSCROLLBAR_H_ */
