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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGCarbonWindowEventProducer.h"

#ifdef __APPLE__

//#include <Quicktime/Movies.h>
//#include <CarbonEvents.h>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CarbonWindowEventProducer
CarbonWindowEventProducer Class.  
*/

#define KeyBackspace 	51
#define KeyEnter 	76
#define KeyHome 	115
#define KeyEnd 	119
#define KeyPageDown 	121
#define KeyPageUp 	116
#define KeyReturn 	36 	
#define KeyDelete 	117
#define KeyTab 	48
#define KeySpacebar 	49
#define KeyShift 	56 	
#define KeyControl 	59 	
#define KeyMenu 	58
//#define KeyPrintScreen 	*
#define KeyEscape 	53
#define KeyCapsLock 	57
#define KeyHelp 	114
#define KeyF1 	122
#define KeyF2 	120
#define KeyF3 	99
#define KeyF4 	118
#define KeyF5 	96
#define KeyF6 	97
#define KeyF7 	98
#define KeyF8 	100
#define KeyF9 	101
#define KeyF10 	109
#define KeyF11 	103
#define KeyF12 	111
#define KeyMacFn 	63
#define KeyMacOption 	58
#define KeyMacCommand 	55
#define KeyWinApplication 	110
#define KeyQ 	12
#define KeyW 	13
#define KeyE 	14 	
#define KeyR 	15 	
#define KeyT 	17 	
#define KeyY 	16 	
#define KeyU 	32 	
#define KeyI 	34 	
#define KeyO 	31 	
#define KeyP 	35 	
#define KeyA 	0 	
#define KeyS 	1 	
#define KeyD 	2 	
#define KeyF 	3 	
#define KeyG 	5 	
#define KeyH 	4 	
#define KeyJ 	38 	
#define KeyK 	40 	
#define KeyL 	37 	
#define KeyZ 	6 	
#define KeyX 	7 	
#define KeyC 	8 	
#define KeyV 	9 	
#define KeyB 	11 	
#define KeyN 	45 	
#define KeyM 	46 	
#define Key0 	29
#define Key1 	18
#define Key2 	19
#define Key3 	20
#define Key4 	21
#define Key5 	23
#define Key6 	22
#define Key7 	26
#define Key8 	28
#define Key9 	25
#define KeyPeriod 	47
#define KeyComma 	43
#define KeySlash 	44
#define KeyNum0 	82
#define KeyNum1 	83
#define KeyNum2 	84
#define KeyNum3 	85
#define KeyNum4 	86
#define KeyNum5 	87
#define KeyNum6 	88
#define KeyNum7 	89
#define KeyNum8 	91
#define KeyNum9 	92
#define KeyMultiply 	67
#define KeyAdd 	69
#define KeySubtract 	78
#define KeyDivide 	75
#define KeyDecimal 	65
#define KeyNumEqual 	81

#define KeyBackquote 50
#define KeyMinus 27
#define KeyEquals 24
#define KeyLeftBracket 33
#define KeyRightBracket 30
#define KeyBackslash 42
#define KeySemicolon 41
#define KeyApostrophe 39
#define KeyClear 71
#define KeyUp 126
#define KeyDown 125
#define KeyLeft 123
#define KeyRight 124

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CarbonWindowEventProducer::CarbonWindowToProducerMap CarbonWindowEventProducer::_CarbonWindowToProducerMap;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindowEventProducer::initMethod (void)
{
	// A magic method that allows applications to react to events even
	// when they are not organized in a bundle
	ProcessSerialNumber psn = { 0, kCurrentProcess };
	TransformProcessType(&psn, kProcessTransformToForegroundApplication);
	SetFrontProcess(&psn);
}

OSStatus CarbonWindowEventProducer::eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    UInt32 WindowId(*static_cast<UInt32*>(userData));
        
   if(_CarbonWindowToProducerMap.find(WindowId) != _CarbonWindowToProducerMap.end())
   {
      return _CarbonWindowToProducerMap[WindowId]->internalEventHandler(nextHandler, event,
                           userData);
   }
   else
   {
        return eventNotHandledErr;
   }
}

UInt32 CarbonWindowEventProducer::getUndefinedWindowId(void)
{
    UInt32 i(1);
    while(_CarbonWindowToProducerMap.find(i) != _CarbonWindowToProducerMap.end())
    {
        ++i;
    }
    return i;
}

void CarbonWindowEventProducer::WindowEventLoopThread(void* args)
{
    
    WindowEventLoopThreadArguments* Arguments(static_cast<WindowEventLoopThreadArguments*>(args));
    
    // Carbon init

    // Create window
    WindowRef window;
    WindowAttributes windowAttrs =
        kWindowStandardDocumentAttributes |
        kWindowLiveResizeAttribute |
        kWindowStandardHandlerAttribute;
    Rect contentRect;
    SetRect(&contentRect, Arguments->_ScreenPosition.x(),  Arguments->_ScreenPosition.y(), Arguments->_Size.x() + Arguments->_ScreenPosition.x(), Arguments->_Size.y() + Arguments->_ScreenPosition.y());
    
    CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, &window);
    SetWindowTitleWithCFString(window, CFStringCreateWithCString(NULL, Arguments->_WindowName.c_str(), Arguments->_WindowName.size()));

    // Install event handler
    EventHandlerUPP eventHandlerUPP = NewEventHandlerUPP(eventHandler);
    EventTypeSpec eventList[] =
    {
		{ kEventClassKeyboard, kEventRawKeyDown},
        { kEventClassKeyboard, kEventRawKeyRepeat},
        { kEventClassKeyboard, kEventRawKeyUp},
        { kEventClassKeyboard, kEventRawKeyModifiersChanged},
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseMoved },
        { kEventClassMouse, kEventMouseDragged },
        { kEventClassMouse, kEventMouseWheelMoved },
        //{ kEventClassWindow, kEventWindowActivate },
        //{ kEventClassWindow, kEventWindowDeactivate },
        { kEventClassWindow, kEventWindowClose },
        { kEventClassWindow, kEventWindowDrawContent },
        { kEventClassWindow, kEventWindowBoundsChanged }
    };
    
	Arguments->_EventProducer->_WindowRef = window;
    Arguments->_EventProducer->_WindowId = getUndefinedWindowId();
    Arguments->_EventProducer->attachWindow();
    
    InstallWindowEventHandler(window, eventHandlerUPP, GetEventTypeCount(eventList), eventList, &(Arguments->_EventProducer->_WindowId), 0);

    // Initialize OpenGL
    GLint attribs[] = { AGL_RGBA, AGL_DOUBLEBUFFER, AGL_DEPTH_SIZE, 16, AGL_STENCIL_SIZE, 8, AGL_NONE };
    AGLPixelFormat pixelFormat = aglChoosePixelFormat(0, 0, attribs);
    if (pixelFormat == 0)
        std::cerr << "Cannot choose pixel format" << std::endl;
    AGLContext context = aglCreateContext(pixelFormat, 0);
    aglDestroyPixelFormat(pixelFormat);
    if (context == 0)
        std::cerr << "Cannot create context" << std::endl;
    aglSetDrawable(context, GetWindowPort(window));
    
    //Attach Window
    beginEditCP(CarbonWindow::Ptr::dcast(Arguments->_EventProducer->getWindow()), CarbonWindow::ContextFieldMask);
        CarbonWindow::Ptr::dcast(Arguments->_EventProducer->getWindow())->setContext(context);
    endEditCP(CarbonWindow::Ptr::dcast(Arguments->_EventProducer->getWindow()), CarbonWindow::ContextFieldMask);

        
    //Arguments->_EventProducer->getWindow()->resize( Arguments->_Size.x(), Arguments->_Size.y() );
	Arguments->_EventProducer->_MainThreadSyncBarrier->enter(2);
    Arguments->_EventProducer->setSize( Vec2f(Arguments->_Size.x(), Arguments->_Size.y()) );
    Arguments->_EventProducer->getWindow()->init();
    Arguments->_EventProducer->getWindow()->deactivate();
    
    // Show window
    RepositionWindow(window, 0, kWindowCascadeOnMainScreen);
    ShowWindow(window);
	
    
    // Main loop ( event dispatching )
    EventRef theEvent;    
    EventTargetRef theTarget;    
    theTarget = GetEventDispatcherTarget(); 
    while (true)
    {
        while  (ReceiveNextEvent(0, NULL,0,true,                             
                                 &theEvent)== noErr)        
        {
            SendEventToEventTarget (theEvent, theTarget);        
            ReleaseEvent(theEvent);
        }
        Arguments->_EventProducer->internalDraw();
    }
    
    aglDestroyContext(context);
    DisposeWindow(window);
    DisposeEventHandlerUPP(eventHandlerUPP);
    
    Arguments->_EventProducer->produceWindowClosed();
    
    //Delete my arguments, to avoid memory leak
    delete Arguments;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//TODO: IMPLEMENT
void CarbonWindowEventProducer::setShowCursor(bool)
{
	//TODO: implement
}
bool CarbonWindowEventProducer::getShowCursor() const
{
	//TODO: implement
}
osg::Vec2f CarbonWindowEventProducer::getDesktopSize() const
{
	//TODO: implement
	return Vec2f();
}
std::vector<osg::Path, std::allocator<osg::Path> > CarbonWindowEventProducer::openFileDialog(const std::string&, const std::vector<osg::WindowEventProducer::FileDialogFilter, std::allocator<osg::WindowEventProducer::FileDialogFilter> >&, const osg::Path&, bool)
{
	//TODO: implement
	return NullFC;
}
osg::Path CarbonWindowEventProducer::saveFileDialog(const std::string&, const std::vector<osg::WindowEventProducer::FileDialogFilter, std::allocator<osg::WindowEventProducer::FileDialogFilter> >&, const osg::Path&, const osg::Path&, bool)
{
	//TODO: implement
	return NullFC;
}
osg::KeyEvent::KeyState CarbonWindowEventProducer::getKeyState(osg::KeyEvent::Key) const
{
	//TODO: implement
	return NullFC;
}





WindowPtr CarbonWindowEventProducer::initWindow(void)
{
	WindowPtr MyWindow = Inherited::initWindow();
	std::string WindowName("Carbon");

    if(_WindowEventLoopThread == NULL)
    {
        std::string ThreadName = WindowName + " Event Loop";
        _WindowEventLoopThread = dynamic_cast<Thread *>(ThreadManager::the()->getThread(ThreadName.c_str()));
    }
    else
    {
    }
    
    WindowEventLoopThreadArguments* Arguments = new WindowEventLoopThreadArguments(  
                    Pnt2f(0.0,0.0),
                    Vec2f(600.0,600.0),
                    WindowName,
                    CarbonWindow::Ptr::dcast(getWindow()),
                    CarbonWindowEventProducerPtr(this)  );
    
    //ChangeList::setReadWriteDefault();
    std::string BarrierName = WindowName + " Event Loop";
	_MainThreadSyncBarrier =  Barrier::get(BarrierName.c_str());
    _WindowEventLoopThread->runFunction(WindowEventLoopThread, 0, static_cast<void*>(Arguments));
	
    return MyWindow;
}


OSStatus CarbonWindowEventProducer::internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    
    ::UInt32 eventClass = GetEventClass(event);
    switch (eventClass)
    {
    // Mouse events
    case kEventClassMouse:
		return handleMouseEvent(nextHandler, event, userData);

    // Key press events
    case kEventClassKeyboard:
		return handleKeyEvent(nextHandler, event, userData);

    // Window events
    case kEventClassWindow:
		return handleWindowEvent(nextHandler, event, userData);

    default:
        return eventNotHandledErr;
    }   
    return noErr;
}


OSStatus CarbonWindowEventProducer::handleMouseEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamWindowRef, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;


    // Get the location of the mouse pointer
    Point location;
    err = GetEventParameter(event, kEventParamMouseLocation, typeQDPoint, 0, sizeof(location), 0, &location);
    if (err != noErr)
        return err;

    // The location of the mouse pointer is in screen coordinates, so
    // we have to transform it into the local coordinate system of the
    // window content area.
    SetPortWindowPort(window);
    GlobalToLocal(&location);

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    MouseEvent::MouseButton TheMouseButton;
    switch(eventKind)
    {
        case kEventMouseDown:
        case kEventMouseUp:
        case kEventMouseDragged:
        {
            // Get the mouse button
            EventMouseButton mouseButton;
            err = GetEventParameter(event, kEventParamMouseButton, typeMouseButton, 0, sizeof(mouseButton), 0, &mouseButton);
            if (err != noErr)
                return err;
            
            switch (mouseButton)
            {
                case kEventMouseButtonPrimary: // left button
                    TheMouseButton = MouseEvent::BUTTON1;
                    break;
                case kEventMouseButtonSecondary: // right button
                    TheMouseButton = MouseEvent::BUTTON3;
                    break;
                case kEventMouseButtonTertiary: // middle button
                    TheMouseButton = MouseEvent::BUTTON2;
                    break;
                case 4:
                    TheMouseButton = MouseEvent::BUTTON4;
                    break;
                case 5:
                    TheMouseButton = MouseEvent::BUTTON5;
                    break;
                case 6:
                    TheMouseButton = MouseEvent::BUTTON6;
                    break;
                case 7:
                    TheMouseButton = MouseEvent::BUTTON7;
                    break;
                case 8:
                    TheMouseButton = MouseEvent::BUTTON8;
                    break;
                case 9:
                    TheMouseButton = MouseEvent::BUTTON9;
                    break;
                case 10:
                    TheMouseButton = MouseEvent::BUTTON10;
                    break;
                default:
                    TheMouseButton = MouseEvent::NO_BUTTON;
                    break;
            }
            break;
        }
    }
    switch (eventKind)
    {
    // mouse button pressed
    case kEventMouseDown:
		produceMousePressed(TheMouseButton, Pnt2f(location.h, location.v));
        break;

	
    // mouse button released
    case kEventMouseUp:
		produceMouseReleased(TheMouseButton, Pnt2f(location.h, location.v));
        break;

	//Mouse Moved
	case kEventMouseMoved:
		produceMouseMoved(Pnt2f(location.h, location.v));
        break;
		
    // mouse moved while a button is pressed
    case kEventMouseDragged:
		produceMouseDragged(TheMouseButton, Pnt2f(location.h, location.v));
        break;
		
	// mouse wheel moved
	case kEventMouseWheelMoved:
		{
			EventMouseWheelAxis axis;
            SInt32 delta;
			
			err = GetEventParameter( event, kEventParamMouseWheelAxis, 
                    typeMouseWheelAxis, NULL, sizeof(axis), NULL, &axis );
			if (err != noErr)
				return err;

            err = GetEventParameter( event, kEventParamMouseWheelDelta, 
                    typeLongInteger, NULL, sizeof(delta), NULL, &delta );
			if (err != noErr)
				return err;

            if ( axis == kEventMouseWheelAxisY )
            {
				produceMouseWheelMoved(delta, Pnt2f(location.h, location.v));
            }
		}
		break;
		
	default:
        std::cerr << "handleMouseEvent event not handled" << std::endl;
		break;
		
    }

    // We have to return eventNotHandledErr, otherwise the system is
    // not able to operate the menu and the window border
    return eventNotHandledErr;
}

OSStatus CarbonWindowEventProducer::handleWindowEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamDirectObject, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    // Quit the application when the user closes the window
    case kEventWindowClose:
        //QuitApplicationEventLoop();
        return noErr;

    // Draw the contents of the window
    case kEventWindowDrawContent:
        internalDraw();
        return noErr;

    case kEventWindowBoundsChanged:
        {
            // Update the GL context
            aglUpdateContext(CarbonWindow::Ptr::dcast(getWindow())->getContext());

            // Find out if we have a move or a resize situation
            ::UInt32 attributes;
            GetEventParameter(event, kEventParamAttributes, typeUInt32, 0, sizeof(attributes), 0, &attributes);

            if ((attributes & kWindowBoundsChangeSizeChanged) != 0)
            {
                // Get the new bounds of the window
                Rect bounds;
                GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, 0, sizeof(Rect), 0, &bounds);

                // Resize the OpenSG Window
                GLsizei width = bounds.right - bounds.left;
                GLsizei height = bounds.bottom - bounds.top;
				getWindow()->resize(width, height );
				internalReshape(Vec2f(width, height));
            }

            return noErr;
        }

    default:
        return eventNotHandledErr;
    }
}

OSStatus CarbonWindowEventProducer::handleKeyEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

	::UInt32 key;
	err = GetEventParameter(event, kEventParamKeyCode, typeUInt32, 0, sizeof(key), 0, &key);
	if (err != noErr)
		return err;
	
	
	::UInt32 keyModifiers;
	err = GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, 0, sizeof(keyModifiers), 0, &keyModifiers);
	if (err != noErr)
		return err;
		
    ::UInt32 eventKind = GetEventKind(event);
	switch(eventKind)
	{
		case kEventRawKeyDown:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));				
			break;
		case kEventRawKeyUp:
			produceKeyReleased(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyRepeat:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyModifiersChanged:
		    //std::cout << "kEventRawKeyModifiersChanged " << determineKeyModifiers(keyModifiers) << std::endl;
			if((determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_CONTROL) &&
			   !(_modifierKeyState & KeyEvent::KEY_MODIFIER_CONTROL))
			{
				//Control key pressed
				produceKeyPressed(KeyEvent::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_CONTROL) &&
			   (_modifierKeyState & KeyEvent::KEY_MODIFIER_CONTROL))
			{
				//Control key released
				produceKeyReleased(KeyEvent::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			_modifierKeyState = determineKeyModifiers(keyModifiers);
			break;
		default:
			break;
	}

    return noErr;
}

UInt32 CarbonWindowEventProducer::determineKeyModifiers(::UInt32 keyModifiers)
{
   UInt32 Modifiers = 0;

   if(keyModifiers & shiftKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_SHIFT;
   }
   if(keyModifiers & controlKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CONTROL;
   }
   if(keyModifiers & optionKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_ALT;
   }
   if(keyModifiers & alphaLock)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CAPS_LOCK;
   }
   //if(GetKeyState(VK_NUMLOCK)>0)
   //{
   //   Modifiers |= KeyEvent::KEY_MODIFIER_NUM_LOCK;
   //}
   //if(GetKeyState(VK_SCROLL)>0)
   //{
   //   Modifiers |= KeyEvent::KEY_MODIFIER_SCROLL_LOCK;
   //}
   return Modifiers;
}

KeyEvent::Key CarbonWindowEventProducer::determineKey(::UInt32 key)
{
    KeyEvent::Key OSGKey;
	switch(key)
	{
	//Alphabet
	case KeyA:
	  OSGKey = KeyEvent::KEY_A;
	  break;
	case KeyB:
	  OSGKey = KeyEvent::KEY_B;
	  break;
	case KeyC:
	  OSGKey = KeyEvent::KEY_C;
	  break;
	case KeyD:
	  OSGKey = KeyEvent::KEY_D;
	  break;
	case KeyE:
	  OSGKey = KeyEvent::KEY_E;
	  break;
	case KeyF:
	  OSGKey = KeyEvent::KEY_F;
	  break;
	case KeyG:
	  OSGKey = KeyEvent::KEY_G;
	  break;
	case KeyH:
	  OSGKey = KeyEvent::KEY_H;
	  break;
	case KeyI:
	  OSGKey = KeyEvent::KEY_I;
	  break;
	case KeyJ:
	  OSGKey = KeyEvent::KEY_J;
	  break;
	case KeyK:
	  OSGKey = KeyEvent::KEY_K;
	  break;
	case KeyL:
	  OSGKey = KeyEvent::KEY_L;
	  break;
	case KeyM:
	  OSGKey = KeyEvent::KEY_M;
	  break;
	case KeyN:
	  OSGKey = KeyEvent::KEY_N;
	  break;
	case KeyO:
	  OSGKey = KeyEvent::KEY_O;
	  break;
	case KeyP:
	  OSGKey = KeyEvent::KEY_P;
	  break;
	case KeyQ:
	  OSGKey = KeyEvent::KEY_Q;
	  break;
	case KeyR:
	  OSGKey = KeyEvent::KEY_R;
	  break;
	case KeyS:
	  OSGKey = KeyEvent::KEY_S;
	  break;
	case KeyT:
	  OSGKey = KeyEvent::KEY_T;
	  break;
	case KeyU:
	  OSGKey = KeyEvent::KEY_U;
	  break;
	case KeyV:
	  OSGKey = KeyEvent::KEY_V;
	  break;
	case KeyW:
	  OSGKey = KeyEvent::KEY_W;
	  break;
	case KeyX:
	  OSGKey = KeyEvent::KEY_X;
	  break;
	case KeyY:
	  OSGKey = KeyEvent::KEY_Y;
	  break;
	case KeyZ:
	  OSGKey = KeyEvent::KEY_Z;
	  break;
	//Numbers
	case Key0:
	  OSGKey = KeyEvent::KEY_0;
	  break;
	case Key1:
	  OSGKey = KeyEvent::KEY_1;
	  break;
	case Key2:
	  OSGKey = KeyEvent::KEY_2;
	  break;
	case Key3:
	  OSGKey = KeyEvent::KEY_3;
	  break;
	case Key4:
	  OSGKey = KeyEvent::KEY_4;
	  break;
	case Key5:
	  OSGKey = KeyEvent::KEY_5;
	  break;
	case Key6:
	  OSGKey = KeyEvent::KEY_6;
	  break;
	case Key7:
	  OSGKey = KeyEvent::KEY_7;
	  break;
	case Key8:
	  OSGKey = KeyEvent::KEY_8;
	  break;
	case Key9:
	  OSGKey = KeyEvent::KEY_9;
	  break;

	//Other
	case KeyMinus:
	  OSGKey = KeyEvent::KEY_MINUS;
	  break;
	case KeyEquals:
	  OSGKey = KeyEvent::KEY_EQUALS;
	  break;
	case KeyBackquote:
	  OSGKey = KeyEvent::KEY_BACK_QUOTE;
	  break;
	case KeyTab:
	  OSGKey = KeyEvent::KEY_TAB;
	  break;
	case KeySpacebar:
	  OSGKey = KeyEvent::KEY_SPACE;
	  break;
	case KeyLeftBracket:
	  OSGKey = KeyEvent::KEY_OPEN_BRACKET;
	  break;
	case KeyRightBracket:
	  OSGKey = KeyEvent::KEY_CLOSE_BRACKET;
	  break;
	case KeySemicolon:
	  OSGKey = KeyEvent::KEY_SEMICOLON;
	  break;
	case KeyComma:
	  OSGKey = KeyEvent::KEY_COMMA;
	  break;
	case KeyPeriod:
	  OSGKey = KeyEvent::KEY_PERIOD;
	  break;
	case KeyBackslash:
	  OSGKey = KeyEvent::KEY_BACK_SLASH;
	  break;
	case KeyApostrophe:
	  OSGKey = KeyEvent::KEY_APOSTROPHE;
	  break;
	case KeySlash:
	  OSGKey = KeyEvent::KEY_SLASH;
	  break;

	//Non-visible
	case KeyEscape:
	  OSGKey = KeyEvent::KEY_ESCAPE;
	  break;
	case KeyShift:
	  OSGKey = KeyEvent::KEY_SHIFT;
	  break;
	case KeyControl:
	  OSGKey = KeyEvent::KEY_CONTROL;
	  break;
	case KeyMacCommand:
	  OSGKey = KeyEvent::KEY_META;
	  break;
	case KeyMenu:
	  OSGKey = KeyEvent::KEY_ALT;
	  break;
	case KeyReturn:
	  OSGKey = KeyEvent::KEY_ENTER;
	  break;
	//case KeyCancel:
	//  OSGKey = KeyEvent::KEY_CANCEL;
	//  break;
	case KeyClear:
	  OSGKey = KeyEvent::KEY_CLEAR;
	  break;
	//case KeyPause:
	//  OSGKey = KeyEvent::KEY_PAUSE;
	//  break;
	case KeyCapsLock:
	  OSGKey = KeyEvent::KEY_CAPS_LOCK;
	  break;
	case KeyEnd:
	  OSGKey = KeyEvent::KEY_END;
	  break;
	case KeyHome:
	  OSGKey = KeyEvent::KEY_HOME;
	  break;
	case KeyPageUp:
	  OSGKey = KeyEvent::KEY_PAGE_UP;
	  break;
	case KeyPageDown:
	  OSGKey = KeyEvent::KEY_PAGE_DOWN;
	  break;
	case KeyUp:
	  OSGKey = KeyEvent::KEY_UP;
	  break;
	case KeyDown:
	  OSGKey = KeyEvent::KEY_DOWN;
	  break;
	case KeyLeft:
	  OSGKey = KeyEvent::KEY_LEFT;
	  break;
	case KeyRight:
	  OSGKey = KeyEvent::KEY_RIGHT;
	  break;
	//case KeySNAPSHOT:
	//  OSGKey = KeyEvent::KEY_PRINTSCREEN;
	//  break;
	//case KeyInsert:
	//  OSGKey = KeyEvent::KEY_INSERT;
	//  break;
	case KeyDelete:
	  OSGKey = KeyEvent::KEY_DELETE;
	  break;
	case KeyHelp:
	  OSGKey = KeyEvent::KEY_HELP;
	  break;
	//case KeyNUMLOCK:
	//  OSGKey = KeyEvent::KEY_NUM_LOCK;
	//  break;
	//case KeySCROLL:
	//  OSGKey = KeyEvent::KEY_SCROLL_LOCK;
	//  break;
	case KeyBackspace:
	  OSGKey = KeyEvent::KEY_BACK_SPACE;
	  break;

	//Function Keys
	case KeyF1:
	  OSGKey = KeyEvent::KEY_F1;
	  break;
	case KeyF2:
	  OSGKey = KeyEvent::KEY_F2;
	  break;
	case KeyF3:
	  OSGKey = KeyEvent::KEY_F3;
	  break;
	case KeyF4:
	  OSGKey = KeyEvent::KEY_F4;
	  break;
	case KeyF5:
	  OSGKey = KeyEvent::KEY_F5;
	  break;
	case KeyF6:
	  OSGKey = KeyEvent::KEY_F6;
	  break;
	case KeyF7:
	  OSGKey = KeyEvent::KEY_F7;
	  break;
	case KeyF8:
	  OSGKey = KeyEvent::KEY_F8;
	  break;
	case KeyF9:
	  OSGKey = KeyEvent::KEY_F9;
	  break;
	case KeyF10:
	  OSGKey = KeyEvent::KEY_F10;
	  break;
	case KeyF11:
	  OSGKey = KeyEvent::KEY_F11;
	  break;
	case KeyF12:
	  OSGKey = KeyEvent::KEY_F12;
	  break;
	  
	//Numpad Keys
	case KeyNum0:
	  OSGKey = KeyEvent::KEY_NUMPAD_0;
	  break;
	case KeyNum1:
	  OSGKey = KeyEvent::KEY_NUMPAD_1;
	  break;
	case KeyNum2:
	  OSGKey = KeyEvent::KEY_NUMPAD_2;
	  break;
	case KeyNum3:
	  OSGKey = KeyEvent::KEY_NUMPAD_3;
	  break;
	case KeyNum4:
	  OSGKey = KeyEvent::KEY_NUMPAD_4;
	  break;
	case KeyNum5:
	  OSGKey = KeyEvent::KEY_NUMPAD_5;
	  break;
	case KeyNum6:
	  OSGKey = KeyEvent::KEY_NUMPAD_6;
	  break;
	case KeyNum7:
	  OSGKey = KeyEvent::KEY_NUMPAD_7;
	  break;
	case KeyNum8:
	  OSGKey = KeyEvent::KEY_NUMPAD_8;
	  break;
	case KeyNum9:
	  OSGKey = KeyEvent::KEY_NUMPAD_9;
	  break;
	case KeyMultiply:
	  OSGKey = KeyEvent::KEY_MULTIPLY;
	  break;
	case KeyAdd:
	  OSGKey = KeyEvent::KEY_ADD;
	  break;
	case KeySubtract:
	  OSGKey = KeyEvent::KEY_SUBTRACT;
	  break;
	case KeyDivide:
	  OSGKey = KeyEvent::KEY_DIVIDE;
	  break;
	case KeyDecimal:
	  OSGKey = KeyEvent::KEY_DECIMAL;
	  break;
	case KeyNumEqual:
	  OSGKey = KeyEvent::KEY_NUMPAD_EQUALS;
	  break;
	  
	default:
	  OSGKey = KeyEvent::KEY_UNKNOWN;
	  break;
	}
	return OSGKey;
}

void CarbonWindowEventProducer::setPosition(Pnt2f Pos)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	Vec3s Size(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
	GlobalBounds.left = Pos.x();
	GlobalBounds.top = Pos.y();
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Pnt2f CarbonWindowEventProducer::getPosition(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Pnt2f(GlobalBounds.left, GlobalBounds.top);
}


void CarbonWindowEventProducer::setSize(Vec2us Size)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Vec2f CarbonWindowEventProducer::getSize(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Vec2f(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
}

void CarbonWindowEventProducer::setFocused(bool Focused)
{
	ActivateWindow(_WindowRef, Focused);
}

bool CarbonWindowEventProducer::getFocused(void) const
{
    return IsWindowActive(_WindowRef);
}

void CarbonWindowEventProducer::setVisible(bool Visible)
{
	if(Visible)
	{
		ShowWindow(_WindowRef);
	}
	else
	{
		HideWindow(_WindowRef);
	}
}

bool CarbonWindowEventProducer::getVisible(void) const
{
    return IsWindowVisible(_WindowRef);
}

void CarbonWindowEventProducer::setIconify(bool Iconify)
{
	CollapseWindow(_WindowRef, Iconify);
}

bool CarbonWindowEventProducer::getIconify(void) const
{
    return IsWindowCollapsed(_WindowRef);
}

void CarbonWindowEventProducer::setFullscreen(bool Fullscreen)
{
    assert(false && "Not Implemented");
	if(Fullscreen)
	{
		::Ptr      _OldScreenState;
		std::cout << "Fullscreen" << std::endl;
		//CGCaptureAllDisplays();
		//BeginFullScreen(&_OldScreenState, NULL, 0, 0, &_WindowRef, NULL, 0);
	}
	else
	{
		std::cout << "NotFullscreen" << std::endl;
		//EndFullScreen(NULL, NULL);
	}
}

bool CarbonWindowEventProducer::getFullscreen(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setTitle(const std::string& TitleText)
{
    SetWindowTitleWithCFString(_WindowRef, CFStringCreateWithCString(NULL, TitleText.c_str(), TitleText.size()));
}

std::string CarbonWindowEventProducer::getTitle(void)
{
	CFStringRef AppleString;
	CopyWindowTitleAsCFString(_WindowRef, &AppleString);
	char value[512];
	CFStringGetCString(AppleString, value, sizeof(value), 0);
	CFRelease(AppleString);
	
    return std::string(value);
}

void CarbonWindowEventProducer::setRisizable(bool IsResizable)
{
	//_WindowRef->kWindowResizableAttribute = (1L << 4);

	
    //TODO: Implement
    assert(false && "Not Implemented");
	
}

bool CarbonWindowEventProducer::getRisizable(void)
{
	WindowAttributes Attributes;
	GetWindowAttributes(_WindowRef, &Attributes);
	
    //TODO: Implement
	
    
    return (Attributes & kWindowResizableAttribute);
	
}

void CarbonWindowEventProducer::setDrawBorder(bool DrawBorder)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getDrawBorder(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}


void CarbonWindowEventProducer::draw(void)
{
    //TODO: Implement
    /*EventRef DrawEvent;
    if( CreateEvent(NULL,kEventClassWindow, kEventWindowDrawContent,0, 0, &DrawEvent) == noErr )
    {
        SetEventParameter(DrawEvent,  kEventParamDirectObject, typeWindowRef, sizeof(_WindowRef), &_WindowRef);
        SendEventToWindow(DrawEvent, _WindowRef);
    }*/
}

void CarbonWindowEventProducer::update(void)
{
    //Updating
    Time Now(getSystemTime());
    Time ElapsedTime(Now - getLastUpdateTime());
    if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
    {
        produceUpdate(ElapsedTime);
    }
    beginEditCP(CarbonWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
	   setLastUpdateTime(Now);
    endEditCP(CarbonWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
}

bool CarbonWindowEventProducer::attachWindow(void)
{
    assert(_WindowId != 0);
    
    if(_CarbonWindowToProducerMap.find(_WindowId) != _CarbonWindowToProducerMap.end())
    {
        return false;
    }
    
    _CarbonWindowToProducerMap[_WindowId] = CarbonWindowEventProducerPtr(this);
    
    return true;
}

UInt32 CarbonWindowEventProducer::getKeyModifiers(void) const
{
    return determineKeyModifiers(GetCurrentEventKeyModifiers());
}

Pnt2f CarbonWindowEventProducer::getMousePosition(void) const
{
	::Point MousePositioon;
	GetGlobalMouse(&MousePositioon);
	
    // Get the window
    SetPortWindowPort(_WindowRef);
    GlobalToLocal(&MousePositioon);
	
    return Pnt2f(MousePositioon.v, MousePositioon.h);
}


std::string CarbonWindowEventProducer::getClipboard(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return std::string("");
}

void CarbonWindowEventProducer::putClipboard(const std::string Value)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

void CarbonWindowEventProducer::openWindow(const Pnt2f& ScreenPosition,
				   const Vec2f& Size,
				   const std::string& WindowName)
{
	//Unblock the main
	_MainThreadSyncBarrier->enter(2);
}

void CarbonWindowEventProducer::closeWindow(void)
{
    DisposeWindow(_WindowRef);
}

void CarbonWindowEventProducer::setCursor(void)
{
	ThemeCursor c;
	switch(getCursorType())
	{
        case CURSOR_HAND:
            c = kThemePointingHandCursor;
            break;
        case CURSOR_I_BEAM:
            c = kThemeIBeamCursor;
            break;
        case CURSOR_WAIT:
            c = kThemeWatchCursor;
            break;
        case CURSOR_RESIZE_W_TO_E:
            c = kThemeResizeLeftRightCursor;
            break;
        case CURSOR_RESIZE_N_TO_S:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_NW_TO_SE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_SW_TO_NE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_ALL:
            c = kThemeClosedHandCursor;
            break;
        case CURSOR_NONE:
            c = kThemeArrowCursor;
            break;
        case CURSOR_POINTER:
        default:
            c = kThemeArrowCursor;
            break;
	}
	SetThemeCursor(c);
}

WindowPtr CarbonWindowEventProducer::createWindow(void)
{
    return CarbonWindow::create();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CarbonWindowEventProducer::CarbonWindowEventProducer(void) :
    Inherited()
{
}

CarbonWindowEventProducer::CarbonWindowEventProducer(const CarbonWindowEventProducer &source) :
    Inherited(source)
{
}

CarbonWindowEventProducer::~CarbonWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CarbonWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CarbonWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CarbonWindowEventProducer NI" << std::endl;
}

CarbonWindowEventProducer::WindowEventLoopThreadArguments::WindowEventLoopThreadArguments(
                       const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName,
                       CarbonWindowPtr TheWindow,
                       CarbonWindowEventProducerPtr TheEventProducer) :
        _ScreenPosition(ScreenPosition),
        _Size(Size),
        _WindowName(WindowName),
        _Window(TheWindow),
        _EventProducer(TheEventProducer)
{
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
    static Char8 cvsid_hpp       [] = OSGCARBONWINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCARBONWINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCARBONWINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

#endif

