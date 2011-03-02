/*---------------------------------------------------------------------------*\
 *                             OpenSGToolbox                                 *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2007-2011                                     *
 *                                                                           *
 *                        www.opensgtoolbox.org                              *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
 \*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library Lesser General Public License as       *
 * published  by the Free Software Foundation, version 3.                    *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library Lesser General Public License for more details.                   *
 *                                                                           *
 * You should have received a copy of the GNU Library Lesser General Public  *
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

#include "OSGInternalWindowFields.h"
#include "OSGComponentContainerFields.h"
#include "OSGUpdateEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*!\class Component
 *
 * \brief An element of a graphical user interface.
 *
 * A Component represents a single element of a user interface. In other
 * frameworks they may be called widgets or controls. All concrete GUI elements
 * inherit from Component, like OSG::Button, OSG::Label, OSG::TextField,
 * OSG::InternalWindow, etc.
 *
 * \par Component states:
 * Components have states for Enabled, Focused,
 * MouseOver, and Visible.  If a Component has Enabled == false, it doesn't receive
 * or produce any events. If a Component has Visible == false, it is not drawn. 
 *
 * \par Event response:
 * Components can respond to Mouse, Key, and Focus events.
 *
 * \par Event production:
 * Components produce Mouse, Key, Focus, Component, and
 * ToolTip events if enabled.
 *
 * \par Drawing:
 * Component handles setting up the clipping of a component, and
 * the drawing of the Border, Background, and Foreground.  The Border,
 * Background, and Foreground used when drawing a Component depends on it's
 * state, and can also be overridden by inheriting classes. There are separate
 * Border, Background, and Foregrounds for Disabled, Focused, Rollover, and <Empty>
 * states.
 *
 * \par Layout:
 * The position and size of a Component is controlled by the
 * OSG::ComponentContainer that contains it. For simple OSG::ComponentContainer
 * like OSG::Panel, the OSG::Layout attached to the container is used to control
 * the position and size of components.  For more complex containers like
 * OSG::SplitPanel, the position and size are controlled by the specific
 * behavior of the container.
 * \warning User code should never set the position or size of a Component
 * directly, this is controlled by the OSG::ComponentContainer of the Component.
 * 
 *
 * \par Focus:
 * Zero, or one Component can have focus in a OSG::InternalWindow.
 * Component has methods for taking, removing, or moving the focus.
 *
 * \par ToolTips:
 * A component can have a ToolTip that will appear after a
 * configurable amount of time passes with the mouse over the Component.
 *
 * \par PopupMenus:
 * A OSG::PopupMenu can be attached to a Component that will
 * be activated with a right-click mouse interaction.
 *
 * \par Scrolling:
 * Components can be contained in a OSG::Viewport or a
 * OSG::ScrollPanel for viewing large Components.
 *
 * \par Inheriting:
 * Concrete GUI elements that inherit from Component must
 * implement drawInternal().
 */

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Component : public ComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    /*! Scrolling characteristics */
    enum ScrollTrackingMasks
    {
        /*! All Scrolling characteristics off */
        SCROLLABLE_TRACKING_OFF               = 0,
        /*! Component height tracks the OSG::Viewport height */
        SCROLLABLE_TRACKS_VIEWPORT_HEIGHT     = 1,
        /*! Component width tracks the OSG::Viewport width */
        SCROLLABLE_TRACKS_VIEWPORT_WIDTH      = 2,
        /*! Component minimum height tracks the OSG::Viewport height */
        SCROLLABLE_HEIGHT_MIN_TRACKS_VIEWPORT = 4,
        /*! Component minimum width tracks the OSG::Viewport width */
        SCROLLABLE_WIDTH_MIN_TRACKS_VIEWPORT  = 8
    };

    typedef ComponentBase Inherited;
    typedef Component     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                     Drawing                                  */
    /*! \{                                                                 */

    /*!
     * \brief Draw this component.
     *
     * The Opacity value is multiplied by all of the opacity values of the
     * rendered primitives of this Component.  So, for example, if the Opacity
     * given is 0.5, and the background color opacity is 0.1, then the
     * background will be drawn with an opacity of 0.05.
     *
     * \param[in] TheGraphics The graphics object to use for rendering calls
     * \param[in] Opacity The opacity to render the component.
     */
    virtual void draw(Graphics* const TheGraphics, Real32 Opacity = 1.0f) const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                     Bounds                                   */
    /*! \{                                                                 */

    /*!
     * \brief Get the bounds of this Component in local space.
     *
     * \param[out] TopLeft The top-left of the boundary
     * \param[out] BottomRight The bottom-right of the boundary
     */
    virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

    /*!
     * \brief Get the clipping bounds of this component in local space
     *
     * \param[out] TopLeft The top-left of the boundary
     * \param[out] BottomRight The bottom-right of the boundary
     */
    virtual void getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    using Inherited::getClipBounds;

    /*!
     * \brief Get the bounds of this component, in local space, interior to
     * the border.
     *
     * This will determine the maximum interior bounds against all of the
     * borders that this component contains.  So, for example, if the
     * FocusedBorder is larger then the DisabledBorder, the dimensions from the
     * FocusedBorder will be used.
     *
     * \param[out] TopLeft The top-left of the boundary
     * \param[out] BottomRight The bottom-right of the boundary
     */
    virtual void getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

    /*!
     * \brief Get the bounds of this Component in rendering surface space.
     *
     * This method gives the same information as getBounds(), except that the
     * positions are in surface-space.
     *
     * \param[out] TopLeft The top-left of the boundary
     * \param[out] BottomRight The bottom-right of the boundary
     */
    virtual void getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

    /*!
     * \brief Force my parent container to update it's layout.
     */
    virtual void updateContainerLayout(void);

    /*!
     * \brief Update the values of my clipping boundaries.
     */
    virtual void updateClipBounds(void);

    /*!
     * \brief Get the requested size.
     *
     * The requested size is different from the preferred, min, or max sizes.
     * This is because it cannot be explicitly assigned.  Instead, based on the
     * concrete-type, of the Component it is the value that the Component
     * desires with respect to it's content.
     *
     * The requested size is computed from getContentRequestedSize() and the 
     * max size of the borders.
     */
    virtual Vec2f getRequestedSize(void) const;

    /*!
     * \brief Get the requested size of the contents of this Component.
     *
     * Gives the size requested for viewing the contents of this Component.
     * A OSG::Label calculates it's requested size with respect to the size of
     * the text it contains.
     */
    virtual Vec2f getContentRequestedSize(void) const;

    /*!
     * \brief Get the maximum x, and y lengths of the borders.
     */
    virtual Vec2f getBorderingLength(void) const;

    /*!
     * \brief Is a location contained in this Component.
     *
     * \param[in] Location A position in drawing surface space
     * \param[in] TestAgainstClipBounds If true, the location will be tested
     * against the clipping bounds.
     *
     * \returns true if the location is contained in this Component, false
     * otherwise.
     */
    virtual bool isContained(const Pnt2f& Location, bool TestAgainstClipBounds = true) const;

    /*!
     * \brief Get the vertical-baseline location.
     *
     * For Components with text, the baseline is the vertical location
     * corresponding to the line on which letters "sit".
     *
     * \param[in] x
     * \param[in] y
     */
    virtual Real32 getBaseline(const Real32& x, const Real32& y) const;


    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                     Events                                   */
    /*! \{                                                                 */

    /*!
     * \brief Handle a mouse clicked event.
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseClicked(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse clicked event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseEntered(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse button clicked event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseExited(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse button press event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mousePressed(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse button release event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseReleased(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse move event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseMoved(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse drag event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseDragged(MouseEventDetails* const e);

    /*!
     * \brief Handle a mouse wheel move event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

    /*!
     * \brief Handle a key pressed event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void keyPressed(KeyEventDetails* const e);

    /*!
     * \brief Handle a key released event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void keyReleased(KeyEventDetails* const e);

    /*!
     * \brief Handle a key typed event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void keyTyped(KeyEventDetails* const e);

    /*!
     * \brief Handle a focus gained event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void focusGained(FocusEventDetails* const e);

    /*!
     * \brief Handle a focus lost event. 
     *
     * \param[in] e The details of the event.
     */
    virtual void focusLost(FocusEventDetails* const e);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                     Focusing                                 */
    /*! \{                                                                 */

    /*!
     * \brief Take focus.
     *
     * \param[in] Temporary flag indicating whether this focus is temporary.
     */
    virtual bool takeFocus(bool Temporary = false);

    /*!
     * \brief Advance the focus by a given amount.
     *
     * \param[in] MoveAmount The number of focusable Components to advance the
     * focus by.  The focus is advanced by a depth-first ordering.
     */
    virtual void moveFocus(Int32 MoveAmount);

    /*!
     * \brief Move the focus to the next Component that accepts focusing.  This
     * moves in a depth-first ordering over the user interface graph.
     */
    void moveFocusNext(void);

    /*!
     * \brief Move the focus to the previous Component that accepts focusing.
     * This moves in a depth-first ordering over the user interface graph.
     */
    void moveFocusPrev(void);

    /*!
     * \brief Move the focus to closest Component in the positive X direction
     * that accepts focusing.
     */
    virtual void moveFocusPosX(void);

    /*!
     * \brief Move the focus to closest Component in the negative X direction
     * that accepts focusing.
     */
    virtual void moveFocusNegX(void);

    /*!
     * \brief Move the focus to closest Component in the positive Y direction
     * that accepts focusing.
     */
    virtual void moveFocusPosY(void);

    /*!
     * \brief Move the focus to closest Component in the negative Y direction
     * that accepts focusing.
     */
    virtual void moveFocusNegY(void);

    /*!
     * \brief Does this Component accept focusing.
     */
    virtual bool isFocusInteractable(void) const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                        Graph                                 */
    /*! \{                                                                 */

    /*!
     * \brief Get the component of my parent container with an index one greater
     * than mine.
     *
     * \returns The next sibling component, NULL if this component has the
     * highest index of all components contained by it's parent container.
     */
    Component* getNextSibling(void) const;

    /*!
     * \brief Get the component of my parent container with an index one less
     * than mine.
     *
     * \returns The previous sibling component, NULL if this component has the
     * lowest index of all components contained by it's parent container.
     */
    Component* getPrevSibling(void) const;

    /*!
     * \brief Get the descendent that is that follows the left side of this
     * subtree
     */
    virtual Component* getLeftmostDecendent(void) const;

    /*!
     * \brief Get the descendent that is that follows the right side of this
     * subtree
     */
    virtual Component* getRightmostDecendent(void) const;

    /*!
     * \brief Get the next depth-first ordering component.
     *
     * \returns The next depth-first ordering component. If the end is reached,
     * NULL is returned.
     */
    Component* getNextDepthFirstComponent(void) const;

    /*!
     * \brief Get the previous depth-first ordering component.
     *
     * \returns The previous depth-first ordering component. If the end is reached,
     * NULL is returned.
     */
    Component* getPrevDepthFirstComponent(void) const;

    /*!
     * \brief Get the closest sibling Component in the positive X direction
     * that accepts focusing.
     */
    Component* getNextSiblingInPosX(void) const;

    /*!
     * \brief Get the closest sibling Component in the negative X direction
     * that accepts focusing.
     */
    Component* getNextSiblingInNegX(void) const;

    /*!
     * \brief Get the closest sibling Component in the positive Y direction
     * that accepts focusing.
     */
    Component* getNextSiblingInPosY(void) const;

    /*!
     * \brief Get the closest sibling Component in the negative Y direction
     * that accepts focusing.
     */
    Component* getNextSiblingInNegY(void) const;

    /*!
     * \brief Is this Component an ancestor of the given Component.
     *
     * \param[in] TheComponent
     */
    bool isAncestor(Component* const TheComponent) const;
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Scrolling                                 */
    /*! \{                                                                 */

    /*!
     * \brief Get the preferred size of the OSG::UIViewport for a view component. 
     */
    virtual Vec2f getPreferredScrollableViewportSize(void);

    //
    /*!
     * \brief Get the scroll distance for a block scroll.
     *
     * Components that display logical rows or columns should compute the scroll
     * increment that will completely expose one block of rows or columns,
     * depending on the value of orientation.
     *
     * \param[in] VisibleRectTopLeft Top-left location of region this component
     * is located in a OSG::UIViewport.
     * \param[in] VisibleRectBottomRight Bottom-right location of region this
     * component is located in a OSG::UIViewport.
     * \param[in] orientation The orientation of the scroll. ScrollBar::Orientation
     * are the accepted values.
     * \param[in] direction Number of block units to scroll.
     *
     * \returns Distance to scroll.
     */
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft,
                                              const Pnt2f& VisibleRectBottomRight,
                                              const UInt32& orientation,
                                              const Int32& direction);

    /*!
     * \brief Should a OSG::UIViewport force this component to match the OSG::UIViewport
     * height.
     *
     * \return true if a OSG::UIViewport should always force the height of this
     * Scrollable to match the height of the OSG::UIViewport.
     */
    virtual bool getScrollableTracksViewportHeight(void);

    /*!
     * \brief Should a OSG::UIViewport force this component to match the OSG::UIViewport
     * width.
     *
     * \return true if a OSG::UIViewport should always force the width of this
     * Scrollable to match the width of the OSG::UIViewport.
     */
    virtual bool getScrollableTracksViewportWidth(void);

    /*!
     * \brief Should a OSG::UIViewport force this components minimum height to
     * match the OSG::UIViewport height.
     *
     * \returns true if a OSG::UIViewport should always force the height of this
     * Scrollable to be at at least the height of the OSG::UIViewport
     */
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return .
    /*!
     * \brief Should a OSG::UIViewport force this components minimum width to
     * match the OSG::UIViewport width.
     *
     * \returns true if a OSG::UIViewport should always force the width of this
     * Scrollable to be at at least the width of the OSG::UIViewport
     */
    virtual bool getScrollableWidthMinTracksViewport(void);

    /*!
     * \brief Sets this component to match the height of a containing
     * OSG::UIViewport
     */
    void setScrollableTracksViewportHeight(bool enable);

    /*!
     * \brief Sets this component to match the width of a containing
     * OSG::UIViewport
     *
     * \param[in] enable
     */
    void setScrollableTracksViewportWidth(bool enable);

    /*!
     * \brief Sets this component to match it's minimum height to the height of
     * a containing OSG::UIViewport
     *
     * \param[in] enable
     */
    void setScrollableHeightMinTracksViewport(bool enable);

    /*!
     * \brief Sets this component to match it's minimum height to the height of
     * a containing OSG::UIViewport
     *
     * \param[in] enable
     */
    void setScrollableWidthMinTracksViewport(bool enable);

    //.
    /*!
     * \brief Get the scroll distance for a unit scroll.
     *
     * Components that display logical rows or columns should compute the scroll
     * increment that will completely expose one new row or column, depending on
     * the value of orientation.
     *
     * \param[in] VisibleRectTopLeft Top-left location of region this component
     * is located in a OSG::UIViewport.
     * \param[in] VisibleRectBottomRight Bottom-right location of region this
     * component is located in a OSG::UIViewport.
     * \param[in] orientation The orientation of the scroll. ScrollBar::Orientation
     * are the accepted values.
     * \param[in] direction Number of block units to scroll.
     *
     * \returns Distance to scroll.
     */
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft,
                                             const Pnt2f& VisibleRectBottomRight,
                                             const UInt32& orientation,
                                             const Int32& direction);

    /*!
     * \brief Scroll to a location.
     *
     * \param[in] PointInComponent The location, in local space to scroll to.
     */
    virtual void scrollToPoint(const Pnt2f& PointInComponent);
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                     Drawing                                  */
    /*! \{                                                                 */

    static const OSG::BitVector BordersFieldMask;
    /*!
     * \brief Set all of the borders to a single value.
     *
     * \param[in] TheBorder
     */
    virtual void setBorders(Border * const TheBorder);

    static const OSG::BitVector BackgroundsFieldMask;
    /*!
     * \brief Set all of the backgrounds to a single value.
     *
     * \param[in] TheBackground
     */
    virtual void setBackgrounds(Layer* const TheBackground);

    static const OSG::BitVector ForegroundsFieldMask;
    /*!
     * \brief Set all of the foregrounds to a single value.
     *
     * \param[in] TheForeground
     */
    virtual void setForegrounds(Layer* const TheForeground);

    /*!
     * \brief Detach from Event producer.
     *
     * This method disconnects all Event connections related to the
     * EventProducer it may be attached to.
     */
    virtual void detachFromEventProducer(void);

    /*!
     * \brief Indicate that the mouse was in this component last update.
     *
     * \param[in] Value
     */
    void setMouseContained(bool Value);

    /*!
     * \brief Get whether the mouse contained in this Component last update.
     */
    bool getMouseContained(void);


    /*!
     * \brief Given a point in parent space get the local space location.
     *
     * \param[in] Location The location in parent space.
     *
     * \returns The location in local space.
     */
    virtual Pnt2f getParentToLocal(const Pnt2f& Location) const;

    /*!
     * \brief Given a point in local space get the parent space location.
     *
     * \param[in] Location The location in local space.
     *
     * \returns The location in parent space.
     */
    virtual Pnt2f getLocalToParent(const Pnt2f& Location) const;

    /*!
     * \brief Get the parent window.
     *
     * \returns The parent window; NULL if there is none.
     */
    virtual InternalWindow* getParentWindow(void) const;

    /*!
     * \brief Set the parent window.
     *
     * \param[in] parent
     */
    virtual void setParentWindow(InternalWindow* const parent);

    /*!
     * \brief Get the parent container.
     *
     * \returns The parent container; NULL if there is none.
     */
    virtual ComponentContainer* getParentContainer(void) const;
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  ToolTips                                    */
    /*! \{                                                                 */

    /*!
     * \brief Create a default ToolTip.
     *
     * The DefaultToolTip defined by the currently active OSG::LookAndFeel is
     * cloned.
     */
    virtual ComponentTransitPtr createDefaultToolTip(void);

    /*! \brief Create a default ToolTip and insert it with text
     *
     * If the type of the ToolTip is derived from
     * OSG::TextComponent, then the text of the component is set with the text
     * given as a parameter to this method.
     *
     *  \param[in] ToolTipText The text of the ToolTip
     */
    virtual void setToolTipText(const std::string& ToolTipText);

    /*!
     * \brief Is the ToolTip for this Component active
     *
     * \returns true if the ToolTip of this Component is active, false otherwise
     */
    bool isToolTipActive(void) const;

    /*!
     * \brief Activate the ToolTip on this Component
     *
     * If the ToolTips is already active, or there is no ToolTip associated with
     * this Component, then nothing is done.
     */
    void activateToolTip(void);

    /*!
     * \brief Deactivate the ToolTip of this Component
     *
     * If the ToolTips is not already active, or there is no ToolTip associated with
     * this Component, then nothing is done.
     */
    void deactivateToolTip(void);

    /*!
     * \brief Set the location of the ToolTip in Component space
     *
     * \param[in] Location Location, in Component space, to put the ToolTip
     */
    void setToolTipLocation(const Pnt2f& Location);

    /*!
     * \brief Get the location of the ToolTip in Component space
     *
     * \returns The location of the ToolTip in Component space. The value retured is
     * Pnt2f(0.0f,0.0f) if the ToolTip is not active.
     */
    Pnt2f getToolTipLocation(void) const;

    /*! \}                                                                 */

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

    /*---------------------------------------------------------------------*/
    /*! \name               Drawing decorations                            */
    /*! \{                                                                 */
    virtual Border* getDrawnBorder    (void) const;
    virtual Layer*  getDrawnBackground(void) const;
    virtual Layer*  getDrawnForeground(void) const;

    virtual void drawBorder    (Graphics* const TheGraphics,
                                const Border*   Border,
                                Real32          Opacity       ) const;

    virtual void drawBackground(Graphics* const TheGraphics,
                                const Layer*    Background,
                                Real32          Opacity       ) const;

    virtual void drawForeground(Graphics* const TheGraphics,
                                const Layer*    Foreground,
                                Real32          Opacity       ) const;
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Internal drawing                            */
    /*! \{                                                                 */
    virtual void drawInternal(Graphics* const   TheGraphics,
                              Real32            Opacity = 1.0f) const = 0;

    virtual void drawUnclipped(Graphics* const   TheGraphics,
                               Real32            Opacity      ) const;

    virtual bool  setupClipping       (Graphics* const TheGraphics) const;
    virtual bool  useBoundsForClipping(void                       ) const;
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  Event production                            */
    /*! \{                                                                 */
    void produceComponentResized  (void);
    void produceComponentMoved    (void);
    void produceComponentEnabled  (void);
    void produceComponentDisabled (void);
    void produceComponentVisible  (void);
    void produceComponentHidden   (void);
    void produceToolTipActivated  (void);
    void produceToolTipDeactivated(void);
    /*! \}                                                                 */

    virtual bool giveFocus(Component* const NewFocusedComponent,
                           bool Temporary= false);

    virtual Pnt2f getClipTopLeft      (void                    ) const;
    virtual Pnt2f getClipBottomRight  (void                    ) const;
    virtual void  setClipTopLeft      (const Pnt2f &value      );
    virtual void  setClipBottomRight  (const Pnt2f &value      );

    virtual UInt32 queryCursor(const Pnt2f& CursorLoc) const;


    void handleToolTipActivateUpdate(UpdateEventDetails* const e);
    void handleToolTipActivateMouseEntered(MouseEventDetails* const e);
    void handleToolTipActivateMouseExited(MouseEventDetails* const e);

    void handleDeactivateToolTipEvent(MouseEventDetails* const e);

    boost::signals2::connection _ToolTipActivateUpdateConnection;

    boost::signals2::connection _ToolTipActivateMouseEnterConnection,
        _ToolTipActivateMouseExitConnection;

    boost::signals2::connection _ActiveTooltipClickConnection,
                                _ActiveTooltipExitConnection,
                                _ActiveTooltipPressConnection,
                                _ActiveTooltipReleaseConnection;

    Real32 _TimeSinceMouseEntered;

    bool _MouseInComponentLastMouse;
    bool _IsToolTipActive;

    InternalWindow* _ParentWindow;


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
