#include "OSGWindowUtils.h"

#ifdef __APPLE__
#include <OpenSG/OSGCarbonWindow.h>
#include <OpenSG/OSGCocoaWindow.h>
#include <OpenSG/OSGCoreGLWindow.h>
#endif

#ifdef WIN32
#include <OpenSG/OSGWIN32Window.h>
#include <windows.h>
#include "WindowSystem/Win32/OSGWin32WindowEventProducer.h"
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
    // Create Windows
    ResultWindow = WIN32Window::create();
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
      ResultWindow = GLUTWindow::create();
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
      return;
   }

#if defined(__APPLE__)
#elif defined(WIN32)
   if(WindowType == WIN32Window::getClassType())
   {
      WNDCLASS  wndClass;
      HWND           hwnd;

      // Win32 Init
      memset(&wndClass, 0, sizeof(wndClass));
      wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
      wndClass.lpfnWndProc = Win32WindowEventProducer::staticWndProc;
      wndClass.hInstance = GetModuleHandle(NULL);
      // doesn't compile?!? wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
      wndClass.lpszClassName = WindowName.c_str();
      if (!RegisterClass(&wndClass)) 
      {
         return;
      }


      // Create a Window
      hwnd = CreateWindow( WindowName.c_str(), WindowName.c_str(),
                     WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                     ScreenPosition.x(), 
                     ScreenPosition.y(), 
                     Size.x(), 
                     Size.y(),
                     NULL, 
                     NULL, 
                     GetModuleHandle(NULL), 
                     0 );

      //Attach Window
      beginEditCP(WIN32Window::Ptr::dcast(ResultWindow), WIN32Window::HwndFieldMask);
         WIN32Window::Ptr::dcast(ResultWindow)->setHwnd(hwnd);
      endEditCP(WIN32Window::Ptr::dcast(ResultWindow), WIN32Window::HwndFieldMask);

      ResultWindowEventProducer->attachWindow(ResultWindow);
            
      ResultWindow->init();
      ResultWindow->deactivate();
   }
#elif defined(__linux)
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

      GLUTWindow::Ptr::dcast(ResultWindow)->setId(winid);
      ResultWindowEventProducer->attachWindow(ResultWindow);
   }
#endif
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
