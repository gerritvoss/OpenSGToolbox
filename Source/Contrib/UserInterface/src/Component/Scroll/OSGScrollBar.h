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
#include "OSGAdjustmentListener.h"

#include "OSGChangeListener.h"
#include "OSGActionListener.h"
#include "OSGMouseMotionAdapter.h"
#include "OSGMouseAdapter.h"
#include "OSGBoundedRangeModel.h"

#include "OSGEventConnection.h"

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
    
    EventConnection addAdjustmentListener(AdjustmentListenerPtr Listener);
	bool isAdjustmentListenerAttached(AdjustmentListenerPtr Listener) const;
    void removeAdjustmentListener(AdjustmentListenerPtr Listener);

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
    virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

    Button* editMinButton(void) const;
    Button* editMaxButton(void) const;
    Button* editScrollField(void) const;
    Button* editScrollBar(void) const;

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

	typedef std::set<AdjustmentListenerPtr> AdjustmentListenerSet;
    typedef AdjustmentListenerSet::iterator AdjustmentListenerSetItor;
    typedef AdjustmentListenerSet::const_iterator AdjustmentListenerSetConstItor;
	
    AdjustmentListenerSet       _AdjustmentListeners;
    void produceAdjustmentValueChanged(const AdjustmentEventUnrecPtr e);

    void updateScrollBarLayout(void);
    

    //Listener for getting change updates of the BoundedRangeModel
	class BoundedRangeModelChangeListener : public ChangeListener
	{
	public:
		BoundedRangeModelChangeListener(ScrollBarRefPtr TheScrollBar);
        virtual void stateChanged(const ChangeEventUnrecPtr e);
	private:
		ScrollBarRefPtr _ScrollBar;
	};

	friend class BoundedRangeModelChangeListener;

	BoundedRangeModelChangeListener _BoundedRangeModelChangeListener;
    EventConnection _RangeModelConnection;


    //Min Button Action Listener
	class MinButtonActionListener : public ActionListener
	{
	public:
		MinButtonActionListener(ScrollBarRefPtr TheScrollBar);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
	private:
		ScrollBarRefPtr _ScrollBar;
	};

	friend class MinButtonActionListener;

	MinButtonActionListener _MinButtonActionListener;

    //Max Button Action Listener
	class MaxButtonActionListener : public ActionListener
	{
	public:
		MaxButtonActionListener(ScrollBarRefPtr TheScrollBar);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
	private:
		ScrollBarRefPtr _ScrollBar;
	};

	friend class MaxButtonActionListener;

	MaxButtonActionListener _MaxButtonActionListener;
    
    //ScrollBar mouse pressed Listener
	class ScrollBarListener : public MouseAdapter
	{
	public :
		ScrollBarListener(ScrollBarRefPtr TheScrollBar);
		virtual void mousePressed(const MouseEventUnrecPtr e);
	protected :
		ScrollBarRefPtr _ScrollBar;
	};

	friend class ScrollBarListener;

	ScrollBarListener _ScrollBarListener;

    //ScrollBar Dragging Listener
	class ScrollBarDraggedListener : public MouseAdapter, public MouseMotionAdapter
	{
	public :
		ScrollBarDraggedListener(ScrollBarRefPtr TheScrollBar);
		virtual void mouseReleased(const MouseEventUnrecPtr e);
        
		virtual void mouseDragged(const MouseEventUnrecPtr e);

        void setInitialMousePosition(const Pnt2f& Pos);
        void setInitialScrollBarPosition(const Pnt2f& Pos);
        
        void disconnect(void);
	protected :
		ScrollBarRefPtr _ScrollBar;
        Pnt2f _InitialMousePosition;
        Pnt2f _InitialScrollBarPosition;
	};

	friend class ScrollBarDraggedListener;

	ScrollBarDraggedListener _ScrollBarDraggedListener;
    
    //ScrollField Mouse Listener
	class ScrollFieldListener : public ActionListener
	{
	public :
		ScrollFieldListener(ScrollBarRefPtr TheScrollBar);
        virtual void actionPerformed(const ActionEventUnrecPtr e);
	protected :
		ScrollBarRefPtr _ScrollBar;
	};

	friend class ScrollFieldListener;

	ScrollFieldListener _ScrollFieldListener;

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

#include "OSGScrollBarBase.inl"
#include "OSGScrollBar.inl"

#endif /* _OSGSCROLLBAR_H_ */
