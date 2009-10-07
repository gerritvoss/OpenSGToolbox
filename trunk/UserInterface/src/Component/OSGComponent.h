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

#ifndef _OSGCOMPONENT_H_
#define _OSGCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComponentBase.h"
#include "Graphics/OSGGraphics.h"

#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseWheelListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Toolbox/OSGEventConnection.h>

#include <set>

#include "Event/OSGFocusListener.h"
#include "Event/OSGComponentListener.h"

#include "Component/Misc/OSGToolTipFields.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Component : public ComponentBase
{
  private:

    typedef ComponentBase Inherited;

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
	virtual void draw(const GraphicsPtr Graphics) const;

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
    virtual void mouseClicked(const MouseEventPtr e);
    virtual void mouseEntered(const MouseEventPtr e);
    virtual void mouseExited(const MouseEventPtr e);
    virtual void mousePressed(const MouseEventPtr e);
    virtual void mouseReleased(const MouseEventPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventPtr e);
    virtual void mouseDragged(const MouseEventPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventPtr e);

	//Key Events
	virtual void keyPressed(const KeyEventPtr e);
	virtual void keyReleased(const KeyEventPtr e);
	virtual void keyTyped(const KeyEventPtr e);

	//Focus Events
	virtual void focusGained(const FocusEventPtr e);
	virtual void focusLost(const FocusEventPtr e);
	
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
    virtual ToolTipPtr createToolTip(void);
    
    //Scrollable Interface
    //Returns the preferred size of the viewport for a view component.
    virtual Vec2f getPreferredScrollableViewportSize(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

	virtual void scrollToPoint(const Pnt2f& PointInComponent);

    static const OSG::BitVector BordersFieldMask;
	virtual void setBorders(BorderPtr TheBorder);

    static const OSG::BitVector BackgroundsFieldMask;
	virtual void setBackgrounds(LayerPtr TheBackground);
    
    static const OSG::BitVector ForegroundsFieldMask;
	virtual void setForegrounds(LayerPtr TheForeground);

    virtual Pnt2f getParentToLocal(const Pnt2f& Location);

    virtual Pnt2f getLocalToParent(const Pnt2f& Location);

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

	virtual bool setupClipping(const GraphicsPtr Graphics) const;
    virtual void drawBorder(const GraphicsPtr TheGraphics, const BorderPtr Border) const;
    virtual void drawBackground(const GraphicsPtr TheGraphics, const LayerPtr Background) const;
    virtual void drawForeground(const GraphicsPtr TheGraphics, const LayerPtr Foreground) const;
    
	virtual void drawInternal(const GraphicsPtr Graphics) const = 0;
	virtual void drawUnclipped(const GraphicsPtr TheGraphics) const;
	
    virtual bool giveFocus(ComponentPtr NewFocusedComponent, bool Temporary= false);
    virtual BorderPtr getDrawnBorder(void) const;
    virtual LayerPtr getDrawnBackground(void) const;
    virtual LayerPtr getDrawnForeground(void) const;

    class ComponentUpdater : public UpdateListener
    {
    public:
        ComponentUpdater(ComponentPtr TheComponent);

        virtual void update(const UpdateEventPtr e);
    private:
        ComponentPtr _Component;
    };

    class DeactivateToolTipListener : public MouseListener
    {
    public:
        DeactivateToolTipListener(ComponentPtr TheComponent);

        virtual void mouseClicked(const MouseEventPtr e);
        virtual void mouseEntered(const MouseEventPtr e);
        virtual void mouseExited(const MouseEventPtr e);
        virtual void mousePressed(const MouseEventPtr e);
        virtual void mouseReleased(const MouseEventPtr e);
    private:
        ComponentPtr _Component;
    };

    class ActivateToolTipListener : public MouseListener
    {
    public:
        ActivateToolTipListener(ComponentPtr TheComponent);

        virtual void mouseClicked(const MouseEventPtr e);
        virtual void mouseEntered(const MouseEventPtr e);
        virtual void mouseExited(const MouseEventPtr e);
        virtual void mousePressed(const MouseEventPtr e);
        virtual void mouseReleased(const MouseEventPtr e);
    private:
        ComponentPtr _Component;
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

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComponentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Component &source);
	
	typedef std::set<MouseMotionListenerPtr> MouseMotionListenerSet;
    typedef MouseMotionListenerSet::iterator MouseMotionListenerSetItor;
    typedef MouseMotionListenerSet::const_iterator MouseMotionListenerSetConstItor;
	
    MouseMotionListenerSet       _MouseMotionListeners;
	
    virtual void produceMouseMoved(const MouseEventPtr e);
    virtual void produceMouseDragged(const MouseEventPtr e);

	typedef std::set<MouseWheelListenerPtr> MouseWheelListenerSet;
    typedef MouseWheelListenerSet::iterator MouseWheelListenerSetItor;
    typedef MouseWheelListenerSet::const_iterator MouseWheelListenerSetConstItor;
	
    MouseWheelListenerSet       _MouseWheelListeners;
	
    void produceMouseWheelMoved(const MouseWheelEventPtr e);
	
	typedef std::set<MouseListenerPtr> MouseListenerSet;
    typedef MouseListenerSet::iterator MouseListenerSetItor;
    typedef MouseListenerSet::const_iterator MouseListenerSetConstItor;
	
    MouseListenerSet       _MouseListeners;
	
    void produceMouseClicked(const MouseEventPtr e);
    void produceMouseEntered(const MouseEventPtr e);
    void produceMouseExited(const MouseEventPtr e);
    void produceMousePressed(const MouseEventPtr e);
    void produceMouseReleased(const MouseEventPtr e);
	
	typedef std::set<KeyListenerPtr> KeyListenerSet;
    typedef KeyListenerSet::iterator KeyListenerSetItor;
    typedef KeyListenerSet::const_iterator KeyListenerSetConstItor;
	
    KeyListenerSet       _KeyListeners;
	
    void produceKeyPressed(const KeyEventPtr e);
    void produceKeyReleased(const KeyEventPtr e);
    void produceKeyTyped(const KeyEventPtr e);
    
	typedef std::set<FocusListenerPtr> FocusListenerSet;
    typedef FocusListenerSet::iterator FocusListenerSetItor;
    typedef FocusListenerSet::const_iterator FocusListenerSetConstItor;
	
    FocusListenerSet       _FocusListeners;
    void produceFocusGained(const FocusEventPtr e);
    void produceFocusLost(const FocusEventPtr e);
    
	typedef std::set<ComponentListenerPtr> ComponentListenerSet;
    typedef ComponentListenerSet::iterator ComponentListenerSetItor;
    typedef ComponentListenerSet::const_iterator ComponentListenerSetConstItor;
	
    ComponentListenerSet       _ComponentListeners;
    void produceComponentHidden(const ComponentEventPtr e);
    void produceComponentVisible(const ComponentEventPtr e);
    void produceComponentMoved(const ComponentEventPtr e);
    void produceComponentResized(const ComponentEventPtr e);
    void produceComponentEnabled(const ComponentEventPtr e);
    void produceComponentDisabled(const ComponentEventPtr e);
	
};

typedef Component *ComponentP;

OSG_END_NAMESPACE

#include "OSGComponentBase.inl"
#include "OSGComponent.inl"

#endif /* _OSGCOMPONENT_H_ */
