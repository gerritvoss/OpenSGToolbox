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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGBaseFunctions.h>
//#include <OpenSG/OSGThreadManager.h>

#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WindowEventProducer
WindowEventProducer is the base class for all Window specific Event producers 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowEventProducer::initMethod (void)
{
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

WindowPtr WindowEventProducer::initWindow(void)
{
    beginEditCP(WindowEventProducerPtr(this), WindowEventProducer::WindowFieldMask);
        setWindow(createWindow());
    endEditCP(WindowEventProducerPtr(this), WindowEventProducer::WindowFieldMask);

	_RenderAction = RenderAction::create();

    return getWindow();
}

void WindowEventProducer::setDisplayCallback(DisplayCallbackFunc Callback)
{
   _DisplayCallbackFunc = Callback;
}

void WindowEventProducer::setReshapeCallback(ReshapeCallbackFunc Callback)
{
   _ReshapeCallbackFunc = Callback;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowEventProducer::WindowEventProducer(void) :
    Inherited(), _WindowEventLoopThread(NULL),
       _DisplayCallbackFunc(NULL),
       _ReshapeCallbackFunc(NULL),
	   _CursorType(CURSOR_POINTER)
{
   _ButtonClickCountMap[MouseEvent::BUTTON1] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON2] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON3] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON4] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON5] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON6] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON7] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON8] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON9] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON10] = ClickVector();
   
   _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON7] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON8] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON9] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON10] = Pnt2f(0,0);
}

WindowEventProducer::WindowEventProducer(const WindowEventProducer &source) :
    Inherited(source), _WindowEventLoopThread(NULL),
       _DisplayCallbackFunc(source._DisplayCallbackFunc),
       _ReshapeCallbackFunc(source._ReshapeCallbackFunc),
	   _CursorType(source._CursorType)
{
   _ButtonClickCountMap[MouseEvent::BUTTON1] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON2] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON3] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON4] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON5] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON6] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON7] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON8] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON9] = ClickVector();
   _ButtonClickCountMap[MouseEvent::BUTTON10] = ClickVector();
   
   _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON7] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON8] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON9] = Pnt2f(0,0);
   _ButtonClickMap[MouseEvent::BUTTON10] = Pnt2f(0,0);
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

void WindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void WindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WindowEventProducer NI" << std::endl;
}

ViewportPtr WindowEventProducer::windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint)
{
	ViewportPtr ThePort;
	for(UInt32 i(0) ; i<getWindow()->getPort().size() ; ++i)
	{
		ThePort = getWindow()->getPort()[i];
		//if(WindowPoint.x() >= ThePort->getPixelLeft() &&
		//   WindowPoint.x() <= ThePort->getPixelRight() &&
		//   WindowPoint.y() <= ThePort->getPixelTop() &&
		//   WindowPoint.y() >= ThePort->getPixelBottom())
		//{
		//}
        ViewportPoint.setValues(WindowPoint.x() - ThePort->getPixelLeft(), WindowPoint.y() - ThePort->getPixelBottom());
		
        return ThePort;
		
	}
	return NullFC;
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
   Time t(getSystemTime());
   updateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
		  (*SetItor)->mouseClicked(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMouseEntered(const Pnt2f& Location)
{
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport );
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
		   (*SetItor)->mouseEntered(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMouseExited(const Pnt2f& Location)
{
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport );
       MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
		  (*SetItor)->mouseExited(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMousePressed(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
	_ButtonClickMap[Button] = Location;
	TimeStamp t(getSystemTime());
	validateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
		  (*SetItor)->mousePressed(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMouseReleased(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
	TimeStamp t(getSystemTime());
	validateClickCount(Button, t, Location);
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   MouseListenerSet ListenerSet(_MouseListeners);
       for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
       {
		  (*SetItor)->mouseReleased(TheEvent);
	   }
   }
   if(_ButtonClickMap[Button] == Location)
   {
	   produceMouseClicked(Button, Location);
   }
}


void WindowEventProducer::produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2f& Location, const MouseWheelEvent::ScrollType& TheScrollType)
{
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseWheelEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), WheelRotation, TheScrollType, ViewportLocation, ResultViewport );
	   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
	   {
		  (*SetItor)->mouseWheelMoved(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMouseMoved(const Pnt2f& Location)
{
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, ViewportLocation, ResultViewport );
       for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
	   {
		  (*SetItor)->mouseMoved(TheEvent);
	   }
   }
}

void WindowEventProducer::produceMouseDragged(const MouseEvent::MouseButton& Button, const Pnt2f& Location)
{
   Pnt2f ViewportLocation;
   ViewportPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NullFC)
   {
	   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), Button, 0, ViewportLocation, ResultViewport );
       for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
	   {
		  (*SetItor)->mouseDragged(TheEvent);
	   }
   }
}

void WindowEventProducer::produceKeyPressed(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers, getWindow() );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->keyPressed(TheEvent);
   }
   produceKeyTyped(TheKey, Modifiers);
}

void WindowEventProducer::produceKeyReleased(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers, getWindow() );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->keyReleased(TheEvent);
   }
}

void WindowEventProducer::produceKeyTyped(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers, getWindow() );
   KeyListenerSet ListenerSet(_KeyListeners);
   for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->keyTyped(TheEvent);
   }
}

void WindowEventProducer::produceWindowOpened(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowOpened(TheEvent);
   }
}

void WindowEventProducer::produceWindowClosing(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosing(TheEvent);
   }
}

void WindowEventProducer::produceWindowClosed(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosed(TheEvent);
   }
}

void WindowEventProducer::produceWindowIconified(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowIconified(TheEvent);
   }
}

void WindowEventProducer::produceWindowDeiconified(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeiconified(TheEvent);
   }
}

void WindowEventProducer::produceWindowActivated(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowActivated(TheEvent);
   }
}

void WindowEventProducer::produceWindowDeactivated(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeactivated(TheEvent);
   }
}

void WindowEventProducer::produceWindowEntered(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowEntered(TheEvent);
   }
}

void WindowEventProducer::produceWindowExited(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime());
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowExited(TheEvent);
   }
}

void WindowEventProducer::produceUpdate(const Time& ElapsedTime)
{
   UpdateEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), ElapsedTime );
   UpdateListenerSet ListenerSet(_UpdateListeners);
   for(UpdateListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->update(TheEvent);
   }
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

OSG_END_NAMESPACE

