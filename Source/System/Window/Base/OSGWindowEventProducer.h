/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGWindowEventProducerBase.h"

#include <set>
#include <vector>
#include <map>
#include "OSGThread.h"
#include "OSGRenderAction.h"
#include "OSGPathType.h"
#include <boost/function.hpp>

#include "OSGWindowEventDetails.h"
#include "OSGKeyEventDetails.h"
#include "OSGMouseEventDetails.h"
#include "OSGMouseWheelEventDetails.h"
#include "OSGUpdateEventDetails.h"
#include "OSGStatTimeStampElem.h"

OSG_BEGIN_NAMESPACE

/*! \brief WindowEventProducer class. See \ref
           PageSystemWindowEventProducer for a description.
*/

class OSG_SYSTEM_DLLMAPPING WindowEventProducer : public WindowEventProducerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef WindowEventProducerBase Inherited;
    typedef WindowEventProducer     Self;

    /**
     * Enumeration values for cursor types.
     */
	enum CursorType {CURSOR_POINTER=0, 
                     CURSOR_HAND=1,
                     CURSOR_I_BEAM=2,
                     CURSOR_WAIT=3,
                     CURSOR_RESIZE_W_TO_E=4,
                     CURSOR_RESIZE_N_TO_S=5,
                     CURSOR_RESIZE_NW_TO_SE=6,
                     CURSOR_RESIZE_SW_TO_NE=7,
                     CURSOR_RESIZE_ALL=8,
                     CURSOR_NONE=9};


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

    struct CursorRegion
	{
		Pnt2f _TopLeft,
			  _BottomRight;

		UInt32 _CursorType;
		CursorRegion(Pnt2f TopLeft, Pnt2f BottomRight, UInt32 Type);
	};

	typedef std::list<CursorRegion> CursorRegionList;
	typedef CursorRegionList::iterator CursorRegionListItor;

    typedef boost::function<void (void)> DisplayCallbackFunc;
    typedef boost::function<void (Vec2f)> ReshapeCallbackFunc;

    static StatElemDesc<StatTimeStampElem    > statWindowLoopTime;

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

    virtual Window* initWindow(void);

    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName) = 0;

    virtual void closeWindow(void) = 0;
    
    virtual void mainLoop(void) = 0;

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
    
    virtual void setAttachMouseToCursor(bool attach) = 0;
    
    virtual bool getAttachMouseToCursor(void) const = 0;

    //Set Display Callback Function
    virtual void setDisplayCallback(DisplayCallbackFunc Callback);

    //Set Reshape Callback Function
    virtual void setReshapeCallback(ReshapeCallbackFunc Callback);

    virtual Vec2f getDesktopSize(void) const = 0;

	virtual std::vector<BoostPath> openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const BoostPath& InitialDir,
		bool AllowMultiSelect) = 0;

    virtual BoostPath saveFileDialog(const std::string& DialogTitle,
                    const std::vector<FileDialogFilter>& Filters,
                    const std::string& InitialFile,
                    const BoostPath& InitialDirectory,
                    bool PromptForOverwrite
                    ) = 0;


    virtual void draw(void) = 0;
    virtual void update(void) = 0;

    virtual bool attachWindow(void) = 0;

	virtual UInt32 getKeyModifiers(void) const = 0;
	virtual KeyEventDetails::KeyState getKeyState(KeyEventDetails::Key TheKey) const = 0;
    
	virtual Pnt2f getMousePosition(void) const = 0;

	ViewportUnrecPtr windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint);

	virtual std::string getClipboard(void) const = 0;

	virtual void putClipboard(const std::string Value) = 0;

	UInt32 getCursorType(void) const;
	void setCursorType(UInt32 Type); 

	RenderAction * getRenderAction(void);
	void setRenderAction(RenderAction *action);

	CursorRegionListItor addCursorRegion(const CursorRegion& r);
	bool removeCursorRegion(CursorRegionListItor RegionItor);

    void blockInputConnections(bool Block);
    bool isBlockInputConnections(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	CursorRegionList _CursorRegions;
	void updateCursor(Pnt2f MousePos);

    struct Click
    {
       Time _TimeStamp;
       Pnt2f _Location;

       Click(Time TimeStamp, Pnt2f Location);
    };

    typedef std::vector<Click> ClickVector;
    typedef ClickVector::iterator ClickVectorIter;
    typedef ClickVector::const_iterator ClickVectorConstIter;

    typedef std::map<MouseEventDetails::MouseButton, ClickVector> ButtonClickCountMap;
    typedef std::map<MouseEventDetails::MouseButton, Pnt2f> ButtonClickMap;

    ButtonClickCountMap _ButtonClickCountMap;
    ButtonClickMap _ButtonClickMap;

    Thread* _WindowEventLoopThread;

    DisplayCallbackFunc _DisplayCallbackFunc;
    ReshapeCallbackFunc _ReshapeCallbackFunc;
	RenderAction *      _RenderAction;

    void internalDraw(void);
    void internalReshape(Vec2f size);

    void updateClickCount(const MouseEventDetails::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location);
    void validateClickCount(const MouseEventDetails::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location);

    void produceMouseClicked(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location);
    void produceMouseEntered(const Pnt2f& Location);
    void produceMouseExited(const Pnt2f& Location);
    void produceMousePressed(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location);
    void produceMouseReleased(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location);

    void produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2f& Location, const MouseWheelEventDetails::ScrollType& TheScrollType = MouseWheelEventDetails::UNIT_SCROLL);

    void produceMouseMoved(const Pnt2f& Location, const Vec2f& Delta);
    void produceMouseDragged(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location, const Vec2f& Delta);

    void produceKeyPressed(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers);
    void produceKeyReleased(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers);
    void produceKeyTyped(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers);
	
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
    bool _BlockInput;

	virtual void setCursor(void) = 0;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class WindowEventProducerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const WindowEventProducer &source);
};

typedef WindowEventProducer *WindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGWindowEventProducerBase.inl"
#include "OSGWindowEventProducer.inl"

#endif /* _OSGWINDOWEVENTPRODUCER_H_ */
