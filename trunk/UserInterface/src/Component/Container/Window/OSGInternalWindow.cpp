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

#include "OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Component/Misc/OSGToolTip.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Menu/OSGMenuBar.h"
#include "Component/Text/OSGLabel.h"
#include "Component/Button/OSGButton.h"
#include "Component/Container/Window/OSGTitlebar.h"
#include "Border/OSGWindowBorder.h"
#include "Util/OSGUIDrawUtils.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::InternalWindow
A UI Internal Window. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InternalWindow::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void InternalWindow::setIconify(bool Iconify)
{
	if(Iconify && !getIsIcon())
	{
		//TODO: Implement
		beginEditCP(InternalWindowPtr(this), IsIconFieldMask);
			setIsIcon(Iconify);
		endEditCP(InternalWindowPtr(this), IsIconFieldMask);

		produceWindowIconified();
	}
	else if(!Iconify && getIsIcon())
	{
		//TODO: Implement
		beginEditCP(InternalWindowPtr(this), IsIconFieldMask);
			setIsIcon(Iconify);
		endEditCP(InternalWindowPtr(this), IsIconFieldMask);

		produceWindowDeiconified();
	}
}

bool InternalWindow::getIconify(void) const
{
	return getIsIcon();
}

void InternalWindow::setMaximize(bool Maximize)
{
	if(Maximize && !getIsMaximized())
	{
		beginEditCP(InternalWindowPtr(this), IsMaximizedFieldMask | PreviousSizeFieldMask | PreviousPositionFieldMask | PreferredSizeFieldMask | PositionFieldMask);
			setIsMaximized(Maximize);
			setPreviousSize(getSize());
			setPreviousPosition(getPosition());
			setPosition(Pnt2f(0,0));
			setPreferredSize(getDrawingSurface()->getSize());
		endEditCP(InternalWindowPtr(this), IsMaximizedFieldMask | PreviousSizeFieldMask | PreviousPositionFieldMask | PreferredSizeFieldMask | PositionFieldMask);
	}
	else if(!Maximize && getIsMaximized())
	{
		beginEditCP(InternalWindowPtr(this), IsMaximizedFieldMask | PreviousSizeFieldMask | PreviousPositionFieldMask | PreferredSizeFieldMask | PositionFieldMask);
			setIsMaximized(Maximize);
			Vec2f TempSize(getPreviousSize());
			Pnt2f TempPos(getPreviousPosition());
			setPreviousSize(getSize());
			setPreviousPosition(getPosition());
			setPreferredSize(TempSize);
			setPosition(TempPos);
		endEditCP(InternalWindowPtr(this), IsMaximizedFieldMask | PreviousSizeFieldMask | PreviousPositionFieldMask | PreferredSizeFieldMask | PositionFieldMask);
	}
}

bool InternalWindow::getMaximize(void) const
{
	return getIsMaximized();
}

void InternalWindow::open(void)
{
	produceWindowOpened();
}

void InternalWindow::close(void)
{
	_VetoWindowClose = false;

	produceWindowClosing();

	if(!_VetoWindowClose && getDrawingSurface() != NullFC)
	{
		getDrawingSurface()->closeWindow(InternalWindowPtr(this));
		produceWindowClosed();
	}
}

bool InternalWindow::giveFocus(ComponentPtr NewFocusedComponent, bool Temporary)
{
	if(ComponentPtr(this) == NewFocusedComponent)
    {
		return true;
    }
	else
	{
        beginEditCP(ComponentPtr(this), FocusedFieldMask);
           setFocused(false);
        endEditCP(ComponentPtr(this), FocusedFieldMask);
        focusLost(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, NewFocusedComponent));
		return true;
	}
}

bool InternalWindow::takeFocus(bool Temporary)
{
    
	if(getFocused() &&
	   getDrawingSurface() != NullFC &&
	   getDrawingSurface()->getFocusedWindow() == InternalWindowPtr(this))
	{
		return true;
	}
    beginEditCP(InternalWindowPtr(this), FocusedFieldMask);
       setFocused(true);
    endEditCP(InternalWindowPtr(this), FocusedFieldMask);
	if(Temporary || getDrawingSurface() == NullFC)
	{
        focusGained(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, NullFC));
	}
	else
	{
		if(getDrawingSurface()->getFocusedWindow() != NullFC)
		{
			getDrawingSurface()->getFocusedWindow()->giveFocus(InternalWindowPtr(this));
		}
	    getDrawingSurface()->setFocusedWindow(InternalWindowPtr(this));
        focusGained(FocusEvent::create(ComponentPtr(this),getSystemTime(),Temporary, getDrawingSurface()->getFocusedWindow()));
	}
	return true;
}

InternalWindowPtr &InternalWindow::getParentWindow(void)
{
    if(Component::getParentWindow() == NullFC)
    {
		beginEditCP(InternalWindowPtr(this), Component::ParentWindowFieldMask);
		   setParentWindow(InternalWindowPtr(this));
		endEditCP(InternalWindowPtr(this), Component::ParentWindowFieldMask);
    }
    return Component::editParentWindow();
}

const InternalWindowPtr &InternalWindow::getParentWindow(void) const
{
    if(Component::getParentWindow() == NullFC)
    {
        beginEditCP(InternalWindowPtr(this), Component::ParentWindowFieldMask);
            const_cast<InternalWindow*>(this)->setParentWindow(InternalWindowPtr(this));
        endEditCP(InternalWindowPtr(this), Component::ParentWindowFieldMask);
    }
    return Component::getParentWindow();
}

void InternalWindow::keyPressed(const KeyEventPtr e)
{
    if(!getLockInput())
    {
        //Check for Accelerator Keys
        UInt32 RelevantModifiers = (e->getModifiers() & KeyEvent::KEY_MODIFIER_ALT) |
                                   (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL) |
                                   (e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT) |
                                   (e->getModifiers() & KeyEvent::KEY_MODIFIER_META);
        KeyAcceleratorMapItor MapItor = _KeyAcceleratorMap.find(KeyEvent::getHashable(e->getKey(), RelevantModifiers));
        if(MapItor != _KeyAcceleratorMap.end())
        {
            (*MapItor).second->acceleratorTyped(KeyAcceleratorEvent::create(InternalWindowPtr(this), e->getTimeStamp(), e->getKey(), e->getModifiers()));
        }
	    //Send Key event to Component that has Focus
	    //If there is not Focused Component then do nothing
	    if(getFocusedComponent() != NullFC &&
	    getFocusedComponent() != ComponentPtr(this))
	    {
		    getFocusedComponent()->keyPressed(e);
		    ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		    while(ParentContainer != NullFC &&
			    ParentContainer != ContainerPtr(this))
		    {
			    ParentContainer->keyPressed(e);
			    ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		    }
	    }
        Component::keyPressed(e);
    }
}

void InternalWindow::keyReleased(const KeyEventPtr e)
{
    if(!getLockInput())
    {
	    //Send Key event to Component that has Focus
	    //If there is not Focused Component then do nothing
	    if(getFocusedComponent() != NullFC &&
	    getFocusedComponent() != ComponentPtr(this))
	    {
		    getFocusedComponent()->keyReleased(e);
		    ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		    while(ParentContainer != NullFC &&
			    ParentContainer != ContainerPtr(this))
		    {
			    ParentContainer->keyReleased(e);
			    ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		    }
	    }
        Component::keyReleased(e);
    }
}

void InternalWindow::keyTyped(const KeyEventPtr e)
{
    if(!getLockInput())
    {
	    //Send Key event to Component that has Focus
	    //If there is not Focused Component then do nothing
	    if(getFocusedComponent() != NullFC &&
	    getFocusedComponent() != ComponentPtr(this))
	    {
		    getFocusedComponent()->keyTyped(e);
		    ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		    while(ParentContainer != NullFC &&
			    ParentContainer != ContainerPtr(this))
		    {
			    ParentContainer->keyTyped(e);
			    ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		    }
	    }
        Component::keyTyped(e);
    }
}

void InternalWindow::mouseClicked(const MouseEventPtr e)
{
    if(!getLockInput())
    {
        if(getMenuBar() != NullFC)
        {
	        bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getMenuBar()->mouseClicked(e);
                Component::mouseClicked(e);
			    return;
		    }
        }
        if(getTitlebar() != NullFC)
        {
	        bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getTitlebar()->mouseClicked(e);
                Component::mouseClicked(e);
			    return;
		    }
        }
        Container::mouseClicked(e);
    }
}

void InternalWindow::mouseEntered(const MouseEventPtr e)
{
    if(getMenuBar() != NullFC)
    {
	    bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
    }
    if(getTitlebar() != NullFC)
    {
	    bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
    }
    if(!getLockInput())
    {
        Container::mouseEntered(e);
    }
}

void InternalWindow::mouseExited(const MouseEventPtr e)
{
    if(getMenuBar() != NullFC)
    {
	    bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
    }
    if(getTitlebar() != NullFC)
    {
	    bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
    }
    if(!getLockInput())
    {
		if(getDrawingSurface() != NullFC && getDrawingSurface()->getEventProducer() != NullFC)
		{
			getDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
		}
        Container::mouseExited(e);
    }
}

void InternalWindow::mousePressed(const MouseEventPtr e)
{
    
	if(!getLockInput())
    {
		
		//Check if the Mouse is whithin the resize border width
		if(getResizable())
		{
			WindowArea TheArea(getCursurArea(e->getLocation()));
			switch(TheArea)
			{
			case WINDOW_LEFT_BORDER:
			case WINDOW_RIGHT_BORDER:
			case WINDOW_TOP_BORDER:
			case WINDOW_BOTTOM_BORDER:
			case WINDOW_TOP_LEFT_BORDER:
			case WINDOW_BOTTOM_RIGHT_BORDER:
			case WINDOW_TOP_RIGHT_BORDER:
			case WINDOW_BOTTOM_LEFT_BORDER:
				beginEditCP(InternalWindowPtr(this), InternalWindow::LockInputFieldMask);
					setLockInput(true);
				endEditCP(InternalWindowPtr(this), InternalWindow::LockInputFieldMask);

				_BorderDraggedListener.setWindowStartPosition(getPosition());
				_BorderDraggedListener.setWindowStartSize(getSize());
				_BorderDraggedListener.setMouseStartPosition(e->getLocation());
				_BorderDraggedListener.setBorderDragged(TheArea);

				getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_BorderDraggedListener);
				getDrawingSurface()->getEventProducer()->addMouseListener(&_BorderDraggedListener);
				getDrawingSurface()->getEventProducer()->addKeyListener(&_BorderDraggedListener);
				break;
			}
		}
        if(getMenuBar() != NullFC)
        {
	        bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getMenuBar()->mousePressed(e);
                Component::mousePressed(e);
			    return;
		    }
        }
        if(getTitlebar() != NullFC)
        {
	        bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getTitlebar()->mousePressed(e);
                Component::mousePressed(e);
			    return;
		    }
        }

		//Container MousePressed Handling
		bool isContained(false);
		for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
		{
			isContained = getChildren()[i]->isContained(e->getLocation(), true);
			checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
			if(isContained)
			{
				takeFocus();
				if(!getChildren()[i]->getType().isDerivedFrom(Container::getClassType()))
				{
					getChildren()[i]->takeFocus();
				}
				getChildren()[i]->mousePressed(e);
				break;
			}
		}
		Component::mousePressed(e);
    }
}

void InternalWindow::mouseReleased(const MouseEventPtr e)
{
    if(!getLockInput())
    {
        if(getMenuBar() != NullFC)
        {
	        bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getMenuBar()->mouseReleased(e);
                Component::mouseReleased(e);
			    return;
		    }
        }
        if(getTitlebar() != NullFC)
        {
	        bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
		    checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
		    if(isContained)
		    {
			    getTitlebar()->mouseReleased(e);
                Component::mouseReleased(e);
			    return;
		    }
        }
        Container::mouseReleased(e);
    }
}

void InternalWindow::getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	if(getDrawDecorations() && getDrawTitlebar() && getDrawnBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
	{
		WindowBorder::Ptr::dcast(getDrawnBorder())->getTitlebarBounds(0, 0, getSize().x(), getSize().y(), TopLeft, BottomRight);
	}
	else
	{
		TopLeft.setValues(0,0);
		BottomRight.setValues(0,0);
	}
}

InternalWindow::WindowArea InternalWindow::getCursurArea(const Pnt2f& DrawingSurfaceLocation) const
{
	Pnt2f LocationInWindow(DrawingSurfaceToComponent(DrawingSurfaceLocation, InternalWindowPtr(this)));
	if(LocationInWindow.x() < 0 ||
	   LocationInWindow.x() > getSize().x() ||
	   LocationInWindow.y() < 0 ||
	   LocationInWindow.y() > getSize().y())
	{
		return WINDOW_OUTSIDE;
	}
	else
	{
		if(getDrawDecorations())
		{
			Pnt2f TitlebarTopLeft, TitlebarBottomRight;
			getTitlebarBounds(TitlebarTopLeft, TitlebarBottomRight);
			//Borders
			if(LocationInWindow.x() < getResizeModifyCursorWidth() || 
				LocationInWindow.y() < getResizeModifyCursorWidth() ||
				LocationInWindow.x() > (getSize().x() - getResizeModifyCursorWidth()) || 
				LocationInWindow.y() > (getSize().y() - getResizeModifyCursorWidth()))
			{
				//Top Left
				if(LocationInWindow.x() >= 0 &&
				   LocationInWindow.x() < getResizeModifyCursorWidth() &&
				   LocationInWindow.y() >= 0 &&
				   LocationInWindow.y() < getResizeModifyCursorWidth())
				{
					return WINDOW_TOP_LEFT_BORDER;
				}
				//Bottom Right
				else if(LocationInWindow.x() >= getSize().x() - getResizeModifyCursorWidth() &&
				   LocationInWindow.x() < getSize().x() &&
				   LocationInWindow.y() >= getSize().y() - getResizeModifyCursorWidth() &&
				   LocationInWindow.y() < getSize().y())
				{
					return WINDOW_BOTTOM_RIGHT_BORDER;
				}
				//Top Right
				else if(LocationInWindow.x() >= getSize().x() - getResizeModifyCursorWidth() &&
				   LocationInWindow.x() < getSize().x() &&
				   LocationInWindow.y() >= 0 &&
				   LocationInWindow.y() < getResizeModifyCursorWidth())
				{
					return WINDOW_TOP_RIGHT_BORDER;
				}
				//Bottom Left
				else if(LocationInWindow.x() >= 0 &&
				   LocationInWindow.x() < getResizeModifyCursorWidth() &&
				   LocationInWindow.y() >= getSize().y() - getResizeModifyCursorWidth() &&
				   LocationInWindow.y() < getSize().y())
				{
					return WINDOW_BOTTOM_LEFT_BORDER;
				}
				//Left
				else if(LocationInWindow.x() >= 0 &&
					   LocationInWindow.x() < getResizeModifyCursorWidth() &&
					   LocationInWindow.y() >= getResizeModifyCursorWidth() &&
					   LocationInWindow.y() < getSize().y() - getResizeModifyCursorWidth())
				{
					return WINDOW_LEFT_BORDER;
				}
				//Right
				else if(LocationInWindow.x() >= getSize().x() - getResizeModifyCursorWidth() &&
					   LocationInWindow.x() < getSize().x() &&
					   LocationInWindow.y() >= getResizeModifyCursorWidth() &&
					   LocationInWindow.y() < getSize().y() - getResizeModifyCursorWidth())
				{
					return WINDOW_RIGHT_BORDER;
				}
				//Top
				else if(LocationInWindow.x() >= getResizeModifyCursorWidth() &&
					   LocationInWindow.x() < getSize().x() - getResizeModifyCursorWidth() &&
					   LocationInWindow.y() >= 0 &&
					   LocationInWindow.y() < getResizeModifyCursorWidth())
				{
					return WINDOW_TOP_BORDER;
				}
				//Bottom
				else if(
					   (LocationInWindow.x() >= getResizeModifyCursorWidth() &&
					   LocationInWindow.x() < getSize().x() - getResizeModifyCursorWidth() &&
					   LocationInWindow.y() >= getSize().y() - getResizeModifyCursorWidth() &&
					   LocationInWindow.y() < getSize().y()))
				{
					return WINDOW_BOTTOM_BORDER;
				}
			}
			//Title bar
			else if(getDrawTitlebar() && isContainedBounds(LocationInWindow, TitlebarTopLeft, TitlebarBottomRight))
			{
				return WINDOW_TITLE_BAR;
			}
			//Main Panel
			else
			{
				return WINDOW_MAIN_PANEL;
			}
		}
		else
		{
			return WINDOW_MAIN_PANEL;
		}
	}
}

void InternalWindow::mouseMoved(const MouseEventPtr e)
{

    if(getMenuBar() != NullFC)
    {
	    bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
		if(isContained)
		{
			getMenuBar()->mouseMoved(e);
            Component::mouseMoved(e);
			return;
		}
    }
    if(getTitlebar() != NullFC)
    {
	    bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
		if(isContained)
		{
			getTitlebar()->mouseMoved(e);
            Component::mouseMoved(e);
			return;
		}
    }
    if(!getLockInput())
    {
        Container::mouseMoved(e);
    }
}

UInt32 InternalWindow::queryCursor(const Pnt2f& CursorLoc) const
{
    if(!getLockInput() && getResizable())
    {
		//Check if the Mouse is whithin the resize border width
		WindowArea TheArea(getCursurArea(CursorLoc));
		switch(TheArea)
		{
		case WINDOW_LEFT_BORDER:
		case WINDOW_RIGHT_BORDER:
			return WindowEventProducer::CURSOR_RESIZE_W_TO_E;
			break;

		case WINDOW_TOP_BORDER:
		case WINDOW_BOTTOM_BORDER:
			return WindowEventProducer::CURSOR_RESIZE_N_TO_S;
			break;
			
		case WINDOW_TOP_LEFT_BORDER:
		case WINDOW_BOTTOM_RIGHT_BORDER:
			return WindowEventProducer::CURSOR_RESIZE_NW_TO_SE;
			break;
			
		case WINDOW_TOP_RIGHT_BORDER:
		case WINDOW_BOTTOM_LEFT_BORDER:
			return WindowEventProducer::CURSOR_RESIZE_SW_TO_NE;
			break;

		case WINDOW_OUTSIDE:
		case WINDOW_MAIN_PANEL:
		case WINDOW_TITLE_BAR:
			return WindowEventProducer::CURSOR_POINTER;
			break;
		}
    }

    return Inherited::queryCursor(CursorLoc);
}

void InternalWindow::mouseDragged(const MouseEventPtr e)
{
    if(getMenuBar() != NullFC)
    {
	    bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
		if(isContained)
		{
			getMenuBar()->mouseDragged(e);
            Component::mouseDragged(e);
			return;
		}
    }
    if(getTitlebar() != NullFC)
    {
	    bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
		if(isContained)
		{
			getTitlebar()->mouseDragged(e);
            Component::mouseDragged(e);
			return;
		}
    }
    if(!getLockInput())
    {
        Container::mouseDragged(e);
    }
}

void InternalWindow::mouseWheelMoved(const MouseWheelEventPtr e)
{
    if(!getLockInput())
    {
        Container::mouseWheelMoved(e);
    }
}

void InternalWindow::drawInternal(const GraphicsPtr TheGraphics, Real32 Opacity) const
{
    Inherited::drawInternal(TheGraphics, Opacity);

    //If I have an active TitleBar then draw it
    if(getDrawDecorations() && getDrawTitlebar() && getTitlebar() != NullFC)
    {
        getTitlebar()->draw(TheGraphics, Opacity*getOpacity());
    }

    //If I have a MenuBar then Draw it
    if(getMenuBar() != NullFC)
    {
        getMenuBar()->draw(TheGraphics, Opacity*getOpacity());
    }
}

void InternalWindow::drawUnclipped(const GraphicsPtr TheGraphics, Real32 Opacity) const
{
    Inherited::drawUnclipped(TheGraphics, Opacity);
        
    //If I have an active tooltip then draw it
    if(getActiveToolTip() != NullFC)
    {
        getActiveToolTip()->draw(TheGraphics, Opacity*getOpacity());
    }
    
    //If I have an active popupMenu then draw it
    for(UInt32 i(0) ; i<getActivePopupMenus().size() ; ++i)
    {
        getActivePopupMenus()[i]->draw(TheGraphics, Opacity*getOpacity());
    }
}

void InternalWindow::destroyPopupMenu(void)
{
    if(getActivePopupMenus().size() > 0)
    {
        for(UInt32 i(0) ; i<getActivePopupMenus().size() ; ++i)
        {
            getActivePopupMenus()[i]->cancel();
        }
        
        beginEditCP(InternalWindowPtr(this), ActivePopupMenusFieldMask | LockInputFieldMask);
            getActivePopupMenus().clear();
            setLockInput(false);
        endEditCP(InternalWindowPtr(this), ActivePopupMenusFieldMask | LockInputFieldMask);

        _PopupMenuInteractionListener.disconnect();
    }
}

void InternalWindow::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    destroyPopupMenu();
    _TitlebarDraggedListener.disconnect();
    _BorderDraggedListener.disconnect();
}


void InternalWindow::getMenuBarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    //Get Insets Bounds
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    Container::getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    TopLeft = InsetsTopLeft;
    if(getMenuBar() == NullFC)
    {
        BottomRight = TopLeft;
    }
    else
    {
        Pnt2f MenuBarTopLeft, MenuBarBottomRight;
        getMenuBar()->getBounds(MenuBarTopLeft, MenuBarBottomRight);
        BottomRight = TopLeft + Vec2f((InsetsBottomRight.x() - InsetsTopLeft.x()), (MenuBarBottomRight.y() - MenuBarTopLeft.y()));
    }
}

void InternalWindow::getContentPaneBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    //Get Insets Bounds
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    Container::getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    BottomRight = InsetsBottomRight;
    if(getMenuBar() == NullFC)
    {
        TopLeft = InsetsTopLeft;
    }
    else
    {
        Pnt2f MenuBarTopLeft, MenuBarBottomRight;
        getMenuBar()->getBounds(MenuBarTopLeft, MenuBarBottomRight);
        TopLeft = InsetsTopLeft + Vec2f(0, (MenuBarBottomRight.y() - MenuBarTopLeft.y()));
    }
}

void InternalWindow::getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    getContentPaneBounds(TopLeft, BottomRight);
}

void InternalWindow::updateLayout(void)
{
    //If I have a MenuBar Update it's layout
    if(getMenuBar() != NullFC)
    {
        Pnt2f MenuTopLeft, MenuBottomRight;
        getMenuBar()->updateLayout();
        getMenuBarBounds(MenuTopLeft, MenuBottomRight);
        beginEditCP(getMenuBar(), MenuBar::PositionFieldMask | MenuBar::SizeFieldMask);
			getMenuBar()->setPosition(MenuTopLeft);
			getMenuBar()->setSize(Vec2f( MenuBottomRight.x() - MenuTopLeft.x(), getMenuBar()->getPreferredSize().y()));
        endEditCP(getMenuBar(), MenuBar::PositionFieldMask | MenuBar::SizeFieldMask);
    }

    //If I have a Titlebar then update it's layout
    if(getDrawDecorations() && getDrawTitlebar() && getTitlebar() != NullFC)
    {
		Pnt2f TitlebarTopLeft, TitlebarBottomRight;
		getTitlebarBounds(TitlebarTopLeft, TitlebarBottomRight);
		beginEditCP(getTitlebar(), Titlebar::PositionFieldMask | Titlebar::SizeFieldMask);
			getTitlebar()->setPosition(TitlebarTopLeft);
			getTitlebar()->setSize(Vec2f( TitlebarBottomRight.x() - TitlebarTopLeft.x(), getTitlebar()->getPreferredSize().y()));
		endEditCP(getTitlebar(), Titlebar::PositionFieldMask | Titlebar::SizeFieldMask);
    }

    Container::updateLayout();
}

EventConnection InternalWindow::addKeyAccelerator(KeyEvent::Key TheKey, UInt32 Modifiers, KeyAcceleratorListenerPtr Listener)
{
    _KeyAcceleratorMap[KeyEvent::getHashable(TheKey, Modifiers)] = Listener;
   return EventConnection(
       boost::bind(&InternalWindow::isKeyAcceleratorAttached, this, TheKey, Modifiers),
       boost::bind(&InternalWindow::removeKeyAccelerator, this, TheKey, Modifiers));
}

void InternalWindow::removeKeyAccelerator(KeyEvent::Key TheKey, UInt32 Modifiers)
{
    _KeyAcceleratorMap.erase(KeyEvent::getHashable(TheKey, Modifiers));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InternalWindow::InternalWindow(void) :
    Inherited(),
    _PopupMenuInteractionListener(InternalWindowPtr(this)),
	_TitlebarStartDragListener(InternalWindowPtr(this)),
	_TitlebarDraggedListener(InternalWindowPtr(this)),
	_BorderDraggedListener(InternalWindowPtr(this)),
	_CloseButtonListener(InternalWindowPtr(this)),
	_MaximizeButtonListener(InternalWindowPtr(this)),
	_IconifyButtonListener(InternalWindowPtr(this))
{
}

InternalWindow::InternalWindow(const InternalWindow &source) :
    Inherited(source),
    _PopupMenuInteractionListener(InternalWindowPtr(this)),
	_TitlebarStartDragListener(InternalWindowPtr(this)),
	_TitlebarDraggedListener(InternalWindowPtr(this)),
	_BorderDraggedListener(InternalWindowPtr(this)),
	_CloseButtonListener(InternalWindowPtr(this)),
	_MaximizeButtonListener(InternalWindowPtr(this)),
	_IconifyButtonListener(InternalWindowPtr(this))
{
    if(getTitlebar() != NullFC)
    {
        beginEditCP(InternalWindowPtr(this), TitlebarFieldMask);
			setTitlebar(Titlebar::Ptr::dcast(getTitlebar()->shallowCopy()));
        endEditCP(InternalWindowPtr(this), TitlebarFieldMask);
    }
    if(getBorder() != NullFC)
    {
        beginEditCP(InternalWindowPtr(this), BorderFieldMask);
			setBorder(Border::Ptr::dcast(getBorder()->shallowCopy()));
        endEditCP(InternalWindowPtr(this), BorderFieldMask);
    }
    if(getDisabledBorder() != NullFC)
    {
        beginEditCP(InternalWindowPtr(this), DisabledBorderFieldMask);
			setDisabledBorder(Border::Ptr::dcast(getDisabledBorder()->shallowCopy()));
        endEditCP(InternalWindowPtr(this), DisabledBorderFieldMask);
    }
    if(getFocusedBorder() != NullFC)
    {
        beginEditCP(InternalWindowPtr(this), FocusedBorderFieldMask);
			setFocusedBorder(Border::Ptr::dcast(getFocusedBorder()->shallowCopy()));
        endEditCP(InternalWindowPtr(this), FocusedBorderFieldMask);
    }
    if(getRolloverBorder() != NullFC)
    {
        beginEditCP(InternalWindowPtr(this), RolloverBorderFieldMask);
			setRolloverBorder(Border::Ptr::dcast(getRolloverBorder()->shallowCopy()));
        endEditCP(InternalWindowPtr(this), RolloverBorderFieldMask);
    }
}

InternalWindow::~InternalWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InternalWindow::changed(BitVector whichField, UInt32 origin)
{
	
	if( ((whichField & FocusedFieldMask) ||
		(whichField & TitlebarFieldMask))&&
		getTitlebar() != NullFC)
	{
		beginEditCP(getTitlebar(), Titlebar::EnabledFieldMask);
			getTitlebar()->setEnabled(getFocused());
		endEditCP(getTitlebar(), Titlebar::EnabledFieldMask);
	}

    if( (whichField & ActiveToolTipFieldMask) &&
        getActiveToolTip() != NullFC)
    {
        getActiveToolTip()->updateClipBounds();
    }
    
    if( (whichField & ActivePopupMenusFieldMask) &&
        getActivePopupMenus().size() > 0)
    {
        for(UInt32 i(0) ; i<getActivePopupMenus().size() ; ++i)
        {
            beginEditCP(getActivePopupMenus()[i], PopupMenu::ParentContainerFieldMask | PopupMenu::ParentWindowFieldMask);
                getActivePopupMenus()[i]->setParentContainer(ContainerPtr(this));
                getActivePopupMenus()[i]->setParentWindow(InternalWindowPtr(this));
            endEditCP(getActivePopupMenus()[i], PopupMenu::ParentContainerFieldMask | PopupMenu::ParentWindowFieldMask);
        }
        
        getDrawingSurface()->getEventProducer()->addMouseListener(&_PopupMenuInteractionListener);
        getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_PopupMenuInteractionListener);
        getDrawingSurface()->getEventProducer()->addKeyListener(&_PopupMenuInteractionListener);
        beginEditCP(InternalWindowPtr(this), LockInputFieldMask);
            setLockInput(true);
        endEditCP(InternalWindowPtr(this), LockInputFieldMask);
    }

    if( (whichField & MenuBarFieldMask) && getMenuBar() != NullFC)
    {
		beginEditCP(getMenuBar(), MenuBar::ParentContainerFieldMask | MenuBar::ParentWindowFieldMask);
            getMenuBar()->setParentContainer(ContainerPtr(this));
            getMenuBar()->setParentWindow(InternalWindowPtr(this));
        endEditCP(getMenuBar(), MenuBar::ParentContainerFieldMask | MenuBar::ParentWindowFieldMask);
    }

    if( (whichField & MenuBarFieldMask) || (whichField & TitlebarFieldMask))
    {
        updateLayout();
    }

	if( (whichField & TitleFieldMask) && getTitlebar() != NullFC)
	{
		getTitlebar()->setTitle(getTitle());
	}
	
    if( (whichField & TitlebarFieldMask) && getTitlebar() != NullFC)
    {
		beginEditCP(getTitlebar(), Panel::ParentContainerFieldMask | Panel::ParentWindowFieldMask);
            getTitlebar()->setParentContainer(ContainerPtr(this));
            getTitlebar()->setParentWindow(InternalWindowPtr(this));
        endEditCP(getTitlebar(), Panel::ParentContainerFieldMask | Panel::ParentWindowFieldMask);
    }

	if((whichField & TitlebarFieldMask) ||
	   (whichField & BorderFieldMask) ||
	   (whichField & DisabledBorderFieldMask) ||
	   (whichField & FocusedBorderFieldMask) ||
	   (whichField & RolloverBorderFieldMask) ||
	   (whichField & DrawTitlebarFieldMask))
	{
		TitlebarPtr TheTitlebar;
		if(getDrawTitlebar())
		{
			TheTitlebar = getTitlebar();
		}
		else
		{
			TheTitlebar = NullFC;
		}

		if(getBorder() != NullFC && getBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
		{
			WindowBorder::Ptr::dcast(getBorder())->setTitlebar(TheTitlebar);
		}
		if(getDisabledBorder() != NullFC && getDisabledBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
		{
			WindowBorder::Ptr::dcast(getDisabledBorder())->setTitlebar(TheTitlebar);
		}
		if(getFocusedBorder() != NullFC && getFocusedBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
		{
			WindowBorder::Ptr::dcast(getFocusedBorder())->setTitlebar(TheTitlebar);
		}
		if(getRolloverBorder() != NullFC && getRolloverBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
		{
			WindowBorder::Ptr::dcast(getRolloverBorder())->setTitlebar(TheTitlebar);
		}
	}
	
    if( whichField & ClipBoundsFieldMask)
	{
		if(getTitlebar() != NullFC)
		{
			getTitlebar()->updateClipBounds();
		}
	}

	if( (whichField & TitlebarFieldMask) &&
		getTitlebar() != NullFC)
	{
		if(getTitlebar()->getTitleLabel() != NullFC)
		{
			getTitlebar()->getTitleLabel()->addMouseListener(&_TitlebarStartDragListener);
		}
		if(getTitlebar()->getCloseButton() != NullFC)
		{
			getTitlebar()->getCloseButton()->addActionListener(&_CloseButtonListener);
		}
		if(getTitlebar()->getMaximizeButton() != NullFC)
		{
			getTitlebar()->getMaximizeButton()->addActionListener(&_MaximizeButtonListener);
		}
		if(getTitlebar()->getIconifyButton() != NullFC)
		{
			getTitlebar()->getIconifyButton()->addActionListener(&_IconifyButtonListener);
		}
	}

	if( (whichField & IconableFieldMask) &&
		getTitlebar() != NullFC)
	{
		beginEditCP(getTitlebar(), Titlebar::DrawIconifyFieldMask);
			getTitlebar()->setDrawIconify(getIconable());
		endEditCP(getTitlebar(), Titlebar::DrawIconifyFieldMask);
	}
	if( (whichField & MaximizableFieldMask) &&
		getTitlebar() != NullFC)
	{
		beginEditCP(getTitlebar(), Titlebar::DrawMaximizeFieldMask);
			getTitlebar()->setDrawMaximize(getMaximizable());
		endEditCP(getTitlebar(), Titlebar::DrawMaximizeFieldMask);
	}
	if( (whichField & ClosableFieldMask) &&
		getTitlebar() != NullFC)
	{
		beginEditCP(getTitlebar(), Titlebar::DrawCloseFieldMask);
			getTitlebar()->setDrawClose(getClosable());
		endEditCP(getTitlebar(), Titlebar::DrawCloseFieldMask);
	}

    Inherited::changed(whichField, origin);
}

void InternalWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump InternalWindow NI" << std::endl;
}


void InternalWindow::PopupMenuInteractionListener::mouseClicked(const MouseEventPtr e)
{
    for(Int32 i(_InternalWindow->getActivePopupMenus().size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus()[i]->isContained(e->getLocation(), true);
		_InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus()[i],isContained,e->getViewport());
		if(isContained)
        {
			_InternalWindow->getActivePopupMenus()[i]->mouseClicked(e);
            return;
        }
    }
	//_InternalWindow->destroyPopupMenu();
}

void InternalWindow::PopupMenuInteractionListener::mousePressed(const MouseEventPtr e)
{
    for(Int32 i(_InternalWindow->getActivePopupMenus().size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus()[i]->isContained(e->getLocation(), true);
		_InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus()[i],isContained,e->getViewport());
		if(isContained)
        {
			_InternalWindow->getActivePopupMenus()[i]->mousePressed(e);
            return;
        }
    }
    _InternalWindow->destroyPopupMenu();
}

void InternalWindow::PopupMenuInteractionListener::mouseReleased(const MouseEventPtr e)
{
    for(Int32 i(_InternalWindow->getActivePopupMenus().size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus()[i]->isContained(e->getLocation(), true);
		_InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus()[i],isContained,e->getViewport());
		if(isContained)
		{
			_InternalWindow->getActivePopupMenus()[i]->mouseReleased(e);
            return;
		}
    }
}

void InternalWindow::PopupMenuInteractionListener::mouseMoved(const MouseEventPtr e)
{
    for(Int32 i(_InternalWindow->getActivePopupMenus().size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus()[i]->isContained(e->getLocation(), true);
		_InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus()[i],isContained,e->getViewport());
		if(isContained)
		{
			_InternalWindow->getActivePopupMenus()[i]->mouseMoved(e);
            return;
		}
    }
}

void InternalWindow::PopupMenuInteractionListener::mouseDragged(const MouseEventPtr e)
{
    for(Int32 i(_InternalWindow->getActivePopupMenus().size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus()[i]->isContained(e->getLocation(), true);
		_InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus()[i],isContained,e->getViewport());
		if(isContained)
		{
			_InternalWindow->getActivePopupMenus()[i]->mouseDragged(e);
            return;
		}
    }
}

void InternalWindow::PopupMenuInteractionListener::keyPressed(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        _InternalWindow->destroyPopupMenu();
    }
    else if(e->getKey() == KeyEvent::KEY_UP)
    {
        _InternalWindow->getActivePopupMenus().front()->setSelection( _InternalWindow->getActivePopupMenus().front()->getSelectionIndex() -1 );
    }
    else if(e->getKey() == KeyEvent::KEY_DOWN)
    {
        _InternalWindow->getActivePopupMenus().front()->setSelection( _InternalWindow->getActivePopupMenus().front()->getSelectionIndex() +1 );
    }
    else if(e->getKey() == KeyEvent::KEY_ENTER && _InternalWindow->getActivePopupMenus().front()->getItem(_InternalWindow->getActivePopupMenus().front()->getSelectionIndex()) != NullFC)
    {
        _InternalWindow->getActivePopupMenus().front()->getItem(_InternalWindow->getActivePopupMenus().front()->getSelectionIndex())->activate();
        _InternalWindow->destroyPopupMenu();
    }
}

void InternalWindow::PopupMenuInteractionListener::disconnect(void)
{
    //Remove the listener
    if(_InternalWindow->getDrawingSurface()->getEventProducer() != NullFC)
    {
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
    }
}

void InternalWindow::TitlebarStartDragListener::mousePressed(const MouseEventPtr e)
{
	_InternalWindow->_TitlebarDraggedListener.setWindowStartPosition(_InternalWindow->getPosition());
	_InternalWindow->_TitlebarDraggedListener.setMouseStartPosition(e->getLocation());

	_InternalWindow->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
	_InternalWindow->getDrawingSurface()->getEventProducer()->addMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
	_InternalWindow->getDrawingSurface()->getEventProducer()->addKeyListener(&(_InternalWindow->_TitlebarDraggedListener));
}

void InternalWindow::TitlebarDraggedListener::mouseReleased(const MouseEventPtr e)
{
	if(_InternalWindow->getDrawingSurface() != NullFC)
	{
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_TitlebarDraggedListener));
		
		beginEditCP(_InternalWindow, InternalWindow::LockInputFieldMask);
			_InternalWindow->setLockInput(false);
		endEditCP(_InternalWindow, InternalWindow::LockInputFieldMask);
	}
}

void InternalWindow::TitlebarDraggedListener::mouseDragged(const MouseEventPtr e)
{
	beginEditCP(_InternalWindow, InternalWindow::PositionFieldMask);
		_InternalWindow->setPosition( _WindowStartPosition - (_MouseStartPosition - e->getLocation()) );
	endEditCP(_InternalWindow, InternalWindow::PositionFieldMask);
}

void InternalWindow::TitlebarDraggedListener::keyPressed(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        disconnect();

		//Reset the Window to it's original Position
		beginEditCP(_InternalWindow, InternalWindow::PositionFieldMask);
			_InternalWindow->setPosition(_WindowStartPosition);
		endEditCP(_InternalWindow, InternalWindow::PositionFieldMask);
    }
}

void InternalWindow::TitlebarDraggedListener::disconnect(void)
{
	if(_InternalWindow->getParentWindow() != NullFC)
	{
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_TitlebarDraggedListener));

        beginEditCP(_InternalWindow,InternalWindow::LockInputFieldMask);
            _InternalWindow->setLockInput(false);
        endEditCP(_InternalWindow, InternalWindow::LockInputFieldMask);
    }
}

void InternalWindow::BorderDraggedListener::disconnect(void)
{
	if(_InternalWindow->getParentWindow() != NullFC)
	{
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_BorderDraggedListener));
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_BorderDraggedListener));
		_InternalWindow->getDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_BorderDraggedListener));
		
		beginEditCP(_InternalWindow, InternalWindow::LockInputFieldMask);
			_InternalWindow->setLockInput(false);
		endEditCP(_InternalWindow, InternalWindow::LockInputFieldMask);
	}
}

void InternalWindow::BorderDraggedListener::mouseReleased(const MouseEventPtr e)
{
    disconnect();
}

void InternalWindow::BorderDraggedListener::mouseDragged(const MouseEventPtr e)
{
	Vec2f Size;
	bool PositionChange;
	Pnt2f Position;
	Pnt2f BottomRight(_InternalWindow->getPosition() + _InternalWindow->getSize());
	switch(_BorderDragged)
	{
	case WINDOW_LEFT_BORDER:
		Size.setValues(BottomRight.x() - e->getLocation().x(), _InternalWindow->getPreferredSize().y());
		PositionChange = true;
		Position = BottomRight - Size;
		break;
	case WINDOW_RIGHT_BORDER:
		PositionChange = false;
		Size.setValues(e->getLocation().x() - _InternalWindow->getPosition().x(), _InternalWindow->getPreferredSize().y());
		break;
	case WINDOW_TOP_BORDER:
		Size.setValues(_InternalWindow->getPreferredSize().x(), BottomRight.y() - e->getLocation().y());
		PositionChange = true;
		Position = BottomRight - Size;
		break;
	case WINDOW_BOTTOM_BORDER:
		PositionChange = false;
		Size.setValues(_InternalWindow->getPreferredSize().x(), e->getLocation().y() - _InternalWindow->getPosition().y());
		break;
	case WINDOW_TOP_LEFT_BORDER:
		Size.setValues(BottomRight.x() - e->getLocation().x(), BottomRight.y() - e->getLocation().y());
		PositionChange = true;
		Position = BottomRight - Size;
		break;
	case WINDOW_BOTTOM_RIGHT_BORDER:
		PositionChange = false;
		Size.setValues(e->getLocation().x() - _InternalWindow->getPosition().x(), e->getLocation().y() - _InternalWindow->getPosition().y());
		break;
	case WINDOW_TOP_RIGHT_BORDER:
		Size.setValues(e->getLocation().x() - _InternalWindow->getPosition().x(), BottomRight.y() - e->getLocation().y());
		PositionChange = true;
		Position.setValues(_InternalWindow->getPosition().x(), BottomRight.y() - Size.y());
		break;
	case WINDOW_BOTTOM_LEFT_BORDER:
		Size.setValues(BottomRight.x() - e->getLocation().x(), e->getLocation().y() - _InternalWindow->getPosition().y());
		PositionChange = true;
		Position.setValues( BottomRight.x() - Size.x(), _InternalWindow->getPosition().y());
		break;
	}

	if(PositionChange)
	{
		beginEditCP(_InternalWindow, InternalWindow::PreferredSizeFieldMask | InternalWindow::PositionFieldMask);
			_InternalWindow->setPreferredSize(Size);
			_InternalWindow->setPosition(Position);
		endEditCP(_InternalWindow, InternalWindow::PreferredSizeFieldMask | InternalWindow::PositionFieldMask);
	}
	else
	{
		beginEditCP(_InternalWindow, InternalWindow::PreferredSizeFieldMask);
			_InternalWindow->setPreferredSize(Size);
		endEditCP(_InternalWindow, InternalWindow::PreferredSizeFieldMask);
	}
}


void InternalWindow::BorderDraggedListener::keyPressed(const KeyEventPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        disconnect();

		//Reset the Window to it's original Position and size
		beginEditCP(_InternalWindow, InternalWindow::PositionFieldMask | InternalWindow::SizeFieldMask);
			_InternalWindow->setPosition(_WindowStartPosition);
			_InternalWindow->setSize(_WindowStartSize);
		endEditCP(_InternalWindow, InternalWindow::PositionFieldMask | InternalWindow::SizeFieldMask);
    }
}

void InternalWindow::CloseButtonListener::actionPerformed(const ActionEventPtr e)
{
	_InternalWindow->close();
}

void InternalWindow::MaximizeButtonListener::actionPerformed(const ActionEventPtr e)
{
	_InternalWindow->setMaximize(!_InternalWindow->getMaximize());
}

void InternalWindow::IconifyButtonListener::actionPerformed(const ActionEventPtr e)
{
	_InternalWindow->setIconify(true);
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
    static Char8 cvsid_hpp       [] = OSGINTERNALWINDOWBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGINTERNALWINDOWBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGINTERNALWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

