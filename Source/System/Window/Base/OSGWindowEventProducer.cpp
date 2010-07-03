/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGWindowEventProducer.h"


#include "OSGTime.h"
#include "OSGBaseFunctions.h"
#include "OSGViewport.h"

#include "OSGWindow.h"
#include "OSGEventFields.h"
#include "OSGInputSettings.h"
#include <boost/bind.hpp>
OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGWindowEventProducerBase.cpp file.
// To modify it, please change the .fcd file (OSGWindowEventProducer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowEventProducer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void WindowEventProducer::updateCursor(Pnt2f MousePos)
{
	CursorRegionListItor ListItor;
	bool CursorChanged(false);
	for(ListItor = _CursorRegions.begin() ; ListItor != _CursorRegions.end() ; ++ListItor)
	{
		if(MousePos.x() >= ListItor->_TopLeft.x() &&
		   MousePos.y() >= ListItor->_TopLeft.y() &&
		   MousePos.x() <= ListItor->_BottomRight.x() &&
		   MousePos.y() <= ListItor->_TopLeft.y())
		{
			setCursorType(ListItor->_CursorType);
			CursorChanged = true;
		}
	}
	if(!CursorChanged)
	{
		setCursorType(CURSOR_POINTER);
	}
}

WindowEventProducer::CursorRegionListItor WindowEventProducer::addCursorRegion(const CursorRegion& r)
{
	_CursorRegions.push_back(r);
	return --(_CursorRegions.end());
}

void WindowEventProducer::setCursorType(UInt32 Type)
{
    if(!getLockCursor())
    {
	    _CursorType = Type;
        setCursor();
    }
}

bool WindowEventProducer::removeCursorRegion(CursorRegionListItor RegionItor)
{
	if(RegionItor != _CursorRegions.end())
	{
		_CursorRegions.erase(RegionItor);
		return true;
	}
	else
	{
		return false;
	}
}

WindowUnrecPtr WindowEventProducer::initWindow(void)
{
    //TODO
	_RenderAction = RenderAction::create();

    return WindowUnrecPtr(this);
}

void WindowEventProducer::setDisplayCallback(DisplayCallbackFunc Callback)
{
   _DisplayCallbackFunc = Callback;
}

void WindowEventProducer::setReshapeCallback(ReshapeCallbackFunc Callback)
{
   _ReshapeCallbackFunc = Callback;
}

EventConnection WindowEventProducer::addUpdateListener(UpdateListenerPtr Listener)
{
   _UpdateListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isUpdateListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeUpdateListener, this, Listener));
}

EventConnection WindowEventProducer::addMouseListener(MouseListenerPtr Listener)
{
   _MouseListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isMouseListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeMouseListener, this, Listener));
}

EventConnection WindowEventProducer::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
   _MouseMotionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isMouseMotionListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeMouseMotionListener, this, Listener));
}

EventConnection WindowEventProducer::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
   _MouseWheelListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isMouseWheelListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeMouseWheelListener, this, Listener));
}

EventConnection WindowEventProducer::addKeyListener(KeyListenerPtr Listener)
{
   _KeyListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isKeyListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeKeyListener, this, Listener));
}

EventConnection WindowEventProducer::addWindowListener(WindowListenerPtr Listener)
{
   _WindowListeners.insert(Listener);
   return EventConnection(
       boost::bind(&WindowEventProducer::isWindowListenerAttached, this, Listener),
       boost::bind(&WindowEventProducer::removeWindowListener, this, Listener));
}

void WindowEventProducer::removeMouseListener(MouseListenerPtr Listener)
{
   MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
   if(EraseIter != _MouseListeners.end())
   {
      _MouseListeners.erase(EraseIter);
   }
}

void WindowEventProducer::removeUpdateListener(UpdateListenerPtr Listener)
{
   UpdateListenerSetItor EraseIter(_UpdateListeners.find(Listener));
   if(EraseIter != _UpdateListeners.end())
   {
      _UpdateListeners.erase(EraseIter);
   }
}

void WindowEventProducer::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
   MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
   if(EraseIter != _MouseMotionListeners.end())
   {
      _MouseMotionListeners.erase(EraseIter);
   }
}

void WindowEventProducer::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
   MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
   if(EraseIter != _MouseWheelListeners.end())
   {
      _MouseWheelListeners.erase(EraseIter);
   }
}

void WindowEventProducer::removeKeyListener(KeyListenerPtr Listener)
{
   KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
   if(EraseIter != _KeyListeners.end())
   {
      _KeyListeners.erase(EraseIter);
   }
}

void WindowEventProducer::removeWindowListener(WindowListenerPtr Listener)
{
   WindowListenerSetItor EraseIter(_WindowListeners.find(Listener));
   if(EraseIter != _WindowListeners.end())
   {
      _WindowListeners.erase(EraseIter);
   }
}

ViewportUnrecPtr WindowEventProducer::windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint)
{
	ViewportUnrecPtr ThePort;
	for(UInt32 i(0) ; i<getMFPort()->size() ; ++i)
	{
		ThePort = getPort(i);
        ViewportPoint.setValues(WindowPoint.x() - ThePort->getPixelLeft(), WindowPoint.y() - ThePort->getPixelBottom());
		
        return ThePort;
		
	}
	return NULL;
}

void WindowEventProducer::detatchAllListeners(void)
{
    _MouseListeners.clear();
    _MouseMotionListeners.clear();
    _MouseWheelListeners.clear();
    _KeyListeners.clear();
    _WindowListeners.clear();
}

void WindowEventProducer::produceMouseClicked(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Time t(getSystemTime());
   updateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
           //If the event is consumed then stop sending the event
           if(TheEvent->isConsumed()) break;

		  (*SetItor)->mouseClicked(TheEvent);
	   }
       _Producer.produceEvent(MouseClickedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMouseEntered(const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport );
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

		   (*SetItor)->mouseEntered(TheEvent);
	   }
       _Producer.produceEvent(MouseEnteredMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMouseExited(const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport );
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

			(*SetItor)->mouseExited(TheEvent);
	   }
       _Producer.produceEvent(MouseExitedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMousePressed(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

	_ButtonClickMap[Button] = Location;
	TimeStamp t(getSystemTime());
	validateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

		    (*SetItor)->mousePressed(TheEvent);
	   }
       _Producer.produceEvent(MousePressedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMouseReleased(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

	TimeStamp t(getSystemTime());
	validateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

		    (*SetItor)->mouseReleased(TheEvent);
	   }
       _Producer.produceEvent(MouseReleasedMethodId,TheEvent);
   }
   if(_ButtonClickMap[Button] == Location)
   {
	   produceMouseClicked(Button, Location);
   }
}


void WindowEventProducer::produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2f& Location, const MouseWheelEvent::ScrollType& TheScrollType)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseWheelEventUnrecPtr TheEvent = MouseWheelEvent::create( WindowUnrecPtr(this), getSystemTime(), WheelRotation, TheScrollType,MouseWheelEvent::SCROLL_ORIENTATION_VERTICAL, ViewportLocation, ResultViewport );
	   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
	   {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

		    (*SetItor)->mouseWheelMoved(TheEvent);
	   }
       _Producer.produceEvent(MouseWheelMovedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMouseMoved(const Pnt2f& Location, const Vec2f& Delta)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport,Delta );
       for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
	   {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

			(*SetItor)->mouseMoved(TheEvent);
	   }
       _Producer.produceEvent(MouseMovedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceMouseDragged(const MouseEvent::MouseButton& Button, const Pnt2f& Location, const Vec2f& Delta)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseEventUnrecPtr TheEvent = MouseEvent::create(WindowUnrecPtr(this), getSystemTime(), Button, 0, ViewportLocation, ResultViewport,Delta );
       for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
	   {
            //If the event is consumed then stop sending the event
            if(TheEvent->isConsumed()) break;

			(*SetItor)->mouseDragged(TheEvent);
	   }
       _Producer.produceEvent(MouseDraggedMethodId,TheEvent);
   }
}

void WindowEventProducer::produceKeyPressed(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   const KeyEventUnrecPtr TheEvent = KeyEvent::create( WindowUnrecPtr(this), getSystemTime(), TheKey, Modifiers, WindowUnrecPtr(this) );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
        //If the event is consumed then stop sending the event
        if(TheEvent->isConsumed()) break;

		(*SetItor)->keyPressed(TheEvent);
   }
   _Producer.produceEvent(KeyPressedMethodId,TheEvent);
   produceKeyTyped(TheKey, Modifiers);
}

void WindowEventProducer::produceKeyReleased(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   const KeyEventUnrecPtr TheEvent = KeyEvent::create( WindowUnrecPtr(this), getSystemTime(), TheKey, Modifiers, WindowUnrecPtr(this) );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
        //If the event is consumed then stop sending the event
        if(TheEvent->isConsumed()) break;

		(*SetItor)->keyReleased(TheEvent);
   }
   _Producer.produceEvent(KeyReleasedMethodId,TheEvent);
}

void WindowEventProducer::produceKeyTyped(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   const KeyEventUnrecPtr TheEvent = KeyEvent::create( WindowUnrecPtr(this), getSystemTime(), TheKey, Modifiers, WindowUnrecPtr(this) );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
        //If the event is consumed then stop sending the event
        if(TheEvent->isConsumed()) break;

		(*SetItor)->keyTyped(TheEvent);
   }
   _Producer.produceEvent(KeyTypedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowOpened(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowOpened(TheEvent);
   }
   _Producer.produceEvent(WindowOpenedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowClosing(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosing(TheEvent);
   }
   _Producer.produceEvent(WindowClosingMethodId,TheEvent);
}

void WindowEventProducer::produceWindowClosed(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosed(TheEvent);
   }
   _Producer.produceEvent(WindowClosedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowIconified(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowIconified(TheEvent);
   }
   _Producer.produceEvent(WindowIconifiedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowDeiconified(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeiconified(TheEvent);
   }
   _Producer.produceEvent(WindowDeiconifiedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowActivated(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowActivated(TheEvent);
   }
   _Producer.produceEvent(WindowActivatedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowDeactivated(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeactivated(TheEvent);
   }
   _Producer.produceEvent(WindowDeactivatedMethodId,TheEvent);
}

void WindowEventProducer::produceWindowEntered(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowEntered(TheEvent);
   }
   _Producer.produceEvent(WindowEnteredMethodId,TheEvent);
}

void WindowEventProducer::produceWindowExited(void)
{
   const WindowEventUnrecPtr TheEvent = WindowEvent::create(WindowUnrecPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowExited(TheEvent);
   }

   _Producer.produceEvent(WindowExitedMethodId,TheEvent);
}

void WindowEventProducer::produceUpdate(const Time& ElapsedTime)
{
   const UpdateEventUnrecPtr TheEvent = UpdateEvent::create( WindowUnrecPtr(this), getSystemTime(),ElapsedTime);
   UpdateListenerSet ListenerSet(_UpdateListeners);
   for(UpdateListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->update(TheEvent);
   }
   
   _Producer.produceEvent(UpdateMethodId,TheEvent);
}


void WindowEventProducer::validateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location)
{
   //Get the vector of Clicks for this Button
   ClickVector& TheClickVector( _ButtonClickCountMap[Button] );
   //If the vector not empty
   if(TheClickVector.size() > 0) 
   {
      //Check if the timestamp for this click is less than the default multiple click Rate
      //Check if the Location of the click is greater then the default allowance away from the last click location
      if((TimeStamp - TheClickVector.back()._TimeStamp) > InputSettings::the()->getMultipleClickRate() ||
         Location.dist2(TheClickVector.back()._Location) > (InputSettings::the()->getMultipleClickMouseDriftAllowance() * InputSettings::the()->getMultipleClickMouseDriftAllowance()) )
      {
         //If so then clear the deque
         TheClickVector.clear();
      }
   }
}

void WindowEventProducer::updateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location)
{
   validateClickCount(Button, TimeStamp, Location);

   //Put the Click on the back of the vector
   _ButtonClickCountMap[Button].push_back( Click(TimeStamp, Location) );
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowEventProducer::WindowEventProducer(void) :
    Inherited(),
    _WindowEventLoopThread (NULL),
    _DisplayCallbackFunc   (NULL),
    _ReshapeCallbackFunc   (NULL),
    _CursorType            (CURSOR_POINTER),
    _BlockInput            (false)
{
    _ButtonClickCountMap[MouseEvent::BUTTON1] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON2] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON3] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON4] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON5] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON6] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON7] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON8] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON9] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON10] = ClickVector();

    _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON7] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON8] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON9] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON10] = Pnt2f(0,0);
}

WindowEventProducer::WindowEventProducer(const WindowEventProducer &source) :
    Inherited(source),
    _WindowEventLoopThread (NULL                          ),
    _DisplayCallbackFunc   (source._DisplayCallbackFunc   ),
    _ReshapeCallbackFunc   (source._ReshapeCallbackFunc   ),
	_CursorType            (source._CursorType            ),
    _BlockInput            (source._BlockInput            )
{
    _ButtonClickCountMap[MouseEvent::BUTTON1] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON2] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON3] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON4] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON5] = ClickVector();
    _ButtonClickCountMap[MouseEvent::BUTTON6] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON7] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON8] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON9] = ClickVector();
    //_ButtonClickCountMap[MouseEvent::BUTTON10] = ClickVector();

    _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2f(0,0);
    _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON7] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON8] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON9] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEvent::BUTTON10] = Pnt2f(0,0);
}

WindowEventProducer::~WindowEventProducer(void)
{
    if(_WindowEventLoopThread != NULL)
    {
        //_WindowEventLoopThread->setEventDispatchThreadFinish();
        //Close the Window
        Thread::join(_WindowEventLoopThread);
    }
}

/*----------------------------- class specific ----------------------------*/

void WindowEventProducer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void WindowEventProducer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump WindowEventProducer NI" << std::endl;
}

OSG_END_NAMESPACE
