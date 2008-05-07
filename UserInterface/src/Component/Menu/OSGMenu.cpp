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

#include "OSGMenu.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "OSGPopupMenu.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Menu
A UI Menu. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Menu::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Menu::drawInternal(const GraphicsPtr Graphics) const
{
    Inherited::drawInternal(Graphics);

    if(getExpandDrawObject() != NullFC && !getTopLevelMenu())
    {
        getExpandDrawObject()->draw(Graphics);
    }
}

void Menu::mouseReleased(const MouseEvent& e)
{
    Component::mouseReleased(e);
}

void Menu::setPopupVisible(bool Visible)
{
    beginEditCP(getInternalPopupMenu(), PopupMenu::VisibleFieldMask);
        getInternalPopupMenu()->setVisible(Visible);
    endEditCP(getInternalPopupMenu(), PopupMenu::VisibleFieldMask);
    if(Visible)
    { 
        //Set the Submenu's position to the correct place
        //Make the Submenu visible
        beginEditCP(getInternalPopupMenu(), PopupMenu::PositionFieldMask);
            if(getTopLevelMenu())
            {
                getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),MenuPtr(this)) + Vec2f(0,getSize().y()));        
            }
            else
            {
                getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),MenuPtr(this)) + Vec2f(getSize().x(),0));
            }
        endEditCP(getInternalPopupMenu(), PopupMenu::PositionFieldMask);
        beginEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
            getParentWindow()->getActivePopupMenus().push_back(getInternalPopupMenu());
        endEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
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

void Menu::addSeparator(SeparatorPtr TheSeparator)
{
    getInternalPopupMenu()->addSeparator(TheSeparator);
}

void Menu::removeSeparator(const UInt32&  Index)
{
    getInternalPopupMenu()->removeSeparator(Index);
}

void Menu::removeSeparator(SeparatorPtr TheSeparator)
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


void Menu::addItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->addItem(Item);
    beginEditCP(MenuPtr(this), MenuItemsFieldMask);
        getMenuItems().push_back(Item);
    endEditCP(MenuPtr(this), MenuItemsFieldMask);
    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
        Item->setParentMenu(MenuPtr(this));
        Item->setParentWindow(getParentWindow());
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
}

void Menu::addItem(MenuItemPtr Item, const UInt32& Index)
{
    getInternalPopupMenu()->addItem(Item, Index);
    
    MFMenuItemPtr::iterator Itor(getMenuItems().begin());
    for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
    beginEditCP(MenuPtr(this), MenuItemsFieldMask);
        getMenuItems().insert(Itor, Item);
    endEditCP(MenuPtr(this), MenuItemsFieldMask);

    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
        Item->setParentMenu(MenuPtr(this));
        Item->setParentWindow(getParentWindow());
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
}

void Menu::removeItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->removeItem(Item);

    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
        Item->setParentMenu(NullFC);
        Item->setParentWindow(NullFC);
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
    
    MFMenuItemPtr::iterator FindResult = getMenuItems().find(Item);
    if(FindResult != getMenuItems().end())
    {
        beginEditCP(MenuPtr(this), MenuItemsFieldMask);
            getMenuItems().erase(FindResult);
        endEditCP(MenuPtr(this), MenuItemsFieldMask);
    }
}

void Menu::removeItem(const UInt32& Index)
{
    MFMenuItemPtr::iterator Itor(getMenuItems().begin());
    for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
    beginEditCP((*Itor), MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);
        (*Itor)->setParentMenu(NullFC);
        (*Itor)->setParentWindow(NullFC);
    endEditCP((*Itor), MenuItem::ParentMenuFieldMask | ParentWindowFieldMask);

    beginEditCP(MenuPtr(this), MenuItemsFieldMask);
        getMenuItems().erase(Itor);
    endEditCP(MenuPtr(this), MenuItemsFieldMask);


    getInternalPopupMenu()->removeItem(Index);
}

void Menu::activate(void)
{
    //Do Nothing
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Menu::Menu(void) :
    Inherited(),
    _PopupUpdateListener(MenuPtr(this))
{
    //setInternalPopupMenu(PopupMenu::create());
    //getInternalPopupMenu()->setVisible(false);
}

Menu::Menu(const Menu &source) :
    Inherited(source),
    _PopupUpdateListener(MenuPtr(this))
{
    setInternalPopupMenu(PopupMenu::create());
    getInternalPopupMenu()->setVisible(false);
}

Menu::~Menu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Menu::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ParentWindowFieldMask)
    {
        beginEditCP(getInternalPopupMenu(), ParentWindowFieldMask);
            getInternalPopupMenu()->setParentWindow(getParentWindow());
        endEditCP(getInternalPopupMenu(), ParentWindowFieldMask);

        for(UInt32 i(0) ; i<getMenuItems().size() ; ++i)
        {
            beginEditCP(getMenuItems()[i], ParentWindowFieldMask);
                getMenuItems()[i]->setParentWindow(getParentWindow());
            endEditCP(getMenuItems()[i], ParentWindowFieldMask);
        }
    }
    
    if(whichField & SelectedFieldMask)
    {
        if(getSelected())
        {
            setPopupVisible(false);
            if(getParentWindow() != NullFC &&
            getParentWindow()->getDrawingSurface() != NullFC &&
            getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
            {
                _PopupUpdateListener.reset();
                getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_PopupUpdateListener);
            }
        }
        else
        {
            setPopupVisible(false);
            if(getParentWindow() != NullFC &&
            getParentWindow()->getDrawingSurface() != NullFC &&
            getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
            {
                getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_PopupUpdateListener);
            }
        }
    }

    if(whichField & ExpandDrawObjectFieldMask)
    {
        beginEditCP(getExpandDrawObject(), UIDrawObjectCanvas::SizeFieldMask);
            getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());
        endEditCP(getExpandDrawObject(), UIDrawObjectCanvas::SizeFieldMask);
    }

    if(whichField & SizeFieldMask)
    {
        beginEditCP(getExpandDrawObject(), UIDrawObjectCanvas::SizeFieldMask);
            getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());
        endEditCP(getExpandDrawObject(), UIDrawObjectCanvas::SizeFieldMask);

        //Calculate Alignment
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Pnt2f ExpandTopLeft, ExpandBottomRight;
        getExpandDrawObject()->getBounds(ExpandTopLeft, ExpandBottomRight);

        Pnt2f AlignedPosition;
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (ExpandBottomRight - ExpandTopLeft),0.5, 1.0);

        beginEditCP(getExpandDrawObject(), PositionFieldMask);
            getExpandDrawObject()->setPosition(AlignedPosition);
        endEditCP(getExpandDrawObject(), PositionFieldMask);
    }
}

void Menu::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Menu NI" << std::endl;
}


void Menu::PopupUpdateListener::update(const UpdateEvent& e)
{
    _PopupElps += e.getElapsedTime();
    if(_PopupElps > LookAndFeelManager::the()->getLookAndFeel()->getSubMenuPopupTime())
    {
        //Tell the menu to popup the submenu
        _Menu->setPopupVisible(true);
        //Remove myself from the update
		_Menu->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
    }
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
    static Char8 cvsid_hpp       [] = OSGMENUBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMENUBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMENUFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

