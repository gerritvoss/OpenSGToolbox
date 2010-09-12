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

void Menu::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{
    Inherited::drawInternal(Graphics, Opacity);

    if(getExpandDrawObject() != NULL && !getTopLevelMenu())
    {
        getExpandDrawObject()->draw(Graphics, getOpacity()*Opacity);
    }
}

void Menu::mouseReleased(MouseEventDetails* const e)
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
            getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),this) + Vec2f(0,getSize().y()));        
        }
        else
        {
            getInternalPopupMenu()->setPosition(ComponentToFrame(Pnt2f(0,0),this) + Vec2f(getSize().x(),0));
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

void Menu::addSeparator(Separator* const TheSeparator)
{
    getInternalPopupMenu()->addSeparator(TheSeparator);
}

void Menu::removeSeparator(const UInt32&  Index)
{
    getInternalPopupMenu()->removeSeparator(Index);
}

void Menu::removeSeparator(Separator* const TheSeparator)
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


void Menu::addItem(MenuItem* const Item)
{
    getInternalPopupMenu()->addItem(Item);
    pushToMenuItems(Item);
    Item->setParentWindow(getParentWindow());
}

void Menu::removeAllItems(void)
{
    getInternalPopupMenu()->removeAllItems();
    clearMenuItems();
}

void Menu::addItem(MenuItem* const Item, const UInt32& Index)
{
    getInternalPopupMenu()->addItem(Item, Index);

    insertIntoMenuItems(Index,Item);

    Item->setParentWindow(getParentWindow());
}

void Menu::removeItem(MenuItem* const Item)
{
    getInternalPopupMenu()->removeItem(Item);

    Item->setParentWindow(NULL);

    removeObjFromMenuItems(Item);
}

void Menu::removeItem(const UInt32& Index)
{
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

void Menu::setParentWindow(InternalWindow* const parent)
{
    Inherited::setParentWindow(parent);

    getInternalPopupMenu()->setParentWindow(getParentWindow());

    for(UInt32 i(0) ; i<getMFMenuItems()->size() ; ++i)
    {
        getMenuItems(i)->setParentWindow(getParentWindow());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Menu::onCreate(const Menu * Id)
{
	Inherited::onCreate(Id);

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
    Inherited()
{
}

Menu::Menu(const Menu &source) :
    Inherited(source)
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

    if(whichField & SelectedFieldMask && getEnabled())
    {
        if(getSelected())
        {
            //setPopupVisible(false);
            if(getParentWindow() != NULL &&
               getParentWindow()->getParentDrawingSurface() != NULL &&
               getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
            {
                _PopupElps = 0.0;
                _PopupUpdateEventConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&Menu::popupUpdate, this, _1));
            }
        }
        else
        {
            setPopupVisible(false);
            _PopupUpdateEventConnection.disconnect();
        }
    }

    if((whichField & ExpandDrawObjectFieldMask) && getExpandDrawObject() != NULL)
    {
        if(getExpandDrawObject()->getSize() != getExpandDrawObject()->getRequestedSize())
        {
            getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());
        }
    }

    if((whichField & SizeFieldMask) && getExpandDrawObject() != NULL)
    {
        if(getExpandDrawObject()->getSize() != getExpandDrawObject()->getRequestedSize())
        {
            getExpandDrawObject()->setSize(getExpandDrawObject()->getRequestedSize());
        }

        //Calculate Alignment
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Pnt2f ExpandTopLeft, ExpandBottomRight;
        getExpandDrawObject()->getBounds(ExpandTopLeft, ExpandBottomRight);

        Pnt2f AlignedPosition;
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (ExpandBottomRight - ExpandTopLeft),0.5, 1.0);

        if(getExpandDrawObject()->getPosition() != AlignedPosition)
        {
            getExpandDrawObject()->setPosition(AlignedPosition);
        }
    }
}

void Menu::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Menu NI" << std::endl;
}

void Menu::popupUpdate(UpdateEventDetails* const e)
{
    _PopupElps += e->getElapsedTime();
    if(_PopupElps > LookAndFeelManager::the()->getLookAndFeel()->getSubMenuPopupTime())
    {
        //Tell the menu to popup the submenu
        setPopupVisible(true);
        //Remove myself from the update
		_PopupUpdateEventConnection.disconnect();
    }
}

OSG_END_NAMESPACE
