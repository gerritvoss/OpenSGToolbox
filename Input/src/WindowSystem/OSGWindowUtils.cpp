#include "OSGWindowUtils.h"

#ifdef __APPLE__
#include <OpenSG/OSGCarbonWindow.h>
#include <OpenSG/OSGCocoaWindow.h>
#include <OpenSG/OSGCoreGLWindow.h>
#endif

#ifdef WIN32
#include <OpenSG/OSGWIN32Window.h>
#include <windows.h>
#endif

#ifdef __linux
#include <OpenSG/OSGXWindow.h>
#endif

#ifdef OSG_WITH_GLUT
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGLUT.h>
#endif

//#include <OpenSG/OSGQTWindow.h>
//#include <OpenSG/OSGQT4Window.h>
#include "OSGWindowEventProducerFactory.h"

LRESULT CALLBACK WndProc(HWND hwnd2, UINT uMsg,
                         WPARAM wParam, LPARAM lParam);
OSG_BEGIN_NAMESPACE

void createWindow(FieldContainerType WindowType,
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       WindowPtr& ResultWindow,
                       WindowEventProducerPtr& ResultWindowEventProducer)
{
#if defined(__APPLE__)
   if(WindowType == CocoaWindow::getClassType())
   {
      //return NullFC;
   }
   else if(WindowType == CarbonWindow::getClassType())
   {
      //return NullFC;
   }
   else if(WindowType == CoreGLWindow::getClassType())
   {
      //return NullFC;
   }
#elif defined(WIN32)
   if(WindowType == WIN32Window::getClassType())
   {
    WNDCLASS  wndClass;
	HWND           hwnd;
	
    // Win32 Init

    memset(&wndClass, 0, sizeof(wndClass));
    wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    // doesn't compile?!? wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszClassName = WindowName.c_str();
    if (!RegisterClass(&wndClass)) 
    {
        return;
    }

    
    // Create Windows
    ResultWindow = WIN32Window::create();
    
    // Create a Window
    hwnd = CreateWindow( WindowName.c_str(), WindowName.c_str(),
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                    CW_USEDEFAULT, 
                    0, 
                    CW_USEDEFAULT, 
                    0,
                    NULL, 
                    NULL, 
                    GetModuleHandle(NULL), 
                    0 );

	beginEditCP(WIN32Window::Ptr::dcast(ResultWindow), WIN32Window::HwndFieldMask);
		WIN32Window::Ptr::dcast(ResultWindow)->setHwnd(hwnd);
		//WIN32Window::Ptr::dcast(ResultWindow)->setHdc();
		//WIN32Window::Ptr::dcast(ResultWindow)->setHglrc();
	endEditCP(WIN32Window::Ptr::dcast(ResultWindow), WIN32Window::HwndFieldMask);


   }
#elif defined(__linux)
   if(WindowType == XWindow::getClassType())
   {
      //return NullFC;
   }
#endif

#ifdef OSG_WITH_GLUT
   else if(WindowType == GLUTWindow::getClassType())
   {
      int argc(1);
      char **argv = new char*[1];
      (*argv)= "Bla";
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
      Int32 winid = glutCreateWindow(WindowName.c_str());
      glutPositionWindow(ScreenPosition.x(), ScreenPosition.y());
      glutReshapeWindow(Size.x(), Size.y());
      
      ResultWindow = GLUTWindow::create();
      GLUTWindow::Ptr::dcast(ResultWindow)->setId(winid);
   }
#endif
   else
   {
      ResultWindow = NullFC;
   }

   //Create the WindowEventProducer
   if(ResultWindow != NullFC)
   {
      ResultWindowEventProducer = WindowEventProducerFactory::the()->createWindowEventProducer(ResultWindow);
   }
   else
   {
      ResultWindowEventProducer = NullFC;
   }
}

void createDefaultWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       WindowPtr& ResultWindow,
                       WindowEventProducerPtr& ResultWindowEventProducer)
{
#if defined(__APPLE__)
   createWindow(CocoaWindow::getClassType(), ScreenPosition, Size, WindowName, ResultWindow, ResultWindowEventProducer);
#elif defined(WIN32)
   createWindow(WIN32Window::getClassType(), ScreenPosition, Size, WindowName, ResultWindow, ResultWindowEventProducer);
#elif defined(__linux)
   createWindow(XWindow::getClassType(), ScreenPosition, Size, WindowName, ResultWindow, ResultWindowEventProducer);
#endif
}

void openWindow(WindowEventProducerPtr TheWindowEventProducer)
{
#if defined(__APPLE__)
#elif defined(WIN32)
	if(TheWindowEventProducer->getWindow()->getType() == WIN32Window::getClassType())
	{
		ShowWindow( WIN32Window::Ptr::dcast(TheWindowEventProducer->getWindow())->getHwnd(), SW_SHOWNORMAL );
		SetActiveWindow( WIN32Window::Ptr::dcast(TheWindowEventProducer->getWindow())->getHwnd() );
		
        MSG           msg;
		// main loop 
		while ( GetMessage(&msg, NULL, 0, 0) )
		{
			DispatchMessage(&msg);
		}
	}
#elif defined(__linux)
#endif

#if defined OSG_WITH_GLUT
   else if(TheWindowEventProducer->getWindow()->getType() == GLUTWindow::getClassType())
   {
      TheWindowEventProducer->getWindow()->init();

      //Get the GLUT window ID
      Int32 winid = GLUTWindow::Ptr::dcast(TheWindowEventProducer->getWindow())->getId();

      //Set the current window to this one
      glutSetWindow(winid);

      // GLUT main loop
      glutMainLoop();
   }
#endif
}

OSG_END_NAMESPACE


LRESULT CALLBACK WndProc(HWND hwnd2, UINT uMsg,
                         WPARAM wParam, LPARAM lParam)
{
    int  eventThread = 0, x, y;

    PIXELFORMATDESCRIPTOR   pfd;    
    HDC           hDC;

    int iPixelFormat;

    switch(uMsg)
    {       
        /*case WM_LBUTTONDOWN:
            mouseb |= 1 << 1;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_MBUTTONDOWN:
            tball.setAutoPosition(true);
            mouseb |= 1 << 2;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONDOWN:
            tball.setAutoPositionNeg(true);     
            mouseb |= 1 << 3;
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;   
        case WM_LBUTTONUP:
            mouseb &= ~(1 << 1);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;              
        case WM_MBUTTONUP:
            tball.setAutoPositionNeg(false); 
            mouseb &= ~(1 << 2);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONUP:
            tball.setAutoPositionNeg(false); 
            mouseb &= ~(1 << 3);
            lastx = (int)LOWORD(lParam);
            lasty = (int)HIWORD(lParam);
            break;

        case WM_MOUSEMOVE:
            {
            Real32 w,h,a,b,c,d;
            
            x = (int)LOWORD(lParam);
            y = (int)HIWORD(lParam);
            w = win->getWidth();
            h = win->getHeight();
    
            a = -2.f * ( lastx / w - .5f );
            b = -2.f * ( .5f - lasty / h );
            c = -2.f * ( x / w - .5f );
            d = -2.f * ( .5f - y / h );
                    
            if ( mouseb & ( 1 << 1 ) )
            {
                //dpr << "Left button dragged" << std::endl;
                tball.updateRotation( a, b, c, d );
                //display();
            }
            else if ( mouseb & ( 1 << 2 ) )
            {
                //dpr << "Middle button dragged" << std::endl;
                tball.updatePosition( a, b, c, d );
                //display();
            }
            else if ( mouseb & ( 1 << 3 ) )
            {
                //dpr << "Right button dragged" << std::endl;
                tball.updatePositionNeg( a, b, c, d );
                //display();
            }
            }
            lastx = x;
            lasty = y;
            break;
                                    
        case WM_KEYDOWN:
            dpr << "Key pressed: " << wParam << std::endl;
            if ( (int)wParam == VK_ESCAPE )
            {
                exit(0);
            }
            break;*/
                                    
        case WM_SIZE:
            //dpr << "Resize: " << wParam << " " << LOWORD(lParam)
            //    << " " << HIWORD( lParam ) << std::endl;
			//std::cout << "Resize: " << wParam << " " << LOWORD(lParam)
            //    << " " << HIWORD( lParam ) << std::endl;
            //if ( win != NullFC)
            //    win->resize( LOWORD(lParam), HIWORD( lParam ) );
            break;
                                    
        case WM_PAINT:
            //if ( win != NullFC)
            //    display();
            break;

        case WM_CREATE:
			std::cout << "Bla" << std::endl;
            /*dpr << "Create " << std::endl;

            memset(&pfd, 0, sizeof(pfd));
            pfd.nSize = sizeof(pfd);
            pfd.nVersion = 1;
            pfd.dwFlags = 
                PFD_DRAW_TO_WINDOW | 
                PFD_SUPPORT_OPENGL | 
                PFD_DOUBLEBUFFER;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.iLayerType = PFD_MAIN_PLANE;
            pfd.cDepthBits = 16;            



            // init the OSG window  
            hDC = GetDC(hwnd2);

            iPixelFormat = ChoosePixelFormat(hDC, &pfd);
            SetPixelFormat(hDC, iPixelFormat, &pfd);    
            
            beginEditCP(win);
               win->setHwnd ( hwnd2 );
               //win->setHdc ( hDC ); // This is done in the init() function of WindowWIN32
               //win->setHglrc (  ); // This is done in the init() function of WindowWIN32
            endEditCP(win);
            
            win->init();
            win->deactivate();*/
            break;

        case WM_CLOSE:
            //return DefWindowProc(hwnd2,uMsg,wParam,lParam);
            break;

        case WM_DESTROY:
            //PostQuitMessage(0);
            break;

        default:
            //return DefWindowProc(hwnd2, uMsg, wParam, lParam);
			break;
    }
    return 0;
}
