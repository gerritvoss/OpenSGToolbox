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

#include "OSGKeyListener.h"
#include "OSGMouseListener.h"
#include "OSGMouseWheelListener.h"
#include "OSGMouseMotionListener.h"
#include "OSGUpdateListener.h"
#include "OSGEventConnection.h"

#include <set>

#include "OSGFocusListener.h"
#include "OSGComponentListener.h"

#include "OSGToolTipFields.h"
#include "OSGInternalWindowFields.h"
#include "OSGComponentContainerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Component class. See \ref
           PageContribUserInterfaceComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Component : public ComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

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
    virtual void mouseClicked(const MouseEventUnrecPtr e);
    virtual void mouseEntered(const MouseEventUnrecPtr e);
    virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mousePressed(const MouseEventUnrecPtr e);
    virtual void mouseReleased(const MouseEventUnrecPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventUnrecPtr e);
    virtual void mouseDragged(const MouseEventUnrecPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);

	//Key Events
	virtual void keyPressed(const KeyEventUnrecPtr e);
	virtual void keyReleased(const KeyEventUnrecPtr e);
	virtual void keyTyped(const KeyEventUnrecPtr e);

	//Focus Events
	virtual void focusGained(const FocusEventUnrecPtr e);
	virtual void focusLost(const FocusEventUnrecPtr e);

    //Detach From Event Producer
    //This method should disconnect all Event Connection to
    //the WindowEventProducer referenced by this Component
    virtual void detachFromEventProducer(void);
	
    EventConnection addMouseMotionListener(MouseMotionListenerPtr Listener);
    void removeMouseMotionListener(MouseMotionListenerPtr Listener);
    EventConnection addMouseWheelListener(MouseWheelListenerPtr Listener);
    void removeMouseWheelListener(MouseWheelListenerPtr Listener);
    EventConnection addMouseListener(MouseListenerPtr Listener);
    void removeMouseListener(MouseListenerPtr Listener);
    EventConnection addKeyListener(KeyListenerPtr Listener);
    void removeKeyListener(KeyListenerPtr Listener);
    
    EventConnection addFocusListener(FocusListenerPtr Listener);
    void removeFocusListener(FocusListenerPtr Listener);

    EventConnection addComponentListener(ComponentListenerPtr Listener);
    void removeComponentListener(ComponentListenerPtr Listener);
    
    bool isMouseListenerAttached(MouseListenerPtr Listener) const;
    bool isMouseMotionListenerAttached(MouseMotionListenerPtr Listener) const;
    bool isMouseWheelListenerAttached(MouseWheelListenerPtr Listener) const;
    bool isKeyListenerAttached(KeyListenerPtr Listener) const;
    bool isFocusListenerAttached(FocusListenerPtr Listener) const;
    bool isComponentListenerAttached(ComponentListenerPtr Listener) const;

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

    class ComponentUpdater : public UpdateListener
    {
    public:
        ComponentUpdater(Component* const TheComponent);

        virtual void update(const UpdateEventUnrecPtr e);
    private:
        Component* _Component;
    };

    class DeactivateToolTipListener : public MouseListener
    {
    public:
        DeactivateToolTipListener(Component* const TheComponent);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);
    private:
        Component* _Component;
    };

    class ActivateToolTipListener : public MouseListener
    {
    public:
        ActivateToolTipListener(Component* const TheComponent);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        void disconnect(void);
    private:
        Component* _Component;
    };
    
    friend class ComponentUpdater;

    Real32 _TimeSinceMouseEntered;
    ComponentUpdater _ComponentUpdater;
    ActivateToolTipListener _ActivateToolTipListener;
    DeactivateToolTipListener _DeactivateToolTipListener;
    
	bool _MouseInComponentLastMouse;

	virtual UInt32 queryCursor(const Pnt2f& CursorLoc) const;
	
    virtual Pnt2f               getClipTopLeft    (void) const;
    virtual Pnt2f               getClipBottomRight(void) const;
    virtual void setClipTopLeft    (const Pnt2f &value);
    virtual void setClipBottomRight(const Pnt2f &value);

    InternalWindow* _ParentWindow;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Component &source);
	
	typedef std::set<MouseMotionListenerPtr> MouseMotionListenerSet;
    typedef MouseMotionListenerSet::iterator MouseMotionListenerSetItor;
    typedef MouseMotionListenerSet::const_iterator MouseMotionListenerSetConstItor;
	
    MouseMotionListenerSet       _MouseMotionListeners;
	
    virtual void produceMouseMoved(const MouseEventUnrecPtr e);
    virtual void produceMouseDragged(const MouseEventUnrecPtr e);

	typedef std::set<MouseWheelListenerPtr> MouseWheelListenerSet;
    typedef MouseWheelListenerSet::iterator MouseWheelListenerSetItor;
    typedef MouseWheelListenerSet::const_iterator MouseWheelListenerSetConstItor;
	
    MouseWheelListenerSet       _MouseWheelListeners;
	
    void produceMouseWheelMoved(const MouseWheelEventUnrecPtr e);
	
	typedef std::set<MouseListenerPtr> MouseListenerSet;
    typedef MouseListenerSet::iterator MouseListenerSetItor;
    typedef MouseListenerSet::const_iterator MouseListenerSetConstItor;
	
    MouseListenerSet       _MouseListeners;
	
    void produceMouseClicked(const MouseEventUnrecPtr e);
    void produceMouseEntered(const MouseEventUnrecPtr e);
    void produceMouseExited(const MouseEventUnrecPtr e);
    void produceMousePressed(const MouseEventUnrecPtr e);
    void produceMouseReleased(const MouseEventUnrecPtr e);
	
	typedef std::set<KeyListenerPtr> KeyListenerSet;
    typedef KeyListenerSet::iterator KeyListenerSetItor;
    typedef KeyListenerSet::const_iterator KeyListenerSetConstItor;
	
    KeyListenerSet       _KeyListeners;
	
    void produceKeyPressed(const KeyEventUnrecPtr e);
    void produceKeyReleased(const KeyEventUnrecPtr e);
    void produceKeyTyped(const KeyEventUnrecPtr e);
    
	typedef std::set<FocusListenerPtr> FocusListenerSet;
    typedef FocusListenerSet::iterator FocusListenerSetItor;
    typedef FocusListenerSet::const_iterator FocusListenerSetConstItor;
	
    FocusListenerSet       _FocusListeners;
    void produceFocusGained(const FocusEventUnrecPtr e);
    void produceFocusLost(const FocusEventUnrecPtr e);
    
	typedef std::set<ComponentListenerPtr> ComponentListenerSet;
    typedef ComponentListenerSet::iterator ComponentListenerSetItor;
    typedef ComponentListenerSet::const_iterator ComponentListenerSetConstItor;
	
    ComponentListenerSet       _ComponentListeners;
    void produceComponentHidden(const ComponentEventUnrecPtr e);
    void produceComponentVisible(const ComponentEventUnrecPtr e);
    void produceComponentMoved(const ComponentEventUnrecPtr e);
    void produceComponentResized(const ComponentEventUnrecPtr e);
    void produceComponentEnabled(const ComponentEventUnrecPtr e);
    void produceComponentDisabled(const ComponentEventUnrecPtr e);
};

typedef Component *ComponentP;

OSG_END_NAMESPACE


#include "OSGComponentBase.inl"
#include "OSGComponent.inl"

#endif /* _OSGCOMPONENT_H_ */
