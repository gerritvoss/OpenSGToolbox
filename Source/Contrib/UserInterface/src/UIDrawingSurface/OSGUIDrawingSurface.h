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

#ifndef _OSGUIDRAWINGSURFACE_H_
#define _OSGUIDRAWINGSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUIDrawingSurfaceBase.h"
#include "OSGWindowEventProducer.h"
#include "OSGGraphics.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawingSurface class. See \ref
           PageContribUserInterfaceUIDrawingSurface for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UIDrawingSurface : public UIDrawingSurfaceBase

{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UIDrawingSurfaceBase Inherited;
    typedef UIDrawingSurface     Self;

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

    void detachFromEventProducer(void);

	//Mouse Events
    void handleMouseClicked(MouseEventDetails* const e);
    void handleMouseEntered(MouseEventDetails* const e);
    void handleMouseExited(MouseEventDetails* const e);
    void handleMousePressed(MouseEventDetails* const e);
    void handleMouseReleased(MouseEventDetails* const e);

    boost::signals2::connection _MouseClickedConnection,
                                _MouseEnteredConnection,
                                _MouseExitedConnection,
                                _MousePressedConnection,
                                _MouseReleasedConnection;

	//Mouse Motion Events
    void handleMouseMoved(MouseEventDetails* const e);
    void handleMouseDragged(MouseEventDetails* const e);

    boost::signals2::connection _MouseMovedConnection,
                                _MouseDraggedConnection;

	//Mouse Wheel Events
    void handleMouseWheelMoved(MouseWheelEventDetails* const e);
    boost::signals2::connection _MouseWheelMovedConnection;

	//Key Events
	void handleKeyPressed(KeyEventDetails* const e);
	void handleKeyReleased(KeyEventDetails* const e);
	void handleKeyTyped(KeyEventDetails* const e);

    boost::signals2::connection _KeyPressedConnection,
                                _KeyReleasedConnection,
                                _KeyTypedConnection;

    virtual Pnt2f getMousePosition(void) const;

	virtual UInt32 getNumWindowLayers(void) const;
	virtual Int32 getWindowLayer(InternalWindow* const TheWindow) const;
	virtual InternalWindow* getWindowAtLayer(const UInt32& Layer) const;
	virtual void setWindowToLayer(InternalWindow* const TheWindow, const UInt32& Layer);
	virtual void moveWindowUp(InternalWindow* const TheWindow);
	virtual void moveWindowDown(InternalWindow* const TheWindow);
	virtual void moveWindowToTop(InternalWindow* const TheWindow);
	virtual void moveWindowToBottom(InternalWindow* const TheWindow);

	virtual void openWindow(InternalWindow* const TheWindow, const Int32 Layer = -1);
	virtual void closeWindow(InternalWindow* const TheWindow);

    void updateWindowLayouts(void);
    void updateWindowLayout(InternalWindow* const TheWindow);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UIDrawingSurfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIDrawingSurface(void);
    UIDrawingSurface(const UIDrawingSurface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIDrawingSurface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void checkMouseEnterExit(InputEventDetails* const e, const Pnt2f& MouseLocation, Viewport* const TheViewport);

    std::set<InternalWindow*> _WindowsToClose;
    bool _IsProcessingEvents;
    void closeWindows(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UIDrawingSurfaceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UIDrawingSurface &source);
};

typedef UIDrawingSurface *UIDrawingSurfaceP;

OSG_END_NAMESPACE

#include "OSGInternalWindow.h"

#include "OSGUIDrawingSurfaceBase.inl"
#include "OSGUIDrawingSurface.inl"

#endif /* _OSGUIDRAWINGSURFACE_H_ */
