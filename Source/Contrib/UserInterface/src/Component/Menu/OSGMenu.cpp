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

#include <OSGConfig.h>

#include "OSGMenu.h"
#include "OSGLookAndFeelManager.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGPopupMenu.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMenuBase.cpp file.
// To modify it, please change the .fcd file (OSGMenu.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Menu::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Menu::drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
    Inherited::drawInternal(Graphics, Opacity);

    if(getExpandDrawObject() != NULL && !getTopLevelMenu())
    {
        getExpandDrawObject()->draw(Graphics, getOpacity()*Opacity);
    }
}

void Menu::mouseReleased(const MouseEventUnrecPtr e)
{
    Component::mouseReleased(e);
}

void Menu::setPopupVisible(bool Visible)
{
    getInternalPopupMenu()->setVisible(Visible);
    if(Visible)
    { 
        //Set the Submenu's position to the correct place
        //Make the Submenu visible
        if(getTopLevelMenu())
        {
            getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),MenuRefPtr(this)) + Vec2f(0,getSize().y()));        
        }
        else
        {
            getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),MenuRefPtr(this)) + Vec2f(getSize().x(),0));
        }
        getParentWindow()->pushToActivePopupMenus(getInternalPopupMenu());
    }
    else
    {
        getInternalPopupMenu()->clearSelection();
    }
}

void Menu::addSeparator(void)
{
    getInternalPopupMenu()->addSeparator();
}

void Menu::addSeparator(SeparatorRefPtr TheSeparator)
{
    getInternalPopupMenu()->addSeparator(TheSeparator);
}

void Menu::removeSeparator(const UInt32&  Index)
{
    getInternalPopupMenu()->removeSeparator(Index);
}

void Menu::removeSeparator(SeparatorRefPtr TheSeparator)
{
    getInternalPopupMenu()->removeSeparator(TheSeparator);
}

void Menu::removeAllSeparators(void)
{
    getInternalPopupMenu()->removeAllSeparators();
}

UInt32 Menu::getNumSeparators(void) const
{
    return getInternalPopupMenu()->getNumSeparators();
}


void Menu::addItem(MenuItemRefPtr Item)
{
    getInternalPopupMenu()->addItem(Item);
    pushToMenuItems(Item);
    Item->setParentMenu(MenuRefPtr(this));
    Item->setParentWindow(getParentWindow());
}

void Menu::removeAllItems(void)
{
    getInternalPopupMenu()->removeAllItems();
    clearMenuItems();
}

void Menu::addItem(MenuItemRefPtr Item, const UInt32& Index)
{
    getInternalPopupMenu()->addItem(Item, Index);

    Menu::MFMenuItemsType::iterator Itor(editMFMenuItems()->begin());
    for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
    editMFMenuItems()->insert(Itor, Item);

    Item->setParentMenu(MenuRefPtr(this));
    Item->setParentWindow(getParentWindow());
}

void Menu::removeItem(MenuItemRefPtr Item)
{
    getInternalPopupMenu()->removeItem(Item);

    Item->setParentMenu(NULL);
    Item->setParentWindow(NULL);

    removeObjFromMenuItems(Item);
}

void Menu::removeItem(const UInt32& Index)
{
    getMenuItems(Index)->setParentMenu(NULL);
    getMenuItems(Index)->setParentWindow(NULL);

    removeFromMenuItems(Index);
}

void Menu::activate(void)
{
    //Do Nothing
}

void Menu::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _PopupUpdateEventConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Menu::onCreate(const Menu * Id)
{
    PopupMenuUnrecPtr ThePopupMenu(PopupMenu::create());
    setInternalPopupMenu(ThePopupMenu);

    if(getInternalPopupMenu() != NULL)
    {
        getInternalPopupMenu()->setVisible(false);
    }
}

void Menu::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

Menu::Menu(void) :
    Inherited(),
    _PopupUpdateListener(this)
{
}

Menu::Menu(const Menu &source) :
    Inherited(source),
    _PopupUpdateListener(this)
{
}

Menu::~Menu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Menu::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ParentWindowFieldMask)
    {
        getInternalPopupMenu()->setParentWindow(getParentWindow());

        for(UInt32 i(0) ; i<getMFMenuItems()->size() ; ++i)
        {
            getMenuItems(i)->setParentWindow(getParentWindow());
        }
    }

    if(whichField & SelectedFieldMask && getEnabled())
    {
        if(getSelected())
        {
            //setPopupVisible(false);
            if(getParentWindow() != NULL &&
               getParentWindow()->getDrawingSurface() != NULL &&
               getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
            {
                _PopupUpdateListener.reset();
                _PopupUpdateEventConnection = getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_PopupUpdateListener);
            }
        }
        else
        {
            setPopupVisible(false);
            if(getParentWindow() != NULL &&
               getParentWindow()->getDrawingSurface() != NULL &&
               getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
            {
                getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_PopupUpdateListener);
            }
        }
    }

    if(whichField & ExpandDrawObjectFieldMask)
    {
        getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());
    }

    if(whichField & SizeFieldMask)
    {
        getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());

        //Calculate Alignment
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Pnt2f ExpandTopLeft, ExpandBottomRight;
        getExpandDrawObject()->getBounds(ExpandTopLeft, ExpandBottomRight);

        Pnt2f AlignedPosition;
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (ExpandBottomRight - ExpandTopLeft),0.5, 1.0);

        getExpandDrawObject()->setPosition(AlignedPosition);
    }
}

void Menu::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Menu NI" << std::endl;
}

void Menu::PopupUpdateListener::update(const UpdateEventUnrecPtr e)
{
    _PopupElps += e->getElapsedTime();
    if(_PopupElps > LookAndFeelManager::the()->getLookAndFeel()->getSubMenuPopupTime())
    {
        //Tell the menu to popup the submenu
        _Menu->setPopupVisible(true);
        //Remove myself from the update
		_Menu->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
    }
}

OSG_END_NAMESPACE
