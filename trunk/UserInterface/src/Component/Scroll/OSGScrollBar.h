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

#ifndef _OSGScrollBar_H_
#define _OSGScrollBar_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGScrollBarBase.h"
#include "Event/OSGAdjustmentListener.h"

#include "Event/OSGChangeListener.h"
#include "Event/OSGActionListener.h"
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGMouseAdapter.h>

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief ScrollBar class. See \ref 
           PageUserInterfaceScrollBar for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ScrollBar : public ScrollBarBase
{
  private:

    typedef ScrollBarBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum Orientation{VERTICAL_ORIENTATION=0, HORIZONTAL_ORIENTATION};

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
    virtual void mouseWheelMoved(const MouseWheelEvent& e);

    ButtonPtr &getMinButton(void);
    const ButtonPtr &getMinButton(void) const;

    ButtonPtr &getMaxButton(void);
    const ButtonPtr &getMaxButton(void) const;
    ButtonPtr &getScrollField(void);
    const ButtonPtr &getScrollField(void) const;
    ButtonPtr &getScrollBar(void);
    const ButtonPtr &getScrollBar(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    Pnt2f calculateScrollBarPosition(void) const;
    Vec2f calculateScrollBarSize(void) const;

    Int32 calculateValueFromPosition(const Pnt2f Position) const;

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

	typedef std::set<AdjustmentListenerPtr> AdjustmentListenerSet;
    typedef AdjustmentListenerSet::iterator AdjustmentListenerSetItor;
    typedef AdjustmentListenerSet::const_iterator AdjustmentListenerSetConstItor;
	
    AdjustmentListenerSet       _AdjustmentListeners;
    void produceAdjustmentValueChanged(const AdjustmentEvent& e);

    void updateScrollBarLayout(void);
    

    //Listener for getting change updates of the BoundedRangeModel
	class BoundedRangeModelChangeListener : public ChangeListener
	{
	public:
		BoundedRangeModelChangeListener(ScrollBarPtr TheScrollBar);
        virtual void stateChanged(const ChangeEvent& e);
	private:
		ScrollBarPtr _ScrollBar;
	};

	friend class BoundedRangeModelChangeListener;

	BoundedRangeModelChangeListener _BoundedRangeModelChangeListener;
    EventConnection _RangeModelConnection;


    //Min Button Action Listener
	class MinButtonActionListener : public ActionListener
	{
	public:
		MinButtonActionListener(ScrollBarPtr TheScrollBar);
        virtual void actionPerformed(const ActionEvent& e);
	private:
		ScrollBarPtr _ScrollBar;
	};

	friend class MinButtonActionListener;

	MinButtonActionListener _MinButtonActionListener;

    //Max Button Action Listener
	class MaxButtonActionListener : public ActionListener
	{
	public:
		MaxButtonActionListener(ScrollBarPtr TheScrollBar);
        virtual void actionPerformed(const ActionEvent& e);
	private:
		ScrollBarPtr _ScrollBar;
	};

	friend class MaxButtonActionListener;

	MaxButtonActionListener _MaxButtonActionListener;
    
    //ScrollBar mouse pressed Listener
	class ScrollBarListener : public MouseAdapter
	{
	public :
		ScrollBarListener(ScrollBarPtr TheScrollBar);
		virtual void mousePressed(const MouseEvent& e);
	protected :
		ScrollBarPtr _ScrollBar;
	};

	friend class ScrollBarListener;

	ScrollBarListener _ScrollBarListener;

    //ScrollBar Dragging Listener
	class ScrollBarDraggedListener : public MouseAdapter, public MouseMotionAdapter
	{
	public :
		ScrollBarDraggedListener(ScrollBarPtr TheScrollBar);
		virtual void mouseReleased(const MouseEvent& e);
        
		virtual void mouseDragged(const MouseEvent& e);

        void setInitialMousePosition(const Pnt2f& Pos);
        void setInitialScrollBarPosition(const Pnt2f& Pos);
	protected :
		ScrollBarPtr _ScrollBar;
        Pnt2f _InitialMousePosition;
        Pnt2f _InitialScrollBarPosition;
	};

	friend class ScrollBarDraggedListener;

	ScrollBarDraggedListener _ScrollBarDraggedListener;
    
    //ScrollField Mouse Listener
	class ScrollFieldListener : public ActionListener
	{
	public :
		ScrollFieldListener(ScrollBarPtr TheScrollBar);
        virtual void actionPerformed(const ActionEvent& e);
	protected :
		ScrollBarPtr _ScrollBar;
	};

	friend class ScrollFieldListener;

	ScrollFieldListener _ScrollFieldListener;

    void setMajorAxisScrollBarPosition(const Pnt2f& Pos);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ScrollBarBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ScrollBar &source);
};

typedef ScrollBar *ScrollBarP;

OSG_END_NAMESPACE

#include "OSGScrollBarBase.inl"
#include "OSGScrollBar.inl"

#define OSGScrollBar_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGScrollBar_H_ */
