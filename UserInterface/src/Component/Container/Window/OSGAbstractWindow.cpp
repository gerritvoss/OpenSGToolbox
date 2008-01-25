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

void AbstractWindow::updateContainerLayout(void)
{
    if(getParentContainer() != NullFC)
    {
		Inherited::updateContainerLayout();
    }
	else if(getSize() != getPreferredSize())
	{
		Vec2s Size(osgMax(osgMin(getPreferredSize().x(), getMaxSize().x()), getMinSize().x()),
			       osgMax(osgMin(getPreferredSize().y(), getMaxSize().y()), getMinSize().y()));
		beginEditCP(ComponentPtr(this), SizeFieldMask);
			setSize(Size);
		endEditCP(ComponentPtr(this), SizeFieldMask);
	}
}

void AbstractWindow::updateClipBounds(void)
{
	Pnt2s TopLeft, BottomRight;
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
        Pnt2s MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Get Parent Container's Clip Bounds
		Pnt2s ContainerClipTopLeft(0,0), ContainerClipBottomRight(getDrawingSurface()->getSize());
		
        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2s(getPosition());
		ContainerClipBottomRight -= Vec2s(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);
	}
	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	beginEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
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

UIBackgroundPtr AbstractWindow::getDrawnBackground(void) const
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

void AbstractWindow::drawInternal(const GraphicsPtr TheGraphics) const
{
    Inherited::drawInternal(TheGraphics);
        
    //If I have an active TitleBar then draw it
	if(getDrawDecorations() && getDrawTitlebar())
	{
	}
}


void AbstractWindow::produceWindowOpened(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowOpened(TheEvent);
   }
}

void AbstractWindow::produceWindowClosing(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosing(TheEvent);
   }
}

void AbstractWindow::produceWindowClosed(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowClosed(TheEvent);
   }
}

void AbstractWindow::produceWindowIconified(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowIconified(TheEvent);
   }
}

void AbstractWindow::produceWindowDeiconified(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeiconified(TheEvent);
   }
}

void AbstractWindow::produceWindowActivated(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowActivated(TheEvent);
   }
}

void AbstractWindow::produceWindowDeactivated(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowDeactivated(TheEvent);
   }
}

void AbstractWindow::produceWindowEntered(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowEntered(TheEvent);
   }
}

void AbstractWindow::produceWindowExited(void)
{
   WindowEvent TheEvent( AbstractWindowPtr(this), getSystemTime() );
   for(WindowListenerSetConstItor SetItor(_WindowListeners.begin()) ; SetItor != _WindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->windowExited(TheEvent);
   }
}

void AbstractWindow::removeWindowListener(WindowListenerPtr Listener)
{
   WindowListenerSetItor EraseIter(_WindowListeners.find(Listener));
   if(EraseIter != _WindowListeners.end())
   {
      _WindowListeners.erase(EraseIter);
   }
}

void AbstractWindow::focusGained(const FocusEvent& e)
{
	Inherited::focusGained(e);
	produceWindowActivated();
}

void AbstractWindow::focusLost(const FocusEvent& e)
{
	Inherited::focusLost(e);
	produceWindowDeactivated();
}

void AbstractWindow::mouseEntered(const MouseEvent& e)
{
	Inherited::mouseEntered(e);
	produceWindowEntered();
}

void AbstractWindow::mouseExited(const MouseEvent& e)
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTWINDOWBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTWINDOWBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

