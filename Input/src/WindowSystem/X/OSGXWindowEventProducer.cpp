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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>
#include <X11/cursorfont.h>

#include "OSGXWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XWindowEventProducer
XWindowEventProducer Class. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void XWindowEventProducer::initMethod (void)
{
}

int XWindowEventProducer::wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

void XWindowEventProducer::WindowEventLoopThread(void* args)
{
    WindowEventLoopThreadArguments* Arguments(static_cast<WindowEventLoopThreadArguments*>(args));
    DisplayP      dpy;
    X11Window     hwin;

    XVisualInfo   *vi;
    Colormap      cmap;
    XSetWindowAttributes swa;

    int dummy;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) 
    {
        std::cerr << "Error: Could not open display!" << std::endl;
    }

    if( ! glXQueryExtension( dpy, &dummy, &dummy ) )
    {
        std::cerr << "Error: X server has no OpenGL GLX extension" << std::endl;
    }

    //int VisualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 32, GLX_DOUBLEBUFFER, None};
    int VisualAttributes[] = {GLX_RGBA, 
                              GLX_DEPTH_SIZE, 16,
                              GLX_DOUBLEBUFFER,
                              GLX_STENCIL_SIZE, 8,
                              None};
    
    vi = glXChooseVisual( dpy, DefaultScreen(dpy), VisualAttributes );
    if ( vi == NULL ) 
    {
        FFATAL(("Could not set Visual Attributes"));
    }
    if (vi->c_class != TrueColor)
    {
        FFATAL(("TrueColor visual required for this program"));
    }

    cmap = XCreateColormap( dpy, 
                            RootWindow(dpy, vi->screen), 
                            vi->visual, 
                            AllocNone );
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = ExposureMask | 
                     ButtonPressMask | 
                     ButtonReleaseMask |
                     KeyPressMask |
                     KeyReleaseMask |
                     PointerMotionMask |
                     StructureNotifyMask |
                     EnterWindowMask |
                     LeaveWindowMask |
                     FocusChangeMask |
                     SubstructureNotifyMask;

    // Create Window

    // Create a Window and connect it to the main display dpy
    hwin = XCreateWindow( dpy, 
                          RootWindow(dpy, vi->screen), 
                          Arguments->_ScreenPosition.x(), 
                          Arguments->_ScreenPosition.y(), 
                          Arguments->_Size.x(), 
                          Arguments->_Size.y(),
                          0, 
                          vi->depth,
                          InputOutput, 
                          vi->visual, 
                          CWBorderPixel | CWColormap | CWEventMask, 
                          &swa );
                          
    XFree(vi);

    int argc(1);
    char **argv = new char*[1];
    (*argv)= "Bla";
     XSetStandardProperties(dpy, hwin, Arguments->_WindowName.c_str(), Arguments->_WindowName.c_str(), None, argv, argc, NULL);

    beginEditCP(XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow()), XWindow::DisplayFieldMask | XWindow::WindowFieldMask);
        XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->setDisplay ( dpy );
        XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->setWindow ( hwin );
    endEditCP(XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow()), XWindow::DisplayFieldMask | XWindow::WindowFieldMask);
    

    Arguments->_EventProducer->attachWindow();
    

    Arguments->_EventProducer->getWindow()->init();
    
    XMapWindow(XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->getDisplay(),
            XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->getWindow());
    XEvent event;
    XIfEvent(XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->getDisplay(), &event, wait_for_map_notify, (char *)(XWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->getWindow()));
    Arguments->_EventProducer->produceWindowOpened();
    
    Arguments->_EventProducer->getWindow()->activate();
    
    Arguments->_EventProducer->setPosition(Arguments->_ScreenPosition);
    
    bool stopIt = false;
    XWindowEventProducerPtr EventProducer(Arguments->_EventProducer);
    
    //Set things up to capture the delete window event
    Atom wm_delete_window=XInternAtom(XWindow::Ptr::dcast(EventProducer->getWindow())->getDisplay(), "WM_DELETE_WINDOW", False);
    XSetWMProtocols(XWindow::Ptr::dcast(EventProducer->getWindow())->getDisplay(), XWindow::Ptr::dcast(EventProducer->getWindow())->getWindow(), &wm_delete_window, 1);
    Atom wm_protocols=XInternAtom(XWindow::Ptr::dcast(EventProducer->getWindow())->getDisplay(), "WM_PROTOCOLS", False); 
  
    while ( event.type != DestroyNotify ) 
    {
        while ( XPending(XWindow::Ptr::dcast(EventProducer->getWindow())->getDisplay()) )
        {
            XNextEvent(XWindow::Ptr::dcast(EventProducer->getWindow())->getDisplay(), &event);
            EventProducer->handleEvent(event);
        }  
        
        if(EventProducer->_IsDrawPending)
        {
            EventProducer->_DisplayCallbackFunc();
            EventProducer->_IsDrawPending = false;
        }
        else
        {
            //Block untill next event or draw event
            //yeild controll
        }
    }
    
    EventProducer->produceWindowClosed();
    
    //Delete my arguments, to avoid memory leak
    delete Arguments;
}

UInt32 XWindowEventProducer::determineKeyModifiers(const unsigned int state)
{
   UInt32 Modifiers = 0;

   if(state & ShiftMask)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_SHIFT;
   }
   if(state & ControlMask)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CONTROL;
   }
   if(state & Mod1Mask)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_ALT;
   }
   if(state & LockMask)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CAPS_LOCK;
   }
   if(state & Mod2Mask)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_NUM_LOCK;
   }
   //if(state & )
   //{
   //   Modifiers |= KeyEvent::KEY_MODIFIER_SCROLL_LOCK;
   //}
   return Modifiers;
}

KeyEvent::Key XWindowEventProducer::determineKey(const KeySym& XKeySym)
{
    switch(XKeySym)
    {
        //Alphabet
        case XK_a:
            return KeyEvent::KEY_A;
        case XK_b:
            return KeyEvent::KEY_B;
        case XK_c:
            return KeyEvent::KEY_C;
        case XK_d:
            return KeyEvent::KEY_D;
        case XK_e:
            return KeyEvent::KEY_E;
        case XK_f:
            return KeyEvent::KEY_F;
        case XK_g:
            return KeyEvent::KEY_G;
        case XK_h:
            return KeyEvent::KEY_H;
        case XK_i:
            return KeyEvent::KEY_I;
        case XK_j:
            return KeyEvent::KEY_J;
        case XK_k:
            return KeyEvent::KEY_K;
        case XK_l:
            return KeyEvent::KEY_L;
        case XK_m:
            return KeyEvent::KEY_M;
        case XK_n:
            return KeyEvent::KEY_N;
        case XK_o:
            return KeyEvent::KEY_O;
        case XK_p:
            return KeyEvent::KEY_P;
        case XK_q:
            return KeyEvent::KEY_Q;
        case XK_r:
            return KeyEvent::KEY_R;
        case XK_s:
            return KeyEvent::KEY_S;
        case XK_t:
            return KeyEvent::KEY_T;
        case XK_u:
            return KeyEvent::KEY_U;
        case XK_v:
            return KeyEvent::KEY_V;
        case XK_w:
            return KeyEvent::KEY_W;
        case XK_x:
            return KeyEvent::KEY_X;
        case XK_y:
            return KeyEvent::KEY_Y;
        case XK_z:
            return KeyEvent::KEY_Z;
        //Numbers
        case XK_0:
            return KeyEvent::KEY_0;
        case XK_1:
            return KeyEvent::KEY_1;
        case XK_2:
            return KeyEvent::KEY_2;
        case XK_3:
            return KeyEvent::KEY_3;
        case XK_4:
            return KeyEvent::KEY_4;
        case XK_5:
            return KeyEvent::KEY_5;
        case XK_6:
            return KeyEvent::KEY_6;
        case XK_7:
            return KeyEvent::KEY_7;
        case XK_8:
            return KeyEvent::KEY_8;
        case XK_9:
            return KeyEvent::KEY_9;

        //Other
        case XK_minus:
            return KeyEvent::KEY_MINUS;
        case XK_equal:
            return KeyEvent::KEY_EQUALS;
        case XK_grave:
            return KeyEvent::KEY_BACK_QUOTE;
        case XK_Tab:
            return KeyEvent::KEY_TAB;
        case XK_space:
            return KeyEvent::KEY_SPACE;
        case XK_bracketleft:
            return KeyEvent::KEY_OPEN_BRACKET;
        case XK_bracketright:
            return KeyEvent::KEY_CLOSE_BRACKET;
        case XK_semicolon:
            return KeyEvent::KEY_SEMICOLON;
        case XK_comma:
            return KeyEvent::KEY_COMMA;
        case XK_period:
            return KeyEvent::KEY_PERIOD;
        case XK_backslash:
            return KeyEvent::KEY_BACK_SLASH;
        case XK_apostrophe:
            return KeyEvent::KEY_APOSTROPHE;
        case XK_slash:
            return KeyEvent::KEY_SLASH;

        //Non-visible
        case XK_Escape:
            return KeyEvent::KEY_ESCAPE;
        case XK_Shift_L:
        case XK_Shift_R:
            return KeyEvent::KEY_SHIFT;
        case XK_Control_L:
        case XK_Control_R:
            return KeyEvent::KEY_CONTROL;
        case XK_Super_L:
        case XK_Super_R:
            return KeyEvent::KEY_META;
        case XK_Alt_L:
        case XK_Alt_R:
            return KeyEvent::KEY_ALT;
        case XK_Return:
            return KeyEvent::KEY_ENTER;
        case XK_Cancel:
            return KeyEvent::KEY_CANCEL;
        case XK_Clear:
            return KeyEvent::KEY_CLEAR;
        case XK_Pause:
            return KeyEvent::KEY_PAUSE;
        case XK_Caps_Lock:
            return KeyEvent::KEY_CAPS_LOCK;
        case XK_End:
            return KeyEvent::KEY_END;
        case XK_Menu:
            return KeyEvent::KEY_MENU;
        case XK_Home:
            return KeyEvent::KEY_HOME;
        case XK_Up:
            return KeyEvent::KEY_UP;
        case XK_Down:
            return KeyEvent::KEY_DOWN;
        case XK_Left:
            return KeyEvent::KEY_LEFT;
        case XK_Right:
            return KeyEvent::KEY_RIGHT;
        case XK_Print:
            return KeyEvent::KEY_PRINTSCREEN;
        case XK_Insert:
            return KeyEvent::KEY_INSERT;
        case XK_Delete:
            return KeyEvent::KEY_DELETE;
        case XK_Help:
            return KeyEvent::KEY_HELP;
        case XK_Num_Lock:
            return KeyEvent::KEY_NUM_LOCK;
        case XK_Scroll_Lock:
            return KeyEvent::KEY_SCROLL_LOCK;
        case XK_BackSpace:
            return KeyEvent::KEY_BACK_SPACE;
        case XK_Page_Up:
            return KeyEvent::KEY_PAGE_UP;
        case XK_Page_Down:
            return KeyEvent::KEY_PAGE_DOWN;

        //Function Keys
        case XK_F1:
            return KeyEvent::KEY_F1;
        case XK_F2:
            return KeyEvent::KEY_F2;
        case XK_F3:
            return KeyEvent::KEY_F3;
        case XK_F4:
            return KeyEvent::KEY_F4;
        case XK_F5:
            return KeyEvent::KEY_F5;
        case XK_F6:
            return KeyEvent::KEY_F6;
        case XK_F7:
            return KeyEvent::KEY_F7;
        case XK_F8:
            return KeyEvent::KEY_F8;
        case XK_F9:
            return KeyEvent::KEY_F9;
        case XK_F10:
            return KeyEvent::KEY_F10;
        case XK_F11:
            return KeyEvent::KEY_F11;
        case XK_F12:
            return KeyEvent::KEY_F12;
        case XK_F13:
            return KeyEvent::KEY_F13;
        case XK_F14:
            return KeyEvent::KEY_F14;
        case XK_F15:
            return KeyEvent::KEY_F15;
        case XK_F16:
            return KeyEvent::KEY_F16;
        case XK_F17:
            return KeyEvent::KEY_F17;
        case XK_F18:
            return KeyEvent::KEY_F18;
        case XK_F19:
            return KeyEvent::KEY_F19;
        case XK_F20:
            return KeyEvent::KEY_F20;
        case XK_F21:
            return KeyEvent::KEY_F21;
        case XK_F22:
            return KeyEvent::KEY_F22;
        case XK_F23:
            return KeyEvent::KEY_F23;
        case XK_F24:
            return KeyEvent::KEY_F24;

        //Numpad 
        case XK_KP_Enter:
            return KeyEvent::KEY_ENTER;
        case XK_KP_Add:
            return KeyEvent::KEY_ADD;
        case XK_KP_Subtract:
            return KeyEvent::KEY_MINUS;
        case XK_KP_Multiply:
            return KeyEvent::KEY_MULTIPLY;
        case XK_KP_Divide:
            return KeyEvent::KEY_DIVIDE;
        case XK_KP_Delete:
            return KeyEvent::KEY_DECIMAL;
        case XK_KP_Insert:
            return KeyEvent::KEY_NUMPAD_0;
        case XK_KP_End:
            return KeyEvent::KEY_NUMPAD_1;
        case XK_KP_Down:
            return KeyEvent::KEY_NUMPAD_2;
        case XK_KP_Next:
            return KeyEvent::KEY_NUMPAD_3;
        case XK_KP_Left:
            return KeyEvent::KEY_NUMPAD_4;
        case XK_KP_Begin:
            return KeyEvent::KEY_NUMPAD_5;
        case XK_KP_Right:
            return KeyEvent::KEY_NUMPAD_6;
        case XK_KP_Home:
            return KeyEvent::KEY_NUMPAD_7;
        case XK_KP_Up:
            return KeyEvent::KEY_NUMPAD_8;
        case XK_KP_Prior:
            return KeyEvent::KEY_NUMPAD_9;

        default:
            std::cout << XKeySym << std::endl;
            return KeyEvent::KEY_UNKNOWN;
    }
    return KeyEvent::KEY_UNKNOWN;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void XWindowEventProducer::setPosition(Pnt2s Pos)
{
    XMoveWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),Pos.x(), Pos.y());
}

Pnt2s XWindowEventProducer::getPosition(void) const
{
    ::Window *RootWindow;
    int x,y;
    unsigned int Width,Height,Depth,BorderWidth;
    
    XGetGeometry(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),RootWindow,
            &x,&y,
            &Width,&Height,
            &BorderWidth,
            &Depth);
    
   return Pnt2s(x,y);
}

void XWindowEventProducer::setSize(Vec2us Size)
{
    XResizeWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),Size.x(), Size.y());
}

Vec2s XWindowEventProducer::getSize(void) const
{
    ::Window *RootWindow;
    int x,y;
    unsigned int Width,Height,Depth,BorderWidth;
    
    XGetGeometry(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),RootWindow,
            &x,&y,
            &Width,&Height,
            &BorderWidth,
            &Depth);
    
   return Vec2s(Width,Height);
}

void XWindowEventProducer::setFocused(bool Focused)
{
   if(Focused)
   {
       XSetInputFocus(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),RevertToParent, getSystemTime());
   }
   else
   {
       XSetInputFocus(XWindow::Ptr::dcast(getWindow())->getDisplay(),None,RevertToParent, getSystemTime());
   }
}

bool XWindowEventProducer::getFocused(void) const
{
    ::Window *FocusWindow;
    int revert_to;
    XGetInputFocus(XWindow::Ptr::dcast(getWindow())->getDisplay(), FocusWindow, &revert_to);
    
   return FocusWindow == &XWindow::Ptr::dcast(getWindow())->getWindow();
}

void XWindowEventProducer::setVisible(bool Visible)
{
   //TODO:Implement
}

bool XWindowEventProducer::getVisible(void) const
{
   //TODO:Implement
   return false;
}

void XWindowEventProducer::setIconify(bool Iconify)
{
    if(Iconify)
    {
        XIconifyWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),0);
    }
    else
    {
        XMapWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(), XWindow::Ptr::dcast(getWindow())->getWindow());
    }
}

bool XWindowEventProducer::getIconify(void) const
{
   //TODO:Implement
   return false;
}

void XWindowEventProducer::setFullscreen(bool Fullscreen)
{
   //TODO:Implement
}

bool XWindowEventProducer::getFullscreen(void) const
{
   //TODO:Implement
   return false;
}

UInt32 XWindowEventProducer::getKeyModifiers(void) const
{
    
    return determineKeyModifiers(_LastKeyboardMouseButtonMask);
}

Pnt2s XWindowEventProducer::getMousePosition(void) const
{   
    return _LastMousePosition;
}

std::string XWindowEventProducer::getClipboard(void) const
{
   //TODO:Implement
   return std::string("");
}

void XWindowEventProducer::putClipboard(const std::string Value)
{
   //TODO:Implement
}

void XWindowEventProducer::closeWindow(void)
{
    XDestroyWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow());
}

void XWindowEventProducer::draw(void)
{
    _IsDrawPending = true;
}


void XWindowEventProducer::setTitle(const std::string& TitleText)
{
   //TODO:Implement
}


std::string XWindowEventProducer::getTitle(void)
{
   //TODO:Implement
    return std::string("");
}

void XWindowEventProducer::setRisizable(bool IsResizable)
{
   //TODO:Implement
}

bool XWindowEventProducer::getRisizable(void)
{
   //TODO:Implement
    return true;
}

void XWindowEventProducer::setDrawBorder(bool DrawBorder)
{
   //TODO:Implement
}

bool XWindowEventProducer::getDrawBorder(void)
{
   //TODO:Implement
    return true;
}

void XWindowEventProducer::update(void)
{
   //Updating
   Time Now(getSystemTime());
   Time ElapsedTime(Now - getLastUpdateTime());
   if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
   {
	   produceUpdate(ElapsedTime);
   }
   beginEditCP(XWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
	   setLastUpdateTime(Now);
   endEditCP(XWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
}

WindowPtr XWindowEventProducer::createWindow(void)
{
    return XWindow::create();
}

void XWindowEventProducer::openWindow(const Pnt2s& ScreenPosition,
                    const Vec2s& Size,
                    const std::string& WindowName)
{
    if(_WindowEventLoopThread == NULL)
    {
        std::string ThreadName = WindowName + " Event Loop";
        _WindowEventLoopThread = dynamic_cast<Thread *>(ThreadManager::the()->getThread(ThreadName.c_str()));
    }
    else
    {
    }
    WindowEventLoopThreadArguments* Arguments = new WindowEventLoopThreadArguments(  
                    ScreenPosition,
                    Size,
                    WindowName,
                    XWindow::Ptr::dcast(getWindow()),
                    XWindowEventProducerPtr(this)  );
    
    //ChangeList::setReadWriteDefault();
    _WindowEventLoopThread->runFunction(WindowEventLoopThread, 0, static_cast<void*>(Arguments));
}

bool XWindowEventProducer::attachWindow(void)
{   
    return true;
}

void XWindowEventProducer::handleEvent(XEvent& Event)
{
    switch (Event.type) 
    {
        case KeyPress:
            //produceKeyPressed(determineKey(wParam),getKeyModifiers());
            _LastKeyboardMouseButtonMask = Event.xkey.state;
            produceKeyPressed(determineKey(XLookupKeysym(&(Event.xkey), 0)),determineKeyModifiers(Event.xkey.state));
            break;
        case KeyRelease:
            //produceKeyReleased(determineKey(wParam),getKeyModifiers());
            _LastKeyboardMouseButtonMask = Event.xkey.state;
            produceKeyReleased(determineKey(XLookupKeysym(&(Event.xkey),0)),determineKeyModifiers(Event.xkey.state));
            break;
        case MotionNotify:
            {
                _LastKeyboardMouseButtonMask = Event.xmotion.state;
                _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
                if(Event.xmotion.state & Button1MotionMask)
                {
                    produceMouseDragged(MouseEvent::BUTTON1,Pnt2s(Event.xmotion.x, Event.xmotion.y));
                }
                if(Event.xmotion.state & Button2MotionMask)
                {
                    produceMouseDragged(MouseEvent::BUTTON2,Pnt2s(Event.xmotion.x, Event.xmotion.y));
                }
                if(Event.xmotion.state & Button3MotionMask)
                {
                    produceMouseDragged(MouseEvent::BUTTON3,Pnt2s(Event.xmotion.x, Event.xmotion.y));
                }
                if(Event.xmotion.state & Button4MotionMask)
                {
                    produceMouseDragged(MouseEvent::BUTTON4,Pnt2s(Event.xmotion.x, Event.xmotion.y));
                }
                if(Event.xmotion.state & Button5MotionMask)
                {
                    produceMouseDragged(MouseEvent::BUTTON5,Pnt2s(Event.xmotion.x, Event.xmotion.y));
                }
                
                produceMouseMoved(Pnt2s(Event.xmotion.x, Event.xmotion.y));
                break;
            }
         case ButtonPress:
            {
                _LastKeyboardMouseButtonMask = Event.xbutton.state;
               _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
               MouseEvent::MouseButton OSGButton(MouseEvent::NO_BUTTON);
               switch(Event.xbutton.button)
               {
               case  1:
                  OSGButton = MouseEvent::BUTTON1;
                  break;
               case  2:
                  OSGButton = MouseEvent::BUTTON2;
                  break;
               case  3:
                  OSGButton = MouseEvent::BUTTON3;
                  break;
               case   4:
				  produceMouseWheelMoved(1, Pnt2s(Event.xbutton.x, Event.xbutton.y));
                  break;
               case   5:
				  produceMouseWheelMoved(-1, Pnt2s(Event.xbutton.x, Event.xbutton.y));
                  break;
               case   6:
                  OSGButton = MouseEvent::BUTTON6;
                  break;
               case   7:
                  OSGButton = MouseEvent::BUTTON7;
                  break;
               case   8:
                  OSGButton = MouseEvent::BUTTON8;
                  break;
               case   9:
                  OSGButton = MouseEvent::BUTTON9;
                  break;
               case   10:
                  OSGButton = MouseEvent::BUTTON10;
                  break;
               default:
                  OSGButton = MouseEvent::NO_BUTTON;
                  break;
               }
               if(OSGButton != MouseEvent::NO_BUTTON)
               {
                   produceMousePressed(OSGButton, Pnt2s(Event.xbutton.x, Event.xbutton.y));
               }
               break;
            }

         case ButtonRelease:
            {
               _LastKeyboardMouseButtonMask = Event.xbutton.state;
               _LastMousePosition.setValues(Event.xbutton.x, Event.xbutton.y);
               MouseEvent::MouseButton OSGButton(MouseEvent::NO_BUTTON);
              switch(Event.xbutton.button)
              {
              case  1:
                 OSGButton = MouseEvent::BUTTON1;
                 break;
              case  2:
                 OSGButton = MouseEvent::BUTTON2;
                 break;
               case  3:
                  OSGButton = MouseEvent::BUTTON3;
                  break;
               case   6:
                  OSGButton = MouseEvent::BUTTON6;
                  break;
               case   7:
                  OSGButton = MouseEvent::BUTTON7;
                  break;
               case   8:
                  OSGButton = MouseEvent::BUTTON8;
                  break;
               case   9:
                  OSGButton = MouseEvent::BUTTON9;
                  break;
               case   10:
                  OSGButton = MouseEvent::BUTTON10;
                  break;
              default:
                 break;
              }
               if(OSGButton != MouseEvent::NO_BUTTON)
               {
                   produceMouseReleased(OSGButton, Pnt2s(Event.xbutton.x, Event.xbutton.y));
               }
              break;
            }
         case ConfigureNotify:
            if ( ! getWindow()->isResizePending() )
            {
               getWindow()->resize( Event.xconfigure.width,
                            Event.xconfigure.height );
               _ReshapeCallbackFunc(Vec2s(Event.xconfigure.width, Event.xconfigure.height));
               _DisplayCallbackFunc();
            }
            break;
            
         case DestroyNotify:
            produceWindowClosing();
            break;
         case EnterNotify:
            produceWindowEntered();
            break;
         case LeaveNotify:
            produceWindowExited();
            break;
         case UnmapNotify:
            produceWindowIconified();
            break;
         case MapNotify:
            produceWindowDeiconified();
            break;
         case FocusIn:
            produceWindowActivated();
            break;
         case FocusOut:
            produceWindowDeactivated();
            break;
         case Expose:
            _DisplayCallbackFunc();
            break;
        case ClientMessage:
        {
            Atom wm_delete_window=XInternAtom(XWindow::Ptr::dcast(getWindow())->getDisplay(), "WM_DELETE_WINDOW", False);
            Atom wm_protocols=XInternAtom(XWindow::Ptr::dcast(getWindow())->getDisplay(), "WM_PROTOCOLS", False);
            if (Event.xclient.message_type == wm_protocols &&
                Event.xclient.data.l[0] == (long)wm_delete_window)
            {
                XDestroyWindow(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow());
            }
            break;
        }
        default:
            //std::cout << "Event Type: " << Event.type << std::endl;
            break;
      }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void XWindowEventProducer::setCursor(void)
{
	int cursor_shape;
	switch(getCursorType())
	{
	case CURSOR_POINTER:
		cursor_shape = XC_top_left_arrow;
		break;
	case CURSOR_HAND:
		cursor_shape = XC_hand1;
		break;
	case CURSOR_I_BEAM:
		cursor_shape = XC_xterm;
		break;
	case CURSOR_WAIT:
		cursor_shape = XC_watch;
		break;
	case CURSOR_RESIZE_W_TO_E:
		cursor_shape = XC_sb_h_double_arrow;
		break;
	case CURSOR_RESIZE_N_TO_S:
		cursor_shape = XC_sb_v_double_arrow;
		break;
	case CURSOR_RESIZE_NW_TO_SE:
		cursor_shape = XC_sizing;
		break;
	case CURSOR_RESIZE_SW_TO_NE:
		cursor_shape = XC_sizing;
		break;
	case CURSOR_RESIZE_ALL:
		cursor_shape = XC_fleur;
		break;
	case CURSOR_NONE:
		cursor_shape = XC_X_cursor;
		break;
	default:
		cursor_shape = XC_arrow;
		break;
	}
    XDefineCursor(XWindow::Ptr::dcast(getWindow())->getDisplay(),XWindow::Ptr::dcast(getWindow())->getWindow(),
            XCreateFontCursor(XWindow::Ptr::dcast(getWindow())->getDisplay(),cursor_shape));
}
/*----------------------- constructors & destructors ----------------------*/

XWindowEventProducer::XWindowEventProducer(void) :
    Inherited(),
        _LastKeyboardMouseButtonMask(0),
        _LastMousePosition(0,0),
        _IsDrawPending(false)
{
}

XWindowEventProducer::XWindowEventProducer(const XWindowEventProducer &source) :
    Inherited(source),
        _LastKeyboardMouseButtonMask(0),
        _LastMousePosition(0,0),
        _IsDrawPending(false)
{
}

XWindowEventProducer::~XWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

XWindowEventProducer::WindowEventLoopThreadArguments::WindowEventLoopThreadArguments(
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       XWindowPtr TheWindow,
                       XWindowEventProducerPtr TheEventProducer) :
        _ScreenPosition(ScreenPosition),
        _Size(Size),
        _WindowName(WindowName),
        _Window(TheWindow),
        _EventProducer(TheEventProducer)
{
}

void XWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void XWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump XWindowEventProducer NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGXWINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGXWINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGXWINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

