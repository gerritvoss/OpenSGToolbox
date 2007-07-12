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
#include "OSGWindowEventProducerFactory.h"

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
      //return NullFC;
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
      ResultWindow->init();
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
#ifdef OSG_WITH_GLUT
   if(TheWindowEventProducer->getWindow()->getType() == GLUTWindow::getClassType())
   {
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