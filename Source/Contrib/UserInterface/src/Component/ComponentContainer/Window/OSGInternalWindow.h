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

#ifndef _OSGINTERNALWINDOW_H_
#define _OSGINTERNALWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGInternalWindowBase.h"
#include "OSGMouseAdapter.h"
#include "OSGMouseMotionAdapter.h"
#include "OSGKeyAdapter.h"
#include "OSGKeyAcceleratorListener.h"
#include "OSGActionListener.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief InternalWindow class. See \ref
           PageContribUserInterfaceInternalWindow for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING InternalWindow : public InternalWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef InternalWindowBase Inherited;
    typedef InternalWindow     Self;

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
	//Key Events
	virtual void keyPressed(const KeyEventUnrecPtr e);
	virtual void keyReleased(const KeyEventUnrecPtr e);
	virtual void keyTyped(const KeyEventUnrecPtr e);

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
    void destroyPopupMenu(void);
    
    virtual void updateLayout(void);
    virtual void getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getMenuBarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getContentPaneBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;


    virtual InternalWindow *            getParentWindow    (void) const;

	bool giveFocus(ComponentRefPtr NewFocusedComponent, bool Temporary = false);
	bool takeFocus(bool Temporary = false);

    EventConnection addKeyAccelerator(KeyEvent::Key TheKey, UInt32 Modifiers, KeyAcceleratorListenerPtr Listener);
    bool isKeyAcceleratorAttached(KeyEvent::Key TheKey, UInt32 Modifiers) const;
    void removeKeyAccelerator(KeyEvent::Key TheKey, UInt32 Modifiers);

	enum WindowArea{WINDOW_OUTSIDE=0, WINDOW_LEFT_BORDER, WINDOW_RIGHT_BORDER, WINDOW_TOP_BORDER, WINDOW_BOTTOM_BORDER, WINDOW_TOP_LEFT_BORDER, WINDOW_TOP_RIGHT_BORDER, WINDOW_BOTTOM_LEFT_BORDER, WINDOW_BOTTOM_RIGHT_BORDER, WINDOW_TITLE_BAR, WINDOW_MAIN_PANEL};
	virtual WindowArea getCursurArea(const Pnt2f& DrawingSurfaceLocation) const;
	
    //Set the Window Iconify
    void setIconify(bool Iconify);

    //Get the Window Iconify
    bool getIconify(void) const;

	void setMaximize(bool Maximize);

	bool getMaximize(void) const;

	virtual void open(void);

	virtual void close(void);

    void detachFromEventProducer(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in InternalWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    InternalWindow(void);
    InternalWindow(const InternalWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~InternalWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	virtual void drawInternal(const GraphicsWeakPtr TheGraphics, Real32 Opacity = 1.0f) const;
	virtual void drawUnclipped(const GraphicsWeakPtr TheGraphics, Real32 Opacity = 1.0f) const;
	
	class PopupMenuInteractionListener : public MouseAdapter, public MouseMotionAdapter, public KeyAdapter
	{
	public :
		PopupMenuInteractionListener(InternalWindowRefPtr TheInternalWindow);
		
        virtual void mouseClicked(const MouseEventUnrecPtr e);
		virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);
		virtual void keyPressed(const KeyEventUnrecPtr e);
		virtual void mouseMoved(const MouseEventUnrecPtr e);
        virtual void mouseDragged(const MouseEventUnrecPtr e);

        void disconnect(void);

	protected :
		InternalWindowRefPtr _InternalWindow;
	};

	friend class PopupMenuInteractionListener;

	PopupMenuInteractionListener _PopupMenuInteractionListener;

    typedef std::map<UInt64, KeyAcceleratorListenerPtr> KeyAcceleratorMap;
    typedef KeyAcceleratorMap::iterator KeyAcceleratorMapItor;
    KeyAcceleratorMap _KeyAcceleratorMap;
	
	class TitlebarStartDragListener : public MouseAdapter
	{
	public :
		TitlebarStartDragListener(InternalWindowRefPtr TheInternalWindow);
		
		virtual void mousePressed(const MouseEventUnrecPtr e);
	protected :
		InternalWindowRefPtr _InternalWindow;
	};

	friend class TitlebarStartDragListener;

	TitlebarStartDragListener _TitlebarStartDragListener;

	class TitlebarDraggedListener : public MouseMotionAdapter, public MouseAdapter, public KeyAdapter
	{
	public :
		TitlebarDraggedListener(InternalWindowRefPtr TheInternalWindow);
		virtual void mouseDragged(const MouseEventUnrecPtr e);
		
		virtual void mouseReleased(const MouseEventUnrecPtr e);

		virtual void keyPressed(const KeyEventUnrecPtr e);

		void setWindowStartPosition(const Pnt2f& Pos);
		void setMouseStartPosition(const Pnt2f& Pos);

        void disconnect(void);
	protected :
		InternalWindowRefPtr _InternalWindow;

		Pnt2f _WindowStartPosition;
		Pnt2f _MouseStartPosition;
	};

	friend class TitlebarDraggedListener;

	TitlebarDraggedListener _TitlebarDraggedListener;
	
	class BorderDraggedListener : public MouseMotionAdapter, public MouseAdapter, public KeyAdapter
	{
	public :
		BorderDraggedListener(InternalWindowRefPtr TheInternalWindow);
		virtual void mouseDragged(const MouseEventUnrecPtr e);
		
		virtual void mouseReleased(const MouseEventUnrecPtr e);
		
		virtual void keyPressed(const KeyEventUnrecPtr e);

		void setWindowStartPosition(const Pnt2f& Pos);
		void setWindowStartSize(const Vec2f& Size);
		void setMouseStartPosition(const Pnt2f& Pos);
		void setBorderDragged(const WindowArea Value);

        void disconnect(void);

	protected :
		InternalWindowRefPtr _InternalWindow;

		Pnt2f _WindowStartPosition;
		Vec2f _WindowStartSize;
		Pnt2f _MouseStartPosition;

		WindowArea _BorderDragged;
	};

	friend class BorderDraggedListener;

	BorderDraggedListener _BorderDraggedListener;
	
	//Titlebar Action Listeners
	//CloseButton
	class CloseButtonListener : public ActionListener
	{
	public :
		CloseButtonListener(InternalWindowRefPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEventUnrecPtr e);
	protected :
		InternalWindowRefPtr _InternalWindow;
	};

	friend class CloseButtonListener;

	CloseButtonListener _CloseButtonListener;
	
	//MaximizeButton
	class MaximizeButtonListener : public ActionListener
	{
	public :
		MaximizeButtonListener(InternalWindowRefPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEventUnrecPtr e);
	protected :
		InternalWindowRefPtr _InternalWindow;
	};

	friend class MaximizeButtonListener;

	MaximizeButtonListener _MaximizeButtonListener;
	
	//IconifyButton
	class IconifyButtonListener : public ActionListener
	{
	public :
		IconifyButtonListener(InternalWindowRefPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEventUnrecPtr e);
	protected :
		InternalWindowRefPtr _InternalWindow;
	};

	friend class IconifyButtonListener;

	IconifyButtonListener _IconifyButtonListener;
	virtual UInt32 queryCursor(const Pnt2f& CursorLoc) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class InternalWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const InternalWindow &source);
};

typedef InternalWindow *InternalWindowP;

OSG_END_NAMESPACE

#include "OSGPopupMenu.h"
#include "OSGToolTip.h"
#include "OSGTitlebar.h"
#include "OSGMenuBar.h"

#include "OSGInternalWindowBase.inl"
#include "OSGInternalWindow.inl"

#endif /* _OSGINTERNALWINDOW_H_ */
