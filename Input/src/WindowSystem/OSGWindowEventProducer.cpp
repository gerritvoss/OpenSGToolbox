/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

void WindowEventProducer::setDisplayCallback(DisplayCallbackFunc Callback)
{
   _DisplayCallbackFunc = Callback;
}

void WindowEventProducer::setReshapeCallback(ReshapeCallbackFunc Callback)
{
   _ReshapeCallbackFunc = Callback;
}

bool WindowEventProducer::attachWindow(WindowPtr Win)
{
   if(getWindow() == NullFC)
   {
      beginEditCP(WindowEventProducerPtr(this), WindowEventProducer::WindowFieldMask);
         setWindow(Win);
      endEditCP(WindowEventProducerPtr(this), WindowEventProducer::WindowFieldMask);
      return true;
   }
   else
   {
      return false;
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowEventProducer::WindowEventProducer(void) :
    Inherited(), _EventDispatchThread(NULL),
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
   
   _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON7] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON8] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON9] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON10] = Pnt2s(0,0);
}

WindowEventProducer::WindowEventProducer(const WindowEventProducer &source) :
    Inherited(source), _EventDispatchThread(source._EventDispatchThread),
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
   
   _ButtonClickMap[MouseEvent::BUTTON1] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON2] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON3] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON4] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON5] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON6] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON7] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON8] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON9] = Pnt2s(0,0);
   _ButtonClickMap[MouseEvent::BUTTON10] = Pnt2s(0,0);
}

WindowEventProducer::~WindowEventProducer(void)
{
   if(_EventDispatchThread != NULL)
   {
      _EventDispatchThread->setEventDispatchThreadFinish();
      Thread::join(_EventDispatchThread);
   }
}

/*----------------------------- class specific ----------------------------*/

void WindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & WindowFieldMask)
    {
       initEventDispatchThread();
    }
}

void WindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WindowEventProducer NI" << std::endl;
}

void WindowEventProducer::initEventDispatchThread(void)
{
   //If my EventDispatchThread has not been created yet
   if(_EventDispatchThread == NULL)
   {
      //Create the thread
      _EventDispatchThread = dynamic_cast<EventDispatchThread *>(ThreadManager::the()->getThread("WindowEventProducer", "OSGEventDispatchThread"));
   }
   else
   {
      _EventDispatchThread->setEventDispatchThreadFinish();
      Thread::join(_EventDispatchThread);
   }
   
   if(getWindow() == NullFC)
   {
      _EventDispatchThread = NULL;
      return;
   }

   //Start the EventDispatchThread
   //Run it on with the MainAspect id
   _EventDispatchThread->run(0);
}

void WindowEventProducer::exitEventDispatchThread(void)
{
   if(_EventDispatchThread != NULL)
   {
      _EventDispatchThread->setEventDispatchThreadFinish();
      Thread::join(_EventDispatchThread);
   }
}

void WindowEventProducer::produceMouseClicked(const MouseEvent::MouseButton& Button, const Pnt2s& Location)
{
   Time t(getSystemTime());
   updateClickCount(Button, t, Location);
   MouseEvent TheEvent( WindowEventProducerPtr(this), t, Button, _ButtonClickCountMap[Button].size(), Location );
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseClicked(TheEvent);
   }
}

void WindowEventProducer::produceMouseEntered(const Pnt2s& Location)
{
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, Location );
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseEntered(TheEvent);
   }
}

void WindowEventProducer::produceMouseExited(const Pnt2s& Location)
{
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, Location );
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseExited(TheEvent);
   }
}

void WindowEventProducer::produceMousePressed(const MouseEvent::MouseButton& Button, const Pnt2s& Location)
{
	_ButtonClickMap[Button] = Location;
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), Button, _ButtonClickCountMap[Button].size(), Location );
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mousePressed(TheEvent);
   }
}

void WindowEventProducer::produceMouseReleased(const MouseEvent::MouseButton& Button, const Pnt2s& Location)
{
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), Button, _ButtonClickCountMap[Button].size(), Location );
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseReleased(TheEvent);
   }
   if(_ButtonClickMap[Button] == Location)
   {
	   produceMouseClicked(Button, Location);
   }
}


void WindowEventProducer::produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2s& Location, const MouseWheelEvent::ScrollType& TheScrollType)
{
   MouseWheelEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), WheelRotation, TheScrollType, Location);
   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseWheelMoved(TheEvent);
   }
}

void WindowEventProducer::produceMouseMoved(const Pnt2s& Location)
{
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), MouseEvent::NO_BUTTON, 0, Location );
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseMoved(TheEvent);
   }
}

void WindowEventProducer::produceMouseDragged(const MouseEvent::MouseButton& Button, const Pnt2s& Location)
{
   MouseEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), Button, 0, Location );
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseDragged(TheEvent);
   }
}

void WindowEventProducer::produceKeyPressed(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers );
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyPressed(TheEvent);
   }
   produceKeyTyped(TheKey, Modifiers);
}

void WindowEventProducer::produceKeyReleased(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers );
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyReleased(TheEvent);
   }
}

void WindowEventProducer::produceKeyTyped(const KeyEvent::Key& TheKey, const UInt32& Modifiers)
{
   KeyEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), TheKey, Modifiers );
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyTyped(TheEvent);
   }
}

void WindowEventProducer::produceWindowOpened(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowOpened(TheEvent);
   }
}

void WindowEventProducer::produceWindowClosing(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosing(TheEvent);
   }
}

void WindowEventProducer::produceWindowClosed(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosed(TheEvent);
   }
}

void WindowEventProducer::produceWindowIconified(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowIconified(TheEvent);
   }
}

void WindowEventProducer::produceWindowDeiconified(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeiconified(TheEvent);
   }
}

void WindowEventProducer::produceWindowActivated(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowActivated(TheEvent);
   }
}

void WindowEventProducer::produceWindowDeactivated(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeactivated(TheEvent);
   }
}

void WindowEventProducer::produceWindowEntered(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowEntered(TheEvent);
   }
}

void WindowEventProducer::produceWindowExited(void)
{
   WindowEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), getWindow() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowExited(TheEvent);
   }
}

void WindowEventProducer::produceUpdate(const Time& ElapsedTime)
{
   UpdateEvent TheEvent( WindowEventProducerPtr(this), getSystemTime(), ElapsedTime );
   for(UpdateListenerSetConstItor SetItor(_UpdateListeners.begin()) ; SetItor != _UpdateListeners.end() ; ++SetItor)
   {
      (*SetItor)->update(TheEvent);
   }
}


void WindowEventProducer::updateClickCount(const MouseEvent::MouseButton& Button, const Time& TimeStamp, const Pnt2s& Location)
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
   //Put the Click on the back of the vector
   TheClickVector.push_back( Click(TimeStamp, Location) );
}

OSG_END_NAMESPACE

