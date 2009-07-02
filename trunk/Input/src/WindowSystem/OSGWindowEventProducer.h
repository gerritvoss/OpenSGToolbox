/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGWINDOWEVENTPRODUCER_H_
#define _OSGWINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <set>
#include <vector>
#include <map>
#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/Toolbox/OSGPathType.h>

#include "OSGWindowEventProducerBase.h"


#include "Event/OSGEventConnection.h"
#include "Event/OSGMouseListener.h"
#include "Event/OSGMouseMotionListener.h"
#include "Event/OSGMouseWheelListener.h"
#include "Event/OSGWindowListener.h"
#include "Event/OSGKeyListener.h"
#include "Event/OSGUpdateListener.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING WindowVisualFormat{
public:
	UInt8 _PixelSize;
	UInt8 _RedSize;
	UInt8 _GreenSize;
	UInt8 _BlueSize;
	UInt8 _AlphaSize;
	
	UInt8 _DepthBufferSize;
	UInt8 _StencilBufferSize;
	
	UInt8 _AccumRedSize;
	UInt8 _AccumGreenSize;
	UInt8 _AccumBlueSize;
	UInt8 _AccumAlphaSize;

	UInt8 _AuxiliaryBufferCount;

	bool _DoubleBuffer;
	bool _Stereo;

	bool _RGBA;
	bool _ColorIndex;

	bool _Multisample;
	UInt8 _SampleBuffers;

	bool _SuperSample;
};

class OSG_INPUTLIB_DLLMAPPING WindowEventProducer : public WindowEventProducerBase
{
  protected:

    typedef WindowEventProducerBase Inherited;

	typedef std::set<MouseListenerPtr> MouseListenerSet;
    typedef MouseListenerSet::iterator MouseListenerSetItor;
    typedef MouseListenerSet::const_iterator MouseListenerSetConstItor;
    typedef std::set<MouseMotionListenerPtr> MouseMotionListenerSet;
    typedef MouseMotionListenerSet::iterator MouseMotionListenerSetItor;
    typedef MouseMotionListenerSet::const_iterator MouseMotionListenerSetConstItor;
    typedef std::set<MouseWheelListenerPtr> MouseWheelListenerSet;
    typedef MouseWheelListenerSet::iterator MouseWheelListenerSetItor;
    typedef MouseWheelListenerSet::const_iterator MouseWheelListenerSetConstItor;
    typedef std::set<KeyListenerPtr> KeyListenerSet;
    typedef KeyListenerSet::iterator KeyListenerSetItor;
    typedef KeyListenerSet::const_iterator KeyListenerSetConstItor;
	
	typedef std::set<WindowListenerPtr> WindowListenerSet;
    typedef WindowListenerSet::iterator WindowListenerSetItor;
    typedef WindowListenerSet::const_iterator WindowListenerSetConstItor;

    MouseListenerSet       _MouseListeners;
    MouseMotionListenerSet _MouseMotionListeners;
    MouseWheelListenerSet  _MouseWheelListeners;
    KeyListenerSet         _KeyListeners;
    WindowListenerSet       _WindowListeners;

	typedef std::set<UpdateListenerPtr> UpdateListenerSet;
    typedef UpdateListenerSet::iterator UpdateListenerSetItor;
    typedef UpdateListenerSet::const_iterator UpdateListenerSetConstItor;
	
    UpdateListenerSet       _UpdateListeners;

    struct Click
    {
       Time _TimeStamp;
       Pnt2f _Location;

       Click(Time TimeStamp, Pnt2f Location);
    };
    typedef std::vector<Click> ClickVector;
    typedef ClickVector::iterator ClickVectorIter;
    typedef ClickVector::const_iterator ClickVectorConstIter;

    typedef std::map<MouseEvent::MouseButton, ClickVector> ButtonClickCountMap;
    typedef std::map<MouseEvent::MouseButton, Pnt2f> ButtonClickMap;

    ButtonClickCountMap _ButtonClickCountMap;
    ButtonClickMap _ButtonClickMap;

    Thread* _WindowEventLoopThread;

    typedef void (*DisplayCallbackFunc)(void);
    typedef void (*ReshapeCallbackFunc)(Vec2f);

    DisplayCallbackFunc _DisplayCallbackFunc;
    ReshapeCallbackFunc _ReshapeCallbackFunc;
	RenderAction *      _RenderAction;

    /*==========================  PUBLIC  =================================*/
  public:

    class FileDialogFilter
    {
    public:
        FileDialogFilter(const std::string& Name, const std::string& Filter);

        const std::string& getName(void) const;
        const std::string& getFilter(void) const;
    private:
        std::string _Name;
        std::string _Filter;
    };

	enum CursorType {CURSOR_POINTER=0, CURSOR_HAND, CURSOR_I_BEAM, CURSOR_WAIT, CURSOR_RESIZE_W_TO_E, CURSOR_RESIZE_N_TO_S, CURSOR_RESIZE_NW_TO_SE, CURSOR_RESIZE_SW_TO_NE, CURSOR_RESIZE_ALL, CURSOR_NONE};

    struct CursorRegion
	{
		Pnt2f _TopLeft,
			  _BottomRight;

		UInt32 _CursorType;
		CursorRegion(Pnt2f TopLeft, Pnt2f BottomRight, UInt32 Type);
	};
	typedef std::list<CursorRegion> CursorRegionList;
	typedef CursorRegionList::iterator CursorRegionListItor;

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
    
    EventConnection addMouseListener(MouseListenerPtr Listener);
    EventConnection addMouseMotionListener(MouseMotionListenerPtr Listener);
    EventConnection addMouseWheelListener(MouseWheelListenerPtr Listener);
    EventConnection addKeyListener(KeyListenerPtr Listener);
    EventConnection addWindowListener(WindowListenerPtr Listener);
    EventConnection addUpdateListener(UpdateListenerPtr Listener);
    
    bool isMouseListenerAttached(MouseListenerPtr Listener) const;
    bool isMouseMotionListenerAttached(MouseMotionListenerPtr Listener) const;
    bool isMouseWheelListenerAttached(MouseWheelListenerPtr Listener) const;
    bool isKeyListenerAttached(KeyListenerPtr Listener) const;
    bool isWindowListenerAttached(WindowListenerPtr Listener) const;
    bool isUpdateListenerAttached(UpdateListenerPtr Listener) const;

    void removeMouseListener(MouseListenerPtr Listener);
    void removeMouseMotionListener(MouseMotionListenerPtr Listener);
    void removeMouseWheelListener(MouseWheelListenerPtr Listener);
    void removeKeyListener(KeyListenerPtr Listener);
    void removeWindowListener(WindowListenerPtr Listener);
    void removeUpdateListener(UpdateListenerPtr Listener);

    void detatchAllListeners(void);

    //Set the Window Position
    virtual void setPosition(Pnt2f Pos) = 0;
    //Set the Window Position
    virtual Pnt2f getPosition(void) const = 0;

    //Set the Window size
    virtual void setSize(Vec2us Size) = 0;

    //Get the Window size
    virtual Vec2f getSize(void) const = 0;

    //Focused
    //Set the Window Focus
    virtual void setFocused(bool Focused) = 0;

    //Get the Window Focus
    virtual bool getFocused(void) const = 0;

    //Visible / Iconify / Normal
    //Set the Window Visible
    virtual void setVisible(bool Visible) = 0;

    //Get the Window Visible
    virtual bool getVisible(void) const = 0;

    //Set the Window Iconify
    virtual void setIconify(bool Iconify) = 0;

    //Get the Window Iconify
    virtual bool getIconify(void) const = 0;

    //Fullscreen
    virtual void setFullscreen(bool Fullscreen) = 0;

    //Get the Window Fullscreen
    virtual bool getFullscreen(void) const = 0;

    //Set the text on the Title bar of the window
    virtual void setTitle(const std::string& TitleText) = 0;

    //Get the text of the Title bar of the window
    virtual std::string getTitle(void) = 0;

    //Set the window to allow or not allow Resizing
    virtual void setRisizable(bool IsResizable) = 0;

    //Get whether or not the window allows resizing
    virtual bool getRisizable(void) = 0;

    //Set the window to draw or not draw it's border
    virtual void setDrawBorder(bool DrawBorder) = 0;

    //Get wether or not the window is drawing a border
    virtual bool getDrawBorder(void) = 0;

    virtual void setShowCursor(bool showCursor) = 0;

    virtual bool getShowCursor(void) const = 0;

    //Set Display Callback Function
    virtual void setDisplayCallback(DisplayCallbackFunc Callback);

    //Set Reshape Callback Function
    virtual void setReshapeCallback(ReshapeCallbackFunc Callback);

    virtual Vec2f getDesktopSize(void) const = 0;

	virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect) = 0;

    virtual Path saveFileDialog(const std::string& DialogTitle,
                    const std::vector<FileDialogFilter>& Filters,
                    const Path& InitialFile,
                    const Path& InitialDirectory,
                    bool PromptForOverwrite
                    ) = 0;


    virtual void draw(void) = 0;
    virtual void update(void) = 0;

    virtual bool attachWindow(void) = 0;

	virtual UInt32 getKeyModifiers(void) const = 0;
	virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const = 0;
    
	virtual Pnt2f getMousePosition(void) const = 0;

	ViewportPtr windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint);

	virtual std::string getClipboard(void) const = 0;

	virtual void putClipboard(const std::string Value) = 0;

    virtual WindowPtr initWindow(void);

    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName) = 0;
    
    virtual void closeWindow(void) = 0;

	UInt32 getCursorType(void) const;
	void setCursorType(UInt32 Type); 

	RenderAction * getRenderAction(void);
	void setRenderAction(RenderAction *action);

	CursorRegionListItor addCursorRegion(const CursorRegion& r);
	bool removeCursorRegion(CursorRegionListItor RegionItor);
    /*=========================  PROTECTED  ===============================*/
  protected:
	  CursorRegionList _CursorRegions;
	  void updateCursor(Pnt2f MousePos);

    // Variables should all be in WindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    WindowEventProducer(void);
    WindowEventProducer(const WindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~WindowEventProducer(void); 

    void internalDraw(void);
    void internalReshape(Vec2f size);

    /*! \}                                                                 */
    
    void updateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location);
    void validateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location);

    void produceMouseClicked(const MouseEvent::MouseButton& Button, const Pnt2f& Location);
    void produceMouseEntered(const Pnt2f& Location);
    void produceMouseExited(const Pnt2f& Location);
    void produceMousePressed(const MouseEvent::MouseButton& Button, const Pnt2f& Location);
    void produceMouseReleased(const MouseEvent::MouseButton& Button, const Pnt2f& Location);

    void produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2f& Location, const MouseWheelEvent::ScrollType& TheScrollType = MouseWheelEvent::UNIT_SCROLL);

    void produceMouseMoved(const Pnt2f& Location);
    void produceMouseDragged(const MouseEvent::MouseButton& Button, const Pnt2f& Location);

    void produceKeyPressed(const KeyEvent::Key& TheKey, const UInt32& Modifiers);
    void produceKeyReleased(const KeyEvent::Key& TheKey, const UInt32& Modifiers);
    void produceKeyTyped(const KeyEvent::Key& TheKey, const UInt32& Modifiers);
	
    void produceUpdate(const Time& ElapsedTime);
	
    void produceWindowOpened(void);
    void produceWindowClosing(void);
    void produceWindowClosed(void);
    void produceWindowIconified(void);
    void produceWindowDeiconified(void);
    void produceWindowActivated(void);
    void produceWindowDeactivated(void);
    void produceWindowEntered(void);
    void produceWindowExited(void);

	UInt32 _CursorType;

	virtual void setCursor(void) = 0;
    virtual WindowPtr createWindow(void) = 0;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class WindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const WindowEventProducer &source);
};

typedef WindowEventProducer *WindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGWindowEventProducerBase.inl"
#include "OSGWindowEventProducer.inl"

#define OSGWINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGWINDOWEVENTPRODUCER_H_ */


