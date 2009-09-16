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

#ifndef _OSGINTERNALWINDOW_H_
#define _OSGINTERNALWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGInternalWindowBase.h"

#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGKeyAdapter.h>
#include "Event/OSGKeyAcceleratorListener.h"
#include "Event/OSGActionListener.h"

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief InternalWindow class. See \ref 
           PageUserInterfaceInternalWindow for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING InternalWindow : public InternalWindowBase
{
  private:

    typedef InternalWindowBase Inherited;

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
	//Key Events
	virtual void keyPressed(const KeyEvent& e);
	virtual void keyReleased(const KeyEvent& e);
	virtual void keyTyped(const KeyEvent& e);

	//Mouse Events
    virtual void mouseClicked(const MouseEvent& e);
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEvent& e);
    void destroyPopupMenu(void);
    
    virtual void updateLayout(void);
    virtual void getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getMenuBarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getContentPaneBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;


    virtual       InternalWindowPtr            &getParentWindow    (void);
    virtual const InternalWindowPtr            &getParentWindow    (void) const;
	

	bool giveFocus(ComponentPtr NewFocusedComponent, bool Temporary = false);
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
    
	virtual void drawInternal(const GraphicsPtr TheGraphics) const;
	virtual void drawUnclipped(const GraphicsPtr TheGraphics) const;
	
	class PopupMenuInteractionListener : public MouseAdapter, public MouseMotionAdapter, public KeyAdapter
	{
	public :
		PopupMenuInteractionListener(InternalWindowPtr TheInternalWindow);
		
        virtual void mouseClicked(const MouseEvent& e);
		virtual void mousePressed(const MouseEvent& e);
        virtual void mouseReleased(const MouseEvent& e);
		virtual void keyPressed(const KeyEvent& e);
		virtual void mouseMoved(const MouseEvent& e);
        virtual void mouseDragged(const MouseEvent& e);
	protected :
		InternalWindowPtr _InternalWindow;
	};

	friend class PopupMenuInteractionListener;

	PopupMenuInteractionListener _PopupMenuInteractionListener;

    typedef std::map<UInt64, KeyAcceleratorListenerPtr> KeyAcceleratorMap;
    typedef KeyAcceleratorMap::iterator KeyAcceleratorMapItor;
    KeyAcceleratorMap _KeyAcceleratorMap;
	
	class TitlebarStartDragListener : public MouseAdapter
	{
	public :
		TitlebarStartDragListener(InternalWindowPtr TheInternalWindow);
		
		virtual void mousePressed(const MouseEvent& e);
	protected :
		InternalWindowPtr _InternalWindow;
	};

	friend class TitlebarStartDragListener;

	TitlebarStartDragListener _TitlebarStartDragListener;

	class TitlebarDraggedListener : public MouseMotionAdapter, public MouseAdapter, public KeyAdapter
	{
	public :
		TitlebarDraggedListener(InternalWindowPtr TheInternalWindow);
		virtual void mouseDragged(const MouseEvent& e);
		
		virtual void mouseReleased(const MouseEvent& e);

		virtual void keyPressed(const KeyEvent& e);

		void setWindowStartPosition(const Pnt2f& Pos);
		void setMouseStartPosition(const Pnt2f& Pos);
	protected :
		InternalWindowPtr _InternalWindow;

		Pnt2f _WindowStartPosition;
		Pnt2f _MouseStartPosition;
	};

	friend class TitlebarDraggedListener;

	TitlebarDraggedListener _TitlebarDraggedListener;
	
	class BorderDraggedListener : public MouseMotionAdapter, public MouseAdapter, public KeyAdapter
	{
	public :
		BorderDraggedListener(InternalWindowPtr TheInternalWindow);
		virtual void mouseDragged(const MouseEvent& e);
		
		virtual void mouseReleased(const MouseEvent& e);
		
		virtual void keyPressed(const KeyEvent& e);

		void setWindowStartPosition(const Pnt2f& Pos);
		void setWindowStartSize(const Vec2f& Size);
		void setMouseStartPosition(const Pnt2f& Pos);
		void setBorderDragged(const WindowArea Value);
	protected :
		InternalWindowPtr _InternalWindow;

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
		CloseButtonListener(InternalWindowPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEvent& e);
	protected :
		InternalWindowPtr _InternalWindow;
	};

	friend class CloseButtonListener;

	CloseButtonListener _CloseButtonListener;
	
	//MaximizeButton
	class MaximizeButtonListener : public ActionListener
	{
	public :
		MaximizeButtonListener(InternalWindowPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEvent& e);
	protected :
		InternalWindowPtr _InternalWindow;
	};

	friend class MaximizeButtonListener;

	MaximizeButtonListener _MaximizeButtonListener;
	
	//IconifyButton
	class IconifyButtonListener : public ActionListener
	{
	public :
		IconifyButtonListener(InternalWindowPtr TheInternalWindow);
		
		virtual void actionPerformed(const ActionEvent& e);
	protected :
		InternalWindowPtr _InternalWindow;
	};

	friend class IconifyButtonListener;

	IconifyButtonListener _IconifyButtonListener;
	virtual UInt32 queryCursor(const Pnt2f& CursorLoc) const;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class InternalWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const InternalWindow &source);
};

typedef InternalWindow *InternalWindowP;

OSG_END_NAMESPACE

#include "OSGInternalWindowBase.inl"
#include "OSGInternalWindow.inl"

#define OSGINTERNALWINDOW_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGINTERNALWINDOW_H_ */
