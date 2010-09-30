/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGConfig.h"

#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGToolTip.h"
#include "OSGPopupMenu.h"
#include "OSGMenuBar.h"
#include "OSGLabel.h"
#include "OSGButton.h"
#include "OSGTitlebar.h"
#include "OSGWindowBorder.h"
#include "OSGUIDrawUtils.h"
#include "OSGWindowEventProducer.h"
#include "OSGMenuItem.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGInternalWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGInternalWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InternalWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void InternalWindow::setIconify(bool Iconify)
{
    if(Iconify && !getIsIcon())
    {
        //TODO: Implement
        setIsIcon(Iconify);

        produceWindowIconified();
    }
    else if(!Iconify && getIsIcon())
    {
        //TODO: Implement
        setIsIcon(Iconify);

        produceWindowDeiconified();
    }
}

void InternalWindow::updateContainerLayout(void)
{
    if(getParentDrawingSurface() != NULL)
    {
		getParentDrawingSurface()->updateWindowLayout(this);
    }
	else if(getSize() != getPreferredSize())
	{
        Inherited::updateContainerLayout();
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
        _PreviousPosition = getPosition();
        _PreviousSize = getSize();
        setIsMaximized(Maximize);
        setPosition(Pnt2f(0,0));
        setPreferredSize(Vec2f(getParentDrawingSurface()->getSize().x(),getParentDrawingSurface()->getSize().x()));
    }
    else if(!Maximize && getIsMaximized())
    {
        setIsMaximized(Maximize);
        Vec2f TempSize(_PreviousSize);
        Pnt2f TempPos(_PreviousPosition);
        setPreferredSize(TempSize);
        setPosition(TempPos);
        _PreviousPosition = getPosition();
        _PreviousSize = getSize();
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

    if(!_VetoWindowClose && getParentDrawingSurface() != NULL)
    {
        getParentDrawingSurface()->closeWindow(this);
        produceWindowClosed();
    }
}

bool InternalWindow::giveFocus(Component* const NewFocusedComponent, bool Temporary)
{
    if(this == NewFocusedComponent)
    {
        return true;
    }
    else
    {
        setFocused(false);
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, NewFocusedComponent));
        focusLost(Details);
        return true;
    }
}

bool InternalWindow::takeFocus(bool Temporary)
{

    if(getFocused() &&
       getParentDrawingSurface() != NULL &&
       getParentDrawingSurface()->getFocusedWindow() == this)
    {
        return true;
    }
    setFocused(true);
    if(Temporary || getParentDrawingSurface() == NULL)
    {
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, NULL));

        focusGained(Details);
    }
    else
    {
        if(getParentDrawingSurface()->getFocusedWindow() != NULL)
        {
            getParentDrawingSurface()->getFocusedWindow()->giveFocus(this);
        }
        getParentDrawingSurface()->setFocusedWindow(this);
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, getParentDrawingSurface()->getFocusedWindow()));
        focusGained(Details);
    }
    return true;
}

InternalWindow* InternalWindow::getParentWindow(void) const
{
    if(_ParentWindow != this)
    {
        const_cast<InternalWindow*>(this)->_ParentWindow = const_cast<InternalWindow*>(this);
    }
    return _ParentWindow;
}

void InternalWindow::setParentWindow(InternalWindow* const parent)
{
    _ParentWindow = this;
}

void InternalWindow::keyPressed(KeyEventDetails* const e)
{
    if(!getLockInput())
    {
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyPressed(e);
            if(e->isConsumed()) return;
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyPressed(e);
                if(e->isConsumed()) return;
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyPressed(e);
    }
}

void InternalWindow::keyReleased(KeyEventDetails* const e)
{
    if(!getLockInput())
    {
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyReleased(e);
            if(e->isConsumed()) return;
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyReleased(e);
                if(e->isConsumed()) return;
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyReleased(e);
    }
}

void InternalWindow::keyTyped(KeyEventDetails* const e)
{
    if(!getLockInput())
    {
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyTyped(e);
            if(e->isConsumed()) return;
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyTyped(e);
                if(e->isConsumed()) return;
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyTyped(e);
    }
}

void InternalWindow::mouseClicked(MouseEventDetails* const e)
{
    if(!getLockInput())
    {
        if(getMenuBar() != NULL)
        {
            bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
            if(isContained)
            {
                getMenuBar()->mouseClicked(e);
                if(e->isConsumed()) return;
                Component::mouseClicked(e);
                return;
            }
        }
        if(getTitlebar() != NULL)
        {
            bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
            if(isContained)
            {
                getTitlebar()->mouseClicked(e);
                if(e->isConsumed()) return;
                Component::mouseClicked(e);
                return;
            }
        }
        ComponentContainer::mouseClicked(e);
    }
}

void InternalWindow::mouseEntered(MouseEventDetails* const e)
{
    if(getMenuBar() != NULL)
    {
        bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
    }
    if(getTitlebar() != NULL)
    {
        bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
    }
    if(!getLockInput())
    {
        ComponentContainer::mouseEntered(e);
    }
}

void InternalWindow::mouseExited(MouseEventDetails* const e)
{
    if(getMenuBar() != NULL)
    {
        bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
    }
    if(getTitlebar() != NULL)
    {
        bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
    }
    if(!getLockInput())
    {
        if(getParentDrawingSurface() != NULL && getParentDrawingSurface()->getEventProducer() != NULL)
        {
            getParentDrawingSurface()->getEventProducer()->setCursorType(WindowEventProducer::CURSOR_POINTER);
        }
        ComponentContainer::mouseExited(e);
    }
}

void InternalWindow::mousePressed(MouseEventDetails* const e)
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
                    setLockInput(true);

                    _WindowStartPosition = getPosition();
                    _WindowStartSize = getSize();
                    _MouseStartPosition = e->getLocation();
                    _BorderDragged = TheArea;
    
                    _BorderDragMouseDraggedConnection = getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&InternalWindow::borderDragMouseDragged, this, _1));
                    _BorderDragMouseReleasedConnection = getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&InternalWindow::borderDragMouseReleased, this, _1));
                    _BorderDragKeyPressedConnection = getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&InternalWindow::borderDragKeyPressed, this, _1));
                    break;
            }
        }
        if(getMenuBar() != NULL)
        {
            bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
            if(isContained)
            {
                getMenuBar()->mousePressed(e);
                if(e->isConsumed()) return;
                Component::mousePressed(e);
                return;
            }
        }
        if(getTitlebar() != NULL)
        {
            bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
            if(isContained)
            {
                getTitlebar()->mousePressed(e);
                if(e->isConsumed()) return;
                Component::mousePressed(e);
                return;
            }
        }

        //ComponentContainer MousePressed Handling
        bool isContained(false);
        for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
        {
            isContained = getChildren(i)->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
            if(isContained)
            {
                takeFocus();
                if(!getChildren(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
                {
                    getChildren(i)->takeFocus();
                }
                getChildren(i)->mousePressed(e);
                if(e->isConsumed()) return;
                break;
            }
        }
        Component::mousePressed(e);
    }
}

void InternalWindow::mouseReleased(MouseEventDetails* const e)
{
    if(!getLockInput())
    {
        if(getMenuBar() != NULL)
        {
            bool isContained;
            isContained = getMenuBar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
            if(isContained)
            {
                getMenuBar()->mouseReleased(e);
                if(e->isConsumed()) return;
                Component::mouseReleased(e);
                return;
            }
        }
        if(getTitlebar() != NULL)
        {
            bool isContained;
            isContained = getTitlebar()->isContained(e->getLocation(), true);
            checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
            if(isContained)
            {
                getTitlebar()->mouseReleased(e);
                if(e->isConsumed()) return;
                Component::mouseReleased(e);
                return;
            }
        }
        ComponentContainer::mouseReleased(e);
    }
}

void InternalWindow::getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    if(getDrawDecorations() && 
       getDrawTitlebar() && 
       getDrawnBorder()  &&
       getDrawnBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
    {
        dynamic_cast<WindowBorder*>(getDrawnBorder())->getTitlebarBounds(0, 0, getSize().x(), getSize().y(), TopLeft, BottomRight);
    }
    else
    {
        TopLeft.setValues(0,0);
        BottomRight.setValues(0,0);
    }
}

InternalWindow::WindowArea InternalWindow::getCursurArea(const Pnt2f& DrawingSurfaceLocation) const
{
    Pnt2f LocationInWindow(DrawingSurfaceToComponent(DrawingSurfaceLocation, this));
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

void InternalWindow::mouseMoved(MouseEventDetails* const e)
{

    if(getMenuBar() != NULL)
    {
        bool isContained;
        isContained = getMenuBar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getMenuBar(),isContained,e->getViewport());
        if(isContained)
        {
            getMenuBar()->mouseMoved(e);
            if(e->isConsumed()) return;
            Component::mouseMoved(e);
            return;
        }
    }
    if(getTitlebar() != NULL)
    {
        bool isContained;
        isContained = getTitlebar()->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTitlebar(),isContained,e->getViewport());
        if(isContained)
        {
            getTitlebar()->mouseMoved(e);
            if(e->isConsumed()) return;
            Component::mouseMoved(e);
            return;
        }
    }
    if(!getLockInput())
    {
        ComponentContainer::mouseMoved(e);
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

void InternalWindow::mouseDragged(MouseEventDetails* const e)
{
    if(getMenuBar() != NULL)
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
    if(getTitlebar() != NULL)
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
        ComponentContainer::mouseDragged(e);
    }
}

void InternalWindow::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    if(!getLockInput())
    {
        ComponentContainer::mouseWheelMoved(e);
    }
}

void InternalWindow::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    Inherited::drawInternal(TheGraphics, Opacity);

    //If I have an active TitleBar then draw it
    if(getDrawDecorations() && getDrawTitlebar() && getTitlebar() != NULL)
    {
        getTitlebar()->draw(TheGraphics, Opacity*getOpacity());
    }

    //If I have a MenuBar then Draw it
    if(getMenuBar() != NULL)
    {
        getMenuBar()->draw(TheGraphics, Opacity*getOpacity());
    }
}

void InternalWindow::drawUnclipped(Graphics* const TheGraphics, Real32 Opacity) const
{
    Inherited::drawUnclipped(TheGraphics, Opacity);

    //If I have an active tooltip then draw it
    if(getActiveToolTip() != NULL)
    {
        getActiveToolTip()->draw(TheGraphics, Opacity*getOpacity());
    }

    //If I have an active popupMenu then draw it
    for(UInt32 i(0) ; i<getMFActivePopupMenus()->size() ; ++i)
    {
        getActivePopupMenus(i)->draw(TheGraphics, Opacity*getOpacity());
    }
}

void InternalWindow::destroyPopupMenu(void)
{
    if(getMFActivePopupMenus()->size() > 0)
    {
        for(UInt32 i(0) ; i<getMFActivePopupMenus()->size() ; ++i)
        {
            getActivePopupMenus(i)->cancel();
        }
        _PopupConnections.clear();

        clearActivePopupMenus();
        setLockInput(false);
    }
}

void InternalWindow::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    destroyPopupMenu();
    _TitleBarMousePressedConnection.disconnect();
    _TitlebarDragMouseDraggedConnection.disconnect();
    _TitlebarDragMouseReleasedConnection.disconnect();
    _TitlebarDragKeyPressedConnection.disconnect();
    _BorderDragMouseDraggedConnection.disconnect();
    _BorderDragMouseReleasedConnection.disconnect();
    _BorderDragKeyPressedConnection.disconnect();
    _CloseButtonActionConnection.disconnect();
    _MaximizeButtonActionConnection.disconnect();
    _IconifyButtonActionConnection.disconnect();
}


void InternalWindow::getMenuBarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    //Get Insets Bounds
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    ComponentContainer::getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    TopLeft = InsetsTopLeft;
    if(getMenuBar() == NULL)
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
    ComponentContainer::getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    BottomRight = InsetsBottomRight;
    if(getMenuBar() == NULL)
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
    if(getMenuBar() != NULL)
    {
        Pnt2f MenuTopLeft, MenuBottomRight;
        getMenuBar()->updateLayout();
        getMenuBarBounds(MenuTopLeft, MenuBottomRight);
        if(getMenuBar()->getPosition() != MenuTopLeft)
        {
            getMenuBar()->setPosition(MenuTopLeft);
        }
        Vec2f Size(MenuBottomRight.x() - MenuTopLeft.x(), getMenuBar()->getPreferredSize().y());
        if(getMenuBar()->getSize() != Size)
        {
            getMenuBar()->setSize(Size);
        }
    }

    //If I have a Titlebar then update it's layout
    if(getDrawDecorations() && getDrawTitlebar() && getTitlebar() != NULL)
    {
        Pnt2f TitlebarTopLeft, TitlebarBottomRight;
        getTitlebarBounds(TitlebarTopLeft, TitlebarBottomRight);
        if(getTitlebar()->getPosition() != TitlebarTopLeft)
        {
            getTitlebar()->setPosition(TitlebarTopLeft);
        }
        Vec2f Size(TitlebarBottomRight.x() - TitlebarTopLeft.x(), getTitlebar()->getPreferredSize().y());
        if(getTitlebar()->getSize() != Size)
        {
            getTitlebar()->setSize(Size);
        }
    }

    ComponentContainer::updateLayout();
}

boost::signals2::connection InternalWindow::connectKeyAccelerator(KeyEventDetails::Key TheKey, 
                                                                  UInt32 Modifiers,
                                                                  const KeyPressedEventType::slot_type &listener,
                                                                  boost::signals2::connect_position at)
{
    //Bind a predicate function to check the key/modifier pair
    boost::function<bool (KeyEventDetails* const)> predicateFunc(boost::bind(&InternalWindow::doKeyDetailsMatch, _1, TheKey, Modifiers));

    //Use the predicate function with a handleKeyAcceleratorCheck function
    return connectKeyPressed(boost::bind(&InternalWindow::handleKeyAcceleratorCheck, _1, predicateFunc, listener), at);
}

boost::signals2::connection InternalWindow::connectKeyAccelerator(KeyEventDetails::Key TheKey, 
                                                                  UInt32 Modifiers,
                                                                  const KeyPressedEventType::group_type &group,
                                                                  const KeyPressedEventType::slot_type &listener,
                                                                  boost::signals2::connect_position at)
{
    //Bind a predicate function to check the key/modifier pair
    boost::function<bool (KeyEventDetails* const)> predicateFunc(boost::bind(&InternalWindow::doKeyDetailsMatch, _1, TheKey, Modifiers));

    //Use the predicate function with a handleKeyAcceleratorCheck function
    return connectKeyPressed(group, boost::bind(&InternalWindow::handleKeyAcceleratorCheck, _1, predicateFunc, listener), at);
}

void InternalWindow::handleKeyAcceleratorCheck(KeyEventDetails* const details,
                                               boost::function<bool (KeyEventDetails* const)> predicateFunc,
                                               KeyPressedEventType::slot_type &listener)
{
    if(predicateFunc(details))
    {
        listener.operator()(details, InternalWindow::KeyPressedEventId);
    }
}

bool InternalWindow::doKeyDetailsMatch(KeyEventDetails* const Details,
                                       KeyEventDetails::Key   Key,
                                       UInt32                 Modifires)
{
    return (Details->getKey() == Key) && ((Details->getModifiers() & Modifires) == Modifires);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void InternalWindow::onCreate(const InternalWindow * Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        if(Id->getTitlebar() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getTitlebar()->shallowCopy());
            setTitlebar(dynamic_pointer_cast<Titlebar>(FCCopy));
        }
        if(Id->getBorder() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getBorder()->shallowCopy());
            setBorder(dynamic_pointer_cast<Border>(FCCopy));
        }
        if(Id->getDisabledBorder() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getDisabledBorder()->shallowCopy());
            setDisabledBorder(dynamic_pointer_cast<Border>(FCCopy));
        }
        if(Id->getFocusedBorder() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getFocusedBorder()->shallowCopy());
            setFocusedBorder(dynamic_pointer_cast<Border>(FCCopy));
        }
        if(Id->getRolloverBorder() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getRolloverBorder()->shallowCopy());
            setRolloverBorder(dynamic_pointer_cast<Border>(FCCopy));
        }
    }
}

void InternalWindow::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

InternalWindow::InternalWindow(void) :
    Inherited()
{
}

InternalWindow::InternalWindow(const InternalWindow &source) :
    Inherited(source)

{
}

InternalWindow::~InternalWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InternalWindow::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    if( ((whichField & FocusedFieldMask) ||
         (whichField & TitlebarFieldMask))&&
         getTitlebar() != NULL &&
         getDrawTitlebar() &&
         !getTitlebar()->getEnabled())
    {
        getTitlebar()->setEnabled(getFocused());
    }

    if( (whichField & ActiveToolTipFieldMask) &&
        getActiveToolTip() != NULL)
    {
        getActiveToolTip()->updateClipBounds();
    }

    if( (whichField & ActivePopupMenusFieldMask) &&
        getMFActivePopupMenus()->size() > 0)
    {
        _PopupConnections.clear();
        for(UInt32 i(0) ; i<getMFActivePopupMenus()->size() ; ++i)
        {
            getActivePopupMenus(i)->setParentWindow(this);
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectMouseClicked(boost::bind(&InternalWindow::popupMenuMousePressed, this, _1)))));
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectMousePressed(boost::bind(&InternalWindow::popupMenuMousePressed, this, _1)))));
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&InternalWindow::popupMenuMouseReleased, this, _1)))));
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&InternalWindow::popupMenuKeyPressed, this, _1)))));
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectMouseMoved(boost::bind(&InternalWindow::popupMenuMouseMoved, this, _1)))));
            _PopupConnections[getActivePopupMenus(i)].push_back(boost::shared_ptr<boost::signals2::scoped_connection>(new boost::signals2::scoped_connection(getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&InternalWindow::popupMenuMouseDragged, this, _1)))));
        }
        setLockInput(true);
    }

    if( (whichField & MenuBarFieldMask) && getMenuBar() != NULL)
    {
        getMenuBar()->setParentWindow(this);
    }

    if( (whichField & MenuBarFieldMask) || (whichField & TitlebarFieldMask))
    {
        updateLayout();
    }

    if( (whichField & TitleFieldMask) && getTitlebar() != NULL)
    {
        getTitlebar()->setTitle(getTitle());
    }

    if( (whichField & TitlebarFieldMask) && getTitlebar() != NULL)
    {
        getTitlebar()->setParentWindow(this);
    }

    if((whichField & TitlebarFieldMask) ||
       (whichField & BorderFieldMask) ||
       (whichField & DisabledBorderFieldMask) ||
       (whichField & FocusedBorderFieldMask) ||
       (whichField & RolloverBorderFieldMask) ||
       (whichField & DrawTitlebarFieldMask))
    {
        TitlebarRefPtr TheTitlebar;
        if(getDrawTitlebar())
        {
            TheTitlebar = getTitlebar();
        }
        else
        {
            TheTitlebar = NULL;
        }

        if(getBorder() != NULL && getBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
        {
            dynamic_cast<WindowBorder*>(getBorder())->setTitlebar(TheTitlebar);
        }
        if(getDisabledBorder() != NULL && getDisabledBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
        {
            dynamic_cast<WindowBorder*>(getDisabledBorder())->setTitlebar(TheTitlebar);
        }
        if(getFocusedBorder() != NULL && getFocusedBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
        {
            dynamic_cast<WindowBorder*>(getFocusedBorder())->setTitlebar(TheTitlebar);
        }
        if(getRolloverBorder() != NULL && getRolloverBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
        {
            dynamic_cast<WindowBorder*>(getRolloverBorder())->setTitlebar(TheTitlebar);
        }
    }

    if( whichField & ClipBoundsFieldMask)
    {
        if(getTitlebar() != NULL)
        {
            getTitlebar()->updateClipBounds();
        }
    }

    if( (whichField & TitlebarFieldMask) &&
        getTitlebar() != NULL)
    {
        if(getTitlebar()->getTitleLabel() != NULL)
        {
            _TitleBarMousePressedConnection = getTitlebar()->getTitleLabel()->connectMousePressed(boost::bind(&InternalWindow::titlebarMousePressed, this, _1));
        }
        if(getTitlebar()->getCloseButton() != NULL)
        {
            _CloseButtonActionConnection = getTitlebar()->getCloseButton()->connectActionPerformed(boost::bind(&InternalWindow::closeButtonAction, this, _1));
        }
        if(getTitlebar()->getMaximizeButton() != NULL)
        {
            _MaximizeButtonActionConnection = getTitlebar()->getMaximizeButton()->connectActionPerformed(boost::bind(&InternalWindow::maximizeButtonAction, this, _1));
        }
        if(getTitlebar()->getIconifyButton() != NULL)
        {
            _IconifyButtonActionConnection = getTitlebar()->getIconifyButton()->connectActionPerformed(boost::bind(&InternalWindow::iconifyButtonAction, this, _1));
        }
    }

    if( (whichField & IconableFieldMask) &&
        getTitlebar() != NULL)
    {
        getTitlebar()->setDrawIconify(getIconable());
    }
    if( (whichField & MaximizableFieldMask) &&
        getTitlebar() != NULL)
    {
        getTitlebar()->setDrawMaximize(getMaximizable());
    }
    if( (whichField & ClosableFieldMask) &&
        getTitlebar() != NULL)
    {
        getTitlebar()->setDrawClose(getClosable());
    }

    Inherited::changed(whichField, origin, details);
}

void InternalWindow::dump(      UInt32    ,
                                const BitVector ) const
{
    SLOG << "Dump InternalWindow NI" << std::endl;
}

void InternalWindow::popupMenuMouseClicked(MouseEventDetails* const e)
{
    for(Int32 i(getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = getActivePopupMenus(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            getActivePopupMenus(i)->mouseClicked(e);
            return;
        }
    }
    //destroyPopupMenu();
}

void InternalWindow::popupMenuMousePressed(MouseEventDetails* const e)
{
    for(Int32 i(getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = getActivePopupMenus(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            getActivePopupMenus(i)->mousePressed(e);
            return;
        }
    }
    destroyPopupMenu();
}

void InternalWindow::popupMenuMouseReleased(MouseEventDetails* const e)
{
    for(Int32 i(getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = getActivePopupMenus(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            getActivePopupMenus(i)->mouseReleased(e);
            return;
        }
    }
}

void InternalWindow::popupMenuMouseMoved(MouseEventDetails* const e)
{
    for(Int32 i(getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = getActivePopupMenus(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            getActivePopupMenus(i)->mouseMoved(e);
            return;
        }
    }
}

void InternalWindow::popupMenuMouseDragged(MouseEventDetails* const e)
{
    for(Int32 i(getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = getActivePopupMenus(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            getActivePopupMenus(i)->mouseDragged(e);
            return;
        }
    }
}

void InternalWindow::popupMenuKeyPressed(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        destroyPopupMenu();
    }
    else if(e->getKey() == KeyEventDetails::KEY_UP)
    {
        getMFActivePopupMenus()->front()->setSelection( getMFActivePopupMenus()->front()->getSelectionIndex() -1 );
    }
    else if(e->getKey() == KeyEventDetails::KEY_DOWN)
    {
        getMFActivePopupMenus()->front()->setSelection( getMFActivePopupMenus()->front()->getSelectionIndex() +1 );
    }
    else if(e->getKey() == KeyEventDetails::KEY_ENTER && getMFActivePopupMenus()->front()->getItem(getMFActivePopupMenus()->front()->getSelectionIndex()) != NULL)
    {
        getMFActivePopupMenus()->front()->getItem(getMFActivePopupMenus()->front()->getSelectionIndex())->activate();
        destroyPopupMenu();
    }
}

void InternalWindow::titlebarMousePressed(MouseEventDetails* const e)
{
    _WindowStartPosition = getPosition();
    _MouseStartPosition = e->getLocation();
            
    _TitlebarDragMouseDraggedConnection = getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&InternalWindow::titlebarDragMouseDragged, this, _1));
    _TitlebarDragMouseReleasedConnection = getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&InternalWindow::titlebarDragMouseReleased, this, _1));
    _TitlebarDragKeyPressedConnection = getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&InternalWindow::titlebarDragKeyPressed, this, _1));
}

void InternalWindow::titlebarDragMouseReleased(MouseEventDetails* const e)
{
    _TitlebarDragMouseDraggedConnection.disconnect();
    _TitlebarDragMouseReleasedConnection.disconnect();
    _TitlebarDragKeyPressedConnection.disconnect();
    setLockInput(false);
}

void InternalWindow::titlebarDragMouseDragged(MouseEventDetails* const e)
{
    setPosition( _WindowStartPosition - (_MouseStartPosition - e->getLocation()) );
}

void InternalWindow::titlebarDragKeyPressed(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        _TitlebarDragMouseDraggedConnection.disconnect();
        _TitlebarDragMouseReleasedConnection.disconnect();
        _TitlebarDragKeyPressedConnection.disconnect();
        setLockInput(false);

        //Reset the Window to it's original Position
        setPosition(_WindowStartPosition);
    }
}

void InternalWindow::borderDragMouseReleased(MouseEventDetails* const e)
{
        _BorderDragMouseDraggedConnection.disconnect();
        _BorderDragMouseReleasedConnection.disconnect();
        _BorderDragKeyPressedConnection.disconnect();

        setLockInput(false);
}

void InternalWindow::borderDragMouseDragged(MouseEventDetails* const e)
{
    Vec2f Size;
    bool PositionChange;
    Pnt2f Position;
    Pnt2f BottomRight(getPosition() + getSize());
    switch(_BorderDragged)
    {
        case WINDOW_LEFT_BORDER:
            Size.setValues(BottomRight.x() - e->getLocation().x(), getPreferredSize().y());
            PositionChange = true;
            Position = BottomRight - Size;
            break;
        case WINDOW_RIGHT_BORDER:
            PositionChange = false;
            Size.setValues(e->getLocation().x() - getPosition().x(), getPreferredSize().y());
            break;
        case WINDOW_TOP_BORDER:
            Size.setValues(getPreferredSize().x(), BottomRight.y() - e->getLocation().y());
            PositionChange = true;
            Position = BottomRight - Size;
            break;
        case WINDOW_BOTTOM_BORDER:
            PositionChange = false;
            Size.setValues(getPreferredSize().x(), e->getLocation().y() - getPosition().y());
            break;
        case WINDOW_TOP_LEFT_BORDER:
            Size.setValues(BottomRight.x() - e->getLocation().x(), BottomRight.y() - e->getLocation().y());
            PositionChange = true;
            Position = BottomRight - Size;
            break;
        case WINDOW_BOTTOM_RIGHT_BORDER:
            PositionChange = false;
            Size.setValues(e->getLocation().x() - getPosition().x(), e->getLocation().y() - getPosition().y());
            break;
        case WINDOW_TOP_RIGHT_BORDER:
            Size.setValues(e->getLocation().x() - getPosition().x(), BottomRight.y() - e->getLocation().y());
            PositionChange = true;
            Position.setValues(getPosition().x(), BottomRight.y() - Size.y());
            break;
        case WINDOW_BOTTOM_LEFT_BORDER:
            Size.setValues(BottomRight.x() - e->getLocation().x(), e->getLocation().y() - getPosition().y());
            PositionChange = true;
            Position.setValues( BottomRight.x() - Size.x(), getPosition().y());
            break;
    }

    if(PositionChange)
    {
        setPreferredSize(Size);
        setPosition(Position);
    }
    else
    {
        setPreferredSize(Size);
    }
}


void InternalWindow::borderDragKeyPressed(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        _BorderDragMouseDraggedConnection.disconnect();
        _BorderDragMouseReleasedConnection.disconnect();
        _BorderDragKeyPressedConnection.disconnect();

        setLockInput(false);

        //Reset the Window to it's original Position and size
        if(getPosition() != _WindowStartPosition)
        {
            setPosition(_WindowStartPosition);
        }
        if(getSize() != _WindowStartSize)
        {
            setSize(_WindowStartSize);
        }
    }
}

void InternalWindow::closeButtonAction(ActionEventDetails* const e)
{
    close();
}

void InternalWindow::maximizeButtonAction(ActionEventDetails* const e)
{
    setMaximize(!getMaximize());
}

void InternalWindow::iconifyButtonAction(ActionEventDetails* const e)
{
    setIconify(true);
}

OSG_END_NAMESPACE
