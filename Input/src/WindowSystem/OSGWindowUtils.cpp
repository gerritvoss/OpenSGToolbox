#include "OSGWindowUtils.h"

#ifdef darwin
//#include <OpenSG/OSGCocoaWindow.h>
//#include <OpenSG/OSGCoreGLWindow.h>
#include "WindowSystem/Carbon/OSGCarbonWindowEventProducer.h"
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

WindowEventProducerPtr createDefaultWindowEventProducer(void)
{
#if defined(__APPLE__)
    return CarbonWindowEventProducer::create();
#elif defined(WIN32)
    return Win32WindowEventProducer::create();
#elif defined(__linux)
    return XWindowEventProducer::create();
#endif
}

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createWindowEventProducer(const FieldContainerType WindowType)
{
#if defined(darwin)
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

OSG_END_NAMESPACE
