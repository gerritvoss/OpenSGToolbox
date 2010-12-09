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

#ifndef _OSGCOMPONENT_H_
#define _OSGCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComponentBase.h"
#include "OSGGraphics.h"

#include "OSGToolTipFields.h"
#include "OSGInternalWindowFields.h"
#include "OSGComponentContainerFields.h"
#include "OSGUpdateEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Component class. See \ref
           PageContribUserInterfaceComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Component : public ComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ScrollTrackingMasks
    {
        SCROLLABLE_TRACKING_OFF               = 0,
        SCROLLABLE_TRACKS_VIEWPORT_HEIGHT     = 1,
        SCROLLABLE_TRACKS_VIEWPORT_WIDTH      = 2,
        SCROLLABLE_HEIGHT_MIN_TRACKS_VIEWPORT = 4,
        SCROLLABLE_WIDTH_MIN_TRACKS_VIEWPORT  = 8
    };

    typedef ComponentBase Inherited;
    typedef Component     Self;

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

    using Inherited::getClipBounds;

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	virtual void draw(Graphics* const Graphics, Real32 Opacity = 1.0f) const;

    virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
	virtual void getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void updateContainerLayout(void);
	virtual void updateClipBounds(void);
	virtual Vec2f getRequestedSize(void) const;
	virtual Vec2f getContentRequestedSize(void) const;
	virtual Vec2f getBorderingLength(void) const;
	
	//Mouse Events
    virtual void mouseClicked(MouseEventDetails* const e);
    virtual void mouseEntered(MouseEventDetails* const e);
    virtual void mouseExited(MouseEventDetails* const e);
    virtual void mousePressed(MouseEventDetails* const e);
    virtual void mouseReleased(MouseEventDetails* const e);

	//Mouse Motion Events
    virtual void mouseMoved(MouseEventDetails* const e);
    virtual void mouseDragged(MouseEventDetails* const e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

	//Key Events
	virtual void keyPressed(KeyEventDetails* const e);
	virtual void keyReleased(KeyEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);

	//Focus Events
	virtual void focusGained(FocusEventDetails* const e);
	virtual void focusLost(FocusEventDetails* const e);

    //Detach From Event Producer
    //This method should disconnect all Event Connection to
    //the WindowEventProducer referenced by this Component
    virtual void detachFromEventProducer(void);

	void setMouseContained(bool Value);
	bool getMouseContained(void);

    virtual bool takeFocus(bool Temporary = false);
    
    virtual bool isContained(const Pnt2f& p, bool TestAgainstClipBounds = true) const;

    virtual Real32 getBaseline(const Real32& x, const Real32& y) const;

    //Returns the tooltip location in this component's coordinate system
    virtual Pnt2f getToolTipLocation(Pnt2f MousePosition);

    virtual ToolTipTransitPtr createToolTip(void);
    
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

    //Sets whether a viewport should always force the height of this Scrollable to match the height of the viewport.
    void setScrollableTracksViewportHeight(bool enable);

    //Sets whether a viewport should always force the width of this Scrollable to match the width of the viewport.
    void setScrollableTracksViewportWidth(bool enable);

    //Sets whether a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    void setScrollableHeightMinTracksViewport(bool enable);

    //Sets whether a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    void setScrollableWidthMinTracksViewport(bool enable);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

	virtual void scrollToPoint(const Pnt2f& PointInComponent);

    static const OSG::BitVector BordersFieldMask;
	virtual void setBorders(Border * const TheBorder);

    static const OSG::BitVector BackgroundsFieldMask;
	virtual void setBackgrounds(Layer* const TheBackground);
    
    static const OSG::BitVector ForegroundsFieldMask;
	virtual void setForegrounds(Layer* const TheForeground);

    virtual Pnt2f getParentToLocal(const Pnt2f& Location) const;

    virtual Pnt2f getLocalToParent(const Pnt2f& Location) const;

    virtual InternalWindow* getParentWindow(void) const;

    virtual void setParentWindow(InternalWindow* const parent);

    virtual ComponentContainer* getParentContainer(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Component(void);
    Component(const Component &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Component(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

	virtual bool setupClipping(Graphics* const Graphics) const;
    virtual void drawBorder(Graphics* const TheGraphics, const Border* Border, Real32 Opacity) const;
    virtual void drawBackground(Graphics* const TheGraphics, const Layer* Background, Real32 Opacity) const;
    virtual void drawForeground(Graphics* const TheGraphics, const Layer* Foreground, Real32 Opacity) const;
    
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const = 0;
	virtual void drawUnclipped(Graphics* const TheGraphics, Real32 Opacity) const;
	
    virtual bool giveFocus(Component* const NewFocusedComponent, bool Temporary= false);
    virtual Border* getDrawnBorder(void) const;
    virtual Layer* getDrawnBackground(void) const;
    virtual Layer* getDrawnForeground(void) const;

    virtual bool useBoundsForClipping(void) const;

    void handleUpdate(UpdateEventDetails* const e);
    void handleMouseEntered(MouseEventDetails* const e);
    void handleMouseExited(MouseEventDetails* const e);

    void deactivateTooltip(MouseEventDetails* const e);

    boost::signals2::connection _UpdateConnection;
    
    boost::signals2::connection _MouseEnterConnection,
                                _MouseExitConnection;

    boost::signals2::connection _ActiveTooltipClickConnection,
                                _ActiveTooltipExitConnection,
                                _ActiveTooltipPressConnection,
                                _ActiveTooltipReleaseConnection;

    Real32 _TimeSinceMouseEntered;
    
	bool _MouseInComponentLastMouse;

	virtual UInt32 queryCursor(const Pnt2f& CursorLoc) const;
	
    virtual Pnt2f               getClipTopLeft    (void) const;
    virtual Pnt2f               getClipBottomRight(void) const;
    virtual void setClipTopLeft    (const Pnt2f &value);
    virtual void setClipBottomRight(const Pnt2f &value);

    InternalWindow* _ParentWindow;

    void produceComponentResized (void);
    void produceComponentMoved   (void);
    void produceComponentEnabled (void);
    void produceComponentDisabled(void);
    void produceComponentVisible (void);
    void produceComponentHidden  (void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Component &source);
};

typedef Component *ComponentP;

OSG_END_NAMESPACE


#include "OSGComponentBase.inl"
#include "OSGComponent.inl"

#endif /* _OSGCOMPONENT_H_ */
