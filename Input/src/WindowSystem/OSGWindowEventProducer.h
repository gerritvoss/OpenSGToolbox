/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGInputConfig.h"

#include <set>
#include <vector>
#include <map>

#include "OSGWindowEventProducerBase.h"


#include "Event/OSGMouseListener.h"
#include "Event/OSGMouseMotionListener.h"
#include "Event/OSGMouseWheelListener.h"
#include "Event/OSGWindowListener.h"
#include "Event/OSGKeyListener.h"

#include "OSGEventDispatchThread.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUT_CLASS_API WindowEventProducer : public WindowEventProducerBase
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

    struct Click
    {
       Time _TimeStamp;
       Pnt2s _Location;

       Click(Time TimeStamp, Pnt2s Location);
    };
    typedef std::vector<Click> ClickVector;
    typedef ClickVector::iterator ClickVectorIter;
    typedef ClickVector::const_iterator ClickVectorConstIter;

    typedef std::map<MouseEvent::MouseButton, ClickVector> ButtonClickMap;

    ButtonClickMap _ButtonClickMap;

    EventDispatchThread* _EventDispatchThread;

    typedef void (*DisplayCallbackFunc)(void);
    typedef void (*ReshapeCallbackFunc)(Vec2s);

    DisplayCallbackFunc _DisplayCallbackFunc;
    ReshapeCallbackFunc _ReshapeCallbackFunc;

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
    
    void addMouseListener(MouseListenerPtr Listener);
    void addMouseMotionListener(MouseMotionListenerPtr Listener);
    void addMouseWheelListener(MouseWheelListenerPtr Listener);
    void addKeyListener(KeyListenerPtr Listener);
    void addWindowListener(WindowListenerPtr Listener);

    void removeMouseListener(MouseListenerPtr Listener);
    void removeMouseMotionListener(MouseMotionListenerPtr Listener);
    void removeMouseWheelListener(MouseWheelListenerPtr Listener);
    void removeKeyListener(KeyListenerPtr Listener);
    void removeWindowListener(WindowListenerPtr Listener);

    //Set the Window Position
    virtual void setPosition(Pnt2s Pos) = 0;
    //Set the Window Position
    virtual Pnt2s getPosition(void) const = 0;

    //Set the Window size
    virtual void setSize(Vec2us Size) = 0;

    //Get the Window size
    virtual Vec2s getSize(void) const = 0;

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

    
    void initEventDispatchThread(void);
    
    void exitEventDispatchThread(void);

    //Set Display Callback Function
    virtual void setDisplayCallback(DisplayCallbackFunc Callback);

    //Set Reshape Callback Function
    virtual void setReshapeCallback(ReshapeCallbackFunc Callback);

    
    virtual bool attachWindow(WindowPtr Win);
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
    
    void updateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2s& Location);

    void produceMouseClicked(const MouseEvent::MouseButton& Button, const Pnt2s& Location);
    void produceMouseEntered(const Pnt2s& Location);
    void produceMouseExited(const Pnt2s& Location);
    void produceMousePressed(const MouseEvent::MouseButton& Button, const Pnt2s& Location);
    void produceMouseReleased(const MouseEvent::MouseButton& Button, const Pnt2s& Location);

    void produceMouseWheelMoved(const Int32& WheelRotation, const MouseWheelEvent::ScrollType& TheScrollType);

    void produceMouseMoved(const Pnt2s& Location);
    void produceMouseDragged(const MouseEvent::MouseButton& Button, const Pnt2s& Location);

    void produceKeyPressed(const KeyEvent::Key& TheKey, const UInt32& Modifiers);
    void produceKeyReleased(const KeyEvent::Key& TheKey, const UInt32& Modifiers);
    void produceKeyTyped(const KeyEvent::Key& TheKey, const UInt32& Modifiers);

	
    void produceWindowOpened(void);
    void produceWindowClosing(void);
    void produceWindowClosed(void);
    void produceWindowIconified(void);
    void produceWindowDeiconified(void);
    void produceWindowActivated(void);
    void produceWindowDeactivated(void);
    void produceWindowEntered(void);
    void produceWindowExited(void);

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
