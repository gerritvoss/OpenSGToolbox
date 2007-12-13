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
#include "Component/Container/OSGFrame.h"
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
    LabelMenuItem::drawInternal(Graphics);

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
                getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2s(0,0),MenuPtr(this)) + Vec2s(0,getSize().y()));        
            }
            else
            {
                getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2s(0,0),MenuPtr(this)) + Vec2s(getSize().x(),0));
            }
        endEditCP(getInternalPopupMenu(), PopupMenu::PositionFieldMask);
        beginEditCP(getParentFrame(), Frame::ActivePopupMenusFieldMask);
            getParentFrame()->getActivePopupMenus().addValue(getInternalPopupMenu());
        endEditCP(getParentFrame(), Frame::ActivePopupMenusFieldMask);
    }
    else
    {
        getInternalPopupMenu()->clearSelection();
    }
}

void Menu::addItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->addItem(Item);
    beginEditCP(MenuPtr(this), MenuItemsFieldMask);
        getMenuItems().push_back(Item);
    endEditCP(MenuPtr(this), MenuItemsFieldMask);
    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
        Item->setParentMenu(MenuPtr(this));
        Item->setParentFrame(getParentFrame());
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
}

void Menu::addItem(MenuItemPtr Item, const UInt32& Index)
{
    getInternalPopupMenu()->addItem(Item, Index);
    
    MFMenuItemPtr::iterator Itor(getMenuItems().begin());
    for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
    beginEditCP(MenuPtr(this), MenuItemsFieldMask);
        getMenuItems().insert(Itor, Item);
    endEditCP(MenuPtr(this), MenuItemsFieldMask);

    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
        Item->setParentMenu(MenuPtr(this));
        Item->setParentFrame(getParentFrame());
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
}

void Menu::removeItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->removeItem(Item);

    beginEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
        Item->setParentMenu(NullFC);
        Item->setParentFrame(NullFC);
    endEditCP(Item, MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
    
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
    beginEditCP((*Itor), MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);
        (*Itor)->setParentMenu(NullFC);
        (*Itor)->setParentFrame(NullFC);
    endEditCP((*Itor), MenuItem::ParentMenuFieldMask | ParentFrameFieldMask);

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

    if(whichField & ParentFrameFieldMask)
    {
        beginEditCP(getInternalPopupMenu(), ParentFrameFieldMask);
            getInternalPopupMenu()->setParentFrame(getParentFrame());
        endEditCP(getInternalPopupMenu(), ParentFrameFieldMask);

        for(UInt32 i(0) ; i<getMenuItems().size() ; ++i)
        {
            beginEditCP(getMenuItems().getValue(i), ParentFrameFieldMask);
                getMenuItems().getValue(i)->setParentFrame(getParentFrame());
            endEditCP(getMenuItems().getValue(i), ParentFrameFieldMask);
        }
    }
    
    if(whichField & SelectedFieldMask)
    {
        if(getSelected())
        {
            setPopupVisible(false);
            if(getParentFrame() != NullFC &&
            getParentFrame()->getDrawingSurface() != NullFC &&
            getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
            {
                _PopupUpdateListener.reset();
                getParentFrame()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_PopupUpdateListener);
            }
        }
        else
        {
            setPopupVisible(false);
            if(getParentFrame() != NullFC &&
            getParentFrame()->getDrawingSurface() != NullFC &&
            getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
            {
                getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_PopupUpdateListener);
            }
        }
    }

    if(whichField & SizeFieldMask)
    {
        //Calculate Alignment
        Pnt2s TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Pnt2s ExpandTopLeft, ExpandBottomRight;
        getExpandDrawObject()->getBounds(ExpandTopLeft, ExpandBottomRight);

        Pnt2s AlignedPosition;
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
		_Menu->getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
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

