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
        focusLost(FocusEvent::create(this,getSystemTime(),Temporary, NewFocusedComponent));
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
        focusGained(FocusEvent::create(this,getSystemTime(),Temporary, NULL));
    }
    else
    {
        if(getParentDrawingSurface()->getFocusedWindow() != NULL)
        {
            getParentDrawingSurface()->getFocusedWindow()->giveFocus(this);
        }
        getParentDrawingSurface()->setFocusedWindow(this);
        focusGained(FocusEvent::create(this,getSystemTime(),Temporary, getParentDrawingSurface()->getFocusedWindow()));
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

void InternalWindow::keyPressed(const KeyEventUnrecPtr e)
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
            (*MapItor).second->acceleratorTyped(KeyAcceleratorEvent::create(this, e->getTimeStamp(), e->getKey(), e->getModifiers()));
        }
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyPressed(e);
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyPressed(e);
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyPressed(e);
    }
}

void InternalWindow::keyReleased(const KeyEventUnrecPtr e)
{
    if(!getLockInput())
    {
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyReleased(e);
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyReleased(e);
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyReleased(e);
    }
}

void InternalWindow::keyTyped(const KeyEventUnrecPtr e)
{
    if(!getLockInput())
    {
        //Send Key event to Component that has Focus
        //If there is not Focused Component then do nothing
        if(getFocusedComponent() != NULL &&
           getFocusedComponent() != this)
        {
            getFocusedComponent()->keyTyped(e);
            ComponentContainerRefPtr ParentContainer(getFocusedComponent()->getParentContainer());
            while(ParentContainer != NULL &&
                  ParentContainer != this)
            {
                ParentContainer->keyTyped(e);
                ParentContainer = dynamic_cast<ComponentContainer*>(ParentContainer->getParentContainer());
            }
        }
        Component::keyTyped(e);
    }
}

void InternalWindow::mouseClicked(const MouseEventUnrecPtr e)
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
                Component::mouseClicked(e);
                return;
            }
        }
        ComponentContainer::mouseClicked(e);
    }
}

void InternalWindow::mouseEntered(const MouseEventUnrecPtr e)
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

void InternalWindow::mouseExited(const MouseEventUnrecPtr e)
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

void InternalWindow::mousePressed(const MouseEventUnrecPtr e)
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

                    _BorderDraggedListener.setWindowStartPosition(getPosition());
                    _BorderDraggedListener.setWindowStartSize(getSize());
                    _BorderDraggedListener.setMouseStartPosition(e->getLocation());
                    _BorderDraggedListener.setBorderDragged(TheArea);

                    getParentDrawingSurface()->getEventProducer()->addMouseMotionListener(&_BorderDraggedListener);
                    getParentDrawingSurface()->getEventProducer()->addMouseListener(&_BorderDraggedListener);
                    getParentDrawingSurface()->getEventProducer()->addKeyListener(&_BorderDraggedListener);
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
                break;
            }
        }
        Component::mousePressed(e);
    }
}

void InternalWindow::mouseReleased(const MouseEventUnrecPtr e)
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
                Component::mouseReleased(e);
                return;
            }
        }
        ComponentContainer::mouseReleased(e);
    }
}

void InternalWindow::getTitlebarBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    if(getDrawDecorations() && getDrawTitlebar() && getDrawnBorder()->getType().isDerivedFrom(WindowBorder::getClassType()))
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

void InternalWindow::mouseMoved(const MouseEventUnrecPtr e)
{

    if(getMenuBar() != NULL)
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
    if(getTitlebar() != NULL)
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

void InternalWindow::mouseDragged(const MouseEventUnrecPtr e)
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

void InternalWindow::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
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

        clearActivePopupMenus();
        setLockInput(false);

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
        getMenuBar()->setPosition(MenuTopLeft);
        getMenuBar()->setSize(Vec2f( MenuBottomRight.x() - MenuTopLeft.x(), getMenuBar()->getPreferredSize().y()));
    }

    //If I have a Titlebar then update it's layout
    if(getDrawDecorations() && getDrawTitlebar() && getTitlebar() != NULL)
    {
        Pnt2f TitlebarTopLeft, TitlebarBottomRight;
        getTitlebarBounds(TitlebarTopLeft, TitlebarBottomRight);
        getTitlebar()->setPosition(TitlebarTopLeft);
        getTitlebar()->setSize(Vec2f( TitlebarBottomRight.x() - TitlebarTopLeft.x(), getTitlebar()->getPreferredSize().y()));
    }

    ComponentContainer::updateLayout();
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
    Inherited(),
    _PopupMenuInteractionListener(this),
	_TitlebarStartDragListener(this),
	_TitlebarDraggedListener(this),
	_BorderDraggedListener(this),
	_CloseButtonListener(this),
	_MaximizeButtonListener(this),
	_IconifyButtonListener(this)
{
}

InternalWindow::InternalWindow(const InternalWindow &source) :
    Inherited(source),
    _PopupMenuInteractionListener(this),
    _TitlebarStartDragListener(this),
    _TitlebarDraggedListener(this),
    _BorderDraggedListener(this),
    _CloseButtonListener(this),
    _MaximizeButtonListener(this),
    _IconifyButtonListener(this)

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
        for(UInt32 i(0) ; i<getMFActivePopupMenus()->size() ; ++i)
        {
            getActivePopupMenus(i)->setParentWindow(this);
        }

        getParentDrawingSurface()->getEventProducer()->addMouseListener(&_PopupMenuInteractionListener);
        getParentDrawingSurface()->getEventProducer()->addMouseMotionListener(&_PopupMenuInteractionListener);
        getParentDrawingSurface()->getEventProducer()->addKeyListener(&_PopupMenuInteractionListener);
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
            getTitlebar()->getTitleLabel()->addMouseListener(&_TitlebarStartDragListener);
        }
        if(getTitlebar()->getCloseButton() != NULL)
        {
            getTitlebar()->getCloseButton()->addActionListener(&_CloseButtonListener);
        }
        if(getTitlebar()->getMaximizeButton() != NULL)
        {
            getTitlebar()->getMaximizeButton()->addActionListener(&_MaximizeButtonListener);
        }
        if(getTitlebar()->getIconifyButton() != NULL)
        {
            getTitlebar()->getIconifyButton()->addActionListener(&_IconifyButtonListener);
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

void InternalWindow::PopupMenuInteractionListener::mouseClicked(const MouseEventUnrecPtr e)
{
    for(Int32 i(_InternalWindow->getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus(i)->isContained(e->getLocation(), true);
        _InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            _InternalWindow->getActivePopupMenus(i)->mouseClicked(e);
            return;
        }
    }
    //_InternalWindow->destroyPopupMenu();
}

void InternalWindow::PopupMenuInteractionListener::mousePressed(const MouseEventUnrecPtr e)
{
    for(Int32 i(_InternalWindow->getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus(i)->isContained(e->getLocation(), true);
        _InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            _InternalWindow->getActivePopupMenus(i)->mousePressed(e);
            return;
        }
    }
    _InternalWindow->destroyPopupMenu();
}

void InternalWindow::PopupMenuInteractionListener::mouseReleased(const MouseEventUnrecPtr e)
{
    for(Int32 i(_InternalWindow->getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus(i)->isContained(e->getLocation(), true);
        _InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            _InternalWindow->getActivePopupMenus(i)->mouseReleased(e);
            return;
        }
    }
}

void InternalWindow::PopupMenuInteractionListener::mouseMoved(const MouseEventUnrecPtr e)
{
    for(Int32 i(_InternalWindow->getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus(i)->isContained(e->getLocation(), true);
        _InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            _InternalWindow->getActivePopupMenus(i)->mouseMoved(e);
            return;
        }
    }
}

void InternalWindow::PopupMenuInteractionListener::mouseDragged(const MouseEventUnrecPtr e)
{
    for(Int32 i(_InternalWindow->getMFActivePopupMenus()->size()-1) ; i>=0 ; --i)
    {
        bool isContained = _InternalWindow->getActivePopupMenus(i)->isContained(e->getLocation(), true);
        _InternalWindow->checkMouseEnterExit(e,e->getLocation(),_InternalWindow->getActivePopupMenus(i),isContained,e->getViewport());
        if(isContained)
        {
            _InternalWindow->getActivePopupMenus(i)->mouseDragged(e);
            return;
        }
    }
}

void InternalWindow::PopupMenuInteractionListener::keyPressed(const KeyEventUnrecPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        _InternalWindow->destroyPopupMenu();
    }
    else if(e->getKey() == KeyEvent::KEY_UP)
    {
        _InternalWindow->getMFActivePopupMenus()->front()->setSelection( _InternalWindow->getMFActivePopupMenus()->front()->getSelectionIndex() -1 );
    }
    else if(e->getKey() == KeyEvent::KEY_DOWN)
    {
        _InternalWindow->getMFActivePopupMenus()->front()->setSelection( _InternalWindow->getMFActivePopupMenus()->front()->getSelectionIndex() +1 );
    }
    else if(e->getKey() == KeyEvent::KEY_ENTER && _InternalWindow->getMFActivePopupMenus()->front()->getItem(_InternalWindow->getMFActivePopupMenus()->front()->getSelectionIndex()) != NULL)
    {
        _InternalWindow->getMFActivePopupMenus()->front()->getItem(_InternalWindow->getMFActivePopupMenus()->front()->getSelectionIndex())->activate();
        _InternalWindow->destroyPopupMenu();
    }
}

void InternalWindow::PopupMenuInteractionListener::disconnect(void)
{
    //Remove the listener
    if(_InternalWindow->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseListener(this);
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeKeyListener(this);
    }
}

void InternalWindow::TitlebarStartDragListener::mousePressed(const MouseEventUnrecPtr e)
{
    _InternalWindow->_TitlebarDraggedListener.setWindowStartPosition(_InternalWindow->getPosition());
    _InternalWindow->_TitlebarDraggedListener.setMouseStartPosition(e->getLocation());

    _InternalWindow->getParentDrawingSurface()->getEventProducer()->addMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
    _InternalWindow->getParentDrawingSurface()->getEventProducer()->addMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
    _InternalWindow->getParentDrawingSurface()->getEventProducer()->addKeyListener(&(_InternalWindow->_TitlebarDraggedListener));
}

void InternalWindow::TitlebarDraggedListener::mouseReleased(const MouseEventUnrecPtr e)
{
    if(_InternalWindow->getParentDrawingSurface() != NULL)
    {
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_TitlebarDraggedListener));

        _InternalWindow->setLockInput(false);
    }
}

void InternalWindow::TitlebarDraggedListener::mouseDragged(const MouseEventUnrecPtr e)
{
    _InternalWindow->setPosition( _WindowStartPosition - (_MouseStartPosition - e->getLocation()) );
}

void InternalWindow::TitlebarDraggedListener::keyPressed(const KeyEventUnrecPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        disconnect();

        //Reset the Window to it's original Position
        _InternalWindow->setPosition(_WindowStartPosition);
    }
}

void InternalWindow::TitlebarDraggedListener::disconnect(void)
{
    if(_InternalWindow->getParentWindow() != NULL)
    {
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_TitlebarDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_TitlebarDraggedListener));

        _InternalWindow->setLockInput(false);
    }
}

void InternalWindow::BorderDraggedListener::disconnect(void)
{
    if(_InternalWindow->getParentWindow() != NULL)
    {
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseMotionListener(&(_InternalWindow->_BorderDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeMouseListener(&(_InternalWindow->_BorderDraggedListener));
        _InternalWindow->getParentDrawingSurface()->getEventProducer()->removeKeyListener(&(_InternalWindow->_BorderDraggedListener));

        _InternalWindow->setLockInput(false);
    }
}

void InternalWindow::BorderDraggedListener::mouseReleased(const MouseEventUnrecPtr e)
{
    disconnect();
}

void InternalWindow::BorderDraggedListener::mouseDragged(const MouseEventUnrecPtr e)
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
        _InternalWindow->setPreferredSize(Size);
        _InternalWindow->setPosition(Position);
    }
    else
    {
        _InternalWindow->setPreferredSize(Size);
    }
}


void InternalWindow::BorderDraggedListener::keyPressed(const KeyEventUnrecPtr e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        disconnect();

        //Reset the Window to it's original Position and size
        _InternalWindow->setPosition(_WindowStartPosition);
        _InternalWindow->setSize(_WindowStartSize);
    }
}

void InternalWindow::CloseButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _InternalWindow->close();
}

void InternalWindow::MaximizeButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _InternalWindow->setMaximize(!_InternalWindow->getMaximize());
}

void InternalWindow::IconifyButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _InternalWindow->setIconify(true);
}

OSG_END_NAMESPACE
