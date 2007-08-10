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
#include "WindowSystem/X/OSGXWindowEventProducer.h"
#include <GL/glx.h>
#endif

#ifdef OSG_WITH_GLUT
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGLUT.h>
#include "WindowSystem/GLUT/OSGGLUTWindowEventProducer.h"
#endif

//#include <OpenSG/OSGQTWindow.h>
//#include <OpenSG/OSGQT4Window.h>
#include "OSGWindowEventProducerFactory.h"

OSG_BEGIN_NAMESPACE

/*#if defined(__linux)
int wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}
#endif

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
   }
#elif defined(__linux)
   if(WindowType == XWindow::getClassType())
   {
	   WindowEventProducerFactory::the()->registerProducer(&XWindow::getClassType(), &XWindowEventProducer::getClassType());
      ResultWindow = XWindow::create();
   }
#endif

#ifdef OSG_WITH_GLUT
   else if(WindowType == GLUTWindow::getClassType())
   {
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
#elif defined(__linux)
    if(WindowType == XWindow::getClassType())
    {
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
        int VisualAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
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
                         Button1MotionMask |
                         Button2MotionMask |
                         Button3MotionMask | 
                         StructureNotifyMask;

        // Create Window

        // Create a Window and connect it to the main display dpy
        hwin = XCreateWindow( dpy, 
                              RootWindow(dpy, vi->screen), 
                              0, 0, 300, 300, 
                              0, 
                              vi->depth,
                              InputOutput, 
                              vi->visual, 
                              CWBorderPixel | CWColormap | CWEventMask, 
                              &swa );

        int argc(1);
        char **argv = new char*[1];
        (*argv)= "Bla";
         XSetStandardProperties(dpy, hwin, WindowName.c_str(), WindowName.c_str(), None, argv, argc, NULL);
                  
        beginEditCP(XWindow::Ptr::dcast(ResultWindow), XWindow::DisplayFieldMask | XWindow::WindowFieldMask);
            XWindow::Ptr::dcast(ResultWindow)->setDisplay ( dpy );
            XWindow::Ptr::dcast(ResultWindow)->setWindow ( hwin );
        endEditCP(XWindow::Ptr::dcast(ResultWindow), XWindow::DisplayFieldMask | XWindow::WindowFieldMask);
        
        ResultWindowEventProducer->attachWindow(ResultWindow);
        
        ResultWindow->init();
        
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
}*/

WindowEventProducerPtr createDefaultWindowEventProducer(void)
{
#if defined(__APPLE__)
    return NullFC;
#elif defined(WIN32)
    return Win32WindowEventProducer::create();
#elif defined(__linux)
    return XWindowEventProducer::create();
#endif
}

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createWindowEventProducer(const FieldContainerType WindowType)
{
#if defined(__APPLE__)
    if(WindowType == CarbonWindow::getClassType())
    {
        return CarbonWindowEventProducer::create();
    }
#elif defined(WIN32)
    if(WindowType == WIN32Window::getClassType())
    {
        return Win32WindowEventProducer::create();
    }
#elif defined(__linux)
    if(WindowType == XWindow::getClassType())
    {
        return XWindowEventProducer::create();
    }
#endif
#if defined(OSG_WITH_GLUT)
    else if(WindowType == GLUTWindow::getClassType())
    {
        return GLUTWindowEventProducer::create();
    }
#endif
    return NullFC;
}

/*void openWindow(WindowEventProducerPtr TheWindowEventProducer)
{
#if defined(__APPLE__)
#elif defined(__linux)
   if(TheWindowEventProducer->getWindow()->getType() == XWindow::getClassType())
   {
        XMapWindow(XWindow::Ptr::dcast(TheWindowEventProducer->getWindow())->getDisplay(),
                XWindow::Ptr::dcast(TheWindowEventProducer->getWindow())->getWindow());
        XEvent event;
        XIfEvent(XWindow::Ptr::dcast(TheWindowEventProducer->getWindow())->getDisplay(), &event, wait_for_map_notify, (char *)(XWindow::Ptr::dcast(TheWindowEventProducer->getWindow())->getWindow()));
        
        TheWindowEventProducer->getWindow()->activate();
        
        bool stopIt = false;
        while ( !stopIt ) 
        {
           XWindowEventProducer::Ptr::dcast(TheWindowEventProducer)->handleEvents();
        }
   }
#endif
}*/

OSG_END_NAMESPACE
