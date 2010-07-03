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

#ifndef _OSGSLIDER_H_
#define _OSGSLIDER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSliderBase.h"
#include "OSGChangeListener.h"

#include "OSGMouseAdapter.h"
#include "OSGKeyAdapter.h"
#include "OSGMouseMotionAdapter.h"

#include "OSGEventConnection.h"
#include "OSGBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Slider class. See \ref
           PageContribUserInterfaceSlider for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Slider : public SliderBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef SliderBase Inherited;
    typedef Slider     Self;

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

    //Adds a listener to the list that is notified each time a change to the model occurs.
    EventConnection addChangeListener(ChangeListenerPtr l);
	bool isChangeListenerAttached(ChangeListenerPtr l) const;

    //Removes a ChangeListener from this spinner.
    void removeChangeListener(ChangeListenerPtr l);

	//Creates a hashtable that will draw text labels starting at the slider minimum using the increment specified.
	FieldContainerMap createStandardLabels(UInt32 increment);

	//Creates a hashtable that will draw text labels starting at the start point specified using the increment specified.
	FieldContainerMap createStandardLabels(UInt32 increment, Int32 start);

	//Returns the "extent" -- the range of values "covered" by the knob.
	UInt32 getExtent(void) const;

	//Returns the maximum value supported by the slider.
	Int32 getMaximum(void) const;

	//Returns the minimum value supported by the slider.
	Int32 getMinimum(void) const;

	//Returns the sliders value.
	Int32 getValue(void) const;

	//True if the slider knob is being dragged.
	bool getValueIsAdjusting(void) const;

	//Sets the size of the range "covered" by the knob.
	void setExtent(UInt32 extent);

	//Sets the models maximum property.
	void setMaximum(Int32 maximum);

	//Sets the models minimum property.
	void setMinimum(Int32 minimum);

	//Sets the sliders current value.
	void setValue(Int32 n);

	//Sets the models valueIsAdjusting property.
	void setValueIsAdjusting(bool b);

    virtual void detachFromEventProducer(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SliderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Slider(void);
    Slider(const Slider &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Slider(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Slider *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    
    //Listener for getting change updates of the BoundedRangeModel
	class BoundedRangeModelChangeListener : public ChangeListener
	{
	public:
		BoundedRangeModelChangeListener(Slider* const TheSlider);
        virtual void stateChanged(const ChangeEventUnrecPtr e);
	private:
		Slider* _Slider;
	};

	friend class BoundedRangeModelChangeListener;

	BoundedRangeModelChangeListener _BoundedRangeModelChangeListener;
    EventConnection _RangeModelConnection;
	
	class KnobDraggedListener : public MouseMotionAdapter, public MouseAdapter, public KeyAdapter
	{
	public :
		KnobDraggedListener(Slider* const TheSlider);
		virtual void mouseDragged(const MouseEventUnrecPtr e);
		
		virtual void mousePressed(const MouseEventUnrecPtr e);
		virtual void mouseReleased(const MouseEventUnrecPtr e);
		
		virtual void keyTyped(const KeyEventUnrecPtr e);

		void disconnect(void);
	protected :
		Slider* _Slider;
		Int32 _InitialValue;
	};

	friend class _KnobDraggedListener;

	KnobDraggedListener _KnobDraggedListener;

	void updateSliderTrack(void);

	UInt32 getTrackLength(void) const;
	Int32 getTrackMin(void) const;
	Int32 getTrackMax(void) const;

	Pnt2f calculateSliderAlignment(const Pnt2f& Position1, const Vec2f& Size1, const Vec2f& Size2, const Real32& VAlign, const Real32& HAlign);
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

	Pnt2f getSliderTrackTopLeft(void) const;
	Vec2f getSliderTrackSize(void) const;

	bool _UsingDefaultLabels;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SliderBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Slider &source);
};

typedef Slider *SliderP;

OSG_END_NAMESPACE

#include "OSGSliderBase.inl"
#include "OSGSlider.inl"

#endif /* _OSGSLIDER_H_ */
