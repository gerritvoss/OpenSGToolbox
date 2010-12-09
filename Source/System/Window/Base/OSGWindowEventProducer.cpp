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

StatElemDesc<StatTimeStampElem> WindowEventProducer::statWindowLoopTime("WindowLoopTime", 
                                                                    "time for last window loop",
                                                                    StatElemDescBase::RESET_NEVER);

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

Window* WindowEventProducer::initWindow(void)
{
    //TODO
	_RenderAction = RenderAction::create();

    return this;
}

void WindowEventProducer::setDisplayCallback(DisplayCallbackFunc Callback)
{
   _DisplayCallbackFunc = Callback;
}

void WindowEventProducer::setReshapeCallback(ReshapeCallbackFunc Callback)
{
   _ReshapeCallbackFunc = Callback;
}

ViewportUnrecPtr WindowEventProducer::windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint)
{
	ViewportUnrecPtr ThePort;
	for(UInt32 i(0) ; i<getMFPort()->size() ; ++i)
	{
		ThePort = getPort(i);
        if(ThePort->getEnabled())
        {
            ViewportPoint.setValues(WindowPoint.x() - ThePort->getPixelLeft(), WindowPoint.y() - ThePort->getPixelBottom());
    		
            return ThePort;
        }
		
	}
	return NULL;
}

void WindowEventProducer::produceMouseClicked(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
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
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );
	   
       WindowEventProducerBase::produceMouseClicked(Details);
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
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, getSystemTime(), MouseEventDetails::NO_BUTTON, 0, ViewportLocation, ResultViewport );

       WindowEventProducerBase::produceMouseEntered(Details);
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
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, getSystemTime(), MouseEventDetails::NO_BUTTON, 0, ViewportLocation, ResultViewport );

       WindowEventProducerBase::produceMouseExited(Details);
   }
}

void WindowEventProducer::produceMousePressed(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
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
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );

       WindowEventProducerBase::produceMousePressed(Details);
   }
}

void WindowEventProducer::produceMouseReleased(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

	TimeStamp t(getSystemTime());
	validateClickCount(Button, t, Location);
    Pnt2f ViewportLocation;
    Real32 DriftAllowance(InputSettings::the()->getMultipleClickMouseDriftAllowance());
    if(Location.dist2(_ButtonClickMap[Button]) <= (DriftAllowance * DriftAllowance))
    {
        produceMouseClicked(Button, Location);
    }
    ViewportUnrecPtr ResultViewport;
    ResultViewport = windowToViewport(Location, ViewportLocation);
    if(ResultViewport != NULL)
    {
        MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, t, Button, _ButtonClickCountMap[Button].size(), ViewportLocation, ResultViewport );

        WindowEventProducerBase::produceMouseReleased(Details);
    }
}


void WindowEventProducer::produceMouseWheelMoved(const Int32& WheelRotation, const Pnt2f& Location, const MouseWheelEventDetails::ScrollType& TheScrollType)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   const MouseWheelEventDetailsUnrecPtr Details = MouseWheelEventDetails::create( this, getSystemTime(), WheelRotation, TheScrollType,MouseWheelEventDetails::SCROLL_ORIENTATION_VERTICAL, ViewportLocation, ResultViewport );

       WindowEventProducerBase::produceMouseWheelMoved(Details);
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
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, getSystemTime(), MouseEventDetails::NO_BUTTON, 0, ViewportLocation, ResultViewport,Delta );

       WindowEventProducerBase::produceMouseMoved(Details);
   }
}

void WindowEventProducer::produceMouseDragged(const MouseEventDetails::MouseButton& Button, const Pnt2f& Location, const Vec2f& Delta)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   Pnt2f ViewportLocation;
   ViewportUnrecPtr ResultViewport;
   ResultViewport = windowToViewport(Location, ViewportLocation);
   if(ResultViewport != NULL)
   {
	   MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(this, getSystemTime(), Button, 0, ViewportLocation, ResultViewport,Delta );

       WindowEventProducerBase::produceMouseDragged(Details);
   }
}

void WindowEventProducer::produceKeyPressed(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   KeyEventDetailsUnrecPtr Details = KeyEventDetails::create( this, getSystemTime(), TheKey, Modifiers, this );

   WindowEventProducerBase::produceKeyPressed(Details);
   produceKeyTyped(TheKey, Modifiers);
}

void WindowEventProducer::produceKeyReleased(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   KeyEventDetailsUnrecPtr Details = KeyEventDetails::create( this, getSystemTime(), TheKey, Modifiers, this );

   WindowEventProducerBase::produceKeyReleased(Details);
}

void WindowEventProducer::produceKeyTyped(const KeyEventDetails::Key& TheKey, const UInt32& Modifiers)
{
    //Check if Input is blocked
    if(_BlockInput) { return; }

   KeyEventDetailsUnrecPtr Details = KeyEventDetails::create( this, getSystemTime(), TheKey, Modifiers, this );

   WindowEventProducerBase::produceKeyTyped(Details);
}

void WindowEventProducer::produceWindowOpened(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowOpened(Details);
}

void WindowEventProducer::produceWindowClosing(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowClosing(Details);
}

void WindowEventProducer::produceWindowClosed(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(NULL, getSystemTime());

   WindowEventProducerBase::produceWindowClosed(Details);
}

void WindowEventProducer::produceWindowIconified(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowIconified(Details);
}

void WindowEventProducer::produceWindowDeiconified(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowDeiconified(Details);
}

void WindowEventProducer::produceWindowActivated(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowActivated(Details);
}

void WindowEventProducer::produceWindowDeactivated(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowDeactivated(Details);
}

void WindowEventProducer::produceWindowEntered(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowEntered(Details);
}

void WindowEventProducer::produceWindowExited(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create(this, getSystemTime());

   WindowEventProducerBase::produceWindowExited(Details);
}

void WindowEventProducer::produceUpdate(const Time& ElapsedTime)
{
   UpdateEventDetailsUnrecPtr Details = UpdateEventDetails::create( this, getSystemTime(),ElapsedTime);
   
   WindowEventProducerBase::produceUpdate(Details);
}


void WindowEventProducer::validateClickCount(const MouseEventDetails::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location)
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

void WindowEventProducer::updateClickCount(const MouseEventDetails::MouseButton& Button, const Time& TimeStamp, const Pnt2f& Location)
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
    _ButtonClickCountMap[MouseEventDetails::BUTTON1] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON2] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON3] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON4] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON5] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON6] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON7] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON8] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON9] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON10] = ClickVector();

    _ButtonClickMap[MouseEventDetails::BUTTON1] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON2] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON3] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON4] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON5] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON6] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON7] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON8] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON9] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON10] = Pnt2f(0,0);
}

WindowEventProducer::WindowEventProducer(const WindowEventProducer &source) :
    Inherited(source),
    _WindowEventLoopThread (NULL                          ),
    _DisplayCallbackFunc   (source._DisplayCallbackFunc   ),
    _ReshapeCallbackFunc   (source._ReshapeCallbackFunc   ),
	_CursorType            (source._CursorType            ),
    _BlockInput            (source._BlockInput            )
{
    _ButtonClickCountMap[MouseEventDetails::BUTTON1] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON2] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON3] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON4] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON5] = ClickVector();
    _ButtonClickCountMap[MouseEventDetails::BUTTON6] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON7] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON8] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON9] = ClickVector();
    //_ButtonClickCountMap[MouseEventDetails::BUTTON10] = ClickVector();

    _ButtonClickMap[MouseEventDetails::BUTTON1] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON2] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON3] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON4] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON5] = Pnt2f(0,0);
    _ButtonClickMap[MouseEventDetails::BUTTON6] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON7] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON8] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON9] = Pnt2f(0,0);
    //_ButtonClickMap[MouseEventDetails::BUTTON10] = Pnt2f(0,0);
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
