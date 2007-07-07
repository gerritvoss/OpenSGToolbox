#include "OSGWindowUtils.h"

#ifdef __APPLE__
#include <OpenSG/OSGCarbonWindow.h>
#include <OpenSG/OSGCocoaWindow.h>
#include <OpenSG/OSGCoreGLWindow.h>
#endif

#ifdef WIN32
#include <OpenSG/OSGWIN32Window.h>
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

OSG_BEGIN_NAMESPACE

WindowPtr createWindow(FieldContainerType WindowType,
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName)
{
#if defined(__APPLE__)
   if(WindowType == CocoaWindow::getClassType())
   {
      return NullFC;
   }
   else if(WindowType == CarbonWindow::getClassType())
   {
      return NullFC;
   }
   else if(WindowType == CoreGLWindow::getClassType())
   {
      return NullFC;
   }
#elif defined(WIN32)
   if(WindowType == WIN32Window::getClassType())
   {
      return NullFC;
   }
#elif defined(__linux)
   if(WindowType == XWindow::getClassType())
   {
      return NullFC;
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
      
      GLUTWindowPtr gwin= GLUTWindow::create();
      gwin->setId(winid);

      return gwin;
   }
#endif
   else
   {
      return NullFC;
   }
}

WindowPtr createDefaultWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName)
{
#if defined(__APPLE__)
   return createWindow(CocoaWindow::getClassType(), ScreenPosition, Size, WindowName);
#elif defined(WIN32)
   return createWindow(WIN32Window::getClassType(), ScreenPosition, Size, WindowName);
#elif defined(__linux)
   return createWindow(XWindow::getClassType(), ScreenPosition, Size, WindowName);
#endif
}

void openWindow(WindowPtr TheWindow)
{
#ifdef OSG_WITH_GLUT
   if(TheWindow->getType() == GLUTWindow::getClassType())
   {
      //Get the GLUT window ID
      Int32 winid = GLUTWindow::Ptr::dcast(TheWindow)->getId();

      //Set the current window to this one
      glutSetWindow(winid);

      // GLUT main loop
      glutMainLoop();
   }
#endif
}

OSG_END_NAMESPACE