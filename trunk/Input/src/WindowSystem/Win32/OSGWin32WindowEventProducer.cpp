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
                pfd.cAlphaBits = 8;
                

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

void  Win32WindowEventProducer::mainLoop(void)
{
	// Main loop ( event dispatching )
    MSG msg;
	// main loop 
    WIN32HWNDToProducerMap::iterator MapItor;
    //while ( GetMessage(&msg, NULL, 0, 0) > 0 )
    while (_WIN32HWNDToProducerMap.size() != 0  )
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            DispatchMessage(&msg);
        }
        //WaitMessage();
        for( MapItor = _WIN32HWNDToProducerMap.begin(); MapItor != _WIN32HWNDToProducerMap.end(); ++MapItor)
        {
            MapItor->second->update();
            MapItor->second->draw();
        }
    }

    if (getFullscreen())								// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);						// Show Mouse Pointer
	}
}

std::string Win32WindowEventProducer::getClipboard(void) const
{
	if(OpenClipboard(WIN32Window::Ptr::dcast(getWindow())->getHwnd()))
	{
        // Try to open the clipboard
        std::string Content;
		if(IsClipboardFormatAvailable(CF_TEXT))
		{
            HANDLE h = GetClipboardData(CF_TEXT);
             if (h)
             {
                const char * buf = (const char *)::GlobalLock(h);
                Content = buf;
                if (!Content.empty())
                   ::GlobalUnlock(h);
             }
		}
		CloseClipboard();
	    return Content;
	}
    else
    {
	    return std::string("");
    }
}

void Win32WindowEventProducer::putClipboard(const std::string Value)
{
	if(OpenClipboard(WIN32Window::Ptr::dcast(getWindow())->getHwnd()))
	{
		if(EmptyClipboard())
		{
			HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (Value.size() + 1) * sizeof(char));
			if(hglbCopy != NULL)
			{
				//LPTSTR  lptstrCopy;
                void * buf = ::GlobalLock(hglbCopy);
                ::memcpy(buf, (const void *)Value.c_str(), Value.length()+1);
                ::GlobalUnlock(hglbCopy);
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

KeyEvent::KeyState Win32WindowEventProducer::getKeyState(KeyEvent::Key TheKey) const
{
	SHORT KeyState(0);
	switch(TheKey)
	{
	   //Alphabet
	   case KeyEvent::KEY_A:
		  KeyState = GetAsyncKeyState('A');
		  break;
	   case KeyEvent::KEY_B:
		  KeyState = GetAsyncKeyState('B');
		  break;
	   case KeyEvent::KEY_C:
		  KeyState = GetAsyncKeyState('C');
		  break;
	   case KeyEvent::KEY_D:
		  KeyState = GetAsyncKeyState('D');
		  break;
	   case KeyEvent::KEY_E:
		  KeyState = GetAsyncKeyState('E');
		  break;
	   case KeyEvent::KEY_F:
		  KeyState = GetAsyncKeyState('F');
		  break;
	   case KeyEvent::KEY_G:
		  KeyState = GetAsyncKeyState('G');
		  break;
	   case KeyEvent::KEY_H:
		  KeyState = GetAsyncKeyState('H');
		  break;
	   case KeyEvent::KEY_I:
		  KeyState = GetAsyncKeyState('I');
		  break;
	   case KeyEvent::KEY_J:
		  KeyState = GetAsyncKeyState('J');
		  break;
	   case KeyEvent::KEY_K:
		  KeyState = GetAsyncKeyState('K');
		  break;
	   case KeyEvent::KEY_L:
		  KeyState = GetAsyncKeyState('L');
		  break;
	   case KeyEvent::KEY_M:
		  KeyState = GetAsyncKeyState('M');
		  break;
	   case KeyEvent::KEY_N:
		  KeyState = GetAsyncKeyState('N');
		  break;
	   case KeyEvent::KEY_O:
		  KeyState = GetAsyncKeyState('O');
		  break;
	   case KeyEvent::KEY_P:
		  KeyState = GetAsyncKeyState('P');
		  break;
	   case KeyEvent::KEY_Q:
		  KeyState = GetAsyncKeyState('Q');
		  break;
	   case KeyEvent::KEY_R:
		  KeyState = GetAsyncKeyState('R');
		  break;
	   case KeyEvent::KEY_S:
		  KeyState = GetAsyncKeyState('S');
		  break;
	   case KeyEvent::KEY_T:
		  KeyState = GetAsyncKeyState('T');
		  break;
	   case KeyEvent::KEY_U:
		  KeyState = GetAsyncKeyState('U');
		  break;
	   case KeyEvent::KEY_V:
		  KeyState = GetAsyncKeyState('V');
		  break;
	   case KeyEvent::KEY_W:
		  KeyState = GetAsyncKeyState('W');
		  break;
	   case KeyEvent::KEY_X:
		  KeyState = GetAsyncKeyState('X');
		  break;
	   case KeyEvent::KEY_Y:
		  KeyState = GetAsyncKeyState('Y');
		  break;
	   case KeyEvent::KEY_Z:
		  KeyState = GetAsyncKeyState('Z');
		  break;
	   //Numbers
	   case KeyEvent::KEY_0:
		  KeyState = GetAsyncKeyState('0');
		  break;
	   case KeyEvent::KEY_1:
		  KeyState = GetAsyncKeyState('1');
		  break;
	   case KeyEvent::KEY_2:
		  KeyState = GetAsyncKeyState('2');
		  break;
	   case KeyEvent::KEY_3:
		  KeyState = GetAsyncKeyState('3');
		  break;
	   case KeyEvent::KEY_4:
		  KeyState = GetAsyncKeyState('4');
		  break;
	   case KeyEvent::KEY_5:
		  KeyState = GetAsyncKeyState('5');
		  break;
	   case KeyEvent::KEY_6:
		  KeyState = GetAsyncKeyState('6');
		  break;
	   case KeyEvent::KEY_7:
		  KeyState = GetAsyncKeyState('7');
		  break;
	   case KeyEvent::KEY_8:
		  KeyState = GetAsyncKeyState('8');
		  break;
	   case KeyEvent::KEY_9:
		  KeyState = GetAsyncKeyState('9');
		  break;

	   //Other
	   case KeyEvent::KEY_MINUS:
		  KeyState = GetAsyncKeyState(VK_OEM_MINUS);
		  break;
	   case KeyEvent::KEY_EQUALS:
		  KeyState = GetAsyncKeyState(VK_OEM_PLUS);
		  break;
	   case KeyEvent::KEY_BACK_QUOTE:
		  KeyState = GetAsyncKeyState(VK_OEM_3);
		  break;
	   case KeyEvent::KEY_TAB:
		  KeyState = GetAsyncKeyState(VK_TAB);
		  break;
	   case KeyEvent::KEY_SPACE:
		  KeyState = GetAsyncKeyState(VK_SPACE);
		  break;
	   case KeyEvent::KEY_OPEN_BRACKET:
		  KeyState = GetAsyncKeyState(VK_OEM_4);
		  break;
	   case KeyEvent::KEY_CLOSE_BRACKET:
		  KeyState = GetAsyncKeyState(VK_OEM_6);
		  break;
	   case KeyEvent::KEY_SEMICOLON:
		  KeyState = GetAsyncKeyState(VK_OEM_1);
		  break;
	   case KeyEvent::KEY_COMMA:
		  KeyState = GetAsyncKeyState(VK_OEM_COMMA);
		  break;
	   case KeyEvent::KEY_PERIOD:
		  KeyState = GetAsyncKeyState(VK_OEM_PERIOD);
		  break;
	   case KeyEvent::KEY_BACK_SLASH:
		  KeyState = GetAsyncKeyState(VK_OEM_5);
		  break;
	   case KeyEvent::KEY_APOSTROPHE:
		  KeyState = GetAsyncKeyState(VK_OEM_7);
		  break;
	   case KeyEvent::KEY_SLASH:
		  KeyState = GetAsyncKeyState(VK_OEM_2);
		  break;

	   //Non-visible
	   case KeyEvent::KEY_ESCAPE:
		  KeyState = GetAsyncKeyState(VK_ESCAPE);
		  break;
	   case KeyEvent::KEY_SHIFT:
		  KeyState = GetAsyncKeyState(VK_SHIFT);
		  break;
	   case KeyEvent::KEY_CONTROL:
		  KeyState = GetAsyncKeyState(VK_CONTROL);
		  break;
	   case KeyEvent::KEY_ALT:
		  KeyState = GetAsyncKeyState(VK_MENU);
		  break;
	   case KeyEvent::KEY_ENTER:
		  KeyState = GetAsyncKeyState(VK_RETURN);
		  break;
	   case KeyEvent::KEY_CANCEL:
		  KeyState = GetAsyncKeyState(VK_CANCEL);
		  break;
	   case KeyEvent::KEY_CLEAR:
		  KeyState = GetAsyncKeyState(VK_CLEAR);
		  break;
	   case KeyEvent::KEY_PAUSE:
		  KeyState = GetAsyncKeyState(VK_PAUSE);
		  break;
	   case KeyEvent::KEY_CAPS_LOCK:
		  KeyState = GetAsyncKeyState(VK_CAPITAL);
		  break;
	   case KeyEvent::KEY_END:
		  KeyState = GetAsyncKeyState(VK_END);
		  break;
	   case KeyEvent::KEY_PAGE_UP:
		  KeyState = GetAsyncKeyState(VK_PRIOR);
		  break;
	   case KeyEvent::KEY_PAGE_DOWN:
		  KeyState = GetAsyncKeyState(VK_NEXT);
		  break;
	   case KeyEvent::KEY_HOME:
		  KeyState = GetAsyncKeyState(VK_HOME);
		  break;
	   case KeyEvent::KEY_UP:
		  KeyState = GetAsyncKeyState(VK_UP);
		  break;
	   case KeyEvent::KEY_DOWN:
		  KeyState = GetAsyncKeyState(VK_DOWN);
		  break;
	   case KeyEvent::KEY_LEFT:
		  KeyState = GetAsyncKeyState(VK_LEFT);
		  break;
	   case KeyEvent::KEY_RIGHT:
		  KeyState = GetAsyncKeyState(VK_RIGHT);
		  break;
	   case KeyEvent::KEY_PRINTSCREEN:
		  KeyState = GetAsyncKeyState(VK_SNAPSHOT);
		  break;
	   case KeyEvent::KEY_INSERT:
		  KeyState = GetAsyncKeyState(VK_INSERT);
		  break;
	   case KeyEvent::KEY_DELETE:
		  KeyState = GetAsyncKeyState(VK_DELETE);
		  break;
	   case KeyEvent::KEY_HELP:
		  KeyState = GetAsyncKeyState(VK_HELP);
		  break;
	   case KeyEvent::KEY_NUM_LOCK:
		  KeyState = GetAsyncKeyState(VK_NUMLOCK);
		  break;
	   case KeyEvent::KEY_SCROLL_LOCK:
		  KeyState = GetAsyncKeyState(VK_SCROLL);
		  break;
	   case KeyEvent::KEY_BACK_SPACE:
		  KeyState = GetAsyncKeyState(VK_BACK);
		  break;

	   //Function Keys
	   case KeyEvent::KEY_F1:
		  KeyState = GetAsyncKeyState(VK_F1);
		  break;
	   case KeyEvent::KEY_F2:
		  KeyState = GetAsyncKeyState(VK_F2);
		  break;
	   case KeyEvent::KEY_F3:
		  KeyState = GetAsyncKeyState(VK_F3);
		  break;
	   case KeyEvent::KEY_F4:
		  KeyState = GetAsyncKeyState(VK_F4);
		  break;
	   case KeyEvent::KEY_F5:
		  KeyState = GetAsyncKeyState(VK_F5);
		  break;
	   case KeyEvent::KEY_F6:
		  KeyState = GetAsyncKeyState(VK_F6);
		  break;
	   case KeyEvent::KEY_F7:
          KeyState = GetAsyncKeyState(VK_F7);
		  break;
	   case KeyEvent::KEY_F8:
          KeyState = GetAsyncKeyState(VK_F8);
		  break;
	   case KeyEvent::KEY_F9:
          KeyState = GetAsyncKeyState(VK_F9);
		  break;
	   case KeyEvent::KEY_F10:
          KeyState = GetAsyncKeyState(VK_F10);
		  break;
	   case KeyEvent::KEY_F11:
          KeyState = GetAsyncKeyState(VK_F11);
		  break;
	   case KeyEvent::KEY_F12:
          KeyState = GetAsyncKeyState(VK_F12);
		  break;
	   case KeyEvent::KEY_F13:
          KeyState = GetAsyncKeyState(VK_F13);
		  break;
	   case KeyEvent::KEY_F14:
          KeyState = GetAsyncKeyState(VK_F14);
		  break;
	   case KeyEvent::KEY_F15:
          KeyState = GetAsyncKeyState(VK_F15);
		  break;
	   case KeyEvent::KEY_F16:
          KeyState = GetAsyncKeyState(VK_F16);
		  break;
	   case KeyEvent::KEY_F17:
          KeyState = GetAsyncKeyState(VK_F17);
		  break;
	   case KeyEvent::KEY_F18:
          KeyState = GetAsyncKeyState(VK_F18);
		  break;
	   case KeyEvent::KEY_F19:
          KeyState = GetAsyncKeyState(VK_F19);
		  break;
	   case KeyEvent::KEY_F20:
          KeyState = GetAsyncKeyState(VK_F20);
		  break;
	   case KeyEvent::KEY_F21:
          KeyState = GetAsyncKeyState(VK_F21);
		  break;
	   case KeyEvent::KEY_F22:
          KeyState = GetAsyncKeyState(VK_F22);
		  break;
	   case KeyEvent::KEY_F23:
          KeyState = GetAsyncKeyState(VK_F23);
		  break;
	   case KeyEvent::KEY_F24:
          KeyState = GetAsyncKeyState(VK_F24);
		  break;
	      
	   //Numpad Keys
	   case KeyEvent::KEY_NUMPAD_0:
          KeyState = GetAsyncKeyState(VK_NUMPAD0);
		  break;
	   case KeyEvent::KEY_NUMPAD_1:
          KeyState = GetAsyncKeyState(VK_NUMPAD1);
		  break;
	   case KeyEvent::KEY_NUMPAD_2:
          KeyState = GetAsyncKeyState(VK_NUMPAD2);
		  break;
	   case KeyEvent::KEY_NUMPAD_3:
          KeyState = GetAsyncKeyState(VK_NUMPAD3);
		  break;
	   case KeyEvent::KEY_NUMPAD_4:
          KeyState = GetAsyncKeyState(VK_NUMPAD4);
		  break;
	   case KeyEvent::KEY_NUMPAD_5:
          KeyState = GetAsyncKeyState(VK_NUMPAD5);
		  break;
	   case KeyEvent::KEY_NUMPAD_6:
          KeyState = GetAsyncKeyState(VK_NUMPAD6);
		  break;
	   case KeyEvent::KEY_NUMPAD_7:
          KeyState = GetAsyncKeyState(VK_NUMPAD7);
		  break;
	   case KeyEvent::KEY_NUMPAD_8:
          KeyState = GetAsyncKeyState(VK_NUMPAD8);
		  break;
	   case KeyEvent::KEY_NUMPAD_9:
          KeyState = GetAsyncKeyState(VK_NUMPAD9);
		  break;
	}
	if(KeyState != 0)
	{
		if(KeyState &0x0001)
		{
			return KeyEvent::KEY_STATE_TOGGLED;
		}
		else
		{
			return KeyEvent::KEY_STATE_DOWN;
		}
	}
	else
	{
		return KeyEvent::KEY_STATE_UP;
	}
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


Path Win32WindowEventProducer::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const std::string& InitialFile,
                const Path& InitialDirectory,
                bool PromptForOverwrite
                )
{
    char FilterString[400];
    UInt32 FilterSize(0);
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        for(UInt32 i(0) ; i<Itor->getName().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getName()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;
        for(UInt32 i(0) ; i<Itor->getFilter().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getFilter()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;
    }
    FilterString[FilterSize] = '\0';
    ++FilterSize;

	LPSTR WindowTitleLPC = _strdup(DialogTitle.c_str());
	LPSTR InitialDirLPC = _strdup(InitialDirectory.string().c_str());

    Path Result;
    OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
    szFile[0] = '\0'; 
     
	ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME); 
    ofn.hwndOwner = WIN32Window::Ptr::dcast(getWindow())->getHwnd(); 
    ofn.lpstrFilter = FilterString; 
    ofn.lpstrFile= szFile; 
    ofn.nMaxFile = sizeof(szFile)/ sizeof(*szFile); 
	ofn.lpstrTitle = WindowTitleLPC;
	ofn.lpstrInitialDir = InitialDirLPC;
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 


    char currentdir[200];
    GetCurrentDirectory(sizeof(currentdir),currentdir);
    if(GetSaveFileName(&ofn)==TRUE)
    {
        Result = Path(ofn.lpstrFile);
    }
    SetCurrentDirectory(currentdir);
    
	free(WindowTitleLPC);
	free(InitialDirLPC);

    return Result;
}

std::vector<Path> Win32WindowEventProducer::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect)
{
    char FilterString[400];
    UInt32 FilterSize(0);
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        for(UInt32 i(0) ; i<Itor->getName().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getName()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;
        FilterString[FilterSize] = '*';
        ++FilterSize;
        FilterString[FilterSize] = '.';
        ++FilterSize;
        for(UInt32 i(0) ; i<Itor->getFilter().size(); ++i)
        {
            FilterString[FilterSize] = Itor->getFilter()[i];
            ++FilterSize;
        }
        FilterString[FilterSize] = '\0';
        ++FilterSize;
    }
    FilterString[FilterSize] = '\0';
    ++FilterSize;

	LPSTR WindowTitleLPC = _strdup(WindowTitle.c_str());
	LPSTR InitialDirLPC = _strdup(InitialDir.string().c_str());

	std::vector<Path> Result;

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = WIN32Window::Ptr::dcast(getWindow())->getHwnd();
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = FilterString;
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = WindowTitleLPC;
	ofn.lpstrInitialDir = InitialDirLPC;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
    
    char currentdir[200];
    GetCurrentDirectory(sizeof(currentdir),currentdir);

    // GetOpenFileName stuffs


	if (GetOpenFileName(&ofn)==TRUE)
	{
        Result.push_back(Path(ofn.lpstrFile));
	}
	else
	{
	}
    SetCurrentDirectory(currentdir);

	free(WindowTitleLPC);
	free(InitialDirLPC);
	return Result;
}

Vec2f Win32WindowEventProducer::getDesktopSize(void) const
{
    DEVMODE dm;
    // initialize the DEVMODE structure
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
    {
        return Vec2f(dm.dmPelsWidth,dm.dmPelsHeight);
    }
    else
    {
        return Vec2f(0.0f,0.0f);
    }
}

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

WindowPtr Win32WindowEventProducer::initWindow(void)
{
	WindowPtr MyWindow = Inherited::initWindow();
    //Create the Win32 Window
    WNDCLASS  wndClass;
    HWND           hwnd;

    // Win32 Init
    memset(&wndClass, 0, sizeof(wndClass));
    
    std::string ClassName("OpenSG Window");
    wndClass.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wndClass.lpfnWndProc		= (WNDPROC) Win32WindowEventProducer::staticWndProc;				// WndProc Handles Messages
	wndClass.cbClsExtra		= 0;						// No Extra Window Data
	wndClass.cbWndExtra		= 0;						// No Extra Window Data
	wndClass.hInstance		= GetModuleHandle(NULL);					// Set The Instance
	wndClass.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	//wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wndClass.hbrBackground	= NULL;						// No Background Required For GL
	wndClass.lpszMenuName		= NULL;						// We Don't Want A Menu
	wndClass.lpszClassName	= ClassName.c_str();

    if (!RegisterClass(&wndClass)) 
    {
        MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
        return NullFC;
    }


    RECT WindowRect;							// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=0;						// Set Left Value To 0
	WindowRect.right=10;						// Set Right Value To Requested Width
	WindowRect.top=0;							// Set Top Value To 0
	WindowRect.bottom=20;						// Set Bottom Value To Requested Height

    //Fullscreen
    //bool fullscreen(_IsFullscreen);
    bool fullscreen(false);
    if(fullscreen)
    {
        DEVMODE dmScreenSettings;					// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		//dmScreenSettings.dmPelsWidth	= _Size.x();			// Selected Screen Width
		//dmScreenSettings.dmPelsHeight	= _Size.y();			// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;				// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

        // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
            // If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
                	fullscreen=FALSE;				// Select Windowed Mode (Fullscreen=FALSE)
			}
			else
			{
                // Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return NullFC;					// Exit And Return FALSE
			}
		}
	}

    DWORD		dwExStyle;						// Window Extended Style
	DWORD		dwStyle;						// Window Style

    if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
	    WindowRect.left=(long)0;						// Set Left Value To 0
	    WindowRect.top=(long)0;						// Set Top Value To 0
        dwExStyle=WS_EX_APPWINDOW;					// Window Extended Style
		dwStyle=WS_POPUP;						// Windows Style
        AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
	}
	else
	{
        dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}
    
    //ShowCursor(true);						// Show/Hide Mouse Pointer

    // Create a Window
    hwnd = CreateWindowEx(	dwExStyle,				// Extended Style For The Window
				ClassName.c_str(),				// Class Name
				"Temp",					// Window Title
				WS_CLIPSIBLINGS |			// Required Window Style
				WS_CLIPCHILDREN |			// Required Window Style
				dwStyle,				// Selected Window Style
				WindowRect.left, WindowRect.top,					// Window Position
				WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
				WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
				NULL,					// No Parent Window
				NULL,					// No Menu
				wndClass.hInstance,				// Instance
				NULL);					// Don't Pass Anything To WM_CREATE

    if(!hwnd)
    {
        DWORD LastError = GetLastError();
        MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
        return NullFC;
    }

    //Attach Window
    beginEditCP(getWindow(), WIN32Window::HwndFieldMask);
        WIN32Window::Ptr::dcast(getWindow())->setHwnd(hwnd);
    endEditCP(getWindow(), WIN32Window::HwndFieldMask);

    _IsFullscreen = fullscreen;

    return MyWindow;
}
void Win32WindowEventProducer::openWindow(const Pnt2f& ScreenPosition,
                    const Vec2f& Size,
                    const std::string& WindowName)
{

    attachWindow();
	
    if(_IsFullscreen)
    {
        //internalReshape(Vec2f(WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top));
    }

    getWindow()->init();
    getWindow()->deactivate();

    
    //Open the Window and enter the main event loop
    setPosition(ScreenPosition);
    setSize(Size);
    setTitle(WindowName);
	ShowWindow( WIN32Window::Ptr::dcast(getWindow())->getHwnd(), SW_SHOWNORMAL );
    SetForegroundWindow(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
    SetFocus(WIN32Window::Ptr::dcast(getWindow())->getHwnd());
	//SetActiveWindow( WIN32Window::Ptr::dcast(getWindow())->getHwnd() );
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

                Pnt2f Position(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                Vec2f MouseDelta(0.0f,0.0f);
                if(_PreviousCursorPos != Pnt2f(-1.0f,-1.0f))
                {
                    MouseDelta = Position - _PreviousCursorPos;
                }
                _PreviousCursorPos = Position;

                if(!_HandleNextMouseMove)
                {
                    _HandleNextMouseMove = true;
                    return 0;
                }
			    if(wParam & MK_LBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON1,Position, MouseDelta);
			    }
			    if(wParam & MK_MBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON2,Position, MouseDelta);
			    }
			    if(wParam & MK_RBUTTON)
			    {
				    produceMouseDragged(MouseEvent::BUTTON3,Position, MouseDelta);
			    }
			    produceMouseMoved(Position, MouseDelta);


                //If the Mouse has been disassociated from the cursor
                //then recenter the cursor in the window
                if(!_IsMouseCursorAssociated)
                {
                    _HandleNextMouseMove = false;
                    setCursorPos(getPosition() + (0.5f * getSize()));
                }
                
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
            _WIN32HWNDToProducerMap.erase(_WIN32HWNDToProducerMap.find(WIN32Window::Ptr::dcast(getWindow())->getHwnd()));
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

void Win32WindowEventProducer::setShowCursor(bool showCursor)
{
    while(getShowCursor() != showCursor)
    {
        ShowCursor(showCursor);
    }
}

bool Win32WindowEventProducer::getShowCursor(void) const
{
    CURSORINFO TheCursorInfo;
    TheCursorInfo.cbSize = sizeof(CURSORINFO);

    if(!GetCursorInfo(&TheCursorInfo))
    {
        SWARNING << "Win32WindowEventProducer::getShowCursor: Failed to get cursor info " << GetLastError() << std::endl;
    }
    return TheCursorInfo.flags == CURSOR_SHOWING;
}

void Win32WindowEventProducer::setAttachMouseToCursor(bool attachCursor)
{
    _IsMouseCursorAssociated = attachCursor;
}

bool Win32WindowEventProducer::getAttachMouseToCursor(void) const
{
    return _IsMouseCursorAssociated;
}

void Win32WindowEventProducer::setCursorPos(Vec2f Pos)
{
    if(!SetCursorPos(static_cast<int>(Pos.x()), static_cast<int>(Pos.y())))
    {
        SWARNING << "Win32WindowEventProducer::setCursorPos: Failed to set cursor position" << std::endl;
    }
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
   return static_cast<bool>(IsWindowVisible(WIN32Window::Ptr::dcast(getWindow())->getHwnd()));
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
   return static_cast<bool>(IsIconic(WIN32Window::Ptr::dcast(getWindow())->getHwnd()));
}

//Fullscreen
void Win32WindowEventProducer::setFullscreen(bool Fullscreen)
{
    //TODO: find a better way to do this
    if(Fullscreen && !getFullscreen())
    {
        _PreviousWindowPosition = getPosition();
        _PreviousWindowSize = getSize();
        //SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN),GetSystemMetrics(SM_CYFULLSCREEN),
        //    SWP_NOZORDER);
        _IsFullscreen = true;
    }
    else if(!Fullscreen && getFullscreen())
    {
        SetWindowPos(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),HWND_NOTOPMOST,
            static_cast<int>(_PreviousWindowPosition.x()),
            static_cast<int>(_PreviousWindowPosition.y()),
            static_cast<int>(_PreviousWindowSize.x()),
            static_cast<int>(_PreviousWindowSize.y()),
            SWP_NOZORDER);
        _IsFullscreen = false;
    }
}

//Get the Window Fullscreen
bool Win32WindowEventProducer::getFullscreen(void) const
{
    return _IsFullscreen;
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
        _MouseOverWindow(false),
        _IsFullscreen(false),
        _IsMouseCursorAssociated(true),
        _HandleNextMouseMove(true),
        _PreviousCursorPos(-1.0,-1.0)
{
}

Win32WindowEventProducer::Win32WindowEventProducer(const Win32WindowEventProducer &source) :
    Inherited(source),
        _MouseOverWindow(false),
        _IsFullscreen(false),
        _IsMouseCursorAssociated(true),
        _HandleNextMouseMove(true),
        _PreviousCursorPos(-1.0,-1.0)
{
}

Win32WindowEventProducer::~Win32WindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

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

