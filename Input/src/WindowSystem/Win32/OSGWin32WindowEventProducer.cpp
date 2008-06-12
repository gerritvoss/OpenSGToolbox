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
#include <OpenSG/OSGConfig.h>

#include "OSGWin32WindowEventProducer.h"
#include "WindowSystem/OSGWindowEventProducerFactory.h"

#ifdef WIN32

#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
#include <Windowsx.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Win32WindowEventProducer
Win32WindowEventProducer Class.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

Win32WindowEventProducer::WIN32HWNDToProducerMap Win32WindowEventProducer::_WIN32HWNDToProducerMap;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Win32WindowEventProducer::initMethod (void)
{
}

void Win32WindowEventProducer::WindowEventLoopThread(void* args)
{
    WindowEventLoopThreadArguments* Arguments(static_cast<WindowEventLoopThreadArguments*>(args));

    //Create the Win32 Window
    WNDCLASS  wndClass;
    HWND           hwnd;

    // Win32 Init
    memset(&wndClass, 0, sizeof(wndClass));
    wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = Win32WindowEventProducer::staticWndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    // doesn't compile?!? wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpszClassName = Arguments->_WindowName.c_str();
    if (!RegisterClass(&wndClass)) 
    {
        return;
    }


    // Create a Window
    hwnd = CreateWindow( Arguments->_WindowName.c_str(), Arguments->_WindowName.c_str(),
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                    Arguments->_ScreenPosition.x(), 
                    Arguments->_ScreenPosition.y(), 
                    Arguments->_Size.x(), 
                    Arguments->_Size.y(),
                    NULL, 
                    NULL, 
                    GetModuleHandle(NULL), 
                    0 );

    //Attach Window
    beginEditCP(Arguments->_Window, WIN32Window::HwndFieldMask);
        Arguments->_Window->setHwnd(hwnd);
    endEditCP(Arguments->_Window, WIN32Window::HwndFieldMask);

    Arguments->_EventProducer->attachWindow();
        
    Arguments->_Window->init();
    Arguments->_Window->deactivate();

    
    //Open the Window and enter the main event loop
	ShowWindow( hwnd, SW_SHOWNORMAL );
	SetActiveWindow( hwnd );
	
    MSG msg;
	// main loop 
    while ( GetMessage(&msg, NULL, 0, 0) > 0 )
    {
        DispatchMessage(&msg);
        WaitMessage();
    }
    Arguments->_EventProducer->produceWindowClosed();
    
    //Delete my arguments, to avoid memory leak
    delete Arguments;
}

LRESULT Win32WindowEventProducer::staticWndProc(HWND hwnd, UINT uMsg,
                         WPARAM wParam, LPARAM lParam)
{
   if(_WIN32HWNDToProducerMap.find(hwnd) != _WIN32HWNDToProducerMap.end())
   {
      return _WIN32HWNDToProducerMap[hwnd]->WndProc(hwnd, uMsg,
                           wParam, lParam);
   }
   else
   {
      switch(uMsg)
      {
         case WM_CREATE:
            {
               PIXELFORMATDESCRIPTOR   pfd;
               HDC           hDC;
               int iPixelFormat;

                ZeroMemory( &pfd, sizeof( pfd ) );
                pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
                pfd.nVersion = 1;
                pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                      PFD_DOUBLEBUFFER;
                pfd.iPixelType = PFD_TYPE_RGBA;
                pfd.cColorBits = 32;
                pfd.cDepthBits = 32;
                pfd.iLayerType = PFD_MAIN_PLANE;
                pfd.cStencilBits = 8;
                

               // init the OSG window  
               hDC = GetDC(hwnd);

               iPixelFormat = ChoosePixelFormat(hDC, &pfd);
               if (! SetPixelFormat(hDC, iPixelFormat, &pfd) )
               {
                   FWARNING(("Failed to set Pixel Format."));
               }
               
               break;
            }
         default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
      }
   }
   return 0;
}

std::string Win32WindowEventProducer::getClipboard(void) const
{
	//TODO:Implement
	return std::string("");
}

void Win32WindowEventProducer::putClipboard(const std::string Value)
{
	//TODO:Implement
	if(OpenClipboard(WIN32Window::Ptr::dcast(getWindow())->getHwnd()))
	{
		if(EmptyClipboard())
		{
			HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (Value.size() + 1) * sizeof(char));
			if(hglbCopy != NULL)
			{
				LPTSTR  lptstrCopy;
				//lptstrCopy = GlobalLock(hglbCopy); 
				//memcpy(lptstrCopy, &pbox->atchLabel[ich1],  cch * sizeof(TCHAR)); 
				//lptstrCopy[Value.size()] = (char) 0;    // null character 
				//GlobalUnlock(hglbCopy);
				SetClipboardData(CF_TEXT, hglbCopy);
			}
		}
		CloseClipboard();
	}
}

void Win32WindowEventProducer::setCursor(void)
{
	LPSTR c;
	switch(getCursorType())
	{
	case CURSOR_POINTER:
		c = IDC_ARROW;
		break;
	case CURSOR_HAND:
		c = IDC_HAND;
		break;
	case CURSOR_I_BEAM:
		c = IDC_IBEAM;
		break;
	case CURSOR_WAIT:
		c = IDC_WAIT;
		break;
	case CURSOR_RESIZE_W_TO_E:
		c = IDC_SIZEWE;
		break;
	case CURSOR_RESIZE_N_TO_S:
		c = IDC_SIZENS;
		break;
	case CURSOR_RESIZE_NW_TO_SE:
		c = IDC_SIZENWSE;
		break;
	case CURSOR_RESIZE_SW_TO_NE:
		c = IDC_SIZENESW;
		break;
	case CURSOR_RESIZE_ALL:
		c = IDC_SIZEALL;
		break;
	case CURSOR_NONE:
		c = IDC_NO;
		break;
	default:
		c = IDC_ARROW;
		break;
	}
	SetCursor(LoadCursor(NULL, c));
}

Pnt2f Win32WindowEventProducer::getMousePosition(void) const
{
    DWORD MousePos = GetMessagePos();
	LPPOINT ClientPoint = new POINT;
	ClientPoint->x = LOWORD(MousePos);
	ClientPoint->y = HIWORD(MousePos);

    Pnt2f Result(0,0);
    if(ScreenToClient(WIN32Window::Ptr::dcast(getWindow())->getHwnd(), ClientPoint))
	{
        Result.setValues(ClientPoint->x, ClientPoint->y);
    }
    delete ClientPoint;
	return Result;

}

UInt32 Win32WindowEventProducer::getKeyModifiers(void) const
{
   UInt32 Modifiers = 0;

   if(GetKeyState(VK_SHIFT)<0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_SHIFT;
   }
   if(GetKeyState(VK_CONTROL)<0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CONTROL;
   }
   if(GetKeyState(VK_MENU)<0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_ALT;
   }
   if(GetKeyState(VK_CAPITAL)>0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CAPS_LOCK;
   }
   if(GetKeyState(VK_NUMLOCK)>0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_NUM_LOCK;
   }
   if(GetKeyState(VK_SCROLL)>0)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_SCROLL_LOCK;
   }
   return Modifiers;
}

KeyEvent::Key Win32WindowEventProducer::determineKey(WPARAM key)
{
   KeyEvent::Key OSGKey;
   switch(key)
   {
   //Alphabet
   case 'A':
      OSGKey = KeyEvent::KEY_A;
      break;
   case 'B':
      OSGKey = KeyEvent::KEY_B;
      break;
   case 'C':
      OSGKey = KeyEvent::KEY_C;
      break;
   case 'D':
      OSGKey = KeyEvent::KEY_D;
      break;
   case 'E':
      OSGKey = KeyEvent::KEY_E;
      break;
   case 'F':
      OSGKey = KeyEvent::KEY_F;
      break;
   case 'G':
      OSGKey = KeyEvent::KEY_G;
      break;
   case 'H':
      OSGKey = KeyEvent::KEY_H;
      break;
   case 'I':
      OSGKey = KeyEvent::KEY_I;
      break;
   case 'J':
      OSGKey = KeyEvent::KEY_J;
      break;
   case 'K':
      OSGKey = KeyEvent::KEY_K;
      break;
   case 'L':
      OSGKey = KeyEvent::KEY_L;
      break;
   case 'M':
      OSGKey = KeyEvent::KEY_M;
      break;
   case 'N':
      OSGKey = KeyEvent::KEY_N;
      break;
   case 'O':
      OSGKey = KeyEvent::KEY_O;
      break;
   case 'P':
      OSGKey = KeyEvent::KEY_P;
      break;
   case 'Q':
      OSGKey = KeyEvent::KEY_Q;
      break;
   case 'R':
      OSGKey = KeyEvent::KEY_R;
      break;
   case 'S':
      OSGKey = KeyEvent::KEY_S;
      break;
   case 'T':
      OSGKey = KeyEvent::KEY_T;
      break;
   case 'U':
      OSGKey = KeyEvent::KEY_U;
      break;
   case 'V':
      OSGKey = KeyEvent::KEY_V;
      break;
   case 'W':
      OSGKey = KeyEvent::KEY_W;
      break;
   case 'X':
      OSGKey = KeyEvent::KEY_X;
      break;
   case 'Y':
      OSGKey = KeyEvent::KEY_Y;
      break;
   case 'Z':
      OSGKey = KeyEvent::KEY_Z;
      break;
   //Numbers
   case '0':
      OSGKey = KeyEvent::KEY_0;
      break;
   case '1':
      OSGKey = KeyEvent::KEY_1;
      break;
   case '2':
      OSGKey = KeyEvent::KEY_2;
      break;
   case '3':
      OSGKey = KeyEvent::KEY_3;
      break;
   case '4':
      OSGKey = KeyEvent::KEY_4;
      break;
   case '5':
      OSGKey = KeyEvent::KEY_5;
      break;
   case '6':
      OSGKey = KeyEvent::KEY_6;
      break;
   case '7':
      OSGKey = KeyEvent::KEY_7;
      break;
   case '8':
      OSGKey = KeyEvent::KEY_8;
      break;
   case '9':
      OSGKey = KeyEvent::KEY_9;
      break;

   //Other
   case VK_OEM_MINUS:
      OSGKey = KeyEvent::KEY_MINUS;
      break;
   case VK_OEM_PLUS:
      OSGKey = KeyEvent::KEY_EQUALS;
      break;
   case VK_OEM_3:
      OSGKey = KeyEvent::KEY_BACK_QUOTE;
      break;
   case VK_TAB:
      OSGKey = KeyEvent::KEY_TAB;
      break;
   case VK_SPACE:
      OSGKey = KeyEvent::KEY_SPACE;
      break;
   case VK_OEM_4:
      OSGKey = KeyEvent::KEY_OPEN_BRACKET;
      break;
   case VK_OEM_6:
      OSGKey = KeyEvent::KEY_CLOSE_BRACKET;
      break;
   case VK_OEM_1:
      OSGKey = KeyEvent::KEY_SEMICOLON;
      break;
   case VK_OEM_COMMA:
      OSGKey = KeyEvent::KEY_COMMA;
      break;
   case VK_OEM_PERIOD:
      OSGKey = KeyEvent::KEY_PERIOD;
      break;
   case VK_OEM_5:
      OSGKey = KeyEvent::KEY_BACK_SLASH;
      break;
   case VK_OEM_7:
      OSGKey = KeyEvent::KEY_APOSTROPHE;
      break;
   case VK_OEM_2:
      OSGKey = KeyEvent::KEY_SLASH;
      break;

   //Non-visible
   case VK_ESCAPE:
      OSGKey = KeyEvent::KEY_ESCAPE;
      break;
   case VK_SHIFT:
      OSGKey = KeyEvent::KEY_SHIFT;
      break;
   case VK_CONTROL:
      OSGKey = KeyEvent::KEY_CONTROL;
      break;
   case VK_MENU:
      OSGKey = KeyEvent::KEY_ALT;
      break;
   case VK_RETURN:
      OSGKey = KeyEvent::KEY_ENTER;
      break;
   case VK_CANCEL:
      OSGKey = KeyEvent::KEY_CANCEL;
      break;
   case VK_CLEAR:
      OSGKey = KeyEvent::KEY_CLEAR;
      break;
   case VK_PAUSE:
      OSGKey = KeyEvent::KEY_PAUSE;
      break;
   case VK_CAPITAL:
      OSGKey = KeyEvent::KEY_CAPS_LOCK;
      break;
   case VK_END:
      OSGKey = KeyEvent::KEY_END;
      break;
   case VK_PRIOR:
      OSGKey = KeyEvent::KEY_PAGE_UP;
      break;
   case VK_NEXT:
      OSGKey = KeyEvent::KEY_PAGE_DOWN;
      break;
   case VK_HOME:
      OSGKey = KeyEvent::KEY_HOME;
      break;
   case VK_UP:
      OSGKey = KeyEvent::KEY_UP;
      break;
   case VK_DOWN:
      OSGKey = KeyEvent::KEY_DOWN;
      break;
   case VK_LEFT:
      OSGKey = KeyEvent::KEY_LEFT;
      break;
   case VK_RIGHT:
      OSGKey = KeyEvent::KEY_RIGHT;
      break;
   case VK_SNAPSHOT:
      OSGKey = KeyEvent::KEY_PRINTSCREEN;
      break;
   case VK_INSERT:
      OSGKey = KeyEvent::KEY_INSERT;
      break;
   case VK_DELETE:
      OSGKey = KeyEvent::KEY_DELETE;
      break;
   case VK_HELP:
      OSGKey = KeyEvent::KEY_HELP;
      break;
   case VK_NUMLOCK:
      OSGKey = KeyEvent::KEY_NUM_LOCK;
      break;
   case VK_SCROLL:
      OSGKey = KeyEvent::KEY_SCROLL_LOCK;
      break;
   case VK_BACK:
      OSGKey = KeyEvent::KEY_BACK_SPACE;
      break;

   //Function Keys
   case VK_F1:
      OSGKey = KeyEvent::KEY_F1;
      break;
   case VK_F2:
      OSGKey = KeyEvent::KEY_F2;
      break;
   case VK_F3:
      OSGKey = KeyEvent::KEY_F3;
      break;
   case VK_F4:
      OSGKey = KeyEvent::KEY_F4;
      break;
   case VK_F5:
      OSGKey = KeyEvent::KEY_F5;
      break;
   case VK_F6:
      OSGKey = KeyEvent::KEY_F6;
      break;
   case VK_F7:
      OSGKey = KeyEvent::KEY_F7;
      break;
   case VK_F8:
      OSGKey = KeyEvent::KEY_F8;
      break;
   case VK_F9:
      OSGKey = KeyEvent::KEY_F9;
      break;
   case VK_F10:
      OSGKey = KeyEvent::KEY_F10;
      break;
   case VK_F11:
      OSGKey = KeyEvent::KEY_F11;
      break;
   case VK_F12:
      OSGKey = KeyEvent::KEY_F12;
      break;
   case VK_F13:
      OSGKey = KeyEvent::KEY_F13;
      break;
   case VK_F14:
      OSGKey = KeyEvent::KEY_F14;
      break;
   case VK_F15:
      OSGKey = KeyEvent::KEY_F15;
      break;
   case VK_F16:
      OSGKey = KeyEvent::KEY_F16;
      break;
   case VK_F17:
      OSGKey = KeyEvent::KEY_F17;
      break;
   case VK_F18:
      OSGKey = KeyEvent::KEY_F18;
      break;
   case VK_F19:
      OSGKey = KeyEvent::KEY_F19;
      break;
   case VK_F20:
      OSGKey = KeyEvent::KEY_F20;
      break;
   case VK_F21:
      OSGKey = KeyEvent::KEY_F21;
      break;
   case VK_F22:
      OSGKey = KeyEvent::KEY_F22;
      break;
   case VK_F23:
      OSGKey = KeyEvent::KEY_F23;
      break;
   case VK_F24:
      OSGKey = KeyEvent::KEY_F24;
      break;
      
   //Numpad Keys
   case VK_NUMPAD0:
      OSGKey = KeyEvent::KEY_NUMPAD_0;
      break;
   case VK_NUMPAD1:
      OSGKey = KeyEvent::KEY_NUMPAD_1;
      break;
   case VK_NUMPAD2:
      OSGKey = KeyEvent::KEY_NUMPAD_2;
      break;
   case VK_NUMPAD3:
      OSGKey = KeyEvent::KEY_NUMPAD_3;
      break;
   case VK_NUMPAD4:
      OSGKey = KeyEvent::KEY_NUMPAD_4;
      break;
   case VK_NUMPAD5:
      OSGKey = KeyEvent::KEY_NUMPAD_5;
      break;
   case VK_NUMPAD6:
      OSGKey = KeyEvent::KEY_NUMPAD_6;
      break;
   case VK_NUMPAD7:
      OSGKey = KeyEvent::KEY_NUMPAD_7;
      break;
   case VK_NUMPAD8:
      OSGKey = KeyEvent::KEY_NUMPAD_8;
      break;
   case VK_NUMPAD9:
      OSGKey = KeyEvent::KEY_NUMPAD_9;
      break;
      
   default:
      OSGKey = KeyEvent::KEY_UNKNOWN;
      break;
   }
   return OSGKey;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Win32WindowEventProducer::draw(void)
{
    SendMessage(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),WIN32_DRAW_MESSAGE,0,0);
}

void Win32WindowEventProducer::update(void)
{
    SendMessage(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),WIN32_UPDATE_MESSAGE,0,0);
}

WindowPtr Win32WindowEventProducer::createWindow(void)
{
    // Create OSGWin32Window
    return WIN32Window::create();
}

void Win32WindowEventProducer::openWindow(const Pnt2f& ScreenPosition,
                    const Vec2f& Size,
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
                    WIN32Window::Ptr::dcast(getWindow()),
                    Win32WindowEventProducerPtr(this)  );
    
    //ChangeList::setReadWriteDefault();
    _WindowEventLoopThread->runFunction(WindowEventLoopThread, 0, static_cast<void*>(Arguments));
}

bool Win32WindowEventProducer::attachWindow(void)
{
    if(_WIN32HWNDToProducerMap.find(WIN32Window::Ptr::dcast(getWindow())->getHwnd()) != _WIN32HWNDToProducerMap.end())
    {
        return false;
    }
    
    _WIN32HWNDToProducerMap[WIN32Window::Ptr::dcast(getWindow())->getHwnd()] = Win32WindowEventProducerPtr(this);
    
    return true;
}

LRESULT Win32WindowEventProducer::WndProc(HWND hwnd, UINT uMsg,
                     WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {       
        case WM_LBUTTONDOWN:
            produceMousePressed(MouseEvent::BUTTON1, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;
        case WM_MBUTTONDOWN:
            produceMousePressed(MouseEvent::BUTTON2, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;
        case WM_RBUTTONDOWN:
            produceMousePressed(MouseEvent::BUTTON3, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            SetCapture(hwnd);
            break;   
        case WM_LBUTTONUP:
            produceMouseReleased(MouseEvent::BUTTON1, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;              
        case WM_MBUTTONUP:
            produceMouseReleased(MouseEvent::BUTTON2, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;
        case WM_RBUTTONUP:
            produceMouseReleased(MouseEvent::BUTTON3, Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
            ReleaseCapture();
            break;
        case WM_MOUSEWHEEL:
			{
				//The lParam gives the Mouse location in screen space
				//Convert it to client area space
				LPPOINT ClientPoint = new POINT;
				ClientPoint->x = GET_X_LPARAM(lParam);
				ClientPoint->y = GET_Y_LPARAM(lParam);
				if(ScreenToClient(hwnd, ClientPoint))
				{
					produceMouseWheelMoved(static_cast<short>(HIWORD(wParam))/WHEEL_DELTA, Pnt2f(ClientPoint->x,ClientPoint->y));
				}
				else
				{
				}
                delete ClientPoint;
			}
            break;

        case WM_MOUSEMOVE:
            {
			    if(wParam & MK_LBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON1,Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			    }
			    if(wParam & MK_MBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON2,Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			    }
			    if(wParam & MK_RBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON3,Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
			    }
			    produceMouseMoved(Pnt2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
                
                /*POINT point;
                RECT rect;

                GetCursorPos(&point);
                GetWindowRect(hwnd, &rect);

                if(PtInRect(&rect, point))
                {
                    if(hwnd != GetCapture())
                    {
                        SetCapture(hwnd);
                    }
                    if(!_MouseOverWindow)
                    {
                        _MouseOverWindow = true;
                        produceWindowEntered();
                    }
                }
                else
                {
                    ReleaseCapture();
                    // Calling ReleaseCapture in Win95 also causes WM_CAPTURECHANGED
                    // to be sent.  Be sure to account for that.
                    if(_MouseOverWindow)
                    {
                        _MouseOverWindow = false;
                        produceWindowExited();
                    }
                }*/
                break;
            }
                                    
        case WM_KEYDOWN:
            produceKeyPressed(determineKey(wParam),getKeyModifiers());
            break;                 
        case WM_KEYUP:
            produceKeyReleased(determineKey(wParam),getKeyModifiers());
            break;
                                    
        case WM_SIZE:
            getWindow()->resize( LOWORD(lParam), HIWORD( lParam ) );
            internalReshape(Vec2f(LOWORD(lParam), HIWORD( lParam )));
            break;

        case WM_CLOSE:
            produceWindowClosing();
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;
            
        case WIN32_DRAW_MESSAGE:
            internalDraw();
            break;

        case WIN32_UPDATE_MESSAGE:
            {
                //Updating
                Time Now(getSystemTime());
                Time ElapsedTime(Now - getLastUpdateTime());
                if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
                {
	                produceUpdate(ElapsedTime);
                }
                setLastUpdateTime(Now);
            }
            break;

        case WM_ACTIVATE:
            if(LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
            {
               produceWindowActivated();
            }
            else
            {
               produceWindowDeactivated();
            }
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;
        case WM_SYSCOMMAND:
           if (wParam == SC_MINIMIZE)
           {
               produceWindowIconified();
           }
           else if (wParam ==  SC_RESTORE)
           {
               produceWindowDeiconified();
           }

        case WM_SHOWWINDOW:
            if(wParam == TRUE && lParam == 0)
            {
               produceWindowOpened();
            }
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
            break;

        case WM_DESTROY:
            produceWindowClosing();
            PostQuitMessage(0);
            break;

		case WM_SETCURSOR:
			setCursor();
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
    }
    return 0;
}
//Set the Window Position
void Win32WindowEventProducer::setPosition(Pnt2f Pos)
{
    SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST, Pos.x(), Pos.y(), 0,0,
         SWP_NOSIZE | SWP_NOZORDER);
}

//Set the Window Position
Pnt2f Win32WindowEventProducer::getPosition(void) const
{
    RECT r;
    GetWindowRect(WIN32Window::Ptr::dcast(getWindow())->getHwnd(), &r);
    return Pnt2f(r.left, r.top);
}

//Set the Window size
void Win32WindowEventProducer::setSize(Vec2us Size)
{
    SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST, 0, 0, Size.x(),Size.y(),
         SWP_NOMOVE | SWP_NOZORDER);
}

//Get the Window size
Vec2f Win32WindowEventProducer::getSize(void) const
{
    RECT r;
    GetWindowRect(WIN32Window::Ptr::dcast(getWindow())->getHwnd(), &r);
    return Vec2f(r.right-r.left, r.bottom-r.top);
}

//Focused
//Set the Window Focus
void Win32WindowEventProducer::setFocused(bool Focused)
{
    if(Focused)
    {
        SetFocus(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
    }
    else
    {
        SetFocus(NULL);
    }
    
}

//Get the Window Focus
bool Win32WindowEventProducer::getFocused(void) const
{
   return GetForegroundWindow() == WIN32Window::Ptr::dcast(getWindow())->getHwnd();
}

//Visible / Iconify / Normal
//Set the Window Visible
void Win32WindowEventProducer::setVisible(bool Visible)
{
    if(Visible)
    {
        ShowWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),SW_SHOW);
    }
    else
    {
        ShowWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),SW_HIDE);
    }
}

//Get the Window Visible
bool Win32WindowEventProducer::getVisible(void) const
{
   return IsWindowVisible(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
}

//Set the Window Iconify
void Win32WindowEventProducer::setIconify(bool Iconify)
{
    if(Iconify)
    {
        ShowWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),SW_MINIMIZE);
    }
    else
    {
        ShowWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),SW_SHOWNORMAL);
    }
}

//Get the Window Iconify
bool Win32WindowEventProducer::getIconify(void) const
{
   return IsIconic(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
}

//Fullscreen
void Win32WindowEventProducer::setFullscreen(bool Fullscreen)
{
    //TODO: find a better way to do this
    if(Fullscreen)
    {
        SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN),
            SWP_NOZORDER);
    }
    else
    {
        SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST, 0, 0, 300,300,
            SWP_NOZORDER);
    }
}

//Get the Window Fullscreen
bool Win32WindowEventProducer::getFullscreen(void) const
{
    //TODO: find a better way to do this
    return false;
}

void Win32WindowEventProducer::closeWindow(void)
{
    if(getWindow() != NullFC)
    {
        DestroyWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
    }
}

void Win32WindowEventProducer::setTitle(const std::string& TitleText)
{
    SetWindowText(WIN32Window::Ptr::dcast(getWindow())->getHwnd(), TitleText.c_str());
}

std::string Win32WindowEventProducer::getTitle(void)
{
    int TextLength = GetWindowTextLength(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
    PTSTR Text = (PSTR) VirtualAlloc((LPVOID) NULL, 
                    (DWORD) (TextLength + 1), MEM_COMMIT, 
                    PAGE_READWRITE);

    GetWindowText(WIN32Window::Ptr::dcast(getWindow())->getHwnd(), Text, 
                    TextLength + 1);
    
    return std::string(Text);
}

void Win32WindowEventProducer::setRisizable(bool IsResizable)
{
    //TODO:Implement
}

bool Win32WindowEventProducer::getRisizable(void)
{
    //TODO:Implement
    return true;
}

void Win32WindowEventProducer::setDrawBorder(bool DrawBorder)
{
    //TODO:Implement
}

bool Win32WindowEventProducer::getDrawBorder(void)
{
    //TODO:Implement
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Win32WindowEventProducer::Win32WindowEventProducer(void) :
    Inherited(),
        _MouseOverWindow(false)
{
}

Win32WindowEventProducer::Win32WindowEventProducer(const Win32WindowEventProducer &source) :
    Inherited(source),
        _MouseOverWindow(false)
{
}

Win32WindowEventProducer::~Win32WindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

Win32WindowEventProducer::WindowEventLoopThreadArguments::WindowEventLoopThreadArguments(
                       const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName,
                       WIN32WindowPtr TheWindow,
                       Win32WindowEventProducerPtr TheEventProducer) :
        _ScreenPosition(ScreenPosition),
        _Size(Size),
        _WindowName(WindowName),
        _Window(TheWindow),
        _EventProducer(TheEventProducer)
{
}

void Win32WindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Win32WindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Win32WindowEventProducer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGWIN32WINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGWIN32WINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGWIN32WINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

#endif

