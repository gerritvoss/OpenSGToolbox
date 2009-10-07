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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractWindow.h"

#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Util/OSGUIDrawUtils.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractWindow
A UI Abstract Window. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractWindow::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractWindow::addWindowListener(WindowListenerPtr Listener)
{
   _WindowListeners.insert(Listener);
   return EventConnection(
       boost::bind(&AbstractWindow::isWindowListenerAttached, this, Listener),
       boost::bind(&AbstractWindow::removeWindowListener, this, Listener));
}

void AbstractWindow::updateContainerLayout(void)
{
    if(getParentContainer() != NullFC)
    {
		Inherited::updateContainerLayout();
    }
	else if(getSize() != getPreferredSize())
	{
		Vec2f Size(osgMax(osgMin(getPreferredSize().x(), getMaxSize().x()), getMinSize().x()),
			       osgMax(osgMin(getPreferredSize().y(), getMaxSize().y()), getMinSize().y()));
		beginEditCP(ComponentPtr(this), SizeFieldMask);
			setSize(Size);
		endEditCP(ComponentPtr(this), SizeFieldMask);
	}
}

void AbstractWindow::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	if( getDrawingSurface() == NullFC )
	{
		//If I have no parent container use my bounds
		getBounds(TopLeft, BottomRight);
	}
	else
	{
		//Get the intersection of:
		     //My Bounds
		     //My Parent Containers Clip Bounds
		     //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Get Parent Container's Clip Bounds
		Pnt2f ContainerClipTopLeft(0,0), ContainerClipBottomRight(getDrawingSurface()->getSize());
		
        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
		ContainerClipBottomRight -= Vec2f(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);
	}
	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	beginEditCP(ComponentPtr(this), Component::ClipBoundsFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipBoundsFieldMask);
}

BorderPtr AbstractWindow::getDrawnBorder(void) const
{
	if(getDrawDecorations())
	{
		return Inherited::getDrawnBorder();
	}
	else
	{
		return NullFC;
	}
}

LayerPtr AbstractWindow::getDrawnBackground(void) const
{
	if(getDrawDecorations())
	{
		return Inherited::getDrawnBackground();
	}
	else
	{
		return NullFC;
	}
}

LayerPtr AbstractWindow::getDrawnForeground(void) const
{
	if(getDrawDecorations())
	{
		return Inherited::getDrawnForeground();
	}
	else
	{
		return NullFC;
	}
}


void AbstractWindow::produceWindowOpened(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowOpened(TheEvent);
   }
   produceEvent(WindowOpenedMethodId,TheEvent);
}

void AbstractWindow::produceWindowClosing(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosing(TheEvent);
   }
   produceEvent(WindowClosingMethodId,TheEvent);
}

void AbstractWindow::produceWindowClosed(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosed(TheEvent);
   }
   produceEvent(WindowClosedMethodId,TheEvent);
}

void AbstractWindow::produceWindowIconified(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowIconified(TheEvent);
   }
   produceEvent(WindowIconifiedMethodId,TheEvent);
}

void AbstractWindow::produceWindowDeiconified(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeiconified(TheEvent);
   }
   produceEvent(WindowDeiconifiedMethodId,TheEvent);
}

void AbstractWindow::produceWindowActivated(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowActivated(TheEvent);
   }
   produceEvent(WindowActivatedMethodId,TheEvent);
}

void AbstractWindow::produceWindowDeactivated(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeactivated(TheEvent);
   }
   produceEvent(WindowDeactivatedMethodId,TheEvent);
}

void AbstractWindow::produceWindowEntered(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowEntered(TheEvent);
   }
   produceEvent(WindowEnteredMethodId,TheEvent);
}

void AbstractWindow::produceWindowExited(void)
{
   const WindowEventPtr TheEvent = WindowEvent::create( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowExited(TheEvent);
   }
   produceEvent(WindowExitedMethodId,TheEvent);
}

void AbstractWindow::removeWindowListener(WindowListenerPtr Listener)
{
   WindowListenerSetItor EraseIter(_WindowListeners.find(Listener));
   if(EraseIter != _WindowListeners.end())
   {
      _WindowListeners.erase(EraseIter);
   }
}

void AbstractWindow::focusGained(const FocusEventPtr e)
{
	Inherited::focusGained(e);
	produceWindowActivated();
}

void AbstractWindow::focusLost(const FocusEventPtr e)
{
	Inherited::focusLost(e);
	produceWindowDeactivated();
}

void AbstractWindow::mouseEntered(const MouseEventPtr e)
{
	Inherited::mouseEntered(e);
	produceWindowEntered();
}

void AbstractWindow::mouseExited(const MouseEventPtr e)
{
	Inherited::mouseExited(e);
	produceWindowExited();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractWindow::AbstractWindow(void) :
    Inherited(),
	_VetoWindowClose(false)
{
}

AbstractWindow::AbstractWindow(const AbstractWindow &source) :
    Inherited(source),
	_VetoWindowClose(false)
{
}

AbstractWindow::~AbstractWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractWindow NI" << std::endl;
}

OSG_END_NAMESPACE

