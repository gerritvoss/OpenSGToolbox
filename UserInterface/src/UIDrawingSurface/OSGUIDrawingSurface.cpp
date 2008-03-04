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

#include "OSGUIDrawingSurface.h"
#include "Util/OSGUIDrawUtils.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"

#include "Component/Container/Window/OSGInternalWindow.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIDrawingSurface
A UI DrawingSurface. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIDrawingSurface::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIDrawingSurface::openWindow(InternalWindowPtr TheWindow, const Int32 Layer)
{
	MFInternalWindowPtr::iterator WindowItor(getInternalWindows().find(TheWindow));
	
	if(WindowItor == getInternalWindows().end())
	{
		beginEditCP(UIDrawingSurfacePtr(this), InternalWindowsFieldMask);
			getInternalWindows().push_back(TheWindow);
			if(Layer < 0 || Layer > getInternalWindows().size())
			{
				moveWindowToTop(TheWindow);
			}
			else
			{
				setWindowToLayer(TheWindow, Layer);
			}
		endEditCP(UIDrawingSurfacePtr(this), InternalWindowsFieldMask);
		
		if(getInternalWindows().back() == TheWindow)
		{
			getInternalWindows().back()->takeFocus();
		}

		TheWindow->open();
	}
	
}

void UIDrawingSurface::closeWindow(InternalWindowPtr TheWindow)
{
	MFInternalWindowPtr::iterator WindowItor(getInternalWindows().find(TheWindow));

	if(WindowItor != getInternalWindows().end())
	{
		beginEditCP(UIDrawingSurfacePtr(this), InternalWindowsFieldMask);
			getInternalWindows().erase(WindowItor);
		endEditCP(UIDrawingSurfacePtr(this), InternalWindowsFieldMask);
	}
	
	if(getFocusedWindow() != NullFC
		&& getInternalWindows().size() > 0)
	{
		getInternalWindows().back()->takeFocus();
	}
}

UInt32 UIDrawingSurface::getNumWindowLayers(void) const
{
	return getInternalWindows().size();
}

InternalWindowPtr UIDrawingSurface::getWindowAtLayer(const UInt32& Layer) const
{
	if(Layer < getInternalWindows().size())
	{
		return getInternalWindows().getValue(Layer);
	}
	else
	{
		return NullFC;
	}
}

Int32 UIDrawingSurface::getWindowLayer(InternalWindowPtr TheWindow) const
{
	UInt32 i(0);
	while(i<getInternalWindows().size() &&
		  getInternalWindows().getValue(i) != TheWindow)
	{
		++i;
	}

	if(i < getInternalWindows().size() )
	{
		return i;
	}
	else
	{
		return -1;
	}
}

void UIDrawingSurface::setWindowToLayer(InternalWindowPtr TheWindow, const UInt32& Layer)
{
	MFInternalWindowPtr::iterator RemovalItor(getInternalWindows().begin());
	while(RemovalItor != getInternalWindows().end() &&
		  (*RemovalItor) != TheWindow)
	{
		++RemovalItor;
	}

	if(RemovalItor < getInternalWindows().end() &&
	   Layer < getInternalWindows().size())
	{
		InternalWindowPtr SwapWindow(*RemovalItor);
		getInternalWindows().erase(RemovalItor);

		MFInternalWindowPtr::iterator InsertItor(getInternalWindows().begin());
		for(UInt32 i(0) ; i<Layer ; ++i){++InsertItor;}

		getInternalWindows().insert(InsertItor, SwapWindow);

		if(getFocusedWindow() != NullFC)
		{
			getInternalWindows().back()->takeFocus();
		}
	}
}

void UIDrawingSurface::moveWindowUp(InternalWindowPtr TheWindow)
{
	Int32 WindowLayer(getWindowLayer(TheWindow));
	if(WindowLayer < getInternalWindows().size())
	{
		setWindowToLayer(TheWindow,  WindowLayer+1);
	}
}

void UIDrawingSurface::moveWindowDown(InternalWindowPtr TheWindow)
{
	Int32 WindowLayer(getWindowLayer(TheWindow));
	if(WindowLayer > 0)
	{
		setWindowToLayer(TheWindow,  WindowLayer-1);
	}
}

void UIDrawingSurface::moveWindowToTop(InternalWindowPtr TheWindow)
{
	MFInternalWindowPtr::iterator RemovalItor(getInternalWindows().begin());
	while(RemovalItor != getInternalWindows().end() &&
		  (*RemovalItor) != TheWindow)
	{
		++RemovalItor;
	}
	
	if(RemovalItor < getInternalWindows().end())
	{
		InternalWindowPtr SwapWindow(*RemovalItor);
		getInternalWindows().erase(RemovalItor);

		MFInternalWindowPtr::iterator InsertItor(getInternalWindows().begin());
		if(TheWindow->getAllwaysOnTop())
		{
			InsertItor = getInternalWindows().end();
		}
		else
		{
			while(InsertItor != getInternalWindows().end() &&
				  !(*InsertItor)->getAllwaysOnTop())
			{
				++InsertItor;
			}
		}

		MFInternalWindowPtr::iterator NewPosition = getInternalWindows().insert(InsertItor,SwapWindow);

		if(getFocusedWindow() != NullFC)
		{
			getInternalWindows().back()->takeFocus();
		}
	}
}

void UIDrawingSurface::moveWindowToBottom(InternalWindowPtr TheWindow)
{
	MFInternalWindowPtr::iterator RemovalItor(getInternalWindows().begin());
	while(RemovalItor != getInternalWindows().end() &&
		  (*RemovalItor) != TheWindow)
	{
		++RemovalItor;
	}
	
	if(RemovalItor < getInternalWindows().end())
	{
		InternalWindowPtr SwapWindow(*RemovalItor);
		getInternalWindows().erase(RemovalItor);

		getInternalWindows().insert(getInternalWindows().begin(), SwapWindow);

		if(getFocusedWindow() != NullFC)
		{
			getInternalWindows().back()->takeFocus();
		}
	}
}

Pnt2f UIDrawingSurface::getMousePosition(void) const
{
    Pnt2f ViewportPoint(0,0);
    ViewportPtr TheViewport( getEventProducer()->windowToViewport(getEventProducer()->getMousePosition(),ViewportPoint) );
    Pnt2f Result(0,0);
    getMouseTransformFunctor()->viewportToRenderingSurface( ViewportPoint,TheViewport, Result);
    return Result;
}

void UIDrawingSurface::mouseClicked(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
	    MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
		    ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				getInternalWindows().getValue(i)->mouseClicked(TransformedMouseEvent);
				break;
			}
		}
    }
}

void UIDrawingSurface::mouseEntered(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
		MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
			ResultMouseLoc,e.getViewport());

		checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
	}
}

void UIDrawingSurface::mouseExited(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
		MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
			ResultMouseLoc,e.getViewport());

		checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
	}
}

void UIDrawingSurface::mousePressed(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
	    MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
		    ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				if(getInternalWindows().getValue(i) != getFocusedWindow())
				{
					moveWindowToTop(getInternalWindows().getValue(i));
				}
				getInternalWindows().back()->mousePressed(TransformedMouseEvent);
				break;
			}
		}
    }
}

void UIDrawingSurface::mouseReleased(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
	    MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
		    ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				getInternalWindows().getValue(i)->mouseReleased(TransformedMouseEvent);
				break;
			}
		}
    }
}


void UIDrawingSurface::mouseMoved(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
	    MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
		    ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				getInternalWindows().getValue(i)->mouseMoved(TransformedMouseEvent);
				break;
			}
		}
    }
}

void UIDrawingSurface::mouseDragged(const MouseEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
	    MouseEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getButton(), e.getClickCount(),
		    ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				getInternalWindows().getValue(i)->mouseDragged(TransformedMouseEvent);
				break;
			}
		}
    }
}

void UIDrawingSurface::mouseWheelMoved(const MouseWheelEvent& e)
{
	Pnt2f ResultMouseLoc;
	if(getMouseTransformFunctor()->viewportToRenderingSurface(e.getLocation(),e.getViewport(), ResultMouseLoc))
    {
		MouseWheelEvent TransformedMouseEvent(e.getSource(), e.getTimeStamp(), e.getWheelRotation(), e.getScrollType(),
			ResultMouseLoc,e.getViewport());

	    checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent.getLocation(),TransformedMouseEvent.getViewport());
		
		for(Int32 i(getInternalWindows().size()-1) ; i>=0 ; --i)
		{
			if(isContainedClipBounds(TransformedMouseEvent.getLocation(), getInternalWindows().getValue(i)))
			{
				getInternalWindows().getValue(i)->mouseWheelMoved(TransformedMouseEvent);
				break;
			}
		}
    }
}

void UIDrawingSurface::keyPressed(const KeyEvent& e)
{
	if(getFocusedWindow() != NullFC)
	{
		getFocusedWindow()->keyPressed(e);
	}
}

void UIDrawingSurface::keyReleased(const KeyEvent& e)
{
	if(getFocusedWindow() != NullFC)
	{
		getFocusedWindow()->keyReleased(e);
	}
}

void UIDrawingSurface::keyTyped(const KeyEvent& e)
{
	if(getFocusedWindow() != NullFC)
	{
		getFocusedWindow()->keyTyped(e);
	}
}

void UIDrawingSurface::checkMouseEnterExit(const Event& e, const Pnt2f& MouseLocation, ViewportPtr TheViewport)
{
	for(UInt32 i(0) ; i<getInternalWindows().size() ; ++i)
	{
		if(getInternalWindows().getValue(i)->getMouseContained())
		{
			//Check if mouse is outside of the frame
			if(!isContainedClipBounds(MouseLocation, getInternalWindows().getValue(i)))
			{
				//Mouse has exited the frame
				getInternalWindows().getValue(i)->setMouseContained(false);
				MouseEvent ExitedEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
				getInternalWindows().getValue(i)->mouseExited(ExitedEvent);
			}
		}
		else
		{
			//Check if mouse is inside of the frame
			if(isContainedClipBounds(MouseLocation, getInternalWindows().getValue(i)))
			{
				//Mouse has entered the frame
			    getInternalWindows().getValue(i)->setMouseContained(true);
				MouseEvent EnteredEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation, TheViewport);
				getInternalWindows().getValue(i)->mouseEntered(EnteredEvent);
			}
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIDrawingSurface::UIDrawingSurface(void) :
    Inherited()
{
}

UIDrawingSurface::UIDrawingSurface(const UIDrawingSurface &source) :
    Inherited(source)
{
}

UIDrawingSurface::~UIDrawingSurface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIDrawingSurface::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	/*if( (whichField & EventProducerFieldMask) )
    {
		//Remove Listeners from old EventProducer
		//Add Listeners to the EventProducer
		if(getEventProducer() != NullFC)
		{
			getEventProducer()->addMouseListener(this);
			getEventProducer()->addMouseMotionListener(this);
			getEventProducer()->addMouseWheelListener(this);
			getEventProducer()->addKeyListener(this);
		}
	}*/
	
	if( (whichField & InternalWindowsFieldMask) )
	{
		for(UInt32 i(0) ; i<getInternalWindows().size() ; ++i)
		{
			if(getInternalWindows().getValue(i)->getDrawingSurface() != UIDrawingSurfacePtr(this))
			{
				beginEditCP(getInternalWindows().getValue(i), InternalWindow::DrawingSurfaceFieldMask);
					getInternalWindows().getValue(i)->setDrawingSurface(UIDrawingSurfacePtr(this));
				endEditCP(getInternalWindows().getValue(i), InternalWindow::DrawingSurfaceFieldMask);
			}
		}
	}

	if(whichField & SizeFieldMask)
	{
		Vec2f Size;
		Pnt2f Position;
		bool isSizeDifferent(false);
		bool isPositionDifferent(false);
		for(UInt32 i(0) ; i<getInternalWindows().size() ; ++i)
		{

			if(getInternalWindows().getValue(i)->isScalableInDrawingSurface())
			{
				//Update Scaling
				Size.setValues(getInternalWindows().getValue(i)->getScalingInDrawingSurface().x() * static_cast<Real32>(getSize().x()),
					         getInternalWindows().getValue(i)->getScalingInDrawingSurface().y() * static_cast<Real32>(getSize().y()));
			}
			else
			{
				Size = getInternalWindows().getValue(i)->getPreferredSize();
			}

			Size.setValues(osgMax(osgMin(Size.x(), getInternalWindows().getValue(i)->getMaxSize().x()), getInternalWindows().getValue(i)->getMinSize().x()),
				           osgMax(osgMin(Size.y(), getInternalWindows().getValue(i)->getMaxSize().y()), getInternalWindows().getValue(i)->getMinSize().y()));

			isSizeDifferent = (getInternalWindows().getValue(i)->getSize().x() != Size.x() ||
				               getInternalWindows().getValue(i)->getSize().y() != Size.y());

			if(getInternalWindows().getValue(i)->isAlignableInDrawingSurface())
			{
				//Update Alignment
				Position = calculateAlignment(Pnt2f(0,0), getSize(), Size, getInternalWindows().getValue(i)->getAlignmentInDrawingSurface().y(), getInternalWindows().getValue(i)->getAlignmentInDrawingSurface().x());

				isPositionDifferent = (getInternalWindows().getValue(i)->getPosition().x() != Position.x() ||
									   getInternalWindows().getValue(i)->getPosition().y() != Position.y());
			}


			UInt32 FieldsToChangeMask(0);
			if(isSizeDifferent)
			{
				FieldsToChangeMask |= InternalWindow::SizeFieldMask;
			}
			if(isPositionDifferent)
			{
				FieldsToChangeMask |= InternalWindow::PositionFieldMask;
			}
			if(isSizeDifferent | isPositionDifferent)
			{
				beginEditCP(getInternalWindows().getValue(i), FieldsToChangeMask);
					if(isSizeDifferent)
					{
						getInternalWindows().getValue(i)->setSize(Size);
					}
					if(isPositionDifferent)
					{
						getInternalWindows().getValue(i)->setPosition(Position);
					}
				endEditCP(getInternalWindows().getValue(i), FieldsToChangeMask);
			}
		}
	}
}

void UIDrawingSurface::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIDrawingSurface NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIDRAWINGSURFACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIDRAWINGSURFACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIDRAWINGSURFACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

