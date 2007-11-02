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

//#include <CarbonEvents.h>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CarbonWindowEventProducer
CarbonWindowEventProducer Class.  
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CarbonWindowEventProducer::CarbonWindowToProducerMap CarbonWindowEventProducer::_CarbonWindowToProducerMap;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindowEventProducer::initMethod (void)
{
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
    SetRect(&contentRect, Arguments->_ScreenPosition.x(),  Arguments->_ScreenPosition.y(), Arguments->_Size.x(), Arguments->_Size.y());
    
    CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, &window);
    SetWindowTitleWithCFString(window, CFStringCreateWithCString(NULL, Arguments->_WindowName.c_str(), Arguments->_WindowName.size()));

    // Install event handler
    EventHandlerUPP eventHandlerUPP = NewEventHandlerUPP(eventHandler);
    EventTypeSpec eventList[] =
    {
        { kEventClassTextInput, kEventTextInputUnicodeForKeyEvent },
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseMoved },
        { kEventClassMouse, kEventMouseDragged },
        //{ kEventClassWindow, kEventWindowActivate },
        //{ kEventClassWindow, kEventWindowDeactivate },
        { kEventClassWindow, kEventWindowClose },
        { kEventClassWindow, kEventWindowDrawContent },
        { kEventClassWindow, kEventWindowBoundsChanged }
    };
    
    Arguments->_EventProducer->_WindowId = getUndefinedWindowId();
    Arguments->_EventProducer->attachWindow();
    
    InstallWindowEventHandler(window, eventHandlerUPP, GetEventTypeCount(eventList), eventList, &(Arguments->_EventProducer->_WindowId), 0);

    // Initialize OpenGL
    GLint attribs[] = { AGL_RGBA, AGL_DOUBLEBUFFER, AGL_DEPTH_SIZE, 16, AGL_NONE };
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

        
    Arguments->_EventProducer->getWindow()->resize( Arguments->_Size.x(), Arguments->_Size.y() );
    Arguments->_EventProducer->getWindow()->init();
    Arguments->_EventProducer->getWindow()->deactivate();
    
    // Show window
    RepositionWindow(window, 0, kWindowCascadeOnMainScreen);
    ShowWindow(window);
    
    // Main loop ( event dispatching )
    RunApplicationEventLoop();
    
    Arguments->_EventProducer->produceWindowClosed();
    
    //Delete my arguments, to avoid memory leak
    delete Arguments;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSStatus CarbonWindowEventProducer::internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    std::cout << "internalEventHandler" << std::endl;
    ::UInt32 eventClass = GetEventClass(event);
    /*switch (eventClass)
    {
    // Mouse events
    case kEventClassMouse:
        return handleMouseEvent(nextHandler, event, userData);

    // Key press events
    case kEventClassTextInput:
        return handleKeyEvent(nextHandler, event, userData);

    // Window events
    case kEventClassWindow:
        return handleWindowEvent(nextHandler, event, userData);

    default:
        return eventNotHandledErr;
    }*/
            _DisplayCallbackFunc();
    return noErr;
}

void CarbonWindowEventProducer::setPosition(Pnt2s Pos)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

Pnt2s CarbonWindowEventProducer::getPosition(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return Pnt2s();
}


void CarbonWindowEventProducer::setSize(Vec2us Size)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

Vec2s CarbonWindowEventProducer::getSize(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return Vec2s();
}

void CarbonWindowEventProducer::setFocused(bool Focused)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getFocused(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setVisible(bool Visible)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getVisible(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setIconify(bool Iconify)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getIconify(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setFullscreen(bool Fullscreen)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getFullscreen(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setTitle(const std::string& TitleText)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

std::string CarbonWindowEventProducer::getTitle(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return std::string("");
}

void CarbonWindowEventProducer::setRisizable(bool IsResizable)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getRisizable(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
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
    //SendMessage(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),WIN32_DRAW_MESSAGE,0,0);
}

void CarbonWindowEventProducer::update(void)
{
    //TODO: Implement
    //SendMessage(WIN32Window::Ptr::dcast(getWindow())->getHwnd(),WIN32_UPDATE_MESSAGE,0,0);
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
    //TODO: Implement
    assert(false && "Not Implemented");
    return 0;
}

Pnt2s CarbonWindowEventProducer::getMousePosition(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return Pnt2s();
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

void CarbonWindowEventProducer::openWindow(const Pnt2s& ScreenPosition,
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
                    CarbonWindow::Ptr::dcast(getWindow()),
                    CarbonWindowEventProducerPtr(this)  );
    
    //ChangeList::setReadWriteDefault();
    _WindowEventLoopThread->runFunction(WindowEventLoopThread, 0, static_cast<void*>(Arguments));
}

void CarbonWindowEventProducer::closeWindow(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

void CarbonWindowEventProducer::setCursor(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
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
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
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

