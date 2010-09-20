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
#include "OSGKeyEventDetails.h"
#include "OSGActionEventDetailsFields.h"

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
	virtual void keyPressed(KeyEventDetails* const e);
	virtual void keyReleased(KeyEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);

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
    void destroyPopupMenu(void);
    
    virtual void updateLayout(void);
    virtual void getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getMenuBarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
    virtual void getContentPaneBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;

	bool giveFocus(Component* const NewFocusedComponent, bool Temporary = false);
	bool takeFocus(bool Temporary = false);

    boost::signals2::connection connectKeyAccelerator(KeyEventDetails::Key TheKey, 
                                                      UInt32 Modifiers,
                                                      const KeyPressedEventType::slot_type &listener,
                                                      boost::signals2::connect_position at= boost::signals2::at_front);

    boost::signals2::connection connectKeyAccelerator(KeyEventDetails::Key TheKey, 
                                                      UInt32 Modifiers,
                                                      const KeyPressedEventType::group_type &group,
                                                      const KeyPressedEventType::slot_type &listener,
                                                      boost::signals2::connect_position at= boost::signals2::at_front);
    
    static void handleKeyAcceleratorCheck(KeyEventDetails* const details,
                                          boost::function<bool (KeyEventDetails* const)> predicateFunc,
                                          KeyPressedEventType::slot_type &listener);

    static bool doKeyDetailsMatch(KeyEventDetails* const Details,
                                  KeyEventDetails::Key   Key,
                                  UInt32                 Modifires);

	enum WindowArea
    {
        WINDOW_OUTSIDE=0,
        WINDOW_LEFT_BORDER=1,
        WINDOW_RIGHT_BORDER=2,
        WINDOW_TOP_BORDER=3,
        WINDOW_BOTTOM_BORDER=4,
        WINDOW_TOP_LEFT_BORDER=5,
        WINDOW_TOP_RIGHT_BORDER=6,
        WINDOW_BOTTOM_LEFT_BORDER=7,
        WINDOW_BOTTOM_RIGHT_BORDER=8,
        WINDOW_TITLE_BAR=9,
        WINDOW_MAIN_PANEL=10
    };

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

    virtual InternalWindow* getParentWindow(void) const;

    virtual void setParentWindow(InternalWindow* const parent);

    virtual void updateContainerLayout(void);
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
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const InternalWindow *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    
	virtual void drawInternal(Graphics* const TheGraphics, Real32 Opacity = 1.0f) const;
	virtual void drawUnclipped(Graphics* const TheGraphics, Real32 Opacity = 1.0f) const;
	
    void popupMenuMouseClicked(MouseEventDetails* const e);
	void popupMenuMousePressed(MouseEventDetails* const e);
    void popupMenuMouseReleased(MouseEventDetails* const e);
	void popupMenuKeyPressed(KeyEventDetails* const e);
	void popupMenuMouseMoved(MouseEventDetails* const e);
    void popupMenuMouseDragged(MouseEventDetails* const e);

    std::map<PopupMenu* const, std::vector<boost::shared_ptr<boost::signals2::scoped_connection> > > _PopupConnections;

    //typedef std::map<UInt64, KeyAcceleratorListenerPtr> KeyAcceleratorMap;
    //typedef KeyAcceleratorMap::iterator KeyAcceleratorMapItor;
    //KeyAcceleratorMap _KeyAcceleratorMap;
	
    void titlebarMousePressed(MouseEventDetails* const e);
    boost::signals2::connection _TitleBarMousePressedConnection;

	virtual void titlebarDragMouseDragged(MouseEventDetails* const e);
	virtual void titlebarDragMouseReleased(MouseEventDetails* const e);
	virtual void titlebarDragKeyPressed(KeyEventDetails* const e);

    boost::signals2::connection _TitlebarDragMouseDraggedConnection,
                                _TitlebarDragMouseReleasedConnection,
                                _TitlebarDragKeyPressedConnection;

	Pnt2f _WindowStartPosition;
	Pnt2f _MouseStartPosition;

	void borderDragMouseDragged(MouseEventDetails* const e);
	void borderDragMouseReleased(MouseEventDetails* const e);
	void borderDragKeyPressed(KeyEventDetails* const e);

    boost::signals2::connection _BorderDragMouseDraggedConnection,
                                _BorderDragMouseReleasedConnection,
                                _BorderDragKeyPressedConnection;

	Vec2f _WindowStartSize;
	WindowArea _BorderDragged;
	
	//CloseButton
	void closeButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _CloseButtonActionConnection;
	
	//MaximizeButton
	void maximizeButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _MaximizeButtonActionConnection;

	//IconifyButton
	void iconifyButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _IconifyButtonActionConnection;
	
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
